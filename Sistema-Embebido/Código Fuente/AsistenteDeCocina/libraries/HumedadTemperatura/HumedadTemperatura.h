#ifndef HumedadTemperatura_h
#define HumedadTemperatura_h
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <DHT.h> 
#include <constantes.h>

class HumedadTemperatura{
public:
  HumedadTemperatura(int pin);
  int leerHumedad();
  int leerTemperatura();
private:
  int pin;
  DHT s;
};
 
#endif
