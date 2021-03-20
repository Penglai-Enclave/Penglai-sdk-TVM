H34421
s 00000/00003/00893
d D 1.34 01/06/19 10:34:41 staelin 35 34
c Remove references to BDS
cC
cK35376
e
s 00000/00002/00896
d D 1.33 01/06/13 11:00:39 staelin 34 33
c Enhance/update portability system to deal with various flavors of
c random number generators available in unix: drand48/rand/random.
cC
cK38377
e
s 00001/00001/00897
d D 1.32 01/05/21 10:56:11 staelin 33 32
c Remove unnecessary #include <malloc.h> which causes problems on some
c operating systems, and add #undef ALIGN, since Darwin/OSX has its own
c ALIGN macro
cC
cK40481
cZ+03:00
e
s 00001/00001/00897
d D 1.31 01/04/02 15:06:28 staelin 32 31
c Change include "timing.h" to include "bench.h" for new automatic types
cC
cHhpli69.hpli.hpl.hp.com
cK41209
e
s 00002/00000/00896
d D 1.30 01/02/07 14:02:28 staelin 31 30
c Don't define FLUSH for Lynx OS in lmdd
cC
cK41345
e
s 00003/00003/00893
d D 1.29 01/02/07 12:13:11 staelin 30 29
c - lmdd fixes for 64-bit HP-UX
cC
cK39278
cZ+02:00
e
s 00002/00002/00894
d D 1.28 00/07/27 14:37:00 staelin 29 28
c - Fixup type cast chains so they do the right thing on Robert G. Brown's machine
cC
cK39488
e
s 00000/00003/00896
d D 1.27 00/07/25 14:45:17 staelin 28 27
c - remove obsolete hardcoded definition of #define RUSAGE since it is now in build script
cC
cHhpli8.hpli.hpl.hp.com
cK38641
cZ+03:00
e
s 00006/00000/00893
d D 1.26 99/09/02 22:47:38 lm 27 26
c #ifdef O_SYNC
cC
cHwork.bitmover.com
cK43495
e
s 00031/00024/00862
d D 1.25 98/06/29 22:37:00 lm 26 25
c Redo to compile clean with -Wall.
cHlm.bitmover.com
cK38618
cZ-07:00
e
s 00002/00002/00884
d D 1.24 98/05/07 15:58:02 staelin 25 24
c - changed #ifdef hpux to #if defined(hpux) || defined(__hpux)
cHhpisc8.lempel
cK26118
cZ-00:00
e
s 00028/00008/00858
d D 1.23 97/12/01 15:47:59 lm 24 23
c add fork option for buffered writes.
cK21840
cZ-08:00
e
s 00008/00000/00858
d D 1.22 97/06/16 19:05:50 lm 23 22
c lint
cK01447
e
s 00001/00000/00857
d D 1.21 97/06/14 18:22:05 lm 22 21
c *** empty log message ***
cK58543
cZ-07:00
e
s 00679/00329/00178
d D 1.20 97/02/12 19:17:20 lm 21 20
c bring it up to date w/ diskbench.
cK56648
e
s 00008/00009/00499
d D 1.19 96/11/11 03:36:51 lm 20 19
c Auto adjusting changes.
cK52608
cZ-08:00
e
s 00001/00001/00507
d D 1.18 96/05/21 23:14:55 lm 19 18
c *** empty log message ***
cK52201
e
s 00008/00008/00500
d D 1.17 95/09/05 13:30:20 lm 18 17
c Made randoms work with 4 byte ints.
cK50305
e
s 00018/00011/00490
d D 1.16 95/09/05 13:24:02 lm 17 16
c made random ipat/opat work with char values.
cK46336
e
s 00111/00002/00390
d D 1.15 95/08/22 15:32:02 lm 16 15
c aio support; sgi specific?
cK33650
e
s 00018/00000/00374
d D 1.14 95/06/21 14:01:19 lm 15 14
c adding support for SGI's O_DIRECT
cK49970
cZ-07:00
e
s 00007/00002/00367
d D 1.13 95/03/10 18:19:39 lm 14 13
c lint
cK25615
e
s 00191/00221/00178
d D 1.12 94/11/18 00:54:27 lm 13 12
c getting closer to net release; lmbench changes.
cK16477
cZ-08:00
e
s 00039/00014/00360
d D 1.11 93/04/13 05:56:23 lm 12 11
c Add randoms.
cK16598
e
s 00038/00075/00336
d D 1.10 92/05/05 15:16:07 lm 11 10
c Better rusage handling.
cK39022
e
s 00077/00009/00334
d D 1.9 92/05/04 09:19:29 lm 10 9
c startup times more appropriate to each cpu type.
c HP snake port.
cK18684
cZ-07:00
e
s 00012/00006/00331
d D 1.8 92/03/22 15:04:14 lm 9 8
c rdukes fix for usec rollover
cK06394
e
s 00002/00000/00335
d D 1.7 92/02/27 02:38:28 lm 8 7
cK61400
e
s 00043/00003/00292
d D 1.6 92/02/27 02:32:25 lm 7 6
c Added mmap flush.
cK58558
e
s 00163/00103/00132
d D 1.5 92/02/12 03:45:13 lm 6 5
c cleanup, skip option
cK02700
e
s 00002/00002/00233
d D 1.4 90/11/28 10:31:32 lm 5 4
cK65305
e
s 00002/00002/00233
d D 1.3 90/11/22 09:36:56 lm 4 3
c adjusting printouts
cK64932
cZ-08:00
e
s 00001/00001/00234
d D 1.2 90/07/09 10:09:59 lm 3 2
cK64837
e
s 00235/00000/00000
d D 1.1 90/06/01 03:32:09 lm 2 1
c date and time created 90/06/01 10:32:09 by lm
cK64653
e
s 00000/00000/00000
d D 1.0 90/06/01 03:32:08 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK08405
cPsrc/lmdd.c
cR49191613a2a80e
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
D 3
static char sccsid = "%W%";
E 3
I 3
D 13
static char sccsid[] = "%W%";
I 6

E 13
I 13
D 25
char	*id = "$Id$\n";
E 25
I 25
char	*id = "$Id: lmdd.c,v 1.23 1997/12/01 23:47:59 lm Exp $\n";
E 25
E 13
E 6
E 3
/*
I 8
D 13
 * lmdd, lm@sun.com (Larry McVoy)
 *
E 8
 * Uncopyrighted, do whatever you want with it.
 *
E 13
 * defaults:
 *	bs=8k
 *	count=forever
D 6
 *	in=stdin
 *	out=stdout
 *	inpat=0
 *	outpat=0
 *	rusage=0
E 6
I 6
D 11
 *	if=stdin
 *	of=stdout
E 11
I 11
 *	if=internal
 *	of=internal
E 11
 *	ipat=0
 *	opat=0
E 6
 *	mismatch=0
I 6
 *	rusage=0
I 7
 *	flush=0
I 12
 *	rand=0
I 13
 *	print=0
I 21
 *	direct=0
 *	rt=0
 *	rtmax=0
 *	wtmax=0
 *	rtmin=0
 *	wtmin=0
E 21
 *	label=""
E 13
E 12
E 7
E 6
 * shorthands:
D 21
 *	recognizes 'k' or 'm' at the end of a number for 1024 & 1024^2
E 21
I 21
 *	k, m, g are 2^10, 2^20, 2^30 multipliers.
 *	K, M, G are 10^3, 10^6, 10^9 multipliers.
E 21
 *	recognizes "internal" as an internal /dev/zero /dev/null file.
I 13
 *
D 17
 * Copyright (c) 1994 Larry McVoy.  All rights reserved.
E 17
I 17
D 21
 * Copyright (c) 1994,1995 Larry McVoy.  All rights reserved.
E 21
I 21
D 26
 * Copyright (c) 1994-1996 by Larry McVoy.  All rights reserved.
E 26
I 26
 * Copyright (c) 1994-1998 by Larry McVoy.  All rights reserved.
E 26
 * See the file COPYING for the licensing terms.
I 26
 *
 * TODO - rewrite this entire thing from scratch.  This is disgusting code.
E 26
E 21
E 17
E 13
 */
I 10

I 31
#ifndef __Lynx__
E 31
I 23
D 25
#if	!defined(hpux)
E 25
I 25
D 28
#if	!defined(hpux) && !defined(__hpux)
E 25
E 23
D 13
/*
 * Compile time configs
 */
#ifdef	sun
#define	FLUSH
#define	RUSAGE
#endif
E 13
I 13
D 20
#include	"timing.c"
E 13

E 20
I 20
D 21
#include "timing.h"
#include "bench.h"
#include <fcntl.h>
E 20
E 10
D 13
#include <signal.h>
I 6
#include <sys/types.h>
E 6
#include <sys/time.h>
I 6
D 10
#ifndef	SVR4
E 10
I 10
#ifdef	RUSAGE
E 10
E 6
#include <sys/resource.h>
I 6
#endif
E 13
I 7
D 10
#define	FLUSH
E 10
#ifdef	FLUSH
D 13
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
E 13
I 13
D 20
#include	<unistd.h>
#include	<sys/mman.h>
#include	<sys/stat.h>
E 20
I 20
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
E 21
I 21
#define	RUSAGE
I 23
#endif
E 28
E 23
#define	FLUSH
I 31
#endif
E 31

#include	<fcntl.h>
#include	<stdio.h>
I 26
#include	<stdlib.h>
E 26
#include	<signal.h>
#include	<string.h>
D 33
#include	<malloc.h>
E 33
#include	<unistd.h>
#include	<sys/types.h>
I 24
#include	<sys/wait.h>
E 24
D 35
#ifdef	USE_BDS
#include	"bds.h"
E 21
E 20
E 13
#endif
E 35
I 22
#include	<sys/time.h>
E 22
I 21
D 32
#include	"timing.h"
E 32
I 32
#include	"bench.h"
E 32
E 21
I 10
D 13
#ifdef	sun
#include <machine/cpu.h>	/* XXX - assumes 4.1.2 at least */
E 13
I 13

I 33
#undef ALIGN
E 33
I 15
D 20
#include	<fcntl.h>

I 16
D 19
#ifdef	sgi
E 19
I 19
#if	defined(sgi) && defined(DO_AIO)
E 20
I 20
D 21
#if	defined(DO_AIO)
E 20
E 19
#define	AIO	10
#ifdef	AIO
D 20
#include	<aio.h>
E 20
I 20
#include <aio.h>
E 21
I 21
#define ALIGN(x, bs)    ((x + (bs - 1)) & ~(bs - 1))

#ifdef	FLUSH
#include	<sys/mman.h>
#include	<sys/stat.h>
I 26
void		flush(void);
E 26
E 21
E 20
#endif
D 21
#endif
E 21

E 16
#define	USE_VALLOC
E 15
#ifdef	USE_VALLOC
#define	VALLOC	valloc
#else
#define	VALLOC	malloc
E 13
#endif
I 17
D 18
#define	uchar	unsigned char
E 18
E 17
E 10
I 9

D 13
#define USECS_PER_SEC   1000000.0
#define USECS_PER_TICK  1000	
E 9
E 7
E 6
D 10
#define	STARTUP		(.11)	/* XXX - about how long before it starts
D 6
				 * working.  So time matches w/ rusage.
				 * This is close on a 20Mhz SS.
				 */
E 6
I 6
				 * working.  So time matches w/ rusage. This is
				 * close on a 20Mhz SS. */
E 10
I 10

D 11
/*
 * Startup costs.  The type is the top byte of gethostid(), the startup
 * is the cost in seconds.
 */
struct	{
	int	type;
	double	startup;
} startup[] = {
#ifdef	sun
	0x51,	.11,	/* ss1 */
	0x52,	.11,	/* IPC */
	0x53,	.10,	/* ss1+ (guess) */
	0x54,	.12,	/* SLC (guess) */
	0x55,	.06,	/* ss2 */
	0x56,	.08,	/* ELC (guess) */
	0x57,	.06,	/* IPX */
	0x21,	.14,	/* 4/200 */
	0x22,	.15,	/* 4/110 (guess) */
	0x23,	.07,	/* 4/3xx */
	0x24,	.05,	/* 4/4xx */
			/* XXX - don't have 40Mhz viking numbers yet */
	0x72,	.035,	/* 33mhz - w/e$ is .03, w/o e$ is .03, avg */
#endif
			/* XXX - snake 9000/730 == .02 */
	0,	.08,	/* a rough guess for all unknowns */
};
E 11
E 10
E 6
#define	uchar	unsigned char

D 6
int out, Fsync, Sync, ru, c;	/* done needs it */
E 6
I 6
D 7
int     out, Fsync, Sync, ru, c;/* done needs it */
E 7
I 7
D 12
int     out, Fsync, Sync, Flush, ru, c;/* done needs it */
E 12
I 12
int     out, Fsync, Sync, Flush, Rand, Bsize, ru, c;/* done needs it */
E 13
I 13
D 21
int     out, Print, Fsync, Sync, Flush, Rand, Bsize, ru, c;/* done needs it */
E 21
I 21
D 26
extern	long long atoll(char *);
extern	long	atol(char *);
E 26
I 26
D 34
extern	double	drand48();
E 26

E 34
#ifdef	__sgi
#	define	LSEEK(a,b,c)	(uint64)lseek64(a, (off64_t)b, c)
#	define	ATOL(s)		atoll(s)
#else
#	define	LSEEK(a,b,c)	(uint64)lseek(a, b, c)
#	define	ATOL(s)		atol(s)
#endif

D 26
double	drand48();
int	getfile(char *s, int ac, char **av);
E 26

int     awrite, poff, out, Print, Fsync, Sync, Flush, Bsize, ru;
uint64	Start, End, Rand, int_count;
int	hash;
int	Realtime, Notrunc;
int	Rtmax, Rtmin, Wtmax, Wtmin;
int	rthist[12];		/* histogram of read times */
int	wthist[12];		/* histogram of write times */
E 21
char	*Label;
I 16
D 21
#ifdef	AIO
int	Aios;
struct aiocb aios[AIO];
struct aiocb *a;
int	next_aio = 0;
E 21
I 21
uint64	*norepeat;
int	norepeats = -1;
#ifdef	USE_BDS
	bds_msg	*m1, *m2;
E 21
#endif

E 16
D 21
long	getarg();
E 21
I 21
uint64	getarg();
I 26
int	been_there(uint64 off);
int	getfile(char *s, int ac, char **av);

E 26
E 21
E 13
E 12
E 7
char   *cmds[] = {
D 21
	"if",			/* input file */
	"of",			/* output file */
	"ipat",			/* check input for pattern */
	"opat",			/* generate pattern on output */
	"mismatch",		/* stop at first mismatch */
E 21
	"bs",			/* block size */
I 21
	"bufs",			/* use this many buffers round robin */
E 21
	"count",		/* number of blocks */
D 21
	"skip",			/* skip this number of blocks on input */
E 21
I 21
#ifdef	DBG
	"debug",		/* set external variable "dbg" */
#endif
#ifdef	O_DIRECT
	"direct",		/* direct I/O on input and output */
	"idirect",		/* direct I/O on input */
	"odirect",		/* direct I/O on output */
#endif
#ifdef	FLUSH
	"flush",		/* map in out and invalidate (flush) */
#endif
I 24
	"fork",			/* fork to do write I/O */
E 24
E 21
	"fsync",		/* fsync output before exit */
D 21
	"sync",			/* sync output before exit */
I 13
	"print",		/* report type */
E 21
I 21
	"if",			/* input file */
	"ipat",			/* check input for pattern */
E 21
	"label",		/* prefix print out with this */
I 21
	"mismatch",		/* stop at first mismatch */
E 21
I 14
	"move",			/* instead of count, limit transfer to this */
I 21
	"of",			/* output file */
	"opat",			/* generate pattern on output */
	"print",		/* report type */
E 21
E 14
E 13
I 12
	"rand",			/* do randoms over the specified size */
				/* must be power of two, not checked */
I 21
	"poff",			/* Print the offsets as we do the io. */
E 21
E 12
I 10
#ifdef	RUSAGE
E 10
	"rusage",		/* dump rusage stats */
I 10
#endif
E 10
I 7
D 21
#ifdef	FLUSH
	"flush",		/* map in out and invalidate (flush) */
E 21
I 21
	"skip",			/* skip this number of blocks */
	"sync",			/* sync output before exit */
	"touch",		/* touch each buffer after the I/O */
I 23
#if	!defined(hpux)
E 23
	"usleep",		/* sleep this many usecs between I/O */
I 23
#endif
E 23
	"hash",			/* hash marks like FTP */
	"append",		/* O_APPEND */
	"rtmax",		/* read latency histogram max in mills */
	"wtmax",		/* write latency histogram max in mills */
	"rtmin",		/* read latency histogram max in mills */
	"wtmin",		/* write latency histogram max in mills */
	"realtime",		/* create files as XFS realtime files */
	"notrunc",		/* overwrite rather than truncing out file */
	"end",			/* limit randoms to this size near the
				 * Rand endpoints. */
	"start",		/* Add this to Rand */
	"time",			/* Run for this many seconds only. */
	"srand",		/* Seed the random number generator */
	"padin",		/* Pad an extra untimed block_size read */
#ifdef	USE_BDS
	"awrite",		/* use async writes and pipeline them. */
E 21
#endif
I 21
	"norepeat",		/* don't ever do the same I/O twice */
E 21
I 15
#ifdef	sgi
D 21
	"direct",		/* O_DIRECT */
E 21
I 21
	"mpin",			/* pin the buffer */
E 21
#endif
I 16
D 21
#ifdef	AIO
	"aios",			/* multiple writers */
#endif
E 21
I 21
	"timeopen",		/* include open time in results */
	"nocreate",		/* just open for writing, don't create/trunc it */
I 27
#ifdef	O_SYNC
E 27
	"osync",		/* O_SYNC */
I 27
#endif
E 27
E 21
E 16
E 15
E 7
	0,
};
E 6

D 21
main(ac, av)
I 13
	int	ac;
E 13
D 6
	char **av;
E 6
I 6
	char  **av;
E 6
{
D 6
	uchar *buf;
	int misses, mismatch, outpat, inpat, bs, in, gotcnt, count;
E 6
I 6
D 17
	uint  *buf;
E 17
I 17
D 18
	uchar  *buf;
E 18
I 18
	uint  *buf;
E 18
E 17
D 12
	int     misses, mismatch, outpat, inpat, bs, in, gotcnt, count;
E 12
I 12
	int     misses, mismatch, outpat, inpat, in, gotcnt, count;
E 12
	int     skip;
I 12
D 14
	int	size;
E 14
I 14
	long	size;
E 14
E 12
E 6
D 13
	extern char *valloc();
E 13
D 6
	void done();
E 6
I 6
	void    done();
I 13
	void	chkarg();
E 13
D 14
	int     i;
E 14
I 14
	long     i;
I 16
	off_t	off = 0;
E 21
E 16
E 14
E 6

I 17
D 21
	if (sizeof(int) != 4) {
		fprintf(stderr, "sizeof(int) != 4\n");
		exit(1);
	}
E 17
I 6
	for (i = 1; i < ac; ++i) {
		chkarg(av[i]);
	}
I 11
	signal(SIGINT, done);
E 11
E 6
	misses = mismatch = getarg("mismatch=", ac, av);
D 6
	inpat = getarg("inpat=", ac, av);
	outpat = getarg("outpat=", ac, av);
E 6
I 6
	inpat = getarg("ipat=", ac, av);
	outpat = getarg("opat=", ac, av);
E 6
D 11
	in = getfile("if=", ac, av);
	if (in == -1)
		in = 0;
	out = getfile("of=", ac, av);
	if (out == -1)
		out = 1;
E 11
D 12
	bs = getarg("bs=", ac, av);
	if (bs < 0)
		bs = 8192;
E 12
I 12
	Bsize = getarg("bs=", ac, av);
	if (Bsize < 0)
		Bsize = 8192;
E 12
	Fsync = getarg("fsync=", ac, av);
	Sync = getarg("sync=", ac, av);
I 12
	Rand = getarg("rand=", ac, av);
I 13
	Print = getarg("print=", ac, av);
	Label = (char *)getarg("label=", ac, av);
E 13
	if (Rand != -1) {
		size = (Rand - 1) & ~511;
	}
E 12
I 10
#ifdef	RUSAGE
E 10
	ru = getarg("rusage=", ac, av);
I 10
#endif
E 10
	count = getarg("count=", ac, av);
I 14
	i = getarg("move=", ac, av);
	if (i > 0)
		count = i / Bsize;

E 14
I 10
#ifdef	FLUSH
E 10
I 7
	Flush = getarg("flush=", ac, av);
I 10
#endif
E 10
E 7
	if (count < 0)
		gotcnt = 0;
	else
		gotcnt = 1;
	c = 0;
I 6
	skip = getarg("skip=", ac, av);
E 6

D 6
	if (!(buf = (uchar*)valloc((unsigned)bs))) {
E 6
I 6
D 12
	if (inpat != -1 || outpat != -1 && (bs & 3)) {
E 12
I 12
D 13
	if (inpat != -1 || outpat != -1 && (Bsize & 3)) {
E 12
		printf("Block size must be word aligned\n");
E 13
I 13
	if ((inpat != -1 || outpat != -1) && (Bsize & 3)) {
		fprintf(stderr, "Block size 0x%x must be word aligned\n", Bsize);
E 13
		exit(1);
	}
D 12
	if (!(buf = (uint *) valloc((unsigned) bs))) {
E 12
I 12
D 13
	if (!(buf = (uint *) valloc((unsigned) Bsize))) {
E 12
E 6
		perror("valloc");
E 13
I 13
	if ((Bsize >> 2) == 0) {
		fprintf(stderr, "Block size must be at least 4.\n");
E 13
		exit(1);
	}
I 16
#ifdef	AIO
	Aios = getarg("aios=", ac, av);
	if (Aios > AIO) {
E 21
I 21
void error(char *);
void    done();
#ifdef	DBG
E 21
D 21
		printf("Only %d aios supported\n", AIO);
E 21
I 21
extern int dbg;
#endif

int 
main(int ac, char **av)
{
	uint  *buf;
	uint  *bufs[10];
	int	nbufs, nextbuf = 0;
D 24
	int     misses, mismatch, outpat, inpat, in, timeopen, gotcnt;
E 24
I 24
	int     Fork, misses, mismatch, outpat, inpat, in, timeopen, gotcnt;
E 24
	int	slp;
	uint64	skip, size, count;
	void	chkarg();
	int     i;
	uint64	off = 0;
	int	touch;
	int	time;
	int	mills;
	int	pad_in;
I 24
	int	pid = 0;
E 24
	struct timeval	start_tv;
	struct timeval	stop_tv;

	if (sizeof(int) != 4) {
		fprintf(stderr, "sizeof(int) != 4\n");
E 21
		exit(1);
	}
D 21
	if (Aios <= 0) {
		Aios = 1;
E 21
I 21
	for (i = 1; i < ac; ++i) {
		chkarg(av[i]);
E 21
	}
D 21
	if (Aios > 1) {
		aio_init();
E 21
I 21
	signal(SIGINT, done);
	signal(SIGALRM, done);
	misses = mismatch = getarg("mismatch=", ac, av);
	inpat = getarg("ipat=", ac, av);
	outpat = getarg("opat=", ac, av);
	Bsize = getarg("bs=", ac, av);
	if (Bsize < 0)
		Bsize = 8192;
I 23
#if	!defined(hpux)
E 23
	slp = getarg("usleep=", ac, av);
I 23
#endif
I 24
	Fork = getarg("fork=", ac, av);
E 24
E 23
	Fsync = getarg("fsync=", ac, av);
	Sync = getarg("sync=", ac, av);
	Rand = getarg("rand=", ac, av);
	Start = getarg("start=", ac, av);
	End = getarg("end=", ac, av);
	time = getarg("time=", ac, av);
	if ((End != -1) && (Rand != -1) && (End > Rand)) {
		End = Rand;
E 21
	}
D 21
	bzero(aios, sizeof(aios));
	for (i = 0; i < Aios; ++i) {
#endif
E 16
I 13
D 17
	if (!(buf = (uint *) VALLOC((unsigned) Bsize))) {
E 17
I 17
D 18
	if (!(buf = (uchar *) VALLOC((unsigned) Bsize))) {
E 18
I 18
	if (!(buf = (uint *) VALLOC((unsigned) Bsize))) {
E 18
E 17
		perror("VALLOC");
E 21
I 21
	if (getarg("srand=", ac, av) != -1) {
		srand48((long)getarg("srand=", ac, av));
	}
	poff = getarg("poff=", ac, av) != -1;
	Print = getarg("print=", ac, av);
	nbufs = getarg("bufs=", ac, av);
	Realtime = getarg("realtime=", ac, av);
	Rtmax = getarg("rtmax=", ac, av);
	if ((Rtmax != -1) && (Rtmax < 10))
		Rtmax = 10;
	Rtmin = getarg("rtmin=", ac, av);
	if ((Rtmax != -1) && (Rtmin == -1)) {
		Rtmin = 0;
	}
	Wtmax = getarg("wtmax=", ac, av);
	if ((Wtmax != -1) && (Wtmax < 10))
		Wtmax = 10;
	Wtmin = getarg("wtmin=", ac, av);
	if ((Wtmax != -1) && (Wtmin == -1)) {
		Wtmin = 0;
	}
	if ((Rtmin && !Rtmax) || (Wtmin && !Wtmax)) {
		fprintf(stderr, "Need a max to go with that min.\n");
E 21
		exit(1);
	}
E 13
D 6
	bzero((char*)buf, bs);
E 6
I 6
D 12
	bzero((char *) buf, bs);
E 12
I 12
D 21
	bzero((char *) buf, Bsize);
I 16
#ifdef	AIO
	aios[i].aio_buf = buf;
E 21
I 21
	if ((Rtmin > Rtmax) || (Wtmin > Wtmax)) {
		fprintf(stderr,
		    "min has to be less than max, R=%d,%d W=%d,%d\n",
		    Rtmax, Rtmin, Wtmax, Wtmin);
		exit(1);
E 21
	}
I 21
	timeopen = getarg("timeopen=", ac, av);
	pad_in = getarg("padin=", ac, av);
	if (pad_in == -1) pad_in = 0;
	
	if (nbufs == -1) nbufs = 1;
	if (nbufs > 10) { printf("Too many bufs\n"); exit(1); }
#ifdef	DBG
	dbg = getarg("debug=", ac, av) != -1;
E 21
#endif
E 16
E 12
E 6
D 21

D 11
	signal(SIGINT, done);
E 11
I 11
	start();
	/*
	 * We want this here because otherwise the accounting gets screwed up
	 */
	in = getfile("if=", ac, av);
	out = getfile("of=", ac, av);
E 11
I 6
D 13
	if (skip > 0)
E 13
I 13
	if (skip > 0) {
E 13
D 12
		lseek(in, skip * bs, 0);
E 12
I 12
		lseek(in, skip * Bsize, 0);
E 21
I 21
#ifdef	RUSAGE
	ru = getarg("rusage=", ac, av);
#endif
	touch = getarg("touch=", ac, av) != -1;
D 26
	hash = getarg("hash=", ac, av) != -1;
E 26
I 26
	hash = getarg("hash=", ac, av) != (uint64)-1;
E 26
D 29
	Label = (char *)getarg("label=", ac, av);
E 29
I 29
D 30
	Label = (char *)(int)getarg("label=", ac, av);
E 30
I 30
	Label = (char *)getarg("label=", ac, av);
E 30
E 29
	count = getarg("count=", ac, av);
	size = getarg("move=", ac, av);
	if (size != (uint64)-1)
		count = size / Bsize;
	if (Rand != -1) {
		size = Rand - Bsize;
		size = ALIGN(size, Bsize);
E 21
I 13
	}
E 13
E 12
E 6
D 11
	start();
I 10
#ifdef	CALC_START
	exit(0);
	/*NOTREACHED*/
#endif
E 11
E 10
D 6
	for ( ;; ) {
E 6
I 6
D 21
	for (;;) {
E 6
		register x;
E 21

D 13
		if (gotcnt && count-- <= 0)
E 13
I 13
D 21
		if (gotcnt && count-- <= 0) {
E 13
			done();
I 13
		}
I 16

#ifdef	AIO
		if (Aios > 1) {
			if (++next_aio == Aios) {
				next_aio = 0;
			}
			a = &aios[next_aio];
			buf = a->aio_buf;
			if (a->aio_nbytes) {
				int	n;

				aio_suspend(&a, 1, 0);
				n = aio_return(a);
				if (n != a->aio_nbytes) {
					printf("aio%d wanted %d got %d\n",
					   next_aio, a->aio_nbytes, n);
					done();
#if 0
				} else {
					printf("aio %x @ %d worked\n", 
					    a->aio_buf, a->aio_offset);
E 21
I 21
#ifdef	FLUSH
	Flush = getarg("flush=", ac, av);
E 21
#endif
D 21
				}
			}
			a->aio_nbytes = 0;
		}
#endif

E 16
E 13
I 12
		/*
		 * Set the seek pointer if doing randoms
		 */
		if (Rand != -1) {
D 16
			u_int	off = lrand48() & size;

E 16
I 16
			off = lrand48() & size;
E 16
D 13
			if (in != -1) 
E 13
I 13
D 17
			if (in != -1) {
E 17
I 17
			if (in >= 0) {
E 17
E 13
				lseek(in, off, 0);
D 13
			if (out != -1)
E 13
I 13
			}
D 17
			if (out != -1) {
E 17
I 17
			if (out >= 0) {
E 17
E 13
				lseek(out, off, 0);
I 13
			}
E 13
		}
I 16

#ifdef	AIO
		if (Aios > 1) {
			a->aio_offset = off;
		}
#endif

E 16
E 12
D 13
		if (in >= 0)
E 13
I 13
		if (in >= 0) {
E 13
D 6
		    x = read(in, buf, bs);
E 6
I 6
D 12
			x = read(in, buf, bs);
E 12
I 12
			x = read(in, buf, Bsize);
E 12
E 6
D 13
		else
E 13
I 13
		} else {
E 13
D 6
		    x = bs;
E 6
I 6
D 12
			x = bs;
E 12
I 12
			x = Bsize;
E 12
E 6
D 13
		if (x <= 0)
E 13
I 13
		}
		if (x <= 0) {
E 13
D 6
		    done();
E 6
I 6
			done();
I 13
		}
E 13
E 6
		if (inpat != -1) {
			register foo, cnt;

D 6
			for (foo=0, cnt=x; cnt--; foo++) {
			    if (buf[foo] != (uchar)(c + foo) & 0xff) {
				printf("MISMATCH: off=%d want=%x got=%x\n",
				    c + foo, c + foo & 0xff, buf[foo]);
				if (mismatch != -1 && --misses == 0)
				    done();
			    }
E 6
I 6
D 17
			for (foo = 0, cnt = x >> 2; cnt--; foo++) {
				if (buf[foo] != (uint) (c + foo)) {
E 17
I 17
D 18
			for (foo = 0, cnt = x; cnt--; foo++) {
				if (buf[foo] != (uchar) (off + foo)) {
E 18
I 18
			for (foo = 0, cnt = x/sizeof(int); cnt--; foo++) {
				if (buf[foo] != (uint) (off + foo*sizeof(int))) {
E 18
E 17
D 13
					printf("ERROR: off=%d want=%x got=%x\n",
E 13
I 13
					fprintf(stderr,
D 17
					    "ERROR: off=%d want=%x got=%x\n",
E 13
					    c + foo, c + foo, buf[foo]);
E 17
I 17
					    "off=%uK want=%x (%uK) got=%x (%uK)\n",
					    off >> 10,
D 18
					    off + foo, (off + foo) >> 10,
E 18
I 18
					    off + foo*sizeof(int),
					    (off + foo*sizeof(int)) >> 10,
E 18
					    buf[foo], buf[foo] >> 10);
E 17
D 13
					if (mismatch != -1 && --misses == 0)
						done();
				}
E 6
			}
		}
		if (outpat != -1) {
			register foo, cnt;

D 6
			for (foo=0, cnt=x; cnt--; foo++)
			    buf[foo] = c + foo & 0xff;
E 6
I 6
			for (foo = 0, cnt = x >> 2; cnt--; foo++)
				buf[foo] = c + foo;
E 6
		}
		if (out >= 0)
D 6
		    if (write(out, buf, x) != x)
			done();
		c += x;
E 6
I 6
			if (write(out, buf, x) != x)
				done();
		c += x >> 2;
E 6
	}
}

I 6
chkarg(arg)
	char	*arg;
{
	int	i;
	char	*a, *b;

	for (i = 0; cmds[i]; ++i) {
		for (a = arg, b = cmds[i]; *a && *b && *a == *b; a++, b++)
			;
		if (*a == '=')
			return (0);
	}
	printf("Bad arg: %s\n", arg);
	exit(1);
I 11
	/*NOTREACHED*/
E 11
}

E 6
void
done()
{
	close(1);
	open("/dev/tty", 1);
D 7
	if (Sync != -1)
E 7
I 7
	if (Sync > 0)
E 7
D 6
	    sync();
E 6
I 6
		sync();
E 6
D 7
	if (Fsync != -1)
E 7
I 7
	if (Fsync > 0)
E 7
D 6
	    fsync(out);
E 6
I 6
		fsync(out);
I 10
#ifdef	FLUSH
E 10
I 7
	if (Flush > 0)
D 11
		flush(out);
E 11
I 11
		flush();
E 11
I 10
#endif
E 10
E 7
E 6
	stop();
I 6
D 10
#ifndef	SVR4
E 10
I 10
#ifdef	RUSAGE
E 10
E 6
	if (ru != -1)
D 6
	    rusage();
	ptime(c);
E 6
I 6
		rusage();
#endif
	ptime(c << 2);
E 6
	exit(0);
}

D 9
#define	secs(tv)	(tv.tv_sec + tv.tv_usec / 1000000.0)
E 9
I 9
#define	secs(tv)	(tv.tv_sec + tv.tv_usec / USECS_PER_SEC)
I 11
#define	mine(f)		(r.f - ru_start.f)
E 11
E 9

I 6
D 10
#ifndef	SVR4
E 10
I 10
#ifdef	RUSAGE
I 11
struct	rusage ru_start;

E 11
E 10
E 6
rusage()
{
	struct rusage r;
I 11
	double  sys, user, idle;
	double  per;
E 11
D 6
	double timespent();
	double idle;
E 6
I 6
	double  timespent();
D 11
	double  idle;
E 11
E 6

	getrusage(RUSAGE_SELF, &r);
D 6
	idle = timespent() - (secs(r.ru_stime) + secs(r.ru_utime)); 
E 6
I 6
D 11
	idle = timespent() - (secs(r.ru_stime) + secs(r.ru_utime));
E 6
	idle = idle / timespent() * 100;
	printf("sys=%g user=%g stalled=%.0f%% rd=%d wr=%d min=%d maj=%d\n",
D 6
	    secs(r.ru_stime), secs(r.ru_utime), 
E 6
I 6
	    secs(r.ru_stime), secs(r.ru_utime),
E 6
	    idle, r.ru_inblock, r.ru_oublock,
	    r.ru_minflt, r.ru_majflt);
E 11
I 11
	sys = secs(r.ru_stime) - secs(ru_start.ru_stime);
	user = secs(r.ru_utime) - secs(ru_start.ru_utime);
	idle = timespent() - (sys + user);
	per = idle / timespent() * 100;
	printf("real=%.2f sys=%.2f user=%.2f idle=%.2f stall=%.0f%% ",
	    timespent(), sys, user, idle, per);
	printf("rd=%d wr=%d min=%d maj=%d\n",
	    mine(ru_inblock), mine(ru_oublock),
	    mine(ru_minflt), mine(ru_majflt));
E 11
}
D 10

E 10
I 6
#endif

E 6
getarg(s, ac, av)
D 6
	char *s;
	char **av;
E 6
I 6
	char   *s;
	char  **av;
E 6
{
	register len, i;

	len = strlen(s);

D 6
	for (i=1; i<ac; ++i)
	    if (!strncmp(av[i], s, len)) {
		register bs = atoi(&av[i][len]);
E 6
I 6
	for (i = 1; i < ac; ++i)
		if (!strncmp(av[i], s, len)) {
			register bs = atoi(&av[i][len]);
E 6

D 6
		if (rindex(&av[i][len], 'k'))
			bs *= 1024;
		else if (rindex(&av[i][len], 'm'))
			bs *= (1024 * 1024);
		return (bs);
	}
	return (-1);
}

getfile(s, ac, av)
	char *s;
	char **av;
{
	register ret, len, i;

	len = strlen(s);

	for (i=1; i<ac; ++i) {
	    if (!strncmp(av[i], s, len)) {
		if (av[i][0] == 'o') {
		    if (!strcmp("of=internal", av[i]))
			return (-2);
		    ret = creat(&av[i][len], 0644);
		    if (ret == -1)
			error(&av[i][len]);
		    return (ret);
		} else {
		    if (!strcmp("if=internal", av[i]))
			return (-2);
		    ret = open(&av[i][len], 0);
		    if (ret == -1)
			error(&av[i][len]);
		    return (ret);
E 6
I 6
			if (rindex(&av[i][len], 'k'))
				bs *= 1024;
			else if (rindex(&av[i][len], 'm'))
				bs *= (1024 * 1024);
			return (bs);
E 6
		}
D 6
	    }
	}
E 6
	return (-1);
}
D 6
/*
 * utilities for timing
 */
#include "stdio.h"
#include "sys/types.h"
#include "sys/time.h"
E 6

I 7
char	*output;

E 7
D 6
static struct timeval t1, t2;

error(s)
    char* s;
{
    perror(s);
    exit(1);
}

start() { gettimeofday(&t1, (struct timezone*)0); }
stop() { gettimeofday(&t2, (struct timezone*)0); }
ptime(bytes) { ptransfer(bytes, &t1, &t2); }
double timespent()
E 6
I 6
getfile(s, ac, av)
	char   *s;
	char  **av;
E 6
{
I 6
	register ret, len, i;

E 13
I 13
					if (mismatch != -1 && --misses == 0) {
						done();
					}
				}
			}
		}
E 21
I 21
	if (count == (uint64)-1)
		gotcnt = 0;
	else
		gotcnt = 1;
	int_count = 0;
	skip = getarg("skip=", ac, av);
	if (getarg("norepeat=", ac, av) != -1) {
E 21
D 21
		if (outpat != -1) {
			register foo, cnt;
E 21
I 21
		if (gotcnt) {
			norepeat = (uint64*)calloc(count, sizeof(uint64));
		} else {
			norepeat = (uint64*)calloc(10<<10, sizeof(uint64));
		}
	}
E 21

D 17
			for (foo = 0, cnt = x >> 2; cnt--; foo++) {
				buf[foo] = c + foo;
E 17
I 17
D 18
			for (foo = 0, cnt = x; cnt--; foo++) {
				buf[foo] = (uchar)(off + foo);
E 18
I 18
D 21
			for (foo = 0, cnt = x/sizeof(int); cnt--; foo++) {
				buf[foo] = (uint)(off + foo*sizeof(int));
E 18
E 17
			}
E 21
I 21
	if ((inpat != -1 || outpat != -1) && (Bsize & 3)) {
		fprintf(stderr, "Block size 0x%x must be word aligned\n", Bsize);
		exit(1);
	}
	if ((Bsize >> 2) == 0) {
		fprintf(stderr, "Block size must be at least 4.\n");
		exit(1);
	}
	for (i = 0; i < nbufs; i++) {
		if (!(bufs[i] = (uint *) VALLOC((unsigned) Bsize))) {
			perror("VALLOC");
			exit(1);
E 21
		}
D 21
		if (out >= 0) {
I 16
#ifdef	AIO
			if (Aios > 1) {
				a->aio_nbytes = x;
				a->aio_fildes = out;
				if (aio_write(a)) {
					perror("aio_write");
					done();
				}
			} else {
				if (write(out, buf, x) != x) {
					done();
				}
E 21
I 21
		bzero((char *) bufs[i], Bsize);
#ifdef sgi
		if (getarg("mpin=", ac, av) != -1) {
			if (mpin((void *)bufs[i], (size_t)Bsize)) {
				perror("mpin for adam");
E 21
			}
D 21
#else
E 16
			if (write(out, buf, x) != x) {
				done();
			}
I 16
#endif
E 21
E 16
		}
I 16
D 21
		off += x;
E 16
		c += (x >> 2);
E 21
I 21
#endif
E 21
	}
D 21
}
E 21

D 21
void
chkarg(arg)
	char	*arg;
{
	int	i;
	char	*a, *b;

	for (i = 0; cmds[i]; ++i) {
		for (a = arg, b = cmds[i]; *a && *b && *a == *b; a++, b++)
			;
		if (*a == '=')
			return;
E 21
I 21
	if (time != -1) {
		alarm(time);
E 21
	}
D 21
	fprintf(stderr, "Bad arg: %s\n", arg);
	exit(1);
	/*NOTREACHED*/
}

void
done()
{
I 16
#ifdef	AIO
	if (Aios > 1) {
		int	i, n;

		for (i = 0; i < Aios; ++i) {
			a = &aios[i];
			if (a->aio_nbytes) {
				aio_suspend(&a, 1, 0);
				n = aio_return(a);
				if (n != a->aio_nbytes) {
					printf("aio%d wanted %d got %d\n",
					   next_aio, a->aio_nbytes, n);
#if 0
				} else {
					printf("aio %d worked\n", n);
#endif
				}
			}
			a->aio_nbytes = 0;
		}
E 21
I 21
	if (timeopen != -1) {
		start(NULL);
E 21
	}
D 21
#endif
E 16
	if (Sync > 0)
		sync();
	if (Fsync > 0)
		fsync(out);
#ifdef	FLUSH
	if (Flush > 0)
		flush();
#endif
	stop();
#ifdef	RUSAGE
	if (ru != -1)
		rusage();
#endif
	if ((long)Label != -1) {
		fprintf(stderr, "%s", Label);
E 21
I 21
	in = getfile("if=", ac, av);
	out = getfile("of=", ac, av);
	if (timeopen == -1) {
		start(NULL);
E 21
	}
D 21
	switch (Print) {
	    case 0:	/* no print out */
	    	break;
E 21
I 21
	if ((Rtmax != -1) && in < 0) {
		fprintf(stderr, "I think you wanted wtmax, not rtmax\n");
		exit(1);
	}
	if ((Wtmax != -1) && out < 0) {
		fprintf(stderr, "I think you wanted rtmax, not wtmax\n");
		exit(1);
	}
	if (skip != (uint64)-1) {
		off = skip;
		off *= Bsize;
		if (in >= 0) {
			LSEEK(in, off, 0);
		}
		if (out >= 0) {
			LSEEK(out, off, 0);
		}
		if (poff) {
			fprintf(stderr, "%s ", p64sz(off));
		}
	}
	for (;;) {
		register int moved;
E 21

D 21
	    case 1:	/* latency type print out */
		latency((c << 2) / Bsize, Bsize);
		break;
E 21
I 21
		if (gotcnt && count-- <= 0) {
			done();
		}
E 21

D 21
	    case 2:	/* microsecond per op print out */
		micro("", (c << 2) / Bsize);
		break;
E 21
I 21
		/*
		 * If End is set, it means alternate back and forth
		 * between the end points of Rand, doing randoms within
		 * the area 0..End and Rand-End..Rand
		 */
		if (End != -1) {
			static	uint64 start = 0;
E 21

D 21
	    case 3:	/* kb / sec print out */
		kb(c << 2);
		break;

	    case 4:	/* mb / sec print out */
		mb(c << 2);
		break;
E 21
I 21
			start = start ? 0 : Rand - End;
			do {
				off = drand48() * End;
				off = ALIGN(off, Bsize);
				off += start;
				if (Start != -1) {
					off += Start;
				}
			} while (norepeat && been_there(off));
			if (norepeat) {
				norepeat[norepeats++] = off;
				if (!gotcnt && (norepeats == 10<<10)) {
					norepeats = 0;
				}
			}
			if (in >= 0) {
				LSEEK(in, off, 0);
			}
			if (out >= 0) {
				LSEEK(out, off, 0);
			}
		}
		/*
		 * Set the seek pointer if doing randoms
		 */
		else if (Rand != -1) {
			do {
				off = drand48() * (size - Bsize);
				if (Start != -1) {
					off += Start;
				}
				off = ALIGN(off, Bsize);
			} while (norepeat && been_there(off));
			if (norepeat) {
				norepeat[norepeats++] = off;
			}
			if (!gotcnt && (norepeats == 10<<10)) {
				norepeats = 0;
			}
			if (in >= 0) {
				LSEEK(in, off, 0);
			}
			if (out >= 0) {
				LSEEK(out, off, 0);
			}
		}
		if (poff) {
			fprintf(stderr, "%s ", p64sz(off));
		}
E 21

D 21
	    case 5:	/* Xgraph output */
		bandwidth(c << 2, 0);
		break;
E 21
I 21
		buf = bufs[nextbuf];
		if (++nextbuf == nbufs) nextbuf = 0;
		if (in >= 0) {
			if ((Rtmax != -1) || (Rtmin != -1)) {
				start(&start_tv);
			}
			moved = read(in, buf, Bsize);
			
			if (pad_in) { /* ignore this run, restart clock */
			    pad_in = 0;
			    count++;
			    start(NULL);
			    continue;
			}
			
			if ((Rtmax != -1) || (Rtmin != -1)) {
				int mics = stop(&start_tv, &stop_tv);
				
D 26
				mills = mills / 1000;
E 26
I 26
				mills = mics / 1000;
E 26
				if ((mills > Rtmax) || (mills < Rtmin)) {
					fprintf(stderr,
					  "READ: %.02f milliseconds offset %s\n",
						((float)mics) / 1000,
						p64sz(LSEEK(in, 0, SEEK_CUR)));
				}
				/*
				 * Put this read time in the histogram.
				 * The buckets are each 1/10th of Rtmax.
				 */
				if (mills >= Rtmax) {
					rthist[11]++;
				} else if (mills < Rtmin) {
					rthist[0]++;
				} else {
					int	step = (Rtmax - Rtmin) / 10;
					int	i;
E 21

D 21
	    default:	/* bandwidth print out */
		bandwidth(c << 2, 1);
		break;
E 21
I 21
					for (i = 1; i <= 10; ++i) {
						if (mills < i * step + Rtmin) {
							rthist[i]++;
							break;
						}
					}
				}
			}
		} else {
			moved = Bsize;
		}
		if (moved == -1) {
			perror("read");
		}
		if (moved <= 0) {
			done();
		}
		if (inpat != -1) {
			register int foo, cnt;

			for (foo = 0, cnt = moved/sizeof(int); cnt--; foo++) {
				if (buf[foo] != (uint) (off + foo*sizeof(int))) {
					fprintf(stderr,
					    "off=%u want=%x got=%x\n",
D 26
					    off,
					    off + foo*sizeof(int),
E 26
I 26
					    (uint)off,
					    (uint)(off + foo*sizeof(int)),
E 26
					    buf[foo]);
					if (mismatch != -1 && --misses == 0) {
						done();
					}
				}
			}
		}
		if ((in >= 0) && touch) {
D 26
			int	j = 0, i;
E 26
I 26
			int	i;
E 26

			for (i = 0; i < moved; i += 4096) {
				((char *)buf)[i] = 0;
			}
		}
D 24
		if (outpat != -1) {
			register int foo, cnt;

			for (foo = 0, cnt = moved/sizeof(int); cnt--; foo++) {
				buf[foo] = (uint)(off + foo*sizeof(int));
			}
		}
E 24
		if (out >= 0) {
			int	moved2;
I 24

			if (Fork != -1) {
				if (pid) {
					waitpid(pid, 0, 0);
				}
D 26
				if (pid = fork()) {
E 26
I 26
				if ((pid = fork())) {
E 26
					off += moved;
					int_count += (moved >> 2);
					continue;
				}
			}
			if (outpat != -1) {
				register int foo, cnt;

				for (foo = 0, cnt = moved/sizeof(int);
				    cnt--; foo++) {
					buf[foo] =
					    (uint)(off + foo*sizeof(int));
				}
			}
E 24
			if ((Wtmax != -1) || (Wtmin != -1)) { 
				start(&start_tv);
			}
#ifdef	USE_BDS
			/*
			 * The first time through, m1 & m2 are null.
			 * The Nth time through, we start the I/O into
			 * m2, and wait on m1, then switch.
			 */
			if (awrite) {
				if (m1) {
					m2 = bds_awrite(out, buf, moved);
					moved2 = bds_adone(out, m1);
					m1 = m2;
				} else {
					m1 = bds_awrite(out, buf, moved);
					goto writedone;
				}
			} else {
				moved2 = write(out, buf, moved);
			}
#else
			moved2 = write(out, buf, moved);
#endif

			if (moved2 == -1) {
				perror("write");
			}
			if (moved2 != moved) {
				fprintf(stderr, "write: wanted=%d got=%d\n",
				    moved, moved2);
				done();
			}
			if ((Wtmax != -1) || (Wtmin != -1)) {
				int mics = stop(&start_tv, &stop_tv);

				mills = mics / 1000;
				if ((mills > Wtmax) || (mills < Wtmin)) {
					fprintf(stderr,
					  "WRITE: %.02f milliseconds offset %s\n",
						((float)mics) / 1000,
						p64sz(LSEEK(out, 0, SEEK_CUR)));
				}
				/*
				 * Put this write time in the histogram.
				 * The buckets are each 1/10th of Wtmax.
				 */
				if (mills >= Wtmax) {
					wthist[11]++;
				} else if (mills < Wtmin) {
					wthist[0]++;
				} else {
					int	step = (Wtmax - Wtmin) / 10;
					int	i;

					for (i = 1; i <= 10; ++i) {
						if (mills < i * step + Wtmin) {
							wthist[i]++;
							break;
						}
					}
				}
			}

			if (moved2 == -1) {
				perror("write");
			}
			if (moved2 != moved) {
				done();
			}

			if (touch) {
D 26
				int	j = 0, i;
E 26
I 26
				int	i;
E 26

				for (i = 0; i < moved; i += 4096) {
					((char *)buf)[i] = 0;
				}
			}
		}
I 26
#ifdef	USE_BDS
E 26
writedone:	/* for the first async write */
I 26
#endif
E 26
		off += moved;
		int_count += (moved >> 2);
I 23
#if	!defined(hpux)
E 23
		if (slp != -1) {
			usleep(slp);
		}
I 23
#endif
E 23
		if (hash) {
			fprintf(stderr, "#");
		}
I 24
		if (Fork != -1) {
			exit(0);
		}
E 24
E 21
	}
D 21
	exit(0);
E 21
}

I 26
int
E 26
D 21
long
E 21
I 21
been_there(uint64 off)
{
	register int i;

	for (i = 0; i <= norepeats; ++i) {
		if (off == norepeat[i]) {
D 26
			fprintf(stderr, "norepeat on %u\n", off);
E 26
I 26
			fprintf(stderr, "norepeat on %u\n", (uint)off);
E 26
			return (1);
		}
	}
	return (0);
}

void 
chkarg(char *arg)
{
	int	i;
	char	*a, *b;

	for (i = 0; cmds[i]; ++i) {
		for (a = arg, b = cmds[i]; *a && *b && *a == *b; a++, b++)
E 21
D 21
getarg(s, ac, av)
	char   *s;
	char  **av;
E 21
I 21
			;
		if (*a == '=')
			return;
	}
	fprintf(stderr, "Bad arg: %s, possible arguments are: ", arg);
	for (i = 0; cmds[i]; ++i) {
		fprintf(stderr, "%s ", cmds[i]);
	}
	fprintf(stderr, "\n");
	exit(1);
	/*NOTREACHED*/
}

void 
done(void)
E 21
{
D 21
	register len, i;
E 21
I 21
	int	i;
	int	step;
	int	size;
E 21

I 21
#ifdef	USE_BDS
	if (awrite && m1) {
		bds_adone(out, m1);
	}
#endif
	if (Sync > 0)
		sync();
	if (Fsync > 0)
		fsync(out);
#ifdef	FLUSH
	if (Flush > 0)
		flush();
#endif
	stop(NULL, NULL);
#ifdef	RUSAGE
	if (ru != -1)
		rusage();
#endif
	if (hash || poff) {
		fprintf(stderr, "\n");
	}
D 30
	if ((int)Label != -1) {
E 30
I 30
	if ((long)Label != -1) {
E 30
		fprintf(stderr, "%s", Label);
	}
	int_count <<= 2;
	switch (Print) {
	    case 0:	/* no print out */
	    	break;

	    case 1:	/* latency type print out */
		latency((uint64)(int_count / Bsize), (uint64)Bsize);
		break;

	    case 2:	/* microsecond per op print out */
		micro("", (uint64)(int_count / Bsize));
		break;

	    case 3:	/* kb / sec print out */
		kb(int_count);
		break;

	    case 4:	/* mb / sec print out */
		mb(int_count);
		break;

	    case 5:	/* Xgraph output */
		bandwidth(int_count, 1, 0);
		break;

	    default:	/* bandwidth print out */
		bandwidth(int_count, 1, 1);
		break;
	}
	if (Rtmax != -1) {
		printf("READ operation latencies\n");
		step = (Rtmax - Rtmin) / 10;
		if (rthist[0]) {
			printf("%d- ms: %d\n", Rtmin, rthist[0]);
		}
		for (i = 1, size = Rtmin; i <= 10; i++, size += step) {
			if (!rthist[i])
				continue;
			printf("%d to %d ms: %d\n",
			       size, size + step - 1, rthist[i]);
		}
		if (rthist[11]) {
			printf("%d+ ms: %d\n", Rtmax, rthist[11]);
		}
	}
	if (Wtmax != -1) {
		printf("WRITE operation latencies\n");
		step = (Wtmax - Wtmin) / 10;
		if (wthist[0]) {
			printf("%d- ms: %d\n", Wtmin, wthist[0]);
		}
		for (i = 1, size = Wtmin; i <= 10; i++, size += step) {
			if (!wthist[i])
				continue;
			printf("%d to %d ms: %d\n",
			       size, size + step - 1, wthist[i]);
		}
		if (wthist[11]) {
			printf("%d+ ms: %d\n", Wtmax, wthist[11]);
		}
	}
	exit(0);
}

uint64 
getarg(char *s, int ac, char **av)
{
	register uint64 len, i;

E 21
E 13
	len = strlen(s);

I 13
D 21
	for (i = 1; i < ac; ++i)
E 21
I 21
	for (i = 1; i < ac; ++i) {
E 21
		if (!strncmp(av[i], s, len)) {
D 21
			register bs = atoi(&av[i][len]);
E 21
I 21
			register uint64 bs = ATOL(&av[i][len]);
E 21

D 21
			if (rindex(&av[i][len], 'k'))
				bs *= 1024;
			else if (rindex(&av[i][len], 'm'))
				bs *= (1024 * 1024);
E 21
I 21
			switch (av[i][strlen(av[i]) - 1]) {
			    case 'K': bs *= 1000; break;
			    case 'k': bs <<= 10; break;
			    case 'M': bs *= 1000000; break;
			    case 'm': bs <<= 20; break;
			    case 'G': bs *= 1000000000L; break;
			    case 'g': bs <<= 30; break;
			}

E 21
			if (!strncmp(av[i], "label", 5)) {
D 21
				return (long)(&av[i][len]);	/* HACK */
E 21
I 21
D 29
				return (uint64)(&av[i][len]);	/* HACK */
E 29
I 29
D 30
				return (uint64)(int)(&av[i][len]); /* HACK */
E 30
I 30
				return (uint64)(long)(&av[i][len]); /* HACK */
E 30
E 29
E 21
			}
I 21
			if (!strncmp(av[i], "bs=", 3)) {
				return (uint64)(bs);
			}
E 21
			return (bs);
		}
D 21
	return (-1);
E 21
I 21
	}
	return ((uint64)-1);
E 21
}

char	*output;

D 21
getfile(s, ac, av)
	char   *s;
	char  **av;
E 21
I 21
int 
getfile(char *s, int ac, char **av)
E 21
{
D 21
	register ret, len, i;
E 21
I 21
	register int ret, len, i;
	int	append = getarg("append=", ac, av) != -1;
	int	notrunc = getarg("notrunc=", ac, av) != -1;
	int	nocreate = getarg("nocreate=", ac, av) != -1;
I 27
#ifdef	O_SYNC
E 27
	int	osync = getarg("osync=", ac, av) != -1;
I 27
#endif
E 27
	int	oflags;
E 21

	len = strlen(s);

E 13
	for (i = 1; i < ac; ++i) {
		if (!strncmp(av[i], s, len)) {
			if (av[i][0] == 'o') {
				if (!strcmp("of=internal", av[i]))
					return (-2);
I 13
				if (!strcmp("of=stdout", av[i]))
					return (1);
				if (!strcmp("of=1", av[i]))
					return (1);
				if (!strcmp("of=-", av[i]))
					return (1);
				if (!strcmp("of=stderr", av[i]))
					return (2);
				if (!strcmp("of=2", av[i]))
					return (2);
E 13
D 21
				ret = creat(&av[i][len], 0644);
I 15
#ifdef	sgi
				if (getarg("direct=", ac, av) != -1) {
E 21
I 21
				oflags = O_WRONLY;
				oflags |= (notrunc || append) ? 0 : O_TRUNC;
				oflags |= nocreate ? 0 : O_CREAT;
				oflags |= append ? O_APPEND : 0;
I 27
#ifdef O_SYNC
E 27
				oflags |= osync ? O_SYNC : 0;
I 27
#endif
E 27
				ret = open(&av[i][len], oflags,0644);
#ifdef	O_DIRECT
				if ((getarg("odirect=", ac, av) != -1) ||
				    (getarg("direct=", ac, av) != -1)) {
E 21
					close(ret);
D 21
					ret = open(&av[i][len], O_WRONLY|O_DIRECT);
E 21
I 21
					ret = open(&av[i][len], oflags|O_DIRECT);
					awrite =
					    getarg("awrite=", ac, av) != -1;
E 21
				}
#endif
E 15
				if (ret == -1)
					error(&av[i][len]);
I 21
#ifdef F_FSSETXATTR
				if (Realtime == 1) {
					struct fsxattr fsxattr;
				
					bzero(&fsxattr,sizeof(struct fsxattr));
					fsxattr.fsx_xflags = 0x1;
					if (fcntl(ret,F_FSSETXATTR,&fsxattr)){
						printf("WARNING: Could not make %s a real time file\n",
						       &av[i][len]);
					}
				}
#endif
E 21
I 7
				output = &av[i][len];
E 7
				return (ret);
			} else {
				if (!strcmp("if=internal", av[i]))
					return (-2);
I 13
				if (!strcmp("if=stdin", av[i]))
					return (0);
				if (!strcmp("if=0", av[i]))
					return (0);
				if (!strcmp("if=-", av[i]))
					return (0);
E 13
				ret = open(&av[i][len], 0);
I 15
D 21
#ifdef	sgi
				if (getarg("direct=", ac, av) != -1) {
E 21
I 21
#ifdef	O_DIRECT
				if ((getarg("idirect=", ac, av) != -1) ||
				    (getarg("direct=", ac, av) != -1)) {
E 21
					close(ret);
					ret = open(&av[i][len], O_RDONLY|O_DIRECT);
				}
#endif
E 15
				if (ret == -1)
					error(&av[i][len]);
				return (ret);
			}
		}
	}
D 11
	return (-1);
E 11
I 11
	return (-2);
E 11
}

I 7
#ifdef	FLUSH
D 21
flush()
E 21
I 21
int 
I 26
warning(char *s)
{
	if ((long)Label != -1) {
		fprintf(stderr, "%s: ", Label);
	}
	perror(s);
	return (-1);
}

void
E 26
flush(void)
E 21
{
	int	fd;
	struct	stat sb;
	caddr_t	where;

D 11
	if (output == NULL || (fd = open(output, 2)) == -1) 
		return (warning("No output file"));
	if (fstat(fd, &sb) == -1 || sb.st_size == 0)
		return (warning(output));
E 11
I 11
	if (output == NULL || (fd = open(output, 2)) == -1) {
		warning("No output file");
		return;
	}
	if (fstat(fd, &sb) == -1 || sb.st_size == 0) {
		warning(output);
		return;
	}
E 11
	where = mmap(0, sb.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	msync(where, sb.st_size, MS_INVALIDATE);
D 26
	/* XXX - didn't unmap */
E 26
I 26
	munmap(where, sb.st_size);
E 26
}
#endif
D 26

E 7
D 13
/*
 * utilities for timing
 */
#include "stdio.h"
#include "sys/types.h"
#include "sys/time.h"

static struct timeval t1, t2;

E 13
I 7
D 21
warning(s)
	char   *s;
E 21
I 21
int 
warning(char *s)
E 21
{
I 13
	if ((long)Label != -1) {
		fprintf(stderr, "%s: ", Label);
	}
E 13
	perror(s);
	return (-1);
}
E 26

E 7
D 21
error(s)
	char   *s;
E 21
I 21
void 
error(char *s)
E 21
{
I 13
	if ((long)Label != -1) {
		fprintf(stderr, "%s: ", Label);
	}
E 13
	perror(s);
	exit(1);
}
D 13

start() {
	gettimeofday(&t1, (struct timezone *) 0);
I 11
#ifdef	RUSAGE
	getrusage(RUSAGE_SELF, &ru_start);
#endif
E 11
}

stop() {
	gettimeofday(&t2, (struct timezone *) 0);
}

ptime(bytes) {
	ptransfer(bytes, &t1, &t2);
}
I 10

D 11
#ifndef	sun
gethostid()
{
	return (0);
}
#endif

double
getstartup()
{
	u_int	type = gethostid() >> 24;
	int	i;

	for (i = 0; startup[i].type && startup[i].type != type; i++)
		;
	if (!startup[i].type)
		printf("Warning: host type %x unknown, guessing startup.\n",
		    type);
	return (startup[i].startup);
}

E 11
E 10
double 
timespent()
{
E 6
	struct timeval td;
D 6
	
E 6
I 6

E 6
	tvsub(&td, &t2, &t1);
D 9
	return (td.tv_sec + (td.tv_usec / 1000000.) + STARTUP);
E 9
I 9
D 10
	return ((td.tv_sec + td.tv_usec/USECS_PER_SEC) + STARTUP);
E 10
I 10
D 11
	return ((td.tv_sec + td.tv_usec/USECS_PER_SEC) + getstartup());
E 11
I 11
	return (td.tv_sec + td.tv_usec/USECS_PER_SEC);
E 11
E 10
E 9
}

ptransfer(bytes, t0, t1)
	struct timeval *t0, *t1;
{
	struct timeval td;
D 6
	float s, bs;
E 6
I 6
D 12
	float   s, bs;
E 12
I 12
	double   s, bytespersec;
E 12
E 6

	tvsub(&td, t1, t0);
D 9
	s = td.tv_sec + (td.tv_usec / 1000000.);
E 9
I 9
	s = td.tv_sec + td.tv_usec/USECS_PER_SEC;
E 9
#define	nz(x)	((x) == 0 ? 1 : (x))
I 5
#define	MB	(1024*1024.0)
E 5
D 12
	bs = bytes / nz(s);
D 4
	printf("%.2f Kbytes in %.4g seconds (%.6g Kbytes/s)\n",
		bytes/1024., s, bs / 1024.);
E 4
I 4
D 5
	printf("%.0f Kbytes in %.2f seconds (%.4f MB/sec)\n",
		bytes/1024., s, bs / (1024. * 1024));
E 5
I 5
D 6
	printf("%.2f MB in %.2f seconds (%.4f MB/sec)\n", bytes/MB, s, bs / MB);
E 6
I 6
	printf("%.2f MB in %.2f seconds (%.4f MB/sec)\n", bytes / MB, s, bs / MB);
E 12
I 12
	bytespersec = bytes / nz(s);
	printf("%.2fMB in %.2f seconds (%.4f MB/s) %.2f IOP/s",
	    bytes / MB, s, bytespersec / MB, (bytes / Bsize) / s);
	if (Bsize != 8192)
		printf(" bsize=%d", Bsize);
	if (Rand != -1)
		printf(" rand=%.2fMB", Rand / MB);
	printf("\n");
E 12
E 6
E 5
E 4
}

tvsub(tdiff, t1, t0)
	struct timeval *tdiff, *t1, *t0;
{

	tdiff->tv_sec = t1->tv_sec - t0->tv_sec;
D 9
	tdiff->tv_usec = t1->tv_usec - t0->tv_usec;
	if (tdiff->tv_usec < 0)
		tdiff->tv_sec--, tdiff->tv_usec += 1000000;
E 9
I 9
	if ( t0->tv_usec > t1->tv_usec ) {
		tdiff->tv_sec--; 
		tdiff->tv_usec = (USECS_PER_SEC - t0->tv_usec) + t1->tv_usec;
	} else
		tdiff->tv_usec = t1->tv_usec - t0->tv_usec;
	
E 9
}
E 13
E 2
I 1
E 1
