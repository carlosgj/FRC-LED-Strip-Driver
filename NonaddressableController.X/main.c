//OPTIONS
#define USE_INTERNAL_OSC

// CONFIG1
#ifdef USE_INTERNAL_OSC
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#else
#pragma config FOSC = HS
#endif
#pragma config WDTE = OFF        // Watchdog Timer Enable (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

#define _XTAL_FREQ 32000000

#include <xc.h>
#include "main.h"
#include "pindefs.h"
#include "spicomm.h"
#include "LUTs.h"
#include "patterns.h"

unsigned char dataByteQueue[255];
unsigned char dataQueueCounter = 0;
unsigned char lastProcessedByte = 0;

unsigned char processByteFlag = FALSE;
unsigned char byteToProcess = 0;
unsigned char currentPWMOffset = 0;

void main(void) {
    init();
    while(TRUE){
        run();
    }
}

void init(void){
    DISINT
#ifdef USE_INTERNAL_OSC
    OSCCONbits.IRCF = 0b1110; //Set HFINTOSC to 32 MHz (w/ PLL)
    OSCCONbits.SCS = 0b0;
#endif
    ANSELA = 0;
    ANSELB = 0;
    INTCONbits.PEIE = TRUE;
    
    J2_RED_TRIS = OUTPUT;
    J2_RED_LAT = FALSE;
    J2_GREEN_TRIS = OUTPUT;
    J2_GREEN_LAT = FALSE;
    J2_BLUE_TRIS = OUTPUT;
    J2_BLUE_LAT = FALSE;
    
    J3_RED_TRIS = OUTPUT;
    J3_RED_LAT = FALSE;
    J3_GREEN_TRIS = OUTPUT;
    J3_GREEN_LAT = FALSE;
    J3_BLUE_TRIS = OUTPUT;
    J3_BLUE_LAT = FALSE;
    
    SPIinit(); 
    
    OPTION_REGbits.TMR0CS = 0; //Fosc/4
    OPTION_REGbits.PSA = 1; //Assign prescaler
    OPTION_REGbits.PS = 0b110; //0b110 -> 1:128 prescaler (should result in 244 Hz rollover interval w/ 32 MHz Fosc)
    INTCONbits.TMR0IE = TRUE;
    
    ENINT
}

unsigned int SPITimeoutCounter = 0;

void run(void){
    if(dataQueueCounter > lastProcessedByte){
        byteToProcess = dataByteQueue[lastProcessedByte++];
        processSPIByte(byteToProcess);
    }
    if(SPIcomm_mode == SPICOMM_MODE_WAITING){
        SPITimeoutCounter++;
        if(SPITimeoutCounter > 50000){
            SPIcomm_mode = SPICOMM_MODE_IDLE;
        }
    }
    else{
        SPITimeoutCounter = 0;
    }
    switch(mode){
        case MODE_PATTERN:
            switch(pattern){
                case PATTERN_GREEN_HEARTBEAT:
                    GreenHeartbeat();
                    break;
                case PATTERN_RAINBOW:
                    Rainbow();
                    break;
                case PATTERN_PINK_GREEN_FADE:
                    PinkGreenFade();
                    break;
                case PATTERN_PINK_GREEN_HEARTBEAT:
                    PinkGreenHeartbeat();
                    break;
                case PATTERN_PINK_HEARTBEAT:
                    PinkHeartbeat();
                    break;
                case PATTERN_SLOW_GREEN_FLASH:
                    J2_Red = J3_Red = 0;
                    J2_Blue = J3_Blue = 0;
                    J2_Green = J3_Green = 255;
                    __delay_ms(750);
                    J2_Green = J3_Green = 0;
                    __delay_ms(750);
                    break;
                case PATTERN_FAST_GREEN_FLASH:
                    J2_Red = J3_Red = 0;
                    J2_Blue = J3_Blue = 0;
                    J2_Green = J3_Green = 255;
                    __delay_ms(60);
                    J2_Green = J3_Green = 0;
                    __delay_ms(60);
                    break;
                case PATTERN_SLOW_RED_FLASH:
                    J2_Red = J3_Red = 255;
                    J2_Blue = J3_Blue = 0;
                    J2_Green = J3_Green = 0;
                    __delay_ms(750);
                    J2_Red = J3_Red = 0;
                    __delay_ms(750);
                    break;
                case PATTERN_FAST_RED_FLASH:
                    J2_Red = J3_Red = 255;
                    J2_Blue = J3_Blue = 0;
                    J2_Green = J3_Green = 0;
                    __delay_ms(60);
                    J2_Red = J3_Red = 0;
                    __delay_ms(60);
                    break;
                case PATTERN_SLOW_PINK_FLASH:
                    J2_Red = J3_Red = 255;
                    J2_Blue = J3_Blue = 255;
                    J2_Green = J3_Green = 0;
                    __delay_ms(750);
                    J2_Red = J3_Red = 0;
                    J2_Blue = J3_Blue = 0;
                    __delay_ms(750);
                    break;
                case PATTERN_FAST_PINK_FLASH:
                    J2_Red = J3_Red = 255;
                    J2_Blue = J3_Blue = 255;
                    J2_Green = J3_Green = 0;
                    __delay_ms(60);
                    J2_Red = J3_Red = 0;
                    J2_Blue = J3_Blue = 0;
                    __delay_ms(60);
                    break;
                case PATTERN_PINK_GREEN_ALTERNATE_SLOW:
                    J2_Red = J3_Red = 255;
                    J2_Blue = J3_Blue = 255;
                    J2_Green = J3_Green = 0;
                    __delay_ms(750);
                    J2_Red = J3_Red = 0;
                    J2_Blue = J3_Blue = 0;
                    J2_Green = J3_Green = 255;
                    __delay_ms(750);
                    break;
                case PATTERN_PINK_GREEN_ALTERNATE_FAST:
                    J2_Red = J3_Red = 255;
                    J2_Blue = J3_Blue = 255;
                    J2_Green = J3_Green = 0;
                    __delay_ms(60);
                    J2_Red = J3_Red = 0;
                    J2_Blue = J3_Blue = 0;
                    J2_Green = J3_Green = 255;
                    __delay_ms(60);
                    break;
                            
                default:
                    pattern = PATTERN_GREEN_HEARTBEAT;
                    break;
            }
            break;
        case MODE_RGB:
            break;
        default:
            mode = MODE_PATTERN;
            break;
    }
}


RgbColor HsvToRgb(HsvColor hsv)
{
    RgbColor rgb;
    unsigned char region, remainder, p, q, t;

    if (hsv.s == 0)
    {
        rgb.r = hsv.v;
        rgb.g = hsv.v;
        rgb.b = hsv.v;
        return rgb;
    }

    region = hsv.h / 43;
    remainder = (hsv.h - (region * 43)) * 6; 

    p = (hsv.v * (255 - hsv.s)) >> 8;
    q = (hsv.v * (255 - ((hsv.s * remainder) >> 8))) >> 8;
    t = (hsv.v * (255 - ((hsv.s * (255 - remainder)) >> 8))) >> 8;

    switch (region)
    {
        case 0:
            rgb.r = hsv.v; rgb.g = t; rgb.b = p;
            break;
        case 1:
            rgb.r = q; rgb.g = hsv.v; rgb.b = p;
            break;
        case 2:
            rgb.r = p; rgb.g = hsv.v; rgb.b = t;
            break;
        case 3:
            rgb.r = p; rgb.g = q; rgb.b = hsv.v;
            break;
        case 4:
            rgb.r = t; rgb.g = p; rgb.b = hsv.v;
            break;
        default:
            rgb.r = hsv.v; rgb.g = p; rgb.b = q;
            break;
    }

    return rgb;
}
void interrupt ISR(void){
    if(PIR1bits.SSP1IF){
        dataByteQueue[dataQueueCounter] = SSP1BUF;
        dataQueueCounter++;
        //byteToProcess = SSP1BUF;
        PIR1bits.SSP1IF = FALSE;
        //processByteFlag = TRUE;
        return;
    }
    
    if(INTCONbits.TMR0IF){
        J2_RED_LAT = (J2_Red > currentPWMOffset);
        J2_GREEN_LAT = (J2_Green > currentPWMOffset);
        J2_BLUE_LAT = (J2_Blue > currentPWMOffset);
        
        J3_RED_LAT = (J3_Red > currentPWMOffset);
        J3_GREEN_LAT = (J3_Green > currentPWMOffset);
        J3_BLUE_LAT = (J3_Blue > currentPWMOffset);
        
        currentPWMOffset++;
        
        INTCONbits.TMR0IF = FALSE; 
    }
}