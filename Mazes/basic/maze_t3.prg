&�� ------------------------------ E�� CREATING A MAZE IN BASIC j�� ------------------------------ �� INITIALISATION DEFINITIONS �� ------------------------------ �� DP(1000):� POS DIRECTIONS �$� SP(1000):� STACK POS 	)� GD(40,25):� GRID X,Y "	.SC � 0: � STACK COUNTER B	8CHD � 0: � CHANGE DIRECTION d	BPNDR �0: � PREVIOUS DIRECTION s	G� AD(15,4) ~	L� MAIN �	Q� 53280,13:� 53281,5:��(151)�(147); �	V�X�0�39�2:�Y�0�24�2:GD(X,Y)�1:�:� �	��I�0�15:�M�0�4:�K:AD(I,M)�K:�:� 

�Y��(�TI):X�0:Y�0:SC�0 1
�P�Y�40�X: SP(SC) � P: � 1024�P,174 <
�� 2000 J
�� THE END g
��A$:�A$�"" � 1260:� WAIT m
� }
�� MAIN LOOP �
�� INPUT PARAMS: SC �
�� SC�0 � 1250: � THE END! �
�P�SP(SC) �
�Y��(P�40):X�P�(Y�40) �(DP(P) � 15) � � 2200: � THIS IS DEAD END! 3� GD(X,Y)�0 � NDR�PNDR:DP(P)�15:� 2100 O� NDR = 2^INT(RND(1)*4) bZDR � 15�DP(P) }A�AD(ZDR,0):B��(1)�A�1 �NDR � AD(ZDR,B) � �((DP(P) � NDR) � NDR) � � 2075 �4�(NDR�1) � �(Y�0) � DP(P) � DP(P) � 1:� 2050 �6�(NDR�1) � Y�Y�1:A�4 0>�(NDR�2) � �(X�0) � DP(P) � DP(P) � 2:� 2050 I@�(NDR�2) � X�X�1:A�8 {H�(NDR�4) � �(Y�24) � DP(P) � DP(P) � 4:� 2050 �J�(NDR�4) � Y�Y�1:A�1 �R�(NDR�8) � �(X�38) � DP(P) � DP(P) � 8:� 2050 �T�(NDR�8) � X�X�1:A�2 "\P2�Y�40�X: SC�SC�1: SP(SC)�P2: DP(P2) � DP(P2) � A: PNDR � NDR Af� 1024�P,160:� 1024�P2,160 ip�(P2�79)� DP(P2�80) � DP(P2�80) � 4 �u�(P2�80�1000)� DP(P2�80) � DP(P2�80) � 1 �z�(P2�1)� DP(P2�2) � DP(P2�2) � 8 ��(P2�2�1000)� DP(P2�2) � DP(P2�2) � 2 ��� 2020 "�� DEAD END, POP FROM STACK, DECREMENT COUNTER 7�� 55296�SP(SC),0 L�SP(SC)�0:SC�SC�1 W�� 2020 ��� 0,0,0,0,0,1,1,0,0,0,1,2,0,0,0,2,2,1,0,0 ��� 1,4,0,0,0,2,4,1,0,0,2,4,2,0,0,3,4,2,1,0 ��� 1,8,0,0,0,2,8,1,0,0,2,8,2,0,0,3,8,2,1,0 �� 2,8,4,0,0,3,8,4,1,0,3,8,4,2,0,4,8,4,2,1   