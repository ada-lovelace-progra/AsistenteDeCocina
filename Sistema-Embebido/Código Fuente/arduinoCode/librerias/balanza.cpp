#include "balanza.h"

Balanza::Balanza(int data, int sck){
	b.begin(data,sck);
	b.set_scale();
	b.tare(20);	
}

double Balanza::leer(){
	return b.is_ready() ? b.get_value() : 0;
}

