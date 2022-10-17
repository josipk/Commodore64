1 print chr$(147)
2 vm=1024:cm=55296:pc=7
3 qt=83


8 rem generate enviroment
9 a=rnd(-ti)
10 for i=1 to 240
20 a=int(rnd(1)*999):b=int(rnd(.)*20+1):pokevm+a,234+b
30 next

40 rem generate player
50 p=int(rnd(.)*999):poke1024+p,87:poke55296+p,pc:pd=p

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
170 goto 100


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

















