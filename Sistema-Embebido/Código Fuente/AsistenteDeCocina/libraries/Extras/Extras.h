#ifndef Extras_h
#define Extras_h
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <constantes.h>
#define RICK 1

class Extras{
public:
	void begin(int pinBuzzer);
	void exec(int op);

private:
	int pinBuzzer;

	int toneR[] = {D4, E4, F4, E4, A4, A4, G4, D4, E4, F4, E4, G4, G4, F4, D4, E4, F4, E4, F4, G4, E4, D4, C4, C4, G4, F4};
	int delayR[]= {S , S , S , S , A , A , D , S , S , S , S , A , A , D , S , S , S , S , Q , E , A , S , Q , E , Q , H };
};
 
#endif

#ifndef definesExtras

#define C0 16.35 // C 0
#define Db0 17.32 // D-flat 0
#define D0  18.35 // D 0
#define Eb0 19.45 // E-flat 0
#define E0  20.60 // E 0
#define F0  21.83 // F 0
#define Gb0 23.12 // G-flat 0
#define G0  24.50 // G 0
#define Ab0 25.96 // A-flat 0
#define A0 27.50 // A 0
#define Bb0 29.14 // B-flat 0
#define B0  30.87 // B 0
#define C1  32.70 // C 1
#define Db1 34.65 // D-flat 1
#define D1  36.71 // D 1
#define Eb1 38.89 // E-flat 1
#define E1  41.20 // E 1
#define F1  43.65 // F 1
#define Gb1 46.25 // G-flat 1
#define G1  49.00 // G 1
#define Ab1 51.91 // A-flat 1
#define A1 55.00 // A 1
#define Bb1 58.27 // B-flat 1
#define B1  61.74 // B 1
#define C2  65.41 // C 2
#define Db2 69.30 // D-flat 2
#define D2  73.42 // D 2
#define Eb2 77.78 // E-flat 2
#define E2  82.41 // E 2
#define F2  87.31 // F 2
#define Gb2 92.50 // G-flat 2
#define G2  98.00 // G 2
#define Ab2 103.83 // A-flat 2
#define A2 110.00 // A 2
#define Bb2 116.54 // B-flat 2
#define B2  123.47 // B 2
#define C3  130.81 // C 3
#define Db3 138.59 // D-flat 3
#define D3  146.83 // D 3
#define Eb3 155.56 // E-flat 3
#define E3  164.81 // E 3
#define F3  174.61 // F 3
#define Gb3 185.00 // G-flat 3
#define G3  196.00 // G 3
#define Ab3 207.65 // A-flat 3
#define A3 220.00 // A 3
#define Bb3 233.08 // B-flat 3
#define B3  246.94 // B 3
#define C4  261.63
#define Db4 277.18
#define D4  293.66
#define Eb4 311.13
#define E4  329.63
#define F4  349.23
#define Gb4 369.99
#define G4  392.00
#define Ab4 415.30
#define A4 440.00
#define Bb4 466.16
#define B4  493.88
#define C5  523.25
#define Db5 554.37
#define D5  587.33
#define Eb5 622.25
#define E5  659.26
#define F5  698.46
#define Gb5 739.99
#define G5  783.99
#define Ab5 830.61
#define A5 880.00
#define Bb5 932.33
#define B5  987.77
#define C6  1046.50
#define Db6 1108.73
#define D6  1174.66
#define Eb6 1244.51
#define E6  1318.51
#define F6  1396.91
#define Gb6 1479.98
#define G6  1567.98
#define Ab6 1661.22
#define A6 1760.00
#define Bb6 1864.66
#define B6  1975.53
#define C7  2093.00
#define Db7 2217.46
#define D7  2349.32
#define Eb7 2489.02
#define E7  2637.02
#define F7  2793.83
#define Gb7 2959.96
#define G7  3135.96
#define Ab7 3322.44
#define A7 3520.01
#define Bb7 3729.31
#define B7  3951.07
#define C8  4186.01
#define Db8 4434.92
#define D8  4698.64
#define Eb8 4978.03

// Change this to alter the BPM of he song
#define BPM 120

// Rests

#define H 2*Q //half 2/4
#define Q 60000/BPM //quarter 1/4 
#define E Q/2   //eighth 1/8
#define S Q/4 // sixteenth 1/16
#define W 4*Q // whole 4/4
#define A Q/1.5
#define D 1.5*Q


#endif