#ifndef PATTERNS_H
#define	PATTERNS_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "shared.h"

#define RAINBOW_PERIOD (4) //A full rainbow will occupy about 256/RAINBOW_PERIOD LEDs
#define SLOW_FLASH_PERIOD (40)
#define FAST_FLASH_PERIOD (10)


#define PATTERN_GREEN_SOLID                 (0)
#define PATTERN_GREEN_HEARTBEAT             (1)
#define PATTERN_RAINBOW                     (2)
#define PATTERN_PINK_GREEN_FADE             (3)
#define PATTERN_PINK_GREEN_HEARTBEAT        (4)
#define PATTERN_PINK_HEARTBEAT              (5)
#define PATTERN_SLOW_GREEN_FLASH            (6)
#define PATTERN_FAST_GREEN_FLASH            (7)
#define PATTERN_SLOW_RED_FLASH              (8)
#define PATTERN_FAST_RED_FLASH              (9)
#define PATTERN_SLOW_PINK_FLASH             (10)
#define PATTERN_FAST_PINK_FLASH             (11)
#define PATTERN_PINK_GREEN_ALTERNATE_SLOW   (12)
#define PATTERN_PINK_GREEN_ALTERNATE_FAST   (13)
#define PATTERN_OUTGOING_RAINBOW_SLOW       (32)
#define PATTERN_OUTGOING_RAINBOW_FAST       (33)
#define PATTERN_INCOMING_RAINBOW_SLOW       (34)
#define PATTERN_INCOMING_RAINBOW_FAST       (35)

#define DEFAULT_PATTERN PATTERN_OUTGOING_RAINBOW_SLOW

#endif	/* XC_HEADER_TEMPLATE_H */

