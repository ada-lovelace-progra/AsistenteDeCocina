#ifndef Motor_h
#define Motor_h
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <constantes.h>

class Motor{
public:
	void begin(int sf1, int sf2, int sfP);
	float setVelocidad(float velocidad);
	float operator=(float mode);
	float operator--(int);
	float operator++(int);

private:
	void horario(float mode);
	void antihorario(float mode);
	void parar();

	float velocidad;
	int pinSF1;
	int pinSF2;
	int pinSFP;
};
 
#endif
