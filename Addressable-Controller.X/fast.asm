#include <xc.inc>
#include "shared.h"
; When assembly code is placed in a psect, it can be manipulated as a
; whole by the linker and placed in memory.  
;
; In this example, barfunc is the program section (psect) name, 'local' means
; that the section will not be combined with other sections even if they have
; the same name.  class=CODE means the barfunc must go in the CODE container.
; PIC18's should have a delta (addressible unit size) of 1 (default) since they
; are byte addressible.  PIC10/12/16's have a delta of 2 since they are word
; addressible.  PIC18's should have a reloc (alignment) flag of 2 for any
; psect which contains executable code.  PIC10/12/16's can use the default
; reloc value of 1.  Use one of the psects below for the device you use:

psect   barfunc,local,class=CODE,delta=2 ; PIC10/12/16
; psect   barfunc,local,class=CODE,reloc=2 ; PIC18

global _toggle 
global _sendData1
global _sendData2
_toggle:
    movlb 2
    beg:
	bsf 0xD, 4
	bcf 0xD, 4
	bsf 0xD, 4
	bcf 0xD, 4
	return

_sendData1:
    ;diable interrupts
    movlb 0
    bcf 0x0B, 7
    
    #ifdef DEBUG
    bsf 0xD, 1
    nop
    bcf 0xD, 1
    #endif
    
    ;setup indirect accesses (set FSR0 to max address)
    movlw 0x20
    movwf FSR0H
    movlw 3*NUM_LEDS
    movwf FSR0L
    
    movlb 2
    clrf 0x70; clear LED counter
    
    byteStart1:
    ;first bit (bit 7) starts here
    bsf THEPIN1 ;Turn on
    nop
    btfss INDF0, 7
    bcf THEPIN1; turn off if this is a 0
    nop
    nop
    btfsc INDF0, 7; turn off if this is a 1
    bcf THEPIN1
    nop
    nop
    
    ;bit 6
    bsf THEPIN1 ;Turn on
    nop
    btfss INDF0, 6
    bcf THEPIN1; turn off if this is a 0
    nop
    nop
    btfsc INDF0, 6; turn off if this is a 1
    bcf THEPIN1
    nop
    nop
    
    ;bit 5
    bsf THEPIN1 ;Turn on
    nop
    btfss INDF0, 5
    bcf THEPIN1; turn off if this is a 0
    nop
    nop
    btfsc INDF0, 5; turn off if this is a 1
    bcf THEPIN1
    nop
    nop
    
    ;bit 4
    bsf THEPIN1 ;Turn on
    nop
    btfss INDF0, 4
    bcf THEPIN1; turn off if this is a 0
    nop
    nop
    btfsc INDF0, 4; turn off if this is a 1
    bcf THEPIN1
    nop
    nop
    
    ;bit 3
    bsf THEPIN1 ;Turn on
    nop
    btfss INDF0, 3
    bcf THEPIN1; turn off if this is a 0
    nop
    nop
    btfsc INDF0, 3; turn off if this is a 1
    bcf THEPIN1
    nop
    nop
    
    ;bit 2
    bsf THEPIN1 ;Turn on
    nop
    btfss INDF0, 2
    bcf THEPIN1; turn off if this is a 0
    nop
    nop
    btfsc INDF0, 2; turn off if this is a 1
    bcf THEPIN1
    nop
    nop
    
    ;bit 1
    bsf THEPIN1 ;Turn on
    nop
    btfss INDF0, 1
    bcf THEPIN1; turn off if this is a 0
    nop
    nop
    btfsc INDF0, 1; turn off if this is a 1
    bcf THEPIN1
    nop
    nop
    
    ;bit 0
    bsf THEPIN1 ;Turn on
    nop
    btfss INDF0, 0
    bcf THEPIN1; turn off if this is a 0
    decfsz FSR0L
    goto lastBCF1
    goto exit1
    lastBCF1:
    bcf THEPIN1
    goto byteStart1
    
    exit1:
    bcf THEPIN1
    
    ;reenable interrupts
    movlb 0
    bsf 0x0B, 7
    
    movlw 6
    movwf FSR0L
    outerwaitloop1:
	movlw 0xff
	waitloop1:
	    decfsz WREG
	    goto waitloop1
	decfsz FSR0L
	goto outerwaitloop1
    return
    
    
_sendData2:
    ;diable interrupts
    movlb 0
    bcf 0x0B, 7
    
    #ifdef DEBUG
    bsf 0xD, 1
    nop
    bcf 0xD, 1
    #endif
    
    ;setup indirect accesses (set FSR0 to max address)
    movlw 0x20
    movwf FSR0H
    movlw 3*NUM_LEDS
    movwf FSR0L
    
    movlb 2
    clrf 0x70; clear LED counter
    
    byteStart2:
    ;first bit (bit 7) starts here
    bsf THEPIN2 ;Turn on
    nop
    btfss INDF0, 7
    bcf THEPIN2; turn off if this is a 0
    nop
    nop
    btfsc INDF0, 7; turn off if this is a 1
    bcf THEPIN2
    nop
    nop
    
    ;bit 6
    bsf THEPIN2 ;Turn on
    nop
    btfss INDF0, 6
    bcf THEPIN2; turn off if this is a 0
    nop
    nop
    btfsc INDF0, 6; turn off if this is a 1
    bcf THEPIN2
    nop
    nop
    
    ;bit 5
    bsf THEPIN2 ;Turn on
    nop
    btfss INDF0, 5
    bcf THEPIN2; turn off if this is a 0
    nop
    nop
    btfsc INDF0, 5; turn off if this is a 1
    bcf THEPIN2
    nop
    nop
    
    ;bit 4
    bsf THEPIN2 ;Turn on
    nop
    btfss INDF0, 4
    bcf THEPIN2; turn off if this is a 0
    nop
    nop
    btfsc INDF0, 4; turn off if this is a 1
    bcf THEPIN2
    nop
    nop
    
    ;bit 3
    bsf THEPIN2 ;Turn on
    nop
    btfss INDF0, 3
    bcf THEPIN2; turn off if this is a 0
    nop
    nop
    btfsc INDF0, 3; turn off if this is a 1
    bcf THEPIN2
    nop
    nop
    
    ;bit 2
    bsf THEPIN2 ;Turn on
    nop
    btfss INDF0, 2
    bcf THEPIN2; turn off if this is a 0
    nop
    nop
    btfsc INDF0, 2; turn off if this is a 1
    bcf THEPIN2
    nop
    nop
    
    ;bit 1
    bsf THEPIN2 ;Turn on
    nop
    btfss INDF0, 1
    bcf THEPIN2; turn off if this is a 0
    nop
    nop
    btfsc INDF0, 1; turn off if this is a 1
    bcf THEPIN2
    nop
    nop
    
    ;bit 0
    bsf THEPIN2 ;Turn on
    nop
    btfss INDF0, 0
    bcf THEPIN2; turn off if this is a 0
    decfsz FSR0L
    goto lastBCF2
    goto exit2
    lastBCF2:
    bcf THEPIN2
    goto byteStart2
    
    exit2:
    bcf THEPIN2
    
    ;reenable interrupts
    movlb 0
    bsf 0x0B, 7
    
    movlw 6
    movwf FSR0L
    outerwaitloop2:
	movlw 0xff
	waitloop2:
	    decfsz WREG
	    goto waitloop2
	decfsz FSR0L
	goto outerwaitloop2
    return