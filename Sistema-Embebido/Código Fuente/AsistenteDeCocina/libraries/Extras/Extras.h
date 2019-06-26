#ifndef Extras_h
#define Extras_h
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <constantes.h>
#define RICK 1

class Extras{
public:
	void begin(int pinBuzzer);
	void exec();

private:
	int pinBuzzer;
};
 
#endif