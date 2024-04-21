10 o=12*40+20:v=1024+o:w=55296+o:printchr$(147)
15 fori=61to84
20 h=int(i/10):g=i-h*10
25 poke2186,(h+48):poke2187,(g+48)
30 fory=-12to12:forx=-20to20
35 gosub88
40 pokev+x+y*40,160:pokew+x+y*40,abs(a)and255
45 next:next:forj=0to3000:next:n=0:c=0:a=0:next
50 end

60 rem algorithms
61 n=n+1:a=((y*y)+(x*x))+sqr(n*n):return
62 c=xory:a=(y*y)or(x*x)+not(cor12):return
63 c=xory:a=sqr(y*y)-sqr(x*x)+not(c):return
64 a=(y*y)or(x*x)ornot(x*y):return
65 c=xory:a=(y*y)+(x*x)+not(cor41):return
66 a=(x*y)or(x+y)ornot(x-y):return
67 c=x+ y:a=sin(y*y)+sin(x*x)orc:return
68 a=sin(x*y)+cos(x+y):return
69 a=sin(x*y)+cos(x+y)+not(xory):return
70 a=sin(x*y)+cos(x+y)*not(xandy):return
71 a=cos(x*y)andcos(x+y)+not(xandy):return
72 a=(x*x-y*y)/((x+y)or1):return
73 n=n+.5:a=not(sqr(abs(x*n+y*n))*.3):return
74 a=cos(xory)andsqr(abs(xory))*not(yandx):return
75 a=sqr(x*x+y*y):return
76 a=sqr(x*x+y*y)andnot(x*y):return
77 a=sqr(x*x+y*y)/(not(xandy)or1):return
78 a=sqr(x*x+y*y-x*y):return
79 a=sqr(x*x+y*y)+sin(x*y):return
80 a=sqr(x*x+y*y)orsqr(abs(x+y)):return
81 n=n+.5:a=(sqr(x*x+y*y)-sqr(n*n)):return
82 n=n+.5:a=not(sqr(x*x+y*y)-sqr(n*5)):return
83 n=n+.1:a=not(sqr(abs(x*n+y*n))*.3):return
84 n=n+.1:a=tan(sqr(abs(x*n+y*n))or(n*.003)):return
