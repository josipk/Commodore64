 ��$1000  JSR $E544  ) LDA #$00 7 STA $D021 D LDA #$FF R STA $D015 ` STA $D418 m
 LDA #$FF y LDX #64 � FILL DEX � STA $3000,X � BNE FILL � LDA #192 � LDX #08 � PO� DEX � STA $07F8,X � BNE PO� � MLOOP JSR $E097 	 LDA $65 	 � #$0F 	 TAX 	 PLA <	  ADC $A1 !#01, #03 E� $A2 D	! PHA T	# STA $D000,X d	( STA $D001,X r	- STX $D016 }	2 � #$0F �	7 TAX  �	< LDA $D012 �	F STA $D400,X �	Z JSR $FFE1 !SCAN � BREAK �	_ BNE MLOOP �	` LDX #$00 �	a STX $D015 �	b JSR $A483 �	c RTS   