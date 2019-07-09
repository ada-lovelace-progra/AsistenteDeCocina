#include "led.h"

void Led::begin(int i){
  Serial.println("Construyendo Led");
	pin=i;
	pinMode(pin, OUTPUT);
	digitalWrite(pin, HIGH);
	digitalWrite(pin, LOW);
}

int Led::operator=(int i){
	digitalWrite(pin, i);
	return i;
}

float Led::operator=(float i){
	analogWrite(pin, i);
	return i;
}

double Led::operator=(double i){
	analogWrite(pin, i);
	return i;
}