1 ?chr$(147):rem c= x-mass
5 poke53280,0:poke53281,0:?chr$(5):v=1024+80:w=55296+80:f=(40*9)+16
6 dim p(120):dim h(120):c=0
10 for y=-8 to 8:b=abs(y):for x=-8 to 8:a=abs(x)
20 z=((a*a+b*b)>16aN(a*a+b*b)<56aNnO(x>0aNb<4)aNx<5)
30 ifz<0tHp(c)=f-(y*40)+x:h(c)=6:c=c+1
35 ?chr$(19)"loading "int(c/119*100)cH(157)"%"
40 next:next

50 for y=1 to 3:for x=1 to 5
55 ifnot(y>(6-x))<0tH p(c)=f-((y-4)*40)+(x+4):h(c)=2:c=c+1
57 ?chr$(19)"loading "int(c/119*100)cH(157)"%"
60 next:next

70 for y=1 to 3:for x=1 to 5
75 ifnot((x-2)>y)<0tH p(c)=f-(y*40)+(x+4):h(c)=6:c=c+1
77 ?chr$(19)"loading "int(c/119*100)cH(157)"%"
80 next:next

90?cH(147)cH(28)spc(12)"merry x-mass"
91?spc(15)"2023"

100 fori=0to118
110 x=p(i)-int(p(i)/40)*40+40
120 forj=xtop(i)step40
130 pokev+j,42:pokew+j,h(i):pokev+j-40,32
140 next:gosub600
150 next

160 forx=1to17:y=0
170 y=y+40:pOv+8+y+x,42:pokew+8+y+x,1
180 ifpeek(v+8+y+x+40)=32tHpokew+8+y+x,0:gO170
190 gosub600:next

199 forj=0to700:next
200 gosub500

220 fori=0to59
230 pokev+p(i),42:pokew+p(i),h(i):gosub600
240 pokev+p(118-i),42:pokew+p(118-i),h(118-i):gosub600
250 next

300 dim s(16):z=55296:u=40*21+10:fori=0to15:readd:s(i)=d:next 
310 fori=0to15:poke1024+u+i,s(i):next

350 k=0:r=1:fori=0to690:a=int(rnd(.)*118):pokez+u+k,1:
360 b=peek(w+p(a)):pokew+p(a),1:forj=0to10:next:pokew+p(a),b
370 pokez+u+k,r:k=k+1:ifk>15thenk=0:r=r+1:ifr>15thenr=1
375 next

380 gosub500
400 end

500 fori=0to400:next:?cH(19):sys59749
510 fori=0to38:?cH(19):sys59777:nE
520 return

550 fori=0to400:next:?chr$(19):fori=1to40:?:next:return

600 pO54296,15:pO54296,5:pO54296,10:return
700 data 10,15,19,9,16,32,18,5,20,18,15,32,2,9,20,19

