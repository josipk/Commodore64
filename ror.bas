[rainbow of rhombuses]

0fOa=-6to6:fOj=.to25:pO780,160:pO89,7:pO88,0:pO114,3:pO113,232:pO12,1:sY45762
1pO646,j:t=6+a:x=1-x*(x<t*2):y=abs(x-t):?sP12+t-y-a)"Z"sPy*2)cH(157)"Z":nE:nE:gO




[memory fill routine]
Memory area we want to fill is: D800 - DBE7
First calculate the difference and add 1 byte: DBE7 - D800 + 0001 = 03e8
Then add the high byte of the start address + high byte of the difference +1: d8 + 03 = db

Poke values:
POKE 88, low byte of start address (00)
POKE 89, high bytes of the start address + high byte of the difference + 1 (d9)
POKE 113, low byte of (the difference + 1) (29)
POKE 114, high byte of (the difference + 1) (00)

POKE 780,(char that we want to fill memory with)

SYS 45762

