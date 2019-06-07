#include <Bluetooth.h>
#include <Constantes.h>

Bluetooth::Bluetooth(){}

Bluetooth::Bluetooth(int tX, int rX){
  Serial.println("Construyendo Bluetooth");
  BTSERIAL.begin(9600);
    if(!BT_IS_SET){
    this->enviar("AT");
    delay(1000);
    this->enviar("AT+NAME");
    this->enviar(BTNAME); // porque es todo de ada?
    //porque la flaca fue la primer persona en programar
    delay(1000);
    this->enviar("AT+PIN");
    this->enviar(PASSWORD);
  }
  conected = false;
}

char Bluetooth::leerBlock(){
  char i = this->leer();
  while(i==UNAVAILABLE)
    i=this->leer();
  return i;
}

char Bluetooth::leer() {
  if (!BTSERIAL.available())
    return UNAVAILABLE;

  char r = BTSERIAL.read();
  Serial.print("BT Recibe: as char: ");
  Serial.print(r);
  Serial.print("\tas int: ");
  Serial.println((int)r);
  if (conected) {
    if (r == BT_DESCONECTADO) {
      conected = false;
    }
  }
  else {
    if (r == BT_CONECTADO) {
      conected = true;\
    }
  }
  return r;
}

char* Bluetooth::leerString(char* c){
  int i=-1;
  char t=(char)this->leer();

  while(t){
    c[++i]=t;
    t=(char)this->leer();
  }
  return c;
}

void Bluetooth::enviarInfo(int accion, int pesoBalanza, int pesoRequerido) {
  this->enviar(1);
  this->enviar(accion);

  if (accion == EXTRAER_PRODUCTO) {
    this->enviar(ledSirviendo);
    this->enviar((millis() % 500 > 250));
  }

  this->enviar(ledDisponible);
  this->enviar(accion == INACTIVO);

  this->enviar(ledCantNoDisponible);
  this->enviar(pesoBalanza > pesoRequerido);
}

bool Bluetooth::isConected() {
  return conected?true:this->leer()>-1;
}

int Bluetooth::leerNbytes(int c){
  c--;
  if(!c)
    return this->leerBlock();
  return this->leerBlock() * pow(256,c) + this->leerNbytes(c); 
}

void Bluetooth::enviar(String c){
  BTSERIAL.println(c);
}

void Bluetooth::enviar(char* c){
  BTSERIAL.print(c);
}

void Bluetooth::enviar(int c){
  BTSERIAL.print(c);
} 

void Bluetooth::enviar(int id, int dato){
  this->enviar(id);
  this->enviar(dato);
} 

int Bluetooth::leerID(){
  return this->leerNbytes(4);
}

int Bluetooth::leerCantidad(){
  return this->leerNbytes(4);
}

int Bluetooth::leerCantDatos(){
  return this->leerNbytes(4);
}