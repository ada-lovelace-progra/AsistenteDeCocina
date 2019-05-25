#include <HumedadTemperatura.h>

HumedadTemperatura::HumedadTemperatura();

HumedadTemperatura::HumedadTemperatura(int pin) : s(DHT(pin, DHT11)){
  s.begin();
}

int HumedadTemperatura::leerHumedad(){
	return s.readHumidity();
}

int HumedadTemperatura::leerTemperatura(){
	return s.readTemperature();
}
