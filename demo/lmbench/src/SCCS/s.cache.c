H34509
s 00067/00052/00684
d D 1.31 01/06/19 10:34:08 staelin 32 31
c Improve cache's design.  Fix some accounting problems in 
c fixup_chunk with swapped variable, simplify code to use a
c subroutine to sort pages by latencies.  Fix bug in test_chunk
c to ensure that we use chunks for even memory hunks smaller
c than the maximum chunk size (it used to be we only used
c the chunking method if the amount of memory was larger than
c the maximum possible chunk size, whereas it should be used
c always, only with a minimum chunk size of one page.).
cC
cK30504
e
s 00001/00001/00735
d D 1.30 01/06/13 13:01:10 staelin 31 30
c Increase search space for "good" pages in cache.  This slows things 
c down but should get it working again...
cC
cK64512
e
s 00003/00059/00733
d D 1.29 01/06/13 11:01:19 staelin 30 29
c Remove or comment out lots of debug statements from cache
cC
cK64356
e
s 00076/00020/00716
d D 1.28 01/06/12 17:38:04 staelin 29 28
c Fix a number of bugs in cache; this is the first working version
c (except that it includes scads of debug print statements)
cC
cK16980
e
s 00108/00047/00628
d D 1.27 01/05/23 12:45:26 staelin 28 27
c Changed cache's fixup_chunk() to try an reduce the number of experiments
c it conducts and to try and maximize the benefit from those experiments.
c Basically, only test at most 2*npages substitutions per chunk, rather than
c 2*npages per pages.
cC
cK21846
e
s 00157/00081/00518
d D 1.26 01/05/22 17:26:14 staelin 27 26
c Add new algorithm to cache, which tries to rapidly identify chunks
c of pages that contain collisions, and then find the best replacement
c for that chunk (building on existing pages as much as possible).
cC
cK08518
e
s 00135/00092/00464
d D 1.25 01/05/21 14:52:43 staelin 26 25
c Restructure of the code:
c - pull code that tries to fixup a chunk into a separate routine
c - separate logic that identifies cache boundaries and cache parameters
c   into a two-pass method
c - fix a bug with the command-line handling that caused a SEGFAULT
cC
cK28918
e
s 00003/00000/00553
d D 1.24 01/05/02 20:16:20 staelin 25 24
c - Change initial page order from random to sequential, in case the OS actually did do page coloring to minimize
c   cache conflicts.  In this way cache only needs to fix things up when the OS goofed and didn't minimize the
c   cache conflicts.
cC
cK16682
e
s 00017/00004/00536
d D 1.23 01/05/02 10:29:38 staelin 24 23
c - fix a bug in the cache latency detection caused by faulty abs()
c - tweak cache's data collection algorithm so it tries harder to find the best set of pages
cC
cK04882
e
s 00018/00008/00522
d D 1.22 01/04/10 10:18:08 staelin 23 22
c Add new heuristics to the new page search so it always retains the
c fastest page, and so it keeps looking for faster pages until it finds
c one that probably wouldn't have triggered the new-page search in the
c first place.
cC
cK49272
e
s 00006/00005/00524
d D 1.21 01/04/10 09:51:51 staelin 22 21
c fix bug in cache line results handling (the result was being lost).
cC
cK32264
e
s 00269/00085/00260
d D 1.20 01/04/09 16:55:34 staelin 21 20
c Nearly a complete rewrite of cache.c to make it possible to factor
c out cache collisions due to direct-mapped or low-associativity caches.
c There is a new algorithm which iterates through the pages to try and
c identify pages which collide with other pages, and then it tries to
c find a replacement page which doesn't collide (as much) with other
c pages.  Needless to say, this process can be excruciatingly slow, but
c it does seem to work pretty well.
cC
cHhpli69.hpli.hpl.hp.com
cK32077
cZ+03:00
e
s 00046/00026/00299
d D 1.19 00/10/19 17:00:29 staelin 20 19
c - Tweak cache boundary detection code
c - Add new 'signal' to cache boundary detection
c - Add memory parallelism calculation for main memory too
c - Fix bug in cache parallelism calculation
c - Fix bug in cache latency calculation
cC
cK06396
e
s 00004/00002/00321
d D 1.18 00/10/18 14:28:44 staelin 19 18
c - Slight tweak to cache boundary detection code to (hopefully) make
c   it more robust
cC
cK21551
e
s 00021/00009/00302
d D 1.17 00/10/17 16:37:54 staelin 18 17
c - Automatically compute cache line size for largest cache
c - Improve heuristics that search for cache boundaries
cC
cK26312
e
s 00153/00124/00158
d D 1.16 00/10/16 17:16:57 staelin 17 16
c - Improve cache's algorithm for identifying cache boundaries
cC
cK03078
cZ+02:00
e
s 00004/00002/00278
d D 1.15 00/09/28 12:44:28 staelin 16 15
c - Tweak cache.c to print out more data
cC
cK44519
e
s 00021/00013/00259
d D 1.14 00/09/25 17:27:45 staelin 15 14
c - Added ability for cache to collect information about memory parallelism
c - Fixed bug so cache would correctly create variational data
cC
cK40577
e
s 00062/00003/00210
d D 1.13 00/09/24 12:58:51 staelin 14 13
c - Beginning of a rewrite of cache to measure more aspects of memory hierarchy to
c   try and determine cache sizes more accurately
cC
cK24574
e
s 00004/00154/00209
d D 1.12 00/09/18 16:44:08 staelin 13 12
c - Create lib_mem.h and lib_mem.c to hold common routines for memory subsystem analysis
cC
cK48231
e
s 00024/00032/00339
d D 1.11 00/09/13 12:41:40 staelin 12 11
c - Add "int* permutation(int N);" which returns a permutation of N integers
c 
cC
cK16750
e
s 00032/00019/00339
d D 1.10 00/07/31 14:50:21 staelin 11 10
c - Add checks for change in result variations; generally there is more variation in 
c   the results at the cache size than at other points, so we look for a peak in 
c   result variations.  For the purposes of discussion, variation = median / minimum.
cC
cK21717
e
s 00078/00034/00280
d D 1.9 00/07/31 11:31:12 staelin 10 9
c - Lots of tweaks to try and make it more accurate/stable, especially on systems without
c   page coloring.  We are going to try and build a system which randomly chooses pages
c   from a subset of available pages.  This is repeated N times.  Hopefully one of them
c   has a better coloring that more accurately represents the actual cache size.
cC
cK55872
e
s 00103/00042/00211
d D 1.8 00/07/30 15:34:05 staelin 9 8
c - Update/replace the cache-size calculation logic
cC
cK21592
e
s 00002/00002/00251
d D 1.7 00/07/30 11:46:06 staelin 8 7
c - Change type of "iterations" from uint64 to iter_t, which is a u_long
cC
cK64373
e
s 00017/00004/00236
d D 1.6 00/07/05 17:14:36 staelin 7 6
c - Add a second level of statistical median filtering on the results; since each
c   benchmark's memory access patterns are random, we need a second level of filtering
c   to determine the "representative" value.
cC
cK64187
e
s 00004/00002/00236
d D 1.5 00/07/05 14:37:17 staelin 6 5
c - tweaks to benchmark so if you change the memory buffer the benchmark doesn't core dump
cC
cK44892
e
s 00018/00007/00220
d D 1.4 00/07/04 14:55:51 staelin 5 4
c - Update to incorporate new "-W <warmup>" and "-N <repetitions>" flags
cC
cK32572
e
s 00025/00007/00202
d D 1.3 00/07/03 15:44:08 staelin 4 3
c - Fixup some buglets
c - It now assumes that a cache line is 1/4 of a page, unless someone passes in the line
c   size in the "-L <line size>" flag
c - Since the default line size guess is likely to be wrong, randomize the accesses 
c   within a cache line so we are likely to use all the lines in the cache (and don't
c   'waste' huge chunks of direct-mapped caches by not accessing those lines).
cC
cK15475
e
s 00013/00009/00196
d D 1.2 00/07/02 18:34:22 staelin 3 2
c - Incomplete first draft of cache.c.  It can measure memory performance at various
c   memory sizes, but doesn't yet have the intelligent search to find cache sizes.
cC
cK35297
e
s 00205/00000/00000
d D 1.1 00/07/02 17:28:03 staelin 2 1
cK31050
cO-rw-rw-r--
e
s 00000/00000/00000
d D 1.0 00/07/02 17:28:02 staelin 1 0
c BitKeeper file /tmp_mnt/usr/WebPaper/users/staelin/src/LMbench/src/cache.c
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHhpli8.hpli.hpl.hp.com
cK28857
cPsrc/cache.c
cR3b0629ed1b004240
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
D 5
 * tlb.c - guess the cache line size
E 5
I 5
 * cache.c - guess the cache size(s)
E 5
 *
D 6
 * usage: tlb
E 6
I 6
 * usage: cache [-c] [-L <line size>] [-M len[K|M]] [-W <warmup>] [-N <repetitions>]
E 6
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

I 24

E 24
I 14
struct cache_results {
	int	len;
D 17
	int	line;
E 17
I 17
	int	maxlen;
I 21
	int	line;
	int	mline;
E 21
E 17
	double	latency;
	double	variation;
I 15
D 17
	double	parallelism;
E 17
I 17
	double	ratio;
I 20
	double	slope;
E 20
E 17
E 15
};

I 17
int	find_cache(int start, int n, struct cache_results* p);
int	collect_data(int start, int line, int maxlen, 
D 21
		int warmup, int repetitions, struct cache_results** pdata);
int	search(int left, int right, int line, 
		int warmup, int repetitions, struct cache_results* p);
int	collect_sample(int line, 
		int warmup, int repetitions, struct cache_results* p);
double	measure(int size, int line, int maxlen, 
		int warmup, int repetitions, double* variation);
E 21
I 21
		     int repetitions, struct cache_results** pdata);
void	search(int left, int right, int repetitions, 
	       struct mem_state* state, struct cache_results* p);
int	collect_sample(int repetitions, struct mem_state* state, 
			struct cache_results* p);
double	measure(int size, int repetitions, 
		double* variation, struct mem_state* state);
double	remove_chunk(int i, int chunk, int npages, int* pages, 
		       int len, int repetitions, struct mem_state* state);
I 27
int	test_chunk(int i, int chunk, int npages, int* pages, int len, 
		   double *baseline, double chunk_baseline,
		   int repetitions, struct mem_state* state);
E 27
I 26
int	fixup_chunk(int i, int chunk, int npages, int* pages, int len, 
D 27
		    double *baseline, double *nodiff_chunk_baseline,
		    double chunk_baseline,
E 27
I 27
		    double *baseline, double chunk_baseline,
E 27
		    int repetitions, struct mem_state* state);
I 29
void	check_memory(int size, struct mem_state* state);
I 32
void	pagesort(int n, int* pages, double* latencies);
E 32
E 29
E 26
E 21
E 17

I 24
#ifdef ABS
#undef ABS
#endif
#define ABS(a) ((a) < 0 ? -(a) : (a))

I 28
#define SWAP(a,b) {int _tmp = (a); (a) = (b); (b) = _tmp;}

E 28
E 24
D 17
int collect_data(int start, int line, int maxlen, 
		 int warmup, int repetitions, struct cache_results** pdata);
E 14
D 13
struct _state {
	char*	addr;
	char*	p;
	int	len;
I 10
	int	maxlen;
E 10
I 3
	int	line;
E 3
	int	pagesize;
};

E 13
D 9
void compute_times(struct _state* state, double* tlb_time, double* cache_time);
E 9
I 9
int find_cache(int start, int line, 
	       int maxlen, int warmup, int repetitions, double* time);
D 10
double measure(int size, int line, int warmup, int repetitions);
E 10
I 10
D 11
double measure(int size, int line, int maxlen, int warmup, int repetitions);
E 11
I 11
double measure(int size, int line, int maxlen, int warmup, 
	       int repetitions, double* variation);
E 11
E 10
E 9
D 3
void initialize_tlb(void* cookie);
void initialize_cache(void* cookie);
E 3
I 3
D 13
void initialize(void* cookie);
E 3
D 8
void benchmark(uint64 iterations, void* cookie);
E 8
I 8
void benchmark(iter_t iterations, void* cookie);
E 8
void cleanup(void* cookie);

#define	ONE	p = (char **)*p;
#define	FIVE	ONE ONE ONE ONE ONE
#define	TEN	FIVE FIVE
#define	FIFTY	TEN TEN TEN TEN TEN
#define	HUNDRED	FIFTY FIFTY
E 13

I 9
D 11
#define THRESHOLD 1.75
E 11
I 11
#define THRESHOLD 2.5
E 17
I 17
#define THRESHOLD 1.5
E 17
E 11

I 21
#define	FIVE(m)		m m m m m
#define	TEN(m)		FIVE(m) FIVE(m)
#define	FIFTY(m)	TEN(m) TEN(m) TEN(m) TEN(m) TEN(m)
#define	HUNDRED(m)	FIFTY(m) FIFTY(m)
#define DEREF		p = (char**)*p;

static char **addr_save = NULL;

void
mem_benchmark(iter_t iterations, void *cookie)
{
	register char **p;
	struct mem_state* state = (struct mem_state*)cookie;

	p = addr_save ? addr_save : (char**)state->p[0];
	while (iterations-- > 0) {
		HUNDRED(DEREF);
	}
	addr_save = p;
}


E 21
E 9
/*
 * Assumptions:
 *
 * 1) Cache lines are a multiple of pointer-size words
D 4
 * 2) Cache lines are smaller than 1/2 a page size
E 4
I 4
D 5
 * 2) Cache lines are smaller than 1/4 a page size
E 5
I 5
 * 2) Cache lines are no larger than 1/8 of a page (typically 512 bytes)
E 5
E 4
 * 3) Pages are an even multiple of cache lines
 */
int
main(int ac, char **av)
{
D 7
	int	i, l, len;
E 7
I 7
D 9
	int	i, j, l, len;
E 9
I 9
D 10
	int	line, l1_cache, l2_cache;
E 9
E 7
	int	c;
E 10
I 10
D 12
	int	line, l1_cache, l2_cache, c;
E 12
I 12
D 17
	int	line, l1_cache, l2_cache, l3_cache, c;
E 17
I 17
	int	c;
D 20
	int	i, n, start, level, prev;
E 20
I 20
	int	i, j, n, start, level, prev, min;
E 20
D 18
	int	line;
E 18
I 18
	int	line = -1;
E 18
E 17
E 12
E 10
I 5
	int	warmup = 0;
	int	repetitions = TRIES;
E 5
	int	print_cost = 0;
	int	maxlen = 32 * 1024 * 1024;
I 26
	int	*levels;
E 26
D 10
	double	time;
E 10
I 10
D 11
	double	l1_time, l2_time, mem_time;
E 11
I 11
D 12
	double	l1_time, l2_time, mem_time, variation;
E 12
I 12
D 17
	double	l1_time, l2_time, l3_time, mem_time, variation;
E 17
I 17
D 20
	double	par;
E 20
I 20
	double	par, maxpar;
E 20
E 17
E 12
E 11
E 10
I 7
D 9
	result_t r, *r_save;
E 7
	struct _state state;
E 9
D 3
	char   *usage = "[-c] [-M len[K|M]]\n";
E 3
I 3
D 5
	char   *usage = "[-c] [-L <line size>] [-M len[K|M]]\n";
E 5
I 5
	char   *usage = "[-c] [-L <line size>] [-M len[K|M]] [-W <warmup>] [-N <repetitions>]\n";
I 14
D 17
	int	n;
E 17
	struct cache_results* r;
I 17
	struct mem_state state;
E 17
E 14
E 5
E 3

I 3
D 4
	state.line = sizeof(char*);
E 4
I 4
D 5
	state.line = getpagesize() / (4 * sizeof(char*));
E 5
I 5
D 9
	state.line = getpagesize() / 8;
E 5
E 4
E 3
	state.pagesize = getpagesize();
E 9
I 9
D 18
	line = getpagesize() / 8;
E 9

E 18
D 3
	while (( c = getopt(ac, av, "cM:")) != EOF) {
E 3
I 3
D 5
	while (( c = getopt(ac, av, "cL:M:")) != EOF) {
E 5
I 5
	while (( c = getopt(ac, av, "cL:M:W:N:")) != EOF) {
E 5
E 3
		switch(c) {
		case 'c':
			print_cost = 1;
			break;
I 3
		case 'L':
D 9
			state.line = atoi(optarg);
I 7
			if (state.line < sizeof(char*))
				state.line = sizeof(char*);
E 9
I 9
			line = atoi(optarg);
			if (line < sizeof(char*))
				line = sizeof(char*);
E 9
E 7
			break;
E 3
		case 'M':
D 9
			l = strlen(optarg);
			if (optarg[l-1] == 'm' || optarg[l-1] == 'M') {
				maxlen = 1024 * 1024;
				optarg[l-1] = 0;
			} else if (optarg[l-1] == 'k' || optarg[l-1] == 'K') {
				maxlen = 1024;
				optarg[l-1] = 0;
			}
			maxlen *= atoi(optarg);
E 9
I 9
			maxlen = bytes(optarg);
E 9
			break;
I 5
		case 'W':
			warmup = atoi(optarg);
			break;
		case 'N':
			repetitions = atoi(optarg);
			break;
E 5
		default:
			lmbench_usage(ac, av, usage);
			break;
		}
	}

I 26
	state.width = 1;
	state.len = maxlen;
	state.maxlen = maxlen;
	state.pagesize = getpagesize();

E 26
I 18
	if (line <= 0) {
D 26
		state.width = 1;
		state.len = maxlen;
		state.maxlen = maxlen;
		state.pagesize = getpagesize();
E 26
		line = line_find(maxlen, warmup, repetitions, &state);
		if (line <= 0)
D 21
			line = getpagesize() / 8;
E 21
I 21
			line = getpagesize() / 16;
		state.line = line;
E 21
	}

E 18
D 3
	for (i = 8; i < maxlen; i<<=1) {
E 3
I 3
D 4
	for (i = 8; i <= maxlen; i<<=1) {
E 4
I 4
D 9
	for (i = sizeof(char*); i <= maxlen; i<<=1) {
E 4
E 3
		state.len = i;
E 9
I 9
D 10
	l1_cache = find_cache(sizeof(char*), 
			      line, maxlen, warmup, repetitions, &time);
E 10
I 10
D 12
	l2_cache = maxlen;
E 12
E 10
E 9
D 3
		benchmp(initialize, benchmark, cleanup, 0, 1, state);
E 3
I 3
D 5
		benchmp(initialize, benchmark, cleanup, 0, 1, &state);
E 5
I 5
D 7
		benchmp(initialize, benchmark, cleanup, 0, 1, 
			warmup, repetitions, &state);
E 7
I 7
D 14

E 14
I 14
D 17
#if 1
E 17
D 21
	n = collect_data(512, line, maxlen, warmup, repetitions, &r);
E 21
I 21
	n = collect_data(512, line, maxlen, repetitions, &r);
I 26
	r[n-1].line = line;
	levels = (int*)malloc(n * sizeof(int));
	bzero(levels, n * sizeof(int));
E 26
E 21
D 17
#else
E 14
D 9
		r_save = get_results();
		insertinit(&r);
E 9
I 9
D 10
	if (l1_cache >= maxlen)
		return (0);
E 10
I 10
	l1_cache = find_cache(512, line, maxlen, warmup, repetitions, &l1_time);
I 12
	l2_cache = maxlen;
	l3_cache = maxlen;
E 12
E 10
E 9

D 9
		for (j = 0; j < TRIES; ++j) {
			benchmp(initialize, benchmark, cleanup, 0, 1, 
				warmup, repetitions, &state);
			insertsort(gettime(), get_n(), &r);
		}
		set_results(&r);
E 9
I 9
D 10
	fprintf(stderr, "L1 cache: %d bytes %.2f nanoseconds\n", l1_cache, time);
E 10
I 10
	if (l1_cache < maxlen) {
D 11
		l2_cache = find_cache(l1_cache, line, 
E 11
I 11
		int	start;
		for (start = 512; start < l1_cache; start<<=1)
			;
		l2_cache = find_cache(start, line, 
E 11
				      maxlen, warmup, repetitions, &l2_time);
	}
E 17
E 10
E 9
E 7
E 5
E 3

I 12
D 17
	if (l2_cache < maxlen) {
		int	start;
		for (start = 512; start < l2_cache; start<<=1)
E 17
I 17
D 20
	for (start = 0, prev = -1, level = 1; 
E 20
I 20
D 26
	for (start = 0, prev = 0, level = 1; 
E 26
I 26
	for (start = 0, prev = 0, level = 0; 
E 26
E 20
	     (i = find_cache(start, n, r)) >= 0; 
	     ++level, start = i + 1, prev = i) 
	{
		/* 
		 * performance is not greatly improved over main memory,
		 * so it is likely not a cache boundary
		 */
		if (r[i].latency / r[n-1].latency > 0.5) break;

		/* 
		 * is cache boundary "legal"? (e.g. 2^N or 1.5*2^N) 
		 * cache sizes are "never" 1.25*2^N or 1.75*2^N
		 */
		for (c = r[i].len; c > 0x7; c >>= 1)
E 17
			;
D 17
		l3_cache = find_cache(start, line, 
				      maxlen, warmup, repetitions, &l3_time);
	}
E 17
I 17
		if (c == 5 || c == 7) {
			i++;
			if (i >= n) break;
		}
E 17

I 26
		levels[level] = i;
	}

	for (i = 0; i < level; ++i) {
		prev = (i > 0 ? levels[i-1]: -1);

E 26
E 12
D 9
		/* We want nanoseconds / load. */
		time = (1000. * (double)gettime()) / (100. * (double)get_n());
D 3
		fprintf(stderr, "tlb: %d bytes %.5f nanoseconds\n", state.len, time);
E 3
I 3
		fprintf(stderr, "cache: %d bytes %.5f nanoseconds\n", state.len, time);
E 9
I 9
D 10
	l2_cache = find_cache(l1_cache,
			      line, maxlen, warmup, repetitions, &time);
E 10
I 10
D 11
	mem_time = measure(maxlen, line, maxlen, warmup, repetitions);
E 11
I 11
D 17
	mem_time = measure(maxlen, line, maxlen, warmup, repetitions, &variation);
E 17
I 17
D 21
		/* Compute line size for cache */
		state.width = 1;
		state.len = r[i].len;
		state.maxlen = r[i].len;
		state.pagesize = getpagesize();
D 20
		state.line = line_find(2*r[i].len, warmup, repetitions, &state);
E 20
I 20
		state.line = line_find(2 * r[i].len, warmup, repetitions, &state);
E 20
		if (state.line == 0) state.line = line;

E 21
D 20
		/* Compute memory parallelism for cache */
		par = par_mem(r[i].len/2, warmup, repetitions, &state);
E 20
I 20
		/* locate most likely cache latency */
D 26
		for (j = prev, min = prev; j < i; ++j) {
D 21
			if (r[j].latency > 0. && r[j].ratio < r[min].ratio)
E 21
I 21
D 24
			if (r[j].latency <= 0.) continue;
			if (abs(r[j].slope) < abs(r[min].slope))
E 24
I 24
			if (r[j].latency <= 0. || r[j].slope == -1.) continue;
E 26
I 26
		for (j = min = prev + 1; j < levels[i]; ++j) {
			if (r[j].latency <= 0.) continue;
E 26
D 30
/*
			fprintf(stderr, 
				"r[%d].s = %8.3f, r[%d].s = %8.3f, r[%d] = %10.6f\n", 
				j, r[j].slope, min, r[min].slope,
				j, r[j].len / (1000. * 1000.));
/**/
E 30
D 26
			if (ABS(r[j].slope) < ABS(r[min].slope))
E 26
I 26
			if (r[min].latency <= 0.
			    || ABS(r[j].slope) < ABS(r[min].slope)) {
E 26
E 24
E 21
				min = j;
I 26
			}
E 26
		}
E 20

I 21
		/* Compute line size */
D 26
		if (i + 3 < n) {
			if (r[i+3].line <= 0 || line <= r[i+3].line) {
				state.width = 1;
				state.len = r[i+3].len;
				state.maxlen = r[i+3].maxlen;
				state.pagesize = getpagesize();
				r[i+3].line = line_find(r[i+3].len, warmup, 
							repetitions, &state);
E 26
I 26
		if (i == level - 1) {
			line = r[n-1].line;
		} else {
			j = (levels[i] + levels[i+1]) / 2;
			for (line = -1; line <= 0 && j < n; ++j) {
				r[j].line = line_find(r[j].len, warmup,
						      repetitions, &state);
				line = r[j].line;
E 26
			}
D 26
			if (0 < r[i+3].line && r[i+3].line < line)
D 22
				state.line = r[i+3].line;
E 22
I 22
				line = r[i+3].line;
E 26
E 22
		}

E 21
D 20
		if (prev >= 0) {
			for (prev++; prev < i && r[prev].latency < 0.; prev++)
				;
E 20
I 20
		/* Compute memory parallelism for cache */
D 21
		maxpar = par_mem(r[min].len, warmup, repetitions, &state);
		for (j = prev + 2; j < i; ++j) {
			if (r[j].latency == -1.) continue;
E 21
I 21
D 26
		maxpar = par_mem(r[i].len, warmup, repetitions, &state);
		for (j = prev; j < i; ++j) {
			if (r[j].latency <= 0.) continue;
			if (r[j].len < 2 * r[prev].len)
				continue;
E 21
			par = par_mem(r[j].len, warmup, repetitions, &state);
			if (par > maxpar) {
				maxpar = par;
			}
E 20
		}
E 26
I 26
		maxpar = par_mem(r[levels[i]-1].len, warmup, 
				 repetitions, &state);
E 26
E 17
E 11
E 10
E 9
I 7

D 9
		set_results(r_save);
E 7
E 3
	}
E 9
I 9
D 10
	if (l2_cache >= maxlen)
		return (0);
E 10
I 10
D 17
	if (l1_cache < maxlen) {
		fprintf(stderr, "L1 cache: %d bytes %.2f nanoseconds\n", 
			l1_cache, l1_time);
E 17
I 17
		fprintf(stderr, 
		    "L%d cache: %d bytes %.2f nanoseconds %d linesize %.2f parallelism\n",
D 20
		    level, r[i].len, r[prev >= 0 ? prev : 0].latency, state.line, par);
E 20
I 20
D 22
		    level, r[i].len, r[min].latency, state.line, maxpar);
I 21
		state.line = line;
E 22
I 22
D 26
		    level, r[i].len, r[min].latency, line, maxpar);
E 26
I 26
		    i+1, r[levels[i]].len, r[min].latency, line, maxpar);
E 26
E 22
E 21
E 20
E 17
	}
I 17
D 20
	fprintf(stderr, "Memory latency: %.2f nanoseconds\n", r[n-1].latency);
E 20
I 20

	/* Compute memory parallelism for main memory */
D 21
	par = par_mem(r[n-1].len, warmup, repetitions, &state);
E 21
I 21
	j = n - 1;
	for (i = n - 1; i >= 0; i--) {
		if (r[i].latency < 0.) continue;
		if (r[i].latency > 0.99 * r[n-1].latency)
			j = i;
	}
	par = par_mem(r[j].len, warmup, repetitions, &state);
E 21

	fprintf(stderr, "Memory latency: %.2f nanoseconds %.2f parallelism\n",
		r[n-1].latency, par);
E 20
E 17

D 17
	if (l2_cache < maxlen) {
		fprintf(stderr, "L2 cache: %d bytes %.2f nanoseconds\n", 
			l2_cache, l2_time);
	}
E 17
I 17
	exit(0);
}
E 17
E 10
E 9

I 12
D 17
	if (l3_cache < maxlen) {
		fprintf(stderr, "L3 cache: %d bytes %.2f nanoseconds\n", 
			l3_cache, l3_time);
	}
E 17
I 17
int
find_cache(int start, int n, struct cache_results* p)
{
D 18
	int	i, j;
E 18
I 18
	int	i, j, prev;
E 18
	double	max = -1.;
E 17

I 18
D 19
	prev = (start == 0 ? start : start - 1);
E 19
I 19
	for (prev = (start == 0 ? start : start - 1); prev > 0; prev--) {
		if (p[prev].ratio > 0.0) break;
	}

E 19
E 18
E 12
I 5
D 9
#if 0
E 5
	if (print_cost) {
		fprintf(stderr, "cache: %d bytes %.5f nanoseconds\n", len, time);
	} else {
		fprintf(stderr, "cache: %d bytes\n", len);
	}
I 5
#endif
E 9
I 9
D 10
	fprintf(stderr, "L2 cache: %d bytes %.2f nanoseconds\n", l2_cache, time);
E 10
I 10
D 17
	fprintf(stderr, "Memory latency: %.2f nanoseconds\n", mem_time);
E 10
E 9
E 5
D 14

E 14
I 14
#endif
E 14
	return(0);
E 17
I 17
D 20
	for (i = start; i < n; ++i) {
E 20
I 20
	for (i = start, j = -1; i < n; ++i) {
E 20
		if (p[i].latency < 0.) continue;
D 18
		if (p[i].ratio > max) {
			j = i;
			max = p[i].ratio;
		} else if (max > THRESHOLD) {
			return j;
E 18
I 18
D 20
		if (p[prev].ratio <= p[i].ratio) {
			if (p[i].ratio > max) {
				j = i;
				max = p[i].ratio;
			} else if (max > THRESHOLD) {
				return j;
			}
E 20
I 20
		if (p[prev].ratio <= p[i].ratio && p[i].ratio > max) {
			j = i;
			max = p[i].ratio;
		} else if (p[i].ratio < max && THRESHOLD < max) {
			return j;
E 20
E 18
		}
I 18
		prev = i;
E 18
	}
	return -1;
E 17
}

I 9
int
I 14
collect_data(int start, int line, int maxlen, 
D 21
	     int warmup, int repetitions, struct cache_results** pdata)
E 21
I 21
	     int repetitions, struct cache_results** pdata)
E 21
{
	int	i;
D 17
	int	idx = 0;
E 17
I 17
	int	samples;
	int	idx;
E 17
	int	len = start;
	int	incr = start / 4;
	double	latency;
	double	variation;
	struct mem_state state;
	struct cache_results* p;

D 17
	state.width = 1;
	state.pagesize = getpagesize();
E 17

D 21
	*pdata = (struct cache_results*)malloc(sizeof(struct cache_results));
E 21
I 21
	state.width = 1;
	state.len = maxlen;
	state.maxlen = maxlen;
	state.line = line;
	state.pagesize = getpagesize();
	state.addr = NULL;
E 21

D 17
	for (len = start, incr = start / 4; len <= maxlen; incr<<=1) {
E 17
I 17
	/* count the (maximum) number of samples to take */
	for (len = start, incr = start / 4, samples = 0; len <= maxlen; incr<<=1) {
		for (i = 0; i < 4 && len <= maxlen; ++i, len += incr)
			samples++;
	}
D 21
	p = (struct cache_results*)
E 21
I 21
	*pdata = (struct cache_results*)
E 21
		malloc(samples * sizeof(struct cache_results));
D 21
	*pdata = p;
	
E 21
I 21

	p = *pdata;
E 21

	/* initialize the data */
	for (len = start, incr = start / 4, idx = 0; len <= maxlen; incr<<=1) {
E 17
		for (i = 0; i < 4 && len <= maxlen; ++i, ++idx, len += incr) {
D 15
			state.line = 2;
E 15
I 15
D 17
			state.line = sizeof(char*);
E 15
			state.len = len;
I 15
			state.maxlen = len;
E 15

			*pdata = (struct cache_results*)
				realloc(*pdata, (idx+1) * sizeof(struct cache_results));
			p = &((*pdata)[idx]);

D 15
			p->latency = measure(len, line, 
					     (2*len)<maxlen ? (2*len) : maxlen,
					     warmup, repetitions, &p->variation);

E 15
			p->len = len;
			p->line = line_find(len, 
					    warmup, repetitions, &state);

I 15
			p->latency = measure(len, line, maxlen, warmup,
					     repetitions, &p->variation);

			p->parallelism = par_mem(len, 
						 warmup, repetitions, &state);

E 15
			/**/
D 15
			fprintf(stderr, "%.6f\t%d\t%.5f\t%.5f\n", 
				p->len / (1000. * 1000.), 
				p->line, p->latency, p->variation);
E 15
I 15
D 16
			fprintf(stderr, "%.6f\t%d\t%.5f\t%.5f\t%.5f\n", 
E 16
I 16
			fprintf(stderr, 
				"%8.6f %4.4d %7.5f %7.5f %7.5f %7.5f\n", 
E 16
				p->len / (1000. * 1000.), p->line, 
D 16
				p->latency, p->variation, p->parallelism);
E 16
I 16
				p->latency, p->variation, p->parallelism,
				p->latency / (*pdata)[idx-(idx>1?1:0)].latency);
E 16
E 15
			/**/
E 17
I 17
			p[idx].len = len;
D 21
			p[idx].maxlen = maxlen;
E 21
I 21
			p[idx].line = -1;
			p[idx].mline = -1;
E 21
			p[idx].latency = -1.;
			p[idx].ratio = -1.;
I 20
			p[idx].slope = -1.;
E 20
E 17
		}
	}
D 17
	return idx;
E 17
I 17

D 21
	collect_sample(line, warmup, repetitions, &p[0]);
	while (collect_sample(line, warmup, repetitions, &p[samples-1]) == 0) {
E 21
I 21
	/* make sure we have enough memory for the scratch data */
	while (state.addr == NULL) {
		mem_initialize(&state);
		if (state.addr == NULL) {
			maxlen /= 2;
			state.len = state.maxlen = maxlen;
			while (p[samples-1].len > maxlen)
				samples--;
		}
	}
	for (i = 0; i < samples; ++i)
		p[i].maxlen = maxlen;
I 25
	/* in case the system has laid out the pages well, don't scramble */
	for (i = 0; i < state.npages; ++i)
		state.pages[i] = i * state.pagesize;
E 25

D 27
	collect_sample(repetitions, &state, &p[0]);
	while (collect_sample(repetitions, &state, &p[samples-1]) == 0) {
E 27
I 27
	p[0].latency = measure(p[0].len, repetitions, &p[0].variation, &state);
	p[samples-1].latency = measure(p[samples-1].len, repetitions, 
				       &p[samples-1].variation, &state);
	while (p[samples-1].latency <= 0.0) {
		p[samples-1].latency = measure(p[samples-1].len, 
					       repetitions, 
					       &p[samples-1].variation, 
					       &state);
E 27
E 21
		--samples;
	}
D 21
	search(0, samples - 1, line, warmup, repetitions, p);
E 21
I 21
	search(0, samples - 1, repetitions, &state, p);
E 21

D 21
	/**/
D 20
	fprintf(stderr, "%10.10s %10.10s %10.10s %10.10s\n", "mem size", "latency", "variation", "ratio");
E 20
I 20
	fprintf(stderr, "%10.10s %10.10s %10.10s %10.10s %10.10s\n", "mem size", "latency", "variation", "ratio", "slope");
E 21
I 21
D 23
	/*
E 23
I 23
D 30
	/**/
E 30
I 30
	/*
E 30
E 23
	fprintf(stderr, "%10.10s %8.8s %8.8s %8.8s %8.8s %5.5s %5.5s\n", 
		"mem size", "latency", "variation", "ratio", "slope", 
		"line", "mline");
E 21
E 20
	for (idx = 0; idx < samples; ++idx) {
		if (p[idx].latency < 0.) continue;
		fprintf(stderr, 
D 20
			"%10.6f %10.5f %10.5f %10.5f\n", 
E 20
I 20
D 21
			"%10.6f %10.5f %10.5f %10.5f %10.5f\n", 
E 21
I 21
			"%10.6f %8.3f %8.3f %8.3f %8.3f %4d %4d\n", 
E 21
E 20
			p[idx].len / (1000. * 1000.), 
			p[idx].latency, 
			p[idx].variation, 
D 20
			p[idx].ratio);
E 20
I 20
			p[idx].ratio,
D 21
			p[idx].slope);
E 21
I 21
			p[idx].slope,
			p[idx].line,
			p[idx].mline);
E 21
E 20
	}
	/**/
I 21
	mem_cleanup(&state);
E 21

	return samples;
E 17
}

D 21
int
E 14
D 17
find_cache(int start, int line, 
	   int maxlen, int warmup, int repetitions, double *time)
E 17
I 17
search(int left, int right, 
       int line, int warmup, int repetitions, struct cache_results* p)
E 21
I 21
void
search(int left, int right, int repetitions, 
       struct mem_state* state, struct cache_results* p)
E 21
E 17
{
D 10
	int	i, len, incr;
	double	baseline, current;
E 10
I 10
D 17
	int	i, len, maxsize, incr;
	double	baseline = -1.;
	double	current;
I 11
	double	max_variation, variation;
E 11
E 10

	/* get the baseline access time */
D 10
	baseline = measure(2 * start, line, warmup, repetitions);
E 10
I 10
	i = 2 * start;
E 17
I 17
	int	middle = left + (right - left) / 2;
E 17
E 10

D 10
	for (i = 4 * start; i <= maxlen; i<<=1) {
		current = measure(i, line, warmup, repetitions);
E 10
I 10
D 17
search:
	for (; i <= maxlen; i<<=1) {
		current = measure(i, line, (2*i) < maxlen ? (2*i) : maxlen, 
D 11
				  warmup, repetitions);
E 11
I 11
				  warmup, repetitions, &max_variation);
E 17
I 17
D 20
	if (p[left].latency != 0.0) {
E 20
I 20
	if (p[left].latency > 0.0) {
E 20
		p[left].ratio = p[right].latency / p[left].latency;
I 20
		p[left].slope = (p[left].ratio - 1.) / (double)(right - left);
E 20
D 21
		/* we probably have a bad data point, so re-test it */
E 21
I 21
		/* we probably have a bad data point, so ignore it */
E 21
D 19
fprintf(stderr, "search(%d, %d, ...): ratio[%d]=%f\n", p[left].len, p[right].len, p[left].len, p[left].ratio);
E 19
		if (p[left].ratio < 0.98) {
I 20
D 21
			/**/
E 20
			fprintf(stderr, "search: retesting %d\n", p[left].len);
I 20
			/**/
E 20
			p[left].ratio = -1.;
I 20
			p[left].latency = -1.;
E 20
			collect_sample(line, warmup, repetitions, &p[left]);
D 20
			if (p[left].latency != 0.0)
E 20
I 20
			if (p[left].latency > 0.0) {
E 20
				p[left].ratio = p[right].latency / p[left].latency;
I 20
				p[left].slope = (p[left].ratio - 1.) / (double)(right - left);
			}
E 21
I 21
			p[left].latency = p[right].latency;
			p[left].ratio = 1.;
D 24
			p[left].slope = 0.;
E 24
I 24
D 28
			p[left].slope = -1.;
E 28
I 28
			p[left].slope = 0.;
E 28
E 24
E 21
E 20
		}
	}
E 17
E 11

D 17
		if (baseline < 0.)
			baseline = current;
E 17
I 17
	if (middle == left || middle == right)
D 21
		return 0;
E 21
I 21
		return;

D 27
	/*
E 27
I 27
D 30
	/**/
E 27
	fprintf(stderr, "search(%d, %d, ...): middle=%d\n", p[left].len, p[right].len, p[middle].len);
	/**/
E 21
E 17
E 10

E 30
D 17
		/* we have crossed a cache boundary */
D 10
		if (current / baseline > THRESHOLD)
E 10
I 10
		if (current / baseline > THRESHOLD) {
E 10
			break;
I 10
		}
I 11
		len = i;
E 17
I 17
D 20
	if (p[left].ratio > 1.1 || p[left].ratio < 0.97) {
E 20
I 20
D 29
	if (p[left].ratio > 1.05 || p[left].ratio < 0.97) {
E 29
I 29
	if (p[left].ratio > 1.35 || p[left].ratio < 0.97) {
E 29
E 20
D 21
		collect_sample(line, warmup, repetitions, &p[middle]);
		search(middle, right, line, warmup, repetitions, p);
		search(left, middle, line, warmup, repetitions, p);
E 21
I 21
		collect_sample(repetitions, state, &p[middle]);
		search(middle, right, repetitions, state, p);
		search(left, middle, repetitions, state, p);
E 21
E 17
E 11
E 10
	}
I 21
	return;
E 21
D 10
	
E 10
D 17
	if (i >= maxlen)
		return i;
E 17
I 17
}
E 17

D 17
	incr = i>>3;
D 10
	maxlen = i;
E 10
I 10
	maxsize = i;
E 10
D 11
	i>>=1;
	len = i;
E 11
I 11
	i = (i>>1) + incr;
E 17
I 17
int
D 21
collect_sample(int line, int warmup, int repetitions, struct cache_results* p)
E 21
I 21
collect_sample(int repetitions, struct mem_state* state, 
	       struct cache_results* p)
E 21
{
D 21
	int	len, maxlen;
	struct mem_state state;
E 21
I 21
D 26
	int	i, j, k, chunk, page, npages, ntotalpages, nsparepages;
D 22
	int	modified, swapped;
E 22
I 22
	int	modified, swapped, iters;
E 26
I 26
D 27
	int	i, chunk, page, npages, ntotalpages, nsparepages;
	int	modified, changed, iters;
E 26
E 22
	int	*pages, *pageset;
	static int	available_index = 0;
D 23
	double	baseline, t, tt, var, nodiff_chunk_baseline;
E 23
I 23
	double	baseline, t, tt, low, var, new_baseline, nodiff_chunk_baseline;
E 23

	p->latency = measure(p->len, repetitions, &p->variation, state);
	baseline = p->latency;
E 27
I 27
	int	i, modified, npages;
	int	*pages;
	double	baseline;
E 27

D 29
	npages = p->len / getpagesize();
E 29
I 29
	npages = (p->len + getpagesize() - 1) / getpagesize();
E 29
D 26
	ntotalpages = state->maxlen / getpagesize();
	nsparepages = ntotalpages - npages;
E 26
D 27
	pages = state->pages;
	pageset = state->pages + npages;
E 27
I 27
        baseline = measure(p->len, repetitions, &p->variation, state);
E 27
D 26
	chunk = (npages + 9) / 10;
	if (chunk > 10)
		chunk = 10;
E 26
	
D 27
	if (npages < 2 || nsparepages <= npages)
		return (p->latency > 0);
E 21
E 17
E 11

D 10
	/*
E 10
I 10
D 11
	/**/
E 11
I 11
D 17
	/*
E 11
E 10
	fprintf(stderr, "find_cache: baseline=%.2f, current=%.2f, ratio=%.2f, i=%d\n", baseline, current, current/baseline, i);
	/**/
E 17
I 17
D 21
	len = p->len;
	maxlen = p->maxlen;
E 21
I 21
	nodiff_chunk_baseline = baseline;
I 24
D 26
	if (available_index >= nsparepages) available_index = 0;
E 26
E 24
I 22
	iters = 0;
E 22
	do {
		modified = 0;
I 26
		chunk = (npages + 9) / 10;
		if (chunk > 10)	chunk = 10;

E 26
		for (i = 0; i < npages; i+=chunk) {
			if (i + chunk > npages) chunk = npages - i;
E 21
E 17

D 10
	for (i; i <= maxlen; i+=incr) {
		current = measure(i, line, warmup, repetitions);
E 10
I 10
D 17
	for (i; i <= maxsize; i+=incr) {
		current = measure(i, line, (2*i) < maxlen ? (2*i) : maxlen, 
D 11
				  warmup, repetitions);
E 11
I 11
				  warmup, repetitions, &variation);
E 17
I 17
D 21
	state.width = 1;
	state.pagesize = getpagesize();
	state.line = line;
	state.len = len;
	state.maxlen = len;
E 21
I 21
			t = remove_chunk(i, chunk, npages, pages, 
					 p->len, repetitions, state);
E 21
E 17
E 11
E 10

I 26
			/**/
			fprintf(stderr, "collect_sample(...): baseline=%G, t=%G, len=%d, chunk=%d, i=%d\n", baseline, t, p->len, chunk, i);
			/**/

E 26
D 17
		/* we have crossed a cache boundary */
		if (current / baseline > THRESHOLD)
			break;
E 17
I 17
D 21
	p->latency = measure(len, line, maxlen, warmup,
			     repetitions, &p->variation);
E 21
I 21
			if (t >= 0.99 * baseline) continue;
			if (t >= 0.999 * nodiff_chunk_baseline) continue;
E 21
E 17
D 11
		len = i;
E 11
I 11

D 17
		if (variation > max_variation) {
			len = i;
			max_variation = variation;
		}
E 11
	}
I 10
	if (len >= maxsize) {
		i = len;
		goto search;
	}
E 10
	
	*time = baseline;
	return len;
E 17
I 17
D 21
	if (p->latency > 0) return 1;
	return 0;
E 21
I 21
D 26
			/*
E 26
I 26
			/**/
E 26
			fprintf(stderr, "collect_sample(...): faster chunk: baseline=%G, t=%G, len=%d, chunk=%d, i=%d\n", baseline, t, p->len, chunk, i);
			/**/
E 27
I 27
D 30
	/**/
D 29
	fprintf(stderr, "collect_sample(...): entering: baseline=%G, len=%d\n", baseline, p->len);
E 29
I 29
	fprintf(stderr, "collect_sample(...): entering: baseline=%G, len=%d, pagesize=%d\n", baseline, p->len, getpagesize());
E 29
	/**/
E 27

E 30
D 26
			swapped = 0;
			for (j = 0; j < chunk; ++j) {
				page = pages[i + j];
				tt = remove_chunk(i + j, 1, npages, pages, 
						  p->len, repetitions, state);
				/*
				fprintf(stderr, 
					"\ti = %d\tpage = %d\tbase = %G\ttt = %G\n", 
					i + j, page, baseline, tt);
				/**/
				if (tt >= 0.995 * baseline) continue;
				
				tt = remove_chunk(i + j, 1, npages, pages, 
						  p->len, repetitions, state);

				if (tt >= 0.995 * baseline) continue;

I 23
				low = tt;
				new_baseline = baseline;

E 23
				/* page is no good, find a substitute! */
				for (k = available_index; k < nsparepages && k - available_index < 2 * npages; ++k) {
					pages[i + j] = pageset[nsparepages - k - 1];
					tt = measure(p->len, repetitions, 
						     &var, state);
					/*
					fprintf(stderr, 
						"\t\tk = %d\tpage = %d\ttt = %G\tbase = %G\n", 
D 23
						k, pageset[k], tt, baseline);
E 23
I 23
						k, pageset[k], tt, new_baseline);
E 23
					/**/
D 23
					if (tt < 0.995 * baseline) {
						/* pageset[k] is OK */
E 23
I 23

					/* this is the minimum so far */
					if (tt < new_baseline) {
E 23
						p->latency = tt;
D 23
						baseline = tt;
						nodiff_chunk_baseline = tt;
E 23
I 23
						new_baseline = tt;
E 23
						p->variation = var;
						pageset[nsparepages - k - 1] = page;
I 23
						page = pages[i + j];
E 23
						++swapped;
						++modified;
D 23
						break;
E 23
					}
I 23

					/* pageset[k] is OK */
					if (tt < 0.995 * baseline
					    && low >= 0.995 * tt)
						break;
E 23
				}
I 23
				baseline = new_baseline;
				nodiff_chunk_baseline = new_baseline;
E 23
				available_index = (k < nsparepages) ? k : 0;
				if (k == nsparepages) 
					pages[i + j] = page;
			}
			if (swapped == 0 && t < nodiff_chunk_baseline)
E 26
I 26
D 27
			changed = fixup_chunk(i, chunk, npages, 
					      pages, p->len, 
					      &baseline,
					      &nodiff_chunk_baseline,
					      t,
					      repetitions, 
					      state);

			if (changed) {
				modified = 1;
			} else {
E 26
				nodiff_chunk_baseline = t;
I 26
			}
E 27
I 27
D 29
	if (npages >= 2) {
E 29
I 29
	if (npages > 1) {
E 29
		for (i = 0, modified = 1; i < 8 && modified; ++i) {
			modified = test_chunk(0, npages, npages, 
					      state->pages, p->len, 
D 32
					      &baseline, baseline, 
E 32
I 32
					      &baseline, 0.0,
E 32
					      repetitions, state);
I 28
D 30
			/**/
			fprintf(stderr, "collect_sample(...): iter=%d: baseline=%G, len=%d\n", i, baseline, p->len);
			/**/
E 30
E 28
E 27
E 26
		}
D 22
	} while (modified);
E 22
I 22
D 27
		++iters;
D 24
	} while (modified && iters < 4);
E 24
I 24
	} while (modified && iters < 8);
E 24
E 22

E 27
I 27
	}
I 29
D 32
	baseline = measure(p->len, repetitions, &p->variation, state);
E 32
E 29
E 27
I 26
	p->latency = baseline;
I 27

E 27
D 30
	/**/
D 27
	fprintf(stderr, "collect_sample(...): end of loop: baseline=%G, len=%d, chunk=%d, iters=%d, modified=%d\n", baseline, p->len, chunk, iters, modified);
E 27
I 27
	fprintf(stderr, "collect_sample(...): exiting: baseline=%G, len=%d, iters=%d, modified=%d\n", baseline, p->len, i, modified);
E 27
	/**/

E 30
E 26
	return (p->latency > 0);
E 21
E 17
}

double
D 10
measure(int size, int line, int warmup, int repetitions)
E 10
I 10
D 11
measure(int size, int line, int maxlen, int warmup, int repetitions)
E 11
I 11
D 21
measure(int size, int line, int maxlen, int warmup, 
	int repetitions, double* variation)
E 21
I 21
measure(int size, int repetitions, 
	double* variation, struct mem_state* state)
E 21
E 11
E 10
{
D 21
	int	i;
E 21
I 21
	int	i, j, npages, nlines;
	int	*pages;
E 21
D 11
	double	time;
E 11
I 11
	double	time, median;
E 11
	result_t *r, *r_save;
D 13
	struct _state state;
E 13
I 13
D 21
	struct mem_state state;
E 21
I 21
	char	*p;
E 21
E 13

I 13
D 21
	state.width = 1;
E 13
	state.len = size;
I 15
	state.maxlen = size;
E 15
I 10
D 13
	state.maxlen = maxlen;
E 13
E 10
	state.line = line;
	state.pagesize = getpagesize();
E 21
I 21
	pages = state->pages;
	npages = (size + getpagesize() - 1) / getpagesize();
	nlines = state->nlines;

	if (size % getpagesize())
		nlines = (size % getpagesize()) / state->line;
E 21

	r_save = get_results();
D 10
	r = (result_t*)malloc(sizeof_result(repetitions));
E 10
I 10
D 15
	r = (result_t*)malloc(sizeof_result(repetitions + 1));
E 15
I 15
	r = (result_t*)malloc(sizeof_result(repetitions));
E 15
E 10
	insertinit(r);

I 21
	/* 
	 * assumes that you have used mem_initialize() to setup the memory
	 */
	p = state->base;
	for (i = 0; i < npages - 1; ++i) {
		for (j = 0; j < state->nwords; ++j) {
			*(char**)(p + pages[i] + state->lines[state->nlines - 1] + state->words[j]) = 
			p + pages[i+1] + state->lines[0] + state->words[j];
		}
	}
	for (j = 0; j < state->nwords; ++j) {
		*(char**)(p + pages[npages - 1] + state->lines[nlines - 1] + state->words[j]) = 
			p + pages[0] + state->lines[0] + state->words[(j+1)%state->nwords];
	}

I 29
	/*
	check_memory(size, state);
	/**/

E 29
	addr_save = NULL;
	state->p[0] = p + pages[0] + state->lines[0] + state->words[0];
	/* now, run through the chain once to clear the cache */
	mem_benchmark((size / sizeof(char*) + 100) / 100, state);

E 21
D 10
	for (i = 0; i < repetitions; ++i) {
E 10
I 10
D 13
	/* 
	 * Get the system to allocate more pages than we need, and
	 * we will choose a random subset.  This is to try and improve
	 * accuracy on systems without page coloring.  We do a sort
	 * of randomized page coloring...
	 */
	for (i = 0; i < repetitions - 1; ++i) {
E 10
		benchmp(initialize, benchmark, cleanup, 0, 1, 
				warmup, TRIES, &state);
		save_minimum();
		insertsort(gettime(), get_n(), r);
	}
I 10

	state.maxlen = size;
	benchmp(initialize, benchmark, cleanup, 0, 1, warmup, 5, &state);
E 13
I 13
D 15
	benchmp(mem_initialize, mem_benchmark_0, mem_cleanup, 
		0, 1, warmup, repetitions, &state);
E 13
E 10
	save_minimum();
I 10
	insertsort(gettime(), get_n(), r);
E 15
I 15
	for (i = 0; i < repetitions; ++i) {
D 21
		benchmp(mem_initialize, mem_benchmark_0, mem_cleanup, 
D 20
			0, 1, warmup, TRIES, &state);
E 20
I 20
			0, 1, warmup, 7, &state);
E 20
		save_minimum();
E 21
I 21
		BENCH1(mem_benchmark(__n, state); __n = 1;, 0)
E 21
		insertsort(gettime(), get_n(), r);
D 21
		state.maxlen = maxlen;
E 21
	}
E 15
D 21

E 21
E 10
	set_results(r);
I 10
D 11
	save_minimum();
E 11
E 10
D 21

E 21
D 11
	/* We want nanoseconds / load. */
E 11
I 11
	median = (1000. * (double)gettime()) / (100. * (double)get_n());

	save_minimum();
E 11
	time = (1000. * (double)gettime()) / (100. * (double)get_n());

D 10
	/*
E 10
I 10
D 11
	/**/
E 10
	fprintf(stderr, "%.6f %.2f\n", state.len / (1000. * 1000.), time);
I 10
	print_results();
E 10
	/**/
E 11
I 11
	/* Are the results stable, or do they vary? */
D 17
	*variation = median / time;
E 17
I 17
	if (time != 0.)
		*variation = median / time;
	else
		*variation = -1.0;
E 17
E 11
D 21

E 21
	set_results(r_save);
	free(r);
I 11

I 21
	if (nlines < state->nlines) {
		for (j = 0; j < state->nwords; ++j) {
			*(char**)(p + pages[npages - 1] + state->lines[nlines - 1] + state->words[j]) = 
				p + pages[npages - 1] + state->lines[nlines] + state->words[j];
		}
	}
E 21
D 14
	/**/
E 14
I 14
	/*
E 14
D 21
	fprintf(stderr, "%.6f %.2f %.2f\n", state.len / (1000. * 1000.), time, *variation);
E 21
I 21
	fprintf(stderr, "%.6f %.2f\n", state->len / (1000. * 1000.), median);
E 21
	/**/
E 11

D 21
	return time;
E 21
I 21
	return median;
}


double
remove_chunk(int i, int chunk, int npages, int* pages, 
	       int len, int repetitions, struct mem_state* state)
{
	int	n, j;
	double	t, var;

	if (i + chunk < npages) {
		for (j = 0; j < chunk; ++j) {
			n = pages[i+j];
			pages[i+j] = pages[npages-1-j];
			pages[npages-1-j] = n;
		}
	}
	t = measure(len - chunk * getpagesize(), repetitions, &var, state);
	if (i + chunk < npages) {
		for (j = 0; j < chunk; ++j) {
			n = pages[i+j];
			pages[i+j] = pages[npages-1-j];
			pages[npages-1-j] = n;
		}
	}
	
	return t;
I 26
}

int
I 27
test_chunk(int i, int chunk, int npages, int* pages, int len, 
	   double *baseline, double chunk_baseline,
	   int repetitions, struct mem_state* state)
{
	int	j, k, subchunk;
D 28
	int	changed = 0;
E 28
	int	modified = 0;
I 28
D 29
	int	changed[20];
E 29
I 29
	int	changed;
E 29
E 28
	double	t, tt, nodiff_chunk_baseline;

D 32
	if (chunk <= 20) {
E 32
I 32
	if (chunk <= 20 && chunk < npages) {
E 32
		return fixup_chunk(i, chunk, npages, pages, len, baseline, 
				   chunk_baseline, repetitions, state);
	}

	nodiff_chunk_baseline = *baseline;
	subchunk = (chunk + 19) / 20;
D 28
	for (j = i; j < i + chunk; j+=subchunk) {
E 28
I 28
D 29
	bzero(&changed[0], 20 * sizeof(int));
E 29
	for (j = i, k = 0; j < i + chunk; j+=subchunk, k++) {
D 29
		if (changed[k]) continue;

E 29
E 28
		if (j + subchunk > i + chunk) subchunk = i + chunk - j;
D 28
		changed = 0;
E 28

		t = remove_chunk(j, subchunk, npages, pages, 
				 len, repetitions, state);

D 30
		/**/
E 30
I 30
		/*
E 30
		fprintf(stderr, "test_chunk(...): baseline=%G, t=%G, len=%d, chunk=%d, i=%d\n", *baseline, t, len, subchunk, j);
		/**/

		if (t >= 0.99 * *baseline) continue;
		if (t >= 0.999 * nodiff_chunk_baseline) continue;

		tt = remove_chunk(j, subchunk, npages, pages, 
				  len, repetitions, state);

		if (tt > t) t = tt;

		if (t >= 0.99 * *baseline) continue;
		if (t >= 0.999 * nodiff_chunk_baseline) continue;

D 30
		/**/
		fprintf(stderr, "test_chunk(...): faster chunk: baseline=%G, t=%G, len=%d, chunk=%d, i=%d\n", *baseline, t, len, subchunk, j);
		/**/

E 30
D 28
		changed = test_chunk(j, subchunk, npages, pages, len,
E 28
I 28
D 29
		changed[k] = test_chunk(j, subchunk, npages, pages, len,
E 29
I 29
		changed = test_chunk(j, subchunk, npages, pages, len,
E 29
E 28
				     baseline, t, repetitions, state);

D 28
		if (changed) {
E 28
I 28
D 29
		if (changed[k]) {
E 29
I 29
		if (changed) {
E 29
E 28
			modified = 1;
		} else {
			nodiff_chunk_baseline = t;
		}
	}
	return modified;
}

/*
 * This routine is called once we have identified a chunk
 * that has pages that are suspected of colliding with other
 * pages.
 *
 * The algorithm is to remove all the pages, and then 
 * slowly add back pages; attempting to add pages with
 * minimal cost.
 */
int
E 27
fixup_chunk(int i, int chunk, int npages, int* pages, int len, 
D 27
	    double *baseline, double *nodiff_chunk_baseline,
	    double chunk_baseline,
E 27
I 27
	    double *baseline, double chunk_baseline,
E 27
	    int repetitions, struct mem_state* state)
{
D 27
	int	j, k, page, substitute, ntotalpages, nsparepages;
E 27
I 27
D 28
	int	j, k;
E 28
I 28
	int	j, k, l, m;
E 28
	int	page, substitute, original;
	int	ntotalpages, nsparepages;
	int	subset_len;
E 27
	int	swapped = 0;
	int	*pageset;
I 27
	int	*saved_pages;
E 27
	static int	available_index = 0;
	double	t, tt, low, var, new_baseline;
I 28
	double	latencies[20];
E 28

I 27
D 30
	/**/
	fprintf(stderr, "fixup_chunk(%d, %d, %d, xxx, %d, %G, %G, ...): entering\n", i, chunk, npages, len, *baseline, chunk_baseline);
	/**/

E 30
E 27
	ntotalpages = state->maxlen / getpagesize();
	nsparepages = ntotalpages - npages;
	pageset = state->pages + npages;
I 27
	new_baseline = *baseline;

	saved_pages = (int*)malloc(sizeof(int) * ntotalpages);
	bcopy(pages, saved_pages, sizeof(int) * ntotalpages);

	/* move everything to the end of the page list */
	if (i + chunk < npages) {
		for (j = 0; j < chunk; ++j) {
			page = pages[i+j];
			pages[i+j] = pages[npages-chunk+j];
			pages[npages-chunk+j] = page;
		}
	}
E 27

	if (available_index >= nsparepages) available_index = 0;

D 28
	for (j = 0; j < chunk; ++j) {
E 28
I 28
	/* 
	 * first try to identify which pages we can definitely keep
	 */
	for (j = 0, k = chunk; j < k; ) {

		t = measure((npages - chunk + j + 1) * getpagesize(), 
			    repetitions, &var, state);

D 29
		if (0.995 * t <= chunk_baseline) {	
E 29
I 29
		if (0.995 * t <= chunk_baseline) {
I 32
			latencies[j] = t;
E 32
E 29
			++j;	/* keep this page */
I 29
D 32
			if (chunk >= npages && t < chunk_baseline)
				chunk_baseline = t;
E 29
			new_baseline = t;
E 32
		} else {	
			--k;	/* this page is probably no good */
D 32
			++swapped;
E 32
			latencies[k] = t;
			SWAP(pages[npages - chunk + j], pages[npages - chunk + k]);
		}
	}
	/*
	 * sort the "bad" pages by increasing latency
	 */
D 29
	fprintf(stderr, "\tbefore sort\n");
E 29
I 29
D 30
	fprintf(stderr, "\tbefore sort: keeping %d of %d pages\n", j, chunk);
E 29
	for (l = j; l < chunk; ++l) {
		fprintf(stderr, "\t\tlatencies[%d] = %G\tpages[%d] = %d\n", l, latencies[l], i + l, pages[npages - chunk + l]);
	}

E 30
D 32
	for (; k < chunk; ++k) {
		for (l = k + 1; l < chunk; ++l) {
			if (latencies[k] > latencies[l]) {
				tt = latencies[k]; 
				latencies[k] = latencies[l];
				latencies[l] = tt;
				SWAP(pages[npages - chunk + k], pages[npages - chunk + l]);
			}
		}
E 32
I 32
	pagesort(chunk - j, &pages[npages - chunk + j], &latencies[j]);

	/*
	fprintf(stderr, "fixup_chunk: len=%d, chunk=%d, j=%d, baseline=%G, lat[%d]=%G..%G\n", len, chunk, j, *baseline, j, (j < chunk ? latencies[j] : -1.0), latencies[chunk - 1]);
	/**/

	if (chunk >= npages && j < chunk / 2) {
		j = chunk / 2;
		t = measure((npages - chunk + j + 1) * getpagesize(), 
			    repetitions, &var, state);
		chunk_baseline = t;
E 32
	}
D 30
	fprintf(stderr, "\tafter sort\n");
	for (l = j; l < chunk; ++l) {
		fprintf(stderr, "\t\tlatencies[%d] = %G\tpages[%d] = %d\n", l, latencies[l], i + l, pages[npages - chunk + l]);
	}

E 30

D 30
	for (k = 0; j < chunk && k < 2 * npages; ++k) {
E 30
I 30
D 31
	for (k = 0; j < chunk && k < npages; ++k) {
E 31
I 31
	for (k = 0; j < chunk && k < 2 * npages; ++k) {
E 31
E 30
E 28
D 27
		page = pages[i + j];
		tt = remove_chunk(i + j, 1, npages, pages, 
				  len, repetitions, state);
E 27
I 27
		original = npages - chunk + j;
I 28
		substitute = nsparepages - 1;
		substitute -= (k + available_index) % (nsparepages - 1);
E 28
		subset_len = (original + 1) * getpagesize();
D 28
		page = pages[original];
E 28
D 32

E 32
I 32
		if (j == chunk - 1 && len % getpagesize()) {
			subset_len = len;
		}
		
E 32
D 28
		tt = measure(subset_len, repetitions, &var, state);
E 28
I 28
		SWAP(pages[original], pageset[substitute]);
		t = measure(subset_len, repetitions, &var, state);
		SWAP(pages[original], pageset[substitute]);
E 28

E 27
D 30
		/**/
D 28
		fprintf(stderr, 
			"\ti = %d\tpage = %d\tbase = %G\ttt = %G\n", 
			i + j, page, *baseline, tt);
E 28
I 28
		fprintf(stderr, "\tk = %d\tj = %d\tpage = %d\ttt = %G\tbase = %G\n", 
			k, j, pageset[substitute], t, new_baseline);
E 28
		/**/
D 27
		if (tt >= 0.995 * *baseline) continue;
E 27
D 28
				
D 27
		tt = remove_chunk(i + j, 1, npages, pages, 
				  len, repetitions, state);

		if (tt >= 0.995 * *baseline) continue;

E 27
		low = tt;
D 27
		new_baseline = *baseline;
E 27
I 27
		new_baseline = tt;

		if (0.995 * tt <= chunk_baseline) continue;
E 27

		/* page is no good, find a substitute! */
		for (k = 0; k < 2 * npages; ++k) {
			substitute = nsparepages - 1;
D 27
			substitute -= (k + available_index) % nsparepages;
			pages[i + j] = pageset[substitute];
E 27
I 27
			substitute -= (k + available_index) % (nsparepages - 1);
			pages[original] = pageset[substitute];
E 27

D 27
			tt = measure(len, repetitions, &var, state);
E 27
I 27
			tt = measure(subset_len, repetitions, &var, state);
E 27
			/**/
			fprintf(stderr, 
				"\t\tk = %d\tpage = %d\ttt = %G\tbase = %G\n", 
				k, pageset[substitute], tt, new_baseline);
			/**/
E 28

E 30
D 28
			/* this is the minimum so far */
			if (tt < new_baseline) {
				new_baseline = tt;
				/* p->variation = var; */
				pageset[substitute] = page;
D 27
				page = pages[i + j];
E 27
I 27
				page = pages[original];
E 28
I 28
		/*
		 * try to keep pages ordered by increasing latency
		 */
D 32
		for (l = j; l < chunk; ++l) {
D 29
			if (latencies[l] > t) {
E 29
I 29
			if (t < latencies[l]) {
E 29
E 28
E 27
				++swapped;
I 28
				SWAP(pages[npages - 1], pageset[substitute]);
				latencies[chunk - 1] = t;
				for (m = chunk - 1; m > l; --m) {
					SWAP(pages[npages - chunk + m], 
					     pages[npages - chunk + m - 1]);
					tt = latencies[m]; 
					latencies[m] = latencies[m-1];
					latencies[m-1] = tt;
				}
D 30
				fprintf(stderr, "\tafter insert of %G\n", t);
				for (l = j; l < chunk; ++l) {
					fprintf(stderr, "\t\tlatencies[%d] = %G\tpages[%d] = %d\n", l, latencies[l], i + l, pages[npages - chunk + l]);
				}
				/**/
				fprintf(stderr, "\t\tj=%d, worst=%G\n", j, latencies[chunk - 1]);
				/**/
E 30
D 29
				if (0.995 * t <= chunk_baseline) {	
					++j;	/* keep this page */
					new_baseline = t;
					/* XXX: should retest each page and 
					 *      then sort pages again
					 */
				}
E 29
				break;
E 28
			}
E 32
I 32
		if (t < latencies[chunk - 1]) {
			latencies[chunk - 1] = t;
			SWAP(pages[npages - 1], pageset[substitute]);
			pagesort(chunk - j, 
				 &pages[npages - chunk + j], &latencies[j]);
E 32
D 28

			/* pageset[k] is OK */
D 27
			if (tt < 0.995 * *baseline
			    && low >= 0.995 * tt)
				break;
E 27
I 27
			if (0.995 * tt <= chunk_baseline) break;
E 28
		}
I 29
		if (0.995 * latencies[j] <= chunk_baseline) {
			++j;	/* keep this page */
D 32
			new_baseline = t;
			/* XXX: should retest each page and 
			 *      then sort pages again
			 */
E 32
I 32
			++swapped;
E 32
		}
E 29
D 28
		/**/
		if ((k + available_index) % (nsparepages - 1) < available_index) {
			fprintf(stderr, "\t\trolled available_index, nsparepages=%d, npages=%d\n", nsparepages, npages);
E 27
		}
I 27
		/**/
E 28
I 28
	}
				
D 30
	if ((k + available_index) % (nsparepages - 1) < available_index) {
		fprintf(stderr, "\t\trolled available_index, nsparepages=%d, npages=%d\n", nsparepages, npages);
	}
	/**/
E 28

E 30
D 28
		available_index = (k + available_index) % (nsparepages - 1);
		pages[original] = page;
E 28
I 28
	available_index = (k + available_index) % (nsparepages - 1);

	/* measure new baseline, in case we didn't manage to optimally
	 * replace every page
	 */
D 32
	if (j < chunk) {
		new_baseline = measure(npages * getpagesize(), 
				       repetitions, &var, state);
E 28
	}
E 32
I 32
	if (swapped) {
		new_baseline = measure(len, repetitions, &var, state);
E 32

D 32
	if (new_baseline >= 0.999 * *baseline) {
		/* there was no benefit to these changes, so back them out */
		swapped = 0;
		bcopy(saved_pages, pages, sizeof(int) * ntotalpages);
	} else {
		/* we sped up, so keep these changes */
E 27
		*baseline = new_baseline;
E 32
I 32
		/*
		fprintf(stderr, "fixup_chunk: len=%d, swapped=%d, k=%d, baseline=%G, newbase=%G\n", len, swapped, k, *baseline, new_baseline);
		/**/

		if (new_baseline >= 0.999 * *baseline) {
			/* no benefit to these changes; back them out */
			swapped = 0;
			bcopy(saved_pages, pages, sizeof(int) * ntotalpages);
		} else {
			/* we sped up, so keep these changes */
			*baseline = new_baseline;
E 32
D 27
		*nodiff_chunk_baseline = new_baseline;
		available_index = substitute;
		pages[i + j] = page;
E 27
I 27

D 32
		/* move back to the middle of the pagelist */
		if (i + chunk < npages) {
			for (j = 0; j < chunk; ++j) {
				page = pages[i+j];
				pages[i+j] = pages[npages-chunk+j];
				pages[npages-chunk+j] = page;
E 32
I 32
			/* move back to the middle of the pagelist */
			if (i + chunk < npages) {
				for (j = 0; j < chunk; ++j) {
					page = pages[i+j];
					pages[i+j] = pages[npages-chunk+j];
					pages[npages-chunk+j] = page;
				}
E 32
			}
		}
I 32
	/*
	} else {
		fprintf(stderr, "fixup_chunk: len=%d, swapped=%d, k=%d\n", len, swapped, k);
	/**/
E 32
E 27
	}
I 27
	free(saved_pages);

E 27
	return swapped;
E 26
E 21
}
E 9
D 13

/*
 * This will access len bytes
 */
void
initialize(void* cookie)
{
D 4
	int i, j, k, nlines, nbytes, npages, npointers;
E 4
I 4
	int i, j, k, nwords, nlines, nbytes, npages, npointers;
E 4
	unsigned int r;
	char ***pages;
	int    *lines;
I 4
	int    *words;
E 4
	struct _state* state = (struct _state*)cookie;
	register char *p = 0 /* lint */;

	nbytes = state->len;
D 7
	npointers = state->len / sizeof(char*);
E 7
I 7
	npointers = state->len / state->line;
E 7
I 4
	nwords = state->line / sizeof(char*);
E 4
D 3
	nlines = state->pagesize / sizeof(char*);
E 3
I 3
	nlines = state->pagesize / state->line;
E 3
D 10
	npages = (nbytes + state->pagesize) / state->pagesize;
E 10
I 10
	npages = (state->maxlen + state->pagesize) / state->pagesize;
E 10

I 4
D 12
	words = (int*)malloc(nwords * sizeof(int));
E 4
	lines = (int*)malloc(nlines * sizeof(int));
E 12
I 12
	srand(getpid());

	words = permutation(nwords);
	lines = permutation(nlines);
E 12
	pages = (char***)malloc(npages * sizeof(char**));
D 10
	state->p = state->addr = (char*)malloc(nbytes + 2 * state->pagesize);
E 10
I 10
	state->p = state->addr = (char*)malloc(state->maxlen + 2 * state->pagesize);
E 10

	if ((unsigned long)state->p % state->pagesize) {
		state->p += state->pagesize - (unsigned long)state->p % state->pagesize;
	}

D 12
	if (state->addr == NULL || pages == NULL) {
E 12
I 12
	if (state->addr == NULL || pages == NULL || words == NULL || lines == NULL) {
E 12
		exit(0);
	}
D 10

	srand(getpid());
E 10
I 10
	
D 12
	srand((int)now() ^ getpid() ^ (getpid()<<16));
E 10

E 12
	/* first, layout the sequence of page accesses */
	p = state->p;
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
D 9
		lines[i] = i * state->pagesize / (nlines * sizeof(char*));
E 9
I 9
D 12
		lines[i] = i * nwords;
E 9
	}

	/* randomize the line sequences */
	for (i = nlines - 2; i > 0; --i) {
		int l;
		r = (r << 1) ^ (rand() >> 4);
		l = lines[(r % i) + 1];
		lines[(r % i) + 1] = lines[i];
		lines[i] = l;
	}

I 4
	/* layout the sequence of word accesses */
	for (i = 0; i < nwords; ++i) {
D 9
		words[i] = i * state->line / (nwords * sizeof(char*));
E 9
I 9
		words[i] = i;
E 9
	}

D 5
	/* randomize the line sequences */
E 5
I 5
	/* randomize the word sequences */
E 5
	for (i = nwords - 2; i > 0; --i) {
		int l;
		r = (r << 1) ^ (rand() >> 4);
		l = words[(r % i) + 1];
		words[(r % i) + 1] = words[i];
		words[i] = l;
E 12
I 12
		lines[i] *= nwords;
E 12
	}

E 4
	/* setup the run through the pages */
D 10
	for (i = 0, k = 0; i < npages; ++i) {
E 10
I 10
	for (i = 0, k = 0; i < npages && k < npointers; ++i) {
E 10
		for (j = 0; j < nlines - 1 && k < npointers - 1; ++j) {
D 4
			pages[i][lines[j]] = (char*)(pages[i] + lines[j+1]);
E 4
I 4
			pages[i][lines[j]+words[k%nwords]] = (char*)(pages[i] + lines[j+1] + words[(k+1)%nwords]);
E 4
			k++;
		}
D 3
		if (i == state->pages - 1 || k == npointers - 1) {
E 3
I 3
		if (i == npages - 1 || k == npointers - 1) {
E 3
D 4
			pages[i][lines[j]] = (char*)(pages[0] + lines[0]);
E 4
I 4
			pages[i][lines[j]+words[k%nwords]] = (char*)(pages[0] + lines[0] + words[0]);
E 4
		} else {
D 4
			pages[i][lines[j]] = (char*)(pages[i+1] + lines[0]);
E 4
I 4
			pages[i][lines[j]+words[k%nwords]] = (char*)(pages[i+1] + lines[0] + words[(k+1)%nwords]);
E 4
		}
		k++;
	}
I 12
	state->p = (char*)(pages[0] + lines[0] + words[0]);
E 12
I 10
/*
fprintf(stderr, "initialize: i=%d, k=%d, npointers=%d, len=%d, line=%d\n", i, k, npointers, state->len, state->line);
fprintf(stderr, "pages={");
for (j = 0; j < i; ++j) {
	u_long base = (u_long)state->addr / state->pagesize;
	u_long page = (u_long)pages[j] / state->pagesize;
	fprintf(stderr, "%lu", page - base);
	if (j < i - 1)
		fprintf(stderr, ", ");
}
fprintf(stderr, "}\n");
/**/
E 10

	free(pages);
	free(lines);
I 4
	free(words);
E 4

	/* run through the chain once to clear the cache */
	benchmark((npointers + 100) / 100, state);
}


D 8
void benchmark(uint64 iterations, void *cookie)
E 8
I 8
void benchmark(iter_t iterations, void *cookie)
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

void cleanup(void* cookie)
{
	struct _state* state = (struct _state*)cookie;
	free(state->addr);
	state->addr = NULL;
	state->p = NULL;
}


E 13

I 29
void
check_memory(int size, struct mem_state* state)
{
	int	i, j, first_page, npages, nwords;
	int	page, word_count, pagesize;
	off_t	offset;
	char	**p, **q;
	char	**start;

	pagesize = getpagesize();
	npages = (size + pagesize - 1) / pagesize;
	nwords = size / sizeof(char*);

	/*
	fprintf(stderr, "check_memory(%d, ...): entering, %d words\n", size, nwords);
	/**/
	word_count = 1;
	first_page = 0;
	start = (char**)(state->base + state->pages[0] + state->lines[0] + state->words[0]);
	for (q = p = (char**)*start; p != start; ) {
		word_count++;
		offset = (unsigned long)p - (unsigned long)state->base;
		page = offset - offset % pagesize;
		for (j = first_page; j < npages; ++j) {
			if (page == state->pages[j]) break;
		}
		if (j == npages) {
			for (j = 0; j < first_page; ++j) {
				if (page == state->pages[j]) break;
			}
			if (j == first_page) {
				fprintf(stderr, 
					"check_memory: bad memory reference for size %d\n", 
					size);
			}
		}
		first_page = j % npages;
		p = (char**)*p;
		if (word_count & 0x1) q == (char**)*q;
		if (*p == *q) {
			fprintf(stderr, "check_memory: unwanted memory cycle! page=%d\n", j);
			return;
		}
	}
	if (word_count != nwords) {
		fprintf(stderr, "check_memory: wrong word count, expected %d, got %d\n", nwords, word_count);
	}
	/*
	fprintf(stderr, "check_memory(%d, ...): exiting\n", size);
	/**/
I 32
}

void
pagesort(int n, int* pages, double* latencies)
{
	int	i, j;
	double	t;

	for (i = 0; i < n - 1; ++i) {
		for (j = i + 1; j < n; ++j) {
			if (latencies[i] > latencies[j]) {
				t = latencies[i]; 
				latencies[i] = latencies[j];
				latencies[j] = t;
				SWAP(pages[i], pages[j]);
			}
		}
	}
E 32
}
E 29
E 2
I 1
E 1
