#ifndef Balanza_h
#define Balanza_h

#include "../HX711/HX711.h" 

class Balanza{
public:
  Balanza(int data, int sck);
  double leer();
  bool isPesoAlcanzado();

private:
  int pin;
  HX711 b;


};
 
#endif
