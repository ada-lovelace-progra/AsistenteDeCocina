#ifndef Bluetooth_h
#define Bluetooth_h
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Constantes.h>

class Bluetooth{
public:
  void begin(int tX, int rX);
  char leerBlock();
  char leer();
  char leerEstado();
  char* leerString(char* c);
  bool isConected();
  long leerNbytes(int c);
  void enviar(String c);
  void enviar(const char* c);
  void enviar(int c);
  void enviarAccion(int accion);
  void enviarError(int errorCode);
  void enviarNotif(int notifCode);
  void enviar(short id, long dato);
  unsigned long leerCantidad();
  unsigned long leerCantDatos();
  long leerID();

private:
  bool conected;
  bool serial = false;
  String errorMessage[3] = {(String)"Cantidad no disponile de producto",
                            (String)"Se espero por demasiado tiempo y se retorno a inactivo",
                            (String)"No se detecto un recipiente donde depositar el producto"};

  String notifMessage[2] = {(String)"Mucha humedad, mayor a " + MAX_HUM + "%", 
                            (String)"Mucha temperatura, mayor a " + MAX_TEMP + "grados"};

};
 

#endif
