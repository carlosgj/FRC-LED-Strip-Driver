#ifndef MAIN_H
#define	MAIN_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "shared.h"
#include "patterns.h"
#include "LUTs.h"

#define _XTAL_FREQ 32000000

#define TRUE 1
#define FALSE 0

#define INPUT 1
#define OUTPUT 0

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

void init(void);
void run(void);
void clearData(void);
void shiftPatternOut(void);
void shiftPatternIn(void);
extern void sendData1(void);
extern void sendData2(void);
void copy(unsigned char * src, unsigned char * dest);
extern void toggle();
void interrupt ISR();
void processPattern(void);
void setSolidColor(unsigned char red, unsigned char green, unsigned char blue);
#endif	/* XC_HEADER_TEMPLATE_H */

