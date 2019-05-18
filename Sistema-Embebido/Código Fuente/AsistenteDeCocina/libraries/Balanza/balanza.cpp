#include <balanza.h>

using namespace std;

Balanza::Balanza(int data, int sck){
	b.begin(data,sck);
	b.set_scale(fcorreccion);
	b.tare(20);	
}

int Balanza::leerBalanza(){
	int p = b.is_ready() ? b.get_value() : 0;

	return p > 0 ? p : 0;
}

bool Balanza::isPesoAlcanzado(){
	pesoBalanza = leerBalanza();
	if (pesoRequerido == 0)
		pesoRequerido = pesoADepositar - pesoBalanza;

	return pesoRequerido < pesoBalanza;
}

int Balanza::setPesoADepositar(int p){
	return pesoADepositar = leerBalanza() - p;
}

int Balanza::leerPesoBalanza(){
	return pesoBalanza = leerBalanza();
}
/*
int Balanza::leerPesoBalanza(){
	return pesoBalanza=leerBalanza();
}*/