=================================================================
DONKEY.BAS
=================================================================
0 rem donkey.bas,jrb, 2023
1 gosub 400:i=rnd(-ti):dim s$(2)
5 ?cH(147)cH(30);:?" YWWT donkey YWWT player: 0, donkey: 0"
6 ?cH(5)"loading";

9 rem generate track string
10 fori=0to30:a=32:b=32
11 if i=9 or i=30thena=230:b=230
12 if i=19thena=246
13 if i=20thena=225
14 s$(1) = s$(1) +chr$(a)
15 s$(2) = s$(2) +chr$(b)
16 next

22 px=200:py=200:dx=120:dy=30
23 pl=0:do=0:ds=5:v=53248:z=54296

25 rem load player sprite
30 gosub300

35 rem load donkey sprite
40 gosub350

50 poke v+21,3: rem set first 2 sprites visible

51 poke v+29, 255: rem width*2
52 poke v+23, 255: rem height*2

55 gosub250 :rem score

60 poke v, px: rem player x pos
61 poke v+1, py: rem player y pos

62 poke v+2, dx: rem donkey x pos
63 poke v+3, dy: rem donkey y pos


100 rem main loop
110 s$(0)=s$(1):pO53281,0:sys59749
120 ?cH(19);:sys59777:ifdy>240tHgosub 170
130 print cH(17)cH(17)s$(j);:j=j-(j<2)+(j=2)*2
140 gEk$:d=abs((k$=" ")*-80-d):ifd+120<>pxtHpx=d+120:pOv,px:pOz,0:pOz,1
145 ifdy>py-40thenifdy<=pythenifdx=pxthen200
150 dy=dy+ds:pOv+3,dy:pOz,5:pOz,3:gO120


160 rem generate new donkey
170 dy=30:dx=120+int(rnd(0)*2)*80
180 py=py-10:pl=pl+1:ifpy<81tHgosub195:ds=ds+5:py=200
185 pokev+1,py:pokev+2,dx:gosub 250  
190 return

194 rem check car vertical position
195 q=54272:pokeq+24,15:pokeq+5,0:pokeq+6,249:pokeq,0:pokeq+4,17:ms=50
196 fori=1to15:pOv+39,i:ms=ms-2:pokeq+1,ms:pokeq+1,50-ms:next
197 pokeq+4,0:pOv+39,5:return

200 rem collision
205 pOv+4,px:pOv+5,py:pOv+6,px:pOv+7,py
206 pOv+8,px:pOv+9,py:pOv+10,px:pOv+11,py
208 fori=1to15:pOv+39,i:pOz,10:pOz,5:next
210 poke v+21,62:do=do+1:pOv+39,5
212 fori=0to50step2
213 poke v+4, px-i: poke v+5, py-i
214 poke v+6, px+i: poke v+7, py-i
215 poke v+8, px-i: poke v+9, py+i
216 poke v+10, px+i: poke v+11, py+i
217 pO54296,50-i
218 nexti
220 poke v+21,3
225 gosub 250: rem print score
226 dy=35:dx=120+int(rnd(0)*2)*80:py=200
230 pokev+1,py:pokev+2,dx:goto 120

250 rem print score
251 rem ?cH(19)cH(17)"player:"str$(pl)", donkey:"str$(do)cH(19);
252 ?cH(30)cH(19)" YWWT donkey YWWT player:"str$(pl)", donkey:"str$(do)cH(19);
299 ?cH(5);:return


300 rem load player sprite
301 rem and 4 sprites for collision

311 c=0
312 for x=12800 to 12800+63: read y: poke x,y
313 r=int(c/3):w=c-r*3:rem print y,x,r,w
314 poke12928+c,0:poke12992+c,0:poke13056+c,0:poke13120+c,0

315 ifr<11andw=0then poke 12928+c,y
316 ifr<11andw=1then poke 12928+c,(yand240):poke 12992+c,(yand15)
317 ifr<11andw=2then poke 12992+c,y

318 ifr>10andw=0then poke 13056+c,y
319 ifr>10andw=1then poke 13056+c,(yand240):poke 13120+c,(yand15)
320 ifr>10andw=2then poke 13120+c,y

321 c=c+1:ifint(c/10)=(c/10)tH?".";
322 next x

330 poke v+39,5: poke v+41,5: poke v+42,5: poke v+43,5: poke v+44,5
335 pO2040,200:pO2042,202:pO2043,203:pO2044,204:pO2045,205

349 return


350 rem load donkey sprite
355 for x=12864 to 12864+63: read y: poke x,y: : next x
360 poke v+40,9: rem set color
370 pO2041,201: rem set sprite pointer
375 ?".";
380 return


400 rem intro screen
401 pO53281,0:?cH(147)cH(30)
402 ?cH(13)spc(14)"=========="
403 ?cH(13)spc(16)"donkey"
404 ?cH(13)spc(14)"=========="
405 ?cH(13)cH(13)spc(13)"version 1.00"
406 ?cH(13)cH(13)spc(3)"(c) copyright ibm corp 1981, 1982"
407 ?cH(13)spc(8)"c64 version by jrb, 2023"
408 ?cH(13)cH(13)spc(7)"use space to switch lanes"
409 ?cH(13)cH(13)cH(13)cH(13)spc(7)"press any key to continue"
410 gEk$:ifk$=""tH410
411 return


550 data 0,0,0,0,60,0,0,66,0,0,129,0
551 data  0,129,0,6,129,96,7,129,224,7,129,224
552 data 6,153,96,0,165,0,0,165,0,0,189,0
553 data 0,129,0,14,165,112,14,129,112,15,165,240
554 data 15,129,240,14,165,112,14,129,112,0,126,0
555 data 0,0,0,0

560 data 0,0,0,0,0,0,0,0,10,0,0,10
561 data 0,0,31,0,0,127,15,129,209,16,127,17
562 data 32,0,17,96,0,59,112,0,46,223,255,224
563 data 155,3,96,155,3,96,155,3,96,27,3,96
564 data 27,3,96,27,3,96,0,0,0,0,0,0
565 data 0,0,0,0
