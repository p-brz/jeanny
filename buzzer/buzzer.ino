#include "pitches.h"

#define BUZZER 15
#define BUTTON1 5
#define BUTTON2 12
#define BUTTON4 13

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 4, 4
};

int buttonState1 = 0;
int buttonState2 = 0;
int buttonState4 = 0;

void setup() {
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON4, INPUT);
}

void loop() {
  buttonState1 = digitalRead(BUTTON1);
  buttonState2 = digitalRead(BUTTON2);
  buttonState4 = digitalRead(BUTTON4);

  if(buttonState1 == HIGH){
    int noteDuration = 1000 / noteDurations[0];
    tone(BUZZER, melody[0], noteDuration);
    delay(250);
    
    noTone(BUZZER);
  }

  if(buttonState2 == HIGH){
    int noteDuration = 1000 / noteDurations[1];
    tone(BUZZER, melody[1], noteDuration);
    delay(250);
    
    noTone(BUZZER);
  }

  if(buttonState4 == HIGH){
    int noteDuration = 1000 / noteDurations[3];
    tone(BUZZER, melody[5], noteDuration);    
    delay(250);
    
    noTone(BUZZER);
  }
}
