#ifndef PATTERNS_H
#define	PATTERNS_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "shared.h"
#include "LUTs.h"
#include "color.h"

#define RAINBOW_PERIOD (4) //A full rainbow will occupy about 256/RAINBOW_PERIOD LEDs
#define SLOW_FLASH_PERIOD (40)
#define FAST_FLASH_PERIOD (10)

#define PATTERN_OFF                         (0)
#define PATTERN_GREEN_SOLID                 (1)
#define PATTERN_PINK_SOLID                  (2)
#define PATTERN_RED_SOLID                   (3)
#define PATTERN_GREEN_HEARTBEAT_SLOW        (4)
#define PATTERN_PINK_HEARTBEAT_SLOW         (5)
#define PATTERN_RED_HEARTBEAT_SLOW          (6)
#define PATTERN_GREEN_HEARTBEAT_FAST        (7)
#define PATTERN_PINK_HEARTBEAT_FAST         (8)
#define PATTERN_RED_HEARTBEAT_FAST          (9)
#define PATTERN_PINK_GREEN_HEARTBEAT_SLOW   (10)
#define PATTERN_PINK_GREEN_HEARTBEAT_FAST   (11)
#define PATTERN_PINK_GREEN_ALTERNATE_SLOW   (12)
#define PATTERN_PINK_GREEN_ALTERNATE_FAST   (13)
#define PATTERN_PINK_GREEN_FADE_SLOW        (14)
#define PATTERN_PINK_GREEN_FADE_FAST        (15)
#define PATTERN_GREEN_FLASH_SLOW            (16)
#define PATTERN_RED_FLASH_SLOW              (17)
#define PATTERN_PINK_FLASH_SLOW             (18)
#define PATTERN_GREEN_FLASH_FAST            (19)
#define PATTERN_RED_FLASH_FAST              (20)
#define PATTERN_PINK_FLASH_FAST             (21)
#define PATTERN_RAINBOW_TIME_SLOW           (22)
#define PATTERN_RAINBOW_TIME_FAST           (23)
#define PATTERN_BROKEN_GREEN                (24)
#define PATTERN_BROKEN_GREEN_OUT_SLOW       (25)
#define PATTERN_BROKEN_GREEN_OUT_FAST       (26)
#define PATTERN_BROKEN_GREEN_IN_SLOW        (27)
#define PATTERN_BROKEN_GREEN_IN_FAST        (28)
#define PATTERN_BROKEN_PINK                 (29)
#define PATTERN_BROKEN_PINK_OUT_SLOW        (30)
#define PATTERN_BROKEN_PINK_OUT_FAST        (31)
#define PATTERN_BROKEN_PINK_IN_SLOW         (32)
#define PATTERN_BROKEN_PINK_IN_FAST         (33)
#define PATTERN_RAINBOW_SPACE               (34)
#define PATTERN_RAINBOW_SPACE_OUT_SLOW      (35)
#define PATTERN_RAINBOW_SPACE_OUT_FAST      (36)
#define PATTERN_RAINBOW_SPACE_IN_SLOW       (37)
#define PATTERN_RAINBOW_SPACE_IN_FAST       (38)
#define PATTERN_BROKEN_PINK_GREEN           (39)
#define PATTERN_BROKEN_PINK_GREEN_OUT_SLOW  (40)
#define PATTERN_BROKEN_PINK_GREEN_OUT_FAST  (41)
#define PATTERN_BROKEN_PINK_GREEN_IN_SLOW   (42)
#define PATTERN_BROKEN_PINK_GREEN_IN_FAST   (43)

#define DEFAULT_PATTERN PATTERN_RAINBOW_SPACE_OUT_SLOW


union ledData_t{
    unsigned char all[3];
    struct{
        unsigned char green;
        unsigned char red;
        unsigned char blue;
    };
};

union ledData_t LedData[NUM_LEDS] @ 0x2001;

unsigned char LEDCounter @ 0x70;
unsigned int ms_count = 0;
unsigned char pattern = DEFAULT_PATTERN;
volatile unsigned char patternState=0;

void processPattern(void);
void setSolidColor(unsigned char red, unsigned char green, unsigned char blue);
void copy(unsigned char * src, unsigned char * dest);
void clearData(void);
void shiftPatternOut(void);
void shiftPatternIn(void);
void flash(unsigned char r1, unsigned char g1, unsigned char b1, 
        unsigned char r2, unsigned char g2, unsigned char b2, 
        unsigned char period);
void heartbeat(unsigned char red, unsigned char green, unsigned char blue, 
        unsigned char speed);

#endif	/* XC_HEADER_TEMPLATE_H */

