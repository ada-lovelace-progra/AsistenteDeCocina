#ifndef Constantes_h
#define Constantes_h
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

/////// constantes que se repiten en java al igual que los leds
	 // constantes accion
enum{
#define INACTIVO            -1
#define LEER_UNICO_PROD		 1
#define LEER_MULTI_PROD		 2
#define ESPERAR_PRODUCTO	 3
#define SENSAR_PESO			 4
#define BAJAR_BRAZO			 5
#define SENSAR_PESO_SINFIN	 6
#define EXTRAER_PRODUCTO	 7
#define SUBIR_BRAZO			 8
#define ESPERAR_NO_PRODUCTO  9
#define CANT_NO_DISP		10 //A
#define SETEAR_IDDISP       90 //5A
#define ENVIAR_IDDISP       91 //5B
#define VALIDAR_HUMEDAD     92 //5C
#define BT_CONECTADO        93 //5D
#define BT_DESCONECTADO     94 //5E
};
	 // constantes 
#define MAX_ARRAY_SIZE	   100
#define UNAVAILABLE		  -100

/////// PIN DEBUG 				
#define debugOut             2
#define debugIn              3

/////// Sensores
#define tem_hum            A13	
#define presencia           25	//falta
#define btPairing           31	//falta
#define btTx				14  
#define btRx				15	
#define balDt	            38  
#define balSck	            39 	

/////// Actuadores
#define MT1					40
#define MV1					41
#define MT2					44
#define MV2					45

/////// Actuadores-Alertas      
#define ledEncendido        13 //rojo 
#define ledConectadoBT      12 //azul
#define ledSirviendo        11 //amarillo
#define ledDisponible       10 //verde
#define ledCantNoDisponible  9 //blanco
#define zumbador             8

/////// Definiciones
#define OFF					 0
#define alimentacionBT      23
#define tiempoZumbador     150
#define zumbadorTime       150
#define FRECUENCIA		   329
#define fcorreccion			 1 //se debe medir la balanza con un peso conocido antes de setear el valor
#define BT_IS_SET		 false
#define BTSERIAL	   Serial3
#define BTNAME			"LaCocinaDeAda"
#define PASSWORD	    "12345"

	
#endif