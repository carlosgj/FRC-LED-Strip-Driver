#ifndef SPICOMM_H
#define	SPICOMM_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define SPICOMM_MODE_IDLE 0
#define SPICOMM_MODE_WAITING 1

unsigned char SPIcomm_mode = SPICOMM_MODE_IDLE;
void SPIinit(void);
void processSPIByte(unsigned char theByte);
#endif
