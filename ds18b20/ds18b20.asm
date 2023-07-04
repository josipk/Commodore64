//----------------------------------------------------
//  DS18B20 temperature sensor 
//  Platform: C64
//  Data GPIO: PB1
//  Kick Assembler
//  @JosipRetroBits, 2023
//----------------------------------------------------
//sys 4096
.var PRB = $dd01
.var DDRB = $dd03
.var CLEAR =  $E544
.var OBA = $af
.var VAL = $a0
.var BVAL = $a2
.var HBYT  = $b0
.var CRC  = $40
.var MIX  = $41
.var CHROUT = $FFD2

.var divisor = $58     ////$59 used for hi-byte
.var dividend = $fb	  //$fc used for hi-byte
.var remainder = $fd	  //$fe used for hi-byte
.var result = dividend //save memory by reusing divident to store the result

.var num1 = $42
.var num1Hi = $43
.var num2 = $44
.var num3 = $45 //$46 for high byte

*=$1000
//sys 4096

mainProg: {             // <- Main scope

	jsr CLEAR

	lda #$1
	sta OBA

	/*
	//all port B pins as output
	lda #$ff
	sta DDRB
	*/
	 	
	lda DDRB
	ora #$02 //0000 0010
	sta DDRB
	

mloop1:	

	jsr sendResetSignal
	
	jsr delay600 

	jsr selectDevice

	jsr delay600 

	//Convert T.
	lda #$44
	jsr sendByte

	jsr delay1000 
	jsr delay1000 

	jsr sendResetSignal
	jsr delay600 
	jsr selectDevice
	jsr delay600
	jsr readScratchpad 

	jmp mloop1
rts
}

readScratchpad: {

	//---Read Scratchpad 
	lda #$be
	jsr sendByte

	jsr delay600 

	lda #$0
readb3:
	pha
	tay
	jsr readByte
	pla
	adc #$01
	cmp #$09
	bcc readb3

	jsr calcCRCmain

	lda HBYT+8
	cmp CRC
	bne rscrpadend

	//--new line--------------
	lda #$0d
	jsr CHROUT

	//Two's complement
	lda HBYT+1
	and #$80
	cmp #$80
	bne notnegative

	//It's negative number
	sec
	lda #$00
	sbc HBYT
    sta HBYT

	lda #$00
	sbc HBYT+1
	sta HBYT+1


	//--print minus --------------
	lda #$2d
	jsr CHROUT

notnegative:

	lda #$10
	sta divisor

	lda #$00
	sta divisor+1

	lda HBYT
	sta dividend

	lda HBYT+1
	sta dividend+1	

	jsr divideP

	lda remainder
	sta num1

	lda #$0a
	sta num2

	jsr multiplyP

	//num3

	//devide with 16 (shitf right by 4)
	ldx #$04
devideBy16:
	lsr num3+1   //hi
	ror num3     //lo	
	dex
	bne devideBy16


	//dividend is the whole part of a floating point number
	//num3 is decimal part of of a floating point number

	lda dividend+1 //high byte
	ldx dividend //low byte
	jsr $BDCD //print to screen	

	//--print dot --------------
	lda #$2e
	jsr CHROUT

	lda num3+1 //high byte
	ldx num3 //low byte
	jsr $BDCD //print to screen	

	rts
	
rscrpadend:

	rts
}

selectDevice: {

	/*
Read Address [0x33]: Only used when there is a single device on the bus. This command reads the 64-bit
device address of the only device present on the bus.
	*/

	//---Select device
	lda #$33
	jsr sendByte

	jsr delay600 

	lda #$0
readb4:
	pha
	tay
	jsr readByte
	pla
	adc #$01
	cmp #$08
	bcc readb4

	rts
}

//read one byte//
readByte: {

	lda #$0
	sta VAL

	jsr readBit	

	jsr readBit	

	jsr readBit	

	jsr readBit	

	jsr readBit	

	jsr readBit	

	jsr readBit	

	jsr readBit								

	sta HBYT, y

	rts
}


sendByte: {

	ldy #$0

	loopsB1:

		bit OBA
		bne loopsB1HighBit

		pha
		jsr sendLowBit
		pla
		jmp loopsB1BitDone

	loopsB1HighBit:	
		
		pha
		jsr sendHighBit
		pla

	loopsB1BitDone:	
		iny
		ror
		cpy #$8 
		bne loopsB1
	
rts
}



// the whole process should take 120us
sendHighBit: {

	//pull pin low
	lda PRB
	and prbval_inv
	sta PRB

	//pull pin high
	lda PRB
	ora prbval
	sta PRB

	jsr delay52  //52 cycles
	jsr delay52  //52 cycles

	rts //6
}


// the whole process should take 120us
sendLowBit: {

	//pull pin low
	lda PRB
	and prbval_inv
	sta PRB

	jsr delay52  //6 cycles

	//pull pin high
	lda PRB
	ora prbval
	sta PRB

	jsr delay52 //6 cycles 

	rts //6
}

// the whole process should take 120us
readBit: {

	//pull pin low
	lda PRB
	and prbval_inv
	sta PRB

	//pull pin high
	lda PRB
	ora prbval
	sta PRB

	nop;
	nop;
	nop;

	lda PRB
	and prbval
	cmp prbval
	bne r_have_zero

r_have_one:
	jsr delay52 //6 cycles 
	lda VAL
	lsr
	ora #$80 
	sta VAL	
	rts

r_have_zero:
	jsr delay52 //6 cycles 
	lda VAL
	lsr
	ora #$0  
	sta VAL	
	rts //6
}

// the whole process should take 960us
sendResetSignal: {

	//pull pin low
	lda PRB
	and prbval_inv
	sta PRB

	jsr delay600  

	//pull pin high
	lda PRB
	ora prbval
	sta PRB

	jsr delay10  

	//wait for response
	ldy #0

srsr2:
	lda PRB
	and prbval
	cmp prbval
	bne we_have_zero
	jsr delay10  //6 cycles

	iny
	cpy #$20
	bcc srsr2

	rts

we_have_zero:
	//we have a device on the bus!!!!!

	rts //6
}




delay10: {

	nop //2
	nop //2
	rts //6
	//total: 10 cycles 

}

delay60: {

	ldx #0 //2
dy3kloop:	
	nop //2
	nop //2
 	inx //2
    cpx #5 //2
    bne dy3kloop //3

	rts //6

}


delay52: {

	ldx #0 //2
dy3kloop:	
	nop //2
 	inx //2
    cpx #4 //2
    bne dy3kloop //3

	rts //6
	//total: 22 cycles 

}


delay96: {

	ldx #0 //2
dy1kloop:	
	nop //2
	nop //2
 	inx //2
    cpx #8 //2
    bne dy1kloop //3

	rts //6
	//total: 22 cycles 

}

delay600: {

	ldx #0 //2
dy2kloop:	
	nop //2
	nop //2
 	inx //2
    cpx #54 //2
    bne dy2kloop //3

	rts //6
	//total: 22 cycles 

}

delay22: {

	nop //2
	nop //2
	nop //2
	nop //2
	nop //2
	nop //2
	nop //2
	nop //2
	rts //6
	//total: 22 cycles 

}

delay1000: {

	ldx #0 //2
dytkloop:	
	nop //2
	nop //2
 	inx //2
    cpx #255 //2
    bne dytkloop //3

	rts //6

}


calcCRCmain: {

	//----------------------------------------

	lda #$0
	sta CRC

	lda HBYT
	sta VAL
	jsr calcCRC

	lda HBYT+1
	sta VAL
	jsr calcCRC

	lda HBYT+2
	sta VAL
	jsr calcCRC

	lda HBYT+3
	sta VAL
	jsr calcCRC

	lda HBYT+4
	sta VAL
	jsr calcCRC

	lda HBYT+5
	sta VAL
	jsr calcCRC

	lda HBYT+6
	sta VAL
	jsr calcCRC

	lda HBYT+7
	sta VAL
	jsr calcCRC			
	//----------------

	rts
}

/*
uint8_t mix = (crc ^ inbyte) & 0x01;
			crc >>= 1;
			if (mix) { crc ^= 0x8C; }
			inbyte >>= 1;
*/

calcCRC: {

	ldy #0

crcloop:
	lda CRC
	eor VAL
	and #$01
	sta MIX

	//shift CRC right
	lda CRC
	lsr
	sta CRC

	lda MIX
	cmp #$1
	bne doNotCrCEor

	lda CRC
	eor #$8c
	sta CRC	

doNotCrCEor:

	//shift VAL right
	lda VAL
	lsr
	sta VAL


	iny
	cpy #$8
	bcc crcloop

	rts
} 


divideP: {

	divide:
		lda #0	        //preset remainder to 0
		sta remainder
		sta remainder+1
		ldx #16	        //repeat for each bit: ...

	divloop:
		asl dividend	//dividend lb & hb*2, msb -> Carry
		rol dividend+1	
		rol remainder	//remainder lb & hb * 2 + msb from carry
		rol remainder+1
		lda remainder
		sec
		sbc divisor	//substract divisor to see if it fits in
		tay	        //lb result -> Y, for we may need it later
		lda remainder+1
		sbc divisor+1
		bcc skip	//if carry=0 then divisor didn't fit in yet

		sta remainder+1	//else save substraction result as new remainder,
		sty remainder
		
		inc result	//and INCrement result cause divisor fit in 1 times

	skip:
		dex
		bne divloop	
		rts
}





//------------------------
// 8bit * 8bit = 16bit multiply
// By White Flame
// Multiplies "num1" by "num2" and stores result in .A (low byte, also in .X) and .Y (high byte)
// uses extra zp var "num1Hi"

// .X and .Y get clobbered.  Change the tax/txa and tay/tya to stack or zp storage if this is an issue.
//  idea to store 16-bit accumulator in .X and .Y instead of zp from bogax

// In this version, both inputs must be unsigned
// Remove the noted line to turn this into a 16bit(either) * 8bit(unsigned) = 16bit multiply.

multiplyP: {

	 lda #$00
	 tay
	 sty num1Hi  // remove this line for 16*8=16bit multiply
	 beq mEnterLoop

	mDoAdd:
	 clc
	 adc num1
	 tax

	 tya
	 adc num1Hi
	 tay
	 txa

	mloop:
	 asl num1
	 rol num1Hi

	mEnterLoop:  // accumulating multiply entry point (enter with .A=lo, .Y=hi)
	 lsr num2
	 bcs mDoAdd
	 bne mloop


	 stx num3  //low byte
	 sty num3+1 //hight byte

	 rts

 }	

prbval: .byte $2
prbval_inv: .byte $fd
