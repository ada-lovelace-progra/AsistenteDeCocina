#ifndef Bluethoot_h
#define Bluethoot_h
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "../Constantes/Constantes.h"
#include <SoftwareSerial.h> 

class Bluethoot{
public:
  Bluethoot(int tx, int rx);
  int leer();
  char* leerString(char* c);
  bool isConected();
  double leer_4bytes();
  void enviar(char* c);
  void enviar(int c);
  void enviarInfo(int accion);
  void enviarHumedad(double humedadLevel);

private:
  SoftwareSerial bt;
  bool conected;
};
 

#endif
