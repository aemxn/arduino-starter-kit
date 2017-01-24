/** Play Melody
 * -----------
 * (cleft) 2005 D. Cuartielles for K3
 * Refactoring and comments 2006 clay.shirky@nyu.edu
 * See NOTES in comments at end for possible improvements
 **/
 
// Birthday Melody
// Note source: http://www.appybirthday.org/wp-content/uploads/2014/08/happy-birthday-song-piano-notes.jpg
 
#include <LiquidCrystal.h>
#include "pitches.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int speakerOut = 9;

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
  "happy", "happy", "birthday", "birthday", "to you", "to you", "to you",
  "happy", "happy", "birthday", "birthday", "to you", "to you", "to you",
  "happy", "happy", "birthday", "birthday", "to Nabila", "to Nabila", "to Nabila",
  "happy", "happy", "birthday", "birthday", "to you!", "to you!", "to you!",
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
long duration = 0;

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

void setup() { 
  pinMode(speakerOut, OUTPUT);
  
  lcd.begin(16, 2);
}

void loop() {
  lcd.clear();
  delay(2000);
  for (int i=0; i<MAX_COUNT; i++) {
    lcd.print(".............................");
    tone_ = melody[i];
    beat = beats[i];

    duration = beat * tempo; // Set up timing

    playTone();
    // A pause between notes...
    delayMicroseconds(pause);
    lcd.setCursor(0, 0);
    lcd.print(lyrics[i]);
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Happy birthday!");
  lcd.setCursor(0, 1);
  lcd.print("<3");
  exit(0);  
}
