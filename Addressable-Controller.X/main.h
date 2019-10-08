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

void init(void);
void run(void);
extern void sendData1(void);
extern void sendData2(void);
extern void toggle();
void interrupt ISR();

#endif	/* XC_HEADER_TEMPLATE_H */

