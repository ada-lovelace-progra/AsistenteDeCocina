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
	EEPROMAda(Bluetooth b);
	void escribirProducto(char * nombre);
	char* leerProducto();

private:
	Bluetooth bt;
};


#endif	