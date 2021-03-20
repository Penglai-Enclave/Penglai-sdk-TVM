h01384
s 00008/00004/00013
d D 1.3 97/06/15 14:36:44 lm 4 3
c *** empty log message ***
cC
cK24725
cSAlpha2.11
e
s 00001/00001/00016
d D 1.2 97/06/14 21:41:44 lm 3 2
c oops.
cK19980
e
s 00017/00000/00000
d D 1.1 97/06/14 21:27:11 lm 2 1
c Initial revision
cK19981
e
s 00000/00000/00000
d D 1.0 97/06/14 21:27:10 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK05121
cPsrc/msleep.c
cRd239bb576a096245
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
#include "bench.h"

int
main(int ac, char **av)
{
I 4
#if	defined(sgi) || defined(sun) || defined(linux)
	usleep(atoi(av[1]) * 1000);
	return (0);
#else
E 4
	fd_set	set;
	int	fd;
	struct	timeval tv;

	tv.tv_sec = 0;
	tv.tv_usec = atoi(av[1]) * 1000;
	FD_ZERO(&set);
D 3
	fd = open("/dev/tty", 1);
E 3
I 3
D 4
	fd = open("/dev/tty", 0);
E 3
	if (fd == -1) { sleep(1); return; }
	FD_SET(fd, &set);
	select(5, &set, 0, 0, &tv);
E 4
I 4
	FD_SET(0, &set);
	select(1, &set, 0, 0, &tv);
	return (0);
#endif
E 4
}
E 2
I 1
E 1
