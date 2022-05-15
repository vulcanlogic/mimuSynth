#include <6502.h>
#include <conio.h>
#include <apple2.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#include "mockingboard.h"
#include "userinterface.h"

unsigned char octave = 3;
unsigned char key = 0x00;
unsigned char lastKey = 0x00;
unsigned int  tonePeriod[] = {1976, 1865, 1760, 1661, 1566, 1480, 1397, 1319, 1245, 1175, 1109, 1047, 0}; // note frequencies rounded up

tMockingSoundRegisters soundDataLeft = {
    { 0, 0, 0 },
    MIN_NOISE_PERIOD,
    ENABLE_ALL_TONE_CHANNELS,
    { MAX_AMPLITUDE, MAX_AMPLITUDE, MAX_AMPLITUDE },
    MIN_ENVELOPE_PERIOD,
    ENVELOPE_SHAPE_ONE_SHOT_DECAY,
    0,
    0
};

tMockingSoundRegisters soundDataRight = {
    { 0, 0, 0 },
    MIN_NOISE_PERIOD,
    ENABLE_ALL_TONE_CHANNELS,
    { MAX_AMPLITUDE, MAX_AMPLITUDE, MAX_AMPLITUDE },
    MIN_ENVELOPE_PERIOD,
    ENVELOPE_SHAPE_ONE_SHOT_DECAY,
    0,
    0
};

int main(void){
  clrscr();

  mockingBoardInit(4);

  while (1){

    if (kbhit()){
      key = (*(unsigned char*) (0xC000));
    }

    if (lastKey!=key){
      gotoxy(0,0);

      if (key==lastKey-128) {
        cprintf("stop     ");
        mockingBoardStopSound(SPEAKER_BOTH);
      }
      else {
        soundDataLeft.tonePeriod[0]=( (tonePeriod[getPeriodIndex(key&0x7F)]) >> (octave) );
        soundDataLeft.tonePeriod[1]=( (tonePeriod[getPeriodIndex(key&0x7F)]) >> (octave) );
        soundDataLeft.tonePeriod[2]=( (tonePeriod[getPeriodIndex(key&0x7F)]) >> (octave) );
        mockingBoardPlaySound(SPEAKER_BOTH, &soundDataLeft);
        cprintf("play: %d ", soundDataLeft.tonePeriod[0]);
      }

    }
    lastKey = key;
    key = (*(unsigned char*) (0xC010)); // strobe keyboard every cycle

  }

  mockingBoardShutdown();
  return 0;
}
