// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
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

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include "main.h"
#include "shared.h"
void main(void) {
    init();
    clearData();
    LedData[0].green = 0xff;
    LedData[1].red = 0xff;
    while(TRUE){
        run();
        __delay_ms(100);
        //shiftPatternOut();
    }
}

void run(){
    sendData();
    //__delay_ms(1);
}

void init(){
    OSCCONbits.IRCF = 0b1110;
    ANSELA = FALSE;
    ANSELB = FALSE;
    TRISBbits.TRISB4 = OUTPUT;
    TRISBbits.TRISB1 = OUTPUT;
    TRISAbits.TRISA2 = OUTPUT;
}

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
            holding.red = LedData[i-1].red;
            holding.green = LedData[i-1].green;
            holding.blue = LedData[i-1].blue;
        }
        if(i == 1){
            LedData[i-1].red = holding.red;
            LedData[i-1].green = holding.green;
            LedData[i-1].blue = holding.blue;
        }
        else{
            LedData[i-1] = LedData[i-2];
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
            copy(LedData[i+1].all, LedData[i].all);
        }
    }
}

void copy(unsigned char * src, unsigned char * dest){
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
}