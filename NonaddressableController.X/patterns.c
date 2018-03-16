#include <xc.h>
#include "LUTs.h"
#include "main.h"
#include "patterns.h"

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 32000000
#endif

void GreenHeartbeat(){
    J2_Red = J3_Red = 0;
    J2_Blue = J3_Blue = 0;
    unsigned char i =0;
    for(i=0;i<56;i++){
        J2_Green = J3_Green = exponentialLUT[i];
        __delay_ms(6);
    }
    for(;i>0;i--){
        J2_Green = J3_Green = exponentialLUT[i];
        __delay_ms(5);
    }

    __delay_ms(1000);
}

void PinkHeartbeat(){
    J2_Green = J3_Green = 0;
    unsigned char i =0;
    for(i=0;i<56;i++){
        J2_Red = J2_Blue = J3_Red = J3_Blue = exponentialLUT[i];
        __delay_ms(6);
    }
    for(;i>0;i--){
        J2_Red = J2_Blue = J3_Red = J3_Blue = exponentialLUT[i];
        __delay_ms(5);
    }

    __delay_ms(1000);
}

void PinkGreenHeartbeat(){
    unsigned char i =0;
    //green
    J2_Red = J3_Red =0;
    J2_Blue = J3_Blue = 0;
    for(i=0;i<sizeof(exponentialLUT);i++){
        J2_Green = J3_Green = exponentialLUT[i];
        __delay_ms(6);
    }
    for(;i>0;i--){
        J2_Green = J3_Green = exponentialLUT[i];
        __delay_ms(5);
    }
    J2_Green = J3_Green = 0;
    __delay_ms(1000);
    
    //pink
    J2_Green = J3_Green =0;
    for(i=0;i<sizeof(exponentialLUT);i++){
        J2_Red = J2_Blue = J3_Red = J3_Blue = exponentialLUT[i];
        __delay_ms(6);
    }
    for(;i>0;i--){
        J2_Red = J2_Blue = J3_Red = J3_Blue = exponentialLUT[i];
        __delay_ms(5);
    }
    J2_Red = J2_Blue = J3_Red = J3_Blue = 0;
    __delay_ms(1000);
}

void PinkGreenFade(){
    J2_Red = J2_Blue = 0;
    J3_Red = J3_Blue = 0;
    J2_Green = J3_Green = 255;
    while(J2_Green > 0){
        J3_Green = --J2_Green;
        J3_Red = ++J2_Red;
        J3_Blue = ++J2_Blue;
        __delay_ms(6);
    }
    __delay_ms(500);
    while(J2_Green < 255){
        J3_Green = ++J2_Green;
        J3_Red = --J2_Red;
        J3_Blue = --J2_Blue;
        __delay_ms(6);
    }
    __delay_ms(500);
}

void Rainbow(){
    J2_Red = J3_Red = 255;
    while(J2_Green < 255){
        J2_Green = ++J3_Green;
        __delay_ms(5);
    }
    while(J2_Red > 0){
        J2_Red = --J3_Red;
        __delay_ms(5);
    }
    while(J2_Blue < 255){
        J2_Blue = ++J3_Blue;
        __delay_ms(5);
    }
    while(J2_Green > 0){
        J2_Green = --J3_Green;
        __delay_ms(5);
    }
    while(J2_Red < 255){
        J2_Red = ++J3_Red;
        __delay_ms(5);
    }
    while(J2_Blue > 0){
        J2_Blue = --J3_Blue;
        __delay_ms(5);
    }
}