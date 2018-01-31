#ifndef MAIN_H
#define	MAIN_H

#include <xc.h> // include processor files - each processor file is guarded.

#define TRUE (1)
#define FALSE (0)

#define INPUT (1)
#define OUTPUT (0)

#define ENINT INTCONbits.GIE == TRUE;
#define DISINT INTCONbits.GIE == FALSE;

#define _XTAL_FREQ (32e6)

unsigned char J2_Red = 0;
unsigned char J2_Green = 0;
unsigned char J2_Blue = 0;

unsigned char J3_Red = 0;
unsigned char J3_Green = 0;
unsigned char J3_Blue = 0;

void init(void);
void run(void);
void interrupt ISR(void);

#endif	/* XC_HEADER_TEMPLATE_H */

