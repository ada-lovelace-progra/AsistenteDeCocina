#include "libraries/Constantes/Constantes.h"
#include "libraries/bluethoot/bluethoot.h"
#include "libraries/balanza/balanza.h"
#include "libraries/EEPROMAda/EEPROMAda.h"
#include "libraries/Led/Led.h"

Bluethoot bt(btTx, btRx);
Balanza bal(balDt, balSck);

char* producto;
long id_dispositivo;
int accion = SIN_ACCION;

int pesoRequerido;
int pesoADepositar;
int zumbadorTime;
int humedadLevel;

Led Encendido        (ledEncendido);
Led ConectadoBT      (ledConectadoBT);
Led Sirviendo        (ledSirviendo);
Led Disponible       (ledDisponible);
Led CantNoDisponible (ledCantNoDisponible);

void setup() {
  pinMode(btPairing           , INPUT);

  // Actuadores
  pinMode(sinFin              , OUTPUT);
  pinMode(zumbador            , OUTPUT);
  
  // necesario para desconectar "a la fuerza" el bt
  pinMode(alimentacionBT      , OUTPUT);

  digitalWrite(ledEncendido, HIGH);

  digitalWrite(debugOut, HIGH);

  producto = EEPROMAda::leerProducto();
}

void loop() {// no usar delay()
  digitalWrite(alimentacionBT, !digitalRead(btPairing));
  if (bt.isConected()) {
    digitalWrite(ledConectadoBT, HIGH);
    switch (accion) {
      case SIN_ACCION:
        accion = bt.leer();
        break;

      case SACAR_CONTENIDO:
        if (digitalRead(presencia) == HIGH) {

          if (!bal.isPesoAlcanzado())
            analogWrite(sinFin, porcentaje(50)); //0-255
          else {
            analogWrite(sinFin, 0); //0-255
            pesoRequerido = 0;
            pesoADepositar = 0;
            zumbadorTime = millis();
            accion = RETORNAR_A_REPOSO;
          }
        }
        else analogWrite(sinFin, 0); //0-255
        break;

      case MOVER_BRAZO:
        //UNIMPLEMENTED
        if (digitalRead(debugIn))
          delay(1000);
        accion = BAJAR_SINFIN;
        break;

      case BAJAR_SINFIN:
        //SEMI-IMPLEMENTED
        if (digitalRead(debugIn))
          delay(1000);
        bt.enviarHumedad(humedadLevel);
        accion = VALIDAR_HUMEDAD;
        break;

      case VALIDAR_HUMEDAD:
        accion = bt.leer();
        break;

      case RETORNAR_A_REPOSO:
        //UNIMPLEMENT
        if (digitalRead(debugIn))
          delay(1000);
        accion = SIN_ACCION;
        break;

      case SETEAR_NOMBRE:
        bt.leerString(producto);
        EEPROMAda::escribirProducto(producto);
        accion = SIN_ACCION;
        break;

      case ENVIAR_NOMBRE:
        bt.enviar(ENVIAR_NOMBRE);
        producto = EEPROMAda::leerProducto();
        bt.enviar(producto);
        bt.enviar(0);
        accion = SIN_ACCION;
        break;
    }
    alertas();
    bt.enviarInfo(accion);
  }
  else
    digitalWrite(ledConectadoBT, (millis() % 450 > 200));
}

void leerPesoADepositar() {
  pesoADepositar = bt.leer_4bytes();
}


int porcentaje(int percent) {
  return (255 * percent) / 100;
}

//////////////////////////// ALERTAS
void alertas() {
  if (accion == SACAR_CONTENIDO)
    digitalWrite(ledSirviendo, (millis() % 500 > 250));

  if (bt.isConected())
    digitalWrite(ledConectadoBT, (millis() % 450 > 200));
  else
    digitalWrite(ledConectadoBT, HIGH);

  digitalWrite(ledDisponible, accion == SIN_ACCION);

  if (zumbadorTime - millis() < tiempoZumbador)
    digitalWrite(zumbador, millis() % (zumbadorTime / 4) < (zumbadorTime / 4) * 0.7); // deberia hacer un pipipipi....

  digitalWrite(ledCantNoDisponible, bal.isPesoAlcanzado());
}
