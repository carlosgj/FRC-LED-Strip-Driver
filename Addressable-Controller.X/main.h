#ifndef MAIN_H
#define	MAIN_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "shared.h"

#define _XTAL_FREQ 32000000

#define TRUE 1
#define FALSE 0

#define INPUT 1
#define OUTPUT 0

union ledData_t{
    unsigned char all[3];
    struct{
        unsigned char blue;
        unsigned char red;
        unsigned char green;
    };
};

union ledData_t LedData[NUM_LEDS] @ 0x2001;

unsigned char LEDCounter @ 0x70;
unsigned int ms_count = 0;
unsigned char pattern = 0;

void init(void);
void run(void);
void clearData(void);
void shiftPatternOut(void);
void shiftPatternIn(void);
extern void sendData(void);
void copy(unsigned char * src, unsigned char * dest);
extern void toggle();
void interrupt ISR();
#endif	/* XC_HEADER_TEMPLATE_H */

