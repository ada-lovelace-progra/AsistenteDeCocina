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
	Motor();
	Motor(int pinMT1, int pinMV1, int pinMT2, int pinMV2);
	float operator=(float mode);
	void Motor::horario(float mode);
	void Motor::antihorario(float mode);
	void Motor::parar();

private:
	int pinMT1;
	int pinMV1;
	int pinMT2;
	int pinMV2;
};
 
#endif
