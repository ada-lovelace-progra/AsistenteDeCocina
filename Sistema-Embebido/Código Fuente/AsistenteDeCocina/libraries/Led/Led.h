#ifndef Led_h
#define Led_h
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class Led{
public:
	Led(int pin);
	int operator=(int mode);
	float operator=(float mode);
	double operator=(double mode);
private:
	int pin;
};

#endif