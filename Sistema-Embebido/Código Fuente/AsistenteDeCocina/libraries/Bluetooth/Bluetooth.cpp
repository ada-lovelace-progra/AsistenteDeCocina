#include <Bluetooth.h>
#include <Constantes.h>

Bluetooth::Bluetooth(int tx, int rx) : bt(SoftwareSerial(tx,rx)){
  bt.begin(9600);
  bt.print("AT");
  delay(1000);
  bt.print("AT+NAME");
  bt.print("LaCocinaDeAda"); // porque es todo de ada?
  //porque la flaca fue la primer persona en programar
  delay(1000);
  bt.print("AT+PIN");
  bt.print("adita");
  delay(1000);
  bt.print("AT+BPS");
  bt.print("4");

  conected = false;
}

int Bluetooth::leer() {
  if (!bt.available())
    return -1;

  int r = bt.read();
  if (conected) {
    if (r == BT_DESCONECTADO) {
      conected = false;
      return r;
    }
    else{
      return r;
    }
  }
  else {
    if (r == BT_CONECTADO) {
      conected = true;
      return r;
    }
  }
}

char* Bluetooth::leerString(char* c){
  int i=-1;
  char t=bt.read();

  while(t){
    c[++i]=t;
    t=bt.read();
  }
  return c;
}

void Bluetooth::enviarInfo(int accion, int pesoBalanza, int pesoRequerido) {
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

void Bluetooth::enviarHumedad(double humedadLevel) {
  bt.print(humedad);
  bt.print(analogRead(humedad));
}

bool Bluetooth::isConected() {
  return conected;
}

double Bluetooth::leer_4bytes(){
  return (leer()) + (leer() * 256) + (leer() * 256 * 256) + (leer() * 256 * 256 * 256);
}

void Bluetooth::enviar(char* c){
  bt.print(c);
}

void Bluetooth::enviar(int c){
  bt.print(c);
} 
