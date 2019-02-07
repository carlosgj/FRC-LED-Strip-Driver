#ifndef SPICOMM_H
#define	SPICOMM_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define SPICOMM_MODE_IDLE 0
#define SPICOMM_MODE_WAITING 1

#define SPICOMM_TIMEOUT 50 //In ms

unsigned char SPIcomm_mode = SPICOMM_MODE_IDLE;
unsigned char prospective_byte; 
unsigned int got_byte_time; 
unsigned char byteBuffer[8];
unsigned char loadByteCounter = 0;
unsigned char processByteCounter = 0;

void SPIinit(void);
void processSPIByte(unsigned char theByte);
void implementSPITimeout(void);
#endif
