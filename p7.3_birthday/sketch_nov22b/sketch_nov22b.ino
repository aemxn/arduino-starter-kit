/* Play Melody
 * -----------
 * (cleft) 2005 D. Cuartielles for K3
 * Refactoring and comments 2006 clay.shirky@nyu.edu
 * See NOTES in comments at end for possible improvements
 */

#include "pitches.h"

// SETUP ============================================
// Set up speaker on a PWM pin (digital 9, 10 or 11)
int speakerOut = 9;
// Do we want debugging on serial out? 1 for yes, 0 for no
int DEBUG = 0;

void setup() { 
  pinMode(speakerOut, OUTPUT);
  if (DEBUG) { 
    //Serial.begin(9600); // Set serial out if we want debugging
  }
  Serial.begin(9600); // Set serial out if we want debugging
}

// MELODY and TIMING  =======================================
//  melody[] is an array of notes, accompanied by beats[], 
//  which sets each note's relative length (higher #, longer note) 

// Birthday Melody
// Note source: http://www.appybirthday.org/wp-content/uploads/2014/08/happy-birthday-song-piano-notes.jpg

int melody[] = {
  NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, NOTE_C3, NOTE_B3, 0,
  NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, NOTE_D3, NOTE_C3, 0,
  NOTE_G3, NOTE_G3, NOTE_G3, NOTE_E3, NOTE_C3, NOTE_B3, NOTE_A3, 0,
  NOTE_F3, NOTE_F3, NOTE_E3, NOTE_C3, NOTE_D3, NOTE_C3, 0
};
int beats[]  = {
  32, 16, 42, 42, 42, 128, 28,
  32, 16, 42, 42, 42, 128, 28,
  32, 16, 42, 42, 42, 42, 42, 32,
  32, 16, 42, 42, 42, 128, 28
};

char* lyrics[] = {
  "ha", "ppy ", "birth", "day ", "to ", "you", "\n",
  "ha", "ppy ", "birth", "day ", "to ", "you", "\n",
  "ha", "ppy ", "birth", "day ", "to ", "Nabila", "\n",
  "ha", "ppy ", "birth", "day ", "to ", "you!", "\n",
};

int MAX_COUNT = sizeof(melody) / 2; // Melody length, for looping.

// Set overall tempo
long tempo = 11000;
// Set length of pause between notes
int pause = 1000;
// Loop variable to increase Rest length
int rest_count = 100; //<-BLETCHEROUS HACK; See NOTES

// Initialize core variables
int tone_ = 0;
int beat = 0;
long duration  = 0;

// PLAY TONE  ==============================================
// Pulse the speaker to play a tone for a particular duration
void playTone() {
  long elapsed_time = 0;
  if (tone_ > 0) { // if this isn't a Rest beat, while the tone has 
    //  played less long than 'duration', pulse speaker HIGH and LOW
    while (elapsed_time < duration) {

      digitalWrite(speakerOut,HIGH);
      delayMicroseconds(tone_ / 2);

      // DOWN
      digitalWrite(speakerOut, LOW);
      delayMicroseconds(tone_ / 2);

      // Keep track of how long we pulsed
      elapsed_time += (tone_);
    } 
  }
  else { // Rest beat; loop times delay
    for (int j = 0; j < rest_count; j++) { // See NOTE on rest_count
      delayMicroseconds(duration);  
    }                                
  }                                 
}

// LET THE WILD RUMPUS BEGIN =============================
void loop() {
  // Set up a counter to pull from melody[] and beats[]
  Serial.print(lyrics[0]);
  for (int i=0; i<MAX_COUNT; i++) {
    tone_ = melody[i];
    beat = beats[i];

    duration = beat * tempo; // Set up timing

    playTone(); 
    // A pause between notes...
    delayMicroseconds(pause);

    if (DEBUG) { // If debugging, report loop, tone, beat, and duration
      Serial.print(i);
      Serial.print(":");
      Serial.print(beat);
      Serial.print(" ");    
      Serial.print(tone_);
      Serial.print(" ");
      Serial.println(duration);
    }
    
    Serial.print(lyrics[i+1]);
  }
  exit(0);  
}
