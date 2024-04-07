5 rem read pb0 
10 poke56579,peek(56579)and254
15 w=0
20 d=ti
30 v=peek(56577)and1
40 if v=w goto 30
50 t=ti-d
60 w=v
70 if v=0 then print t
80 goto 20