&�� ------------------------------ :�� MAZE IN BASIC \�� RECURSIVE BACKTRACKER ALGO. y� JOSIP RETRO BITS, 2023 �� ------------------------------ �� DP(1000):� POS DIRECTIONS �$� SP(1000):� STACK POS �BSC � 0: � STACK COUNTER  	L� MAIN 	VX��(�TI):SC�0 0	[X��(�(.)�40):Y��(�(.)�24) W	`P�Y�40�X: SP(SC) � P: � 1024�P,166 b	j� 2000 m	t� 1130 {	~� THE END �	��A$:�A$�"" � 1160:� WAIT �	�� �	�� MAIN LOOP �	�� INPUT PARAMS: SC �	�� SC�0 � 1150: � THE END! �	�P�SP(SC) 	
�Y��(P�40):X�P�(Y�40) 9
�(DP(P) � 15) � � 2200: � THIS IS DEAD END! O
NDR � 2��(�(1)�4) s
�((DP(P) � NDR) � NDR) � � 2060 �
 � WE HAVE A DIRECTION �
4�(NDR�1) � �(Y�0) � DP(P) � DP(P) � 1:� 2020 �
5�(NDR�1) � Y�Y�1:A�4:� 2140 >�(NDR�2) � �(X�0) � DP(P) � DP(P) � 2:� 2020 /?�(NDR�2) � X�X�1:A�8:� 2140 aH�(NDR�4) � �(Y�24) � DP(P) � DP(P) � 4:� 2020 �I�(NDR�4) � Y�Y�1:A�1:� 2140 �R�(NDR�8) � �(X�39) � DP(P) � DP(P) � 8:� 2020 �S�(NDR�8) � X�X�1:A�2 \P2�Y�40�X: SC�SC�1: SP(SC)�P2: DP(P2) � DP(P2) � A "f� 1024�P,161:� 1024�P2,166 Jp�(P2�39)� DP(P2�40) � DP(P2�40) � 4 su�(P2�960)� DP(P2�40) � DP(P2�40) � 1 �z�(P2�0)� DP(P2�1) � DP(P2�1) � 8 ��(P2�999)� DP(P2�1) � DP(P2�1) � 2 ��� 2020 ��� DEAD END, POP FROM STACK, DECREMENT COUNTER �� 55296�SP(SC),15 '�SP(SC)�0:SC�SC�1 2�� 2020   