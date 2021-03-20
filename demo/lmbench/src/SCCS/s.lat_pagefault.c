H54100
s 00053/00032/00145
d D 1.15 02/10/28 09:22:15 staelin 16 15
c lat_pagefault: 
c   - rewrite so it destroys and recreates the mmap'ing
c     each time it loops through all the pages.
c   - change the page access order so it is randomized
c   - subtract off the overhead of mmap'ing and munmap'ing
c     the file
cC
cK17319
e
s 00024/00006/00153
d D 1.14 01/11/13 16:36:34 staelin 15 14
c Add ability for child processes in file-related benchmarks to each
c have their own file, as it sometimes makes a difference whether you
c measure N processes beating on a single file or on N independent
c files.
cC
cHhpli69.hpli.hpl.hp.com
cK38162
cZ+02:00
e
s 00121/00033/00038
d D 1.13 00/08/02 18:04:59 staelin 14 13
c - Rewrite to use benchmp() timing harness
cC
cHhpli8.hpli.hpl.hp.com
cK10120
cZ+03:00
e
s 00001/00001/00070
d D 1.12 97/10/31 18:06:23 lm 13 12
c use_result -> use_int/pointer
cC
cK61244
cZ-08:00
e
s 00001/00001/00070
d D 1.11 97/06/15 22:38:58 lm 12 11
c lint
cK61584
e
s 00001/00002/00070
d D 1.10 97/06/13 20:24:14 lm 11 10
c typo - sgi's cc caught it.
cK61354
e
s 00017/00021/00055
d D 1.9 97/06/12 21:30:06 lm 10 9
c new bench.h macros.
cK61956
cZ-07:00
e
s 00008/00008/00068
d D 1.8 96/11/11 03:36:51 lm 9 8
c Auto adjusting changes.
cK00301
e
s 00007/00004/00069
d D 1.7 96/11/08 20:00:16 lm 8 7
c gcc -Wall cleanup.
cK00115
cZ-08:00
e
s 00000/00001/00073
d D 1.6 96/05/30 00:33:07 lm 7 6
c no what strings
cK59305
cZ-07:00
e
s 00002/00004/00072
d D 1.5 95/11/07 17:39:50 lm 6 5
c *** empty log message ***
cK61376
e
s 00000/00002/00076
d D 1.4 95/03/10 18:26:03 lm 5 4
c lint.
cK64277
e
s 00004/00000/00074
d D 1.3 94/11/29 11:52:20 lm 4 3
c changes from Alain Durand for NetBSD
cK00220
e
s 00003/00003/00071
d D 1.2 94/11/23 17:59:11 lm 3 2
c change to 256K.
cK60736
e
s 00074/00000/00000
d D 1.1 94/11/18 00:49:48 lm 2 1
c Initial revision
cK60570
e
s 00000/00000/00000
d D 1.0 94/11/18 00:49:47 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK33722
cPsrc/lat_pagefault.c
cR21040cf28d60fb56
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
 * lat_pagefault.c - time a page fault in
 *
D 14
 * Usage: lat_pagefault file [file file...]
E 14
I 14
 * Usage: lat_pagefault [-W <warmup>] [-N <repetitions>] file 
E 14
 *
I 14
 * Copyright (c) 2000 Carl Staelin.
E 14
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
char	*id = "$Id$\n";

D 9
#include "timing.c"

E 9
I 9
D 10
#include "timing.h"
E 10
#include "bench.h"
E 9
D 10
#include <sys/stat.h>
#include <sys/mman.h>
I 8
#include <fcntl.h>
E 10
E 8

#define	CHK(x)	if ((x) == -1) { perror("x"); exit(1); }

D 8
main(ac, av)
	char **av;
E 8
I 8
D 14
void	timeit(char *file, char *where, int size);
E 14
I 14
typedef struct _state {
	int fd;
	int size;
	int npages;
D 16
	int page;
E 16
I 15
	int clone;
E 15
	char* file;
	char* where;
D 16
	char** pages;
E 16
I 16
	int* pages;
E 16
} state_t;

void	initialize(void *cookie);
void	cleanup(void *cookie);
void	benchmark(iter_t iterations, void * cookie);
I 16
void	benchmark_mmap(iter_t iterations, void * cookie);
E 16
E 14

int
main(int ac, char **av)
E 8
{
I 6
D 16
#ifdef	MS_INVALIDATE
E 16
E 6
D 14
	int fd;
D 11
	int i;
E 11
	char *where;
D 5
	int *p;
	int size;
E 5
	struct stat sbuf;
E 14
I 14
	int parallel = 1;
	int warmup = 0;
	int repetitions = TRIES;
	int c;
I 16
	double t_mmap;
	double t_combined;
	struct stat   st;
E 16
	struct _state state;
	char buf[2048];
	char* usage = "[-W <warmup>] [-N <repetitions>] file\n";

D 15
	while (( c = getopt(ac, av, "W:N:")) != EOF) {
E 15
I 15
	state.clone = 0;

	while (( c = getopt(ac, av, "P:W:N:C")) != EOF) {
E 15
		switch(c) {
		case 'P':
D 15
			/*
			 * don't allow this for now.  Not sure how to
			 * manage parallel processes to ensure that they
			 * each have to pagefault on each page access
			 */
E 15
			parallel = atoi(optarg);
			if (parallel <= 0) lmbench_usage(ac, av, usage);
			break;
		case 'W':
			warmup = atoi(optarg);
			break;
		case 'N':
			repetitions = atoi(optarg);
			break;
I 15
		case 'C':
			state.clone = 1;
			break;
E 15
		default:
			lmbench_usage(ac, av, usage);
			break;
		}
	}
	if (optind != ac - 1 ) {
		lmbench_usage(ac, av, usage);
	}
	
	state.file = av[optind];
I 16
	CHK(stat(state.file, &st));
	state.npages = st.st_size / (size_t)getpagesize();

#ifdef	MS_INVALIDATE
	benchmp(initialize, benchmark_mmap, cleanup, 0, parallel, 
		warmup, repetitions, &state);
	t_mmap = gettime() / (double)get_n();

E 16
	benchmp(initialize, benchmark, cleanup, 0, parallel, 
		warmup, repetitions, &state);
I 16
	t_combined = gettime() / (double)get_n();
	settime(get_n() * (t_combined - t_mmap));

E 16
	sprintf(buf, "Pagefaults on %s", state.file);
D 16
	micro(buf, get_n());
E 16
I 16
	micro(buf, state.npages * get_n());
E 16
#endif
I 16
	return(0);
E 16
}
E 14

D 7
	write(2, id, strlen(id));
E 7
D 10
	if (ac < 2) {
		fprintf(stderr, "usage: %s file [file...]\n", av[0]);
E 10
I 10
D 14
	if (ac != 2) {
		fprintf(stderr, "usage: %s file\n", av[0]);
E 14
I 14
void
initialize(void* cookie)
{
	int 		i, npages, pagesize;
I 16
	int		*p;
E 16
	unsigned int	r;
D 16
	char		*p;
E 16
	struct stat 	sbuf;
	state_t 	*state = (state_t *) cookie;

I 15
	if (state->clone) {
		char buf[128];
		char* s;

		/* copy original file into a process-specific one */
		sprintf(buf, "%d", (int)getpid());
		s = (char*)malloc(strlen(state->file) + strlen(buf) + 1);
		sprintf(s, "%s%d", state->file, (int)getpid());
		if (cp(state->file, s, S_IREAD|S_IWRITE) < 0) {
			perror("Could not copy file");
			unlink(s);
			exit(1);
		}
		state->file = s;
	}
E 15
	CHK(state->fd = open(state->file, 0));
I 15
	if (state->clone) unlink(state->file);
E 15
	CHK(fstat(state->fd, &sbuf));

	srand(getpid());
	pagesize = getpagesize();
	state->size = sbuf.st_size;
	state->size -= state->size % pagesize;
	state->npages = state->size / pagesize;
D 16
	state->pages = (char**)malloc(state->npages * sizeof(char*));
	state->page = 0;
E 16
I 16
	state->pages = permutation(state->npages, pagesize);
E 16

	if (state->size < 1024*1024) {
		fprintf(stderr, "lat_pagefault: %s too small\n", state->file);
E 14
E 10
		exit(1);
	}
D 10
	for (i = 1; i < ac; ++i) {
		CHK(fd = open(av[i], 0));
		CHK(fstat(fd, &sbuf));
		sbuf.st_size &= ~(16*1024 - 1);		/* align it */
D 3
		if (sbuf.st_size < 100*1024) {
E 3
I 3
		if (sbuf.st_size < 1024*1024) {
E 3
			fprintf(stderr, "%s: %s too small\n", av[0], av[i]);
			continue;
		}
		where = mmap(0, sbuf.st_size, PROT_READ, MAP_SHARED, fd, 0);
I 4
D 6
#ifdef	BSD
		if (msync(where, sbuf.st_size) != 0) {
#else
E 6
E 4
		if (msync(where, sbuf.st_size, MS_INVALIDATE) != 0) {
I 4
D 6
#endif
E 6
E 4
			perror("msync");
			exit(1);
		}
		timeit(av[i], where, sbuf.st_size);
		munmap(where, sbuf.st_size);
E 10
I 10
D 14
	CHK(fd = open(av[1], 0));
	CHK(fstat(fd, &sbuf));
	sbuf.st_size &= ~(16*1024 - 1);		/* align it */
	if (sbuf.st_size < 1024*1024) {
		fprintf(stderr, "%s: %s too small\n", av[0], av[2]);
		exit(1);
E 14
I 14
D 16
	state->where = mmap(0, state->size, PROT_READ, MAP_SHARED, state->fd, 0);

	/* first, layout the sequence of page accesses */
	p = state->where;
	for (i = 0; i < state->npages; ++i) {
		state->pages[i] = (char*)p;
		p += pagesize;
E 14
E 10
	}
I 10
D 14
	where = mmap(0, sbuf.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (msync(where, sbuf.st_size, MS_INVALIDATE) != 0) {
E 14
I 14

	/* randomize the page sequences */
	r = (rand() << 15) ^ rand();
	for (i = state->npages - 1; i > 0; --i) {
		char *l;
		r = (r << 1) ^ (rand() >> 4);
		l = state->pages[r % i];
		state->pages[r % i] = state->pages[i];
		state->pages[i] = l;
	}
E 16
I 16
	state->where = mmap(0, state->size, 
			    PROT_READ, MAP_SHARED, state->fd, 0);
E 16

#ifdef	MS_INVALIDATE
	if (msync(state->where, state->size, MS_INVALIDATE) != 0) {
E 14
		perror("msync");
		exit(1);
	}
D 11
	timeit(av[i], where, sbuf.st_size);
E 11
I 11
D 14
	timeit(av[1], where, sbuf.st_size);
E 11
	munmap(where, sbuf.st_size);
E 14
E 10
I 6
#endif
E 6
D 12
	exit(0);
E 12
I 12
D 14
	return(0);
E 14
E 12
}

D 14
/*
D 3
 * Get page fault times by going backwards in a stride of 32K
E 3
I 3
 * Get page fault times by going backwards in a stride of 256K
I 10
 * We don't want to do this in a loop, it needs a hi res clock.
 * XXX - hires.
E 10
E 3
 */
E 14
D 8
timeit(file, where, size)
	char	*file, *where;
E 8
I 8
void
D 14
timeit(char *file, char *where, int size)
E 14
I 14
cleanup(void* cookie)
{	
	state_t *state = (state_t *) cookie;

	munmap(state->where, state->size);
I 15
	if (state->fd >= 0) close(state->fd);
E 15
	free(state->pages);
}

void
benchmark(iter_t iterations, void* cookie)
E 14
E 8
{
I 16
	int	i;
E 16
D 14
	char	*end = where + size - 16*1024;
E 14
	int	sum = 0;
D 9
	int	lowest = 0x7fffffff;
E 9
I 9
D 14
	int	n = 0, usecs = 0;
E 14
I 14
	state_t *state = (state_t *) cookie;
E 14
E 9

D 14
	while (end > where) {
D 9
		start();
E 9
I 9
		start(0);
E 9
		sum += *end;
D 3
		end -= 32*1024;
E 3
I 3
		end -= 256*1024;
E 3
D 9
		sum = stop(sum);
		if (sum < lowest)
			lowest = sum;
E 9
I 9
		usecs += stop(0,0);
		n++;
E 14
I 14
	while (iterations-- > 0) {
D 16
		sum += *(state->pages[state->page++]);
		if (state->page >= state->npages) {
			state->page = 0;
E 16
I 16
		for (i = 0; i < state->npages; ++i) {
			sum += *(state->where + state->pages[i]);
		}
		munmap(state->where, state->size);
		state->where = mmap(0, state->size, 
				    PROT_READ, MAP_SHARED, state->fd, 0);
E 16
#ifdef	MS_INVALIDATE
D 16
			if (msync(state->where, state->size, MS_INVALIDATE) != 0) {
				perror("msync");
				exit(1);
			}
E 16
I 16
		if (msync(state->where, state->size, MS_INVALIDATE) != 0) {
			perror("msync");
			exit(1);
		}
E 16
#endif
I 16
	}
	use_int(sum);
}

void
benchmark_mmap(iter_t iterations, void* cookie)
{
	int	i;
	int	sum = 0;
	state_t *state = (state_t *) cookie;

	while (iterations-- > 0) {
		munmap(state->where, state->size);
		state->where = mmap(0, state->size, 
				    PROT_READ, MAP_SHARED, state->fd, 0);
#ifdef	MS_INVALIDATE
		if (msync(state->where, state->size, MS_INVALIDATE) != 0) {
			perror("msync");
			exit(1);
E 16
		}
I 16
#endif
E 16
E 14
E 9
	}
D 9
	fprintf(stderr, "Pagefaults on %s: %d usecs\n", file, lowest);
E 9
I 9
D 13
	use_result(sum);
E 13
I 13
	use_int(sum);
E 13
D 14
	fprintf(stderr, "Pagefaults on %s: %d usecs\n", file, usecs/n);
E 14
E 9
}
I 14

E 14
E 2
I 1
E 1
