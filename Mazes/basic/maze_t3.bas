1000 rem ------------------------------
1010 rem maze in basic
1020 rem recursive backtracker algo.
1030 rem josip retro bits, 2023
1040 rem ------------------------------
1050 dim dp(1000):rem pos directions
1060 dim sp(1000):rem stack pos
1065 dim gd(40,25):rem grid x,y
1070 sc = 0: rem stack counter
1080 chd = 0: rem change direction
1090 pndr =0: rem previous direction
1095 dim ad(15,4)

1100 rem main

1105 poke 53280,13:poke 53281,5:printchr$(151)chr$(147);

1110 forx=0to39step2:fory=0to24step2:gd(x,y)=1:next:next

1200 fori=0to15:form=0to4:readk:ad(i,m)=k:next:next

1220 y=rnd(-ti):x=0:y=0:sc=0
1230 p=y*40+x: sp(sc) = p: poke 1024+p,174
1240 goto 2000
1250 rem the end
1260 geta$:ifa$="" then 1260:rem wait
1300 end

2000 rem main loop
2010 rem input params: sc
2020 if sc<0 then 1250: rem the end!
2030 p=sp(sc)
2040 y=int(p/40):x=p-(y*40)
2050 if(dp(p) = 15) then goto 2200: rem this is dead end!

2070 if gd(x,y)=0 then ndr=pndr:dp(p)=15:goto 2100
2075 rem ndr = 2^int(rnd(1)*4)

2076 zdr = 15-dp(p)
2077 a=ad(zdr,0):b=rnd(1)*a+1
2078 ndr = ad(zdr,b)

2080 if((dp(p) and ndr) = ndr) then goto 2075

2100 if(ndr=1) then if(y=0) then dp(p) = dp(p) or 1:goto 2050
2102 if(ndr=1) then y=y-1:a=4

2110 if(ndr=2) then if(x=0) then dp(p) = dp(p) or 2:goto 2050
2112 if(ndr=2) then x=x-1:a=8

2120 if(ndr=4) then if(y=24) then dp(p) = dp(p) or 4:goto 2050
2122 if(ndr=4) then y=y+1:a=1

2130 if(ndr=8) then if(x=38) then dp(p) = dp(p) or 8:goto 2050
2132 if(ndr=8) then x=x+1:a=2

2140 p2=y*40+x: sc=sc+1: sp(sc)=p2: dp(p2) = dp(p2) or a: pndr = ndr

2150 poke 1024+p,160:poke 1024+p2,160

2160 if(p2>79)then dp(p2-80) = dp(p2-80) or 4
2165 if(p2+80<1000)then dp(p2+80) = dp(p2+80) or 1
2170 if(p2>1)then dp(p2-2) = dp(p2-2) or 8
2175 if(p2+2<1000)then dp(p2+2) = dp(p2+2) or 2

2180 goto 2020

2200 rem dead end, pop from stack, decrement counter
2205 poke 55296+sp(sc),0
2210 sp(sc)=0:sc=sc-1
2220 goto 2020

3000 data 0,0,0,0,0,1,1,0,0,0,1,2,0,0,0,2,2,1,0,0
3010 data 1,4,0,0,0,2,4,1,0,0,2,4,2,0,0,3,4,2,1,0
3020 data 1,8,0,0,0,2,8,1,0,0,2,8,2,0,0,3,8,2,1,0
3030 data 2,8,4,0,0,3,8,4,1,0,3,8,4,2,0,4,8,4,2,1
