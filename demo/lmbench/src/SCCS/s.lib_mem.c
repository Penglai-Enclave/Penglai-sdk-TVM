H03528
s 00022/00022/00567
d D 1.11 02/09/29 21:53:51 staelin 12 11
c - switch from 'int' to 'size_t' for better portability to large memory 
c   machines
cC
cHfirewall.staelin.co.il
cK03941
e
s 00020/00019/00569
d D 1.10 01/06/20 10:21:39 staelin 11 10
c src/line.c: Fix bug in automatic resizing when you request more memory than is
c available; matching fixes in lib_mem.c
cC
cK61725
e
s 00022/00006/00566
d D 1.9 01/05/22 17:27:15 staelin 10 9
c Fixup line_find so that it is robust on small memory machines.  Also,
c fix up par_mem so the minimum parallelism is 1.0.
cC
cK54617
e
s 00002/00000/00570
d D 1.8 01/04/09 16:57:46 staelin 9 8
c bugfix to par_mem to ensure that we check whether mem_initialize()
c was able to actually malloc() the memory!
cC
cK20733
e
s 00279/00094/00291
d D 1.7 01/04/09 16:45:49 staelin 8 7
c Rewrite lib_mem.c to eliminate or reduce a number of problems.
c First, reorganize the manner in which mem_initialize() creates
c the pointer chain to reduce the dependence on accurate line-size
c estimates.  Second, add a number of parameters to mem_state so 
c that external routines can easily change the pointer chain, which
c is useful for cache.c and others.  Third, modify line_find and
c par_mem so that they do their work without forking, which makes
c them faster and more efficient.  Fourth, fixup the cleanup routines
c so they are more careful and really delete all the utilized space.
cC
cHhpli69.hpli.hpl.hp.com
cK17885
cZ+03:00
e
s 00001/00001/00384
d D 1.6 00/10/19 17:05:42 staelin 7 6
c - Tweak lib_mem's line_test() to reduce the runtime by reducing
c   the number of experiments that are done.  
cC
cK13649
e
s 00010/00006/00375
d D 1.5 00/10/16 17:20:24 staelin 6 5
c - Fix result handling in lib_mem's line_test
cC
cK13985
cZ+02:00
e
s 00013/00010/00368
d D 1.4 00/09/28 12:16:50 staelin 5 4
c - Add error checking to par_mem() so you don't divide by zero
c - Tweak line_find()'s algorithm for identifying the line size to make it more stable
cC
cK06922
e
s 00081/00089/00297
d D 1.3 00/09/25 17:27:46 staelin 4 3
c - Major revision to simplify initialization code in mem_initialize() and line_initialize()
c - Change state->line for line_initialize(), line_test(), and find_line() to have the
c   same meaning as it already head elsewhere.  It now represents the number of bytes in
c   a cache line as opposed to the number of pointers in a cache line.
c - Add state->maxlen parameter which allows the caller to control the number of pages
c   allocated by the initialization routines.  The initialization routines will then 
c   randomly select pages to cover state->len bytes.  This allows the benchmarks to 
c   experiment with cache-unfriendly allocations.  It might have a beneficial effect on
c   systems without page coloring (to be determined ;-)
c - Move par_mem from par_mem.c so it is available to both par_mem.c and cache.c
cC
cK02500
e
s 00104/00021/00282
d D 1.2 00/09/19 16:52:52 staelin 3 2
c - Fix bug in mem_initialize where memory was accessed after it was freed
c - Add code to mem_initialize which runs through the memory once
c - Fix bug in line_initialize so you always have at least one page
c - Add comments before each of the initialize routines
c - Migrate line_find and line_test from line.c to lib_mem.c
cC
cK18010
e
s 00303/00000/00000
d D 1.1 00/09/18 16:42:55 staelin 2 1
cC
cF1
cK23083
cO-rw-rw-r--
e
s 00000/00000/00000
d D 1.0 00/09/18 16:42:55 staelin 1 0
c BitKeeper file /tmp_mnt/usr/WebPaper/users/staelin/src/LMbench/src/lib_mem.c
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHhpli8.hpli.hpl.hp.com
cK11663
cPsrc/lib_mem.c
cR6f15ac35118b1b38
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
 * lib_mem.c - library of routines used to analyze the memory hierarchy
 *
 * %W% %@%
 *
 * Copyright (c) 2000 Carl Staelin.
 * Copyright (c) 1994 Larry McVoy.  
 * Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */

#include "bench.h"

#define	FIVE(m)		m m m m m
#define	TEN(m)		FIVE(m) FIVE(m)
#define	FIFTY(m)	TEN(m) TEN(m) TEN(m) TEN(m) TEN(m)
#define	HUNDRED(m)	FIFTY(m) FIFTY(m)

#define DEREF(N)	p##N = (char**)*p##N;
#define DECLARE(N)	static char **sp##N; register char **p##N;
D 8
#define INIT(N)		p##N = (addr_save==state->addr) ? sp##N : (char**)state->p[N];
E 8
I 8
#define INIT(N)		p##N = (mem_benchmark_rerun && addr_save==state->addr) ? sp##N : (char**)state->p[N];
E 8
#define SAVE(N)		sp##N = p##N;

#define MEM_BENCHMARK_F(N) mem_benchmark_##N,
bench_f mem_benchmarks[] = {REPEAT_15(MEM_BENCHMARK_F)};

I 8
static int mem_benchmark_rerun = 0;

E 8
#define MEM_BENCHMARK_DEF(N,repeat,body) 				\
void									\
mem_benchmark_##N(iter_t iterations, void *cookie)			\
{									\
	struct mem_state* state = (struct mem_state*)cookie;		\
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
I 8
	mem_benchmark_rerun = 1;					\
E 8
}

MEM_BENCHMARK_DEF(0, REPEAT_0, DEREF)
MEM_BENCHMARK_DEF(1, REPEAT_1, DEREF)
MEM_BENCHMARK_DEF(2, REPEAT_2, DEREF)
MEM_BENCHMARK_DEF(3, REPEAT_3, DEREF)
MEM_BENCHMARK_DEF(4, REPEAT_4, DEREF)
MEM_BENCHMARK_DEF(5, REPEAT_5, DEREF)
MEM_BENCHMARK_DEF(6, REPEAT_6, DEREF)
MEM_BENCHMARK_DEF(7, REPEAT_7, DEREF)
MEM_BENCHMARK_DEF(8, REPEAT_8, DEREF)
MEM_BENCHMARK_DEF(9, REPEAT_9, DEREF)
MEM_BENCHMARK_DEF(10, REPEAT_10, DEREF)
MEM_BENCHMARK_DEF(11, REPEAT_11, DEREF)
MEM_BENCHMARK_DEF(12, REPEAT_12, DEREF)
MEM_BENCHMARK_DEF(13, REPEAT_13, DEREF)
MEM_BENCHMARK_DEF(14, REPEAT_14, DEREF)
MEM_BENCHMARK_DEF(15, REPEAT_15, DEREF)

I 3

I 8
D 12
int*	words_initialize(int max, int scale);
E 12
I 12
size_t*	words_initialize(size_t max, int scale);
E 12


void
mem_reset()
{
	mem_benchmark_rerun = 0;
}

E 8
void
mem_cleanup(void* cookie)
{
	struct mem_state* state = (struct mem_state*)cookie;
D 8
	free(state->addr);
	state->addr = NULL;
E 8
I 8
	if (state->addr) {
		free(state->addr);
		state->addr = NULL;
	}
	if (state->lines) {
		free(state->lines);
		state->lines = NULL;
	}
	if (state->pages) {
		free(state->pages);
		state->pages = NULL;
	}
	if (state->words) {
		free(state->words);
		state->words = NULL;
	}
}

void
tlb_cleanup(void* cookie)
{
D 12
	int i;
E 12
I 12
	size_t i;
E 12
	struct mem_state* state = (struct mem_state*)cookie;
	char **addr = (char**)state->addr;

	if (addr) {
		for (i = 0; i < state->npages; ++i) {
			if (addr[i]) free(addr[i]);
		}
		free(addr);
		state->addr = NULL;
	}
	if (state->pages) {
		free(state->pages);
		state->pages = NULL;
	}
	if (state->lines) {
		free(state->lines);
		state->lines = NULL;
	}
E 8
}

/*
 * mem_initialize
 *
 * Create a circular pointer chain that runs through memory.
 *
 * The chain threads through each cache line on a page before
 * moving to the next page.  The order of cache line accesses
 * is randomized to defeat cache prefetching algorithms.  In
 * addition, the order of page accesses is randomized.  Finally,
 * to reduce the impact of incorrect line-size estimates on
 * machines with direct-mapped caches, we randomize which 
 * word in the cache line is used to hold the pointer.
 *
 * It initializes state->width pointers to elements evenly
 * spaced through the chain.
 */
E 3
void
mem_initialize(void* cookie)
{
D 4
	int i, j, k, nwords, nlines, nbytes, npages, npointers;
E 4
I 4
D 8
	int i, j, k, w, nwords, nlines, nbytes, npages, nmpages, npointers;
E 8
I 8
	int i, j, k, l, np, nw, nwords, nlines, nbytes, npages, nmpages, npointers;
E 8
E 4
	unsigned int r;
D 4
	char ***pages;
E 4
I 4
	int    *pages;
E 4
	int    *lines;
	int    *words;
	struct mem_state* state = (struct mem_state*)cookie;
	register char *p = 0 /* lint */;

I 8
	state->initialized = 0;
	mem_reset();

E 8
	npointers = state->len / state->line;
	nbytes = state->len;
	nwords = state->line / sizeof(char*);
	nlines = state->pagesize / state->line;
D 4
	npages = (nbytes + state->pagesize) / state->pagesize;
E 4
I 4
	npages = (nbytes + state->pagesize - 1) / state->pagesize;
	nmpages= (state->maxlen + state->pagesize - 1) / state->pagesize;
E 4

	srand(getpid());

D 4
	words = permutation(nwords);
	lines = permutation(nlines);
	pages = (char***)malloc(npages * sizeof(char**));
	state->p[0] = state->addr = (char*)malloc(nbytes + 2 * state->pagesize);
E 4
I 4
D 8
	words = permutation(nwords, sizeof(char*));
	lines = permutation(nlines, state->line);
E 8
I 8
	words = words_initialize(nwords, sizeof(char*));
	lines = words_initialize(nlines, state->line);
E 8
	pages = permutation(nmpages, state->pagesize);
	p = state->addr = (char*)malloc(state->maxlen + 2 * state->pagesize);
E 4

I 8
	state->nwords = nwords;
	state->nlines = nlines;
	state->npages = npages;
	state->lines = lines;
	state->pages = pages;
	state->words = words;

E 8
I 3
D 4
	if (state->addr == NULL || pages == NULL || lines == NULL || words == NULL) {
E 4
I 4
	if (state->addr == NULL \
	    || pages == NULL || lines == NULL || words == NULL) {
E 4
D 8
		exit(0);
E 8
I 8
		return;
E 8
	}

E 3
D 4
	if ((unsigned long)state->p[0] % state->pagesize) {
		state->p[0] += state->pagesize;
		state->p[0] -= (unsigned long)state->p[0] % state->pagesize;
	}

D 3
	if (state->addr == NULL || pages == NULL) {
		exit(0);
	}

E 3
	/* first, layout the sequence of page accesses */
	p = state->p[0];
	for (i = 0; i < npages; ++i) {
		pages[i] = (char**)p;
E 4
I 4
	if ((unsigned long)p % state->pagesize) {
E 4
		p += state->pagesize;
D 4
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
D 3
		lines[i] *= state->pagesize / (nlines * sizeof(char*));
	}

	/* layout the sequence of word accesses */
	for (i = 0; i < nwords; ++i) {
		words[i] *= state->line / (nwords * sizeof(char*));
E 3
I 3
		lines[i] *= nwords;
E 4
I 4
		p -= (unsigned long)p % state->pagesize;
E 4
E 3
	}
I 8
	state->base = p;
E 8

	/* setup the run through the pages */
D 4
	for (i = 0, k = 0; i < npages; ++i) {
E 4
I 4
D 8
	for (i = 0, k = 0, w = 0; i < npages; ++i) {
E 4
		for (j = 0; j < nlines - 1 && k < npointers - 1; ++j) {
D 4
			pages[i][lines[j]+words[k%nwords]] = (char*)(pages[i] + lines[j+1] + words[(k+1)%nwords]);
E 4
I 4
			*(char**)(p + pages[i] + lines[j] + words[w]) =
			    p + pages[i] + lines[j+1] + words[w];
			if (k % (npointers/state->width) == 0
			    && k / (npointers/state->width) < MAX_MEM_PARALLELISM) {
				state->p[k / (npointers/state->width)] = 
					p + pages[i] + lines[j] + words[w];
E 8
I 8
	l = 0;
	for (i = 0; i < npages; ++i) {
		for (j = 0; j < nlines - 1 && l < npointers - 1; ++j, ++l) {
			for (k = 0; k < state->line; k += sizeof(char*)) {
				*(char**)(p + pages[i] + lines[j] + k) =
					p + pages[i] + lines[j+1] + k;
			}
			if (l % (npointers/state->width) == 0
			    && l / (npointers/state->width) < MAX_MEM_PARALLELISM) {
				k = l / (npointers/state->width);
				state->p[k] = p + pages[i] + lines[j] + words[k % nwords];
E 8
			}
E 4
D 8
			k++;
E 8
		}
D 8
		if (i == npages - 1 || k == npointers - 1) {
D 4
			pages[i][lines[j]+words[k%nwords]] = (char*)(pages[0] + lines[0] + words[0]);
E 4
I 4
			*(char**)(p + pages[i] + lines[j] + words[w]) =
			    p + pages[0] + lines[0] + words[0];
E 4
		} else {
D 4
			pages[i][lines[j]+words[k%nwords]] = (char*)(pages[i+1] + lines[0] + words[(k+1)%nwords]);
E 4
I 4
			*(char**)(p + pages[i] + lines[j] + words[w]) =
			    p + pages[i+1] + lines[0] + words[(w+1)%nwords];
		}
		if (k % (npointers/state->width) == 0
		    && k / (npointers/state->width) < MAX_MEM_PARALLELISM) {
			state->p[k / (npointers/state->width)] = 
				p + pages[i] + lines[j] + words[w];
E 4
		}
		k++;
I 4
		w = (w+1) % nwords;
E 4
	}
I 3
D 4
	state->p[0] = (char*)(pages[0] + lines[0] + words[0]);
E 4
E 3

	free(pages);
	free(lines);
	free(words);
E 8
I 8

		if (i < npages - 1) {
			for (k = 0; k < nwords; ++k) 
				*(char**)(p + pages[i] + lines[j] + words[k]) =
					p + pages[i+1] + lines[0] + words[k];
		}
	}
	for (k = 0; k < nwords; ++k) {
		nw = (k == nwords - 1) ? 0 : k + 1;
		*(char**)(p + pages[npages-1] + lines[j] + words[k]) =
			p + pages[0] + lines[0] + words[nw];
	}
E 8

D 3
	state->p[0] = (char*)(pages[0] + lines[0] + words[0]);
E 3
D 4
	for (p = state->p[0], i = 0; i < k; ++i) {
		if (i % (k/state->width) == 0) {
			state->p[i / (k/state->width)] = p;
		}
		p = *(char**)p;
	}
I 3

E 4
	/* now, run through the chain once to clear the cache */
D 8
	(*mem_benchmarks[state->width-1])((npointers + 100) / 100, state);
E 8
I 8
	mem_reset();
	(*mem_benchmarks[state->width-1])((nwords * npointers + 100) / 100, state);

	state->initialized = 1;
E 8
E 3
}

I 3
/*
 * line_initialize
 *
 * This is very similar to mem_initialize, except that we always use
 * the first element of the cache line to hold the pointer.
 *
 */
E 3
void
line_initialize(void* cookie)
{
D 4
	int i, j, k, last, line, nlines, npages;
E 4
I 4
	int i, j, k, line, nlines, npages;
E 4
	unsigned int r;
D 4
	char ***pages;
E 4
I 4
	int    *pages;
E 4
	int    *lines;
	struct mem_state* state = (struct mem_state*)cookie;
	register char *p = 0 /* lint */;

I 8
	state->initialized = 0;

E 8
	state->width = 1;
D 4
	last = state->line - 1;
	line = state->line * sizeof(char*);
	nlines = state->pagesize / line;
E 4
I 4
	nlines = state->pagesize / state->line;
E 4
D 3
	npages = state->len / state->pagesize;
E 3
I 3
	npages = (state->len + state->pagesize - 1) / state->pagesize;
E 3

	srand(getpid());

D 4
	state->p[0] = state->addr = (char*)valloc(state->len + state->pagesize);
	pages = (char***)malloc(npages * sizeof(char**));
	lines = permutation(nlines);
E 4
I 4
D 8
	p     = state->addr = (char*)valloc(state->len + state->pagesize);
E 8
I 8
	lines = words_initialize(nlines, state->line);
E 8
	pages = permutation(npages, state->pagesize);
D 8
	lines = permutation(nlines, state->line);
E 8
I 8
	p     = state->addr = (char*)valloc(state->len + state->pagesize);
E 8
E 4

I 8
	state->nwords = 0;
	state->nlines = nlines;
	state->npages = npages;
	state->words = NULL;
	state->lines = lines;
	state->pages = pages;
	
E 8
D 10
	if (state->addr == NULL || lines == NULL || pages == NULL) {
E 10
I 10
	if (state->addr == NULL || state->lines == NULL || state->pages == NULL) {
		if (state->lines) free(state->lines);
		if (state->pages) free(state->pages);
		if (state->addr)  free(state->addr);
		state->lines = NULL;
		state->pages = NULL;
		state->addr = NULL;
E 10
D 8
		exit(0);
E 8
I 8
		return;
E 8
	}

D 4
	if ((unsigned long)state->p[0] % state->pagesize) {
		state->p[0] += state->pagesize;
		state->p[0] -= (unsigned long)state->p[0] % state->pagesize;
	}

	/* first, layout the sequence of page accesses */
	p = state->p[0];
	for (i = 0; i < npages; ++i) {
		pages[i] = (char**)p;
E 4
I 4
	if ((unsigned long)p % state->pagesize) {
E 4
		p += state->pagesize;
I 4
		p -= (unsigned long)p % state->pagesize;
E 4
	}
I 8
	state->base = p;
E 8

D 4
	/* randomize the page sequences */
	r = (rand() << 15) ^ rand();
	for (i = npages - 1; i > 0; --i) {
		char **l;
		r = (r << 1) ^ (rand() >> 4);
		l = pages[r % i];
		pages[r % i] = pages[i];
		pages[i] = l;
	}

	for (i = 0; i < nlines; ++i)
		lines[i] *= state->line;

E 4
	/* new setup runs through the lines */
	for (i = 0; i < npages; ++i) {
		/* sequence through the first word of each line */
		for (j = 0; j < nlines - 1; ++j) {
D 4
			pages[i][lines[j]] = (char*)(pages[i] + lines[j+1]);
E 4
I 4
			*(char**)(p + pages[i] + lines[j]) = 
				p + pages[i] + lines[j+1];
E 4
		}

		/* jump to the fist word of the first line on next page */
D 4
		if (i < npages - 1) {
			pages[i][lines[j]] = (char*)(pages[i+1] + lines[0]);
		} else {
			pages[i][lines[j]] = (char*)(pages[0] + lines[0]);
		}
E 4
I 4
		*(char**)(p + pages[i] + lines[j]) = 
			p + pages[(i < npages-1) ? i+1 : 0] + lines[0];
E 4
	}
D 4
	state->p[0] = (char*)(pages[0] + lines[0]);
E 4
I 4
	state->p[0] = p + pages[0] + lines[0];
E 4

D 8
	free(lines);
	free(pages);

E 8
	/* now, run through the chain once to clear the cache */
I 8
	mem_reset();
E 8
	mem_benchmark_0((nlines * npages + 100) / 100, state);
I 8

	state->initialized = 1;
E 8
}

/*
D 3
 * This will access one word per page, for a total of 
 * (line * pages) of data loaded into cache.
E 3
I 3
 * tlb_initialize
 *
 * Build a pointer chain which accesses one word per page, for a total
 * of (line * pages) bytes of data loaded into cache.  
 *
 * If the number of elements in the chain (== #pages) is larger than the
 * number of pages addressed by the TLB, then each access should cause
 * a TLB miss (certainly as the number of pages becomes much larger than
 * the TLB-addressed space).
 *
 * In addition, if we arrange the chain properly, each word we access
 * will be in the cache.
 *
 * This means that the average access time for each pointer dereference
 * should be a cache hit plus a TLB miss.
 *
E 3
 */
void
tlb_initialize(void* cookie)
{
D 8
	int i, nwords, nlines, npages, pagesize;
E 8
I 8
	int i, j, nwords, nlines, npages, pagesize;
E 8
	unsigned int r;
D 8
	char ***pages;
	int    *lines;
	int    *words;
E 8
I 8
	char **pages = NULL;
	char **addr = NULL;
	int    *lines = NULL;
E 8
	struct mem_state* state = (struct mem_state*)cookie;
	register char *p = 0 /* lint */;

I 8
	state->initialized = 0;

E 8
	pagesize = state->pagesize;
D 8
	nwords   = state->line / sizeof(char*);
	nlines   = pagesize / state->line;
E 8
I 8
	nwords   = 0;
	nlines   = pagesize / sizeof(char*);
E 8
	npages   = state->len / pagesize;

D 8
	srand(getpid());
E 8
I 8
	srand(getpid() ^ (getppid()<<7));
E 8

D 4
	words = permutation(nwords);
	lines = permutation(nlines);
E 4
I 4
D 8
	words = permutation(nwords, 1);
	lines = permutation(nlines, 1);
E 4
	pages = (char***)malloc(npages * sizeof(char**));
	state->addr = (char*)valloc(pagesize);
E 8
I 8
	lines = words_initialize(nlines, sizeof(char*));
	pages = (char**)malloc(npages * sizeof(char**));
	addr = (char**)malloc(npages * sizeof(char**));

	state->nwords = 1;
	state->nlines = nlines;
	state->npages = npages;
	state->words = NULL;
	state->lines = lines;
	state->pages = (int*)pages;
	state->addr = (char*)addr;
	if (addr) bzero(addr, npages * sizeof(char**));
	if (pages) bzero(pages, npages * sizeof(char**));
E 8

D 3
	if (state->addr == NULL || pages == NULL || lines == NULL) {
E 3
I 3
D 8
	if (state->addr == NULL || pages == NULL || lines == NULL || words == NULL) {
E 3
		exit(0);
E 8
I 8
	if (addr == NULL || pages == NULL || lines == NULL) {
		return;
E 8
	}

	/* first, layout the sequence of page accesses */
	for (i = 0; i < npages; ++i) {
D 8
		p = (char*)valloc(pagesize);
		if ((unsigned long)state->p % pagesize) {
E 8
I 8
		p = addr[i] = (char*)valloc(pagesize);
		if (p == NULL) return;
		if ((unsigned long)p % pagesize) {
E 8
			free(p);
D 8
			p = (char*)valloc(2 * pagesize);
E 8
I 8
			p = addr[i] = (char*)valloc(2 * pagesize);
			if (p == NULL) return;
E 8
			p += pagesize - (unsigned long)p % pagesize;
		}
D 8
		pages[i] = (char**)p;
E 8
I 8
		pages[i] = (char*)p;
E 8
	}

	/* randomize the page sequences (except for zeroth page) */
	r = (rand() << 15) ^ rand();
	for (i = npages - 2; i > 0; --i) {
D 8
		char** l;
E 8
I 8
		char* l;
E 8
		r = (r << 1) ^ (rand() >> 4);
		l = pages[(r % i) + 1];
		pages[(r % i) + 1] = pages[i + 1];
		pages[i + 1] = l;
	}

D 8
	for (i = 0; i < nlines; ++i)
		lines[i] *= nwords;

E 8
	/* now setup run through the pages */
	for (i = 0; i < npages - 1; ++i) {
D 8
		pages[i][lines[i % nlines]+words[i%nwords]] = (char*)(pages[i+1] + lines[(i+1) % nlines] + words[(i+1) % nwords]);
E 8
I 8
		*(char**)(pages[i] + lines[i%nlines]) = 
			pages[i+1] + lines[(i+1)%nlines];
E 8
	}
D 8
	pages[i][lines[i % nlines]+words[i%nwords]] = (char*)(pages[0] + lines[0] + words[0]);
	state->p[0] = (char*)(pages[0] + lines[0] + words[0]);

	free(pages);
	free(lines);
	free(words);
E 8
I 8
	*(char**)(pages[i] + lines[i%nlines]) = pages[0] + lines[0];
	state->p[0] = pages[0] + lines[0];
E 8

	/* run through the chain once to clear the cache */
I 8
	mem_reset();
E 8
	mem_benchmark_0((npages + 100) / 100, state);
I 8

	state->initialized = 1;
}

/*
 * words_initialize
 *
 * This is supposed to create the order in which the words in a 
 * "cache line" are used.  Since we rarely know the cache line
 * size with any real reliability, we need to jump around so
 * as to maximize the number of potential cache misses, and to
 * minimize the possibility of re-using a cache line.
 */
D 12
int*
words_initialize(int max, int scale)
E 12
I 12
size_t*
words_initialize(size_t max, int scale)
E 12
{
D 12
	int	i, j, nbits;
	int*	words = (int*)malloc(max * sizeof(int));
E 12
I 12
	size_t	i, j, nbits;
	size_t*	words = (int*)malloc(max * sizeof(size_t));
E 12

D 12
	if (words) bzero(words, max * sizeof(int));
E 12
I 12
	if (words) bzero(words, max * sizeof(size_t));
E 12
	else return NULL;

	for (i = max>>1, nbits = 0; i != 0; i >>= 1, nbits++)
		;
	for (i = 0; i < max; ++i) {
		/* now reverse the bits */
		for (j = 0; j < nbits; j++) {
			if (i & (1<<j)) {
				words[i] |= (1<<(nbits-j-1));
			}
		}
		words[i] *= scale;
	}
	return words;
E 8
}

I 8

E 8
D 3

void
mem_cleanup(void* cookie)
E 3
I 3
D 12
int
line_find(int len, int warmup, int repetitions, struct mem_state* state)
E 12
I 12
size_t
line_find(size_t len, int warmup, int repetitions, struct mem_state* state)
E 12
E 3
{
D 3
	struct mem_state* state = (struct mem_state*)cookie;
	free(state->addr);
	state->addr = NULL;
E 3
I 3
D 5
	int 	i, j;
	int 	l = 0;
E 5
I 5
D 8
	int 	i, j, big_jump;
E 5
D 4
	int	maxline = getpagesize() / (8 * sizeof(char*));
E 4
I 4
	int	maxline = getpagesize() / 8;
E 8
I 8
D 12
	int 	i, j, big_jump, line;
	int	maxline = getpagesize() / 16;
E 12
I 12
	size_t 	i, j, big_jump, line;
	size_t	maxline = getpagesize() / 16;
E 12
E 8
E 4
D 5
	double	t, threshold;
E 5
I 5
	double	baseline, t;
E 5

D 8
	state->len = len;
E 8
I 5
	big_jump = 0;
I 8
	line = 0;
E 8
E 5

D 5
	threshold = .85 * line_test(maxline, warmup, repetitions, state);

D 4
	for (i = maxline>>1; i >= 2; i>>=1) {
E 4
I 4
	for (i = maxline>>1; i >= sizeof(char*); i>>=1) {
E 5
I 5
D 8
	for (i = sizeof(char*); i <= maxline; i<<=1) {
E 5
E 4
		t = line_test(i, warmup, repetitions, state);

I 6
		if (t == 0.) break;

E 6
D 5
		if (t <= threshold) {
D 4
			return ((i<<1) * sizeof(char*));
E 4
I 4
			return (i<<1);
E 5
I 5
		if (i > sizeof(char*)) {
			if (t > 1.3 * baseline) {
				big_jump = 1;
			} else if (big_jump && t < 1.15 * baseline) {
				return (i>>1);
E 8
I 8
D 10
	state->len = len;
	state->maxlen = len;
E 10
I 10
	/*
	fprintf(stderr, "line_find(%d, ...): entering\n", len);
	/**/

E 10
	state->width = 1;
	state->line = sizeof(char*);
D 10
	line_initialize(state);
E 10
I 10
D 11
	state->addr = NULL;
	while (state->addr == NULL) {
E 11
I 11
	for (state->addr = NULL; !state->addr && len; ) {
E 11
		state->len = state->maxlen = len;
		line_initialize(state);
		if (state->addr == NULL) len >>= 1;
	}
E 10
D 11
	if (state->addr) {
		for (i = sizeof(char*); i <= maxline; i<<=1) {
			t = line_test(i, warmup, repetitions, state);

			if (t == 0.) break;

			if (i > sizeof(char*)) {
				if (t > 1.3 * baseline) {
					big_jump = 1;
				} else if (big_jump && t < 1.15 * baseline) {
					line = (i>>1);
					break;
				}
E 11
I 11
	if (state->addr == NULL) return -1;

	for (i = sizeof(char*); i <= maxline; i<<=1) {
		t = line_test(i, warmup, repetitions, state);

		if (t == 0.) break;

		if (i > sizeof(char*)) {
			if (t > 1.3 * baseline) {
				big_jump = 1;
			} else if (big_jump && t < 1.15 * baseline) {
				line = (i>>1);
				break;
E 11
E 8
			}
I 8
D 11
			baseline = t;
E 11
E 8
E 5
E 4
		}
I 11
		baseline = t;
E 11
I 5
D 8
		baseline = t;
E 8
E 5
	}
D 8

	return (0);
E 8
I 8
	mem_cleanup(state);
I 10
	/*
	fprintf(stderr, "line_find(%d, ...): returning %d\n", len, line);
	/**/
E 10
	return line;
E 8
E 3
}

I 3
double
D 4
line_test(int len, int warmup, int repetitions, struct mem_state* state)
E 4
I 4
D 12
line_test(int line, int warmup, int repetitions, struct mem_state* state)
E 12
I 12
line_test(size_t line, int warmup, int repetitions, struct mem_state* state)
E 12
E 4
{
D 12
	int	i;
I 8
	int	npages = state->npages;
	int	nlines = state->pagesize / line;
E 12
I 12
	size_t	i;
	size_t	npages = state->npages;
	size_t	nlines = state->pagesize / line;
E 12
E 8
	double	t;
I 8
	char*	p = state->base;
	char*	first = p + state->pages[0] + state->lines[0];
	char*	last = p + state->pages[npages-1] + state->lines[nlines-1];
E 8
D 6
	result_t r, *r_save;
E 6
I 6
	result_t *r, *r_save;
E 6

D 4
	state->line = len;
E 4
I 4
D 8
	state->line = line;
E 8
I 8

	/* only visit a subset of the lines in each page */
	if (nlines < state->nlines) {
		p = state->base;
		for (i = 0; i < npages - 1; ++i) {
			*(char**)(p + state->pages[i] + state->lines[nlines-1]) =
				p + state->pages[i+1] + state->lines[0];
		}
		*(char**)(p + state->pages[npages-1] + state->lines[nlines-1]) =
			p + state->pages[0] + state->lines[0];
	}

E 8
E 4
	r_save = get_results();
D 6
	insertinit(&r);
	for (i = 0; i < 5; ++i) {
E 6
I 6
	r = (result_t*)malloc(sizeof_result(repetitions));
	insertinit(r);
I 8
	p = first;
E 8
	for (i = 0; i < repetitions; ++i) {
E 6
D 8
		benchmp(line_initialize, mem_benchmark_0, mem_cleanup, 
D 6
			0, 1, warmup, repetitions, state);
		insertsort(gettime(), get_n(), &r);
E 6
I 6
D 7
			0, 1, warmup, TRIES, state);
E 7
I 7
			0, 1, warmup, 7, state);
E 8
I 8
		BENCH1(HUNDRED(p = *(char**)p;),0);
		/*
D 10
		fprintf(stderr, "%d\t%d\n", (int)gettime(), (int)get_n()); 
E 10
I 10
		fprintf(stderr, "%d\t%d\t%d\n", line, (int)gettime(), (int)get_n()); 
E 10
		/**/
E 8
E 7
		insertsort(gettime(), get_n(), r);
E 6
	}
I 8
	use_pointer(p);
E 8
D 6
	set_results(&r);
E 6
I 6
	set_results(r);
E 6
	t = 10. * (double)gettime() / (double)get_n();
	set_results(r_save);
I 6
	free(r);
E 6
	
	/*
D 4
	fprintf(stderr, "%d\t%.5f\t%d\n", len * sizeof(char*), t, state->len); 
E 4
I 4
	fprintf(stderr, "%d\t%.5f\t%d\n", line, t, state->len); 
E 4
	/**/

I 8
	/* fixup full path again */
	if (nlines < state->nlines) {
		p = state->base;
		for (i = 0; i < npages - 1; ++i) {
			*(char**)(p + 
				  state->pages[i] + 
				  state->lines[nlines-1]) =
				p + 
				state->pages[i] + 
				state->lines[nlines];
		}
		*(char**)(p + 
			  state->pages[npages-1] + 
			  state->lines[nlines-1]) =
			p + 
			state->pages[npages-1] + 
			state->lines[nlines];
	}

E 8
	return (t);
}
I 4

double
D 12
par_mem(int len, int warmup, int repetitions, struct mem_state* state)
E 12
I 12
par_mem(size_t len, int warmup, int repetitions, struct mem_state* state)
E 12
{
D 8
	int	i;
E 8
I 8
	int	i, j, k, n, __n;
E 8
	double	baseline, max_par, par;

I 8
	state->width = 1;
E 8
D 11
	state->len = len;
	state->maxlen = len;
E 11
D 5
	max_par = 1.;
E 5
I 5
D 10
	max_par = -1.;
E 10
I 10
	max_par = 1.;
E 10
E 5
D 8
		
E 8
I 8
	__n = 1;

D 11
	mem_initialize(state);
E 11
I 11
	for (state->addr = NULL; !state->addr && len; ) {
		state->len = state->maxlen = len;
		mem_initialize(state);
		if (state->addr == NULL) len >>= 1;
	}
E 11
I 9
	if (state->addr == NULL) return -1.;

E 9
E 8
	for (i = 0; i < MAX_MEM_PARALLELISM; ++i) {
D 8
		state->width = i + 1;
		benchmp(mem_initialize, mem_benchmarks[i], mem_cleanup, 
			0, 1, warmup, repetitions, state);
E 8
I 8
		n = len / state->line;
		for (j = 0; j <= i; j++) {
D 12
			int nlines = len / state->line;
			int lines_per_chunk = nlines / (i + 1);
			int lines_per_page = state->pagesize / state->line;
			int words_per_chunk = state->nwords / (i + 1);
			int line = j * lines_per_chunk;
			int word = (j * state->nwords) / (i + 1);
E 12
I 12
			size_t nlines = len / state->line;
			size_t lines_per_chunk = nlines / (i + 1);
			size_t lines_per_page = state->pagesize / state->line;
			size_t words_per_chunk = state->nwords / (i + 1);
			size_t line = j * lines_per_chunk;
			size_t word = (j * state->nwords) / (i + 1);
E 12

			/*
			if (state->len == 32768 && i == 7) {
				fprintf(stderr, "\tj=%d, line=%d, word=%d, page=%d, _line=%d, _word=%d\n", j, line, word, line / lines_per_page, line % lines_per_page, word % state->nwords);
			}
			/**/
			state->p[j] = state->base + 
				state->pages[line / lines_per_page] + 
				state->lines[line % lines_per_page] + 
				state->words[word % state->nwords];
		}
		mem_reset();
		(*mem_benchmarks[i])((len / sizeof(char*) + 100) / 100, state);
		BENCH((*mem_benchmarks[i])(__n, state); __n = 1;, 0);
E 8
		if (i == 0) {
			baseline = (double)gettime() / (double)get_n();
D 5
		} else {
E 5
I 5
		} else if (gettime() > 0) {
E 5
			par = baseline;
			par /= (double)gettime() / (double)((i + 1) * get_n());
I 8
			/*
			fprintf(stderr, "par_mem(%d): i=%d, p=%5.2f, l=%d, lpp=%d, lpc=%d, nl=%d, wpc=%d\n", len, i, par, state->line, state->pagesize / state->line, (len / state->line) / (i + 1), len / state->line, state->nwords / (i + 1));
			/**/
E 8
			if (par > max_par) {
				max_par = par;
			}
		}
	}
I 8
	mem_cleanup(state);
E 8

	return max_par;
}


E 4
E 3
E 2
I 1
E 1
