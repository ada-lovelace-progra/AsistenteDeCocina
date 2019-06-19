#ifndef EepromAda_h
#define EepromAda_h
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class EEPROMAda{
public:
	void begin();
	void escribirID_DIS(char * nombre);
	char* leerID_DISP();

private:
	char* idDisp=nullptr;
};


#endif	