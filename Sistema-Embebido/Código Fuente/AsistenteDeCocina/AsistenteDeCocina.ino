#include <Constantes.h>
#include <EEPROMAda.h>
#include <Led.h>
#include <Bluetooth.h>
#include <Balanza.h>
#include <Motor.h>
#include <HumedadTemperatura.h>

// objetos para controlar los modulos conectados
Bluetooth bt;
Balanza bal;
EEPROMAda eeada;
HumedadTemperatura ht;
Motor sinFin;

// objetos para controlar los leds conectados
Led Encendido;
Led ConectadoBT;
Led Sirviendo;
Led Disponible;
Led CantNoDisponible;

// variables de estado necesarias para la ejecucion
char* id_dispositivo;
int accion = INACTIVO;
int idProducto[MAX_ARRAY_SIZE];
int cantidad[MAX_ARRAY_SIZE];
int cantDatos = 0;
bool alertaHumedad = false;
bool alertaTemperatura = false;

// varibles de timeout
int lastAccionForTimeout = accion - 1;
unsigned long timeFromLastAccion = 0;

// variables para interrupccion
int interrupt = NO_INTERRUPT;
int lastInterrupt = NO_INTERRUPT;
unsigned long timeFromLastInterrupt = 0;

// variables para debug
unsigned long debugTime = 0;
int lastAccion = accion - 1;
int lastAccion2 = accion - 1;

void setup() {
  Serial.begin(9600);
  if (isInDebug())
    Serial.println("arranca");

  pinMode(presencia           , INPUT);
  // Actuadores
  pinMode(zumbador            , OUTPUT);

  digitalWrite(debugOut, HIGH);

  sinFin.begin(SF1, SF2, SFP);
  bal.begin(balDt, balSck);
  ht.begin(tem_hum);
  eeada.begin();
  bt.begin(btTx, btRx);

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
    if (isAccion(temp))
      accion = temp;
    else if (isInterrupt(temp)) {
      interrupt = temp;
      timeFromLastInterrupt = millis() - timeFromLastInterrupt;
    }

    alertasBT();
  } else
    ConectadoBT = (millis() % 450 > 200);

  if (interrupt == NO_INTERRUPT) {
    controlDeTimeout();
    estados();
  }
  alertas();
}

void estados() {
  if (accion == INACTIVO || accion == UNAVAILABLE) {
    debug();
    if (accion != INACTIVO)
      Serial.println((String)"Accion Seteada con '" + accion + "'");

  } else if (accion == LEER_UNICO_PROD) {
    debug();
    cantDatos = 1;
    idProducto[0] = bt.leerID();
    cantidad[0] = bt.leerCantidad();
    accion = ESPERAR_NO_PRODUCTO;
    debug((String)"Id recibido: " + idProducto[0] + " con un peso de " + cantidad[0]);

  } else if (accion == LEER_MULTI_PROD) {
    debug();
    int temp = cantDatos = bt.leerCantDatos();
    cantDatos--;
    while (--temp) {
      idProducto[temp] = bt.leerID();
      cantidad[temp] = bt.leerCantidad();
      Serial.println((String)"Id recibido: " + idProducto[temp] + " con un peso de " + cantidad[temp]);
    }
    accion = ESPERAR_NO_PRODUCTO;

  } else if (accion == ESPERAR_PRODUCTO) {
    debug();
    if (digitalRead(presencia)) {
      Serial.println("boton presionado");
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
    accion = EXTRAER_PRODUCTO;

  } else if (accion == SENSAR_PESO_SINFIN) {
    debug();
    bal.setPesoADepositar(cantidad[cantDatos]);
    accion = EXTRAER_PRODUCTO;

  } else if (accion == EXTRAER_PRODUCTO) {
    debug();
    sinFin++;

    if (bal.isPesoAlcanzado()) {
      Serial.println((String)"Se alcanzo el peso: " + cantidad[cantDatos] + " en balanza:" + bal.leerPesoBalanza());
      sinFin = OFF;
      accion = DEVOLVER_PROD;
    }

  } else if (accion == DEVOLVER_PROD) {
    sinFin--;
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
    if (!digitalRead(presencia)) {
      Serial.println("boton NO Presionado");
      if (cantDatos--) {
        accion = ESPERAR_PRODUCTO;
      }
      else {
        accion = INACTIVO;
      }
    }

  } else if (accion == CANT_NO_DISP) {
    debug();
    CantNoDisponible = HIGH;
    int idprod = idProducto[cantDatos];
    bt.enviar(CANT_NO_DISP, idprod);
    delay(2000);
    CantNoDisponible = LOW;
    accion = INACTIVO;

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
    Serial.println("entro por default");
    accion = INACTIVO;
  }
}

void controlDeTimeout() {
  if (lastAccionForTimeout != accion) {
    timeFromLastAccion = millis();
    lastAccionForTimeout = accion;
  }
  unsigned int times = millis() - timeFromLastAccion - timeFromLastInterrupt;
  if (accion == INACTIVO) {
  } else if (accion == UNAVAILABLE) {
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
  } else if (accion == SENSAR_PESO) {
  } else if (accion == BAJAR_BRAZO) {
  } else if (accion == SENSAR_PESO_SINFIN) {
  } else if (accion == EXTRAER_PRODUCTO) {
  } else if (accion == SUBIR_BRAZO) {
  } else if (accion == ESPERAR_NO_PRODUCTO) {
    if (times > TIMEOUTESPERAR_NO_PRODUCTO) {
      debugTimeout(times);
      cantDatos = 0;
      bt.enviar(TIMEOUT_CUMPLIDO, accion);
      accion = INACTIVO;
    }
  } else if (accion == CANT_NO_DISP) {
  } else if (accion == SETEAR_IDDISP) {
  } else if (accion == ENVIAR_IDDISP) {
  } else if (accion == VALIDAR_HUMEDAD) {
  } else if (accion == BT_CONECTADO) {
  } else if (accion == BT_DESCONECTADO) {
  } else {
  }
}

void interrupciones() {
  if (interrupt == NO_INTERRUPT)
    return;
  else if (interrupt == FRENAR_SINFIN) {

  }
  else
    serialD("Entro por default con interrupcionid: " + interrupt);
}

bool isAccion(int temp) {
  return (temp == LEER_MULTI_PROD || temp ==  LEER_UNICO_PROD || temp == SETEAR_IDDISP || temp == ENVIAR_IDDISP);
}

bool isInterrupt(int temp) {
  return (temp == FRENAR_SINFIN);
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
}

void alertas() {

  Sirviendo = accion == EXTRAER_PRODUCTO;

  if (!bt.isConected())
    ConectadoBT = (millis() % 450 > 200);
  else
    ConectadoBT = HIGH;

  if (interrupt != NO_INTERRUPT)
    Encendido = (int)(millis() / 350) % 2;

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

int debugLoopTimes = 1000;
void debugLoop() {
  if (false && isInDebug() && !debugLoopTimes--) {
    debugLoopTimes = 1000;
    Serial.println((String)"Tiempo entre loops: " + (debugTime = millis() - debugTime) / 1000);
  }
}

void debugTimeout(unsigned int times) {
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
    Serial.println((String) c);
}

void debug() {
  if (isInDebug())
    if (lastAccion2 != accion) {
      Serial.println((String)"Accion: " + accion);
      lastAccion2 = accion;
    }
}
