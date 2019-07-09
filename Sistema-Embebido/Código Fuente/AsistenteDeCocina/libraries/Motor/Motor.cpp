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
	velocidad += (float)MOTOR_VELOCIDAD_MOD;
	return setVelocidad(velocidad);
}

float Motor::operator--(int){
	velocidad -= (float)MOTOR_VELOCIDAD_MOD;
	return setVelocidad(velocidad);
}

float Motor::operator=(float mode){
	return setVelocidad(mode);
}

float Motor::setVelocidad(float mode) {
	this->velocidad = mode > MOTOR_LIMITE_VEL_TOP ? MOTOR_LIMITE_VEL_TOP : mode;
	this->velocidad = mode < MOTOR_LIMITE_VEL_BOT ? MOTOR_LIMITE_VEL_BOT : mode;

	if(mode > MOTOR_VELOCIDAD_MOD)
		horario(mode);
	else if(mode < -MOTOR_VELOCIDAD_MOD)
		antihorario(mode);
	else 
		parar();

	return mode;
}

void Motor::horario(float mode){
	digitalWrite(this->pinSF1,HIGH); 
	digitalWrite(this->pinSF2,LOW); 
	analogWrite(this->pinSFP, mode * MOTOR_MULT_VELOCIDAD); 
}

void Motor::antihorario(float mode){
	digitalWrite(this->pinSF1,LOW);
	digitalWrite(this->pinSF2,HIGH); 
	analogWrite(this->pinSFP, mode * (-MOTOR_MULT_VELOCIDAD)); 
}

void Motor::parar(){
	digitalWrite(this->pinSF1,LOW); 
	digitalWrite(this->pinSF2,LOW);
	digitalWrite(this->pinSFP,LOW); 
}