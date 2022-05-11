Generating weird colorful patterns using a Random Numbers in Commodore Basic

1 printchr$(18)" {left}";:printmid$("{right}{left}{down}{up}",rnd(ti)*4+1,1);:poke646,rnd(.)*256:goto1

Build prg file:

petcat -w2 -o patterns.prg -- patterns.bas

petcat is part of vice package
