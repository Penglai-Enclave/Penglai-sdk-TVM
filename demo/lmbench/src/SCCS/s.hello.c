h52889
s 00002/00005/00006
d D 1.3 97/06/12 21:30:06 lm 4 3
c new bench.h macros.
cC
cK05957
cSAlpha2.11
cZ-07:00
e
s 00008/00001/00003
d D 1.2 96/11/08 19:58:34 lm 3 2
c gcc -Wall cleanup.
cK10914
e
s 00004/00000/00000
d D 1.1 94/11/18 00:49:48 lm 2 1
c Initial revision
cK02998
e
s 00000/00000/00000
d D 1.0 94/11/18 00:49:47 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK57098
cPsrc/hello.c
cRf8859fefaf295a3c
cV4
cX0x21
cZ-08:00
e
u
U
f e 0
f x 0x21
t
lmbench src
T
I 3
D 4
#include	<string.h>
#define	str	"Hello world.\n"
E 4
I 4
#include "bench.h"
E 4

int
E 3
I 2
main()
{
D 3
	printf("Hello world.\n");
E 3
I 3
D 4
	int	write(int, char *, int);

	write(1, str, strlen(str));
E 4
I 4
	write(1, "Hello world\n", 12);
E 4
	return (0);
E 3
}
E 2
I 1
E 1
