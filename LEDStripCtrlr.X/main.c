#define _XTAL_FREQ 32000000

#include <xc.h>
#include "pindefs.h"
#include "common.h"

void LongWait(void){
    EIGHTNOP
    TWONOP
    ONENOP
}

void ShortWait(void){
    FOURNOP
    ONENOP
}

void sendPixel(unsigned long ch1, unsigned long ch2){
    unsigned char i;
    for(i=0;i<24;i++){
        //Assume we start low
        CH1HIGH
        CH2HIGH
        ShortWait();
        if(ch1 & 1){
            //This bit is 1
            ONENOP
        }
        else{
            //This bit is 0
            CH1LOW
        }
        if(ch2 & 1){
            //This bit is 1
            ONENOP
        }
        else{
            //This bit is 0
            CH2LOW
        }
        ShortWait();
        CH1LOW
        CH2LOW
        ShortWait();
        
        ch1 >>= 1;
        ch2 >>= 1;
    }
}

void SetSolidColor(pixel * pixelBuffer, unsigned char pixelCount, unsigned char red, unsigned char green, unsigned char blue){
    unsigned char i;
    for(i=0; i<pixelCount; i++){
        pixelBuffer[i].red = red;
        pixelBuffer[i].green = green;
        pixelBuffer[i].blue = blue;
    }
}

void TestPattern(void){
    pixel data[10];
    unsigned char testpattern[6][3] = {
        {0x00, 0x00, 0x00},
        {0x00, 0x00, 0xff},
        {0x00, 0xff, 0xff},
        {0xff, 0xff, 0xff},
        {0xff, 0xff, 0x00},
        {0xff, 0x00, 0x00}
    };
    unsigned char patternIdx;
    unsigned char j;
    for(patternIdx=0; patternIdx<6; patternIdx++){
        SetSolidColor(data, 10, testpattern[patternIdx][0], testpattern[patternIdx][1], testpattern[patternIdx][2]);
        for(j=0; j<10; j++){
            sendPixel(data[j].all, data[j].all);
        }
        __delay_ms(500);
    }
}

void main(void) {
    TestPattern();
}
