#include <EEPROMAda.h>
#include <Led.h>
#include <Constantes.h>
#include <bluetooth.h>
#include <balanza.h>
#include <HumedadTemperatura.h>

Bluetooth bt;
Balanza bal;
EEPROMAda eeada;
HumedadTemperatura ht;

char* id_dispositivo;
int accion = INACTIVO;

int idProducto[MAX_ARRAY_SIZE];
int cantidad[MAX_ARRAY_SIZE];
int cantDatos = 0;

Led Encendido        ;
Led ConectadoBT      ;
Led Sirviendo        ;
Led Disponible       ;
Led CantNoDisponible ;

void setup() {
  Serial.begin(9600);
  Serial.print("arranca");

  pinMode(btPairing           , INPUT);
  // Actuadores
  pinMode(sinFin              , OUTPUT);
  pinMode(zumbador            , OUTPUT);

  // necesario para desconectar "a la fuerza" el bt
  pinMode(alimentacionBT      , OUTPUT);

  Encendido        = Led(ledEncendido);
  ConectadoBT      = Led(ledConectadoBT);
  Sirviendo        = Led(ledSirviendo);
  Disponible       = Led(ledDisponible);
  CantNoDisponible = Led(ledCantNoDisponible);
  tone(zumbador, 1000);
  delay(250);
  noTone(zumbador);

  Encendido = HIGH;

  digitalWrite(debugOut, HIGH);
  bt = Bluetooth(btTx, btRx);
  bal = Balanza(balDt, balSck);
  eeada = EEPROMAda(bt);
  ht = HumedadTemperatura(tem_hum);
}

void loop() {
  double b = bal.leerBalanza();
  //if (b > 0) {
    Serial.print("Bal: ");
    Serial.println(b);
  //}
  digitalWrite(alimentacionBT, !digitalRead(btPairing));
  if (bt.isConected()) {
    ConectadoBT = HIGH;
    switch (accion) {
      case INACTIVO:
        accion = bt.leer();
        Serial.print("Accion: ");
        Serial.println(accion);
        break;
      case LEER_UNICO_PROD:
        cantDatos = 1;
        idProducto[0] = bt.leerID();
        cantidad[0] = bt.leerCantidad();
        accion = ESPERAR_NO_PRODUCTO;
        break;
      case LEER_MULTI_PROD:
        int temp = cantDatos = bt.leerCantDatos();
        cantDatos--;
        while (--temp) {
          idProducto[temp] = bt.leerID();
          cantidad[temp] = bt.leerCantidad();
        }
        accion = ESPERAR_NO_PRODUCTO;
        break;
      case ESPERAR_PRODUCTO:
        if (digitalRead(presencia)) {
          //validarProducto(idProducto[cantDatos])// se debe verificar que el producto sea el correcto mediante sensores NFC, quedan pendientes por falta de tiempo y financiamiento
          accion = SENSAR_PESO;
        }
        break;
      case SENSAR_PESO:
        if (cantidad[cantDatos] < bal.leerPesoBalanza()) {
          accion = BAJAR_BRAZO;
        }
        else {
          accion = CANT_NO_DISP;
        }
        break;
      case BAJAR_BRAZO:
        //quedan pendientes por falta de tiempo y financiamiento
        delay(60);
        break;
      case SENSAR_PESO_SINFIN:
        bal.setPesoADepositar(cantidad[cantDatos]);
        accion = EXTRAER_PRODUCTO;
        break;
      case EXTRAER_PRODUCTO:
        analogWrite(sinFin, porcentaje(50));
        if (bal.isPesoAlcanzado()) {
          digitalWrite(sinFin, LOW);
          accion = SUBIR_BRAZO;
        }
        break;
      case SUBIR_BRAZO:
        //quedan pendientes por falta de tiempo y financiamiento
        delay(60);
        break;
      case ESPERAR_NO_PRODUCTO:
        if (!digitalRead(presencia)) {
          if (--cantDatos) {
            accion = ESPERAR_PRODUCTO;
          }
          else {
            accion = INACTIVO;
          }
        }
        break;
      case CANT_NO_DISP:
        CantNoDisponible = HIGH;
        int idprod = idProducto[cantDatos];
        bt.enviar(CANT_NO_DISP, idprod);
        delay(500);
        CantNoDisponible = LOW;
        accion = INACTIVO;
        break;
      case SETEAR_IDDISP:
        bt.leerString(id_dispositivo);
        eeada.escribirID_DIS(id_dispositivo);
        accion = INACTIVO;
        break;
      case ENVIAR_IDDISP:
        id_dispositivo = eeada.leerID_DISP();
        bt.enviar(id_dispositivo);
        accion = INACTIVO;
        break;
      case VALIDAR_HUMEDAD:
        bt.enviar("humedad: ");
        bt.enviar(ht.leerHumedad());
        bt.enviar("temperatura: ");
        bt.enviar(ht.leerHumedad());
        break;
      case BT_CONECTADO:
        break;
      case BT_DESCONECTADO:
        break;
    }
    alertas();
    bt.enviarInfo(accion, bal.pesoBalanza, bal.pesoRequerido);
  }
  else
    ConectadoBT = (millis() % 450 > 200);
}

int porcentaje(int percent) {
  return (255 * percent) / 100;
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

  Serial.print("humedad: ");
  Serial.print(ht.leerHumedad());
  Serial.print("temperatura: ");
  Serial.print(ht.leerHumedad());
  Serial.println();
}
