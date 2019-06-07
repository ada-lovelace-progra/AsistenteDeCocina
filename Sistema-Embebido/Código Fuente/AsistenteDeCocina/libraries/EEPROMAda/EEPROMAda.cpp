#include <EEPROMAda.h>
#include <bluetooth.h>
#include <EEPROM.h> 

EEPROMAda::EEPROMAda(){}

EEPROMAda::EEPROMAda(int a){
  Serial.print("Construyendo EEPROMAda");
    Serial.println();
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

  char nombre[999];
  int index = 0;

  char c = 0;
  do {
    c = EEPROM.read(index);
    nombre[index++] = c;
  } while (c);
  return nombre;
}