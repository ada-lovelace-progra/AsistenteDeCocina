#include <EEPROMAda.h>
#include <Led.h>
#include <Constantes.h>
#include <bluetooth.h>
#include <balanza.h>
#include <HumedadTemperatura.h>
#include <Motor.h>

Bluetooth bt;
Balanza bal;
EEPROMAda eeada;
HumedadTemperatura ht;
Motor sinFin;

char* id_dispositivo;
int accion = INACTIVO;
int lastAccion = accion - 1;
int lastAccion2 = accion - 1;

int idProducto[MAX_ARRAY_SIZE];
int cantidad[MAX_ARRAY_SIZE];
int cantDatos = 0;

Led Encendido;
Led ConectadoBT;
Led Sirviendo;
Led Disponible;
Led CantNoDisponible;

void setup() {
  Serial.begin(9600);
  Serial.println("arranca");

  pinMode(btPairing           , INPUT);
  pinMode(presencia           , INPUT);
  // Actuadores
  pinMode(zumbador            , OUTPUT);

  // necesario para desconectar "a la fuerza" el bt
  pinMode(alimentacionBT      , OUTPUT);
  digitalWrite(debugOut, HIGH);
  sinFin = Motor(MT1, MV1, MT2, MV2);
  bal = Balanza(balDt, balSck);
  ht = HumedadTemperatura(tem_hum);
  eeada = EEPROMAda(1);
  bt = Bluetooth(btTx, btRx);

  Encendido        = Led(ledEncendido);
  ConectadoBT      = Led(ledConectadoBT);
  Sirviendo        = Led(ledSirviendo);
  Disponible       = Led(ledDisponible);
  CantNoDisponible = Led(ledCantNoDisponible);
  tone(zumbador, FRECUENCIA);
  delay(100);
  noTone(zumbador);

  Encendido = HIGH;
}

void loop() {
  digitalWrite(alimentacionBT, !digitalRead(btPairing));
  if (bt.isConected()) {
    ConectadoBT = HIGH;
    debug("init loop ");
    switch (accion) {
      case INACTIVO:
        debug();
        accion = bt.leer();
        break;
      case UNAVAILABLE:
        debug();
        accion = bt.leer();
        break;
      case LEER_UNICO_PROD:
        debug();
        cantDatos = 1;
        idProducto[0] = bt.leerID();
        cantidad[0] = bt.leerCantidad();
        accion = ESPERAR_NO_PRODUCTO;
        Serial.println((String)"Id recibido: " + idProducto[0] + " con un peso de " + cantidad[0]);
        break;
      case LEER_MULTI_PROD:
        debug();
        int temp = cantDatos = bt.leerCantDatos();
        cantDatos--;
        while (--temp) {
          idProducto[temp] = bt.leerID();
          cantidad[temp] = bt.leerCantidad();
        }
        accion = ESPERAR_NO_PRODUCTO;
        break;
      case ESPERAR_PRODUCTO:
        debug();
        if (digitalRead(presencia)) {
          //validarProducto(idProducto[cantDatos])// se debe verificar que el producto sea el correcto mediante sensores NFC, quedan pendientes por falta de tiempo y financiamiento
          Serial.print("boton Presionado");
          accion = SENSAR_PESO;
        }
        Serial.print("boton NO Presionado");
        break;
      case SENSAR_PESO:
        debug();
        if (cantidad[cantDatos] < bal.leerPesoBalanza()) {
          accion = BAJAR_BRAZO;
        }
        else {
          accion = CANT_NO_DISP;
        }
        break;
      case BAJAR_BRAZO:
        debug();
        //quedan pendientes por falta de tiempo y financiamiento
        delay(600);
        break;
      case SENSAR_PESO_SINFIN:
        debug();
        bal.setPesoADepositar(cantidad[cantDatos]);
        accion = EXTRAER_PRODUCTO;
        break;
      case EXTRAER_PRODUCTO:
        debug();
        sinFin = 0.5;
        if (bal.isPesoAlcanzado()) {
          sinFin = OFF;
          accion = SUBIR_BRAZO;
        }
        break;
      case SUBIR_BRAZO:
        debug();
        //quedan pendientes por falta de tiempo y financiamiento
        delay(600);
        break;
      case 9:
      Serial.println("entra por 9");
      case ESPERAR_NO_PRODUCTO:
        debug();
//        if (!digitalRead(presencia)) {
          
          Serial.print("boton NO Presionado");
          if (cantDatos--) {
            accion = ESPERAR_PRODUCTO;
          }
          else {
            accion = INACTIVO;
          }
//        }
//        else
          Serial.print("boton Presionado");
        break;
      case CANT_NO_DISP:
        debug();
        CantNoDisponible = HIGH;
        int idprod = idProducto[cantDatos];
        bt.enviar(CANT_NO_DISP, idprod);
        delay(500);
        CantNoDisponible = LOW;
        accion = INACTIVO;
        break;
      case SETEAR_IDDISP:
        debug();
        bt.leerString(id_dispositivo);
        eeada.escribirID_DIS(id_dispositivo);
        accion = INACTIVO;
        break;
      case ENVIAR_IDDISP:
        debug();
        id_dispositivo = eeada.leerID_DISP();
        bt.enviar(id_dispositivo);
        accion = INACTIVO;
        break;
      case VALIDAR_HUMEDAD:
        debug();
        bt.enviar("humedad: ");
        bt.enviar(ht.leerHumedad());
        bt.enviar("temperatura: ");
        bt.enviar(ht.leerHumedad());
        break;
      case BT_CONECTADO:
        debug();
        break;
      case BT_DESCONECTADO:
        debug();
        break;
     default:   
        debug();
        Serial.print("entro por default");
        accion = INACTIVO;
      break;
    }
    //  bt.enviarInfo(accion, bal.pesoBalanza, bal.pesoRequerido);
  } else
    ConectadoBT = (millis() % 450 > 200);

    alertas();
  //  delay(500);
}

//////////////////////////// ALERTAS
void alertas() {

  Sirviendo = accion == EXTRAER_PRODUCTO;

  if (!bt.isConected())
    ConectadoBT = (millis() % 450 > 200);
  else
    ConectadoBT = HIGH;

  Disponible = (accion == INACTIVO ? HIGH : (int)(millis() / 250) % 2);

  if (zumbadorTime - millis() < tiempoZumbador) {
    if (millis() % (zumbadorTime / 4) < (zumbadorTime / 4) * 0.7)
      tone(zumbador, FRECUENCIA); // deberia hacer un pipipipi....
    else
      noTone(zumbador);
  }
  else {
    noTone(zumbador);
  }

  //bt.enviar((String)"humedad: " + ht.leerHumedad() + "\ttemperatura: " + ht.leerHumedad() + "\tBalanza: " + bal.leerBalanza() + "Acc: " + accion);
}


void debug(String c) {
  if (lastAccion != accion) {
    Serial.println(c+"Accion: "+accion);
    lastAccion = accion;
  }
}

void debug() {
  if (lastAccion2 != accion) {
    Serial.print("Accion: ");
    Serial.println(accion);
    lastAccion2 = accion;
  }
}
