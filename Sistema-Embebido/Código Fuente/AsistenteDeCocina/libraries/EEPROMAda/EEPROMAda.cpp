#include <EEPROMAda.h>
#include <EEPROM.h>
void EEPROMAda::begin(){
  Serial.println("Construyendo EEPROMAda");
}

void EEPROMAda::escribirID_DIS(char * nombre) {
  int index = -1;
  idDisp=nombre;
  while (idDisp[++index]) {
    EEPROM.write(index, nombre[index]);
  }
}

char* EEPROMAda::leerID_DISP() {
  if(idDisp)
    return idDisp;

  char* nombre = (char *) malloc(EEPROM_SIZE_MALLOC);
  int index = 0;

  char c = 0;
  do {
    c = EEPROM.read(index);
    nombre[index++] = c;
  } while (c);
  return nombre;
}