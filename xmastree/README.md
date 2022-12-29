# Christams Tree in Commodore Basic v2

```
0 rem christmas tree
1 a=1:m=55296:printchr$(147)chr$(30)
2 printspc(16-a/2):fori=1toa:print "*";:next:print"":a=a+2
6 ifc=0thenifa>9thenc=c+1:a=3:goto2
7 ifc=1thenifa>15thenc=c+1:a=5:goto2
8 ifc=2thenifa>20thenc=c+1:goto10
9 goto 2
10 printchr$(149);:fori=1to2:print spc(14)"***":next
11 ?chr$(5)chr$(19)chr$(17)chr$(17);:fori=1to20:?chr$(29);:next
12 print"merry christmas";
13 fori=1to14:?chr$(157);:next
14 ?chr$(17)chr$(17)"and";
15 fori=1to2:?chr$(157);:next
16 ?chr$(17)chr$(17)"happy new year";
17 fori=1to13:?chr$(157);:next
18 ?chr$(155)chr$(17)chr$(17)"josip retro bits";
20 v=53248:pokev+21,1:poke 2040,200:fort=12800to12800+63:ready:poket,y:next
22 poke v+29, 1: rem double width? no
23 poke v+23, 1: rem double height? no
24 poke v+37,2: rem multicolor 1
25 poke v+38,9: rem multicolor 2
26 poke v+39,1: rem multicolor main
27 poke v+28,7: rem enable multicolor
29 ys = rnd(-ti)
30 ys=rnd(.)*60+150:xs=90:xp=1:zs=0:cs=0
31 pokev,xs:pokev+1,ys:pokev+16,xp
50 foru=3to.step.
51 i=i+1:x=i*40+sin(i)*2.5+15
52 if(peek(m+x)=5)thenpokem+x,2:goto 54
53 if(peek(m+x)=2)thenpokem+x,5
54 ifi>20theni=0
55 pokev,xs
56 xs=xs-1:ifxs=0thenifxp=1thenxp=0:xs=254:pokev,xs:pokev+16,xp
57 ifxs=1thenifxp=0thengoto30
80 next
100 data 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,20,0,0,18,0,0,48,0
110 data 0,32,0,1,80,0,240,83,16,63,95,20,63,255,16,143,252,0
120 data 35,14,0,10,168,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
```
