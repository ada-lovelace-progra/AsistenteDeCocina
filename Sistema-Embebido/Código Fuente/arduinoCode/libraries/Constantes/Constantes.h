#ifndef Constantes_h
#define Constantes_h
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif



/////// constantes que se repiten en java al igual que los leds
#define SIN_ACCION           0
#define SACAR_CONTENIDO      1
#define MOVER_BRAZO          2
#define BAJAR_SINFIN         3
#define RETORNAR_A_REPOSO    4
#define SETEAR_NOMBRE        5
#define ENVIAR_NOMBRE        6
#define VALIDAR_HUMEDAD      7
#define BT_CONECTADO         8
#define BT_DESCONECTADO      9

/////// PIN DEBUG
#define debugIn             54
#define debugOut            55

/////// Sensores
#define humedad             68
#define temperatura         69
#define presencia           48
#define btPairing           49
#define btTx				50
#define btRx				51
#define balDt	            52 
#define balSck	            53 

/////// Actuadores
#define sinFin              44
#define zumbador            13
#define ledEncendido        12
#define ledConectadoBT      11
#define ledSirviendo        10
#define ledDisponible        9
#define ledCantNoDisponible  8

#define alimentacionBT      23
#define tiempoZumbador     150

#endif