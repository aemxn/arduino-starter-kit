/*
  Melody

 Plays a melody

 circuit:
 * 8-ohm speaker on digital pin 8

 created 21 Jan 2010
 modified 30 Aug 2011
 by Tom Igoe

This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Tone

 */
#include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_E6, NOTE_B6, 0, // 3
  NOTE_FS6, NOTE_B6, NOTE_E6, 0, // 4
  NOTE_E6, NOTE_GS6, NOTE_A6, NOTE_CS6, NOTE_FS6, 0, // 6
  NOTE_E6, NOTE_FS6, NOTE_E6, 0, // 4
  NOTE_E6, NOTE_GS6, NOTE_A6, NOTE_CS6, NOTE_FS6, 0, // 6
  NOTE_E6, NOTE_B6, NOTE_E6 // 3
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4, 4, 4,
  4, 4, 4
};

void setup() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < sizeof(melody); thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

void loop() {
  // no need to repeat the melody.
}
