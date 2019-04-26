#include "SoftwareSerial.h"
#include "HX711.h"

/////// constantes
#define SIN_ACCION           0;
#define SACAR_CONTENIDO      1;
#define MOVER_BRAZO          2;
#define BAJAR_SINFIN         3;
#define RETORNAR_A_REPOSO    4;

/////// Sensores
#define humedad             68;
#define temperatura         69;
#define presencia           48;
#define btPairing           49;
#define balanza             50; // no se usa como pin para sensor, se utiliza para enviar al celular

/////// Actuadores
#define sinFin              44;
#define zumbador            13;
#define ledEncendido        12;
#define ledConectadoBT      11;
#define ledSirviendo        10;
#define ledDisponible        9;
#define ledCantNoDisponible  8;

#define alimentacionBT      23;
#define tiempoZumbador     150;

SoftwareSerial bt(20, 21); // RX, TX
HX711 bal(62, 63);

int accion = SIN_ACCION;
int pesoADepositar = 0;
int zumbadorTime = 0;

float calibration_factor = 2230;

void setup() {
  bt.begin(9600);
  bt.print("AT + NAMELaJarraDeAda"); // porque es todo de ada?
  //porque la flaca fue la primer persona en programar
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

  // necesario para desconectar "a la fuerza" el bt
  pinMode(alimentacionBT      , OUTPUT);

  digitalWrite(ledEncendido, HIGH);
}

void loop() {// no usar delay()
  digitalWrite(alimentacionBT, !digitalRead(btPairing));

  if (btConectado) {
    digitalWrite(ledConectadoBT, HIGH);
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
          else {
            analogWrite(sinFin, 0); //0-255
            pesoRequerido = 0;
            pesoADepositar = 0;
            zumbadorTime = milis();
            accion = RETORNAR_A_REPOSO;
          }
        }
        break;

      case MOVER_BRAZO:
        //UNIMPLEMENTED
        accion = BAJAR_SINFIN;
        break;

      case BAJAR_SINFIN:
        //SEMI-IMPLEMENTED
        enviarHumedad();
        accion = SACAR_CONTENIDO;
        break;

      case RETORNAR_A_REPOSO:
        //UNIMPLEMENT
        accion = SIN_ACCION;
        break;
    }
    alertas();
    enviarInfo();
  }
  else
    digitalWrite(ledConectadoBT, (milis() % 450 > 200));
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

//////////////////////////// Info
void enviarInfo() {
  bt.print(1)
  bt.print(accion);

  if (accion == SACAR_CONTENIDO)
  {
    bt.print(ledSirviendo);
    bt.print((milis() % 500 > 250));
  }

  bt.print(ledDisponible);
  bt.print(accion == SIN_ACCION);

  bt.print(ledCantNoDisponible);
  bt.print(pesoBalanza > pesoRequerido);
}

void enviarHumedad() {
  bt.print(balanza);
  bt.print(analogRead(humedad));
}

//////////////////////////// ALERTAS
void alertas() {
  if (accion == SACAR_CONTENIDO)
    digitalWrite(ledSirviendo, (milis() % 500 > 250));

  if (!btConectado)
    digitalWrite(ledConectadoBT, (milis() % 450 > 200));
  else
    digitalWrite(ledConectadoBT, HIGH);

  digitalWrite(ledDisponible, accion == SIN_ACCION);

  if (zumbadorTime - milis() < tiempoZumbador)
    digitalWrite(zumbador, milis() % (zumbadorTime / 4) < (zumbadorTime / 4) * 0.7); // deberia hacer un pipipipi....

  digitalWrite(ledCantNoDisponible, pesoBalanza > pesoRequerido);
}
