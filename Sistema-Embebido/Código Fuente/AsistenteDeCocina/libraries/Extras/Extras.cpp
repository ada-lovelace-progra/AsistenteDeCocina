		#include <Extras.h>



void Extras::begin(int pinBuzzer){
	pinMode(pinBuzzer, OUTPUT);

}

void Extras::exec(int op, int veces){
	while(veces--){
		if(op==RICK){
			int notes = 26;
			int index = -1;
			while(++index < notes){
				tone(pinBuzzer, toneR[index]);
				delay(delayR[index]);
			}
		}
	}
}