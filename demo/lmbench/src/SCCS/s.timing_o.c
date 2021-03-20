h61898
s 00002/00003/00008
d D 1.4 98/06/26 17:35:21 staelin 5 4
c update to reflect new type (uint64) returned by l_overhead()
cC
cHbitmover
cK10787
cSAlpha2.11
cZ-07:00
e
s 00001/00000/00010
d D 1.3 98/03/06 12:02:08 lm 4 3
c Carl's.
cK10126
cZ-08:00
e
s 00003/00001/00007
d D 1.2 97/06/15 22:38:58 lm 3 2
c lint
cK08534
e
s 00008/00000/00000
d D 1.1 97/06/12 21:33:41 lm 2 1
c Initial revision
cK06848
e
s 00000/00000/00000
d D 1.0 97/06/12 21:33:40 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK28440
cPsrc/timing_o.c
cRed38e6e135adb2ce
cV4
cX0x21
cZ-07:00
e
u
U
f e 0
f x 0x21
t
T
I 2
#include <stdio.h>
D 5

D 3
double t_overhead();
E 3
I 3
double t_overhead(void);
E 5
I 5
#include "bench.h"
E 5
E 3

I 3
int
E 3
main()
{
I 4
	putenv("LOOP_O=0.0");
E 4
D 5
	printf("%.3f\n", t_overhead());
E 5
I 5
	printf("%lu\n", (unsigned long)t_overhead());
E 5
I 3
	return (0);
E 3
}
E 2
I 1
E 1
