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
	void begin(int data, int sck);
	double leerBalanza();
	double leerPesoBalanza();
	double setPesoADepositar(double c);
	bool isPesoAlcanzado();
	void leerPesoADepositar();
	double pesoRequerido;
	double pesoADepositar;
	double pesoBalanza;

private:
	int pin;
	HX711 b;
};
 
#endif
