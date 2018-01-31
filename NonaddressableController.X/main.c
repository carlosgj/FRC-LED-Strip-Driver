//OPTIONS
#define USE_INTERNAL_OSC

// CONFIG1
#ifdef USE_INTERNAL_OSC
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#else
#pragma config FOSC = HS
#endif
#pragma config WDTE = ON        // Watchdog Timer Enable (WDT enabled)
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
#include <xc.h>
#include "main.h"
#include "pindefs.h"
#include "spicomm.h"

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
#endif
    
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
    OPTION_REGbits.PSA = 0; //Assign prescaler
    OPTION_REGbits.PS = 0b110; //1:128 prescaler (should result in 244 Hz rollover interval w/ 32 MHz Fosc)
    INTCONbits.TMR0IE = TRUE;
    
    ENINT
}

void run(void){
    if(processByteFlag){
        processSPIByte(byteToProcess);
        processByteFlag = FALSE;
    }
}

void interrupt ISR(void){
    if(PIR1bits.SSP1IF){
        processByteFlag = TRUE;
        byteToProcess = SSP1BUF;
        PIR1bits.SSP1IF = FALSE;
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