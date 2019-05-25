#include "led.h"

Led::Led(int i){
	pin=i;
	pinMode(pin, OUTPUT);
}

int Led::operator=(int i){
	digitalWrite(pin, i);
}

float Led::operator=(float i){
	analogWrite(pin, i);
}

double Led::operator=(double i){
	analogWrite(pin, i);
}