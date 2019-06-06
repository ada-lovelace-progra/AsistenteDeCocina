#include <HumedadTemperatura.h>

HumedadTemperatura::HumedadTemperatura() : dht(DHT(tem_hum, DHT11)){}

HumedadTemperatura::HumedadTemperatura(int pin) : dht(DHT(pin, DHT11)){
	Serial.println("Construyendo HumedadTemperatura");
  	dht.begin();
}

float HumedadTemperatura::leerHumedad(){
	this->actualizarDatos();
	return this->hum;
}

float HumedadTemperatura::leerTemperatura(){
	this->actualizarDatos();
	return this->temp;
}

void HumedadTemperatura::actualizarDatos(){
	if(millis() - this->lastRead < 2000)
		return;

	lastRead = millis();
	this->temp = dht.readTemperature();
	this->hum =  dht.readHumidity();
}