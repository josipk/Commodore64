1 rem mandelbrot-set
10 print chr$(147)
50 p=0

100 for py=0 to 24
110 for px=0 to 39

120 xz = px*3.5/40-2.5
130 yz = py*2/25-1

140 x = 0
150 y = 0

160 for i=15 to 0 step -1
170 if x*x+y*y > 4 then goto 215
180 xt = x*x - y*y + xz
190 y = 2*x*y + yz
200 x = xt
210 next i

215 i = i+1
220 poke 1024+p,160
230 poke 55296+p,i

235 p=p+1
240 next px
260 next py

280 goto 280
