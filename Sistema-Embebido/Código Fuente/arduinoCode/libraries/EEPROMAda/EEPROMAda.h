#ifndef EepromAda_h
#define EepromAda_h
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


class EEPROMAda{
public:
	static void escribirProducto(char * nombre);
	static char* leerProducto();


};


#endif