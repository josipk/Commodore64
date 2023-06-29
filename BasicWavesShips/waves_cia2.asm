/**********************************************
 Waves v1.0
 CIA 2, Timer A, NMI Interrupt
 josip.kalebic@gmail.com
 Zadar, 2022
***********************************************/
//BasicUpstart2(mainProg)
//----------------------------------------------------
// 			Main Program
//----------------------------------------------------
//sys49152
*=$c000

mainProg: {		// <- Main scope

   sei                           // disable interrupts
  
   lda #<timer1
   sta $0318 
   lda #>timer1
   sta $0319 

   //#$1ac7	-> fine tuned to match the speed that we get in basin one-liner code!
   lda #$c7
   sta $dd04  //Low Byte
   lda #$1a   
   sta $dd05  //High Byze

   lda #$83   // set NMI timer ready
   sta $dd0d
   lda #1      // Start NMI A timer
   sta $dd0e   

   cli                       // re-enable interrupts
   rts                       // return to caller                       
			
}


timer1:

    pha
    txa
    pha
    tya
    pha


    ldy #0
innerloop:
    lda wave,y
    jsr $FFD2
    iny
    cpy #13
    bne innerloop 
	
	lda $dd0d   // look what timer it was

    pla
    tay  
    pla
    tax 
    pla     

rti             // Return from interrupt

//wave chars
wave: .byte 239,210,198,195,196,197,247,197,196,195,198,210,239
