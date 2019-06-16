#ifndef Bluetooth_h
#define Bluetooth_h
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Constantes.h>

class Bluetooth{
public:
  void begin(int tX, int rX);
  char leerBlock();
  char leer();
  int leerAccion();
  char* leerString(char* c);
  bool isConected();
  long leerNbytes(int c);
  void enviar(String c);
  void enviar(const char* c);
  void enviar(int c);
  void enviarl(long c);
  void enviar(short id, long dato);
  long leerCantidad();
  int leerCantDatos();
  short leerID();

private:
  bool conected;
  bool serial=false;

};
 

#endif
