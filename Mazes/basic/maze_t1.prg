&�� ------------------------------ :�� MAZE IN BASIC \�� RECURSIVE BACKTRACKER ALGO. y� JOSIP RETRO BITS, 2023 �� ------------------------------ �� DP(999):� POS DIRECTIONS �$� SP(999):� STACK POS �.SC � 0: � STACK COUNTER 	BPNDR �0: � PREVIOUS DIRECTION I	C� AD$(15): � AVAILABLE DIRECTIONS, LOOKUP TABLE �	DAD$(0)�"0":AD$(1)�"1":AD$(2)�"2":AD$(3)�"21":AD$(4)�"4" �	EAD$(5)�"41":AD$(6)�"42":AD$(7)�"421":AD$(8)�"8":AD$(9)�"81" �	FAD$(10)�"82":AD$(11)�"821":AD$(12)�"84":AD$(13)�"841"  
GAD$(14)�"842":AD$(15)�"8421" +
L� MAIN S
Q� 53280,13:� 53281,5:��(151)�(147); m
VY��(�TI):X�0:Y�0:SC�0 �
`P�Y�40�X: SP(SC) � P: � 1024�P,174 �
j� 2000 �
~� THE END �
��A$:�A$�"" � 1160:� WAIT �
�� �
�� MAIN LOOP �
�� INPUT PARAMS: SC �� SC�0 � 1150: � THE END! "�P�SP(SC) ;�Y��(P�40):X�P�(Y�40) k�(DP(P) � 15) � � 2200: � THIS IS DEAD END! �� (SC�2)���(SC�2) � NDR�PNDR:DP(P)�15:� 2100 �ZDR � 15�DP(P) �DR$�AD$(ZDR):A��(DR$):B��(1)�A�1 �NDR � �(�(DR$,B,1)) 4�(NDR�1) � �(Y�0) � DP(P) � DP(P) � 1:� 2050 66�(NDR�1) � Y�Y�1:A�4 g>�(NDR�2) � �(X�0) � DP(P) � DP(P) � 2:� 2050 �@�(NDR�2) � X�X�1:A�8 �H�(NDR�4) � �(Y�24) � DP(P) � DP(P) � 4:� 2050 �J�(NDR�4) � Y�Y�1:A�1 �R�(NDR�8) � �(X�38) � DP(P) � DP(P) � 8:� 2050 T�(NDR�8) � X�X�1:A�2 Y\P2�Y�40�X: SC�SC�1: SP(SC)�P2: DP(P2) � DP(P2) � A: PNDR � NDR xf� 1024�P,160:� 1024�P2,160 �p�(P2�79)� DP(P2�80) � DP(P2�80) � 4 �u�(P2�80�1000)� DP(P2�80) � DP(P2�80) � 1 �z�(P2�1)� DP(P2�2) � DP(P2�2) � 8 �(P2�2�1000)� DP(P2�2) � DP(P2�2) � 2 '�� 2020 Y�� DEAD END, POP FROM STACK, DECREMENT COUNTER n�� 55296�SP(SC),0 ��SP(SC)�0:SC�SC�1 ��� 2020   