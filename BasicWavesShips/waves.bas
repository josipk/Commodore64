10 v=53248:pokev+21,1:poke 2040,200
11 fort=12800to12800+63:ready:poket,y:next

18 poke v+29, 0: rem double width?
19 poke v+23, 0: rem double height?

20 poke v+37,5: rem multicolor 1
21 poke v+38,1: rem multicolor 2
22 poke v+39,9: rem sprite main color
23 poke v+28, 7: rem multicolor

30 w$="{CBM-P}RFCDE{CBM-Y}EDCFR{CBM-P}"

40 y=rnd(-ti) 
   
50 y=int(rnd(1)*120)+80:x=90:xp=1
60 pokev,x:pokev+1,y:pokev+16,xp

70 foru=3to.step.:printw$;:pokev,x
80 printw$;:x=x-1:ifx=0thenifxp=1thenxp=0:x=254:pokev,x:pokev+16,xp
90 printw$;:ifx=1thenifxp=0thengoto50
100 printw$;:next

500 rem this is sprite data
501 data 0,0,0,2,0,0,3,128,0,1,192,0,1,240,0,1,252,0
502 data 1,255,0,1,255,192,1,255,240,1,255,252,1,85,86
503 data 1,0,0,1,0,0,170,0,10,42,128,42,42,170,170,10,170,170
504 data 10,170,168,2,170,168,0,170,160,0,0,0,0

