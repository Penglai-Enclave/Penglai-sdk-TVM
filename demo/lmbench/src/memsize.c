/*
 * memsize.c - figure out how much memory we have to use.
 *
 * Usage: memsize [max_wanted_in_MB]
 *
 * Copyright (c) 1995 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 */
char	*id = "$Id$\n";

#include "bench.h"

#define	CHK(x)	if ((x) == -1) { perror("x"); exit(1); }

#ifndef	TOO_LONG
#define	TOO_LONG	10	/* usecs */
#endif

void	timeit(char *where, size_t size);
static	void touchRange(char *p, size_t range, ssize_t stride);


int
main(int ac, char **av)
{
	char	*where;
	char	*tmp;
	size_t	size;
	size_t	max;

	if (ac == 2) {
		unsigned long t;
		sscanf(av[1], "%lu", &t);
		max = size = t * 1024 * 1024;
	} else {
		max = size = 1024 * 1024 * 1024;
	}
	/*
	 * Binary search down and then linear search up
	 */
	for (where = 0; !where; where = malloc(size)) {
		size >>= 1;
	}
	while (size < max) {
		free(where);
		size += 1024*1024;
		where = malloc(size);
		if (!where) {
			size -= 1024*1024;
			where = malloc(size);
			if (!where) {
				perror("malloc");
				exit(1);
			}
			break;
		}
	} 
	if (where) {
		timeit(where, size);
		free(where);
	}
	exit (0);
}

void
timeit(char *where, size_t size)
{
	int	sum = 0;
	size_t	n;
	char	*end = where + size;
	size_t	range;
	size_t	incr = 1024 * 1024;
	ssize_t	stride;
	size_t	pagesize = getpagesize();

	if (size < 1024*1024 - 16*1024) {
		fprintf(stderr, "Bad size\n");
		return;
	}

	range = 1024 * 1024;
	incr = 1024 * 1024;
	touchRange(where, range, pagesize);
	for (range += incr; range <= size; range += incr) {
		touchRange(where + range - incr, incr, pagesize);
		start(0);
		/* 
		 * reverse page order to minimize the number
		 * of pages swapped to disk.  We really
		 * want only to find when swapping starts.
		 * Particularly for large memory systems,
		 * we don't want to "fall off a cliff" and
		 * suddenly have to wait to swap everything
		 * when we start swapping.
		 */
		touchRange(where, range, -pagesize);
		sum = stop(0, 0);
		n = range / pagesize;
		if ((sum / n) > TOO_LONG) {
			fprintf(stderr, "\n");
			printf("%d\n", (range - incr)>>20);
			return;
		}
		if (range < 20 * 1024 * 1024) 
			incr = 1024 * 1024;
		else if (range < 50 * 1024 * 1024)
			incr = 2 * 1024 * 1024;
		else if (range < 200 * 1024 * 1024)
			incr = 10 * 1024 * 1024;
		else    incr = 20 * 1024 * 1024;
		if (range < size && size < range + incr) {
			incr = size - range;
		}
		fprintf(stderr, "%dMB OK\r", range/(1024*1024));
	}
	fprintf(stderr, "\n");
	printf("%d\n", (size>>20));
}

static void
touchRange(char *p, size_t range, ssize_t stride)
{
	int i = 0;
	register char	*tmp = p + (stride > 0 ? 0 : range - 1);
	register size_t delta = (stride > 0 ? stride : -stride);

	while (range > delta - 1) {
		*tmp = 0;
		tmp += stride;
		range -= delta;
		i++;
	}
}

#undef	malloc
#undef	free

char	*
Malloc(int n)
{
	char	*p = malloc(n);

	fprintf(stderr, "malloc(%d) = %x\n", n, p);
	return (p);
}

Free(char *p)
{
	fprintf(stderr, "free(%x)\n", p);
	free(p);
}
