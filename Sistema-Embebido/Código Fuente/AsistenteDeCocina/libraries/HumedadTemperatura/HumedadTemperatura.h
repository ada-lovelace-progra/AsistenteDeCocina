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
	HumedadTemperatura();
  HumedadTemperatura(int pin);
  float leerHumedad();
  float leerTemperatura();
  void actualizarDatos();
private:
  DHT dht;
  float temp;
  float hum;
  int lastRead=-9999;
};
 
#endif
