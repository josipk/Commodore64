1 print chr$(147)
2 vm=1024:cm=55296:pc=7
3 qt=83
4 dim z(3):dim zl(3):zc=2
5 dim zx(3):dim zy(3) 



8 rem generate enviroment
9 a=rnd(-ti)
10 for i=1 to 240
20 a=int(rnd(1)*999):b=int(rnd(.)*20+1):pokevm+a,234+b
30 next

40 rem generate player
45 p=int(rnd(.)*999):poke1024+p,87:poke55296+p,pc:pd=p

50 rem generate enemy
51 fori=0to3
52 z(i)=int(rnd(.)*999):poke1024+z(i),102:poke55296+z(i),zc:zl(i)=z(i)
53 nexti

60 rem generate targets
65 for i=1 to 10
70 q=int(rnd(.)*999):qc=int(rnd(1)*13+1):poke1024+q,qt:poke55296+q,qc
75 next


100 j2=not(peek(56320))
120 if (j2 and 1) then gosub 200
130 if (j2 and 2) then gosub 300
140 if (j2 and 4) then gosub 400
150 if (j2 and 8) then gosub 500
160 if (j2 and 16)then gosub 600
170 gosub 2000: rem call enemy subrutine
180 goto 100


200 rem move up
201 p=p-40:gosub 900
299 return

300 rem move down
301 p=p+40:gosub 900
399 return

400 rem move left
401 p=p-1:gosub 900
499 return

500 rem move right
501 p=p+1:gosub 900
599 return

600 rem fire
601 pc=pc+1:pokecm+p,pc
699 return

900 rem move player
901 g=peek(vm+p)
902 rem ifg<>32thenp=pd:return
903 ifg<>32thenifg<>qtthenp=pd:return
904 ifg=qtthengosub 1000
910 pokevm+p,87:pokecm+p,pc
911 pokevm+pd,32:pokecm+pd,6
912 pd=p
999 return 


1000 rem collect target
1001 h=peek(cm+p)
1002 pc=h:pokecm+p,pc
1010 return

2000 rem enemy subrutine


2010 fori=0to3

2020 z(i)=z(i)+(zy(i)*40)+zx(i)
2022 g=peek(vm+z(i))
2023 ifg<>32thenz(i)=zl(i):gosub3000:goto2100
2024 pokevm+z(i),102:pokecm+z(i),zc
2025 pokevm+zl(i),32:pokecm+zl(i),6
2026 zl(i)=z(i)

2100 nexti
2200 return

3000 rem recalulate directions

3001 yd=int((p-z(i))/40)
3002 rem ifyd<0thenyd=yd+1

3005 zzx = z(i)-(int(z(i)/40)*40)
3006 ppx = p-(int(p/40)*40)
3007 xd=ppx-zzx

3008 rem print p,z,yd,xd

3010 if yd<0thenzy(i)=-1
3011 if yd>0thenzy(i)=1
3012 if yd=0thenzy(i)=0

3020 if xd<0thenzx(i)=-1
3021 if xd>0thenzx(i)=1
3022 if xd=0thenzx(i)=0

3999 return 













