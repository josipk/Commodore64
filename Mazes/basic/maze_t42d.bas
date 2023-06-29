1000 rem ------------------------------
1010 rem maze in basic
1020 rem recursive backtracker algo.
1030 rem josip retro bits, 2023
1040 rem ------------------------------

1050 dim dp(40,25):rem pos directions (two-dimensional)
1060 dim sp(1000):rem stack pos
1090 sc = 0: rem stack counter


1100 rem main
1105 x=rnd(-ti)
1110 x=20:y=10:sc=0
1120 p=y*40+x: sp(sc) = p: poke 1024+p,166
1130 goto 2000
1140 goto 1130
1150 rem the end
1160 geta$:ifa$="" then 1160:rem wait
1999 end


2000 rem block direction choose
2010 rem input params: sc
2020 if sc<0 then 1150: rem the end!
2030 p=sp(sc)
2040 y=int(p/40):x=p-(y*40)
2050 if(dp(x,y) = 15) then goto 2200: rem this is dead end!
2060 ndr = 2^int(rnd(1)*4)
2070 if((dp(x,y) and ndr) = ndr) then goto 2060
2080 rem we have a free direction

2100 if(ndr=1) then if(y=0) then dp(x,y) = dp(x,y) or 1:goto 2020
2101 if(ndr=1) then y=y-1:a=4

2110 if(ndr=2) then if(x=0) then dp(x,y) = dp(x,y) or 2:goto 2020
2111 if(ndr=2) then x=x-1:a=8

2120 if(ndr=4) then if(y=24) then dp(x,y) = dp(x,y) or 4:goto 2020
2121 if(ndr=4) then y=y+1:a=1

2130 if(ndr=8) then if(x=39) then dp(x,y) = dp(x,y) or 8:goto 2020
2131 if(ndr=8) then x=x+1:a=2

2140 p2=y*40+x: sc=sc+1: sp(sc)=p2: dp(x,y) = dp(x,y) or a
2150 poke 1024+p,161:poke 1024+p2,166

2160 if(y>0)then dp(x,y-1) = dp(x,y-1) or 4
2165 if(y<24)then dp(x,y+1) = dp(x,y+1) or 1
2170 if(x>0)then dp(x-1,y) = dp(x-1,y) or 8
2175 if(x<39)then dp(x+1,y) = dp(x+1,y) or 2

2180 goto 2020

2200 rem dead end, pop from stack, decrement counter
2205 poke 55296+sp(sc),15
2210 sp(sc)=0:sc=sc-1
2220 goto 2020


