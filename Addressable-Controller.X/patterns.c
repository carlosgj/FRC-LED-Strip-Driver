#include <xc.h>
#include "patterns.h"

void clearData(void){
    unsigned char i;
    for(i=0; i<NUM_LEDS; i++){
        LedData[i].red = 0x00;
        LedData[i].green = 0x00;
        LedData[i].blue = 0x00;
    }
}

void shiftPatternIn(){
    unsigned char i;
    union ledData_t holding;
    for(i=(NUM_LEDS); i>0; i--){
        if(i==(NUM_LEDS)){
            holding.red = LedData[i-1u].red;
            holding.green = LedData[i-1u].green;
            holding.blue = LedData[i-1u].blue;
        }
        if(i == 1){
            LedData[i-1u].red = holding.red;
            LedData[i-1u].green = holding.green;
            LedData[i-1u].blue = holding.blue;
        }
        else{
            LedData[i-1u] = LedData[i-2u];
        }
    }
}

void shiftPatternOut(){
    unsigned char i;
    union ledData_t holding;
    for(i=0; i<NUM_LEDS; i++){
        if(i==0){
            copy(LedData[i].all, holding.all);
        }
        if(i == (NUM_LEDS-1)){
            copy(holding.all, LedData[i].all);
        }
        else{
            copy(LedData[i+1u].all, LedData[i].all);
        }
    }
}

void pushOutward(unsigned char red, unsigned char green, unsigned char blue){
    unsigned char i;
    for(i=0; i<NUM_LEDS; i++){
        if(i == (NUM_LEDS-1)){
            LedData[i].red = red;
            LedData[i].green = green;
            LedData[i].blue = blue;
        }
        else{
            copy(LedData[i+1u].all, LedData[i].all);
        }
    }
}

void copy(unsigned char * src, unsigned char * dest){
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
}

void setSolidColor(unsigned char red, unsigned char green, unsigned char blue){
    unsigned char i;
    for(i=0; i<NUM_LEDS; i++){
        LedData[i].green = green;
        LedData[i].blue = blue;
        LedData[i].red = red;
    }
}

void flash(unsigned char r1, unsigned char g1, unsigned char b1, 
        unsigned char r2, unsigned char g2, unsigned char b2, 
        unsigned char period){
    if(patternState < (period / 2)){
        setSolidColor(r1, g1, b1);
    }
    else{
        setSolidColor(r2, g2, b2);
    }
    patternState++;
    if(patternState == period){
        patternState = 0;
    }
}

void heartbeat(unsigned char red, unsigned char green, unsigned char blue, unsigned char speed){
    unsigned char val;
    if(patternState < sizeof(exponentialLUT)){
        val = exponentialLUT[patternState];
        patternState += speed;
    }
    else{
        val = exponentialLUT[111u-patternState];
        patternState += speed;
    }
    setSolidColor((unsigned char)(red*val), (unsigned char)(green*val), (unsigned char)(blue*val));
    if(patternState >= (2*sizeof(exponentialLUT))){
        patternState = 0;
    }
}

void processPattern(){
    unsigned char i; 
    unsigned char j;
    static HsvColor hsv;
    
    switch(pattern){
        case PATTERN_OFF:
            if(patternState == 0){
                clearData();
            }
            patternState++;
            break;
        case PATTERN_GREEN_SOLID:
            if(patternState == 0){
                setSolidColor(0, 255, 0);
            }
            patternState++;
            break;
        case PATTERN_PINK_SOLID:
            if(patternState == 0){
                setSolidColor(255, 0, 255);
            }
            patternState++;
            break;
        case PATTERN_RED_SOLID:
            if(patternState == 0){
                setSolidColor(255, 0, 0);
            }
            patternState++;
            break;
        case PATTERN_GREEN_HEARTBEAT_SLOW:
            heartbeat(0, 1, 0, 1);
            break;
        case PATTERN_PINK_HEARTBEAT_SLOW:
            heartbeat(1, 0, 1, 1);
            break;
        case PATTERN_RED_HEARTBEAT_SLOW:
            heartbeat(1, 0, 0, 1);
            break;
        case PATTERN_GREEN_HEARTBEAT_FAST:
            heartbeat(0, 1, 0, 2);
            break;
        case PATTERN_PINK_HEARTBEAT_FAST:
            heartbeat(1, 0, 1, 2);
            break;
        case PATTERN_RED_HEARTBEAT_FAST:
            heartbeat(1, 0, 0, 2);
            break;
        case PATTERN_RAINBOW_SPACE:
            if(patternState == 0){
                hsv.h = 0;
                hsv.s = 255;
                hsv.v = 100;
                for(i=0; i<NUM_LEDS; i++){
                    RgbColor thisRGB = HsvToRgb(hsv);
                    LedData[i].blue = thisRGB.b;
                    LedData[i].green = thisRGB.g;
                    LedData[i].red = thisRGB.r;
                    hsv.h += RAINBOW_PERIOD;
                }
            }
            patternState++;
            break;
        case PATTERN_PINK_GREEN_FADE_SLOW:
            if(patternState < 128u){
                setSolidColor((2u*patternState), 255u-(2u*patternState), (2u*patternState));
            }
            else{
                setSolidColor((2u*(255u-patternState)), (2u*(patternState-128u)), (2u*(255u-patternState)));
            }
            
            patternState++;
            break;
        case PATTERN_PINK_GREEN_FADE_FAST:
            if(patternState < 128u){
                setSolidColor((2u*patternState), 255u-(2u*patternState), (2u*patternState));
            }
            else{
                setSolidColor((2u*(255u-patternState)), (2u*(patternState-128u)), (2u*(255u-patternState)));
            }
            
            patternState += 2;
            break;
        case PATTERN_PINK_GREEN_HEARTBEAT_SLOW:
            break;
        case PATTERN_GREEN_FLASH_SLOW:
            flash(0, 0, 0, 0, 255, 0, SLOW_FLASH_PERIOD);
            break;
        case PATTERN_GREEN_FLASH_FAST:
            flash(0, 0, 0, 0, 255, 0, FAST_FLASH_PERIOD);
            break;
        case PATTERN_RED_FLASH_SLOW:
            flash(0, 0, 0, 255, 0, 0, SLOW_FLASH_PERIOD);
            break;
        case PATTERN_RED_FLASH_FAST:
            flash(0, 0, 0, 255, 0, 0, FAST_FLASH_PERIOD);
            break;
        case PATTERN_PINK_FLASH_SLOW:
            flash(0, 0, 0, 255, 0, 255, SLOW_FLASH_PERIOD);
            break;
        case PATTERN_PINK_FLASH_FAST:
            flash(0, 0, 0, 255, 0, 255, FAST_FLASH_PERIOD);
            break;
        case PATTERN_PINK_GREEN_ALTERNATE_SLOW:
            flash(0, 255, 0, 255, 0, 255, SLOW_FLASH_PERIOD);
            break;
        case PATTERN_PINK_GREEN_ALTERNATE_FAST:
            flash(0, 255, 0, 255, 0, 255, FAST_FLASH_PERIOD);
            break;
        case PATTERN_RAINBOW_SPACE_OUT_SLOW:
            if(patternState == 0){
                hsv.h = 0; 
                hsv.s = 255; 
                hsv.v = 255;
                j=0; 
                for(i=0; i<NUM_LEDS; i++){
                    RgbColor thisRGB = HsvToRgb(hsv);
                    LedData[i].blue = thisRGB.b;
                    LedData[i].green = thisRGB.g;
                    LedData[i].red = thisRGB.r;
                    hsv.h += RAINBOW_PERIOD;
                }
            }
            else{
                if((patternState % 2) == 0){
                    RgbColor thisRGB = HsvToRgb(hsv);
                    pushOutward(thisRGB.r, thisRGB.g, thisRGB.b);
                    hsv.h += RAINBOW_PERIOD;
                }
            }
            if(patternState == 255){
                patternState = 1;
            }
            else{
                patternState++;
            }
            break;
        case PATTERN_RAINBOW_SPACE_OUT_FAST:
            if(patternState == 0){
                hsv.h = 0; 
                hsv.s = 255; 
                hsv.v = 255;
                j=0; 
                for(i=0; i<NUM_LEDS; i++){
                    RgbColor thisRGB = HsvToRgb(hsv);
                    LedData[i].blue = thisRGB.b;
                    LedData[i].green = thisRGB.g;
                    LedData[i].red = thisRGB.r;
                    hsv.h += RAINBOW_PERIOD;
                }
            }
            else{
                RgbColor thisRGB = HsvToRgb(hsv);
                pushOutward(thisRGB.r, thisRGB.g, thisRGB.b);
                hsv.h += RAINBOW_PERIOD;
            }
            if(patternState == 255){
                patternState = 1;
            }
            else{
                patternState++;
            }
            break;
        default:
            break;
            
    }
    
}