#ifndef EepromAda_h
#define EepromAda_h
#include <Bluetooth.h>

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class EEPROMAda{
public:
	EEPROMAda();
	EEPROMAda(int a);
	void escribirID_DIS(char * nombre);
	char* leerID_DISP();

private:
	char* idDisp=nullptr;
};


#endif	