#include "../Bluethoot/Bluethoot.h"
#include <EEPROM.h> 

void EEPROMAda::escribirProducto(char * nombre, Bluethoot bt) {
  int index = -1;
  while (bt.leer()) {
    index++;
    EEPROM.write(index, nombre[index]);
  }
}

char* EEPROMAda::leerProducto(Bluethoot bt) {
  char nombre[999];
  int index = 0;

  char c = 0;
  do {
    c = EEPROM.read(index);
    nombre[index++] = c;
  } while (c);
  return nombre;
}