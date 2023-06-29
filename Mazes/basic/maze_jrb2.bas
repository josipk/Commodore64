1000 rem ------------------------------
1010 rem maze in basic
1020 rem recursive backtracker algo.
1030 rem josip retro bits, 2023
1040 rem ------------------------------
1050 dim dp(1000):rem pos directions
1060 dim sp(1000):rem stack pos
1070 dim ad(15,4)

1090 sc = 0: rem stack counter

1100 printchr$(5)chr$(147);:rem main

1105 fori=0to15:form=0to4:readk:ad(i,m)=k:next:next
1110 x=rnd(-ti):x=20:y=10:sc=0
1120 p=y*40+x: sp(sc) = p: poke 1024+p,166
1130 goto 2000
1140 goto 1130
1150 rem the end
1160 geta$:ifa$="" then 1160:rem wait
1200 end


2000 rem main loop
2010 rem input params: sc
2020 if sc<0 then 1150: rem the end!
2030 p=sp(sc)
2040 y=int(p/40):x=p-(y*40)
2050 if(dp(p) = 15) then goto 2200: rem this is dead end!

2060 zdr = 15-dp(p)
2065 a=ad(zdr,0):b=rnd(1)*a+1
2070 ndr = ad(zdr,b)

2080 rem we have a direction

2100 if(ndr=1) then if(y=0) then dp(p) = dp(p) or 1:goto 2020
2101 if(ndr=1) then y=y-1:a=4:goto 2140

2110 if(ndr=2) then if(x=0) then dp(p) = dp(p) or 2:goto 2020
2111 if(ndr=2) then x=x-1:a=8:goto 2140

2120 if(ndr=4) then if(y=24) then dp(p) = dp(p) or 4:goto 2020
2121 if(ndr=4) then y=y+1:a=1:goto 2140

2130 if(ndr=8) then if(x=39) then dp(p) = dp(p) or 8:goto 2020
2131 if(ndr=8) then x=x+1:a=2

2140 p2=y*40+x: sc=sc+1: sp(sc)=p2: dp(p2) = dp(p2) or a
2150 poke 1024+p,161:poke 1024+p2,166

2160 if(p2>39)then dp(p2-40) = dp(p2-40) or 4
2165 if(p2<960)then dp(p2+40) = dp(p2+40) or 1
2170 if(p2>0)then dp(p2-1) = dp(p2-1) or 8
2175 if(p2<999)then dp(p2+1) = dp(p2+1) or 2

2180 goto 2020

2200 rem dead end, pop from stack, decrement counter
2205 poke 55296+sp(sc),5
2210 sp(sc)=0:sc=sc-1
2220 goto 2020

3000 data 0,0,0,0,0,1,1,0,0,0,1,2,0,0,0,2,2,1,0,0
3010 data 1,4,0,0,0,2,4,1,0,0,2,4,2,0,0,3,4,2,1,0
3020 data 1,8,0,0,0,2,8,1,0,0,2,8,2,0,0,3,8,2,1,0
3030 data 2,8,4,0,0,

13- 3,8,4,1,0,
14- 3,8,4,2,0,
15- 4,8,4,2,1

0
15-0 = 15
