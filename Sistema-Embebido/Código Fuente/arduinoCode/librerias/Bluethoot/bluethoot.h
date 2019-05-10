#ifndef Bluethoot_h
#define Bluethoot_h
#include "../Constantes/Constantes.h"
#include <SoftwareSerial.h> 

class Bluethoot{
public:
  Bluethoot(int tx, int rx);
  int leer();
  char* leerString();
  bool isConected();
  double leer_4bytes();
  void enviar(char* c);
  void enviar(int c);
  void enviarInfo(int accion);
  void enviarHumedad(double humedadLevel);

private:
  SoftwareSerial bt;
  bool conected;
};
 
#endif
