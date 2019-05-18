#ifndef Balanza_h
#define Balanza_h
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <HX711.h> 
#include <constantes.h>

class Balanza{
public:
  Balanza(int data, int sck);
  int leerBalanza();
  int leerPesoBalanza();
  int setPesoADepositar(int c);
  bool isPesoAlcanzado();
  void leerPesoADepositar();
  int pesoRequerido;
  int pesoADepositar;
  int pesoBalanza;

private:
  int pin;
  HX711 b;
};
 
#endif
