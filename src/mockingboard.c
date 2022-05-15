#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <conio.h>

#include "mockingboard.h"

bool gMockingBoardInitialized = false;

typedef enum {
    SOUND_CHIP_1 = 0,
    SOUND_CHIP_2 = 1,
    NUM_SOUND_CHIPS = 2
} tMockingBoardSoundChip;

// fixed to slot 4
static uint8_t *gMockPortB[NUM_SOUND_CHIPS]    = { (uint8_t *)0xc400, (uint8_t *)0xc480 };
static uint8_t *gMockPortA[NUM_SOUND_CHIPS]    = { (uint8_t *)0xc401, (uint8_t *)0xc481 };
static uint8_t *gMockDataDirB[NUM_SOUND_CHIPS] = { (uint8_t *)0xc402, (uint8_t *)0xc482 };
static uint8_t *gMockDataDirA[NUM_SOUND_CHIPS] = { (uint8_t *)0xc403, (uint8_t *)0xc483 };

void mockingBoardInit(tSlot slot)
{

  // $C400 ORB1 function to perform, OUT 1
  // $C480 ORB2 function to perform, OUT 2
  // $C401 ORA1 data, OUT 1
  // $C481 ORA2 data, OUT 2
  // $C402 DDRB1 data direction, OUT 1
  // $C482 DDRB2 data direction, OUT 2
  // $C403 DDRA1 data direction, OUT 1
  // $C483 DDRA2 data direction, OUT 2

  tMockingBoardSoundChip soundChip;

    for (soundChip = SOUND_CHIP_1; soundChip < NUM_SOUND_CHIPS; soundChip++) {
        *(gMockDataDirA[soundChip]) = 0xff;     // Set port A for output
        *(gMockDataDirB[soundChip]) = 0xff;     // Set port B for output
    }

    slot = 4; // never used
    gMockingBoardInitialized = true;
}


void mockingBoardShutdown(void)
{
    gMockingBoardInitialized = false;
}


static void issueCommand(tMockingBoardSoundChip soundChip, uint8_t command)
{
    volatile uint8_t *ptr = gMockPortB[soundChip];

    *ptr = command;
    *ptr = THROUGH_PORT_B;
}


static void mockingBoardTableAccess(tMockingBoardSoundChip soundChip, tMockingSoundRegisters *registers)
{
    uint8_t *data = (uint8_t *)registers;
    volatile uint8_t *ptr = gMockPortA[soundChip];
    uint8_t index;

    if (!gMockingBoardInitialized)
        return;

    issueCommand((soundChip), RESET_COMMAND);
    for (index = 0; index < 16; index++) {
        *ptr = index;
        issueCommand((soundChip), LATCH_COMMAND);
        *ptr = *data;
        issueCommand((soundChip), WRITE_COMMAND);
        data++;
    }
}


void mockingBoardPlaySound(tMockingBoardSpeaker speaker, tMockingSoundRegisters *registers)
{
    if ((speaker & SPEAKER_LEFT) != 0) {
        mockingBoardTableAccess(SOUND_CHIP_1, registers);
    }

    if ((speaker & SPEAKER_RIGHT) != 0) {
        mockingBoardTableAccess(SOUND_CHIP_2, registers);
    }
}


void mockingBoardStopSound(tMockingBoardSpeaker speaker)
{
    if ((speaker & SPEAKER_LEFT) != 0) {
        issueCommand((SOUND_CHIP_1), RESET_COMMAND);
    }

    if ((speaker & SPEAKER_RIGHT) != 0) {
        issueCommand((SOUND_CHIP_2), RESET_COMMAND);
    }
}
