10 *= $1000
20 ivlo=$0318
25 ivhi=$0319

30 sei

35 lda #<intrtn
40 sta ivlo

50 lda #>intrtn
55 sta ivhi

60  lda #%10010000
65  sta $dd0d
70  cli

95 rts 

100 inthand inc $d020
110 bit $dd0d
120 rti
