h21512
s 00001/00000/00012
d D 1.8 98/06/29 23:49:51 lm 9 8
c stdlib.h
cC
cK13806
cSAlpha2.11
cZ-07:00
e
s 00002/00000/00010
d D 1.7 98/03/06 12:00:35 lm 8 7
c Some nifty carl hack.
cK12075
cZ-08:00
e
s 00006/00000/00004
d D 1.6 97/06/15 22:38:58 lm 7 6
c lint
cK08749
e
s 00001/00144/00003
d D 1.5 97/06/14 18:22:54 lm 6 5
c *** empty log message ***
cK03288
e
s 00142/00001/00005
d D 1.4 97/06/14 12:19:38 lm 5 4
c Carl's new version.
cK00646
e
s 00003/00005/00003
d D 1.3 97/06/13 20:24:35 lm 4 3
c move it to lib_timing
cK04828
e
s 00001/00001/00007
d D 1.2 97/06/13 09:15:19 lm 3 2
c *** empty log message ***
cK07623
e
s 00008/00000/00000
d D 1.1 97/06/12 21:33:41 lm 2 1
c Initial revision
cK07579
e
s 00000/00000/00000
d D 1.0 97/06/12 21:33:40 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK63250
cPsrc/enough.c
cR9a0843e42c129a15
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
I 7
#include <stdio.h>
I 9
#include <stdlib.h>
E 9

extern	int	get_enough(int);

int
E 7
I 5
D 6
/*
 * enough.c - length of accurate timing interval
 *
 * usage: enough
 *
 * Copyright (c) 1997 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 */
char   *id = "$Id$";

E 5
I 4
#include "bench.h"

I 5
typedef long TYPE;

static void 
use_p(TYPE ** p)
{
}

static TYPE **
enough_duration(register long N, register TYPE ** p)
{
#define	ENOUGH_DURATION_TEN(one)	one one one one one one one one one one
	while (N-- > 0) {
		ENOUGH_DURATION_TEN(p = (TYPE **) *p;);
	}
	return p;
}

static int
duration(int N)
{
	int     usecs;
	TYPE   *x = (TYPE *)&x;
	TYPE  **p = (TYPE **)&x;

	start(0);
	p = enough_duration(N, p);
	usecs = stop(0, 0);
	use_p(p);
	return usecs;
}

/*
 * find the minimum time that work "N" takes in "tries" tests
 */
static int
time_N(int tries, long N)
{
	int     i, usecs;

	usecs = duration(N);
	for (i = 1; i < tries; ++i) {
		int     tmp = duration(N);

		if (tmp < usecs)
			usecs = tmp;
	}
	return usecs;
}

/*
 * return the amount of work needed to run "enough" microseconds
 */
static int
find_N(int enough)
{
	int     i, N;

	for (N = 1;;) {
		/*
		 * XXX - prevent infinite loops? 
		 */
		int     usecs = duration(N);

		if (0.98 * enough < usecs && usecs < 1.02 * enough)
			break;
		if (usecs < 150)
			N *= 10;
		else {
			double  n = N;

			n /= usecs;
			n *= enough;
			N = n + 1;
		}
	}
	return N;
}

/*
 * We want to verify that small modifications proportionally affect the runtime
 */
#define	POINTS	4
static int
test_time(int tries, int enough)
{
	int     i, j, N = find_N(enough);
	int     n[POINTS], usecs[POINTS];
	double  rate[POINTS];

	if (N <= 0)
		return 0;

	for (i = 0; i < POINTS; ++i) {
		n[i] = (int) ((double) N * (1.0 + (double) i * 0.01));
		usecs[i] = time_N(tries, n[i]);
		rate[i] = (double) usecs[i] / n[i];
		for (j = 0; j < i; ++j) {
			if (ABS(rate[i] - rate[j]) > 0.01)
				return 0;
		}
	}
	return 1;
}

int     possibilities[] =
{
    1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000,
    10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000,
    100000, 200000, 300000, 400000, 500000
};

/*
 * We want to find the smallest timing interval that has accurate timing
 */
static int
compute_enough(int tries)
{
	int     i;

	for (i = 0; i < sizeof(possibilities) / sizeof(int); ++i) {
		if (test_time(tries, possibilities[i]))
			return possibilities[i];
	}

	return possibilities[sizeof(possibilities) / sizeof(int) - 1];
}

E 6
E 5
E 4
I 2
main()
{
I 8
	putenv("LOOP_O=0.0");
	putenv("TIMING_O=0.0");
E 8
D 4
#if	defined(sgi) || defined(linux)
D 3
	printf("50000\n");
E 3
I 3
	printf("100000\n");
E 3
#else
	printf("100000\n");
#endif
E 4
I 4
D 5
	printf("%d\n", get_enough(0));
E 5
I 5
D 6
	uint64  enough = compute_enough(9);

	printf("%lu\n", (unsigned long) enough);
E 6
I 6
	printf("%u\n", get_enough(0));
I 7
	return (0);
E 7
E 6
E 5
E 4
}
E 2
I 1
E 1
