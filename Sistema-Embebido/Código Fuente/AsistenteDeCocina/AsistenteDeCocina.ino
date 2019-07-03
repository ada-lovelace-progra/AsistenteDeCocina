#include <Constantes.h>
#include <EEPROMAda.h>
#include <Led.h>
#include <Bluetooth.h>
#include <Balanza.h>
#include <Motor.h>
#include <HumedadTemperatura.h>
#include <Extras.h>

// objetos para controlar los modulos conectados
Bluetooth bt;
Balanza bal;
EEPROMAda eeada;
HumedadTemperatura ht;
Motor sinFin;
Extras extras;
int vecesEnInterrupcion = 0;

// objetos para controlar los leds conectados
Led Encendido;
Led ConectadoBT;
Led Sirviendo;
Led Disponible;
Led CantNoDisponible;

// variables de estado necesarias para la ejecucion
char* id_dispositivo;
int accion = INACTIVO;
long idProducto[MAX_ARRAY_SIZE];
unsigned long cantidad[MAX_ARRAY_SIZE];
long cantDatos = 0;

// variables para comunicacion con android
bool alertaHumedad = false;
bool alertaTemperatura = false;
int errorCode = NO_ERROR;
int notifCode = NO_NOTIF;
char lastAccion = accion - 1;

// varibles de timeout
int lastAccionForTimeout = accion - 1;
unsigned long timeFromLastAccion = 0;

// variables para interrupccion
int interrupt = NO_INTERRUPT;
int lastInterrupt = NO_INTERRUPT;
unsigned long timeFromLastInterrupt = 0;

// variables para debug
unsigned long debugTime = 0;
char lastAccion2 = accion - 1;

void setup() {
  Serial.begin(9600);
  serialD("arranca");

  pinMode(presencia           , INPUT);
  // Actuadores
  pinMode(zumbador            , OUTPUT);


  pinMode(debugOut, OUTPUT);
  pinMode(debugIn, INPUT);

  digitalWrite(debugOut, HIGH);

  sinFin.begin(SF1, SF2, SFP);
  bal.begin(balDt, balSck);
  ht.begin(tem_hum);
  eeada.begin();
  bt.begin(btTx, btRx);
  extras.begin(zumbador);

  Encendido.begin(ledEncendido);
  ConectadoBT.begin(ledConectadoBT);
  Sirviendo.begin(ledSirviendo);
  Disponible.begin(ledDisponible);
  CantNoDisponible.begin(ledCantNoDisponible);
  tone(zumbador, FRECUENCIA, 200);

  //while (digitalRead(pulsadorOn));  //opcional para poner una tecla para que arranque

  Encendido = HIGH;
}

void loop() {
  debugLoop();
  if (bt.isConected()) {
    int temp = bt.leerEstado();
    if (isAccion(temp) && accion == INACTIVO) {
      accion = temp;
      bt.enviarAccion(accion);
    }
    else if (isInterrupt(temp)) {
      interrupt = temp;
      timeFromLastInterrupt = millis() - timeFromLastInterrupt;
    }

    alertasBT();
  }

  if (interrupt == NO_INTERRUPT) {
    controlDeTimeout();
    estados();
  }
  else
    interrupciones();

  alertas();
}

void estados() {
  if (accion == INACTIVO || accion == UNAVAILABLE) {
    debug();

  } else if (accion == LEER_UNICO_PROD) {
    debug();
    cantDatos = 1;
    idProducto[0] = bt.leerID();
    cantidad[0] = bt.leerCantidad();
    accion = ESPERAR_PRODUCTO;
    debug((String)"Id recibido: " + idProducto[0] + " con un peso de " + cantidad[0]);

  } else if (accion == LEER_MULTI_PROD) {
    debug();
    unsigned long temp = -1;
    unsigned long cantDatos = bt.leerCantDatos();
    serialD("ccantidad seteada con " + (unsigned long)cantDatos);
    while (cantDatos - ++temp) {
      serialD("ENTRO WHILE MULTIPROD");
      idProducto[temp] = bt.leerID();
      cantidad[temp] = bt.leerCantidad();
      serialD((String)"Id recibido: " + idProducto[temp] + " con un peso de " + cantidad[temp] + " faltan " + (cantDatos - temp) + " productos");
    }
    accion = ESPERAR_PRODUCTO;
    cantDatos--;
  } else if (accion == ESPERAR_PRODUCTO) {
    debug();
    if (bal.isProducto()) {
      serialD("hay algo en la balanza");
      //validarProducto(idProducto[cantDatos])// se debe verificar que el producto sea el correcto mediante sensores NFC, quedan pendientes por falta de tiempo y financiamiento
      accion = SENSAR_PESO;
    }

  } else if (accion == SENSAR_PESO) {
    debug();
    if (cantidad[cantDatos] < bal.leerPesoBalanza()) {
      accion = BAJAR_BRAZO;
    }
    else {
      accion = CANT_NO_DISP;
    }

  } else if (accion == BAJAR_BRAZO) {
    debug();
    //quedan pendientes por falta de tiempo y financiamiento
    delay(600);
    accion = SENSAR_PESO_SINFIN;

  } else if (accion == SENSAR_PESO_SINFIN) {
    debug();
    bal.setPesoADepositar(cantidad[cantDatos]);
    accion = EXTRAER_PRODUCTO;

  } else if (accion == EXTRAER_PRODUCTO) {
    if (digitalRead(presencia)) {
      sinFin = 0;
      errorCode = ERROR_NO_TACHO;
      serialD("NO tacho");
    } else {

      debug();
      sinFin = 1;
      
      if (bal.isPesoAlcanzado()) {
        serialD((String)"Se alcanzo el peso: " + cantidad[cantDatos] + " en balanza:" + bal.leerPesoBalanza());
        sinFin = OFF;
        accion = DEVOLVER_PROD;
      }
    }
  } else if (accion == DEVOLVER_PROD) {
    sinFin = -1;
    if (millis() - timeFromLastAccion > TIME_DEVOLVER_PROD) {
      accion = SUBIR_BRAZO;
    }

  } else if (accion == SUBIR_BRAZO) {
    debug();
    //quedan pendientes por falta de tiempo y financiamiento
    delay(600);
    accion = ESPERAR_NO_PRODUCTO;

  } else if (accion == ESPERAR_NO_PRODUCTO) {
    debug();
    if (!bal.isProducto()) {
      serialD("sacaron el prod de la balanza");
    }
    if (--cantDatos >= 0) {
      accion = ESPERAR_PRODUCTO;
    } else
      accion = INACTIVO;

  } else if (accion == CANT_NO_DISP) {
    debug();
    serialD((String)"Cantidad no disponible con " + cantidad[0] + "gramos pedidos y " + bal.leerBalanza() + "gramos en balanza");
    CantNoDisponible = HIGH;
    char idprod = idProducto[cantDatos];
    bt.enviar(CANT_NO_DISP, idprod);
    delay(1000);
    CantNoDisponible = LOW;
    accion = INACTIVO;
    errorCode = CANT_NO_DISP;

  } else if (accion == SETEAR_IDDISP) {
    debug();
    bt.leerString(id_dispositivo);
    eeada.escribirID_DIS(id_dispositivo);
    accion = INACTIVO;

  } else if (accion == ENVIAR_IDDISP) {
    debug();
    id_dispositivo = eeada.leerID_DISP();
    bt.enviar(id_dispositivo);
    accion = INACTIVO;

  } else {
    serialD("entro por default");
    accion = INACTIVO;
  }
}

void controlDeTimeout() {
  if (lastAccionForTimeout != accion) {
    timeFromLastAccion = millis();
    lastAccionForTimeout = accion;
  }
  unsigned long times = millis() - timeFromLastAccion - timeFromLastInterrupt;
  if (accion == INACTIVO || accion == UNAVAILABLE) {
  } else if (accion == LEER_UNICO_PROD) {
    if (times > TIMEOUTLEER_UNICO_PROD) {
      debugTimeout(times);
      cantDatos = 0;
      bt.enviar(TIMEOUT_CUMPLIDO, accion);
      accion = INACTIVO;
    }
  } else if (accion == LEER_MULTI_PROD) {
    if (times > TIMEOUTLEER_MULTI_PROD) {
      debugTimeout(times);
      cantDatos = 0;
      bt.enviar(TIMEOUT_CUMPLIDO, accion);
      accion = INACTIVO;
    }
  } else if (accion == ESPERAR_PRODUCTO) {
    if (times > TIMEOUTESPERAR_PRODUCTO) {
      debugTimeout(times);
      cantDatos = 0;
      bt.enviar(TIMEOUT_CUMPLIDO, accion);
      accion = INACTIVO;
    }
  } else if (accion == ESPERAR_NO_PRODUCTO) {
    if (times > TIMEOUTESPERAR_NO_PRODUCTO) {
      debugTimeout(times);
      cantDatos = 0;
      bt.enviar(TIMEOUT_CUMPLIDO, accion);
      accion = INACTIVO;
    }
  } else {
    if (times > TIMEOUT_POR_DEFAULT) {
      serialD("Se cumplio el timeout por default de la siguiente accion: " + accion);
    }
  }
}

void interrupciones() {
  if (interrupt == NO_INTERRUPT)
    return;
  else {
    if (!vecesEnInterrupcion)
      vecesEnInterrupcion = 1000;

    if (!--vecesEnInterrupcion)
      interrupt = NO_INTERRUPT;

    serialD((String)"entra en interrupccion: " + interrupt + " falta " + vecesEnInterrupcion + " ciclos");
    if (interrupt == ENCENDER_LED) {
      if (vecesEnInterrupcion > 30)
        vecesEnInterrupcion = 29;
      extras.exec();
    } else if (interrupt == GIRAR_SINFIN_HORARIO) {
      if (vecesEnInterrupcion >= 1)
        sinFin++;
      else
        sinFin = OFF;
    } else if (interrupt == GIRAR_SINFIN_ANTIHORARIO) {
      if (vecesEnInterrupcion >= 1)
        sinFin--;
      else
        sinFin = OFF;
    } else if (interrupt == DETENER_SINFIN) {
      sinFin = OFF;
      vecesEnInterrupcion = 0;
    } else
      serialD("Entro por default con interrupcionid: " + interrupt);
  }
}

bool isAccion(int  temp) {
  return (temp == LEER_MULTI_PROD || temp ==  LEER_UNICO_PROD || temp == SETEAR_IDDISP || temp == ENVIAR_IDDISP);
}

bool isInterrupt(int  temp) {
  return temp == ENCENDER_LED || temp == GIRAR_SINFIN_HORARIO || temp == GIRAR_SINFIN_ANTIHORARIO || temp == DETENER_SINFIN;
}

//////////////////////////// ALERTAS
void alertasBT() {
  if (alertaHumedad) {
    bt.enviar(HUMEDAD, ht.leerHumedad());
    alertaHumedad = false;
  }
  if (alertaTemperatura) {
    bt.enviar(TEMPERATURA, ht.leerTemperatura());
    alertaTemperatura = false;
  }
  bt.enviarAccion(accion);

  if (errorCode != NO_ERROR) {
    bt.enviarError(errorCode);
    errorCode = NO_ERROR;
  }

  if (notifCode != NO_NOTIF) {
    bt.enviarNotif(notifCode);
    notifCode = NO_NOTIF;
  }
}

void alertas() {

  Sirviendo = accion == EXTRAER_PRODUCTO;

  if (!bt.isConected())
    ConectadoBT = (millis() % 450 > 200);
  else
    ConectadoBT = HIGH;

  if (interrupt != NO_INTERRUPT)
    Encendido = (int)(millis() / 350) % 2;
  else
    Encendido = HIGH;

  Disponible = (accion == INACTIVO ? HIGH : (int)(millis() / 250) % 2);

  if (zumbadorTime - millis() < tiempoZumbador) {
    if (millis() % (zumbadorTime / 4) < (zumbadorTime / 4) * 0.7)
      tone(zumbador, FRECUENCIA);
    else
      noTone(zumbador);
  }
  else {
    noTone(zumbador);
  }
}

//////////////////////////// DEBUG
bool isInDebug() {
  return digitalRead(debugIn);
}

double vecesporloop = 10000;
unsigned long debugLoopTimes = vecesporloop;
void debugLoop() {
  if (isInDebug() && !debugLoopTimes--) {
    debugLoopTimes = vecesporloop;
    Serial.println((String)"Tiempo entre loops: " + (debugTime = millis() - debugTime) / vecesporloop + "ms con accion: " + accion + " e interrupccion: " + interrupt + " con cantDatos: " + cantDatos + " peso en balanza: " + bal.leerBalanza());
  }
}

void debugTimeout(unsigned long times) {
  if (isInDebug())
    Serial.println((String)"Se cumplio el timeout de " + times + "ms de la accion " + accion);
}

void debug(String c) {
  if (isInDebug())
    if (lastAccion != accion) {
      Serial.println((String)c + "Accion: " + accion);
      lastAccion = accion;
    }
}

void serialD(String c) {
  if (isInDebug())
    Serial.println(c);
}

void debug() {
  if (isInDebug())
    if (lastAccion2 != accion) {
      Serial.println((String)"Accion: " + accion);
      lastAccion2 = accion;
    }
}
