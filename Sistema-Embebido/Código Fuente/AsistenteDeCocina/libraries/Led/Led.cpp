#include "led.h"

Led::Led(){}

Led::Led(int i){
  Serial.println("Construyendo Led");
	pin=i;
	pinMode(pin, OUTPUT);
	digitalWrite(pin, HIGH);
	delay(250);
	digitalWrite(pin, LOW);
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