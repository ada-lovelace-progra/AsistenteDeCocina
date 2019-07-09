#ifndef Constantes_h
#define Constantes_h
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

/////// constantes que se repiten en java al igual que los leds
	 // constantes estado
#define INACTIVO            	-1
#define LEER_UNICO_PROD		 		1
#define LEER_MULTI_PROD		 		2
#define ESPERAR_PRODUCTO	 		3
#define SENSAR_PESO			 			4
#define BAJAR_BRAZO			 			5
#define SENSAR_PESO_SINFIN		6
#define EXTRAER_PRODUCTO	 		7
#define SUBIR_BRAZO			 			8
#define ESPERAR_NO_PRODUCTO  	9
#define CANT_NO_DISP					10 //A
#define DEVOLVER_PROD 				11 //B
#define SETEAR_IDDISP       	90 //5A
#define ENVIAR_IDDISP       	91 //5B
#define VALIDAR_HUMEDAD     	92 //5C
#define BT_CONECTADO        	93 //5D
#define BT_DESCONECTADO     	94 //5E

	// constantes interrupcion
#define GIRAR_SINFIN_HORARIO 	   		126
#define GIRAR_SINFIN_ANTIHORARIO   	125
#define ENCENDER_LED			   				124
#define DETENER_SINFIN			   			123

	// constantes error
#define NO_ERROR						-1
#define ERROR_CANT					0
#define ERROR_TIME					1
#define ERROR_NO_TACHO			2

	// constantes error
#define MAX_TEMP				40
#define MAX_HUM					60

#define NO_NOTIF				-1
#define NOTIF_CANT 			 0
#define NOTIF_TIME			 1

	// definicione de TIMEOUTS
#define TIMEOUT_CUMPLIDO			  		999
#define TIMEOUT_POR_DEFAULT					90000
#define TIMEOUTLEER_UNICO_PROD  		10000
#define TIMEOUTLEER_MULTI_PROD  		10000
#define TIMEOUTESPERAR_PRODUCTO 		60000
#define TIMEOUTESPERAR_NO_PRODUCTO 	60000
	
	// constantes envio data
#define ACTION_ERROR		100
#define ACTION_ESTADO		101
#define ACTION_NOTIF		102

	 // constantes 
#define HUMEDAD 						95
#define TEMPERATURA					96
#define MAX_ARRAY_SIZE	   	100
#define UNAVAILABLE		  		-100
#define NO_INTERRUPT	  		-101
#define TIME_DEVOLVER_PROD 	10000 

/////// PIN DEBUG 				
#define DEBUG_OUT						24
#define DEBUG_IN							25

/////// Sensores
#define TEM_HUM         52 
#define PRESENCIA       46	
#define BT_TX						14  
#define BT_RX						15	
#define BAL_DT	        A0  
#define BAL_SCK	        A1 	
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
#define LED_ENCENDIDO        	13 //Rojo 
#define LED_CONECTADO_BT      12 //Azul
#define LED_SIRVIENDO        	11 //Amarillo
#define LED_DISPONIBLE       	10 //Verde
#define LED_CANT_NO_DISP	  	9 //Blanco
#define ZUMBADOR             	8

/////// Definiciones
#define OFF					 				0
#define TIEMPO_ZUMBADOR    	150
#define ZUMBADOR_TIME      	150
#define FRECUENCIA		   		329
#define PASSWORD	    			"1234"
#define TAM_BYTE						8
#define DEFAULT_RATE				9600
#define TONE_DURACION				200
#define CICLOS_INTERRUPCION 1000
#define CICLOS_ALERTAS			10000
#define LIM_INTERRUPCION		30
#define TIEMPO_LED_BT				450
#define LIMITE_LED_BT				200
#define TIEMPO_LED_ON				350
#define TIEMPO_LED_DISP			250
#define DIV_ZUMBADOR				4
#define MULT_ZUMBADOR				0.7

// Balanza
#define BALANZA_FCORRECCION	 	 	-1 //se debe medir la balanza con un peso conocido antes de setear el valor
#define BALANZA_UNIDAD	 	 			2
#define BALANZA_PESOPRODUCTO		1000
#define BALANZA_FDIVISION	 	 		100

// Bluetooth
#define BT_RATE										9600
#define BT_SERIAL3_PIN_RX					15
#define BT_SERIAL3_PIN_TX					14
#define BT_IS_SET		  						true
#define BT_BYTES_ID		  					true
#define BT_BYTES_CANT		  				true
#define BT_BYTES_CANTDATOS				true
#define BTSERIAL	   							Serial3
#define BTNAME										"AppSistenteDeCocina"

// EEPROM
#define EEPROM_SIZE_MALLOC				99

// DHT11
#define DHT_TIEMPO_ACTUALIZACION	2000
#define DHT_DEFAULT_LASTREAD			-9999

// MOTOR
#define MOTOR_VELOCIDAD_MOD				0.05
#define MOTOR_LIMITE_VEL_TOP			1
#define MOTOR_LIMITE_VEL_BOT			-1
#define MOTOR_MULT_VELOCIDAD			254

#endif