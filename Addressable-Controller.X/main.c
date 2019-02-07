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
#include "color.h"
#include "spicomm.h"

void main(void) {
    init();
    clearData();
    unsigned char i;
    HsvColor hsv;
    hsv.h = 0;
    hsv.s = 255;
    hsv.v = 100;
//    for(i=0; i<NUM_LEDS; i+=10){
//        LedData[i].green = 0xff;
//    }
//    for(i=5; i<NUM_LEDS; i+=10){
//        LedData[i].red = 0x7f;
//        LedData[i].blue = 0x7f;
//    }
    for(i=0; i<NUM_LEDS; i++){
        RgbColor thisRGB = HsvToRgb(hsv);
        LedData[i].blue = thisRGB.b;
        LedData[i].green = thisRGB.g;
        LedData[i].red = thisRGB.r;
        hsv.h += 3;
    }
    while(TRUE){
        run();
    }
}

void run(){
    sendData();
    __delay_ms(30);
    shiftPatternOut();
    implementSPITimeout();
    if(SSP1CON1bits.SSPOV){
        SSP1CON1bits.SSPOV = FALSE;
    }
    if(loadByteCounter != processByteCounter){
        processSPIByte(byteBuffer[processByteCounter]);
        processByteCounter++;
        processByteCounter &= 0x7;
    }
}

void init(){
    OSCCONbits.IRCF = 0b1110;
    ANSELA = FALSE;
    ANSELB = FALSE;
    TRISAbits.TRISA2 = OUTPUT;
    
    //Setup timer
    OPTION_REGbits.TMR0CS = 0; //Fosc/4 = 8 MHz
    OPTION_REGbits.PSA = 0; //Assign prescaler
    OPTION_REGbits.PS = 0b110; //0b101 -> 1:64 prescaler (should result in 8 us timer tick w/ 32 MHz Fosc)
    INTCONbits.TMR0IF = FALSE;
    TMR0 = 125; //Setup timer for 1 ms clock
    INTCONbits.TMR0IE = TRUE;
    SPIinit();
    
    INTCONbits.PEIE = TRUE;
    INTCONbits.GIE = TRUE;
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

void interrupt ISR(){
    //Service timer interrupts
    if(INTCONbits.TMR0IF){ 
        ms_count++;
        TMR0 = 125;
        INTCONbits.TMR0IF = FALSE; 
    }
    
    //Handle SPI reception
    if(PIR1bits.SSP1IF){
        byteBuffer[loadByteCounter] = SSP1BUF;
        PIR1bits.SSP1IF = FALSE;
        SSP1CON1bits.SSPOV = FALSE;
        loadByteCounter++;
        loadByteCounter &= 0x7;
    }
}