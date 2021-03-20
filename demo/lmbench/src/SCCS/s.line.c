H30955
s 00001/00006/00067
d D 1.15 01/06/20 10:21:39 staelin 16 15
c src/line.c: Fix bug in automatic resizing when you request more memory than is
c available; matching fixes in lib_mem.c
cC
cK47343
e
s 00009/00006/00064
d D 1.14 01/04/09 16:48:14 staelin 15 14
c Increase the default memory size from 32MB to 64MB, and add additional
c tests so line won't print any output if it can't find a line size.
cC
cHhpli69.hpli.hpl.hp.com
cK51887
cZ+03:00
e
s 00007/00027/00063
d D 1.13 00/10/16 17:21:29 staelin 14 13
c - Assorted code cleanups
cC
cK48490
cZ+02:00
e
s 00001/00001/00089
d D 1.12 00/09/25 17:27:52 staelin 13 12
c - Change meaning of state->line from number of words per cache line to number of bytes
c   per cache line to bring it into line with tlb, cache, and par_mem
cC
cK18121
e
s 00000/00056/00090
d D 1.11 00/09/19 16:52:54 staelin 12 11
c - Migrate line_find and line_test from line.c to lib_mem.c
cC
cK16978
e
s 00007/00123/00139
d D 1.10 00/09/18 16:44:09 staelin 11 10
c - Create lib_mem.h and lib_mem.c to hold common routines for memory subsystem analysis
cC
cK43972
e
s 00106/00077/00156
d D 1.9 00/09/13 12:41:43 staelin 10 9
c - Debug benchmark so TLB effects are minimized/eliminated.  We used to access only
c   four lines per page, but now we actively utilize all lines on a page.
c - Add "int* permutation(int N);" which returns a permutation of N integers
cC
cK02215
e
s 00001/00009/00232
d D 1.8 00/08/01 09:21:26 staelin 9 8
c - Replace custom code with call to bytes(optarg)
cC
cK15166
e
s 00002/00002/00239
d D 1.7 00/07/30 11:46:17 staelin 8 7
c - Change type of "iterations" from uint64 to iter_t, which is a u_long
cC
cK30434
e
s 00022/00012/00219
d D 1.6 00/07/05 17:14:37 staelin 7 6
c - Add a second level of statistical median filtering on the results; since each
c   benchmark's memory access patterns are random, we need a second level of filtering
c   to determine the "representative" value.
cC
cK30248
e
s 00003/00001/00228
d D 1.5 00/07/05 14:37:18 staelin 6 5
c - tweaks to benchmark so if you change the memory buffer the benchmark doesn't core dump
cC
cK23534
e
s 00002/00002/00227
d D 1.4 00/07/05 12:02:12 staelin 5 4
c - Send output to stdout rather than stderr
cC
cK17160
e
s 00012/00012/00217
d D 1.3 00/07/05 11:28:07 staelin 4 3
c - make 'line' more like 'enough'; it just prints the answer unless you give it a '-v' flag
cC
cK18836
e
s 00016/00005/00213
d D 1.2 00/07/04 14:56:02 staelin 3 2
c - Update to incorporate new "-W <warmup>" and "-N <repetitions>" flags
cC
cK17554
e
s 00218/00000/00000
d D 1.1 00/07/02 17:28:00 staelin 2 1
cC
cF1
cK01434
cO-rw-rw-r--
e
s 00000/00000/00000
d D 1.0 00/07/02 17:28:00 staelin 1 0
c BitKeeper file /tmp_mnt/usr/WebPaper/users/staelin/src/LMbench/src/line.c
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHhpli8.hpli.hpl.hp.com
cK39686
cPsrc/line.c
cR3b0368f91b02d0e2
cV4
cX0xa1
cZ+03:00
e
u
U
f e 0
f x 0xa1
t
T
I 2
/*
 * line.c - guess the cache line size
 *
 * usage: line
 *
 * Copyright (c) 2000 Carl Staelin.
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
char	*id = "$Id$\n";

#include "bench.h"

D 11
struct _state {
	char*	addr;
	char*	p;
	int	len;
	int	line;
	int	pagesize;
};

D 10
void initialize(void* cookie);
D 8
void benchmark(uint64 iterations, void* cookie);
E 8
I 8
void benchmark(iter_t iterations, void* cookie);
E 8
void cleanup(void* cookie);
E 10
I 10
double	line_test(int l, int warmup, int repetitions, struct _state* state);
int	line_find(int len, int warmup, int repetitions, struct _state* state);
void	line_initialize(void* cookie);
void	line_benchmark(iter_t iterations, void* cookie);
void	line_cleanup(void* cookie);
E 10

#define	ONE	p = (char **)*p; 
/*	fprintf(stderr, "0x%x:\t%d\t%d\t%d\n", (unsigned int)p, (unsigned int)p / state->pagesize, (((unsigned int)p % state->pagesize) * 4) / state->pagesize, (unsigned int)p % state->pagesize); */
#define	FIVE	ONE ONE ONE ONE ONE
#define	TEN	FIVE FIVE
#define	FIFTY	TEN TEN TEN TEN TEN
#define	HUNDRED	FIFTY FIFTY
E 11
I 11
D 12
double	line_test(int l, int warmup, int repetitions, struct mem_state* state);
int	line_find(int len, int warmup, int repetitions, struct mem_state* state);
E 11

E 12
/*
 * Assumptions:
 *
 * 1) Cache lines are a multiple of pointer-size words
D 7
 * 2) Cache lines are smaller than 1/4 a page size
E 7
I 7
 * 2) Cache lines are no larger than 1/4 a page size
E 7
 * 3) Pages are an even multiple of cache lines
 */
int
main(int ac, char **av)
{
D 7
	int	i, l;
E 7
I 7
	int	i, j, l;
I 10
D 14
	int	find_all = 0;
E 14
E 10
E 7
I 4
	int	verbose = 0;
I 10
D 15
	int	maxlen = 32 * 1024 * 1024;
E 15
I 15
	int	maxlen = 64 * 1024 * 1024;
E 15
E 10
E 4
I 3
	int	warmup = 0;
	int	repetitions = TRIES;
E 3
	int	c;
D 10
	int	maxline = getpagesize() / (4 * sizeof(char*));
D 7
	double* times;
E 7
I 7
	double	t, threshold;
	result_t r, *r_save;
E 10
E 7
D 11
	struct _state state;
E 11
I 11
	struct mem_state state;
E 11
D 3
	char   *usage = "[-M len[K|M]]\n";
E 3
I 3
D 4
	char   *usage = "[-W <warmup>] [-N <repetitions>][-M len[K|M]]\n";
E 4
I 4
	char   *usage = "[-v] [-W <warmup>] [-N <repetitions>][-M len[K|M]]\n";
E 4
E 3

D 10
        state.len = 32 * 1024 * 1024;
E 10
D 13
	state.line = 2;
E 13
I 13
	state.line = sizeof(char*);
E 13
	state.pagesize = getpagesize();

D 3
	while (( c = getopt(ac, av, "M:")) != EOF) {
E 3
I 3
D 4
	while (( c = getopt(ac, av, "M:W:N:")) != EOF) {
E 4
I 4
D 10
	while (( c = getopt(ac, av, "vM:W:N:")) != EOF) {
E 10
I 10
	while (( c = getopt(ac, av, "avM:W:N:")) != EOF) {
E 10
E 4
E 3
		switch(c) {
I 10
D 14
		case 'a':
			find_all = 1;
			break;
E 14
E 10
I 4
		case 'v':
			verbose = 1;
			break;
E 4
		case 'M':
D 9
			l = strlen(optarg);
			if (optarg[l-1] == 'm' || optarg[l-1] == 'M') {
				state.len = 1024 * 1024;
				optarg[l-1] = 0;
			} else if (optarg[l-1] == 'k' || optarg[l-1] == 'K') {
				state.len = 1024;
				optarg[l-1] = 0;
			}
			state.len *= atoi(optarg);
E 9
I 9
D 10
			state.len = bytes(optarg);
E 10
I 10
			maxlen = bytes(optarg);
E 10
E 9
			break;
I 3
		case 'W':
			warmup = atoi(optarg);
			break;
		case 'N':
			repetitions = atoi(optarg);
			break;
E 3
		default:
			lmbench_usage(ac, av, usage);
			break;
		}
	}

D 4
/*
	state.line = 2;
	initialize(&state);
	benchmark(1, &state);
	cleanup(&state);
	exit(0);
D 3
*/	
E 3
I 3
/**/	
E 3

E 4
D 7
	times = (double*)malloc(maxline * sizeof(double));

	for (i = 2; i < maxline; i<<=1) {
E 7
I 7
D 10
	for (i = 2; i <= maxline; i<<=1) {
E 7
		state.line = i;
D 3
		benchmp(initialize, benchmark, cleanup, 0, 1, &state);
E 3
I 3
D 7
		benchmp(initialize, benchmark, cleanup, 0, 1, 
			warmup, repetitions, &state);
E 7
E 3

D 7
		/* We want to get to nanoseconds / load. */
		times[i] = (1000. * (double)gettime()) / (100. * (double)get_n());
E 7
I 7
		r_save = get_results();
		insertinit(&r);
		for (j = 0; j < 5; ++j) {
			benchmp(initialize, benchmark, cleanup, 0, 1, 
				warmup, repetitions, &state);
			insertsort(gettime(), get_n(), &r);
		}
		set_results(&r);
		t = (double)gettime() / (double)get_n();
		set_results(r_save);

		if (i == 2) {
			threshold = 1.25 * t;
			continue;
		}
E 7

D 3
		/* fprintf(stderr, "%d %.5f\n", state.line * sizeof(char*), times[i]); */
E 3
I 3
D 4
		/**/
E 4
I 4
		/*
E 4
D 7
		fprintf(stderr, "%d %.5f\n", state.line * sizeof(char*), times[i]); 
E 7
I 7
		fprintf(stderr, "%d %.5f\n", state.line * sizeof(char*), t); 
E 7
		/**/
E 3
		
D 7
		if (i > 2 && times[i] / times[2] > 1.25) {
E 7
I 7
		if (t > threshold) {
E 7
D 4
			fprintf(stderr, "cache line size: %d bytes\n", l);
E 4
I 4
			if (verbose) {
D 5
				fprintf(stderr, "cache line size: %d bytes\n", l);
E 5
I 5
				printf("cache line size: %d bytes\n", l);
E 5
			} else {
D 5
				fprintf(stderr, "%d\n", l);
E 5
I 5
				printf("%d\n", l);
E 10
I 10
D 14
	if (!find_all) {
		l = line_find(maxlen, warmup, repetitions, &state);
		if (verbose) {
			printf("cache line size: %d bytes\n", l);
		} else {
			printf("%d\n", l);
		}
	} else {
		int len = 0;
		int level = 1;
E 14
I 14
D 15
	while(!(l = line_find(maxlen, warmup, repetitions, &state))) {
E 15
I 15
D 16
	while (maxlen > state.pagesize
	       && !(l = line_find(maxlen, warmup, repetitions, &state))) {
E 15
		maxlen >>= 1;
	}
E 14

D 14
		for (i = getpagesize(); i <= maxlen; i<<=1) {
			l = line_find(i, warmup, repetitions, &state);
			if ((i<<1) <= maxlen && l != 0 &&
			    (len == 0 || len != 0 && l != len)) {
				/*
				 * near edge of cache, move away from edge
				 * to get more reliable reading
				 */
				l = line_find(i<<=1, warmup, repetitions, &state);
				printf("L%d cache line size: %d bytes\n", level, l);
				level++;
E 10
E 5
			}
E 4
D 10
			break;
E 10
		}
E 14
I 14
D 15
	if (verbose) {
		printf("cache line size: %d bytes\n", l);
	} else {
		printf("%d\n", l);
E 15
I 15
	if (l) {
E 16
I 16
	if ((l = line_find(maxlen, warmup, repetitions, &state)) > 0) {
E 16
		if (verbose) {
			printf("cache line size: %d bytes\n", l);
		} else {
			printf("%d\n", l);
		}
E 15
E 14
I 10
	}
E 10

D 10
		l = state.line * sizeof(char*);
E 10
I 10
	return (0);
}
D 12

int
D 11
line_find(int len, int warmup, int repetitions, struct _state* state)
E 11
I 11
line_find(int len, int warmup, int repetitions, struct mem_state* state)
E 11
{
	int 	i, j;
	int 	l = 0;
	int	maxline = getpagesize() / (8 * sizeof(char*));
	double	t, threshold;

	state->len = len;

	threshold = .85 * line_test(maxline, warmup, repetitions, state);

	for (i = maxline>>1; i >= 2; i>>=1) {
		t = line_test(i, warmup, repetitions, state);

		if (t <= threshold) {
			return ((i<<1) * sizeof(char*));
		}
E 10
	}

D 10
	return(0);
E 10
I 10
	return (0);
}

double
D 11
line_test(int len, int warmup, int repetitions, struct _state* state)
E 11
I 11
line_test(int len, int warmup, int repetitions, struct mem_state* state)
E 11
{
	int	i;
	double	t;
	result_t r, *r_save;

	state->line = len;
	r_save = get_results();
	insertinit(&r);
	for (i = 0; i < 5; ++i) {
D 11
		benchmp(line_initialize, line_benchmark, line_cleanup, 
E 11
I 11
		benchmp(line_initialize, mem_benchmark_0, mem_cleanup, 
E 11
			0, 1, warmup, repetitions, state);
		insertsort(gettime(), get_n(), &r);
	}
	set_results(&r);
	t = 10. * (double)gettime() / (double)get_n();
	set_results(r_save);
	
D 11
	/**/
E 11
I 11
	/*
E 11
	fprintf(stderr, "%d\t%.5f\t%d\n", len * sizeof(char*), t, state->len); 
	/**/

	return (t);
E 10
}

D 11
void
D 10
initialize(void* cookie)
E 10
I 10
line_initialize(void* cookie)
E 10
{
	int i, j, k, last, line, nlines, npages;
	unsigned int r;
	char ***pages;
	int    *lines;
	struct _state* state = (struct _state*)cookie;
	register char *p = 0 /* lint */;

	last = state->line - 1;
	line = state->line * sizeof(char*);
D 10
	nlines = 4;
E 10
I 10
	nlines = state->pagesize / line;
E 10
	npages = state->len / state->pagesize;

D 10
	state->p = state->addr = (char*)malloc(state->len + state->pagesize);
E 10
I 10
	srand(getpid());

	state->p = state->addr = (char*)valloc(state->len + state->pagesize);
E 10
	pages = (char***)malloc(npages * sizeof(char**));
D 10
	lines = (int*)malloc(nlines * sizeof(int));
E 10
I 10
	lines = permutation(nlines);
E 10

	if (state->addr == NULL || lines == NULL || pages == NULL) {
		exit(0);
	}

D 10
	srand(getpid());

E 10
	if ((unsigned long)state->p % state->pagesize) {
		state->p += state->pagesize - (unsigned long)state->p % state->pagesize;
	}

	/* first, layout the sequence of page accesses */
	p = state->p;
	for (i = 0; i < npages; ++i) {
		pages[i] = (char**)p;
		p += state->pagesize;
	}

	/* randomize the page sequences */
	r = (rand() << 15) ^ rand();
	for (i = npages - 1; i > 0; --i) {
		char **l;
		r = (r << 1) ^ (rand() >> 4);
		l = pages[r % i];
		pages[r % i] = pages[i];
		pages[i] = l;
	}

D 10
	/* layout the sequence of line accesses */
	for (i = 0; i < nlines; ++i) {
		lines[i] = i * state->pagesize / (nlines * sizeof(char*));
	}
	
	/* randomize the line sequences */
	for (i = nlines - 1; i > 0; --i) {
		int l;
		r = (r << 1) ^ (rand() >> 4);
		l = lines[r % i];
		lines[r % i] = lines[i];
		lines[i] = l;
	}
E 10
I 10
	for (i = 0; i < nlines; ++i)
		lines[i] *= state->line;
E 10

	/* new setup runs through the lines */
	for (i = 0; i < npages; ++i) {
D 10
		/* sequence through the last word of line j */
		for (j = 0; j < nlines - 1; ++j) {
			pages[i][lines[j]+last] = (char*)(pages[i] + lines[j+1] + last);
		}

		/* jump back to first word on first line of the page */
		pages[i][lines[j]+last] = (char*)(pages[i] + lines[0]);

		/* sequence through first word of line j */
E 10
I 10
		/* sequence through the first word of each line */
E 10
		for (j = 0; j < nlines - 1; ++j) {
			pages[i][lines[j]] = (char*)(pages[i] + lines[j+1]);
		}

D 10
		/* jump to the last word of the first line on next page */
		if (i < npages - 1)
			pages[i][lines[j]] = (char*)(pages[i+1] + lines[0] + last);
		else
			pages[i][lines[j]] = (char*)(pages[0] + lines[0] + last);
E 10
I 10
		/* jump to the fist word of the first line on next page */
		if (i < npages - 1) {
			pages[i][lines[j]] = (char*)(pages[i+1] + lines[0]);
		} else {
			pages[i][lines[j]] = (char*)(pages[0] + lines[0]);
		}
E 10
	}
I 10
	state->p = (char*)(pages[0] + lines[0]);

E 10
	free(lines);
	free(pages);
D 10
	
E 10
I 10

E 10
	/* now, run through the chain once to clear the cache */
D 10
	benchmark((8 * npages + 100) / 100, state);
E 10
I 10
	line_benchmark((nlines * npages + 100) / 100, state);
E 10
}


D 8
void benchmark(uint64 iterations, void *cookie)
E 8
I 8
D 10
void benchmark(iter_t iterations, void *cookie)
E 10
I 10
void
line_benchmark(iter_t iterations, void *cookie)
E 10
E 8
{
	struct _state* state = (struct _state*)cookie;
I 6
	static char *addr_save = NULL;
E 6
	static char **p_save = NULL;
D 6
	register char **p = p_save ? p_save : (char**)state->p;
E 6
I 6
	register char **p = addr_save == state->addr ? p_save : (char**)state->p;
E 6

	while (iterations-- > 0) {
		HUNDRED;
	}

	use_pointer((void *)p);
	p_save = p;
I 6
	addr_save = state->addr;
E 6
}

D 10
void cleanup(void* cookie)
E 10
I 10
void
line_cleanup(void* cookie)
E 10
{
	struct _state* state = (struct _state*)cookie;
	free(state->addr);
	state->addr = NULL;
	state->p = NULL;
}
E 11



E 12
E 2
I 1
E 1
