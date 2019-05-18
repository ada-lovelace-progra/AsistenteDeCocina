#include <EEPROMAda.h>
#include <bluetooth.h>
#include <EEPROM.h> 

EEPROMAda::EEPROMAda(Bluetooth b):bt(b){
}

void EEPROMAda::escribirProducto(char * nombre) {
  int index = -1;
  while (bt.leer()) {
    index++;
    EEPROM.write(index, nombre[index]);
  }
}

char* EEPROMAda::leerProducto() {
  char nombre[999];
  int index = 0;

  char c = 0;
  do {
    c = EEPROM.read(index);
    nombre[index++] = c;
  } while (c);
  return nombre;
}