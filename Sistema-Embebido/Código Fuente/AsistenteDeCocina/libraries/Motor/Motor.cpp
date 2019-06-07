#include <Motor.h>

Motor::Motor(){}

Motor::Motor(int pinMT1, int pinMV1, int pinMT2, int pinMV2){
	this->pinMT1 = pinMT1;
	this->pinMV1 = pinMV1;
	this->pinMT2 = pinMT2;
	this->pinMV2 = pinMT2;

	pinMode(this->pinMT1,OUTPUT);
	pinMode(this->pinMV1,OUTPUT);
	pinMode(this->pinMT2,OUTPUT);
	pinMode(this->pinMV2,OUTPUT);
}

float Motor::operator=(float mode){
	if(mode<0)
		horario(mode);
	else if(mode>0)
		antihorario(mode);
	else 
		parar();

	return mode;
}

void Motor::horario(float mode){
	analogWrite(this->pinMT1,mode); 
	analogWrite(this->pinMV1,mode); 
	digitalWrite(this->pinMT2,LOW); 
	digitalWrite(this->pinMV2,LOW); 
}

void Motor::antihorario(float mode){
	digitalWrite(this->pinMT1,LOW); 
	digitalWrite(this->pinMV1,LOW); 
	analogWrite(this->pinMT2,mode); 
	analogWrite(this->pinMV2,mode); 
}

void Motor::parar(){
	digitalWrite(this->pinMT1,LOW); 
	digitalWrite(this->pinMV1,LOW);
	digitalWrite(this->pinMT2,LOW); 
	digitalWrite(this->pinMV2,LOW); 
}