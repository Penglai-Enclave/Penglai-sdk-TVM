H33716
s 00000/00000/00176
d D 1.22 02/09/29 21:55:04 staelin 24 22
i 23
c Auto merged
cC
cHfirewall.staelin.co.il
cK11795
cM23
e
s 00004/00003/00207
d D 1.19.1.1 02/09/29 21:53:51 staelin 23 20
c - switch from 'int' to 'size_t' for better portability to large memory 
c   machines
cC
cHfirewall.staelin.co.il
cK42293
cZ+03:00
e
s 00009/00045/00166
d D 1.21 02/09/20 09:34:01 staelin 22 21
c - switch to using new bread() utility to read data into CPU
cC
cK10484
e
s 00002/00001/00209
d D 1.20 02/06/30 18:27:36 staelin 21 20
c In bw_mmap_rd, only check the file size for regular files as the
c field st_size is possibly invalid otherwise.
cC
cK43131
cZ+03:00
e
s 00045/00007/00165
d D 1.19 01/11/13 16:36:33 staelin 20 19
c Add ability for child processes in file-related benchmarks to each
c have their own file, as it sometimes makes a difference whether you
c measure N processes beating on a single file or on N independent
c files.
cC
cHhpli69.hpli.hpl.hp.com
cK40982
cZ+02:00
e
s 00004/00004/00168
d D 1.18 00/07/30 11:46:03 staelin 19 18
c - Change type of "iterations" from uint64 to iter_t, which is a u_long
cC
cK47862
e
s 00013/00005/00159
d D 1.17 00/07/04 14:55:48 staelin 18 17
c - Update to incorporate new "-W <warmup>" and "-N <repetitions>" flags
cC
cK46182
cZ+03:00
e
s 00001/00001/00163
d D 1.16 00/04/17 13:05:59 staelin 17 16
c - convert 'char c' to 'int c' for getopt()
cC
cHhpli8.hpli.hpl.hp.com
cK25463
cZ+02:00
e
s 00120/00056/00044
d D 1.15 00/03/10 18:02:24 brucec 16 15
c Make changes so test can be run in parallel "-P <parallelism>"
cC
cHrx7
cK25546
cZ-05:00
e
s 00004/00004/00096
d D 1.14 98/06/29 22:37:27 lm 15 14
c Redo to compile clean with -Wall.
cC
cK21305
cZ-07:00
e
s 00001/00001/00099
d D 1.13 97/10/31 18:06:23 lm 14 13
c use_result -> use_int/pointer
cK19301
cZ-08:00
e
s 00001/00004/00099
d D 1.12 97/10/19 23:45:04 lm 13 12
c 64bit -> 32bit
cK20276
e
s 00046/00057/00057
d D 1.11 97/06/25 10:25:01 lm 12 11
c 64 bit types
cK25918
e
s 00002/00004/00112
d D 1.10 97/06/15 22:38:58 lm 11 10
c lint
cK16408
e
s 00034/00032/00082
d D 1.9 97/06/13 20:39:50 lm 10 9
c lint
cK18490
e
s 00025/00026/00089
d D 1.8 97/06/12 21:30:06 lm 9 8
c new bench.h macros.
cK17602
cZ-07:00
e
s 00062/00021/00053
d D 1.7 96/11/13 16:09:37 lm 8 7
c make the loop do 128 load/stores
c add the option to time open to close
cK25089
e
s 00029/00025/00045
d D 1.6 96/11/11 03:36:51 lm 7 6
c Auto adjusting changes.
cK18885
e
s 00002/00021/00068
d D 1.5 96/11/08 19:57:32 lm 6 5
c gcc -Wall cleanup & new timing.c integration.
cK08234
cZ-08:00
e
s 00000/00001/00089
d D 1.4 96/05/30 00:33:07 lm 5 4
c no what strings
cK21488
e
s 00004/00000/00086
d D 1.3 95/10/25 18:03:42 lm 4 3
c MAP_FILE for FreeBSD.
cK23559
cZ-07:00
e
s 00001/00000/00085
d D 1.2 95/03/10 18:19:39 lm 3 2
c lint
cK16479
e
s 00085/00000/00000
d D 1.1 94/11/18 00:49:48 lm 2 1
c Initial revision
cK15600
e
s 00000/00000/00000
d D 1.0 94/11/18 00:49:47 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK04186
cPsrc/bw_mmap_rd.c
cR418ae16dc12971
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
 * bw_mmap_rd.c - time reading & summing of a file using mmap
 *
D 16
 * Usage: bw_mmap_rd size file
E 16
I 16
D 18
 * Usage: bw_mmap_rd [-P <parallelism>] size file
E 18
I 18
 * Usage: bw_mmap_rd [-P <parallelism>] [-W <warmup>] [-N <repetitions>] size file
E 18
E 16
 *
 * Sizes less than 2m are not recommended.  Memory is read by summing it up
 * so the numbers include the cost of the adds.  If you use sizes large
 * enough, you can compare to bw_mem_rd and get the cost of TLB fills 
 * (very roughly).
 *
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
char	*id = "$Id$\n";

D 7
#include "timing.c"
E 7
I 7
D 9
#include "timing.h"
E 9
#include "bench.h"
E 7
D 9
#include <sys/mman.h>
E 9
I 8
#ifdef MAP_FILE
#	define	MMAP_FLAGS	MAP_FILE|MAP_SHARED
#else
#	define	MMAP_FLAGS	MAP_SHARED
#endif
E 8
D 9
#include <sys/stat.h>
I 6
#include <fcntl.h>
E 9
E 6

D 7

E 7
I 7
D 13
#ifndef	TYPE
D 12
#define	TYPE	unsigned int
E 12
I 12
#define	TYPE	uint64
E 12
#endif
E 13
I 13
#define	TYPE	int
E 13
D 8
#define	MINSZ	(sizeof(TYPE) * 32)
E 8
I 8
#define	MINSZ	(sizeof(TYPE) * 128)
E 8
E 7
#define	CHK(x)	if ((int)(x) == -1) { perror("x"); exit(1); }

I 6
D 10
int
E 6
main(ac, av)
	char **av;
{
D 7
	int i, size, fd;
	char *where;
	unsigned int sum = 0, *p;
	struct stat sbuf;
E 7
I 7
D 8
	int	fd, sum, i, nbytes, N;
	char	*p, *buf, *end;
E 8
I 8
D 9
	int	fd, sum, i, nbytes;
	uint64	N;
E 9
I 9
	int	fd, nbytes;
E 9
	TYPE	*p, *buf, *lastone;
E 8
	struct	stat sbuf;
E 7

D 5
	write(2, id, strlen(id));
E 5
	if (ac != 3) {
		fprintf(stderr, "Usage: %s size file\n", av[0]);
		exit(1);
	}
D 7
	/* XXX - align size? */
	size = bytes(av[1]);
E 7
I 7
	nbytes = bytes(av[1]);
E 7
D 8
	CHK(fd = open(av[2], 0));
	CHK(fstat(fd, &sbuf));
E 8
I 8
	CHK(stat(av[2], &sbuf));
E 8
D 7
	if (size > sbuf.st_size) {
E 7
I 7
	if ((nbytes > sbuf.st_size) || (nbytes < MINSZ)) {
E 7
		fprintf(stderr, "%s: is too small\n", av[1]);
		exit(1);
	}
I 4
D 8
#ifdef MAP_FILE
D 7
	CHK(where = mmap(0, size, PROT_READ, MAP_FILE|MAP_SHARED, fd, 0));
E 7
I 7
	CHK(buf = mmap(0, nbytes, PROT_READ, MAP_FILE|MAP_SHARED, fd, 0));
E 7
#else
E 4
D 7
	CHK(where = mmap(0, size, PROT_READ, MAP_SHARED, fd, 0));
E 7
I 7
	CHK(buf = mmap(0, nbytes, PROT_READ, MAP_SHARED, fd, 0));
E 7
I 4
#endif
E 8
I 8
D 9
	{ /* warm the cache */
	char	buf[8192];
	int	nread = 0;
	CHK(fd = open(av[2], 0));
	while ((nread < nbytes) && ((sum = read(fd, buf, sizeof(buf))) > 0))
		nread += sum;
	close(fd);
	}
E 9
E 8
E 4
D 7
	p = (unsigned int*)where;
E 7

D 7
	start();
     	for (i = size/sizeof(*p); i >= 200; i -= 200) {
#define	TWENTY	sum += p[0]+p[1]+p[2]+p[3]+p[4]+p[5]+p[6]+p[7]+p[8]+p[9]+ \
		p[10]+p[11]+p[12]+p[13]+p[14]+p[15]+p[16]+p[17]+p[18]+p[19]; \
		p += 20;
#define	HUNDRED	TWENTY TWENTY TWENTY TWENTY TWENTY
		HUNDRED
		HUNDRED
E 7
I 7
D 8
	/*
	 * This preread is critical, at least on Intel P5s.
	 */
	for (sum = 1, p = buf; p < end; p++) {
		sum += *p;
E 8
I 8
#ifdef	TIME_OPEN2CLOSE
D 9
	LOOP_FIRST(N, i, ENOUGH);
E 9
I 9
	BENCH(time_with_open(av[2], nbytes), 0);
#else
E 9
	CHK(fd = open(av[2], 0));
	CHK(buf = mmap(0, nbytes, PROT_READ, MMAP_FLAGS, fd, 0));
	lastone = (TYPE*)((char*)buf + nbytes - MINSZ);
I 9
	BENCH(time_io_only(p, buf, lastone), 0);
	mmunmap(buf, nbytes);
#endif
	bandwidth(nbytes, get_n(), 0);
	return (0);
}

E 10
I 10
D 16
void
I 12
doit(register TYPE *p, register TYPE *lastone)
{
	register int sum = 0;

	while (p <= lastone) {
	    sum += p[0]+p[1]+p[2]+p[3]+p[4]+p[5]+p[6]+p[7]+p[8]+
	    p[9]+p[10]+p[11]+p[12]+p[13]+p[14]+p[15]+p[16]+p[17]+
	    p[18]+p[19]+p[20]+p[21]+p[22]+p[23]+p[24]+p[25]+p[26]+
	    p[27]+p[28]+p[29]+p[30]+p[31]+p[32]+p[33]+p[34]+p[35]+
	    p[36]+p[37]+p[38]+p[39]+p[40]+p[41]+p[42]+p[43]+
	    p[44]+p[45]+p[46]+p[47]+p[48]+p[49]+p[50]+p[51]+
	    p[52]+p[53]+p[54]+p[55]+p[56]+p[57]+p[58]+p[59]+
	    p[60]+p[61]+p[62]+p[63]+p[64]+p[65]+p[66]+p[67]+
	    p[68]+p[69]+p[70]+p[71]+p[72]+p[73]+p[74]+p[75]+
	    p[76]+p[77]+p[78]+p[79]+p[80]+p[81]+p[82]+p[83]+
	    p[84]+p[85]+p[86]+p[87]+p[88]+p[89]+p[90]+p[91]+
	    p[92]+p[93]+p[94]+p[95]+p[96]+p[97]+p[98]+p[99]+
	    p[100]+p[101]+p[102]+p[103]+p[104]+p[105]+p[106]+
	    p[107]+p[108]+p[109]+p[110]+p[111]+p[112]+p[113]+
	    p[114]+p[115]+p[116]+p[117]+p[118]+p[119]+p[120]+
	    p[121]+p[122]+p[123]+p[124]+p[125]+p[126]+p[127];
	    p += 128;
	}
D 14
	use_result((uint64)sum);
E 14
I 14
	use_int(sum);
E 14
}

void
E 12
E 10
time_with_open(char *file, int nbytes)
{
E 16
I 16
typedef struct _state {
D 23
	int	nbytes;
E 23
I 23
	size_t	nbytes;
E 23
	char	filename[256];
E 16
D 12
	int	sum = 0, fd;
	TYPE	*p, *buf, *lastone;
E 12
I 12
	int	fd;
I 20
	int	clone;
E 20
D 16
	TYPE	*buf, *lastone;
E 16
I 16
D 22
	TYPE	*buf;
	TYPE	*lastone;
E 22
I 22
	void	*buf;
E 22
} state_t;

D 19
void time_no_open(uint64 iter, void * cookie);
void time_with_open(uint64 iter, void * cookie);
E 19
I 19
void time_no_open(iter_t iterations, void * cookie);
void time_with_open(iter_t iterations, void * cookie);
I 20
void initialize(void *cookie);
E 20
E 19
void init_open(void *cookie);
void cleanup(void *cookie);
E 16
E 12

D 16
	CHK(fd = open(file, 0));
D 15
	CHK(buf = mmap(0, nbytes, PROT_READ, MMAP_FLAGS, fd, 0));
E 15
I 15
	CHK(buf = (TYPE*)mmap(0, nbytes, PROT_READ, MMAP_FLAGS, fd, 0));
E 15
	lastone = (TYPE*)((char*)buf + nbytes - MINSZ);
E 9
D 12
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
		p += 128;
E 8
E 7
	}
E 12
I 12
	doit(buf, lastone);
E 12
I 8
	close(fd);
D 15
	munmap(buf, nbytes);
E 15
I 15
	munmap((void*)buf, nbytes);
E 15
D 9
	LOOP_LAST(N, i, ENOUGH);
#else
	CHK(fd = open(av[2], 0));
E 8
D 7
	stop(sum);
#ifdef	CHECK
	printf("%s: %u\n", av[2], sum);
#endif
	bandwidth(size, 0);
E 7
I 7
	LOOP_FIRST(N, i, ENOUGH);
D 8
	for (p = buf; p < end; ) {
		sum += p[0]+p[1]+p[2]+p[3]+p[4]+p[5]+p[6]+p[7]+p[8]+p[9]+ 
		p[10]+p[11]+p[12]+p[13]+p[14]+p[15]+p[16]+p[17]+p[18]+p[19]+
E 8
I 8
	CHK(buf = mmap(0, nbytes, PROT_READ, MMAP_FLAGS, fd, 0));
	lastone = (TYPE*)((char*)buf + nbytes - MINSZ);
E 9
I 9
D 12
	use_result(sum);
E 12
}

I 10
D 12
void
E 10
time_io_only(TYPE *p, TYPE *buf, TYPE *lastone)
{
	int	sum = 0;

E 9
	for (p = buf; p <= lastone; ) {
		sum += p[0]+p[1]+p[2]+p[3]+p[4]+p[5]+p[6]+p[7]+p[8]+p[9]+
		p[10]+p[11]+p[12]+p[13]+p[14]+p[15]+p[16]+p[17]+p[18]+p[19]+ 
E 8
		p[20]+p[21]+p[22]+p[23]+p[24]+p[25]+p[26]+p[27]+p[28]+p[29]+
D 8
		p[30]+p[31];
		p += 32;
E 8
I 8
		p[30]+p[31]+p[32]+p[33]+p[34]+p[35]+p[36]+p[37]+p[38]+p[39]+
		p[40]+p[41]+p[42]+p[43]+p[44]+p[45]+p[46]+p[47]+p[48]+p[49]+
		p[50]+p[51]+p[52]+p[53]+p[54]+p[55]+p[56]+p[57]+p[58]+p[59]+
		p[60]+p[61]+p[62]+p[63]+p[64]+p[65]+p[66]+p[67]+p[68]+p[69]+
		p[70]+p[71]+p[72]+p[73]+p[74]+p[75]+p[76]+p[77]+p[78]+p[79]+
		p[80]+p[81]+p[82]+p[83]+p[84]+p[85]+p[86]+p[87]+p[88]+p[89]+
		p[90]+p[91]+p[92]+p[93]+p[94]+p[95]+p[96]+p[97]+p[98]+p[99]+
		p[100]+p[101]+p[102]+p[103]+p[104]+p[105]+p[106]+p[107]+p[108]+p[109]+
		p[110]+p[111]+p[112]+p[113]+p[114]+p[115]+p[116]+p[117]+p[118]+p[119]+
		p[120]+p[121]+p[122]+p[123]+p[124]+p[125]+p[126]+p[127]+p[128];
		p += 128;
E 8
	}
I 8
D 9
	munmap(buf, nbytes);
E 8
	LOOP_LAST(N, i, ENOUGH);
I 8
#endif
E 8
	bandwidth(nbytes, N, 0);
E 9
	use_result(sum);
E 7
I 3
D 8
	return(0);
E 8
I 8
D 9
	return (0);
E 9
E 8
E 3
}
I 10

E 12
int
D 11
main(ac, av)
	char **av;
E 11
I 11
main(int ac, char **av)
E 16
I 16
int main(int ac, char **av)
E 16
E 11
{
D 11
	int	fd, nbytes;
	TYPE	*p, *buf, *lastone;
E 11
I 11
D 12
	int	nbytes;
E 12
I 12
D 23
	int	fd, nbytes;
E 23
I 23
	int	fd;
E 23
E 12
E 11
	struct	stat sbuf;
I 12
D 22
	TYPE	*buf, *lastone;
E 22
I 22
	void	*buf;
E 22
I 16
	int	parallel = 1;
I 18
	int	warmup = 0;
	int	repetitions = TRIES;
I 23
	size_t	nbytes;
E 23
E 18
	state_t	state;
D 17
	char	c;
E 17
I 17
	int	c;
E 17
D 18
	char	*usage = "[-P <parallelism>] <size> open2close|mmap_only <filename>";
E 18
I 18
	char	*usage = "[-P <parallelism>] [-W <warmup>] [-N <repetitions>] <size> open2close|mmap_only <filename>";
E 18

D 18
	while (( c = getopt(ac, av, "P:")) != EOF) {
E 18
I 18
D 20
	while (( c = getopt(ac, av, "P:W:N:")) != EOF) {
E 20
I 20
	state.clone = 0;

	while (( c = getopt(ac, av, "P:W:N:C")) != EOF) {
E 20
E 18
		switch(c) {
		case 'P':
			parallel = atoi(optarg);
			if (parallel <= 0) lmbench_usage(ac, av, usage);
			break;
I 18
		case 'W':
			warmup = atoi(optarg);
			break;
		case 'N':
			repetitions = atoi(optarg);
			break;
I 20
		case 'C':
			state.clone = 1;
			break;
E 20
E 18
		default:
			lmbench_usage(ac, av, usage);
			break;
		}
	}
E 16
E 12

D 12
	if (ac != 3) {
		fprintf(stderr, "Usage: %s size file\n", av[0]);
E 12
I 12
D 16
	if (ac != 4) {
		fprintf(stderr,
		    "Usage: %s size open2close|mmap_only file\n", av[0]);
E 12
		exit(1);
E 16
I 16
	/* should have three arguments left (bytes type filename) */
	if (optind + 3 != ac) {
		lmbench_usage(ac, av, usage);
E 16
	}
D 16
	nbytes = bytes(av[1]);
D 12
	CHK(stat(av[2], &sbuf));
E 12
I 12
	CHK(stat(av[3], &sbuf));
E 16
I 16

	nbytes = state.nbytes = bytes(av[optind]);
	strcpy(state.filename,av[optind+2]);
	CHK(stat(state.filename, &sbuf));
E 16
E 12
D 21
	if ((nbytes > sbuf.st_size) || (nbytes < MINSZ)) {
E 21
I 21
	if ((S_ISREG(sbuf.st_mode) && nbytes > sbuf.st_size) 
	    || (nbytes < MINSZ)) {
E 21
I 16
		fprintf(stderr,"<size> out of range!\n");
E 16
D 13
		fprintf(stderr, "%s: is too small\n", av[1]);
E 13
		exit(1);
	}

D 12
#ifdef	TIME_OPEN2CLOSE
	BENCH(time_with_open(av[2], nbytes), 0);
#else
	CHK(fd = open(av[2], 0));
	CHK(buf = mmap(0, nbytes, PROT_READ, MMAP_FLAGS, fd, 0));
	lastone = (TYPE*)((char*)buf + nbytes - MINSZ);
	BENCH(time_io_only(p, buf, lastone), 0);
	mmunmap(buf, nbytes);
#endif
E 12
I 12
D 16
	if (!strcmp("open2close", av[2])) {
		BENCH(time_with_open(av[3], nbytes), 0);
E 16
I 16
	if (!strcmp("open2close", av[optind+1])) {
D 20
		benchmp(NULL, time_with_open, NULL,
E 20
I 20
		benchmp(initialize, time_with_open, cleanup,
E 20
D 18
			0, parallel, &state);
E 18
I 18
			0, parallel, warmup, repetitions, &state);
E 18
	} else if (!strcmp("mmap_only", av[optind+1])) {
		benchmp(init_open, time_no_open, cleanup,
D 18
			0, parallel, &state);
E 18
I 18
			0, parallel, warmup, repetitions, &state);
E 18
E 16
	} else {
D 16
		CHK(fd = open(av[3], 0));
D 15
		CHK(buf = mmap(0, nbytes, PROT_READ, MMAP_FLAGS, fd, 0));
E 15
I 15
		CHK(buf = (TYPE*)mmap(0, nbytes, PROT_READ, MMAP_FLAGS, fd, 0));
E 15
		lastone = (TYPE*)((char*)buf + nbytes - MINSZ);
		BENCH(doit(buf, lastone), 0);
D 15
		munmap(buf, nbytes);
E 15
I 15
		munmap((void*)buf, nbytes);
E 16
I 16
		lmbench_usage(ac, av, usage);
E 16
E 15
	}
E 12
D 16
	bandwidth(nbytes, get_n(), 0);
E 16
I 16
	bandwidth(nbytes, get_n() * parallel, 0);
E 16
	return (0);
I 16
}

D 20
void init_open(void *cookie)
E 20
I 20
void
initialize(void* cookie)
{
	state_t	*state = (state_t *) cookie;

	state->fd = -1;
	state->buf = NULL;

	if (state->clone) {
		char buf[8192];
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

void
init_open(void *cookie)
E 20
{
	state_t *state = (state_t *) cookie;

I 20
	initialize(cookie);
E 20
	CHK(state->fd = open(state->filename, 0));
D 22
	CHK(state->buf = (TYPE*)mmap(0, state->nbytes, PROT_READ,
E 22
I 22
	CHK(state->buf = mmap(0, state->nbytes, PROT_READ,
E 22
				     MMAP_FLAGS, state->fd, 0));
D 22
	state->lastone = (TYPE*)((char*)state->buf + state->nbytes - MINSZ);
E 22
}
D 20
void cleanup(void *cookie)
E 20
I 20

void
cleanup(void *cookie)
E 20
{
	state_t *state = (state_t *) cookie;
D 20
	munmap((void*)state->buf, state->nbytes);
	close(state->fd);
E 20
I 20
D 22
	if (state->buf) munmap((void*)state->buf, state->nbytes);
E 22
I 22
	if (state->buf) munmap(state->buf, state->nbytes);
E 22
	if (state->fd >= 0) close(state->fd);
	if (state->clone) unlink(state->filename);
E 20
}

D 20
int doit(register TYPE *p, register TYPE *lastone)
E 20
I 20
D 22
int
doit(register TYPE *p, register TYPE *lastone)
E 20
{
	register int sum = 0;
	while (p <= lastone) {
		sum += p[0]+p[1]+p[2]+p[3]+p[4]+p[5]+p[6]+p[7]+p[8]+
		    p[9]+p[10]+p[11]+p[12]+p[13]+p[14]+p[15]+p[16]+p[17]+
		    p[18]+p[19]+p[20]+p[21]+p[22]+p[23]+p[24]+p[25]+p[26]+
		    p[27]+p[28]+p[29]+p[30]+p[31]+p[32]+p[33]+p[34]+p[35]+
		    p[36]+p[37]+p[38]+p[39]+p[40]+p[41]+p[42]+p[43]+
		    p[44]+p[45]+p[46]+p[47]+p[48]+p[49]+p[50]+p[51]+
		    p[52]+p[53]+p[54]+p[55]+p[56]+p[57]+p[58]+p[59]+
		    p[60]+p[61]+p[62]+p[63]+p[64]+p[65]+p[66]+p[67]+
		    p[68]+p[69]+p[70]+p[71]+p[72]+p[73]+p[74]+p[75]+
		    p[76]+p[77]+p[78]+p[79]+p[80]+p[81]+p[82]+p[83]+
		    p[84]+p[85]+p[86]+p[87]+p[88]+p[89]+p[90]+p[91]+
		    p[92]+p[93]+p[94]+p[95]+p[96]+p[97]+p[98]+p[99]+
		    p[100]+p[101]+p[102]+p[103]+p[104]+p[105]+p[106]+
		    p[107]+p[108]+p[109]+p[110]+p[111]+p[112]+p[113]+
		    p[114]+p[115]+p[116]+p[117]+p[118]+p[119]+p[120]+
		    p[121]+p[122]+p[123]+p[124]+p[125]+p[126]+p[127];
		p += 128;
	}
	return sum;
}

E 22
D 19
void time_no_open(uint64 iterations, void * cookie)
E 19
I 19
void time_no_open(iter_t iterations, void * cookie)
E 19
{
	state_t *state = (state_t *) cookie;
D 22
	register TYPE *p = state->buf;
	register TYPE *lastone;
	register int sum = 0;
E 22

D 22
	lastone = state->lastone;
E 22
	while (iterations-- > 0) {
D 22
	    sum += doit(p,lastone);
E 22
I 22
	    bread(state->buf, state->nbytes);
E 22
	}
D 22
	use_int(sum);
E 22
}

D 19
void time_with_open(uint64 iterations, void *cookie)
E 19
I 19
void time_with_open(iter_t iterations, void *cookie)
E 19
{
	state_t *state    = (state_t *) cookie;
	char 	*filename = state->filename;
D 23
	int	nbytes    = state->nbytes;
E 23
I 23
	size_t	nbytes    = state->nbytes;
E 23
	int 	fd;
D 22
	register TYPE *p, *lastone;
	register int sum = 0;
E 22
I 22
	void	*p;
E 22

	while (iterations-- > 0) {
	    CHK(fd = open(filename, 0));
D 22
	    CHK(p = (TYPE*)mmap(0, nbytes, PROT_READ, MMAP_FLAGS, fd, 0));
	    lastone = (TYPE*)((char*)p + nbytes - MINSZ);
	    sum += doit(p,lastone);
E 22
I 22
	    CHK(p = mmap(0, nbytes, PROT_READ, MMAP_FLAGS, fd, 0));
	    bread(p, nbytes);
E 22
	    close(fd);
D 22
	    munmap((void*)p, nbytes);
E 22
I 22
	    munmap(p, nbytes);
E 22
	}
D 22
	use_int(sum);
E 22
E 16
}
E 10
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
