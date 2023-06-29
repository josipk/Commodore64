1 print"{clr}{white}"
5 input "enter current and new sd2iec number";a, b
10 open 15,a,15,"u0>"+chr$(b):close15
20 print "sd2iec new device number is: ";b
30 input "permanent change? (y/n)";c$
40 if c$<>"y"thengoto70
50 open 15,b,15,"xw":close15
60 print "permanent change done!"
70 input "reset sd2iec? (y/n)";c$
80 if c$<>"y"thenend
90 open 15,b,15,"u"+chr$(202):close15
100 print "reset done!"
