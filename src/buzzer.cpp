#include "buzzer.h"
#include "pins.h"


Buzzer::Buzzer(){
    // this->melody = {
    //     NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, NOTE_B3, NOTE_C4
    // };
    //
    // this->noteDurations = {
    //     4, 4, 4, 4, 4, 4, 4, 4
    // };
}

void Buzzer::playNumberedMelody(int melodyIndex, int delayMilis){
    int noteDuration = 1000 / this->noteDurations[melodyIndex];
    tone(buzzerPin, this->melody[melodyIndex], noteDuration);
    delay(delayMilis);
    noTone(buzzerPin);
}
