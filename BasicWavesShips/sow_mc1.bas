10 v=53248:pokev+21,1:poke 2040,200:fort=12800to12800+63:ready:poket,y:next
20 poke v+29, 0: rem width*2
30 poke v+23, 0: rem height*2
31 poke v+37,2: rem multicolor 1
32 poke v+38,1: rem multicolor 2
33 poke v+39,9: rem sprite main color
34 poke v+28, 7: rem multicolor

40 fori=49152to49152+72:readz:pokei,z:next:sys49152

50 y=rnd(-ti) 

60 y=int(rnd(1)*120)+80:x=90:xp=1:c=0
65 pokev,x:pokev+1,y:pokev+16,xp

70 foru=3to.step.
80 pokev,x:x=x-1
90 ifx=0thenifxp=1thenxp=0:x=254:pokev,x:pokev+16,xp
100 ifx<=1thenifxp=0thengoto60
105 next

500 rem this is sprite data
501 data 0,0,0,2,0,0,3,128,0,1,192,0,1,240,0,1,252,0
502 data 1,255,0,1,255,192,1,255,240,1,255,252,1,85,86
503 data 1,0,0,1,0,0,170,0,10,42,128,42,42,170,170,10,170,170
504 data 10,170,168,2,170,168,0,170,160,0,0,0,0

600 rem machine code to generate waves
601 data 120,169,33,141,24,3,169,192,141,25,3,169,199,141,4
602 data 221,169,30,141,5,221,169,131,141,13,221,169,1,141,14,221
603 data 88,96,72,138,72,152,72,160,0,185,60,192,32,210,255,200
604 data 192,13,208,245,173,13,221,104,168,104,170,104,64,239,210,198
605 data 195,196,197,247,197,196,195,198,210,239

