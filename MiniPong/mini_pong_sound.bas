0 rem mini pong v.0.1, @jk, 2022

1 y2=53253:x2=53252:x0=53248:y0=53249:y1=53251:x1=53250
7 sbt5=53279: rem sprite bkg collision register
8 sct5=53278: rem sprite sprite collision register

9 for sprite=12800 to sprite+192:read a:poke sprite,a:next sprite

10 printchr$(147)
20 poke 53280,0:poke53281,0:poke 646,1

30 poke 53264,0
35 poke 2040,200
40 poke 2041,201
45 poke 2042,202

50 printtab(13)"{white}mini pong"
51 printtab(8)"{orange}single player with sound"
55 printtab(8)"{gray}press any key to start"

60 a$="":get a$:if a$="" then goto 60
70 printchr$(147):print "{home}mini pong"
100 print "{blue}0{white}  :  {red}0{white}"
110 print "FFFFFFF"
120 print "   {103}"
130 print "   "
140 print "   {103}"
150 print "   "
160 print "   {103}"
170 print "FFFFFFF"

180 p1=0:p2=0
181 b1=80:b2=80

182 x=40:y=62
181 poke x0,20:poke y0,b1
182 poke x1,50:poke y1,b2
183 poke x2,x:poke y2,y

320 poke 53287,1:poke 53288,1:poke 53289,8
330 poke 53269,255

340 xd=2:yd=2

400 foru=3to.step.:k=peek(203)

410 if k=9 then if b1>70 then b1=b1-5:poke y0,b1
420 if k=9 then if b2<100 then b2=b2+5:poke y1,b2
430 if k=13 then if b1<100 then b1=b1+5:poke y0,b1
440 if k=13 then if b2>70 then b2=b2-5:poke y1,b2

450 x=x+xd:y=y+yd:pokex2,x:pokey2,y

470 bt6 = peek(sbt5)
475 if bt6<>0 then if y<64 then yd=-yd:y=y+4:poke y2,y
480 if bt6<>0 then if y>100 then yd=-yd:y=y-4:poke y2,y

490 if peek(sct5)>250 then goto 600

491 if x<20 then goto 900
492 if x>75 then goto 910

500 nextu

600 poke 53278,0:xd=-xd
610 if xd<0 then x=x-4: ifx>60then xd=-xd:x=x+4:goto 630
620 if xd>0 then x=x+4: ifx<34then xd=-xd:x=x-4:goto 630

621 r=54272:for z=5 to 0 step -1
622 poke r+24,z
623 poke r,200:next z

630 poke x2,x:poke 53278,0
699 goto 400

900 p2=p2+1:goto 920
910 p1=p1+1
920 print "{home}{down}{blue}{left}";p1;"{white} : {red}";p2;"{white}"
930 print "{down}{down}{down}{down}{down}{down}{down}"
940 print "score!";
950 forz=0to180:nextz:print"...go";
960 forw=0to100:nextw
970 print "{left}{left}{left}{left}{left}{left}{left}{left}{left}{left}{left}{left}{left}{left}";"                    "
980 goto 182

1000 rem Sprite data for bat (4 lines repeated)
1010 data 0,0,0,0,0,0,0,255,0,0,255,0,0,255,0,0
1020 data 255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255
1030 data 0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0
1040 data 0,255,0,0,255,0,0,255,0,0,0,0,0,0,0,0,0
1050 data 0,0,0,0,0,0,0,255,0,0,255,0,0,255,0,0
1060 data 255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255
1070 data 0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0
1080 data 0,255,0,0,255,0,0,255,0,0,0,0,0,0,0,0,0

1100 rem Sprite data for ball
1110 data 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
1120 data 0,0,0,0,0,0,60,0,0,126,0,0,255,0,0,255
1130 data 0,0,255,0,0,255,0,0,126,0,0,60,0,0,0,0
1140 data 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

