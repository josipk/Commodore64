
---
5 rem grab and save kernal data
10 rem kernal start: $e000 - 57344 
20 rem kernal end: $ffff - 65535
30 rem pointer start: 43 - low,44 - high 
40 rem pointer end: 45 - low,46 - high

50 poke 44,57344/256:poke 43,57344-256*peek(44)
60 poke 46,65535/256:poke 45,65535-256*peek(46)
70 save "kernal",8,1
---




Full version that restore all BASIC pointer vectors to the original values
---
10 s(0)=57344:s(1)=65535:n$(0)="kernal"
20 fori=43to46:a(i-43)=peek(i):next
30 poke 44,s(0)/256:poke 43,s(0)-256*peek(44)
40 poke 46,s(1)/256:poke 45,s(1)-256*peek(46)
50 saven$(0),8,1
60 poke43,a(0):poke44,a(1):poke45,a(2):poke46,a(3)
---
