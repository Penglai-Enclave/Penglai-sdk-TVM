H10806
s 00005/00005/00454
d D 1.16 02/09/29 21:53:51 staelin 17 16
c - switch from 'int' to 'size_t' for better portability to large memory 
c   machines
cC
cHfirewall.staelin.co.il
cK39656
cZ+03:00
e
s 00003/00003/00456
d D 1.15 01/11/13 16:34:33 staelin 16 15
c Add globally visible routine cp(char* src, char* dst, mode_t mode)
c which copies a file.  Required renaming a cp() routine in bw_mem
c to avoid name collisions.
cC
cK38041
e
s 00018/00053/00441
d D 1.14 01/04/02 14:48:23 staelin 15 14
c Remove old overhead calculations from bw_mem that aren't required with the new timing harness
cC
cHhpli69.hpli.hpl.hp.com
cK37714
cZ+02:00
e
s 00018/00018/00476
d D 1.13 00/07/30 11:46:02 staelin 14 13
c - Change type of "iterations" from uint64 to iter_t, which is a u_long
cC
cK27676
e
s 00002/00002/00492
d D 1.12 00/07/27 14:36:57 staelin 13 12
c - Add comment about minimum memory size
cC
cK26002
e
s 00026/00037/00468
d D 1.11 00/07/04 16:37:28 staelin 12 11
c - Fix nasty bugs in bw_mem which were causing cp and fcp to fail horribly
cC
cK21443
e
s 00047/00021/00458
d D 1.10 00/07/04 14:55:47 staelin 11 10
c - Update to incorporate new "-W <warmup>" and "-N <repetitions>" flags
cC
cK55236
e
s 00005/00004/00474
d D 1.9 00/06/25 15:33:43 staelin 10 9
c - fix bug in bw_mem which sometimes caused infinite loops
cC
cK01307
cZ+03:00
e
s 00001/00001/00477
d D 1.8 00/04/17 13:05:59 staelin 9 8
c - convert 'char c' to 'int c' for getopt()
cC
cHhpli8.hpli.hpl.hp.com
cK62859
cZ+02:00
e
s 00033/00003/00445
d D 1.7 00/03/10 18:02:23 brucec 8 7
c Make changes to properly use overhead calculations
cC
cK62942
e
s 00246/00077/00202
d D 1.6 00/03/09 18:24:53 brucec 7 6
c Make changes so it can be run with different parallelism levels.
cC
cHrx7
cK02781
cZ-05:00
e
s 00000/00001/00279
d D 1.5 98/06/29 22:37:23 lm 6 5
c Redo to compile clean with -Wall.
cC
cK13554
cZ-07:00
e
s 00002/00002/00278
d D 1.4 98/03/06 12:00:15 lm 5 4
c lint.
cK15295
e
s 00003/00003/00277
d D 1.3 97/10/31 18:06:23 lm 4 3
c use_result -> use_int/pointer
cK11953
cZ-08:00
e
s 00002/00000/00278
d D 1.2 97/10/19 23:41:50 lm 3 2
c looks like I needed to move the destination pointer too :-)
cK14878
e
s 00278/00000/00000
d D 1.1 97/07/07 23:18:00 lm 2 1
c Initial revision
cK13396
e
s 00000/00000/00000
d D 1.0 97/07/07 23:17:59 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK19200
cPsrc/bw_mem.c
cR6b79a80385eb9ec7
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
/*
D 7
 * bw_mem_wr.c - simple memory write bandwidth benchmark
E 7
I 7
 * bw_mem.c - simple memory write bandwidth benchmark
E 7
 *
D 7
 * Usage: bw_mem_wr size
 *
 * This benchmark is directly comparable to the bw_mem_rd benchmark because
 * both do a load/store and an add per word.
E 7
I 7
D 11
 * Usage: bw_mem [-P <parallelism>] size what
E 11
I 11
 * Usage: bw_mem [-P <parallelism>] [-W <warmup>] [-N <repetitions>] size what
E 11
 *        what: rd wr rdwr cp fwr frd fcp bzero bcopy
E 7
 *
 * Copyright (c) 1994-1996 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
char	*id = "$Id$";

#include "bench.h"

#define TYPE    int

/*
 * rd - 4 byte read, 32 byte stride
 * wr - 4 byte write, 32 byte stride
 * rdwr - 4 byte read followed by 4 byte write to same place, 32 byte stride
 * cp - 4 byte read then 4 byte write to different place, 32 byte stride
 * fwr - write every 4 byte word
 * frd - read every 4 byte word
 * fcp - copy every 4 byte word
 *
 * All tests do 512 byte chunks in a loop.
 *
 * XXX - do a 64bit version of this.
 */
D 7
void	rd(TYPE *buf, TYPE *lastone);
void	wr(TYPE *buf, TYPE *lastone);
void	rdwr(TYPE *buf, TYPE *lastone);
void	cp(TYPE *buf, TYPE *dst, TYPE *lastone);
void	fwr(TYPE *buf, TYPE *lastone);
void	frd(TYPE *buf, TYPE *lastone);
void	fcp(TYPE *buf, TYPE *dst, TYPE *lastone);

int
main(ac, av)
        char  **av;
E 7
I 7
D 14
void	rd(uint64 iterations, void *cookie);
void	wr(uint64 iterations, void *cookie);
void	rdwr(uint64 iterations, void *cookie);
void	cp(uint64 iterations, void *cookie);
void	fwr(uint64 iterations, void *cookie);
void	frd(uint64 iterations, void *cookie);
void	fcp(uint64 iterations, void *cookie);
void	loop_bzero(uint64 iterations, void *cookie);
void	loop_bcopy(uint64 iterations, void *cookie);
E 14
I 14
void	rd(iter_t iterations, void *cookie);
void	wr(iter_t iterations, void *cookie);
void	rdwr(iter_t iterations, void *cookie);
D 16
void	cp(iter_t iterations, void *cookie);
E 16
I 16
void	mcp(iter_t iterations, void *cookie);
E 16
void	fwr(iter_t iterations, void *cookie);
void	frd(iter_t iterations, void *cookie);
void	fcp(iter_t iterations, void *cookie);
void	loop_bzero(iter_t iterations, void *cookie);
void	loop_bcopy(iter_t iterations, void *cookie);
E 14
void	init_overhead(void *cookie);
void	init_loop(void *cookie);
void	cleanup(void *cookie);

typedef struct _state {
	double	overhead;
D 17
	int	nbytes;
E 17
I 17
	size_t	nbytes;
E 17
	int	need_buf2;
D 12
	int	isOverheadLoop;
E 12
	int	aligned;
	TYPE	*buf;
	TYPE	*buf2;
I 10
	TYPE	*buf2_orig;
E 10
	TYPE	*lastone;
I 12
D 17
	int	N;
E 17
I 17
	size_t	N;
E 17
E 12
} state_t;

I 8
void	adjusted_bandwidth(uint64 t, uint64 b, uint64 iter, double ovrhd);

E 8
int main(int ac, char **av)
E 7
{
I 7
	int	parallel = 1;
I 11
	int	warmup = 0;
	int	repetitions = TRIES;
E 11
E 7
D 17
	int	nbytes;
E 17
I 17
	size_t	nbytes;
E 17
D 7
	TYPE   *buf = 0, *buf2 = 0, *lastone;
E 7
I 7
	state_t	state;
D 9
	char	c;
E 9
I 9
	int	c;
E 9
D 8
	char	*usage = "size what [conflict]\nwhat: rd wr rdwr cp fwr frd fcp bzero bcopy\n";
E 8
I 8
D 11
	char	*usage = "[-P <parallelism>] <size> what [conflict]\nwhat: rd wr rdwr cp fwr frd fcp bzero bcopy\n";
E 11
I 11
D 13
	char	*usage = "[-P <parallelism>] [-W <warmup>] [-N <repetitions>] <size> what [conflict]\nwhat: rd wr rdwr cp fwr frd fcp bzero bcopy\n";
E 13
I 13
	char	*usage = "[-P <parallelism>] [-W <warmup>] [-N <repetitions>] <size> what [conflict]\nwhat: rd wr rdwr cp fwr frd fcp bzero bcopy\n<size> must be larger than 512";
E 13
E 11
E 8

I 15
	state.overhead = 0;

E 15
D 11
	while (( c = getopt(ac, av, "P:")) != EOF) {
E 11
I 11
	while (( c = getopt(ac, av, "P:W:N:")) != EOF) {
E 11
		switch(c) {
		case 'P':
			parallel = atoi(optarg);
			if (parallel <= 0) lmbench_usage(ac, av, usage);
			break;
I 11
		case 'W':
			warmup = atoi(optarg);
			break;
		case 'N':
			repetitions = atoi(optarg);
			break;
E 11
		default:
			lmbench_usage(ac, av, usage);
			break;
		}
	}
E 7
D 6
	double	overhead = 0;
E 6

D 7
	if (ac < 3) {
usage:		fprintf(stderr, "Usage: %s size what [conflict]\n", av[0]);
		fprintf(stderr, 
		    "what: rd wr rdwr cp fwr frd fcp bzero bcopy\n");
		exit(1);
E 7
I 7
	/* should have two, possibly three [indicates align] arguments left */
	state.aligned = state.need_buf2 = 0;
	if (optind + 3 == ac) {
		state.aligned = 1;
	} else if (optind + 2 != ac) {
		lmbench_usage(ac, av, usage);
E 7
	}
D 7
	nbytes = bytes(av[1]);
	if (nbytes < 512) {	/* this is the number of bytes in the loop */
E 7
I 7

	nbytes = state.nbytes = bytes(av[optind]);
	if (state.nbytes < 512) { /* this is the number of bytes in the loop */
E 7
D 13
		exit(1);
E 13
I 13
		lmbench_usage(ac, av, usage);
E 13
	}
D 7
        buf = (TYPE *)valloc(nbytes);
	lastone = (TYPE*)((char *)buf + nbytes - 512);
	if (!buf) {
E 7
I 7

	if (streq(av[optind+1], "cp") ||
	    streq(av[optind+1], "fcp") || streq(av[optind+1], "bcopy")) {
		state.need_buf2 = 1;
	}
		
	if (streq(av[optind+1], "rd")) {
D 11
		benchmp(init_overhead, rd, cleanup, 0, parallel, &state);
E 11
I 11
D 15
		benchmp(init_overhead, rd, cleanup, 0, parallel, 
			warmup, repetitions, &state);
E 11
		state.overhead = gettime();
		state.overhead /= get_n();
E 15
D 11
		benchmp(init_loop, rd, cleanup, 0, parallel, &state);
E 11
I 11
		benchmp(init_loop, rd, cleanup, 0, parallel, 
			warmup, repetitions, &state);
E 11
	} else if (streq(av[optind+1], "wr")) {
D 11
		benchmp(init_overhead, wr, cleanup, 0, parallel, &state);
E 11
I 11
D 15
		benchmp(init_overhead, wr, cleanup, 0, parallel, 
			warmup, repetitions, &state);
E 11
		state.overhead = gettime();
		state.overhead /= get_n();
E 15
D 11
		benchmp(init_loop, wr, cleanup, 0, parallel, &state);
E 11
I 11
		benchmp(init_loop, wr, cleanup, 0, parallel, 
			warmup, repetitions, &state);
E 11
	} else if (streq(av[optind+1], "rdwr")) {
D 11
		benchmp(init_overhead, rdwr, cleanup, 0, parallel, &state);
E 11
I 11
D 15
		benchmp(init_overhead, rdwr, cleanup, 0, parallel, 
			warmup, repetitions, &state);
E 11
		state.overhead = gettime();
		state.overhead /= get_n();
E 15
D 11
		benchmp(init_loop, rdwr, cleanup, 0, parallel, &state);
E 11
I 11
		benchmp(init_loop, rdwr, cleanup, 0, parallel, 
			warmup, repetitions, &state);
E 11
	} else if (streq(av[optind+1], "cp")) {
D 11
		benchmp(init_overhead, cp, cleanup, 0, parallel, &state);
E 11
I 11
D 15
		benchmp(init_overhead, cp, cleanup, 0, parallel, 
			warmup, repetitions, &state);
E 11
		state.overhead = gettime();
		state.overhead /= get_n();
E 15
D 11
		benchmp(init_loop, cp, cleanup, 0, parallel, &state);
E 11
I 11
D 16
		benchmp(init_loop, cp, cleanup, 0, parallel, 
E 16
I 16
		benchmp(init_loop, mcp, cleanup, 0, parallel, 
E 16
			warmup, repetitions, &state);
E 11
	} else if (streq(av[optind+1], "frd")) {
D 11
		benchmp(init_overhead, frd, cleanup, 0, parallel, &state);
E 11
I 11
D 15
		benchmp(init_overhead, frd, cleanup, 0, parallel, 
			warmup, repetitions, &state);
E 11
		state.overhead = gettime();
		state.overhead /= get_n();
E 15
D 11
		benchmp(init_loop, frd, cleanup, 0, parallel, &state);
E 11
I 11
		benchmp(init_loop, frd, cleanup, 0, parallel, 
			warmup, repetitions, &state);
E 11
	} else if (streq(av[optind+1], "fwr")) {
D 11
		benchmp(init_overhead, fwr, cleanup, 0, parallel, &state);
E 11
I 11
D 15
		benchmp(init_overhead, fwr, cleanup, 0, parallel, 
			warmup, repetitions, &state);
E 11
		state.overhead = gettime();
		state.overhead /= get_n();
E 15
D 11
		benchmp(init_loop, fwr, cleanup, 0, parallel, &state);
E 11
I 11
		benchmp(init_loop, fwr, cleanup, 0, parallel, 
			warmup, repetitions, &state);
E 11
	} else if (streq(av[optind+1], "fcp")) {
D 11
		benchmp(init_overhead, fcp, cleanup, 0, parallel, &state);
E 11
I 11
D 15
		benchmp(init_overhead, fcp, cleanup, 0, parallel, 
			warmup, repetitions, &state);
E 11
		state.overhead = gettime();
		state.overhead /= get_n();
E 15
D 11
		benchmp(init_loop, fcp, cleanup, 0, parallel, &state);
E 11
I 11
		benchmp(init_loop, fcp, cleanup, 0, parallel, 
			warmup, repetitions, &state);
E 11
	} else if (streq(av[optind+1], "bzero")) {
D 11
		benchmp(init_overhead, loop_bzero, cleanup,0,parallel, &state);
E 11
I 11
D 15
		benchmp(init_overhead, loop_bzero, cleanup, 0, parallel, 
			warmup, repetitions, &state);
E 11
		state.overhead = gettime();
		state.overhead /= get_n();
E 15
D 11
		benchmp(init_loop, loop_bzero, cleanup, 0, parallel, &state);
E 11
I 11
		benchmp(init_loop, loop_bzero, cleanup, 0, parallel, 
			warmup, repetitions, &state);
E 11
	} else if (streq(av[optind+1], "bcopy")) {
D 15
		/* XXX - if gcc inlines this the numbers could be off */
		/* But they are off in a good way - the bcopy will appear
		 * to cost around 0...
		 */
D 8
		benchmp(init_overhead, loop_bcopy, cleanup, 0, parallel, &state);
E 8
I 8
D 11
		benchmp(init_overhead, loop_bcopy, cleanup,0,parallel, &state);
E 11
I 11
		benchmp(init_overhead, loop_bcopy, cleanup, 0, parallel, 
			warmup, repetitions, &state);
E 11
E 8
		state.overhead = gettime();
		state.overhead /= get_n();
E 15
D 11
		benchmp(init_loop, loop_bcopy, cleanup, 0, parallel, &state);
E 11
I 11
		benchmp(init_loop, loop_bcopy, cleanup, 0, parallel, 
			warmup, repetitions, &state);
E 11
	} else {
		lmbench_usage(ac, av, usage);
	}
D 8
	bandwidth(nbytes, get_n() * parallel, 0);
E 8
I 8
D 15
	adjusted_bandwidth(gettime(), nbytes,
E 15
I 15
	adjusted_bandwidth(gettime(), nbytes, 
E 15
			   get_n() * parallel, state.overhead);
E 8
	return(0);
}

void init_overhead(void *cookie)
{
	state_t *state = (state_t *) cookie;
I 15
}

void init_loop(void *cookie)
{
	state_t *state = (state_t *) cookie;

E 15
        state->buf = (TYPE *)valloc(state->nbytes);
I 15
	state->buf2_orig = NULL;
E 15
D 12
	state->lastone = (TYPE*)((char *)state->buf + state->nbytes - 512);
E 12
I 12
	state->lastone = (TYPE*)state->buf - 1;
D 15
	state->N = 0;
E 15
I 15
	state->lastone = (TYPE*)((char *)state->buf + state->nbytes - 512);
	state->N = state->nbytes;

E 15
E 12
	if (!state->buf) {
E 7
		perror("malloc");
		exit(1);
	}
D 7
	if (streq(av[2], "cp") ||
	    streq(av[2], "fcp") || streq(av[2], "bcopy")) {
        	buf2 = (TYPE *)valloc(nbytes + 2048);
		if (!buf2) {
E 7
I 7
	bzero((void*)state->buf, state->nbytes);

	if (state->need_buf2 == 1) {
D 10
		state->buf2 = (TYPE *)valloc(state->nbytes + 2048);
E 10
I 10
		state->buf2_orig = state->buf2 = (TYPE *)valloc(state->nbytes + 2048);
E 10
		if (!state->buf2) {
E 7
			perror("malloc");
			exit(1);
		}
I 15

E 15
		/* default is to have stuff unaligned wrt each other */
		/* XXX - this is not well tested or thought out */
D 7
		if (ac == 3) {
			char	*tmp = (char *)buf2;
E 7
I 7
		if (state->aligned) {
			char	*tmp = (char *)state->buf2;
E 7

			tmp += 2048 - 128;
D 7
			buf2 = (TYPE *)tmp;
E 7
I 7
			state->buf2 = (TYPE *)tmp;
E 7
		}
	}
D 7
		
	bzero((void*)buf, nbytes);
	if (streq(av[2], "rd")) {
		BENCHO(rd(buf, lastone), rd(buf, 0), 0);
	} else if (streq(av[2], "wr")) {
		BENCHO(wr(buf, lastone), wr(buf, 0), 0);
	} else if (streq(av[2], "rdwr")) {
		BENCHO(rdwr(buf, lastone), rdwr(buf, 0), 0);
	} else if (streq(av[2], "cp")) {
		BENCHO(cp(buf, buf2, lastone), cp(buf, buf2, 0), 0);
	} else if (streq(av[2], "frd")) {
		BENCHO(frd(buf, lastone), frd(buf, 0), 0);
	} else if (streq(av[2], "fwr")) {
		BENCHO(fwr(buf, lastone), fwr(buf, 0), 0);
	} else if (streq(av[2], "fcp")) {
		BENCHO(fcp(buf, buf2, lastone), fcp(buf, buf2, 0), 0);
	} else if (streq(av[2], "bzero")) {
D 5
		BENCHO(bzero(buf, nbytes), bzero(buf, 1), 0);
E 5
I 5
		BENCHO(bzero((void*)buf, nbytes), bzero((void*)buf, 1), 0);
E 5
	} else if (streq(av[2], "bcopy")) {
		/* XXX - if gcc inlines this the numbers could be off */
		/* But they are off in a good way - the bcopy will appear
		 * to cost around 0...
		 */
D 5
		BENCHO(bcopy(buf, buf2, nbytes), bcopy(buf, buf2, 1), 0);
E 5
I 5
		BENCHO(bcopy((void*)buf, (void*)buf2, nbytes), bcopy((void*)buf, (void*)buf2, 1), 0);
E 5
	} else {
		goto usage;
E 7
I 7
D 12
	state->isOverheadLoop = 1;
E 12
}

D 15
void init_loop(void *cookie)
{
	state_t *state = (state_t *) cookie;
	init_overhead(state);
D 12
	state->isOverheadLoop = 0;
E 12
I 12
	state->lastone = (TYPE*)((char *)state->buf + state->nbytes - 512);
	state->N = state->nbytes;
E 12
}

E 15
void cleanup(void *cookie)
{
	state_t *state = (state_t *) cookie;
	free(state->buf);
D 15
	if (state->need_buf2 == 1) {
D 10
		free(state->buf2);
E 10
I 10
		free(state->buf2_orig);
E 10
E 7
	}
E 15
I 15
	if (state->buf2_orig) free(state->buf2_orig);
E 15
D 7
	bandwidth(nbytes, get_n(), 0);
	return(0);
E 7
}

void
D 7
rd(register TYPE *p, register TYPE *lastone)
E 7
I 7
D 14
rd(uint64 iterations, void *cookie)
E 14
I 14
rd(iter_t iterations, void *cookie)
E 14
E 7
{	
I 7
	state_t *state = (state_t *) cookie;
	register TYPE *lastone = state->lastone;
E 7
	register int sum = 0;

D 7
	while (p <= lastone) {
E 7
I 7
D 12
	if (state->isOverheadLoop == 1)
		lastone = state->buf - 1;

E 12
	while (iterations-- > 0) {
	    register TYPE *p = state->buf;
	    while (p <= lastone) {
E 7
		sum += 
#define	DOIT(i)	p[i]+
		DOIT(0) DOIT(4) DOIT(8) DOIT(12) DOIT(16) DOIT(20) DOIT(24)
		DOIT(28) DOIT(32) DOIT(36) DOIT(40) DOIT(44) DOIT(48) DOIT(52)
		DOIT(56) DOIT(60) DOIT(64) DOIT(68) DOIT(72) DOIT(76)
		DOIT(80) DOIT(84) DOIT(88) DOIT(92) DOIT(96) DOIT(100)
		DOIT(104) DOIT(108) DOIT(112) DOIT(116) DOIT(120) 
		p[124];
		p +=  128;
I 7
	    }
E 7
	}
D 4
	use_result((uint64)sum);
E 4
I 4
	use_int(sum);
E 4
}
#undef	DOIT

void
D 7
wr(register TYPE *p, register TYPE *lastone)
E 7
I 7
D 14
wr(uint64 iterations, void *cookie)
E 14
I 14
wr(iter_t iterations, void *cookie)
E 14
E 7
{	
D 7
	while (p <= lastone) {
E 7
I 7
	state_t *state = (state_t *) cookie;
	register TYPE *lastone = state->lastone;
D 12
	if (state->isOverheadLoop == 1)
		lastone = state->buf - 1;
E 12

	while (iterations-- > 0) {
	    register TYPE *p = state->buf;
	    while (p <= lastone) {
E 7
#define	DOIT(i)	p[i] = 1;
		DOIT(0) DOIT(4) DOIT(8) DOIT(12) DOIT(16) DOIT(20) DOIT(24)
		DOIT(28) DOIT(32) DOIT(36) DOIT(40) DOIT(44) DOIT(48) DOIT(52)
		DOIT(56) DOIT(60) DOIT(64) DOIT(68) DOIT(72) DOIT(76)
		DOIT(80) DOIT(84) DOIT(88) DOIT(92) DOIT(96) DOIT(100)
		DOIT(104) DOIT(108) DOIT(112) DOIT(116) DOIT(120) DOIT(124);
		p +=  128;
I 7
	    }
E 7
	}
}
#undef	DOIT

void
D 7
rdwr(register TYPE *p, register TYPE *lastone)
E 7
I 7
D 14
rdwr(uint64 iterations, void *cookie)
E 14
I 14
rdwr(iter_t iterations, void *cookie)
E 14
E 7
{	
I 7
	state_t *state = (state_t *) cookie;
	register TYPE *lastone = state->lastone;
E 7
	register int sum = 0;

D 7
	while (p <= lastone) {
E 7
I 7
D 12
	if (state->isOverheadLoop == 1)
		lastone = state->buf - 1;

E 12
	while (iterations-- > 0) {
	    register TYPE *p = state->buf;
	    while (p <= lastone) {
E 7
#define	DOIT(i)	sum += p[i]; p[i] = 1;
		DOIT(0) DOIT(4) DOIT(8) DOIT(12) DOIT(16) DOIT(20) DOIT(24)
		DOIT(28) DOIT(32) DOIT(36) DOIT(40) DOIT(44) DOIT(48) DOIT(52)
		DOIT(56) DOIT(60) DOIT(64) DOIT(68) DOIT(72) DOIT(76)
		DOIT(80) DOIT(84) DOIT(88) DOIT(92) DOIT(96) DOIT(100)
		DOIT(104) DOIT(108) DOIT(112) DOIT(116) DOIT(120) DOIT(124);
		p +=  128;
I 7
	    }
E 7
	}
D 4
	use_result((uint64)sum);
E 4
I 4
	use_int(sum);
E 4
}
#undef	DOIT

void
D 7
cp(register TYPE *p, register TYPE *dst, register TYPE *lastone)
E 7
I 7
D 14
cp(uint64 iterations, void *cookie)
E 14
I 14
D 16
cp(iter_t iterations, void *cookie)
E 16
I 16
mcp(iter_t iterations, void *cookie)
E 16
E 14
E 7
{	
D 7
	while (p <= lastone) {
E 7
I 7
	state_t *state = (state_t *) cookie;
	register TYPE *lastone = state->lastone;
D 12

	if (state->isOverheadLoop == 1)
		lastone = state->buf - 1;
E 12
I 12
	TYPE* p_save = NULL;
E 12

	while (iterations-- > 0) {
	    register TYPE *p = state->buf;
	    register TYPE *dst = state->buf2;
D 10
	    while (p <= lastone) {
E 10
I 10
D 12
	    while (dst <= lastone) {
E 12
I 12
	    while (p <= lastone) {
E 12
E 10
E 7
#define	DOIT(i)	dst[i] = p[i];
		DOIT(0) DOIT(4) DOIT(8) DOIT(12) DOIT(16) DOIT(20) DOIT(24)
		DOIT(28) DOIT(32) DOIT(36) DOIT(40) DOIT(44) DOIT(48) DOIT(52)
		DOIT(56) DOIT(60) DOIT(64) DOIT(68) DOIT(72) DOIT(76)
		DOIT(80) DOIT(84) DOIT(88) DOIT(92) DOIT(96) DOIT(100)
		DOIT(104) DOIT(108) DOIT(112) DOIT(116) DOIT(120) DOIT(124);
		p += 128;
I 3
		dst += 128;
I 7
	    }
I 12
	    p_save = p;
E 12
E 7
E 3
	}
I 12
	use_pointer(p_save);
E 12
}
#undef	DOIT

void
D 7
fwr(register TYPE *p, register TYPE *lastone)
E 7
I 7
D 14
fwr(uint64 iterations, void *cookie)
E 14
I 14
fwr(iter_t iterations, void *cookie)
E 14
E 7
{	
D 7
	while (p <= lastone) {
E 7
I 7
	state_t *state = (state_t *) cookie;
	register TYPE *lastone = state->lastone;
D 12
	if (state->isOverheadLoop == 1)
		lastone = state->buf - 1;
E 12
I 12
	TYPE* p_save = NULL;
E 12

	while (iterations-- > 0) {
	    register TYPE *p = state->buf;
	    while (p <= lastone) {
E 7
#define	DOIT(i)	p[i]=
		DOIT(0) DOIT(1) DOIT(2) DOIT(3) DOIT(4) DOIT(5) DOIT(6)
		DOIT(7) DOIT(8) DOIT(9) DOIT(10) DOIT(11) DOIT(12)
		DOIT(13) DOIT(14) DOIT(15) DOIT(16) DOIT(17) DOIT(18)
		DOIT(19) DOIT(20) DOIT(21) DOIT(22) DOIT(23) DOIT(24)
		DOIT(25) DOIT(26) DOIT(27) DOIT(28) DOIT(29) DOIT(30)
		DOIT(31) DOIT(32) DOIT(33) DOIT(34) DOIT(35) DOIT(36)
		DOIT(37) DOIT(38) DOIT(39) DOIT(40) DOIT(41) DOIT(42)
		DOIT(43) DOIT(44) DOIT(45) DOIT(46) DOIT(47) DOIT(48)
		DOIT(49) DOIT(50) DOIT(51) DOIT(52) DOIT(53) DOIT(54)
		DOIT(55) DOIT(56) DOIT(57) DOIT(58) DOIT(59) DOIT(60)
		DOIT(61) DOIT(62) DOIT(63) DOIT(64) DOIT(65) DOIT(66)
		DOIT(67) DOIT(68) DOIT(69) DOIT(70) DOIT(71) DOIT(72)
		DOIT(73) DOIT(74) DOIT(75) DOIT(76) DOIT(77) DOIT(78)
		DOIT(79) DOIT(80) DOIT(81) DOIT(82) DOIT(83) DOIT(84)
		DOIT(85) DOIT(86) DOIT(87) DOIT(88) DOIT(89) DOIT(90)
		DOIT(91) DOIT(92) DOIT(93) DOIT(94) DOIT(95) DOIT(96)
		DOIT(97) DOIT(98) DOIT(99) DOIT(100) DOIT(101) DOIT(102)
		DOIT(103) DOIT(104) DOIT(105) DOIT(106) DOIT(107)
		DOIT(108) DOIT(109) DOIT(110) DOIT(111) DOIT(112)
		DOIT(113) DOIT(114) DOIT(115) DOIT(116) DOIT(117)
		DOIT(118) DOIT(119) DOIT(120) DOIT(121) DOIT(122)
		DOIT(123) DOIT(124) DOIT(125) DOIT(126) DOIT(127) 1;
		p += 128;
I 7
	    }
I 12
	    p_save = p;
E 12
E 7
	}
I 12
	use_pointer(p_save);
E 12
}
#undef	DOIT

void
D 7
frd(register TYPE *p, register TYPE *lastone)
E 7
I 7
D 14
frd(uint64 iterations, void *cookie)
E 14
I 14
frd(iter_t iterations, void *cookie)
E 14
E 7
{	
I 7
	state_t *state = (state_t *) cookie;
E 7
	register int sum = 0;
D 7

	while (p <= lastone) {
E 7
I 7
	register TYPE *lastone = state->lastone;
D 12
	if (state->isOverheadLoop == 1)
		lastone = state->buf - 1;
E 12

	while (iterations-- > 0) {
	    register TYPE *p = state->buf;
	    while (p <= lastone) {
E 7
		sum +=
#define	DOIT(i)	p[i]+
		DOIT(0) DOIT(1) DOIT(2) DOIT(3) DOIT(4) DOIT(5) DOIT(6)
		DOIT(7) DOIT(8) DOIT(9) DOIT(10) DOIT(11) DOIT(12)
		DOIT(13) DOIT(14) DOIT(15) DOIT(16) DOIT(17) DOIT(18)
		DOIT(19) DOIT(20) DOIT(21) DOIT(22) DOIT(23) DOIT(24)
		DOIT(25) DOIT(26) DOIT(27) DOIT(28) DOIT(29) DOIT(30)
		DOIT(31) DOIT(32) DOIT(33) DOIT(34) DOIT(35) DOIT(36)
		DOIT(37) DOIT(38) DOIT(39) DOIT(40) DOIT(41) DOIT(42)
		DOIT(43) DOIT(44) DOIT(45) DOIT(46) DOIT(47) DOIT(48)
		DOIT(49) DOIT(50) DOIT(51) DOIT(52) DOIT(53) DOIT(54)
		DOIT(55) DOIT(56) DOIT(57) DOIT(58) DOIT(59) DOIT(60)
		DOIT(61) DOIT(62) DOIT(63) DOIT(64) DOIT(65) DOIT(66)
		DOIT(67) DOIT(68) DOIT(69) DOIT(70) DOIT(71) DOIT(72)
		DOIT(73) DOIT(74) DOIT(75) DOIT(76) DOIT(77) DOIT(78)
		DOIT(79) DOIT(80) DOIT(81) DOIT(82) DOIT(83) DOIT(84)
		DOIT(85) DOIT(86) DOIT(87) DOIT(88) DOIT(89) DOIT(90)
		DOIT(91) DOIT(92) DOIT(93) DOIT(94) DOIT(95) DOIT(96)
		DOIT(97) DOIT(98) DOIT(99) DOIT(100) DOIT(101) DOIT(102)
		DOIT(103) DOIT(104) DOIT(105) DOIT(106) DOIT(107)
		DOIT(108) DOIT(109) DOIT(110) DOIT(111) DOIT(112)
		DOIT(113) DOIT(114) DOIT(115) DOIT(116) DOIT(117)
		DOIT(118) DOIT(119) DOIT(120) DOIT(121) DOIT(122)
		DOIT(123) DOIT(124) DOIT(125) DOIT(126) p[127];
		p += 128;
I 7
	    }
E 7
	}
D 4
	use_result((uint64)sum);
E 4
I 4
	use_int(sum);
E 4
}
#undef	DOIT

void
D 7
fcp(register TYPE *p, register TYPE *dst, register TYPE *lastone)
E 7
I 7
D 14
fcp(uint64 iterations, void *cookie)
E 14
I 14
fcp(iter_t iterations, void *cookie)
E 14
E 7
{	
D 7
	while (p <= lastone) {
E 7
I 7
	state_t *state = (state_t *) cookie;
	register TYPE *lastone = state->lastone;
D 12
	if (state->isOverheadLoop == 1)
		lastone = state->buf - 1;
E 12

	while (iterations-- > 0) {
	    register TYPE *p = state->buf;
	    register TYPE *dst = state->buf2;
D 10
	    while (p <= lastone) {
E 10
I 10
D 12
	    while (dst <= lastone) {
E 12
I 12
	    while (p <= lastone) {
E 12
E 10
E 7
#define	DOIT(i)	dst[i]=p[i];
		DOIT(0) DOIT(1) DOIT(2) DOIT(3) DOIT(4) DOIT(5) DOIT(6)
		DOIT(7) DOIT(8) DOIT(9) DOIT(10) DOIT(11) DOIT(12)
		DOIT(13) DOIT(14) DOIT(15) DOIT(16) DOIT(17) DOIT(18)
		DOIT(19) DOIT(20) DOIT(21) DOIT(22) DOIT(23) DOIT(24)
		DOIT(25) DOIT(26) DOIT(27) DOIT(28) DOIT(29) DOIT(30)
		DOIT(31) DOIT(32) DOIT(33) DOIT(34) DOIT(35) DOIT(36)
		DOIT(37) DOIT(38) DOIT(39) DOIT(40) DOIT(41) DOIT(42)
		DOIT(43) DOIT(44) DOIT(45) DOIT(46) DOIT(47) DOIT(48)
		DOIT(49) DOIT(50) DOIT(51) DOIT(52) DOIT(53) DOIT(54)
		DOIT(55) DOIT(56) DOIT(57) DOIT(58) DOIT(59) DOIT(60)
		DOIT(61) DOIT(62) DOIT(63) DOIT(64) DOIT(65) DOIT(66)
		DOIT(67) DOIT(68) DOIT(69) DOIT(70) DOIT(71) DOIT(72)
		DOIT(73) DOIT(74) DOIT(75) DOIT(76) DOIT(77) DOIT(78)
		DOIT(79) DOIT(80) DOIT(81) DOIT(82) DOIT(83) DOIT(84)
		DOIT(85) DOIT(86) DOIT(87) DOIT(88) DOIT(89) DOIT(90)
		DOIT(91) DOIT(92) DOIT(93) DOIT(94) DOIT(95) DOIT(96)
		DOIT(97) DOIT(98) DOIT(99) DOIT(100) DOIT(101) DOIT(102)
		DOIT(103) DOIT(104) DOIT(105) DOIT(106) DOIT(107)
		DOIT(108) DOIT(109) DOIT(110) DOIT(111) DOIT(112)
		DOIT(113) DOIT(114) DOIT(115) DOIT(116) DOIT(117)
		DOIT(118) DOIT(119) DOIT(120) DOIT(121) DOIT(122)
		DOIT(123) DOIT(124) DOIT(125) DOIT(126) DOIT(127)
		p += 128;
I 3
		dst += 128;
I 7
	    }
	}
}

void
D 14
loop_bzero(uint64 iterations, void *cookie)
E 14
I 14
loop_bzero(iter_t iterations, void *cookie)
E 14
{	
	state_t *state = (state_t *) cookie;
	register TYPE *p = state->buf;
	register TYPE *dst = state->buf2;
D 12
	register int  nbytes = state->nbytes;
	if (state->isOverheadLoop == 1)
		nbytes = 1;
E 12
I 12
D 17
	register int  N = state->N;
E 17
I 17
	register size_t  N = state->N;
E 17

E 12
	while (iterations-- > 0) {
D 12
		bzero(p, nbytes);
E 12
I 12
		bzero(p, N);
E 12
	}
}
I 15

E 15
void
D 14
loop_bcopy(uint64 iterations, void *cookie)
E 14
I 14
loop_bcopy(iter_t iterations, void *cookie)
E 14
{	
	state_t *state = (state_t *) cookie;
	register TYPE *p = state->buf;
	register TYPE *dst = state->buf2;
D 12
	register int  nbytes = state->nbytes;
	if (state->isOverheadLoop == 1)
		nbytes = 1;
E 12
I 12
D 17
	register int  N = state->N;
E 17
I 17
	register size_t  N = state->N;
E 17

E 12
	while (iterations-- > 0) {
D 12
		bcopy(p,dst,nbytes);
E 12
I 12
		bcopy(p,dst,N);
E 12
E 7
E 3
	}
}
I 7

I 8
/*
 * Almost like bandwidth() in lib_timing.c, but we need to adjust
 * bandwidth based upon loop overhead.
 */
void adjusted_bandwidth(uint64 time, uint64 bytes, uint64 iter, double overhd)
{
D 12
#define MB	(1000 * 1000.0)
E 12
I 12
#define MB	(1000. * 1000.)
E 12
	extern FILE *ftiming;
D 12
	double secs = time / 1000000.0;
E 12
I 12
	double secs = ((double)time / (double)iter - overhd) / 1000000.0;
E 12
	double mb;
	
D 12
	secs /= iter;
E 12
        mb = bytes / MB;
D 12
	secs = secs - ( overhd / 1000000.0 );
E 12
I 12

	if (secs <= 0.)
		return;
E 12

        if (!ftiming) ftiming = stderr;
D 12
	if (mb < 1) {
E 12
I 12
	if (mb < 1.) {
E 12
		(void) fprintf(ftiming, "%.6f ", mb);
	} else {
		(void) fprintf(ftiming, "%.2f ", mb);
	}
D 12
	if (mb / secs < 1) {
E 12
I 12
	if (mb / secs < 1.) {
E 12
		(void) fprintf(ftiming, "%.6f\n", mb/secs);
	} else {
		(void) fprintf(ftiming, "%.2f\n", mb/secs);
	}
}
I 15


E 15
E 8
E 7
E 2
I 1
E 1
