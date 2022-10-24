// File preloader for C64
// josip@kalebic@gmail.com
// code: KickAssembler
// filename is defined at the end of the file

.var load_address = $801  //just an example
.var p1 = $ae

*=$1000   //sys4096

mainProg: {             // <- a main scope

        lda #$25     
        jsr $FFD2    //(print it)

        lda #fname_end-fname
        ldx #<fname
        ldy #>fname
        jsr $ffbd     //call setnam

        lda #$02      //file number 2
        ldx $ba       //last used device number
        bne skip
        ldx #$08      //default to device 8
skip:   ldy #$02      //secondary address 2
        jsr $ffba     //call setlfs

        jsr $ffc0     //call open
        bcs error    //if carry set, the file could not be opened

        //check drive error channel here to test for
        //file not found error etc.

        ldx #$02      //filenumber 2
        jsr $ffc6     //call chkin (file 2 now used as input)

        lda #<load_address
        sta p1
        lda #>load_address
        sta p1+1

        ldy #$00
        
        //read first two bytes from file and do nothing with them!
        jsr $ffb7     //call readst (read status byte)
        jsr $ffcf     //call chrin (get a byte from file)

        jsr $ffb7     //call readst (read status byte)
        jsr $ffcf     //call chrin (get a byte from file)
		//-------------------------------------------------

loop:   jsr $ffb7     //call readst (read status byte)
        bne eof       //either eof or read error
        jsr $ffcf     //call chrin (get a byte from file)
        sta (p1),y   //write byte to memory
        inc p1
        bne skip2
        inc p1+1
        
        //lda #$21     
        //jsr $FFD2    //(print it)

skip2:  jmp loop     //next byte

eof:
        and #$40      //end of file?
        beq readerror
close:
        lda #$02      //filenumber 2
        jsr $ffc3     //call close

        lda #$25     
        jsr $FFD2    //(print it)

        jsr $ffcc     //call clrchn
        rts
error:
        lda #$21     
        jsr $FFD2    //(print it)
        jmp close    //even if open failed, the file has to be closed
readerror:
        lda #$21     
        jsr $FFD2    //(print it)
        jmp close

}

fname: .text "DEMO2.PRG"
fname_end:
