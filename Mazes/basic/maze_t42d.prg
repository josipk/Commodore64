&�� ------------------------------ E�� CREATING A MAZE IN BASIC j�� ------------------------------ �� INITIALISATION DEFINITIONS �� ------------------------------ �� DP(40,25):� POS DIRECTIONS (TWO-DIMENSIONAL) �$� SP(1000):� STACK POS 	BSC � 0: � STACK COUNTER %	L� MAIN 2	QX��(�TI) E	VX�20:Y�10:SC�0 l	`P�Y�40�X: SP(SC) � P: � 1024�P,166 w	j� 2000 �	t� 1130 �	~� THE END �	��A$:�A$�"" � 1160:� WAIT �	�� �	�� BLOCK DIRECTION CHOOSE �	�� INPUT PARAMS: SC 
�� SC�0 � 1150: � THE END! 
�P�SP(SC) +
�Y��(P�40):X�P�(Y�40) ]
�(DP(X,Y) � 15) � � 2200: � THIS IS DEAD END! s
NDR � 2��(�(1)�4) �
�((DP(X,Y) � NDR) � NDR) � � 2060 �
 � WE HAVE A FREE DIRECTION �
4�(NDR�1) � �(Y�0) � DP(X,Y) � DP(X,Y) � 1:� 2020 5�(NDR�1) � Y�Y�1:A�4 ;>�(NDR�2) � �(X�0) � DP(X,Y) � DP(X,Y) � 2:� 2020 T?�(NDR�2) � X�X�1:A�8 �H�(NDR�4) � �(Y�24) � DP(X,Y) � DP(X,Y) � 4:� 2020 �I�(NDR�4) � Y�Y�1:A�1 �R�(NDR�8) � �(X�39) � DP(X,Y) � DP(X,Y) � 8:� 2020 �S�(NDR�8) � X�X�1:A�2 +\P2�Y�40�X: SC�SC�1: SP(SC)�P2: DP(X,Y) � DP(X,Y) � A Jf� 1024�P,161:� 1024�P2,166 pp�(Y�0)� DP(X,Y�1) � DP(X,Y�1) � 4 �u�(Y�24)� DP(X,Y�1) � DP(X,Y�1) � 1 �z�(X�0)� DP(X�1,Y) � DP(X�1,Y) � 8 ��(X�39)� DP(X�1,Y) � DP(X�1,Y) � 2 ��� 2020 !�� DEAD END, POP FROM STACK, DECREMENT COUNTER 7�� 55296�SP(SC),15 L�SP(SC)�0:SC�SC�1 W�� 2020   