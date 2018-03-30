#include <xc.h>
#include "main.h"
#include "spicomm.h"

/*
State machine:
 * Idle -> Receive byte -> Valid command? y -> Waiting for data -> Got data
 *  ^                           n                                       |
 *  |------------------<--------|---------------------------------<-----|
*/

unsigned char *dataDestination = 0; 

void processSPIByte(unsigned char theByte){
    if(SPIcomm_mode == SPICOMM_MODE_IDLE){
        //Check if this is a valid command byte
        switch(theByte){
            case 'r':
                dataDestination = &J2_Red;
                SPIcomm_mode = SPICOMM_MODE_WAITING;
                mode = MODE_RGB;
                break;
            case 'g':
                dataDestination = &J2_Green;
                SPIcomm_mode = SPICOMM_MODE_WAITING;
                mode = MODE_RGB;
                break;
            case 'b':
                dataDestination = &J2_Blue;
                SPIcomm_mode = SPICOMM_MODE_WAITING;
                mode = MODE_RGB;
                break;
            case 'R':
                dataDestination = &J3_Red;
                SPIcomm_mode = SPICOMM_MODE_WAITING;
                mode = MODE_RGB;
                break;
            case 'G':
                dataDestination = &J3_Green;
                SPIcomm_mode = SPICOMM_MODE_WAITING;
                mode = MODE_RGB;
                break;
            case 'B':
                dataDestination = &J3_Blue;
                SPIcomm_mode = SPICOMM_MODE_WAITING;
                mode = MODE_RGB;
                break;
            case 'P':
                dataDestination = &pattern;
                SPIcomm_mode = SPICOMM_MODE_WAITING;
                mode = MODE_PATTERN;
                break;
        }
    }
    else{
        //Process data byte
        *dataDestination = theByte;
        dataDestination = 0;
        SPIcomm_mode = SPICOMM_MODE_IDLE;
    }
}

void SPIinit(void){
    TRISBbits.TRISB5 = INPUT;
    TRISBbits.TRISB4 = INPUT;
    TRISBbits.TRISB1 = INPUT;
    SSP1CON3bits.BOEN = TRUE;
    SSP1CON1bits.CKP = TRUE; //Clock idles low
    SSP1CON1bits.SSPM = 0b0100; //SPI Slave mode, clock = SCKx pin, SSx pin control enabled
    SSP1CON1bits.SSPEN = TRUE;
    PIE1bits.SSP1IE = TRUE;
}