#include <6502.h>
#include <conio.h>
#include <apple2.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#include "mockingboard.h"
#include "userinterface.h"

unsigned char octave1 = 0;
unsigned char octave2 = 0;
unsigned char key = 0x00;
unsigned char lastKey = 0x00;
unsigned int  tonePeriod[] = {1976, 1865, 1760, 1661, 1566, 1480, 1397, 1319, 1245, 1175, 1109, 1047, 0}; // note frequencies rounded up

/*

int pow(int x, unsigned int y)
{
    if (y == 0)
        return 1;
    else if ((y % 2) == 0)
        return pow (x, y / 2) * pow (x, y / 2);
    else
        return x * pow (x, y / 2) * pow (x, y / 2);

}

// soundDataLeft.tonePeriod[0]=147*pow(2, (tonePeriod[getPeriodIndex(key&0x7F)]/12) );

*/

tMockingSoundRegisters soundDataLeft = {
    { 0, 0, 0 },
    MIN_NOISE_PERIOD,
    ENABLE_CHANNEL(TONE_CHANNEL_A),
    { MAX_AMPLITUDE, 0, 0 },
    4096,
    ENVELOPE_SHAPE_CONT_ATTACK,
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

unsigned int  envelopePeriod=0;
unsigned char envelopeShape=0;
unsigned char periodIndex=0;

int main(void){
  clrscr();

  mockingBoardInit(4);
  gotoxy(1,21); cprintf("  [s] [d]  [g] [h] [j]");
  gotoxy(1,22); cprintf("[z] [x] [c] [v] [b] [n] [m]");

  while (1){

    if (kbhit()){
      key = (*(unsigned char*) (0xC000));
    }

    if (lastKey!=key){
      gotoxy(0,0);

      if (key==lastKey-128) {
        cprintf("%d", envelopeShape);
        mockingBoardStopSound(SPEAKER_BOTH);
      }
      else if (key==219){
        envelopePeriod-=100;
      }
      else if (key==221){
        envelopePeriod+=100;
      }
      else if (key==167){
        envelopeShape--;
        if (envelopeShape<1) envelopeShape = 0;
      }
      else if (key==220){
        envelopeShape++;
        if (envelopeShape>14) envelopeShape=15;
      }
      else {
        periodIndex = getPeriodIndex(key&0x7F);
        soundDataLeft.tonePeriod[0] = ( tonePeriod[periodIndex] >> (octave1) );
        soundDataLeft.envelopePeriod = envelopePeriod;
        soundDataLeft.envelopeShape = envelopeShape;
        mockingBoardPlaySound(SPEAKER_BOTH, &soundDataLeft);
        cprintf("%04d Hz", soundDataLeft.tonePeriod[0]);
      }

    }
    lastKey = key;
    key = (*(unsigned char*) (0xC010)); // strobe keyboard every cycle

  }

  mockingBoardShutdown();
  return 0;
}
