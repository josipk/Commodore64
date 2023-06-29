0 goS10:?cH(147)cH(5):sys59749
1 ?cH(19)cH(13)cH(13)sPrN(.)*38)"*";
2 ?cH(19):sys59777:gO1
10 print chr$(147): poke53280,0: poke 53281,0
20 v=53248
30 poke v+37,5: rem multicolor 1
40 poke v+38,1: rem multicolor 2
50 poke v+21,255 : rem set all 8 sprites visible
60 for x=12800 to 12800+63: read y: poke x,y: next x: rem sprite generation
70 poke v+39,9: poke v+40,9: poke v+41,9
80 poke 2040,200: poke 2041,200: poke 2042,200
90 poke v, 140: rem x pos
100 poke v+1, 210: rem y pos
122 poke v+2, 60: rem x pos
123 poke v+3, 210: rem y pos
124 poke v+4, 220: rem x pos
125 poke v+5, 210: rem y pos
110 poke v+28, 7: rem multicolor
120 poke v+29, 7: rem width*2
130 poke v+23, 7: rem height*2
140 return
200 rem christmas tree
210 data  0,0,0,0,0,0,0,48,0,0,28,0,0,215,0
220 data  0,85,0,0,20,0,3,85,192,1,85,64,0,20,0
230 data  3,85,192,13,85,112,5,85,80,0,85,0,13,85,112
240 data  53,85,92,21,85,84,0,40,0,0,40,0,0,40,0,0,40,0,0
