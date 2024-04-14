
10 *= $1000

100 lda $dd03 
110 and #254  ! set pin b0 as input
120 sta $dd03

125 dado=$fb
126 delay=$fc ! delay+1 ($fd)
127 pos=$fe
128 ltt=$ff
130 ivlo=$0318
135 ivhi=$0319

140 sei

150 lda #<inthand
155 sta ivlo

160 lda #>inthand
165 sta ivhi

170 lda #%10010000
175 sta $dd0d
180 cli

190 lda #00
192 sta pos
193 sta delay
194 lda #$80
195 sta delay+1

200 mloop lda delay+1
210 cmp #$80
220 bcs nospc

230 dec delay
235 lda delay
240 cmp #00
245 bne nospc

250 inc delay+1
255 lda delay+1
260 cmp #$80
265 bne nospc

270 lda ltt
275 jsr $e716 ! output char to screen
276 jsr nextline

277 lda #00
278 sta pos

280 nospc lda $dc01
285 cmp #$ef ! check if spc pressed
290 bne mloop

291 sei
292 lda #%00010000  ! stop nmi interrupt
293 sta $dd0d
294 cli 

295 rts 

300 !interupt handler
310 inthand pha
320 txa
325 pha
330 tya
335 pha

340 lda #00
345 sta delay
347 sta delay+1

350 lda #$71
355 sta dado

360 ldx #$00 ! set x counter zero
365 ldy #$00 ! set y counter zero

370 rploop inx
380 cpx #00
385 bne noyc

390 iny
395 cpy #$12 !this define dot duration
400 bne noyc

410 lda #$63
420 sta dado

440 noyc lda $dd01
445 and #01
450 cmp #00  ! check if pin down
455 bne rploop

460 jsr locate

463 lda dado
465 jsr $e716 ! output char to screen

470 lda #00
475 sta delay
480 sta delay+1

490 bit $dd0d

500 pla
505 tay  
510 pla
515 tax 
520 pla 
550 rti !return


600 locate pha
605 txa
610 pha
615 tya
620 pha

630 ldx pos
640 lcloop lda codes,x
650 cmp dado
660 beq lcdone 

670 txa
675 clc 
680 adc #$04
690 tax
700 jmp lcloop 
  
710 lcdone lda letters,x
720 sta ltt
730 inx 
740 stx pos

750 pla
760 tay  
770 pla
780 tax 
790 pla 
800 rts !return

850 nextline lda #00
855 sta $d3
860 jsr $e87c
865 rts

900 codes byt $71,$63,$71,$71
905 byt $71,$63,$63,$71
910 byt $71,$63,$63,$63
915 byt $71,$71,$63,$71
920 byt $71,$71,$71,$63
925 byt $71,$71,$71,$71
930 byt $63,$71,$63,$71
935 byt $63,$71,$63,$63
940 byt $63,$71,$71,$63
945 byt $63,$71,$71,$71
950 byt $63,$63,$71,$71
955 byt $63,$63,$71,$63
960 byt $63,$63,$63,$63

970 letters txt "earleawpeawjeiufeisveish"
980 txt "tnkctnkytndxtndbtmgztmgqtmo",$00
