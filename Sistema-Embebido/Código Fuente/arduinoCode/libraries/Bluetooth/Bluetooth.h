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
  double leer_4bytes();
  void enviar(char* c);
  void enviar(int c);
  void enviarInfo(int accion, int pesoBalanza, int pesoRequerido);
  void enviarHumedad(double humedadLevel);

private:
  SoftwareSerial bt;
  bool conected;

};
 

#endif
