0 goS10:?cH(147)cH(28)sP10)"merry x-mass 2023"cH(5):sys59749
1 ?cH(19)cH(13)cH(13)sPrN(.)*38)"*";:?cH(19):sys59777:pokev+6,xs
4 xs=xs-1:ifxs=0thenifxp=8thenxp=0:xs=254:pokev+6,xs:pokev+16,xp
5 ifxs=1thenifxp=0thenxs=100:xp=8:pokev+6,xs:pokev+16,xp:pokev+7,rnd(.)*100+80
6 pokev+21,30+a:a=a+.1+(a>1.4)*a:gO1

10 print chr$(147): poke53280,0: poke 53281,0
20 v=53248:xs=90:xp=8:u=rnd(-ti)
30 poke v+37,5: rem multicolor 1
40 poke v+38,1: rem multicolor 2
50 poke v+21,255 : rem set all 8 sprites visible
60 for x=12800 to 12800+252: read y: poke x,y: next x
70 poke v+39,2: poke v+40,9: poke v+41,9: poke v+42,2: poke v+43,9
80 poke 2040,203: poke 2041,200: poke 2042,200: poke 2043,201: poke 2044,202
90 poke v, 140: rem x pos
100 poke v+1, 210: rem y pos
110 poke v+2, 60: rem x pos
111 poke v+3, 210: rem y pos
112 poke v+4, 220: rem x pos
113 poke v+5, 210: rem y pos
114 poke v+6, 200: rem x pos
115 poke v+7, 100: rem y pos
116 poke v+8, 140: rem x pos
117 poke v+9, 210: rem y pos

120 pokev+16,xp
125 poke v+28, 31: rem multicolor
130 poke v+29, 31: rem width*2
135 poke v+23, 31: rem height*2
140 return

200 rem christmas tree
210 data 0,0,0,0,0,0,0,48,0,0,28,0,0,215,0
220 data 0,85,0,0,20,0,3,85,192,1,85,64,0,20,0
230 data 3,85,192,13,85,112,5,85,80,0,85,0,13,85,112
240 data 53,85,92,21,85,84,0,40,0,0,40,0,0,40,0,0,40,0,0

245 rem santa
250 data 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,40,0,0,35,0,0,48,0
260 data 0,32,0,2,160,0,80,161,32,21,165,40,21,85,32,197,84
270 data 0,49,7,0,15,252,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

275 rem house
280 data 0,0,0,0,0,0,0,0,0,0,0,0,0,0,192,0,0,128,0,0,128
290 data 0,60,128,0,235,128,3,170,128,14,170,176,58,170
300 data 172,42,0,168,2,65,128,2,65,128,50,0,140,210,0
310 data 135,86,40,149,86,40,149,18,40,132,34,170,136,0

315 rem house lights
320 data 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
330 data 40,0,0,130,0,2,0,128,8,0,32,32,0,8,0,0,0,0,0,0,0
340 data 0,0,0,0,0,32,0,8,0,0,0,0,0,0,0,0,0
