'�� ------------------------------- M�� MAZE DEMO, JOSIPRETROBITS, 2023 s�� ------------------------------- �� DP(1000):� POS DIRECTIONS �$� SP(1000):� STACK POS �.SC � 0: � STACK COUNTER �7� AVAILABLE DIRECTIONS, LOOKUP TABLE 	8� AD$(15)  >	:AD$(0)�"0":AD$(1)�"1":AD$(2)�"2":AD$(3)�"21":AD$(4)�"4" ~	;AD$(5)�"41":AD$(6)�"42":AD$(7)�"421":AD$(8)�"8":AD$(9)�"81" �	<AD$(10)�"82":AD$(11)�"821":AD$(12)�"84":AD$(13)�"841" �	=AD$(14)�"842":AD$(15)�"8421" �	L� MAIN 
Q� 53280,0:� 53281,0:��(147); -
V� X=INT(RND(1)*40):Y=INT(RND(1)*24) B
[� X=20:Y=10:SC=0 i
`P�Y�40�X: SP(SC) � P: � 1024�P,174 t
j� 2000 �
~� THE END �
��A$:�A$�"" � 1160:� WAIT �
�� �
�� LOOP SINGLE STEP �
�� INPUT PARAMS: SC �
�� SC�0 � 1150: � THE END! �
�P�SP(SC) �Y��(P�40):X�P�(Y�40) :� DS=DP(P): REM GET DIRECTIONS j�(DP(P) � 15) � � 2200: � THIS IS DEAD END! }NDR � 15�DP(P) �DR$�AD$(NDR):A��(DR$):B��(1)�A�1 �RDR � �(�(DR$,B,1))  *� MARK THIS DIRECTION, CREATE NEW POSITION, MARK ALL NEIGHBOURS!  34�(RDR � 1) � �(Y�0) � DP(P) � DP(P) � 1:� 2020 U5�(RDR � 1) � Y�Y�1:A�4:� 2132 �>�(RDR � 2) � �(X�0) � DP(P) � DP(P) � 2:� 2020 �?�(RDR � 2) � X�X�1:A�8:� 2132 �H�(RDR � 4) � �(Y�24) � DP(P) � DP(P) � 4:� 2020  I�(RDR � 4) � Y�Y�1:A�1:� 2132 4R�(RDR � 8) � �(X�39) � DP(P) � DP(P) � 8:� 2020 OS�(RDR � 8) � X�X�1:A�2 {TCDH�(RDR�1�RDR�4)��66�(RDR�2�RDR�8)��67 �UB1�((RHR�2 � RDR�4) � (RHR�1 � RDR�8))��85 �VB2 �((RHR�8 � RDR�4) � (RHR�1 � RDR�2))��73 	WB3�((RHR�2 � RDR�1) � (RHR�4 � RDR�8))��74 8XB4�((RHR�8 � RDR�1) � (RHR�4 � RDR�2))��75 gYB5�((RHR�1 � RDR�1) � (RHR�4 � RDR�4))��66 �ZB6�((RHR�2 � RDR�2) � (RHR�8 � RDR�8))��67 �[CHP�B1�B2�B3�B4�B5�B6 �\P2�Y�40�X: SC�SC�1: SP(SC)�P2: DP(P2) � DP(P2) � A f� 1024�P2,CDH: RHR�RDR:� Z�0 � � 1024�P,CHP ?p�(P2�39)� DP(P2�40) � DP(P2�40) � 4 hu�(P2�960)� DP(P2�40) � DP(P2�40) � 1 �z�(P2�0)� DP(P2�1) � DP(P2�1) � 8 ��(P2�999)� DP(P2�1) � DP(P2�1) � 2 ��Z�0:� 2020 ��� DEAD END, POP FROM STACK, DECREMENT COUNTER �� 55296�SP(SC),15 $�SP(SC)�0:SC�SC�1:Z�1 /�� 2020   