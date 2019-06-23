#include <Motor.h>

void Motor::begin(int pinSF1, int pinSF2, int pinSFP){
	this->pinSF1 = pinSF1;
	this->pinSF2 = pinSF2;
	this->pinSFP = pinSFP;

	pinMode(this->pinSF1,OUTPUT);
	pinMode(this->pinSF2,OUTPUT);
	pinMode(this->pinSFP,OUTPUT);

	velocidad = 0;
}

float Motor::operator++(int){
	velocidad+=(float)0.05;
	return setVelocidad(velocidad);
}

float Motor::operator--(int){
	velocidad-=(float)0.05;
	return setVelocidad(velocidad);
}

float Motor::operator=(float mode){
	return setVelocidad(mode);
}

float Motor::setVelocidad(float mode){
	this->velocidad=mode>1?1:mode;
	if(mode<0)
		horario(mode);
	else if(mode>0)
		antihorario(mode);
	else 
		parar();

	return mode;
}

void Motor::horario(float mode){
	digitalWrite(this->pinSF1,HIGH); 
	digitalWrite(this->pinSF2,LOW); 
	analogWrite(this->pinSFP,mode*254); 
}

void Motor::antihorario(float mode){
	digitalWrite(this->pinSF1,LOW);
	digitalWrite(this->pinSF2,HIGH); 
	analogWrite(this->pinSFP,mode*-254); 
}

void Motor::parar(){
	digitalWrite(this->pinSF1,LOW); 
	digitalWrite(this->pinSF2,LOW);
	digitalWrite(this->pinSFP,LOW); 
}