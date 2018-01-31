#ifndef PINDEFS_H
#define	PINDEFS_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define J2_GREEN_TRIS   TRISAbits.TRISA0
#define J2_GREEN_LAT    LATAbits.LATA0

#define J2_RED_TRIS     TRISAbits.TRISA1
#define J2_RED_LAT      LATAbits.LATA1

#define J2_BLUE_TRIS    TRISAbits.TRISA2
#define J2_BLUE_LAT     LATAbits.LATA2


#define J3_GREEN_TRIS   TRISAbits.TRISA3
#define J3_GREEN_LAT    LATAbits.LATA3

#define J3_RED_TRIS     TRISAbits.TRISA4
#define J3_RED_LAT      LATAbits.LATA4

#define J3_BLUE_TRIS    TRISBbits.TRISB0
#define J3_BLUE_LAT     LATBbits.LATB0

#endif

