#include <balanza.h>

void Balanza::begin(int data, int sck) {
  Serial.println("Construyendo Balanza");
	b.begin(data, sck);
	b.set_scale(BALANZA_FCORRECCION);
	b.tare(20);	
}

double Balanza::leerBalanza() {
	double r =  b.get_units(BALANZA_UNIDAD) / BALANZA_FDIVISION;
	return r;
}

bool Balanza::isPesoAlcanzado() {
	pesoBalanza = leerBalanza();
	return pesoRequerido > pesoBalanza;
}

double Balanza::setPesoADepositar(double p) {
	return pesoRequerido = leerBalanza() - (pesoADepositar = p);
}

double Balanza::leerPesoBalanza() {
	return pesoBalanza = leerBalanza();
}

bool Balanza::isProducto() {
	return b.get_units(BALANZA_UNIDAD) > BALANZA_PESOPRODUCTO;
}
