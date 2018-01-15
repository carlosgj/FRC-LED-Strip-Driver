#ifndef COMMON_H
#define COMMON_H
#include <xc.h>

#define ONENOP asm("NOP");
#define TWONOP ONENOP ONENOP
#define FOURNOP TWONOP TWONOP
#define EIGHTNOP FOURNOP FOURNOP
#define SIXTEENNOP EIGHTNOP EIGHTNOP

#define CH1HIGH asm("BSF LATA, 2");
#define CH1LOW asm("BCF LATA, 2");
#define CH2HIGH asm("BSF LATA, 3");
#define CH2LOW asm("BCF LATA, 3");

#define INTERRUPTS asm("BSF INTCON, GIE");
#define NOINTERRUPTS asm("BCF INTCON, GIE");


typedef union{
    unsigned long all;
    struct{
        unsigned char red;
        unsigned char green;
        unsigned char blue;
    };
} pixel;


#endif