#ifndef _BUZZER_H_
#define _BUZZER_H_

#include "pitches.h"

class Buzzer{
private:
    int melody[7] = {
        NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, NOTE_B3, NOTE_C4
    };

    int noteDurations[7] = {
        4, 4, 4, 4, 4, 4, 4
    };

public:
    Buzzer();

    void playNumberedMelody(int melodyIndex, int delayMilis);
};

#endif
