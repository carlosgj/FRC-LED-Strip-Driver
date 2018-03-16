#ifndef PATTERNS_H
#define	PATTERNS_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define PATTERN_GREEN_HEARTBEAT (0)
#define PATTERN_RAINBOW (1)
#define PATTERN_PINK_GREEN_FADE (2)
#define PATTERN_PINK_GREEN_HEARTBEAT (3)
#define PATTERN_PINK_HEARTBEAT (4)
#define PATTERN_SLOW_GREEN_FLASH (5)
#define PATTERN_FAST_GREEN_FLASH (6)
#define PATTERN_SLOW_RED_FLASH (7)
#define PATTERN_FAST_RED_FLASH (8)
#define PATTERN_SLOW_PINK_FLASH (9)
#define PATTERN_FAST_PINK_FLASH (10)
#define PATTERN_PINK_GREEN_ALTERNATE_SLOW (11)
#define PATTERN_PINK_GREEN_ALTERNATE_FAST (12)

//#define DEFAULT_PATTERN PATTERN_GREEN_HEARTBEAT
#define DEFAULT_PATTERN PATTERN_PINK_GREEN_HEARTBEAT

void GreenHeartbeat();
void PinkGreenFade();
void Rainbow();
void PinkGreenHeartbeat();
void PinkHeartbeat();
#endif	/* XC_HEADER_TEMPLATE_H */

