H51747
s 00003/00002/00078
d D 1.14 02/09/29 21:53:51 staelin 15 14
c - switch from 'int' to 'size_t' for better portability to large memory 
c   machines
cC
cHfirewall.staelin.co.il
cK13737
e
s 00002/00002/00078
d D 1.13 01/04/09 16:58:40 staelin 14 13
c Increase the maximum memory for par_mem from 32MB to 64MB due to
c increasing cache sizes.  We want the maximum size to be several
c times larger than the largest cache to minimize cache effects.
cC
cHhpli69.hpli.hpl.hp.com
cK13298
e
s 00004/00002/00076
d D 1.12 00/09/28 12:16:51 staelin 13 12
c - Add error checking to par_mem
cC
cK13246
e
s 00005/00039/00073
d D 1.11 00/09/25 17:27:53 staelin 12 11
c - Migrate core of benchmark into a separate routine, par_mem, which is now in lib_mem.c
cC
cK13468
e
s 00009/00196/00103
d D 1.10 00/09/18 16:44:10 staelin 11 10
c - Create lib_mem.h and lib_mem.c to hold common routines for memory subsystem analysis
cC
cK28100
e
s 00009/00026/00290
d D 1.9 00/09/13 12:41:44 staelin 10 9
c - Rename "loads" to "par_mem"
c - Add "int* permutation(int N);" which returns a permutation of N integers
cC
cK50426
e
s 00000/00000/00316
d D 1.8 00/08/16 09:32:18 staelin 9 8
c Rename: src/loads.c -> src/par_mem.c
cC
cK61414
cPsrc/par_mem.c
e
s 00058/00039/00258
d D 1.7 00/08/16 09:31:23 staelin 8 7
c - Fix bug in setup of pointer chains; ensure that pointers are always equidistant
c - Fixup macros which build benchmark functions
cC
cK06322
e
s 00001/00009/00296
d D 1.6 00/08/01 09:21:26 staelin 7 6
c - Replace custom code with call to bytes(optarg)
cC
cK30385
e
s 00037/00023/00268
d D 1.5 00/07/30 14:40:00 staelin 6 5
c - Change loads so that it tests all load widths and reports the fastest result
cC
cK45123
e
s 00002/00002/00289
d D 1.4 00/07/30 11:46:18 staelin 5 4
c - Change type of "iterations" from uint64 to iter_t, which is a u_long
cC
cK07224
e
s 00040/00030/00251
d D 1.3 00/07/25 13:48:39 staelin 4 3
c - Change loads to test up to 16-wide load paths (this should probably be 32, but then
c   we will have to have some intelligence that can test the intermediate widths in case
c   we have a processor which doesn't have enough registers to keep all the pointers in
c   registers so we spill our pointers onto the stack)
cC
cK07038
e
s 00027/00017/00254
d D 1.2 00/07/05 17:14:37 staelin 3 2
c - Add a second level of statistical median filtering on the results; since each
c   benchmark's memory access patterns are random, we need a second level of filtering
c   to determine the "representative" value.
c - Also add check that we only access as much memory as we desire; important when the
c   desired memory size is less than a page.
cC
cK23792
e
s 00271/00000/00000
d D 1.1 00/07/05 14:37:28 staelin 2 1
cC
cF1
cK60006
cO-rw-rw-r--
e
s 00000/00000/00000
d D 1.0 00/07/05 14:37:28 staelin 1 0
c BitKeeper file /tmp_mnt/usr/WebPaper/users/staelin/src/LMbench/src/loads.c
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHhpli8.hpli.hpl.hp.com
cK29808
cPsrc/loads.c
cR3a067dd8318af052
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
D 10
 * loads.c - guess the cache size(s)
E 10
I 10
 * par_mem.c - determine the memory hierarchy parallelism
E 10
 *
D 10
 * usage: loads [-L <line size>] [-M len[K|M]] [-W <warmup>] [-N <repetitions>]
E 10
I 10
 * usage: par_mem [-L <line size>] [-M len[K|M]] [-W <warmup>] [-N <repetitions>]
E 10
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
D 4
	char*	p[8];
E 4
I 4
	char*	p[16];
I 8
	int	width;
E 8
E 4
	int	len;
	int	line;
	int	pagesize;
};

void compute_times(struct _state* state, double* tlb_time, double* cache_time);
void initialize(void* cookie);
D 5
void benchmark(uint64 iterations, void* cookie);
E 5
I 5
void benchmark(iter_t iterations, void* cookie);
E 5
void cleanup(void* cookie);

#define	FIVE(m)		m m m m m
#define	TEN(m)		FIVE(m) FIVE(m)
#define	FIFTY(m)	TEN(m) TEN(m) TEN(m) TEN(m) TEN(m)
#define	HUNDRED(m)	FIFTY(m) FIFTY(m)

I 6
#define MAX_LOAD_PARALLELISM 16

E 6
D 4
#define REPEAT(m) m(0) m(1) m(2) m(3) m(4) m(5) m(6) m(7)
E 4
I 4
D 8
#define REPEAT(m) m(0) m(1) m(2) m(3) m(4) m(5) m(6) m(7) m(8) m(9) m(10) m(11) m(12) m(13) m(14) m(15)
#define DEREF(N) p##N = (char**)*p##N
#define DECLARE(N) static char **sp##N; register char **p##N;
E 4
#define INIT(N) p##N = (addr_save==state->addr) ? sp##N : (char**)state->p[N];
#define SAVE(N) sp##N = p##N;
#define BENCHMARK(N,body) \
D 5
void benchmark_##N(uint64 iterations, void *cookie) \
E 5
I 5
void benchmark_##N(iter_t iterations, void *cookie) \
E 5
{ \
	struct _state* state = (struct _state*)cookie; \
	static char *addr_save = NULL; \
D 4
	static char **sp0, **sp1, **sp2, **sp3, **sp4, **sp5, **sp6, **sp7; \
	register char **p0, **p1, **p2, **p3, **p4, **p5, **p6, **p7; \
E 4
I 4
	REPEAT(DECLARE); \
E 4
\
	REPEAT(INIT); \
	while (iterations-- > 0) { \
		HUNDRED(body); \
	} \
\
	REPEAT(SAVE); \
	addr_save = state->addr; \
E 8
I 8
#define REPEAT_0(m)	m(0)
#define REPEAT_1(m)	REPEAT_0(m) m(1)
#define REPEAT_2(m)	REPEAT_1(m) m(2)
#define REPEAT_3(m)	REPEAT_2(m) m(3)
#define REPEAT_4(m)	REPEAT_3(m) m(4)
#define REPEAT_5(m)	REPEAT_4(m) m(5)
#define REPEAT_6(m)	REPEAT_5(m) m(6)
#define REPEAT_7(m)	REPEAT_6(m) m(7)
#define REPEAT_8(m)	REPEAT_7(m) m(8)
#define REPEAT_9(m)	REPEAT_8(m) m(9)
#define REPEAT_10(m)	REPEAT_9(m) m(10)
#define REPEAT_11(m)	REPEAT_10(m) m(11)
#define REPEAT_12(m)	REPEAT_11(m) m(12)
#define REPEAT_13(m)	REPEAT_12(m) m(13)
#define REPEAT_14(m)	REPEAT_13(m) m(14)
#define REPEAT_15(m)	REPEAT_14(m) m(15)

#define DEREF(N)	p##N = (char**)*p##N;
#define DECLARE(N)	static char **sp##N; register char **p##N;
#define INIT(N)		p##N = (addr_save==state->addr) ? sp##N : (char**)state->p[N];
#define SAVE(N)		sp##N = p##N;

#define BENCHMARK(N,repeat,body) 					\
void benchmark_##N(iter_t iterations, void *cookie) 			\
{									\
	struct _state* state = (struct _state*)cookie;			\
	static char *addr_save = NULL;					\
	repeat(DECLARE);						\
									\
	repeat(INIT);							\
	while (iterations-- > 0) {					\
		HUNDRED(repeat(body));					\
	}								\
									\
	repeat(SAVE);							\
	addr_save = state->addr;					\
E 8
}
E 11
I 11
void compute_times(struct mem_state* state, double* tlb_time, double* cache_time);
E 11

D 4
BENCHMARK(0, p0 = (char **)*p0;)
BENCHMARK(1, p0 = (char **)*p0; p4 = (char **)*p4;)
BENCHMARK(2, p0 = (char **)*p0; p4 = (char **)*p4; p2 = (char **)*p2;)
BENCHMARK(3, p0 = (char **)*p0; p4 = (char **)*p4; p2 = (char **)*p2; p6 = (char **)*p6;)
BENCHMARK(4, p0 = (char **)*p0; p4 = (char **)*p4; p2 = (char **)*p2; p6 = (char **)*p6; p1 = (char **)*p1;)
BENCHMARK(5, p0 = (char **)*p0; p4 = (char **)*p4; p2 = (char **)*p2; p6 = (char **)*p6; p1 = (char **)*p1; p5 = (char **)*p5;)
BENCHMARK(6, p0 = (char **)*p0; p4 = (char **)*p4; p2 = (char **)*p2; p6 = (char **)*p6; p1 = (char **)*p1; p5 = (char **)*p5; p3 = (char **)*p3;)
BENCHMARK(7, p0 = (char **)*p0; p4 = (char **)*p4; p2 = (char **)*p2; p6 = (char **)*p6; p1 = (char **)*p1; p5 = (char **)*p5; p3 = (char **)*p3; p7 = (char **)*p7;)
E 4
I 4
D 8
BENCHMARK(0, DEREF(0);)
BENCHMARK(1, DEREF(0); DEREF(8);)
BENCHMARK(2, DEREF(0); DEREF(8); DEREF(4);)
BENCHMARK(3, DEREF(0); DEREF(8); DEREF(4); DEREF(12);)
BENCHMARK(4, DEREF(0); DEREF(8); DEREF(4); DEREF(12); DEREF(2);)
BENCHMARK(5, DEREF(0); DEREF(8); DEREF(4); DEREF(12); DEREF(2); DEREF(10);)
BENCHMARK(6, DEREF(0); DEREF(8); DEREF(4); DEREF(12); DEREF(2); DEREF(10); DEREF(6);)
BENCHMARK(7, DEREF(0); DEREF(8); DEREF(4); DEREF(12); DEREF(2); DEREF(10); DEREF(6); DEREF(14);)
BENCHMARK(8, DEREF(0); DEREF(8); DEREF(4); DEREF(12); DEREF(2); DEREF(10); DEREF(6); DEREF(14); DEREF(1);)
BENCHMARK(9, DEREF(0); DEREF(8); DEREF(4); DEREF(12); DEREF(2); DEREF(10); DEREF(6); DEREF(14); DEREF(1); DEREF(11);)
BENCHMARK(10, DEREF(0); DEREF(8); DEREF(4); DEREF(12); DEREF(2); DEREF(10); DEREF(6); DEREF(14); DEREF(1); DEREF(11); DEREF(3);)
BENCHMARK(11, DEREF(0); DEREF(8); DEREF(4); DEREF(12); DEREF(2); DEREF(10); DEREF(6); DEREF(14); DEREF(1); DEREF(11); DEREF(3); DEREF(9);)
BENCHMARK(12, DEREF(0); DEREF(8); DEREF(4); DEREF(12); DEREF(2); DEREF(10); DEREF(6); DEREF(14); DEREF(1); DEREF(11); DEREF(3); DEREF(9); DEREF(15);)
BENCHMARK(13, DEREF(0); DEREF(8); DEREF(4); DEREF(12); DEREF(2); DEREF(10); DEREF(6); DEREF(14); DEREF(1); DEREF(11); DEREF(3); DEREF(9); DEREF(15); DEREF(5);)
BENCHMARK(14, DEREF(0); DEREF(8); DEREF(4); DEREF(12); DEREF(2); DEREF(10); DEREF(6); DEREF(14); DEREF(1); DEREF(11); DEREF(3); DEREF(9); DEREF(15); DEREF(5); DEREF(13);)
BENCHMARK(15, DEREF(0); DEREF(8); DEREF(4); DEREF(12); DEREF(2); DEREF(10); DEREF(6); DEREF(14); DEREF(1); DEREF(11); DEREF(3); DEREF(9); DEREF(15); DEREF(5); DEREF(13); DEREF(7);)
E 8
I 8
D 11
BENCHMARK(0, REPEAT_0, DEREF)
BENCHMARK(1, REPEAT_1, DEREF)
BENCHMARK(2, REPEAT_2, DEREF)
BENCHMARK(3, REPEAT_3, DEREF)
BENCHMARK(4, REPEAT_4, DEREF)
BENCHMARK(5, REPEAT_5, DEREF)
BENCHMARK(6, REPEAT_6, DEREF)
BENCHMARK(7, REPEAT_7, DEREF)
BENCHMARK(8, REPEAT_8, DEREF)
BENCHMARK(9, REPEAT_9, DEREF)
BENCHMARK(10, REPEAT_10, DEREF)
BENCHMARK(11, REPEAT_11, DEREF)
BENCHMARK(12, REPEAT_12, DEREF)
BENCHMARK(13, REPEAT_13, DEREF)
BENCHMARK(14, REPEAT_14, DEREF)
BENCHMARK(15, REPEAT_15, DEREF)
E 8
E 4

bench_f benchmarks[] = {
	benchmark_0,
	benchmark_1,
	benchmark_2,
	benchmark_3,
	benchmark_4,
	benchmark_5,
	benchmark_6,
D 4
	benchmark_7
E 4
I 4
	benchmark_7,
	benchmark_8,
	benchmark_9,
	benchmark_10,
	benchmark_11,
	benchmark_12,
	benchmark_13,
	benchmark_14,
	benchmark_15
E 4
};
E 11

/*
 * Assumptions:
 *
 * 1) Cache lines are a multiple of pointer-size words
 * 2) Cache lines are no larger than 1/8 of a page (typically 512 bytes)
 * 3) Pages are an even multiple of cache lines
 */
int
main(int ac, char **av)
{
D 6
	int	i, j, l, len;
E 6
I 6
D 15
	int	i, j, k, l, len;
E 15
I 15
	int	i;
E 15
E 6
	int	c;
	int	warmup = 0;
	int	repetitions = TRIES;
	int	print_cost = 0;
D 14
	int	maxlen = 32 * 1024 * 1024;
E 14
I 14
D 15
	int	maxlen = 64 * 1024 * 1024;
E 15
I 15
	size_t	len;
	size_t	maxlen = 64 * 1024 * 1024;
E 15
E 14
D 4
	double	time;
E 4
I 4
D 6
	double	load_parallelism;
E 4
I 3
	result_t base, wide, *r_save;
E 6
I 6
D 12
	double	baseline, max_load_parallelism, load_parallelism;
	result_t **results, *r_save;
E 12
I 12
	double	par;
E 12
E 6
E 3
D 11
	struct _state state;
E 11
I 11
	struct mem_state state;
E 11
	char   *usage = "[-c] [-L <line size>] [-M len[K|M]] [-W <warmup>] [-N <repetitions>]\n";

D 14
	state.line = getpagesize() / 8;
E 14
I 14
	state.line = getpagesize() / 16;
E 14
	state.pagesize = getpagesize();

	while (( c = getopt(ac, av, "cL:M:W:N:")) != EOF) {
		switch(c) {
		case 'c':
			print_cost = 1;
			break;
		case 'L':
			state.line = atoi(optarg);
I 3
			if (state.line < sizeof(char*))
				state.line = sizeof(char*);
E 3
			break;
		case 'M':
D 7
			l = strlen(optarg);
			if (optarg[l-1] == 'm' || optarg[l-1] == 'M') {
				maxlen = 1024 * 1024;
				optarg[l-1] = 0;
			} else if (optarg[l-1] == 'k' || optarg[l-1] == 'K') {
				maxlen = 1024;
				optarg[l-1] = 0;
			}
			maxlen *= atoi(optarg);
E 7
I 7
			maxlen = bytes(optarg);
E 7
			break;
		case 'W':
			warmup = atoi(optarg);
			break;
		case 'N':
			repetitions = atoi(optarg);
			break;
		default:
			lmbench_usage(ac, av, usage);
			break;
		}
	}

D 3
	for (i = sizeof(char*); i <= maxlen; i<<=1) { 
E 3
I 3
D 4
	for (i = 8 * state.line; i <= maxlen; i<<=1) { 
E 4
I 4
D 6
	for (i = 16 * state.line; i <= maxlen; i<<=1) { 
E 4
E 3
		state.len = i;
E 6
I 6
D 11
	results = (result_t**)malloc(MAX_LOAD_PARALLELISM * sizeof(result_t*));
	for (i = 0; i < MAX_LOAD_PARALLELISM; ++i) {
E 11
I 11
D 12
	results = (result_t**)malloc(MAX_MEM_PARALLELISM * sizeof(result_t*));
	for (i = 0; i < MAX_MEM_PARALLELISM; ++i) {
E 11
		results[i] = (result_t*)malloc(sizeof(result_t));
	}
E 6
D 3
		benchmp(initialize, benchmarks[0], cleanup, 0, 1, 
			warmup, repetitions, &state);
E 3

E 12
I 6
D 11
	for (i = MAX_LOAD_PARALLELISM * state.line; i <= maxlen; i<<=1) { 
E 11
I 11
	for (i = MAX_MEM_PARALLELISM * state.line; i <= maxlen; i<<=1) { 
E 11
D 12
		state.len = i;
E 6
D 3
		/* We want nanoseconds / load. */
		time = (1000. * (double)gettime()) / (100. * (double)get_n());

		benchmp(initialize, benchmarks[7], cleanup, 0, 1, 
			warmup, repetitions, &state);
E 3
I 3
		r_save = get_results();
D 6
		insertinit(&base);
		insertinit(&wide);
E 6
		
I 6
D 11
		for (k = 0; k < MAX_LOAD_PARALLELISM; ++k) {
E 11
I 11
		for (k = 0; k < MAX_MEM_PARALLELISM; ++k) {
E 11
			insertinit(results[k]);
		}

E 6
		for (j = 0; j < TRIES; ++j) {
D 6
			benchmp(initialize, benchmarks[0], cleanup, 0, 1, 
				warmup, repetitions, &state);
			insertsort(gettime(), get_n(), &base);

D 4
			benchmp(initialize, benchmarks[7], cleanup, 0, 1, 
E 4
I 4
			benchmp(initialize, benchmarks[15], cleanup, 0, 1, 
E 4
				warmup, repetitions, &state);
D 4
			insertsort(gettime(), 8 * get_n(), &wide);
E 4
I 4
			insertsort(gettime(), 16 * get_n(), &wide);
E 6
I 6
D 11
			for (k = 0; k < MAX_LOAD_PARALLELISM; ++k) {
E 11
I 11
			for (k = 0; k < MAX_MEM_PARALLELISM; ++k) {
E 11
I 8
				state.width = k + 1;
E 8
D 11
				benchmp(initialize, benchmarks[k], cleanup, 
E 11
I 11
				benchmp(mem_initialize, mem_benchmarks[k], mem_cleanup, 
E 11
					0, 1, warmup, repetitions, &state);
D 8
				insertsort(gettime(), (k + 1) * get_n(), results[k]);
E 8
I 8
				insertsort(gettime(), state.width * get_n(), results[k]);
E 8
			}
		}
		set_results(results[0]);
		baseline = (double)gettime() / (double)get_n();
		max_load_parallelism = 1.;

D 11
		for (k = 1; k < MAX_LOAD_PARALLELISM; ++k) {
E 11
I 11
		for (k = 1; k < MAX_MEM_PARALLELISM; ++k) {
E 11
			set_results(results[k]);
			load_parallelism = baseline;
			load_parallelism /= (double)gettime() / (double)get_n();
			if (load_parallelism > max_load_parallelism) {
				max_load_parallelism = load_parallelism;
			}
E 6
E 4
		}
D 6
		set_results(&base);
D 4
		time = (double)gettime() / (double)get_n();
E 4
I 4
		load_parallelism = (double)gettime() / (double)get_n();
E 6
E 4
E 3

D 3
		time /= (1000. * (double)gettime()) / (100. * (double)(8 * get_n()));
		j = (int)(time + 0.5);
E 3
I 3
D 6
		set_results(&wide);
D 4
		time /= (double)gettime() / get_n();
E 4
I 4
		load_parallelism /= (double)gettime() / get_n();
E 4
		set_results(r_save);
E 6
I 6
D 8
		fprintf(stderr, "%.5f %.2f\n", 
E 8
I 8
		fprintf(stderr, "%.6f %.2f\n", 
E 8
			state.len / (1000. * 1000.), max_load_parallelism);
E 12
I 12
		par = par_mem(i, warmup, repetitions, &state);
E 12
E 6
E 3

D 3
		fprintf(stderr, "loads: %d loads %d bytes\n", j, state.len);
E 3
I 3
D 4
		fprintf(stderr, "loads: %.5f loads %d bytes\n", time, state.len);
E 4
I 4
D 6
		fprintf(stderr, "%.5f %.3f\n", 
			state.len / (1000. * 1000.), load_parallelism);
E 6
I 6
D 12
		set_results(r_save);
E 12
I 12
D 13
		fprintf(stderr, "%.6f %.2f\n", i / (1000. * 1000.), par);
		fflush(stderr);
E 13
I 13
		if (par > 0.) {
			fprintf(stderr, "%.6f %.2f\n", 
				i / (1000. * 1000.), par);
		}
E 13
E 12
E 6
E 4
E 3
	}

D 4
#if 0
	if (print_cost) {
		fprintf(stderr, "cache: %d bytes %.5f nanoseconds\n", len, time);
	} else {
		fprintf(stderr, "cache: %d bytes\n", len);
	}
#endif

E 4
D 12
	return(0);
E 12
I 12
	exit(0);
E 12
}


D 11
/*
 * This will access len bytes
 */
void
initialize(void* cookie)
{
D 3
	int i, j, k, nwords, nlines, nbytes, npages;
E 3
I 3
	int i, j, k, nwords, nlines, nbytes, npages, npointers;
E 3
	unsigned int r;
	char ***pages;
	int    *lines;
	int    *words;
	struct _state* state = (struct _state*)cookie;
	register char *p = 0 /* lint */;

I 3
	npointers = state->len / state->line;
E 3
	nbytes = state->len;
	nwords = state->line / sizeof(char*);
	nlines = state->pagesize / state->line;
	npages = (nbytes + state->pagesize) / state->pagesize;

D 10
	words = (int*)malloc(nwords * sizeof(int));
	lines = (int*)malloc(nlines * sizeof(int));
E 10
I 10
	srand(getpid());

	words = permutation(nwords);
	lines = permutation(nlines);
E 10
	pages = (char***)malloc(npages * sizeof(char**));
	state->p[0] = state->addr = (char*)malloc(nbytes + 2 * state->pagesize);

	if ((unsigned long)state->p[0] % state->pagesize) {
		state->p[0] += state->pagesize - (unsigned long)state->p[0] % state->pagesize;
	}

	if (state->addr == NULL || pages == NULL) {
		exit(0);
	}

D 10
	srand(getpid());

E 10
	/* first, layout the sequence of page accesses */
	p = state->p[0];
	for (i = 0; i < npages; ++i) {
		pages[i] = (char**)p;
		p += state->pagesize;
	}

	/* randomize the page sequences (except for zeroth page) */
	r = (rand() << 15) ^ rand();
	for (i = npages - 2; i > 0; --i) {
		char** l;
		r = (r << 1) ^ (rand() >> 4);
		l = pages[(r % i) + 1];
		pages[(r % i) + 1] = pages[i + 1];
		pages[i + 1] = l;
	}

	/* layout the sequence of line accesses */
	for (i = 0; i < nlines; ++i) {
D 10
		lines[i] = i * state->pagesize / (nlines * sizeof(char*));
	}

	/* randomize the line sequences */
	for (i = nlines - 2; i > 0; --i) {
		int l;
		r = (r << 1) ^ (rand() >> 4);
		l = lines[(r % i) + 1];
		lines[(r % i) + 1] = lines[i];
		lines[i] = l;
E 10
I 10
		lines[i] *= state->pagesize / (nlines * sizeof(char*));
E 10
	}

	/* layout the sequence of word accesses */
	for (i = 0; i < nwords; ++i) {
D 10
		words[i] = i * state->line / (nwords * sizeof(char*));
	}

	/* randomize the word sequences */
	for (i = nwords - 2; i > 0; --i) {
		int l;
		r = (r << 1) ^ (rand() >> 4);
		l = words[(r % i) + 1];
		words[(r % i) + 1] = words[i];
		words[i] = l;
E 10
I 10
		words[i] *= state->line / (nwords * sizeof(char*));
E 10
	}

	/* setup the run through the pages */
	for (i = 0, k = 0; i < npages; ++i) {
D 3
		for (j = 0; j < nlines - 1; ++j) {
E 3
I 3
		for (j = 0; j < nlines - 1 && k < npointers - 1; ++j) {
E 3
			pages[i][lines[j]+words[k%nwords]] = (char*)(pages[i] + lines[j+1] + words[(k+1)%nwords]);
			k++;
		}
D 3
		if (i == npages - 1) {
E 3
I 3
		if (i == npages - 1 || k == npointers - 1) {
E 3
			pages[i][lines[j]+words[k%nwords]] = (char*)(pages[0] + lines[0] + words[0]);
		} else {
			pages[i][lines[j]+words[k%nwords]] = (char*)(pages[i+1] + lines[0] + words[(k+1)%nwords]);
		}
		k++;
	}

	free(pages);
	free(lines);
	free(words);

I 10
	state->p[0] = (char*)(pages[0] + lines[0] + words[0]);
E 10
	for (p = state->p[0], i = 0; i < k; ++i) {
D 4
		if (i % (k/8) == 0) {
			state->p[i / (k/8)] = p;
E 4
I 4
D 6
		if (i % (k/16) == 0) {
			state->p[i / (k/16)] = p;
E 6
I 6
D 8
		if (i % (k/MAX_LOAD_PARALLELISM) == 0) {
			state->p[i / (k/MAX_LOAD_PARALLELISM)] = p;
E 8
I 8
		if (i % (k/state->width) == 0) {
			state->p[i / (k/state->width)] = p;
E 8
E 6
E 4
		}
		p = *(char**)p;
	}
}

void cleanup(void* cookie)
{
	struct _state* state = (struct _state*)cookie;
	free(state->addr);
	state->addr = NULL;
}
E 11
D 3



E 3
E 2
I 1
E 1
