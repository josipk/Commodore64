Optimized code!

'''
10 *=$1000
15 xv = $fb
17 yv = $fc

20 lda #$d9
22 sta xv
24 lda #$e8
26 sta yv

30 loop jsr ball

65 inc xv
66 inc yv

70 lda xv
71 cmp #$28
72 bne *+6
73 lda #$d9
74 sta xv

80 lda yv
81 cmp #$19
82 bne *+6
83 lda #$e8
84 sta yv

95 jsr $ffe1
96 bne loop
100 done rts

200 ball nop 
210 lda xv
220 bpl *+6
230 and #$7f
240 eor #$7f
250 tay

260 lda yv
270 bpl *+6
280 and #$7f
290 eor #$7f
300 tax

350 lda $d9,x 
360 and #$0f 
370 sta $03
380 lda $ecf0,x 
390 sta $02

400 lda #81
410 sta ($02),y

420 lda #250
430 cmp $d012
440 bne *-3

460 lda #32
470 sta ($02),y

500 rts
'''
