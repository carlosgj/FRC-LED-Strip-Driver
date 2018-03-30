#ifndef LUTS_H
#define	LUTS_H

#include <xc.h> // include processor files - each processor file is guarded.  

const unsigned char heartbeatLUT[] = {
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

#endif	/* XC_HEADER_TEMPLATE_H */

