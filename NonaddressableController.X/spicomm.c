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
                break;
            case 'g':
                dataDestination = &J2_Green;
                SPIcomm_mode = SPICOMM_MODE_WAITING;
                break;
            case 'b':
                dataDestination = &J2_Blue;
                SPIcomm_mode = SPICOMM_MODE_WAITING;
                break;
            case 'R':
                dataDestination = &J3_Red;
                SPIcomm_mode = SPICOMM_MODE_WAITING;
                break;
            case 'G':
                dataDestination = &J3_Green;
                SPIcomm_mode = SPICOMM_MODE_WAITING;
                break;
            case 'B':
                dataDestination = &J3_Blue;
                SPIcomm_mode = SPICOMM_MODE_WAITING;
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
    SSP1CON1bits.SSPEN = TRUE;
    SSP1CON1bits.SSPM = 0b0100; //SPI Slave mode, clock = SCKx pin, SSx pin control enabled
    PIE1bits.SSP1IE = TRUE;
}