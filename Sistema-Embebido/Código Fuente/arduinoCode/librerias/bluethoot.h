#ifndef Bluethoot_h
#define Bluethoot_h

#include <SoftwareSerial.h> 

class Bluethoot{
public:
	Bluethoot(int tx, int rx);
	int leer();

private:
	SoftwareSerial bt;
}
 
#endif