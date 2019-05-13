#ifndef Balanza_h
#define Balanza_h
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <HX711.h> 

class Balanza{
public:
  Balanza(int data, int sck);
  double leerBalanza();
  bool isPesoAlcanzado();
  void leerPesoADepositar();

private:
  int pin;
  HX711 b;

  int pesoRequerido;
  int pesoADepositar;
  int pesoBalanza;
};
 
#endif
