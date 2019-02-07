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
    switch(SPIcomm_mode){
        case SPICOMM_MODE_IDLE:
            prospective_byte = theByte;
            got_byte_time = ms_count;
            SPIcomm_mode = SPICOMM_MODE_WAITING;
            break;
        case SPICOMM_MODE_WAITING:
            if(theByte ^ prospective_byte == 0xff){
                //Good message
                pattern = prospective_byte;
                SPIcomm_mode = SPICOMM_MODE_IDLE;
            }
            else{
                //Bad message
                SPIcomm_mode = SPICOMM_MODE_IDLE;
            }
            break;
        default:
            SPIcomm_mode = SPICOMM_MODE_IDLE;
            break;
    }
}

void implementSPITimeout(){
    if((SPIcomm_mode == SPICOMM_MODE_WAITING) && ((ms_count - got_byte_time) > SPICOMM_TIMEOUT)){
        SPIcomm_mode = SPICOMM_MODE_IDLE;
    }
}

void SPIinit(void){
    TRISBbits.TRISB5 = INPUT;
    TRISBbits.TRISB4 = INPUT;
    TRISBbits.TRISB1 = INPUT;
    SSP1CON3bits.BOEN = FALSE;
    SSP1CON1bits.CKP = FALSE; //Clock idles low
    SSP1STATbits.CKE = TRUE;
    SSP1CON1bits.SSPM = 0b0101; //SPI Slave mode, clock = SCKx pin, SSx pin control enabled
    SSP1CON1bits.SSPEN = TRUE;
    PIE1bits.SSP1IE = TRUE;
}