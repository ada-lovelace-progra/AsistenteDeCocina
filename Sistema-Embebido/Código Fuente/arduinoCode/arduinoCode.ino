#include "constantes.h"
#include "bluethoot.h"
#include "balanza.h"

int accion = SIN_ACCION;
int pesoADepositar = 0;
int zumbadorTime = 0;
bool btConectado;
int pesoBalanza;
int pesoRequerido;



float calibration_factor = 2230;

char* nombre;

void setup() {
  bal.begin(62, 63);

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

  digitalWrite(debugOut, HIGH);

  nombre = leerProducto();
}

void loop() {// no usar delay()
  digitalWrite(alimentacionBT, !digitalRead(btPairing));
  //  estadoBT();
  if (btConectado || bt.available() > 0) {
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
            zumbadorTime = millis();
            accion = RETORNAR_A_REPOSO;
          }
        }
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
        enviarHumedad();
        accion = VALIDAR_HUMEDAD;
        break;

      case VALIDAR_HUMEDAD:
        if (bt.available()) {
          if (bt.read())
            accion = SACAR_CONTENIDO;
          else
            accion = RETORNAR_A_REPOSO;
        }
        break;

      case RETORNAR_A_REPOSO:
        //UNIMPLEMENT
        if (digitalRead(debugIn))
          delay(1000);
        accion = SIN_ACCION;
        break;

      case SETEAR_NOMBRE:
        escribirProducto();
        accion = SIN_ACCION;
        break;

      case ENVIAR_NOMBRE:
        bt.print(ENVIAR_NOMBRE);
        leerProducto();
        bt.print(nombre);
        bt.print(0);
        accion = SIN_ACCION;
        break;
      case BT_DESCONECTADO:
        btConectado = 0;
        break;
      case BT_CONECTADO:
        btConectado = 1;
        break;
    }
    alertas();
    enviarInfo();
  }
  else
    digitalWrite(ledConectadoBT, (millis() % 450 > 200));
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
  long peso = 0;
  if (bal.is_ready()) {
    peso  = bal.read();
    if (peso < 0)
      peso = 0.00;

    return peso;
  }
}
//////////////////////////// Info
void enviarInfo() {
  bt.print(1);
  bt.print(accion);

  if (accion == SACAR_CONTENIDO) {
    bt.print(ledSirviendo);
    bt.print((millis() % 500 > 250));
  }

  bt.print(ledDisponible);
  bt.print(accion == SIN_ACCION);

  bt.print(ledCantNoDisponible);
  bt.print(pesoBalanza > pesoRequerido);
}

void enviarHumedad() {
  bt.print(humedad);
  bt.print(analogRead(humedad));
}

//////////////////////////// ALERTAS
void alertas() {
  if (accion == SACAR_CONTENIDO)
    digitalWrite(ledSirviendo, (millis() % 500 > 250));

  if (!btConectado)
    digitalWrite(ledConectadoBT, (millis() % 450 > 200));
  else
    digitalWrite(ledConectadoBT, HIGH);

  digitalWrite(ledDisponible, accion == SIN_ACCION);

  if (zumbadorTime - millis() < tiempoZumbador)
    digitalWrite(zumbador, millis() % (zumbadorTime / 4) < (zumbadorTime / 4) * 0.7); // deberia hacer un pipipipi....

  digitalWrite(ledCantNoDisponible, pesoBalanza > pesoRequerido);
}

//////////////////////////// EEPROM
void escribirProducto() {
  int index = -1;
  while (bt.read()) {
    index++;
    EEPROM.write(index, nombre[index]);
  }
}

char* leerProducto() {
  int index = 0;
  char c = 0;
  do {
    c = EEPROM.read(index);
    nombre[index++] = c;
  } while (c);
}
