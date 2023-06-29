10-liner games in Commodore Basic

-------------------------------------

Game 1.1-v2, no TIMER
```
0 ?chr$(147):s=1024:p=40:o=1:u=1024+(p*12):z=0:y=55296+(p*12)
1 pO(u+z),62:pO(y+z),13:g=0:h=24:dt=1:t=0:n=0:m=0:gO5
2 o=o+2:if(h-g)>5tHif(int(o/2)/2)-int(int(o/2)/2)<>0tHh=h-1:g=g+1 
3 t=((t>=h)*(-h+1))+((t<=g)*(-g-1))+((t>g)*(t<h)*t):ifo>40gO9 
4 t=t+dt:n=s+(p*t)+o:d=pE(n):dt=dt*(1+((t<=g)*2)+((t>=h)*2))
5 poken,42:pokem,32:m=n:ifd=62tHpO(n),86:pOy+z,2:gO9
6 getk$:ifk$<>""tHc=pE(u+z+1):ifc=32tHpOu+z+1,62:pOy+z+1,13:z=z+1:ifz>ogO2
7 ifk$<>""tHifc<>32tHpOu+z+1,86:pOy+z+1,2:gO9
8 gO4
9 ?"score:"z+1",game over";:ifo>40tH?cH(20)cH(20)cH(20)cH(20)"end "
```
-------------------------------------

Game 1.1-v2, with TIMER
```
0 ?chr$(147):s=1024:p=40:o=1:u=s+(p*12):z=0:y=55296+(p*12)
1 pOu+z,62:pOy+z,13:g=0:h=24:dt=1:t=0:n=0:m=0:w=0:gO4
2 o=o+2:if(h-g)>5tHif(int(o/2)/2)-int(int(o/2)/2)<>0tHh=h-1:g=g+1 
3 t=((t>=h)*(-h+1))+((t<=g)*(-g-1))+((t>g)*(t<h)*t):ifo>40gO9 
4 t=t+dt:n=s+(p*t)+o:d=pE(n):dt=dt*(1+((t<=g)*2)+((t>=h)*2))
5 poken,42:pokem,32:m=n:ifd=62tHpOn,86:pOy+z,2:gO9
6 getk$:ifk$<>""tHc=pE(u+z+1):ifc=32tHpOu+z+1,62:pOy+z+1,13:z=z+1:ifz>ogO2
7 ifk$<>""tHifc<>32tHpOu+z+1,86:pOy+z+1,2:gO9
8 w=w+.07:pOs+19+w,121:ifw<20tHgO4
9 ?"score:"z+1",game over";:ifo>40tH?cH(20)cH(20)cH(20)cH(20)"end "
```
-------------------------------------

Game 1.2-v1, no TIMER
```
0 ?chr$(147):s=1024:p=40:o=1:u=1024+(p*12):z=0:pOu+z,62:y=55296+(p*12)
1 pOy+z,13:dimw(2):w(0)=32:w(1)=42:g=0:h=24:dt=1:t=0:gO4
2 o=o+2:if(int(o/2)/2)-int(int(o/2)/2)<>0tHh=h-1:g=g+1
3 t=((t>=h)*(-h+1))+((t<=g)*(-g-1))+((t>g)*(t<h)*t):ifo>40gO9 
4 t=t+dt:n=s+(p*t)+o:d=pE(n):dt=dt*(1+((t<=g)*2)+((t>=h)*2))
5 poken,w(int(rnd(.)*2)):ifd=62tHpOn,86:pOy+z,2:gO9
6 getk$:ifk$<>""tHc=pE(u+z+1):ifc=32tHpOu+z+1,62:pOy+z+1,13:z=z+1:ifz>ogO2
7 ifk$<>""tHifc<>32tHpO(u+z+1),86:pOy+z+1,2:gO9
8 gO4
9 ?"score:"z+1",game over";:ifo>40tH?cH(20)cH(20)cH(20)cH(20)"end "
```
-------------------------------------

Game 1.2-v2, with TIMER
```
0 ?chr$(147):s=1024:p=40:o=1:u=1024+(p*12):z=0:pOu+z,62:y=55296+(p*12)
1 pOy+z,13:dimw(2):w(0)=32:w(1)=42:g=0:h=24:dt=1:t=0:w=0:gO5
2 o=o+2:if(int(o/2)/2)-int(int(o/2)/2)<>0tHh=h-1:g=g+1
3 t=((t>=h)*(-h+1))+((t<=g)*(-g-1))+((t>g)*(t<h)*t):ifo>40gO9 
4 t=t+dt:n=s+(p*t)+o:d=pE(n):dt=dt*(1+((t<=g)*2)+((t>=h)*2))
5 poken,w(int(rnd(.)*2)):ifd=62tHpOn,86:pOy+z,2:gO9
6 getk$:ifk$<>""tHc=pE(u+z+1):ifc=32tHpOu+z+1,62:pOy+z+1,13:z=z+1:ifz>ogO2
7 ifk$<>""tHifc<>32tHpO(u+z+1),86:pOy+z+1,2:gO9
8 w=w+.02:pOs+19+w,121:ifw<20tHgO4
9 ?"score:"z+1",game over";:ifo>40tH?cH(20)cH(20)cH(20)cH(20)"end "
```
----------------------------------------

Game 2-v1, Crap Game
```
0 ?chr$(147):s=1024:p=40:o=1
1 ifo=40goto9 
2 z=0:pokes+(z*p)+o,35
3 np=s+((z+1)*p)+(p*int(rnd(.)*(24-z)))+o
4 pokenp,32+int(rnd(.)*2)
5 getk$:ifk$<>""thenz=z+1
6 c=peek(s+(z*p)+o):ifc<>32thenpokes+(z*p)+o,35:ifz=24theno=o+1:goto1
7 ifc=32thenz=z-1
8 goto 3
9 ?"game over" 
```
---------------------------------------------------

Game 2-v2, Crap Game
```
0 ?chr$(147):s=1024:p=40:o=1
1 ifo=40goto9 
2 z=0:pokes+(z*p)+o,35
3 np=s+((z+1)*p)+(p*int(rnd(.)*(24-z)))+o
4 pokenp,32+int(rnd(.)*2)
5 getk$:ifk$<>""thenz=z+1
6 c=pE(s+(z*p)+o):ifc<>32tHpOs+(z*p)+o,35:ifz=24tHo=o+1:gO1
7 ifc=32tHpOs+(z*p)+o,86:gO9
8 goto 3
9 ?"game over" 
```
---------------------------------------------------
