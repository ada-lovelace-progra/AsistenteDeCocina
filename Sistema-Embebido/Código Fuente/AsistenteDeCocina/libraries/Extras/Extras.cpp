#include <Extras.h>
/*  Rick Roll Code
    AUTHOR: Samantha Lagestee
    Copyright 2017 samilagestee at gmail dot com

    This program is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version.

    DISCLAIMER: The song "Never Gonna Give You Up" by Rick Astley
    is not the creative property of the author. This code simply
    plays a pinBuzzer buzzer rendition of the song.
*/

#define  A3F    208     // 208 Hz
#define  B3F    233     // 233 Hz
#define  B3     247     // 247 Hz
#define  C4     261     // 261 Hz MIDDLE C
#define  C4S    277     // 277 Hz
#define  E4F    311     // 311 Hz    
#define  F4     349     // 349 Hz 
#define  A4F    415     // 415 Hz  
#define  B4F    466     // 466 Hz 
#define  B4     493     // 493 Hz 
#define  C5     523     // 523 Hz 
#define  C5S    554     // 554 Hz
#define  E5F    622     // 622 Hz  
#define  F5     698     // 698 Hz 
#define  F5S    740     // 740 Hz
#define  A5F    831     // 831 Hz 

#define REST    -1

#define BEAT_LENGTH       100
#define BEAT_SEPARATION   0.3
#define BEAT_MULT         2
#define INIT_PART         4
#define INIT_SONG         0
#define INIT_LYRIC        0
#define PART_INTRO1       1
#define PART_INTRO1       2
#define PART_VERSE1       3
#define PART_VERSE2       5
#define PART_CHORUS1      4
#define PART_CHORUS2      6
#define PART_END          7

// change these pins according to your setup
int pinBuzzer;
int led = LED_CANT_NO_DISP;

volatile int beatlength = BEAT_LENGTH; // determines tempo
float beatseparationconstant = BEAT_SEPARATION;

int a; // part index
unsigned int b; // song index
int c; // lyric index

boolean flag; // play/pause

// Parts 1 and 2 (Intro)

int song1_intro_melody[] =
{C5S, E5F, E5F, F5, A5F, F5S, F5, E5F, C5S, E5F, REST, A4F, A4F};

int song1_intro_rhythmn[] =
{6, 10, 6, 6, 1, 1, 1, 1, 6, 10, 4, 2, 10};

// Parts 3 or 5 (Verse 1)

int song1_verse1_melody[] =
{ REST, C4S, C4S, C4S, C4S, E4F, REST, C4, B3F, A3F,
  REST, B3F, B3F, C4, C4S, A3F, A4F, A4F, E4F,
  REST, B3F, B3F, C4, C4S, B3F, C4S, E4F, REST, C4, B3F, B3F, A3F,
  REST, B3F, B3F, C4, C4S, A3F, A3F, E4F, E4F, E4F, F4, E4F,
  C4S, E4F, F4, C4S, E4F, E4F, E4F, F4, E4F, A3F,
  REST, B3F, C4, C4S, A3F, REST, E4F, F4, E4F
};

int song1_verse1_rhythmn[] =
{ 2, 1, 1, 1, 1, 2, 1, 1, 1, 5,
  1, 1, 1, 1, 3, 1, 2, 1, 5,
  1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 3,
  1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 4,
  5, 1, 1, 1, 1, 1, 1, 1, 2, 2,
  2, 1, 1, 1, 3, 1, 1, 1, 3
};

String lyrics_verse1[] =
{ "We're ", "no ", "strangers ", "", "to ", "love ", "", "\r\n",
  "You ", "know ", "the ", "rules ", "and ", "so ", "do ", "I\r\n",
  "A ", "full ", "commitment's ", "", "", "what ", "I'm ", "thinking ", "", "of", "\r\n",
  "You ", "wouldn't ", "", "get ", "this ", "from ", "any ", "", "other ", "", "guy\r\n",
  "I ", "just ", "wanna ", "", "tell ", "you ", "how ", "I'm ", "feeling", "\r\n",
  "Gotta ", "", "make ", "you ", "understand", "", "\r\n"
};

// Parts 4 or 6 (Chorus)

int song1_chorus_melody[] =
{ B4F, B4F, A4F, A4F,
  F5, F5, E5F, B4F, B4F, A4F, A4F, E5F, E5F, C5S, C5, B4F,
  C5S, C5S, C5S, C5S,
  C5S, E5F, C5, B4F, A4F, A4F, A4F, E5F, C5S,
  B4F, B4F, A4F, A4F,
  F5, F5, E5F, B4F, B4F, A4F, A4F, A5F, C5, C5S, C5, B4F,
  C5S, C5S, C5S, C5S,
  C5S, E5F, C5, B4F, A4F, REST, A4F, E5F, C5S, REST
};

int song1_chorus_rhythmn[] =
{ 1, 1, 1, 1,
  3, 3, 6, 1, 1, 1, 1, 3, 3, 3, 1, 2,
  1, 1, 1, 1,
  3, 3, 3, 1, 2, 2, 2, 4, 8,
  1, 1, 1, 1,
  3, 3, 6, 1, 1, 1, 1, 3, 3, 3, 1, 2,
  1, 1, 1, 1,
  3, 3, 3, 1, 2, 2, 2, 4, 8, 4
};

String lyrics_chorus[] =
{ "Never ", "", "gonna ", "", "give ", "you ", "up\r\n",
  "Never ", "", "gonna ", "", "let ", "you ", "down", "", "\r\n",
  "Never ", "", "gonna ", "", "run ", "around ", "", "", "", "and ", "desert ", "", "you\r\n",
  "Never ", "", "gonna ", "", "make ", "you ", "cry\r\n",
  "Never ", "", "gonna ", "", "say ", "goodbye ", "", "", "\r\n",
  "Never ", "", "gonna ", "", "tell ", "a ", "lie ", "", "", "and ", "hurt ", "you\r\n"
};

void Extras::begin(int pinBuzzer)
{
	this->pinBuzzer = pinBuzzer;
  flag = true;
  a = INIT_PART;
  b = INIT_SONG;
  c = INIT_LYRIC;
}

void Extras::exec(){
  int notelength = 0;
  if (a == PART_INTRO1 || a == PART_INTRO2) { // Intro
    // intro
    notelength = beatlength * song1_intro_rhythmn[b];
    if (song1_intro_melody[b] > 0) { // if not a REST, play note
      digitalWrite(led, HIGH);
      tone(pinBuzzer, song1_intro_melody[b], notelength);
    }
    b++;
    if (b >= sizeof(song1_intro_melody) / sizeof(int)) {
      a++;
      b = 0;
      c = 0;
    }
  }
  else if (a == PART_VERSE1 || a == PART_VERSE2) { // Verse 1
    // verse
    notelength = beatlength * BEAT_MULT * song1_verse1_rhythmn[b];
    if (song1_verse1_melody[b] > 0) {
      digitalWrite(led, HIGH);
      Serial.print(lyrics_verse1[c]);
      tone(pinBuzzer, song1_verse1_melody[b], notelength);
      c++;
    }
    b++;
    if (b >= sizeof(song1_verse1_melody) / sizeof(int)) {
      a++;
      b = 0;
      c = 0;
    }
  }
  else if (a == PART_CHORUS1 || a == PART_CHORUS2) { //chorus
    // chorus
    notelength = beatlength * song1_chorus_rhythmn[b];
    if (song1_chorus_melody[b] > 0) {
      digitalWrite(led, HIGH);
      Serial.print(lyrics_chorus[c]);
      tone(pinBuzzer, song1_chorus_melody[b], notelength);
      c++;
    }
    b++;
    if (b >= sizeof(song1_chorus_melody) / sizeof(int)) {
      Serial.println("");
      a++;
      b = 0;
      c = 0;
    }
  }
  noTone(pinBuzzer);
  digitalWrite(led, LOW);
  if (a == PART_END) { // loop back around to beginning of song
    a = PART_INTRO1;
  }
} 
