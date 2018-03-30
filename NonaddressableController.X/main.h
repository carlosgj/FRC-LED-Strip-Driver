#ifndef MAIN_H
#define	MAIN_H

#include <xc.h> // include processor files - each processor file is guarded.
#include "patterns.h"

#define TRUE (1)
#define FALSE (0)

#define INPUT (1)
#define OUTPUT (0)

#define ENINT INTCONbits.GIE = TRUE;
#define DISINT INTCONbits.GIE = FALSE;

#define TMR0_INIT_VALUE 200

#define MODE_RGB (0)
#define MODE_PATTERN (1)

unsigned char J2_Red = 0;
unsigned char J2_Green = 0;
unsigned char J2_Blue = 0;

unsigned char J3_Red = 0;
unsigned char J3_Green = 0;
unsigned char J3_Blue = 0;

unsigned char mode = MODE_PATTERN;
unsigned char pattern = DEFAULT_PATTERN;

typedef struct RgbColor
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RgbColor;

typedef struct HsvColor
{
    unsigned char h;
    unsigned char s;
    unsigned char v;
} HsvColor;

void init(void);
void run(void);
RgbColor HsvToRgb(HsvColor hsv);
void interrupt ISR(void);
#endif	/* XC_HEADER_TEMPLATE_H */

