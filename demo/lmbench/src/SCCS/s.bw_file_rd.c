H54363
s 00000/00006/00181
d D 1.23 02/09/29 22:12:26 staelin 25 23
i 24
c - Merge changes with 32-bit size changes
cC
cHfirewall.staelin.co.il
cK47259
cM24
e
s 00015/00012/00191
d D 1.21.1.1 02/09/29 21:53:51 staelin 24 22
c - switch from 'int' to 'size_t' for better portability to large memory 
c   machines
cC
cHfirewall.staelin.co.il
cK51672
cZ+03:00
e
s 00012/00037/00166
d D 1.22 02/09/20 09:34:01 staelin 23 22
c - switch to using new bread() utility to read data into CPU
cC
cK41273
cZ+03:00
e
s 00041/00009/00162
d D 1.21 01/11/13 16:36:32 staelin 22 21
c Add ability for child processes in file-related benchmarks to each
c have their own file, as it sometimes makes a difference whether you
c measure N processes beating on a single file or on N independent
c files.
cC
cHhpli69.hpli.hpl.hp.com
cK46551
cZ+02:00
e
s 00002/00002/00169
d D 1.20 00/07/30 11:46:01 staelin 21 20
c - Change type of "iterations" from uint64 to iter_t, which is a u_long
cC
cK59390
e
s 00013/00005/00158
d D 1.19 00/07/04 14:55:47 staelin 20 19
c - Update to incorporate new "-W <warmup>" and "-N <repetitions>" flags
cC
cHhpli8.hpli.hpl.hp.com
cK59204
cZ+03:00
e
s 00072/00031/00091
d D 1.18 00/03/09 18:24:53 brucec 19 18
c Make changes so it can be run with different parallelism levels.
cC
cHrx7
cK38845
cZ-05:00
e
s 00003/00001/00119
d D 1.17 98/06/29 22:37:25 lm 18 17
c Redo to compile clean with -Wall.
cC
cK12743
cZ-07:00
e
s 00001/00001/00119
d D 1.16 97/10/31 18:06:23 lm 17 16
c use_result -> use_int/pointer
cK11105
cZ-08:00
e
s 00001/00001/00119
d D 1.15 97/10/19 23:45:25 lm 16 15
c 64bit -> 32bit
cK11445
e
s 00042/00045/00078
d D 1.14 97/06/25 10:25:01 lm 15 14
c 64 bit types
cK11668
e
s 00002/00000/00121
d D 1.13 97/06/19 13:51:14 lm 14 13
c margo stuff
cK17327
e
s 00001/00001/00120
d D 1.12 97/06/16 19:05:50 lm 13 12
c lint
cK15716
e
s 00017/00016/00104
d D 1.11 97/06/13 20:28:08 lm 12 11
c protos
cK15159
e
s 00049/00048/00071
d D 1.10 97/06/12 21:30:06 lm 11 10
c new bench.h macros.
cK15079
e
s 00003/00002/00116
d D 1.9 97/04/23 22:43:05 lm 10 9
c lint.
cK22051
cZ-07:00
e
s 00034/00018/00084
d D 1.8 96/11/13 16:09:37 lm 9 8
c make the loop do 128 load/stores
c add the option to time open to close
cK21445
e
s 00008/00035/00094
d D 1.7 96/11/11 03:36:51 lm 8 7
c Auto adjusting changes.
cK32472
e
s 00017/00003/00112
d D 1.6 96/11/08 17:50:46 lm 7 6
c gcc -Wall cleanup
c clear the buffer (probably to allocate it on Linux).
cK11845
cZ-08:00
e
s 00076/00042/00039
d D 1.5 96/07/27 00:51:29 lm 6 5
c Rewacked to support sizes down to 8K or so with relatively accurate
c results. I have not yet factored out the read overhead and
c probably won't.
cK45231
e
s 00000/00002/00081
d D 1.4 96/05/30 00:33:07 lm 5 4
c no what strings
cK62413
cZ-07:00
e
s 00002/00002/00081
d D 1.3 96/01/24 17:09:19 lm 4 3
c Make everything use XFERSIZE
cK64494
e
s 00003/00001/00080
d D 1.2 95/03/10 18:19:56 lm 3 2
c lint
cK63942
e
s 00081/00000/00000
d D 1.1 94/11/18 00:49:48 lm 2 1
c Initial revision
cK62658
e
s 00000/00000/00000
d D 1.0 94/11/18 00:49:47 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK42959
cPsrc/bw_file_rd.c
cR7d6e949af5846971
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
I 2
/*
 * bw_file_rd.c - time reading & summing of a file
 *
D 19
 * Usage: bw_file_rd size file
E 19
I 19
D 20
 * Usage: bw_file_rd [-P <parallelism] size file
E 20
I 20
 * Usage: bw_file_rd [-P <parallelism] [-W <warmup>] [-N <repetitions>] size file
E 20
E 19
 *
D 6
 * The intent is that the file is in memory, so run this twice or more,
 * and report only the best numbers.  Disk benchmarking is done with lmdd.
E 6
I 6
 * The intent is that the file is in memory.
 * Disk benchmarking is done with lmdd.
E 6
 *
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
char	*id = "$Id$\n";

I 7
D 8
#include	<fcntl.h>	/* for open() */
E 8
I 8
D 11
#include "timing.h"
E 11
#include "bench.h"
D 11
#include <fcntl.h>	/* for open() */
E 11
E 8

E 7
D 8
#include "timing.c"

E 8
D 7

E 7
D 19
#define	CHK(x)		if ((int)(x) == -1) { perror("x"); exit(1); }
E 19
I 19
#define	CHK(x)		if ((int)(x) == -1) { perror(#x); exit(1); }
E 19
I 18
#ifndef	MIN
E 18
#define	MIN(a, b)	((a) < (b) ? (a) : (b))
I 18
#endif
E 18
I 6
D 15
#if (XFERSIZE != 64*1024) 
#	include	"Bad XFERSIZE, should be 64K"
#endif
E 15
E 6

I 9
D 15
#define	TYPE	unsigned int
E 15
I 15
D 16
#define	TYPE	uint64
E 16
I 16
#define	TYPE	int
E 16
E 15
#define	MINSZ	(sizeof(TYPE) * 128)

E 9
I 6
D 11
/*
 * Globals so that there isn't the calling overhead.
 */
int	fd;		/* fd for I/O */
E 11
D 15
int	count;		/* bytes to move (can't be modified) */
E 15
D 9
char	*buf;		/* do the I/O here */
E 9
I 9
D 23
TYPE	*buf;		/* do the I/O here */
I 15
TYPE	*lastone;	/* I/O ends here + MINSZ */
E 23
I 23
void	*buf;		/* do the I/O here */
E 23
E 15
E 9
D 24
int	xfersize;	/* do it in units of this */
I 15
int	count;		/* bytes to move (can't be modified) */
E 24
I 24
size_t	xfersize;	/* do it in units of this */
size_t	count;		/* bytes to move (can't be modified) */
E 24
E 15

E 6
I 3
D 11
int
E 3
main(ac, av)
D 3
	char **av;
E 3
I 3
	char  **av;
E 11
I 11
D 15

E 15
D 12
time_with_open(char *file)
E 11
E 3
{
D 6
	int n, j, size, fd;
D 4
	char	buf[1024*64];
E 4
I 4
	char	*buf = valloc(XFERSIZE);
E 4
	unsigned int sum, *p;
E 6
I 6
D 11
	int	i, N;
D 8
	float	adj;
E 8
I 7
	int	doit();
E 11
I 11
	int	fd = open(file, 0);
E 11
E 7
E 6

D 5
	write(2, id, strlen(id));

E 5
D 11
	if (ac != 3) {
D 6
		fprintf(stderr, "Usage: %s size file\n", av[0]);
E 6
I 6
D 7
usage:		fprintf(stderr, "Usage: %s size file, min size=%u\n",
E 7
I 7
		fprintf(stderr, "Usage: %s size file, min size=%u\n",
E 7
		    av[0], XFERSIZE);
E 6
		exit(1);
	}
D 6
	size = bytes(av[1]);
E 6
I 6
	if (sizeof(int) != 4) {
		exit (1);
	}
	count = bytes(av[1]);
D 9
	if (count < 128) {
E 9
I 9
	if (count < MINSZ) {
E 9
		exit(1);	/* I want this to be quiet */
	}
	if (count < XFERSIZE) {
		xfersize = count;
	} else {
		xfersize = XFERSIZE;
	}
D 9
	buf = valloc(XFERSIZE);
E 9
I 9
	buf = (TYPE *)valloc(XFERSIZE);
E 9
I 7
	bzero(buf, XFERSIZE);
E 7
E 6
	CHK(fd = open(av[2], 0));
D 6
	start();
E 6
I 6
	doit();
E 11
I 11
	doit(fd);
E 11
I 9
	close(fd);
D 11
#ifdef	TIME_OPEN2CLOSE
E 9
D 8
	N = 0;
	do {
		if (!N) {
			N = 1;
		} else {
			/*
			 * Adjust the amount of time proportional to how
			 * far we need to go.  We want ENOUGH/i to be ~1.
I 7
			 *
			 * For systems with low resolution clocks, i can
			 * be 0 or very close to 0.  We don't know how 
			 * much time we spent, it could be anywhere from
			 * 1 to 9999 usecs.  We pretend it was 1000 usecs.
			 * The 129 value is because some systems bump the
			 * timeval each time you call gettimeofday().
E 7
			 */
I 7
			if (i <= 129) {
				i = 1000;
			}
E 7
			adj = (ENOUGH * 1.5)/i;
D 7
			/* printf("N=%d adjust=%.2f\n", N, adj); */
E 7
I 7
			/* printf("N=%d i=%d adjust=%.5f\n", N, i, adj); */
E 7
			N *= adj;
		}
		start();
		for (i = 0; i < N; ++i) {
			lseek(fd, 0, 0);
			doit();
		}
	} while ((i = stop()) < ENOUGH);
	divide(N);
	bandwidth(count, 0);
E 8
I 8
	LOOP_FIRST(N, i, ENOUGH);
I 9
	CHK(fd = open(av[2], 0));
	doit();
	close(fd);
	LOOP_LAST(N, i, ENOUGH);
#else	
	CHK(fd = open(av[2], 0));
	LOOP_FIRST(N, i, ENOUGH);
E 11
I 11
}

time_io_only(int fd)
{
E 11
E 9
	lseek(fd, 0, 0);
D 11
	doit();
	LOOP_LAST(N, i, ENOUGH);
I 9
	close(fd);
#endif
E 9
	bandwidth(count, N, 0);
E 8
	return (0);
E 11
I 11
	doit(fd);
E 11
}

D 9
/*
 * xfersize must be multiples of 32*4 == 128.
 */
E 9
I 7
int
E 12
I 12
D 19
void
E 12
E 7
D 11
doit()
E 11
I 11
doit(int fd)
E 19
I 19
typedef struct _state {
	char filename[256];
	int fd;
I 22
	int clone;
E 22
} state_t;

void doit(int fd)
E 19
E 11
{
D 10
	int	size, n, j, loop;
E 10
I 10
D 15
	int	size, n;
E 10
D 9
	unsigned int sum, *p;
E 9
I 9
	TYPE	sum, *p, *lastone;
E 15
I 15
D 18
	int	sum, size;
E 18
I 18
D 23
D 24
	int	sum = 0, size;
E 24
I 24
	int	sum = 0;
	size_t	size, chunk;
E 24
E 18
	register TYPE *p, *end;
E 23
I 23
D 25
	int	size;
E 25
E 23
E 15
E 9

D 19

E 19
D 9
	loop = xfersize / 128;
E 9
I 9
D 15
	lastone = (TYPE*)((char*)buf + xfersize - MINSZ);
E 15
E 9
	size = count;
I 24
	chunk = xfersize;
E 24
E 6
D 15
	while (size > 0) {
D 4
		CHK(n = read(fd, buf, sizeof(buf)));
E 4
I 4
D 6
		CHK(n = read(fd, buf, XFERSIZE));
E 4
		if (n < sizeof(buf)) {
E 6
I 6
		CHK(n = read(fd, buf, xfersize));
		if (n < xfersize) {
E 15
I 15
D 23
	end = lastone;
E 23
	while (size >= 0) {
D 24
		if (read(fd, buf, MIN(size, xfersize)) <= 0) {
E 24
I 24
		if (size < chunk) chunk = size;
		if (read(fd, buf, MIN(size, chunk)) <= 0) {
E 24
E 15
E 6
			break;
		}
I 14
D 15
#ifndef	MARGO
E 14
D 6
#define	SIXTEEN	sum += p[0]+p[1]+p[2]+p[3]+p[4]+p[5]+p[6]+p[7]+p[8]+p[9]+ \
		p[10]+p[11]+p[12]+p[13]+p[14]+p[15]; p += 16;
#define	SIXTYFOUR	SIXTEEN SIXTEEN SIXTEEN SIXTEEN
		for (p=(unsigned int*)buf, j=0; j < 64; ++j) {
E 6
I 6
D 9
#define	LOOP	sum += p[0]+p[1]+p[2]+p[3]+p[4]+p[5]+p[6]+p[7]+p[8]+p[9]+ \
		p[10]+p[11]+p[12]+p[13]+p[14]+p[15]+p[16]+p[17]+p[18]+p[19]+ \
		p[20]+p[21]+p[22]+p[23]+p[24]+p[25]+p[26]+p[27]+p[28]+p[29]+ \
		p[30]+p[31]; p += 32;

		for (p=(unsigned int*)buf, j = loop; j; j--) {
E 6
			/*
			 * This assumes that sizeof(int) == 4
			 */
D 6
			SIXTYFOUR
			SIXTYFOUR
			SIXTYFOUR
			SIXTYFOUR	/* 256 * 4 = 1K; * 64 in loop = 64K */
E 6
I 6
			LOOP;
E 9
I 9
		for (p = buf; p <= lastone; ) {
			sum += p[0]+p[1]+p[2]+p[3]+p[4]+p[5]+p[6]+p[7]+p[8]+p[9]+
			p[10]+p[11]+p[12]+p[13]+p[14]+p[15]+p[16]+p[17]+p[18]+p[19]+ 
			p[20]+p[21]+p[22]+p[23]+p[24]+p[25]+p[26]+p[27]+p[28]+p[29]+
			p[30]+p[31]+p[32]+p[33]+p[34]+p[35]+p[36]+p[37]+p[38]+p[39]+
			p[40]+p[41]+p[42]+p[43]+p[44]+p[45]+p[46]+p[47]+p[48]+p[49]+
			p[50]+p[51]+p[52]+p[53]+p[54]+p[55]+p[56]+p[57]+p[58]+p[59]+
			p[60]+p[61]+p[62]+p[63]+p[64]+p[65]+p[66]+p[67]+p[68]+p[69]+
			p[70]+p[71]+p[72]+p[73]+p[74]+p[75]+p[76]+p[77]+p[78]+p[79]+
			p[80]+p[81]+p[82]+p[83]+p[84]+p[85]+p[86]+p[87]+p[88]+p[89]+
			p[90]+p[91]+p[92]+p[93]+p[94]+p[95]+p[96]+p[97]+p[98]+p[99]+
			p[100]+p[101]+p[102]+p[103]+p[104]+p[105]+p[106]+p[107]+p[108]+p[109]+
			p[110]+p[111]+p[112]+p[113]+p[114]+p[115]+p[116]+p[117]+p[118]+p[119]+
			p[120]+p[121]+p[122]+p[123]+p[124]+p[125]+p[126]+p[127];
E 15
I 15
D 23
		for (p = buf; p <= end; ) {
			sum +=
			p[0]+p[1]+p[2]+p[3]+p[4]+p[5]+p[6]+p[7]+
			p[8]+p[9]+p[10]+p[11]+p[12]+p[13]+p[14]+
			p[15]+p[16]+p[17]+p[18]+p[19]+p[20]+p[21]+
			p[22]+p[23]+p[24]+p[25]+p[26]+p[27]+p[28]+
			p[29]+p[30]+p[31]+p[32]+p[33]+p[34]+p[35]+
			p[36]+p[37]+p[38]+p[39]+p[40]+p[41]+p[42]+
			p[43]+p[44]+p[45]+p[46]+p[47]+p[48]+p[49]+
			p[50]+p[51]+p[52]+p[53]+p[54]+p[55]+p[56]+
			p[57]+p[58]+p[59]+p[60]+p[61]+p[62]+p[63]+
			p[64]+p[65]+p[66]+p[67]+p[68]+p[69]+p[70]+
			p[71]+p[72]+p[73]+p[74]+p[75]+p[76]+p[77]+
			p[78]+p[79]+p[80]+p[81]+p[82]+p[83]+p[84]+
			p[85]+p[86]+p[87]+p[88]+p[89]+p[90]+p[91]+
			p[92]+p[93]+p[94]+p[95]+p[96]+p[97]+p[98]+
			p[99]+p[100]+p[101]+p[102]+p[103]+p[104]+
			p[105]+p[106]+p[107]+p[108]+p[109]+p[110]+
			p[111]+p[112]+p[113]+p[114]+p[115]+p[116]+
			p[117]+p[118]+p[119]+p[120]+p[121]+p[122]+
			p[123]+p[124]+p[125]+p[126]+p[127];
E 15
			p += 128;
E 9
E 6
		}
E 23
I 23
		bread(buf, MIN(size, xfersize));
E 23
I 14
D 15
#endif
E 14
		size -= n;
E 15
I 15
D 24
		size -= xfersize;
E 24
I 24
		size -= chunk;
E 24
E 15
	}
D 6
	stop();
	bandwidth(bytes(av[1]), 0);
I 3
	return (0);
E 6
I 6
D 10
	return (sum);
E 10
I 10
D 17
	use_result(sum);
E 17
I 17
D 23
	use_int(sum);
E 23
E 17
D 12
	return (0);
E 12
E 10
E 6
E 3
}
I 11

I 22
void
initialize(void* cookie)
{
	state_t	*state = (state_t *) cookie;

	state->fd = -1;
	if (state->clone) {
		char buf[128];
		char* s;

		/* copy original file into a process-specific one */
		sprintf(buf, "%d", (int)getpid());
		s = (char*)malloc(strlen(state->filename) + strlen(buf) + 1);
		sprintf(s, "%s%d", state->filename, (int)getpid());
		if (cp(state->filename, s, S_IREAD|S_IWRITE) < 0) {
			perror("creating private tempfile");
			unlink(s);
			exit(1);
		}
		strcpy(state->filename, s);
	}
}

E 22
I 12
D 19
void
time_with_open(char *file)
E 19
I 19
void init_open(void * cookie)
E 19
{
D 19
	int	fd = open(file, 0);
E 19
I 19
	state_t	*state = (state_t *) cookie;
	int	ofd;
E 19

I 22
	initialize(cookie);
E 22
D 19
	doit(fd);
	close(fd);
E 19
I 19
	CHK(ofd = open(state->filename, O_RDONLY));
	state->fd = ofd;
E 19
}

D 19
void
time_io_only(int fd)
E 19
I 19
D 22
void cleanup_io(void * cookie)
E 19
{
D 19
	lseek(fd, 0, 0);
	doit(fd);
E 19
I 19
	state_t *state = (state_t *) cookie;
	close(state->fd);
E 19
}

E 22
E 12
D 19
int
main(ac, av)
	char  **av;
E 19
I 19
D 21
void time_with_open(uint64 iterations, void * cookie)
E 21
I 21
void time_with_open(iter_t iterations, void * cookie)
E 21
E 19
{
I 19
	state_t	*state = (state_t *) cookie;
	char	*filename = state->filename;
E 19
	int	fd;

D 15
	if (ac != 3) {
		fprintf(stderr, "Usage: %s size file, min size=%u\n",
		    av[0], XFERSIZE);
E 15
I 15
D 19
	if (ac != 4) {
		fprintf(stderr,
		    "Usage: %s size open2close|io_only file, min size=%uk\n",
		    av[0], XFERSIZE>>10);
E 15
		exit(1);
E 19
I 19
	while (iterations-- > 0) {
D 23
D 24
	  fd= open(filename, O_RDONLY);
	  doit(fd);
	  close(fd);
E 24
I 24
		fd= open(filename, O_RDONLY);
		doit(fd);
		close(fd);
E 24
E 23
I 23
D 25
		fd= open(filename, O_RDONLY);
		doit(fd);
		close(fd);
E 25
E 23
E 19
	}
D 15
	if (sizeof(int) != 4) {
		exit (1);
	}
E 15
D 19
	count = bytes(av[1]);
E 19
I 19
}

D 21
void time_io_only(uint64 iterations,void * cookie)
E 21
I 21
void time_io_only(iter_t iterations,void * cookie)
E 21
{
	state_t *state = (state_t *) cookie;
	int fd = state->fd;

	while (iterations-- > 0) {
D 24
	  lseek(fd, 0, 0);
	  doit(fd);
E 24
I 24
		lseek(fd, 0, 0);
		doit(fd);
E 24
	}
}

I 22
void cleanup(void * cookie)
{
	state_t *state = (state_t *) cookie;

	if (state->fd >= 0) close(state->fd);
	if (state->clone) unlink(state->filename);
}

E 22
int main(int ac, char **av)
{
	int	fd;
	state_t state;
	int	parallel = 1;
I 20
	int	warmup = 0;
	int	repetitions = TRIES;
E 20
	int	c;
D 20
	char	usage[132];
E 20
I 20
	char	usage[1024];
E 20
	
D 20
	sprintf(usage,"[-P <parallelism>] <size> open2close|io_only <filename>"
E 20
I 20
	sprintf(usage,"[-P <parallelism>] [-W <warmup>] [-N <repetitions>] <size> open2close|io_only <filename>"
E 20
		"\nmin size=%d\n",(int) (XFERSIZE>>10)) ;

D 22
	while (( c = getopt(ac, av, "P:")) != EOF) {
E 22
I 22
	state.clone = 0;

	while (( c = getopt(ac, av, "P:W:N:C")) != EOF) {
E 22
		switch(c) {
		case 'P':
			parallel = atoi(optarg);
			if (parallel <= 0) lmbench_usage(ac, av, usage);
			break;
I 20
		case 'W':
			warmup = atoi(optarg);
			break;
		case 'N':
			repetitions = atoi(optarg);
			break;
I 22
		case 'C':
			state.clone = 1;
			break;
E 22
E 20
		default:
			lmbench_usage(ac, av, usage);
			break;
		}
	}

	if (optind + 3 != ac) { /* should have three arguments left */
		lmbench_usage(ac, av, usage);
	}

	strcpy(state.filename,av[optind+2]);
	count = bytes(av[optind]);
E 19
	if (count < MINSZ) {
		exit(1);	/* I want this to be quiet */
	}
	if (count < XFERSIZE) {
		xfersize = count;
	} else {
		xfersize = XFERSIZE;
	}
D 23
	buf = (TYPE *)valloc(XFERSIZE);
I 15
	lastone = (TYPE*)((char*)buf + xfersize - MINSZ);
E 15
D 13
	bzero(buf, XFERSIZE);
E 13
I 13
	bzero((void*)buf, XFERSIZE);
E 23
I 23
	buf = (void *)valloc(XFERSIZE);
	bzero(buf, XFERSIZE);
E 23
E 13
D 15
	CHK(fd = open(av[2], 0));
	doit(fd);
	close(fd);
#ifdef	TIME_OPEN2CLOSE
	BENCH(time_with_open(av[2]), 0);
#else	
	CHK(fd = open(av[2], 0));
	BENCH(time_io_only(av[2]), 0);
	close(fd);
#endif
E 15
I 15
D 19
	if (!strcmp("open2close", av[2])) {
		BENCH(time_with_open(av[3]), 0);
	} else {
		CHK(fd = open(av[3], 0));
		BENCH(time_io_only(fd), 0);
		close(fd);
	}
E 15
	bandwidth(count, get_n(), 0);
E 19
I 19

	if (!strcmp("open2close", av[optind+1])) {
D 20
	  benchmp(NULL,time_with_open,NULL,0,parallel,&state);
E 20
I 20
D 22
	  benchmp(NULL,time_with_open,NULL,0,parallel,warmup,repetitions,&state);
E 22
I 22
D 23
D 24
	  benchmp(initialize,time_with_open,cleanup,0,parallel,warmup,repetitions,&state);
E 24
I 24
D 25
		benchmp(initialize,time_with_open,cleanup,0,parallel,warmup,repetitions,&state);
E 25
E 24
E 23
I 23
		benchmp(initialize, time_with_open, cleanup,
			0, parallel, warmup, repetitions, &state);
E 23
E 22
E 20
	} else if (!strcmp("io_only", av[optind+1])) {
D 20
	  benchmp(init_open,time_io_only,cleanup_io,0,parallel,&state);
E 20
I 20
D 22
	  benchmp(init_open,time_io_only,cleanup_io,0,parallel,warmup,repetitions,&state);
E 22
I 22
D 23
D 24
	  benchmp(init_open,time_io_only,cleanup,0,parallel,warmup,repetitions,&state);
E 24
I 24
D 25
		benchmp(init_open,time_io_only,cleanup,0,parallel,warmup,repetitions,&state);
E 25
E 24
E 23
I 23
		benchmp(init_open, time_io_only, cleanup,
			0, parallel, warmup, repetitions, &state);
E 23
E 22
E 20
	} else lmbench_usage(ac, av, usage);
	bandwidth(count, get_n() * parallel, 0);
E 19
	return (0);
}
E 11
D 6

int
bytes(s)
	char	*s;
{
	int	n = atoi(s);

	if ((last(s) == 'k') || (last(s) == 'K'))
		n *= 1024;
	if ((last(s) == 'm') || (last(s) == 'M'))
		n *= (1024 * 1024);
	return (n);
}

last(s)
	char	*s;
{
	while (*s++)
		;
	return (s[-2]);
}
E 6
E 2
I 1
E 1
