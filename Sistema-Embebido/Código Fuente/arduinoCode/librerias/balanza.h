#ifndef Balanza_h
#define Balanza_h

#include <H711.h> 

class Balanza{
public:
	Balanza(int data, int sck);
	double leer();

private:
	int pin;
	H711 b;
}
 
#endif