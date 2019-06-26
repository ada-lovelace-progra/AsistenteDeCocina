#ifndef Constantes_h
#define Constantes_h
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

/////// constantes que se repiten en java al igual que los leds
	 // constantes estado
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
#define DEVOLVER_PROD 		11 //B
#define SETEAR_IDDISP       90 //5A
#define ENVIAR_IDDISP       91 //5B
#define VALIDAR_HUMEDAD     92 //5C
#define BT_CONECTADO        93 //5D
#define BT_DESCONECTADO     94 //5E

	// constantes interrupcion
#define GIRAR_SINFIN_HORARIO 	   126
#define GIRAR_SINFIN_ANTIHORARIO   125
#define ENCENDER_LED			   124
#define DETENER_SINFIN			   123

// definicione de TIMEOUTS
#define TIMEOUT_CUMPLIDO			  999
#define TIMEOUT_POR_DEFAULT			90000
#define TIMEOUTLEER_UNICO_PROD  	10000
#define TIMEOUTLEER_MULTI_PROD  	10000
#define TIMEOUTESPERAR_PRODUCTO 	60000
#define TIMEOUTESPERAR_NO_PRODUCTO 	60000

	 // constantes 
#define HUMEDAD 			95
#define TEMPERATURA			96
#define MAX_ARRAY_SIZE	   100
#define UNAVAILABLE		  -100
#define NO_INTERRUPT	  -101
#define TIME_DEVOLVER_PROD 10000 

/////// PIN DEBUG 				
#define debugOut            22
#define debugIn             23

/////// Sensores
#define tem_hum             52
#define presencia           46	
#define btTx				14  
#define btRx				15	
#define balDt	            38  
#define balSck	            39 	
///////	referencia de balanza
//		E+				Rojo 	Marron
//		E-				Negro	Azul
//		A-				Blanco 	Blanco-Azul
//		A+				Verde 	Verde

/////// Actuadores
#define SF1					 2
#define SF2					 3
#define SFP				 	 4
	// Alertas      
#define ledEncendido        13 //Rojo 
#define ledConectadoBT      12 //Azul
#define ledSirviendo        11 //Amarillo
#define ledDisponible       10 //Verde
#define ledCantNoDisponible  9 //Blanco
#define zumbador             8

/////// Definiciones
#define OFF					 0
#define tiempoZumbador     150
#define zumbadorTime       150
#define FRECUENCIA		   329
#define fcorreccion			-1 //se debe medir la balanza con un peso conocido antes de setear el valor
#define BT_IS_SET		  false
#define BTSERIAL	   Serial3
#define BTNAME			"AppSistenteDeCocina"
#define PASSWORD	    "ada"

#endif