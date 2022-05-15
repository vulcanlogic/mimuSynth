#ifndef __mockingboard__h__
#define __mockingboard__h__

/* Based on the library of Jeremy Rand */

#include <stdbool.h>
#include <stdint.h>

#define MOCK_NUM_CHANNELS 3
#define LATCH_COMMAND 0x7
#define WRITE_COMMAND 0x6
#define RESET_COMMAND 0x0
#define THROUGH_PORT_B 0x4

#define MIN_NOISE_PERIOD 0
#define MAX_NOISE_PERIOD 31

#define TONE_CHANNEL_A    1
#define TONE_CHANNEL_B    2
#define TONE_CHANNEL_C    4
#define NOISE_CHANNEL_A   8
#define NOISE_CHANNEL_B  16
#define NOISE_CHANNEL_C  32

#define ENABLE_CHANNEL(channels)  (0x3f ^ (channels))
#define ENABLE_ALL_TONE_CHANNELS  ENABLE_CHANNEL(TONE_CHANNEL_A|TONE_CHANNEL_B|TONE_CHANNEL_C)
#define ENABLE_ALL_NOISE_CHANNELS ENABLE_CHANNEL(NOISE_CHANNEL_A|NOISE_CHANNEL_B|NOISE_CHANNEL_C)
#define ENABLE_ALL_CHANNELS       ENABLE_CHANNEL(TONE_CHANNEL_A|TONE_CHANNEL_B|TONE_CHANNEL_C|NOISE_CHANNEL_A|NOISE_CHANNEL_B|NOISE_CHANNEL_C)

#define MIN_AMPLITUDE       0
#define MAX_AMPLITUDE      15
#define VARIABLE_AMPLITUDE 16

#define MIN_ENVELOPE_PERIOD 0
#define MAX_ENVELOPE_PERIOD 65535u
#define MILLISEC_TO_ENVELOP_PERIOD(ms) ((ms) * 4)

#define ENVELOPE_SHAPE_ONE_SHOT_DECAY        0
#define ENVELOPE_SHAPE_ONE_SHOT_ATTACK       4
#define ENVELOPE_SHAPE_CONT_DECAY            8
#define ENVELOPE_SHAPE_CONT_DECAY_HOLD       9
#define ENVELOPE_SHAPE_CONT_DECAY_ALT       10
#define ENVELOPE_SHAPE_CONT_DECAY_ALT_HOLD  11
#define ENVELOPE_SHAPE_CONT_ATTACK          12
#define ENVELOPE_SHAPE_CONT_ATTACK_HOLD     13
#define ENVELOPE_SHAPE_CONT_ATTACK_ALT      14
#define ENVELOPE_SHAPE_CONT_ATTACK_ALT_HOLD 15


typedef uint8_t tSlot;


typedef enum {
    SPEAKER_NONE = 0,
    SPEAKER_LEFT = (1 << 0),
    SPEAKER_RIGHT = (1 << 1),
    SPEAKER_BOTH = (1 << 0) | (1 << 1)
} tMockingBoardSpeaker;


typedef struct tMockingSoundRegisters {
    uint16_t tonePeriod[MOCK_NUM_CHANNELS];
    uint8_t  noisePeriod;
    uint8_t  enable;
    uint8_t  amplitude[MOCK_NUM_CHANNELS];
    uint16_t envelopePeriod;
    uint8_t  envelopeShape;
    uint8_t  dummy1;
    uint8_t  dummy2;
} tMockingSoundRegisters;

// API

extern void mockingBoardInit(tSlot slot);
extern void mockingBoardShutdown(void);

extern void mockingBoardPlaySound(tMockingBoardSpeaker speaker, tMockingSoundRegisters *registers);
extern void mockingBoardStopSound(tMockingBoardSpeaker speaker);



#endif
