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
#include "patterns.h"

void main(void) {
    init();
    clearData();
    while(TRUE){
        run();
    }
}

void run(){
    sendData1();
    sendData2();
    __delay_ms(30);
    //shiftPatternOut();
    implementSPITimeout();
    if(SSP1CON1bits.SSPOV){
        SSP1CON1bits.SSPOV = FALSE;
    }
    if(loadByteCounter != processByteCounter){
        processSPIByte(byteBuffer[processByteCounter]);
        processByteCounter++;
        processByteCounter &= 0x7;
    }
    processPattern();
}

void init(){
    OSCCONbits.IRCF = 0b1110;
    ANSELA = FALSE;
    ANSELB = FALSE;
    TRISAbits.TRISA2 = OUTPUT;
    TRISAbits.TRISA3 = OUTPUT;
    
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

