#ifndef _BUZZER_H_
#define _BUZZER_H_

class Buzzer{
private:
    int melody[];
    int noteDurations[];

public:
    Buzzer();

    void playNumberedMelody(int melodyIndex, int delayMilis);
};

#endif
