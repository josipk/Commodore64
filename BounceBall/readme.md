BOUNCE BALL (asm)

*=$1000
xv = $fb
yv = $fc
xb = $fd
yb = $fe

;init x and y values
lda #$d9
sta xv
lda #$e8
sta yv

;two's complement to normal  
loop lda xv
bpl *+3
and #$7f
eor #$7f
sta xb

;two's complement to normal
lda yv
bpl *+3
and #$7f
eor #$7f
sta yb

jsr ball

; increments x and y
inc xv
inc yv

; x max value detection
lda xv
cmp #$28
bne *+6
lda #$d9
sta xv

; y max value detection
lda yv
cmp #$19
bne *+6
lda #$e8
sta yv

; detects stop/brk pressed to exit
jsr $ffe1
bne loop
done rts

; handle ball routine
ball ldy xb
ldx yb
lda $d9,x 
and #$0f 
sta $03
lda $ecf0,x 
sta $02

; poke ball
lda #81
sta ($02),y

; raster wait command
lda #250
cmp $d012
bne *-3

; poke space (ball disappear)
ldy xb
lda #32
sta ($02),y
rts
