#ifndef MAIN_H
#define	MAIN_H

#include <xc.h> // include processor files - each processor file is guarded.

#define TRUE (1)
#define FALSE (0)

#define INPUT (1)
#define OUTPUT (0)

#define ENINT INTCONbits.GIE = TRUE;
#define DISINT INTCONbits.GIE = FALSE;

#define TMR0_INIT_VALUE 200

unsigned char J2_Red = 0;
unsigned char J2_Green = 0;
unsigned char J2_Blue = 0;

unsigned char J3_Red = 0;
unsigned char J3_Green = 0;
unsigned char J3_Blue = 0;

unsigned char heartbeatLUT[] = {
0,
1,
6,
13,
24,
37,
52,
69,
87,
107,
127,
146,
166,
184,
201,
216,
229,
240,
247,
252,
254,
252,
247,
240,
229,
216,
201,
184,
166,
146,
127,
107,
87,
69,
52,
37,
24,
13,
6,
1,
0
};

unsigned char exponentialLUT[] ={
1,
1,
1,
1,
1,
1,
1,
2,
2,
2,
2,
3,
3,
3,
4,
4,
4,
5,
6,
6,
7,
8,
9,
9,
11,
12,
13,
14,
16,
18,
20,
22,
24,
27,
29,
33,
36,
40,
44,
49,
54,
60,
66,
73,
81,
90,
99,
109,
121,
134,
148,
164,
181,
200,
221,
244
};

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
void rainbow();
void pinkGreenFade();
void heartbeat();
#endif	/* XC_HEADER_TEMPLATE_H */

