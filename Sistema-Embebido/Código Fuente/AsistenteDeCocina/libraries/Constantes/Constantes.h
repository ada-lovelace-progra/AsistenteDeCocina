#ifndef Constantes_h
#define Constantes_h
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

/////// constantes que se repiten en java al igual que los leds
	 // constantes accion
#define INACTIVO             0
#define LEER_UNICO_PROD		 1
#define LEER_MULTI_PROD		 2
#define ESPERAR_PRODUCTO	 3
#define SENSAR_PESO			 4
#define BAJAR_BRAZO			 5
#define SENSAR_PESO_SINFIN	 6
#define EXTRAER_PRODUCTO	 7
#define SUBIR_BRAZO			 8
#define ESPERAR_NO_PRODUCTO  9
#define CANT_NO_DISP		10
#define SETEAR_NOMBRE       90
#define ENVIAR_NOMBRE       91
#define VALIDAR_HUMEDAD     92
#define BT_CONECTADO        93
#define BT_DESCONECTADO     94
	 // constantes 
#define MAX_ARRAY_SIZE	   100

/////// PIN DEBUG 				
#define debugOut             2
#define debugIn              3

/////// Sensores
#define tem_hum             22	
#define presencia           25	//falta
#define btPairing           31	//falta
#define btTx				14  
#define btRx				15	
#define balDt	            38  
#define balSck	            39 	

/////// Actuadores
#define sinFin              44	//falta

/////// Actuadores-Alertas      
#define ledEncendido        13 
#define ledConectadoBT      12
#define ledSirviendo        11
#define ledDisponible       10
#define ledCantNoDisponible  9
#define zumbador             8

/////// Definiciones
#define alimentacionBT      23
#define tiempoZumbador     150
#define zumbadorTime       150
#define FRECUENCIA		  1000
#define fcorreccion			 1 //se debe medir la balanza con un peso conocido antes de setear el valor
	
#endif