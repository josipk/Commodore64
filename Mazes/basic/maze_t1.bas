1000 rem ------------------------------
1010 rem maze in basic
1020 rem recursive backtracker algo.
1030 rem josip retro bits, 2023
1040 rem ------------------------------
1050 dim dp(999):rem pos directions
1060 dim sp(999):rem stack pos
1070 sc = 0: rem stack counter
1090 pndr =0: rem previous direction

1091 dim ad$(15): rem available directions, lookup table
1092 ad$(0)="0":ad$(1)="1":ad$(2)="2":ad$(3)="21":ad$(4)="4"
1093 ad$(5)="41":ad$(6)="42":ad$(7)="421":ad$(8)="8":ad$(9)="81"
1094 ad$(10)="82":ad$(11)="821":ad$(12)="84":ad$(13)="841"
1095 ad$(14)="842":ad$(15)="8421"


1100 rem main
1105 poke 53280,13:poke 53281,5:printchr$(151)chr$(147);
1110 y=rnd(-ti):x=0:y=0:sc=0
1120 p=y*40+x: sp(sc) = p: poke 1024+p,174
1130 goto 2000
1150 rem the end
1160 geta$:ifa$="" then 1160:rem wait
1999 end

2000 rem main loop
2010 rem input params: sc
2020 if sc<0 then 1150: rem the end!
2030 p=sp(sc)
2040 y=int(p/40):x=p-(y*40)
2050 if(dp(p) = 15) then goto 2200: rem this is dead end!

2070 if (sc/2)<>int(sc/2) then ndr=pndr:dp(p)=15:goto 2100

2075 zdr = 15-dp(p)
2077 dr$=ad$(zdr):a=len(dr$):b=rnd(1)*a+1
2078 ndr = val(mid$(dr$,b,1))

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

