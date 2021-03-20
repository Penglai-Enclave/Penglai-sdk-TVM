H51704
s 00002/00002/00164
d D 1.19 02/09/29 21:53:51 staelin 20 19
c - switch from 'int' to 'size_t' for better portability to large memory 
c   machines
cC
cHfirewall.staelin.co.il
cK18321
cZ+03:00
e
s 00027/00006/00139
d D 1.18 01/11/13 16:36:33 staelin 19 18
c Add ability for child processes in file-related benchmarks to each
c have their own file, as it sometimes makes a difference whether you
c measure N processes beating on a single file or on N independent
c files.
cC
cHhpli69.hpli.hpl.hp.com
cK17675
e
s 00004/00001/00141
d D 1.17 00/10/31 10:00:42 staelin 18 17
c - Only print any output if benchmark produces a valid result
c   (needed for mb() and micromb()-style outputs where prefix is
c   printed by main() and only the result is printed by the output
c   routine, and only then if the result is valid)
c - Add SOCKOPT_REUSE to tcp_server() call
cC
cK49705
cZ+02:00
e
s 00002/00002/00140
d D 1.16 00/07/30 11:46:09 staelin 17 16
c - Change type of "iterations" from uint64 to iter_t, which is a u_long
cC
cK48042
e
s 00013/00005/00129
d D 1.15 00/07/04 14:55:54 staelin 16 15
c - Update to incorporate new "-W <warmup>" and "-N <repetitions>" flags
cC
cK47856
e
s 00004/00002/00130
d D 1.14 00/05/31 16:16:17 staelin 15 14
c Remove unnecessary print statement that was confusing lmbench's result parsing scripts
cC
cK27462
cZ+03:00
e
s 00001/00001/00131
d D 1.13 00/04/17 13:06:02 staelin 14 13
c - convert 'char c' to 'int c' for getopt()
cC
cHhpli8.hpli.hpl.hp.com
cK27961
cZ+02:00
e
s 00094/00046/00038
d D 1.12 00/03/16 18:07:48 brucec 13 12
c Make changes for parallel runs ("-P <parallelism>").  
c 
cC
cHrx7
cK28044
cZ-05:00
e
s 00001/00001/00083
d D 1.11 97/06/15 22:38:58 lm 12 11
c lint
cC
cK10049
e
s 00028/00027/00056
d D 1.10 97/06/13 20:39:50 lm 11 10
c lint
cK09819
e
s 00045/00021/00038
d D 1.9 97/06/12 21:30:06 lm 10 9
c new bench.h macros.
cK09375
cZ-07:00
e
s 00001/00001/00058
d D 1.8 96/11/13 16:09:37 lm 9 8
c timing.c interfaces.
cK47751
e
s 00014/00020/00045
d D 1.7 96/11/11 03:36:51 lm 8 7
c Auto adjusting changes.
cK50131
e
s 00004/00015/00061
d D 1.6 96/11/08 20:00:09 lm 7 6
c gcc -Wall cleanup & new timing.c integration.
cK51089
cZ-08:00
e
s 00000/00001/00076
d D 1.5 96/05/30 00:33:07 lm 6 5
c no what strings
cK61854
e
s 00004/00000/00073
d D 1.4 95/10/25 18:03:42 lm 5 4
c MAP_FILE for FreeBSD.
cK63925
cZ-07:00
e
s 00000/00001/00073
d D 1.3 95/03/10 18:22:37 lm 4 3
c lint
cK57154
e
s 00001/00001/00073
d D 1.2 95/02/14 12:34:34 lm 3 2
c linux wants readonly fd's for mmap MAP_READ.
cK57749
e
s 00074/00000/00000
d D 1.1 94/11/18 00:49:48 lm 2 1
c Initial revision
cK57751
e
s 00000/00000/00000
d D 1.0 94/11/18 00:49:47 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK19537
cPsrc/lat_mmap.c
cRe3044628e9a37e7
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
 * lat_mmap.c - time how fast a mapping can be made and broken down
 *
D 16
 * Usage: mmap size file
E 16
I 16
 * Usage: mmap [-P <parallelism>] [-W <warmup>] [-N <repetitions>] size file
E 16
 *
 * XXX - If an implementation did lazy address space mapping, this test
 * will make that system look very good.  I haven't heard of such a system.
 *
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
char	*id = "$Id$\n";

D 8
#include "timing.c"

E 8
I 8
D 10
#include "timing.h"
E 10
#include "bench.h"
E 8
D 10
#include <sys/stat.h>
#include <sys/mman.h>
I 7
#include <fcntl.h>
E 10
E 7

I 10
#define	PSIZE	(16<<10)
#define	N	10
#define	STRIDE	(10*PSIZE)
#define	MINSIZE	(STRIDE*2)

E 10
#define	CHK(x)	if ((x) == -1) { perror("x"); exit(1); }
D 8
#ifndef	N
#define	N	5000
#endif
E 8

I 13

typedef struct _state {
D 20
	int	size;
E 20
I 20
	size_t	size;
E 20
	int	fd;
	int	random;
I 19
	int	clone;
E 19
	char	*name;
D 19
	char	myname[256];
E 19
} state_t;

void	init(void *cookie);
void	cleanup(void *cookie);
D 17
void	domapping(uint64 iterations, void * cookie);
E 17
I 17
void	domapping(iter_t iterations, void * cookie);
E 17

int main(int ac, char **av)
{
	state_t state;
	int	parallel = 1;
I 16
	int	warmup = 0;
	int	repetitions = TRIES;
E 16
	char	buf[256];
D 14
	char	c;
E 14
I 14
	int	c;
E 14
D 16
	char	*usage = "[-r] [-P <parallelism>] size file\n";
E 16
I 16
	char	*usage = "[-r] [-P <parallelism>] [-W <warmup>] [-N <repetitions>] size file\n";
E 16
	

	state.random = 0;
D 16
	while (( c = getopt(ac, av, "rP:")) != EOF) {
E 16
I 16
D 19
	while (( c = getopt(ac, av, "rP:W:N:")) != EOF) {
E 19
I 19
	state.clone = 0;
	while (( c = getopt(ac, av, "rP:W:N:C")) != EOF) {
E 19
E 16
		switch(c) {
		case 'P':
			parallel = atoi(optarg);
			if (parallel <= 0)
				lmbench_usage(ac, av, usage);
			break;
I 16
		case 'W':
			warmup = atoi(optarg);
			break;
		case 'N':
			repetitions = atoi(optarg);
			break;
E 16
		case 'r':
			state.random = 1;
			break;
I 19
		case 'C':
			state.clone = 1;
			break;
E 19
		default:
			lmbench_usage(ac, av, usage);
			break;
		}
	}

	if (optind + 2 != ac) {
		lmbench_usage(ac, av, usage);
	}

	state.size = bytes(av[optind]);
D 15
	if (state.size < MINSIZE)	
		lmbench_usage(ac, av, usage);
E 15
I 15
	if (state.size < MINSIZE) {
		return (1);
	}
E 15
	state.name = av[optind+1];

D 16
	benchmp(init, domapping, cleanup,
		0, parallel, &state);
E 16
I 16
	benchmp(init, domapping, cleanup, 0, parallel, 
		warmup, repetitions, &state);
E 16
D 18
	micromb(state.size, get_n());
E 18
I 18

	if (gettime() > 0) {
		micromb(state.size, get_n());
	}
E 18
I 15
	return (0);
E 15
}

void init(void * cookie)
{
	state_t *state = (state_t *) cookie;
	
D 19
	sprintf(state->myname,"%s.%d",state->name,getpid());
	CHK(state->fd = open(state->myname, O_CREAT|O_RDWR, 0666));
	CHK(ftruncate(state->fd, state->size));
E 19
I 19
	if (state->clone) {
		char buf[128];
		char* s;

		/* copy original file into a process-specific one */
		sprintf(buf, "%d", (int)getpid());
		s = (char*)malloc(strlen(state->name) + strlen(buf) + 1);
		sprintf(s, "%s%d", state->name, (int)getpid());
		if (cp(state->name, s, S_IREAD|S_IWRITE) < 0) {
			perror("Could not copy file");
			unlink(s);
			exit(1);
		}
		state->name = s;
	}
	CHK(state->fd = open(state->name, O_RDWR));
	if (lseek(state->fd, 0, SEEK_END) < state->size) {
		fprintf(stderr, "Input file too small\n");
		exit(1);
	}
E 19
}

void cleanup(void * cookie)
{
	state_t *state = (state_t *) cookie;
	close(state->fd);
D 19
	unlink(state->myname);
E 19
I 19
	if (state->clone) unlink(state->name);
E 19
}

E 13
D 7
main(ac, av)
	char **av;
E 7
I 7
D 11
int
main(int ac, char **av)
E 7
{
D 8
	int fd;
	int i;
	char *where;
D 4
	int *p;
E 4
	int size;
	struct stat sbuf;
E 8
I 8
D 10
	int	fd, i, N;
	char	*where;
E 10
I 10
	int	fd;
E 10
	int	size;
D 10
	struct	stat sbuf;
E 10
I 10
	int	random = 0;
	char	*prog = av[0];
E 10
E 8

D 6
	write(2, id, strlen(id));
E 6
D 10
	if (ac != 3) {
		fprintf(stderr, "usage: %s size file\n", av[0]);
E 10
I 10
	if (ac != 3 && ac != 4) {
		fprintf(stderr, "usage: %s [-r] size file\n", prog);
E 10
		exit(1);
	}
I 10
	if (strcmp("-r", av[1]) == 0) {
		random = 1;
		ac--, av++;
	}
E 10
D 7
	size = atoi(av[1]);
	if ((last(av[1]) == 'k') || (last(av[1]) == 'K'))
		size *= 1024;
	if ((last(av[1]) == 'm') || (last(av[1]) == 'M'))
		size *= (1024 * 1024);
E 7
I 7
	size = bytes(av[1]);
E 7
D 3
	CHK(fd = open(av[2], 2));
E 3
I 3
D 10
	CHK(fd = open(av[2], 0));
E 3
	CHK(fstat(fd, &sbuf));
	if (sbuf.st_size < size) {
		fprintf(stderr, "%s: file %s is not as big as size %d\n",
		    av[0], av[2], size);
		exit(1);
E 10
I 10
	if (size < MINSIZE) {	
		return (1);
E 10
	}
D 8
	start();
	for (i = 0; i < N; ++i) {
E 8
I 8
D 10
	LOOP_FIRST(N, i, ENOUGH);
E 10
I 10
	CHK(fd = open(av[2], O_CREAT|O_RDWR, 0666));
	CHK(ftruncate(fd, size));
	BENCH(mapit(fd, size, random), 0);
	micromb(size, get_n());
	exit(0);
}

E 11
/*
 * This alg due to Linus.  The goal is to have both sparse and full
 * mappings reported.
 */
I 11
D 13
void
E 11
mapit(int fd, int size, int random)
E 13
I 13
D 17
void domapping(uint64 iterations, void *cookie)
E 17
I 17
void domapping(iter_t iterations, void *cookie)
E 17
E 13
{
D 13
	char	*p, *where, *end;
	char	c = size & 0xff;
E 13
I 13
	state_t *state = (state_t *) cookie;
	register int fd = state->fd;
D 20
	register int size = state->size;
E 20
I 20
	register size_t size = state->size;
E 20
	register int random = state->random;
	register char	*p, *where, *end;
	register char	c = size & 0xff;

	while (iterations-- > 0) {
E 13

E 10
E 8
I 5
#ifdef	MAP_FILE
D 8
		where = mmap(0, size, PROT_READ, MAP_FILE|MAP_SHARED, fd, 0);
E 8
I 8
D 10
	where = mmap(0, size, PROT_READ, MAP_FILE|MAP_SHARED, fd, 0);
E 10
I 10
D 13
	where = mmap(0, size, PROT_READ|PROT_WRITE, MAP_FILE|MAP_SHARED, fd, 0);
E 13
I 13
		where = mmap(0, size, PROT_READ|PROT_WRITE, MAP_FILE|MAP_SHARED, fd, 0);
E 13
E 10
E 8
#else
E 5
D 8
		where = mmap(0, size, PROT_READ, MAP_SHARED, fd, 0);
E 8
I 8
D 10
	where = mmap(0, size, PROT_READ, MAP_SHARED, fd, 0);
E 10
I 10
D 13
	where = mmap(0, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
E 13
I 13
		where = mmap(0, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
E 13
E 10
E 8
I 5
#endif
E 5
D 8
		if ((int)where == -1) {
			perror("mmap");
			exit(1);
		}
		munmap(where, size);
E 8
I 8
D 13
	if ((int)where == -1) {
		perror("mmap");
		exit(1);
E 8
	}
I 10
	if (random) {
		end = where + size;
		for (p = where; p < end; p += STRIDE) {
			*p = c;
E 13
I 13
		if ((int)where == -1) {
			perror("mmap");
			exit(1);
E 13
		}
D 13
	} else {
		end = where + (size / N);
		for (p = where; p < end; p += PSIZE) {
			*p = c;
E 13
I 13
		if (random) {
			end = where + size;
			for (p = where; p < end; p += STRIDE) {
				*p = c;
			}
		} else {
			end = where + (size / N);
			for (p = where; p < end; p += PSIZE) {
				*p = c;
			}
E 13
		}
I 13
		munmap(where, size);
E 13
	}
E 10
D 8
	i = stop();
E 8
I 8
D 13
	munmap(where, size);
D 10
	LOOP_LAST(N, i, ENOUGH);
E 8
D 9
	fprintf(stderr, "%.02f %d\n", size/(1024*1024.), i / N);
E 9
I 9
	micromb(size, N);
E 9
	exit(0);
E 10
}
I 11

int
main(int ac, char **av)
{
	int	fd;
	int	size;
	int	random = 0;
	char	*prog = av[0];

	if (ac != 3 && ac != 4) {
		fprintf(stderr, "usage: %s [-r] size file\n", prog);
		exit(1);
	}
	if (strcmp("-r", av[1]) == 0) {
		random = 1;
		ac--, av++;
	}
	size = bytes(av[1]);
	if (size < MINSIZE) {	
		return (1);
	}
	CHK(fd = open(av[2], O_CREAT|O_RDWR, 0666));
	CHK(ftruncate(fd, size));
	BENCH(mapit(fd, size, random), 0);
	micromb(size, get_n());
D 12
	exit(0);
E 12
I 12
	return(0);
E 13
E 12
}
E 11
D 7

last(s)
	char	*s;
{
	while (*s++)
		;
	return (s[-2]);
}
E 7
E 2
I 1
E 1
