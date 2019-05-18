#ifndef Bluetooth_h
#define Bluetooth_h
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Constantes.h>
#include <SoftwareSerial.h> 

class Bluetooth{
public:
  Bluetooth(int tx, int rx);
  int leer();
  char* leerString(char* c);
  bool isConected();
  int leerNbytes(int c);
  void enviar(char* c);
  void enviar(int c);
  void enviarInfo(int accion, int pesoBalanza, int pesoRequerido);
  int leerCantidad();
  int leerCantDatos();
  int leerID();

private:
  SoftwareSerial bt;
  bool conected;

};
 

#endif
