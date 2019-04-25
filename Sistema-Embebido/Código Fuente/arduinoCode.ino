#include "SoftwareSerial.h"
#include "HX711.h"


/////// constantes
int SIN_ACCION = 0;
int SACAR_CONTENIDO = 1;
/////// constantes


SoftwareSerial bt(9, 10); // RX, TX
HX711 bal(5, 6);

bool isInAction = false;
int pesoADepositar = 0;

float calibration_factor = 2230;

void setup() {
  bt.begin(9600);
  bt.print("AT + NAMELaJarraDeAda");
  bt.print("AT + PINpass");

  bal.set_scale();
  bal.tare();

  // Sensores
  pinMode(presencia           , INPUT);
  pinMode(humedad             , INPUT);
  pinMode(temperatura         , INPUT);
  pinMode(btPairing           , INPUT);

  // Actuadores
  pinMode(sinFin              , OUTPUT);
  pinMode(zumbador            , OUTPUT);
  pinMode(ledEncendido        , OUTPUT);
  pinMode(ledConectadoBT      , OUTPUT);
  pinMode(ledSirviendo        , OUTPUT);
  pinMode(ledDisponible       , OUTPUT);
  pinMode(ledCantNoDisponible , OUTPUT);

}

void loop() {// no usar delay()
  switch (accion) {

    case SIN_ACCION:
      leerBT();
      break;

    case SACAR_CONTENIDO:
      if (digitalRead(presencia) == HIGH) {
        pesoBalanza = leerBalanza();
        if (pesoADepositar == 0)
          leerPesoADepositar();
        if (pesoRequerido == 0)
          pesoRequerido = pesoADepositar - pesoBalanza;
        if (pesoRequerido != pesoBalanza)
          analogWrite(sinFin, porcentaje(50)); //0-255
        else
          accion = SIN_ACCION;
      }
      break;

    case MOVER_BRAZO:
    case BAJAR_SINFIN:
      //UNIMPLEMENTED
      break;
  }
  alertas();
}

void leerPesoADepositar() {
  if (bt.available() > 3)
    pesoADepositar =  bt.read() * 256
                      + bt.read() * 256 * 256
                      + bt.read() * 256 * 256 * 256
                      + bt.read() * 256 * 256 * 256 * 256;
}

void leerBT() {
  if (bt.available() > 0)
    accion = bt.read();
}

int porcentaje(int percent) {
  return (255 * percent) / 100;
}

float leerBalanza() {
  float peso = bal.get_units(), 10;
  if (peso < 0)
    peso = 0.00;

  return peso;
}

//////////////////////////// ALERTAS

void alertas() {
  alertaHumedad();

}

void alertaHumedad() {
  bt.print(analogRead(humedad));
}
