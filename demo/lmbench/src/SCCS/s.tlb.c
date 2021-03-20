h11848
s 00029/00018/00149
d D 1.14 01/04/09 16:53:25 staelin 15 14
c Modify tlb's algorithm so that it is not dependent on line size
c calculations.  We use the new words_initialize() algorithm which 
c always jumps as far as possible from previously referenced words
c in a cache line.  Also, changed it from using sub-processes to
c doing everything in-process using the old BENCH() timing harness.
cC
cHhpli69.hpli.hpl.hp.com
cK25781
e
s 00003/00001/00164
d D 1.13 00/09/25 17:27:55 staelin 14 13
c - Add code to handle new state->maxlen parameter
cC
cK22098
e
s 00028/00222/00137
d D 1.12 00/09/18 16:44:11 staelin 13 12
c - Create lib_mem.h and lib_mem.c to hold common routines for memory subsystem analysis
cC
cK15880
e
s 00087/00122/00272
d D 1.11 00/09/13 12:41:46 staelin 12 11
c - Debug initialization routines so they set up pointer chains that work properly
c - Add "int* permutation(int N);" which returns a permutation of N integers
c - Replace custom command line parsing with "bytes(optarg);"
c - More tweaks to tlb-finding algorithm
cC
cK26846
e
s 00002/00002/00392
d D 1.10 00/07/30 11:46:19 staelin 11 10
c - Change type of "iterations" from uint64 to iter_t, which is a u_long
cC
cK28149
e
s 00023/00030/00371
d D 1.9 00/07/25 13:48:40 staelin 10 9
c - Switch from a sequential search to a binary search for the TLB size
c - Fix maxpages command-line processing which use to report bytes instead of pages
cC
cK27963
e
s 00021/00007/00380
d D 1.8 00/07/05 17:14:38 staelin 9 8
c - Add a second level of statistical median filtering on the results; since each
c   benchmark's memory access patterns are random, we need a second level of filtering
c   to determine the "representative" value.
cC
cK23439
e
s 00005/00003/00382
d D 1.7 00/07/05 14:37:18 staelin 8 7
c - tweaks to benchmark so if you change the memory buffer the benchmark doesn't core dump
cC
cK58844
e
s 00002/00002/00383
d D 1.6 00/07/05 12:02:13 staelin 7 6
c - Send output to stdout rather than stderr
cC
cK42443
e
s 00065/00021/00320
d D 1.5 00/07/05 11:28:08 staelin 6 5
c - Change memory access patterns to make better use of known cache line sizes
cC
cK44119
e
s 00041/00006/00300
d D 1.4 00/07/04 14:56:03 staelin 5 4
c - Update to incorporate new "-W <warmup>" and "-N <repetitions>" flags
cC
cK23511
e
s 00006/00002/00300
d D 1.3 00/07/03 15:44:09 staelin 4 3
c - Buglet/typos fixes
cC
cK23513
e
s 00001/00001/00301
d D 1.2 00/07/02 18:34:22 staelin 3 2
c - New benchmark which reports the size of the TLB (in pages) and optionally the cost
c   of a TLB miss
cC
cK18220
e
s 00302/00000/00000
d D 1.1 00/07/02 17:28:01 staelin 2 1
cF1
cK18762
cO-rw-rw-r--
e
s 00000/00000/00000
d D 1.0 00/07/02 17:28:01 staelin 1 0
c BitKeeper file /tmp_mnt/usr/WebPaper/users/staelin/src/LMbench/src/tlb.c
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHhpli8.hpli.hpl.hp.com
cK00373
cPsrc/tlb.c
cR3b067cbc1b0a6aca
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
 * tlb.c - guess the cache line size
 *
D 8
 * usage: tlb
E 8
I 8
 * usage: tlb [-c] [-L <line size>] [-M len[K|M]] [-W <warmup>] [-N <repetitions>]
E 8
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

D 13
struct _state {
	char*	addr;
	char*	p;
	int	pages;
I 6
	int	line;
E 6
	int	pagesize;
I 5
	int	warmup;
	int	repetitions;
E 5
};

I 12
int find_tlb(int start, int maxpages, double* tlb_time, double* cache_time, 
	     struct _state* state);
E 12
void compute_times(struct _state* state, double* tlb_time, double* cache_time);
void initialize_tlb(void* cookie);
void initialize_cache(void* cookie);
D 11
void benchmark(uint64 iterations, void* cookie);
E 11
I 11
void benchmark(iter_t iterations, void* cookie);
E 11
void cleanup(void* cookie);

#define	ONE	p = (char **)*p;
#define	FIVE	ONE ONE ONE ONE ONE
#define	TEN	FIVE FIVE
#define	FIFTY	TEN TEN TEN TEN TEN
#define	HUNDRED	FIFTY FIFTY
E 13
I 13
int find_tlb(int start, int maxpages, int warmup, int repetitions, 
	     double* tlb_time, double* cache_time, struct mem_state* state);
void compute_times(int pages, int warmup, int repetitions,
	     double* tlb_time, double* cache_time, struct mem_state* state);
E 13

I 10
#define THRESHOLD 1.15

E 10
/*
 * Assumptions:
 *
 * 1) Cache lines are a multiple of pointer-size words
D 6
 * 2) Cache lines are smaller than 1/2 a page size
E 6
I 6
 * 2) Cache lines no larger than 1/8 a page size
E 6
 * 3) Pages are an even multiple of cache lines
 */
int
main(int ac, char **av)
{
D 10
	int	i, l, len, tlb, maxpages;
E 10
I 10
D 12
	int	i, l, len, tlb, maxpages, lower, upper;
E 12
I 12
	int	i, l, len, tlb, maxpages;
E 12
E 10
	int	c;
	int	print_cost = 0;
I 13
	int	warmup = 0;
	int	repetitions = TRIES;
E 13
D 15
	int	maxline = getpagesize() / sizeof(char*);
E 15
D 9
	double tlb_time, cache_time, diff;
E 9
I 9
	double	tlb_time, cache_time, diff;
E 9
D 13
	struct _state state;
E 13
I 13
	struct mem_state state;
E 13
D 8
	char   *usage = "[-c] [-M len[K|M]]\n";
E 8
I 8
	char   *usage = "[-c] [-L <line size>] [-M len[K|M]] [-W <warmup>] [-N <repetitions>]\n";
E 8

	maxpages = 16 * 1024;
I 6
D 13
	state.line = state.pagesize / 8;
E 13
I 13
	state.width = 1;
D 15
	state.line = state.pagesize / 32;
E 15
E 13
E 6
	state.pagesize = getpagesize();
I 15
	state.line = sizeof(char*);
E 15
I 5
D 13
	state.warmup = 0;
	state.repetitions = TRIES;
E 13

E 5
	tlb = 2;

D 6
	while (( c = getopt(ac, av, "cM:")) != EOF) {
E 6
I 6
	while (( c = getopt(ac, av, "cL:M:W:N:")) != EOF) {
E 6
		switch(c) {
		case 'c':
			print_cost = 1;
			break;
I 6
		case 'L':
			state.line = atoi(optarg);
			break;
E 6
		case 'M':
D 12
			l = strlen(optarg);
			if (optarg[l-1] == 'm' || optarg[l-1] == 'M') {
				maxpages = 1024 * 1024;
				optarg[l-1] = 0;
			} else if (optarg[l-1] == 'k' || optarg[l-1] == 'K') {
				maxpages = 1024;
				optarg[l-1] = 0;
			}
D 10
			maxpages *= atoi(optarg);
E 10
I 10
			maxpages *= atoi(optarg);	/* max in bytes */
E 12
I 12
			maxpages = bytes(optarg);	/* max in bytes */
E 12
			maxpages /= getpagesize();	/* max in pages */
E 10
			break;
I 5
		case 'W':
D 13
			state.warmup = atoi(optarg);
E 13
I 13
			warmup = atoi(optarg);
E 13
			break;
		case 'N':
D 13
			state.repetitions = atoi(optarg);
E 13
I 13
			repetitions = atoi(optarg);
E 13
			break;
E 5
		default:
			lmbench_usage(ac, av, usage);
			break;
		}
	}

D 10
/*
	state.pages = 4;
	initialize_cache(&state);
	benchmark(1000, &state);
	cleanup(&state);
	exit(0);
/**/

E 10
D 4
	for (i = 2; maxpages; i<<=1) {
E 4
I 4
D 12
	for (i = 2; i <= maxpages; i<<=1) {
E 12
I 12
	/* assumption: no TLB will have less than 16 entries */
D 13
	tlb = find_tlb(8, maxpages, &tlb_time, &cache_time, &state);
E 13
I 13
	tlb = find_tlb(8, maxpages, warmup, repetitions, &tlb_time, &cache_time, &state);
E 13

D 15
	if (print_cost) {
D 13
		state.pages *= 2;
		compute_times(&state, &tlb_time, &cache_time);
E 13
I 13
		compute_times(tlb * 2, warmup, repetitions, &tlb_time, &cache_time, &state);
E 13
		fprintf(stderr, "tlb: %d pages %.5f nanoseconds\n", tlb, tlb_time - cache_time);
	} else {
		fprintf(stderr, "tlb: %d pages\n", tlb);
E 15
I 15
	if (tlb > 0) {
		if (print_cost) {
			compute_times(tlb * 2, warmup, repetitions, &tlb_time, &cache_time, &state);
			fprintf(stderr, "tlb: %d pages %.5f nanoseconds\n", tlb, tlb_time - cache_time);
		} else {
			fprintf(stderr, "tlb: %d pages\n", tlb);
		}
E 15
	}

I 15
	/*
E 15
	for (i = tlb<<1; i <= maxpages; i<<=1) {
E 12
E 4
D 13
		state.pages = i;
		compute_times(&state, &tlb_time, &cache_time);
E 13
I 13
		compute_times(i, warmup, repetitions, &tlb_time, &cache_time, &state);
E 13
I 12
	}
I 15
	/**/
E 15

	return(0);
}

int
D 13
find_tlb(int start, int maxpages, double* tlb_time, double* cache_time, struct _state* state)
E 13
I 13
find_tlb(int start, int maxpages, int warmup, int repetitions,
	 double* tlb_time, double* cache_time, struct mem_state* state)
E 13
{
	int	i, lower, upper;

	for (i = start; i <= maxpages; i<<=1) {
D 13
		state->pages = i;
		compute_times(state, tlb_time, cache_time);
E 13
I 13
		compute_times(i, warmup, repetitions, tlb_time, cache_time, state);
E 13
E 12

D 10
		if (tlb_time / cache_time > 1.25) {
			i>>=1;
E 10
I 10
D 12
		if (tlb_time / cache_time > THRESHOLD) {
E 12
I 12
		if (*tlb_time / *cache_time > THRESHOLD) {
E 12
			lower = i>>1;
			upper = i;
			i = lower + (upper - lower) / 2;
E 10
			break;
		}
D 10
		tlb = state.pages;
E 10
	}

D 4
	for (++i; i < maxpages; ++i) {
E 4
I 4
	/* we can't find any tlb effect */
D 10
	if (i == maxpages)
E 10
I 10
D 12
	if (i >= maxpages)
E 10
		exit(0);
E 12
I 12
	if (i >= maxpages) {
D 13
		state->pages = 0;
E 13
I 13
		state->len = 0;
E 13
		return (0);
	}
E 12

D 10
	for (++i; i <= maxpages; ++i) {
E 10
I 10
	/* use a binary search to locate point at which TLB effects start */
	while (lower + 1 < upper) {
E 10
E 4
D 12
		state.pages = i;
		compute_times(&state, &tlb_time, &cache_time);
E 12
I 12
D 13
		state->pages = i;
		compute_times(state, tlb_time, cache_time);
E 13
I 13
		compute_times(i, warmup, repetitions, tlb_time, cache_time, state);
E 13
E 12

D 9
		if (tlb_time / cache_time > 1.25) {
E 9
I 9
D 10
		if (tlb_time / cache_time > 1.15) {
E 9
			if (print_cost) {
				state.pages *= 2;
				compute_times(&state, &tlb_time, &cache_time);
			}
			break;
E 10
I 10
D 12
		if (tlb_time / cache_time > THRESHOLD) {
E 12
I 12
		if (*tlb_time / *cache_time > THRESHOLD) {
E 12
			upper = i;
		} else {
			lower = i;
E 10
		}
D 10
		tlb = state.pages;
	}

I 5
	for (i = 2; i <= maxpages; i<<=1) {
		state.pages = i;
		compute_times(&state, &tlb_time, &cache_time);
E 10
I 10
		i = lower + (upper - lower) / 2;
E 10
	}
I 10
D 12
	tlb = lower;
E 10

E 5
	if (print_cost) {
D 7
		fprintf(stderr, "tlb: %d pages %.5f nanoseconds\n", tlb, tlb_time - cache_time);
E 7
I 7
D 10
		printf("tlb: %d pages %.5f nanoseconds\n", tlb, tlb_time - cache_time);
E 10
I 10
		state.pages *= 2;
		compute_times(&state, &tlb_time, &cache_time);
		fprintf(stderr, "tlb: %d pages %.5f nanoseconds\n", tlb, tlb_time - cache_time);
E 10
E 7
	} else {
D 7
		fprintf(stderr, "tlb: %d pages\n", tlb);
E 7
I 7
D 10
		printf("tlb: %d pages\n", tlb);
E 10
I 10
		fprintf(stderr, "tlb: %d pages\n", tlb);
E 10
E 7
	}

	return(0);
E 12
I 12
D 13
	state->pages = lower;
E 13
	return (lower);
E 12
}

void
D 13
compute_times(struct _state* state, double* tlb_time, double* cache_time)
E 13
I 13
compute_times(int pages, int warmup, int repetitions,
	 double* tlb_time, double* cache_time, struct mem_state* state)
E 13
{
D 5
	benchmp(initialize_tlb, benchmark, cleanup, 0, 1, state);
E 5
I 5
D 9
	benchmp(initialize_tlb, benchmark, cleanup, 0, 1, 
		state->warmup, state->repetitions, state);
E 9
I 9
	int i;
	result_t tlb_results, cache_results, *r_save;

	r_save = get_results();
	insertinit(&tlb_results);
	insertinit(&cache_results);

D 15
	for (i = 0; i < TRIES; ++i) {
D 13
		benchmp(initialize_tlb, benchmark, cleanup, 0, 1, 
			state->warmup, state->repetitions, state);
E 13
I 13
		state->len = pages * state->pagesize;
I 14
		state->maxlen = pages * state->pagesize;
E 14
		benchmp(tlb_initialize, mem_benchmark_0, mem_cleanup, 0, 1, 
			warmup, repetitions, state);
E 13
		insertsort(gettime(), get_n(), &tlb_results);
E 15
I 15
	state->len = pages * state->pagesize;
	state->maxlen = pages * state->pagesize;
	tlb_initialize(state);
	if (state->initialized) {
		for (i = 0; i < TRIES; ++i) {
			BENCH1(mem_benchmark_0(__n, state); __n = 1;, 0);
			insertsort(gettime(), get_n(), &tlb_results);
		}
	}
	tlb_cleanup(state);
E 15
E 9
E 5
	
I 9
D 13
		benchmp(initialize_cache, benchmark, cleanup, 0, 1,
			state->warmup, state->repetitions, state);
E 13
I 13
D 15
		state->len = pages * state->line;
I 14
		state->maxlen = pages * state->line;
E 14
		benchmp(mem_initialize, mem_benchmark_0, mem_cleanup, 0, 1,
			warmup, repetitions, state);
E 13
		insertsort(gettime(), get_n(), &cache_results);
E 15
I 15
	state->len = pages * state->line;
	state->maxlen = pages * state->line;
	mem_initialize(state);
	if (state->initialized) {
		for (i = 0; i < TRIES; ++i) {
			BENCH1(mem_benchmark_0(__n, state); __n = 1;, 0);
			insertsort(gettime(), get_n(), &cache_results);
		}
E 15
	}
I 15
	mem_cleanup(state);
E 15

E 9
	/* We want nanoseconds / load. */
I 9
	set_results(&tlb_results);
E 9
	*tlb_time = (1000. * (double)gettime()) / (100. * (double)get_n());

D 5
	benchmp(initialize_cache, benchmark, cleanup, 0, 1, state);
E 5
I 5
D 9
	benchmp(initialize_cache, benchmark, cleanup, 0, 1,
		state->warmup, state->repetitions, state);
E 5
	
E 9
	/* We want nanoseconds / load. */
I 9
	set_results(&cache_results);
E 9
	*cache_time = (1000. * (double)gettime()) / (100. * (double)get_n());
I 9
	set_results(r_save);
E 9

D 5
	/* fprintf(stderr, "%d %.5f %.5f\n", state->pages, *tlb_time, *cache_time); */
E 5
I 5
D 10
	fprintf(stderr, "%d %.5f %.5f\n", state->pages, *tlb_time, *cache_time);
E 10
I 10
D 12
	/* fprintf(stderr, "%d %.5f %.5f\n", state->pages, *tlb_time, *cache_time); */
E 12
I 12
D 13
	/**/
E 13
I 13
	/*
E 13
D 14
	fprintf(stderr, "%d %.5f %.5f\n", state->pages, *tlb_time, *cache_time);
E 14
I 14
	fprintf(stderr, "%d %.5f %.5f\n", pages, *tlb_time, *cache_time);
E 14
	/**/
E 12
E 10
E 5
}
D 13

/*
 * This will access one word per page, for a total of len bytes of accessed
 * memory.
 */
void
initialize_tlb(void* cookie)
{
D 6
	int i, npointers;
E 6
I 6
D 12
	int i, nwords, nlines, npages;
E 12
I 12
	int i, nwords, nlines, npages, pagesize;
E 12
E 6
	unsigned int r;
	char ***pages;
I 5
	int    *lines;
I 6
	int    *words;
E 6
E 5
	struct _state* state = (struct _state*)cookie;
	register char *p = 0 /* lint */;

D 6
	npointers = state->pagesize / sizeof(char*);
E 6
I 6
D 12
	nwords = state->line / sizeof(char*);
	nlines = state->pagesize / state->line;
	npages = state->pages;
E 12
I 12
	pagesize = state->pagesize;
	nwords   = state->line / sizeof(char*);
	nlines   = pagesize / state->line;
	npages   = state->pages;

	srand(getpid());
E 12
E 6

D 6
	state->p = state->addr = (char*)malloc((state->pages + 1) * state->pagesize);
	pages = (char***)malloc(state->pages * sizeof(char**));
I 5
	lines = (int*)malloc(npointers * sizeof(int));
E 6
I 6
D 12
	words = (int*)malloc(nwords * sizeof(int));
	lines = (int*)malloc(nlines * sizeof(int));
E 12
I 12
	words = permutation(nwords);
	lines = permutation(nlines);
E 12
	pages = (char***)malloc(npages * sizeof(char**));
D 12
	state->p = state->addr = (char*)malloc((state->pages + 2) * state->pagesize);
E 12
I 12
	state->addr = (char*)valloc(pagesize);
E 12
E 6
E 5

D 5
	if (state->addr == NULL || pages == NULL) {
E 5
I 5
	if (state->addr == NULL || pages == NULL || lines == NULL) {
E 5
		exit(0);
	}

D 12
	if ((unsigned long)state->p % state->pagesize) {
		state->p += state->pagesize - (unsigned long)state->p % state->pagesize;
	}

	srand(getpid());

E 12
	/* first, layout the sequence of page accesses */
D 12
	p = state->p;
	for (i = 0; i < state->pages; ++i) {
E 12
I 12
	for (i = 0; i < npages; ++i) {
		p = (char*)valloc(pagesize);
		if ((unsigned long)state->p % pagesize) {
			free(p);
			p = (char*)valloc(2 * pagesize);
			p += pagesize - (unsigned long)p % pagesize;
		}
E 12
		pages[i] = (char**)p;
D 12
		p += state->pagesize;
E 12
	}

	/* randomize the page sequences (except for zeroth page) */
	r = (rand() << 15) ^ rand();
D 12
	for (i = state->pages - 2; i > 0; --i) {
E 12
I 12
	for (i = npages - 2; i > 0; --i) {
E 12
		char** l;
		r = (r << 1) ^ (rand() >> 4);
		l = pages[(r % i) + 1];
		pages[(r % i) + 1] = pages[i + 1];
		pages[i + 1] = l;
	}

I 5
D 12
	/* layout the sequence of line accesses */
D 6
	for (i = 0; i < npointers; ++i) {
		lines[i] = i * state->pagesize / (npointers * sizeof(char*));
E 6
I 6
	for (i = 0; i < nlines; ++i) {
		lines[i] = i * state->pagesize / (nlines * sizeof(char*));
E 6
	}

	/* randomize the line sequences */
D 6
	for (i = npointers - 2; i > 0; --i) {
E 6
I 6
	for (i = nlines - 2; i > 0; --i) {
E 6
		int l;
		r = (r << 1) ^ (rand() >> 4);
		l = lines[(r % i) + 1];
		lines[(r % i) + 1] = lines[i];
		lines[i] = l;
	}

E 5
D 6
	/* new setup run through the pages */
E 6
I 6
	/* layout the sequence of word accesses */
	for (i = 0; i < nwords; ++i) {
		words[i] = i * state->line / (nwords * sizeof(char*));
	}

	/* randomize the word sequences */
	for (i = nwords - 2; i > 0; --i) {
		int l;
		r = (r << 1) ^ (rand() >> 4);
		l = words[(r % i) + 1];
		words[(r % i) + 1] = words[i];
		words[i] = l;
	}
E 12
I 12
	for (i = 0; i < nlines; ++i)
		lines[i] *= nwords;
E 12

	/* now setup run through the pages */
E 6
D 12
	for (i = 0; i < state->pages - 1; ++i) {
E 12
I 12
	for (i = 0; i < npages - 1; ++i) {
E 12
D 5
		pages[i][i % npointers] = (char*)(pages[i+1] + (i+1) % npointers);
E 5
I 5
D 6
		pages[i][lines[i % npointers]] = (char*)(pages[i+1] + lines[(i+1) % npointers]);
E 6
I 6
		pages[i][lines[i % nlines]+words[i%nwords]] = (char*)(pages[i+1] + lines[(i+1) % nlines] + words[(i+1) % nwords]);
E 6
E 5
	}
D 5
	pages[state->pages - 1][(state->pages - 1) % npointers] = (char*)pages[0];
E 5
I 5
D 6
	pages[state->pages - 1][lines[(state->pages - 1) % npointers]] = (char*)(pages[0] + lines[0]);
E 6
I 6
	pages[i][lines[i % nlines]+words[i%nwords]] = (char*)(pages[0] + lines[0] + words[0]);
I 12
	state->p = (char*)(pages[0] + lines[0] + words[0]);
E 12
E 6
E 5

	free(pages);
I 5
	free(lines);
I 6
	free(words);
E 6
E 5

	/* run through the chain once to clear the cache */
D 12
	benchmark((state->pages + 100) / 100, state);
E 12
I 12
	benchmark((npages + 100) / 100, state);
E 12
}

/*
 * This will access len bytes
 */
void
initialize_cache(void* cookie)
{
D 6
	int i, j, nlines, nbytes, npages, npointers;
E 6
I 6
D 12
	int i, j, nwords, nlines, npages, npointers;
E 12
I 12
	int i, j, nwords, nlines, npages, npointers, pagesize;
E 12
E 6
	unsigned int r;
	char ***pages;
	int    *lines;
I 6
	int    *words;
E 6
	struct _state* state = (struct _state*)cookie;
	register char *p = 0 /* lint */;

D 6
	nbytes = state->pages * sizeof(char*);
	nlines = state->pagesize / sizeof(char*);
	npages = (nbytes + state->pagesize) / state->pagesize;
E 6
I 6
D 12
	nwords = state->line / sizeof(char*);
	nlines = state->pagesize / state->line;
	npages = state->pages / nlines;
E 12
I 12
	pagesize = state->pagesize;
	nwords   = state->line / sizeof(char*);
	nlines   = pagesize / state->line;
	npages   = state->pages / nlines;

	srand(getpid());
E 12

	if (state->pages % nlines)
		npages++;
E 6

I 6
D 12
	words = (int*)malloc(nwords * sizeof(int));
E 6
	lines = (int*)malloc(nlines * sizeof(int));
E 12
I 12
	words = permutation(nwords);
	lines = permutation(nlines);
E 12
	pages = (char***)malloc(npages * sizeof(char**));
D 6
	state->p = state->addr = (char*)malloc(nbytes + 2 * state->pagesize);
E 6
I 6
D 12
	state->p = state->addr = (char*)malloc((npages + 2) * state->pagesize);
E 6

	if ((unsigned long)state->p % state->pagesize) {
		state->p += state->pagesize - (unsigned long)state->p % state->pagesize;
	}
E 12
I 12
	state->addr = (char*)valloc((npages + 2) * pagesize);
E 12

	if (state->addr == NULL || pages == NULL) {
		exit(0);
	}

D 12
	srand(getpid());

E 12
	/* first, layout the sequence of page accesses */
D 12
	p = state->p;
	for (i = 0; i < npages; ++i) {
E 12
I 12
	p = state->addr;
	for (i = 0; i < npages; ++i, p += pagesize) {
E 12
		pages[i] = (char**)p;
D 12
		p += state->pagesize;
E 12
	}
I 12
	state->p = (char*)pages[0];
E 12

	/* randomize the page sequences (except for zeroth page) */
	r = (rand() << 15) ^ rand();
	for (i = npages - 2; i > 0; --i) {
		char** l;
		r = (r << 1) ^ (rand() >> 4);
		l = pages[(r % i) + 1];
		pages[(r % i) + 1] = pages[i + 1];
		pages[i + 1] = l;
	}

D 12
	/* layout the sequence of line accesses */
	for (i = 0; i < nlines; ++i) {
		lines[i] = i * state->pagesize / (nlines * sizeof(char*));
	}

	/* randomize the line sequences */
	for (i = nlines - 2; i > 0; --i) {
		int l;
		r = (r << 1) ^ (rand() >> 4);
		l = lines[(r % i) + 1];
		lines[(r % i) + 1] = lines[i];
		lines[i] = l;
	}

I 6
	/* layout the sequence of word accesses */
	for (i = 0; i < nwords; ++i) {
		words[i] = i * state->line / (nwords * sizeof(char*));
	}

	/* randomize the word sequences */
	for (i = nwords - 2; i > 0; --i) {
		int l;
		r = (r << 1) ^ (rand() >> 4);
		l = words[(r % i) + 1];
		words[(r % i) + 1] = words[i];
		words[i] = l;
	}
E 12
I 12
	for (i = 0; i < nlines; ++i)
		lines[i] *= nwords;
E 12

E 6
	/* setup the run through the pages */
	for (i = 0, npointers = 0; i < npages; ++i) {
D 12
		for (j = 0; j < nlines - 1 && npointers < state->pages - 1; ++j) {
E 12
I 12
		for (j = 0; j < nlines - 1 && npointers < npages - 1; ++j) {
E 12
D 6
			pages[i][lines[j]] = (char*)(pages[i] + lines[j+1]);
E 6
I 6
			pages[i][lines[j]+words[npointers%nwords]] = (char*)(pages[i] + lines[j+1] + words[(npointers+1)%nwords]);
E 6
			npointers++;
		}
D 3
		if (i == state->pages - 1 || npointers == state->pages - 1) {
E 3
I 3
D 12
		if (i == npages - 1 || npointers == state->pages - 1) {
E 12
I 12
		if (i == npages - 1 || npointers == npages - 1) {
E 12
E 3
D 6
			pages[i][lines[j]] = (char*)(pages[0] + lines[0]);
E 6
I 6
			pages[i][lines[j]+words[npointers%nwords]] = (char*)(pages[0] + lines[0] + words[0]);
E 6
		} else {
D 6
			pages[i][lines[j]] = (char*)(pages[i+1] + lines[0]);
E 6
I 6
			pages[i][lines[j]+words[npointers%nwords]] = (char*)(pages[i+1] + lines[0] + words[0]);
E 6
		}
		npointers++;
	}
I 12
	state->p = (char*)(pages[0] + lines[0] + words[0]);
E 12

	free(pages);
	free(lines);
I 6
	free(words);
E 6

	/* run through the chain once to clear the cache */
	benchmark((npages * nlines + 100) / 100, state);
}


D 11
void benchmark(uint64 iterations, void *cookie)
E 11
I 11
D 12
void benchmark(iter_t iterations, void *cookie)
E 12
I 12
void
benchmark(iter_t iterations, void *cookie)
E 12
E 11
{
	struct _state* state = (struct _state*)cookie;
I 8
	static char *addr_save = NULL;
E 8
	static char **p_save = NULL;
D 8
	register char **p = p_save ? p_save : (char**)state->p;
E 8
I 8
	register char **p = addr_save == state->addr ? p_save : (char**)state->p;
E 8

	while (iterations-- > 0) {
		HUNDRED;
	}

	use_pointer((void *)p);
	p_save = p;
I 8
	addr_save = state->addr;
E 8
}

D 12
void cleanup(void* cookie)
E 12
I 12
void
cleanup(void* cookie)
E 12
{
	struct _state* state = (struct _state*)cookie;
	free(state->addr);
	state->addr = NULL;
	state->p = NULL;
}


E 13

E 2
I 1
E 1
