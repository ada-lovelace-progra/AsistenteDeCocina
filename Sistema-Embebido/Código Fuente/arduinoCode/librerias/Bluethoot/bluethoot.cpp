#include "bluethoot.h"
#include "librerias\constantes.h"

Bluethoot::Bluethoot(int tx, int rx) {
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

int Bluethoot::leer() {
  if (!bt.isAvailable())
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

char* Bluethoot::leerString(){
  int i=-1;
  char c[999];
  char t=bt.read();

  while(t){
    c[++i]=t;
    t=bt.read();
  }
  return c;
}

void Bluethoot::enviarInfo(int accion) {
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

void Bluethoot::enviarHumedad(double humedadLevel) {
  bt.print(humedad);
  bt.print(analogRead(humedad));
}

bool Bluethoot::isConected() {
  return conected;
}

double Balanza::leer_4bytes(){
  return  leer() * 256
          + leer() * 256 * 256
          + leer() * 256 * 256 * 256
          + leer() * 256 * 256 * 256 * 256;
}

void Bluethoot::enviar(char* c){
  bt.print(c);
}
void Bluethoot::enviar(int c){
  bt.print(c);
}