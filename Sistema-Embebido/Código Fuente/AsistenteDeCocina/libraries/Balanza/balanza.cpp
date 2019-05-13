#include <balanza.h>

using namespace std;

Balanza::Balanza(int data, int sck){
	b.begin(data,sck);
	b.set_scale();
	b.tare(20);	
}

double Balanza::leerBalanza(){
	double p = b.is_ready() ? b.get_value() : 0;

	return p > 0 ? p : 0;
}

bool Balanza::isPesoAlcanzado(){
	pesoBalanza = leerBalanza();
	if (pesoADepositar == 0)
		leerPesoADepositar();
	if (pesoRequerido == 0)
		pesoRequerido = pesoADepositar - pesoBalanza;

	return pesoRequerido < pesoBalanza;
}

void Balanza::leerPesoADepositar(){
	pesoADepositar=123;
}