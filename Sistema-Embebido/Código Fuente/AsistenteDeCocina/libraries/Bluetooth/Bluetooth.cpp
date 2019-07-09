#include <Bluetooth.h>

void Bluetooth::begin(int tX, int rX){
  Serial.println("Construyendo Bluetooth");
  BTSERIAL.begin(BT_RATE);
  if(tX != BT_SERIAL3_PIN_TX || rX != BT_SERIAL3_PIN_RX)
    Serial.print("LOS PINS ENVIADOS NO PERTENECEN A Serial3");
  
  if(!BT_IS_SET) {
    this->enviar("AT");
    this->enviar("AT+NAME");
    this->enviar(BTNAME); // porque es todo de ada?
    //porque la flaca fue la primer persona en programar
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
      enviarAccion(BT_DESCONECTADO);
    }
  }
  else {
    if (r == BT_CONECTADO) {
      conected = true;
      enviarAccion(BT_CONECTADO);
    }
  }
  return r;
}

char* Bluetooth::leerString(char* c){
  int i=-1;
  char t=this->leer();

  while(t){
    c[++i]=t;
    t=this->leer();
  }
  return c;
}

bool Bluetooth::isConected() {
  return conected?true:this->leer()>=-1;
}

long Bluetooth::leerNbytes(int c){
  c--;
  char l = this->leerBlock();
  if(!c)
    return (short)(l);

  return (l << (TAM_BYTE*c)) + this->leerNbytes(c); 
}

void Bluetooth::enviar(String c){
  BTSERIAL.print(c);
}

void Bluetooth::enviar(const char* c){
  BTSERIAL.print(c);
}

void Bluetooth::enviar(int c){
  BTSERIAL.print(c);
} 

void Bluetooth::enviar(short id, long dato){
  this->enviar(id);
  this->enviar(dato);
  if(id == TIMEOUT_CUMPLIDO)
    enviarError(id);
} 

long Bluetooth::leerID(){
  return this->leerNbytes(BT_BYTES_ID);
}

unsigned long Bluetooth::leerCantidad(){
  return this->leerNbytes(BT_BYTES_CANT);
}

unsigned long Bluetooth::leerCantDatos(){
  return this->leerNbytes(BT_BYTES_CANTDATOS);
}

char Bluetooth::leerEstado(){
    return leer();
}

void Bluetooth::enviarAccion(int accion){
  enviar(ACTION_ESTADO+":"+accion);
}

void Bluetooth::enviarError(int errorCode){
  enviar(ACTION_ERROR+":"+errorMessage[errorCode]);
}

void Bluetooth::enviarNotif(int notifCode){
  enviar(ACTION_NOTIF+":"+notifMessage[notifCode]);
}