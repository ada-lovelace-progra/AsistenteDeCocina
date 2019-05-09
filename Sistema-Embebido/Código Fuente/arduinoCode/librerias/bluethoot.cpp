#include "bluethoot.h"

Bluethoot::Bluethoot(int tx, int rx){
  bt.begin(9600);
  bt.print("AT");
  delay(1000);
  bt.print("AT+NAME");
  bt.print("LaJarraDeAda"); // porque es todo de ada?
  //porque la flaca fue la primer persona en programar
  delay(1000);
  bt.print("AT+PIN");
  bt.print("pass");
  delay(1000);
  bt.print("AT+BPS");
  bt.print("4");

}

int Bluethoot::leer(){
	bt.read();
}

