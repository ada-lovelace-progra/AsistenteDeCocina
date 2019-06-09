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
  Bluetooth();
  Bluetooth(int tX, int rX);
  char leerBlock();
  char leer();
  int leerAccion();
  char* leerString(char* c);
  bool isConected();
  int leerNbytes(int c);
  void enviar(String c);
  void enviar(char* c);
  void enviar(int c);
  void enviar(int id, int dato);
  void enviarInfo(int accion, int pesoBalanza, int pesoRequerido);
  int leerCantidad();
  int leerCantDatos();
  int leerID();

private:
  bool conected;
  bool serial=false;

};
 

#endif
