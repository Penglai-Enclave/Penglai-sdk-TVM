h36973
s 00001/00001/00174
d D 1.18 00/10/16 17:21:25 staelin 19 18
c - Assorted code cleanups
cC
cK32278
cZ+02:00
e
s 00007/00007/00168
d D 1.17 00/07/30 11:46:14 staelin 18 17
c - Change type of "iterations" from uint64 to iter_t, which is a u_long
cC
cK31608
e
s 00001/00001/00174
d D 1.16 00/07/25 13:48:38 staelin 17 16
c - fix printout of 'lat_syscall read' when /dev/zero cannot be opened
cC
cK32112
e
s 00001/00001/00174
d D 1.15 00/07/06 15:49:11 staelin 16 15
c - Fix output bug; missing newline at end of error output
cC
cK32791
e
s 00022/00008/00153
d D 1.14 00/07/04 14:55:58 staelin 15 14
c - Update to incorporate new "-W <warmup>" and "-N <repetitions>" flags
cC
cK32589
cZ+03:00
e
s 00039/00020/00122
d D 1.13 00/03/01 17:23:38 staelin 14 13
c - Convert to the new getopt argument processing
cC
cK06367
e
s 00069/00038/00073
d D 1.12 00/02/23 11:15:39 staelin 13 12
c Convert to use new draft benchmp() timing harness.
cC
cHhpli8.hpli.hpl.hp.com
cK40529
cZ+02:00
e
s 00001/00001/00110
d D 1.11 97/06/15 22:38:58 lm 12 11
c lint
cC
cK11950
cSAlpha2.11
e
s 00002/00002/00109
d D 1.10 97/06/14 12:19:26 lm 11 10
c FILE -> FNAME
cK11720
e
s 00035/00064/00076
d D 1.9 97/06/12 21:30:06 lm 10 9
c new bench.h macros.
cK11578
e
s 00001/00001/00139
d D 1.8 97/05/27 16:02:31 lm 9 8
c typo
cK44691
e
s 00083/00017/00057
d D 1.7 97/04/23 22:02:15 lm 8 7
c make it work with the new bench.h timing loop.
c New usage is: Usage: %s null|read|write|stat|open [filename]
cK44589
cZ-07:00
e
s 00005/00004/00069
d D 1.6 96/11/13 16:09:37 lm 7 6
c comments
cK42938
e
s 00040/00050/00033
d D 1.5 96/11/11 03:36:51 lm 6 5
c Auto adjusting changes.
cK47678
e
s 00063/00012/00020
d D 1.4 96/11/08 20:05:40 lm 5 4
c gcc -Wall cleanup.
c Change it to null call, null write, null read, null stat.
cK41846
cZ-08:00
e
s 00001/00002/00031
d D 1.3 96/05/30 00:33:07 lm 4 3
c no what strings
cK53094
e
s 00001/00001/00032
d D 1.2 95/09/23 18:32:37 lm 3 2
c Getting too short of a time.
cK55275
cZ-07:00
e
s 00033/00000/00000
d D 1.1 94/11/18 00:49:48 lm 2 1
c Initial revision
cK55231
e
s 00000/00000/00000
d D 1.0 94/11/18 00:49:47 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK13682
cPsrc/lat_syscall.c
cR92127cb9fcc9c374
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
D 7
 * lat_syscall.c - time simple entry into the system
E 7
I 7
 * lat_syscall.c - time simple system calls
E 7
 *
D 7
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
E 7
I 7
 * Copyright (c) 1996 Larry McVoy.  Distributed under the FSF GPL with
E 7
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
D 7
 * Support for this development by Sun Microsystems is gratefully acknowledged.
E 7
 */
D 13
char	*id = "$Id$\n";
E 13
I 13
char	*id = "$Id: s.lat_syscall.c 1.11 97/06/15 22:38:58-07:00 lm $\n";
E 13

D 5
#include "timing.c"
D 3
#define	N	50000
E 3
I 3
#define	N	100000
E 5
I 5
D 6
#include	"timing.c"
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>
E 6
I 6
D 10
#include "timing.h"
E 10
#include "bench.h"
I 7
D 10
#include <sys/time.h>
E 7
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
I 7
#include <unistd.h>
E 10
I 8
D 11
#define	FILE "/usr/include/sys/types.h"
E 11
I 11
#define	FNAME "/usr/include/sys/types.h"
E 11
E 8
E 7
E 6
E 5
E 3

I 13
struct _state {
	int fd;
	char* file;
};

void
D 18
do_getppid(uint64 iterations, void *cookie)
E 18
I 18
do_getppid(iter_t iterations, void *cookie)
E 18
{
	struct _state *pState = (struct _state*)cookie;
	char	c;

D 14
	for (; iterations > 0; --iterations) {
E 14
I 14
	while (iterations-- > 0) {
E 14
		getppid();
	}
}

E 13
I 5
D 8
int
E 5
main(ac, av)
	char  **av;
E 8
I 8
void
D 10
do_getppid()
E 10
I 10
D 13
do_write(int fd)
E 13
I 13
D 18
do_write(uint64 iterations, void *cookie)
E 18
I 18
do_write(iter_t iterations, void *cookie)
E 18
E 13
E 10
E 8
{
I 13
	struct _state *pState = (struct _state*)cookie;
E 13
D 5
	int	fd = open("/dev/null", 1);
	int	i;
E 5
D 8
	char	c;
I 5
	int	i, N, fd;
	struct	stat sbuf;
E 5
D 7

E 7
I 7
	
E 8
I 8
D 10
	int	i, N;

E 8
E 7
D 4
	write(2, id, strlen(id));
E 4
D 5
	start();
	for (i = 0; i < N; ++i) {
		if (write(fd, &c, 1) != 1) {
			perror("/dev/null");
			exit(1);
E 5
I 5
D 6
	N = 1<<10;
	do {
		N <<= 2;
		start();
		for (i = 0; i < N; ++i) {
			getppid();
E 5
		}
D 5
	}
	stop();
E 5
I 5
	} while (stop() < ENOUGH);
E 5
D 4
	micro("Null syscall", N);
E 4
I 4
	nano("Null syscall", N);
E 6
I 6
	LOOP_FIRST(N, i, ENOUGH);
	getppid();
	LOOP_LAST(N, i, ENOUGH);
	micro("Simple syscall", N);
I 8
}
E 8
E 6
E 4
D 5
	exit(0);
E 5
I 5

I 8
void
do_write()
{
E 10
	char	c;
D 10
	int	i, N, fd;
E 10

E 8
D 10
	fd = open("/dev/null", 1);
D 6
	N = 1<<10;
	do {
		N <<= 2;
		start();
		for (i = 0; i < N; ++i) {
			if (write(fd, &c, 1) != 1) {
				perror("/dev/null");
				return(1);
			}
		}
	} while (stop() < ENOUGH);
	nano("Null write", N);

E 6
I 6
	LOOP_FIRST(N, i, ENOUGH);
E 10
D 13
	if (write(fd, &c, 1) != 1) {
		perror("/dev/null");
D 8
		return(1);
E 8
I 8
		return;
E 13
I 13
D 14
	for (; iterations > 0; --iterations) {
E 14
I 14
	while (iterations-- > 0) {
E 14
		if (write(pState->fd, &c, 1) != 1) {
			perror("/dev/null");
			return;
		}
E 13
E 8
	}
D 10
	LOOP_LAST(N, i, ENOUGH);
	micro("Simple write", N);
E 6
	close(fd);
E 10
I 8
}
E 8
I 6

I 8
void
D 10
do_read()
E 10
I 10
D 13
do_read(int fd)
E 13
I 13
D 18
do_read(uint64 iterations, void *cookie)
E 18
I 18
do_read(iter_t iterations, void *cookie)
E 18
E 13
E 10
{
I 13
	struct _state *pState = (struct _state*)cookie;
E 13
	char	c;
D 10
	int	i, N, fd;
E 10

E 8
E 6
D 10
	fd = open("/dev/zero", 0);
D 6
	N = 1<<10;
E 6
	if (fd == -1) {
		fprintf(stderr, "Read from /dev/zero: -1");
D 8
		return(0);
E 8
I 8
		return;
E 8
	}
D 6
	do {
		N <<= 2;
		start();
		for (i = 0; i < N; ++i) {
			if (read(fd, &c, 1) != 1) {
				perror("/dev/zero");
				exit(1);
			}
		}
	} while (stop() < ENOUGH);
	nano("Null read", N);
E 6
I 6
	LOOP_FIRST(N, i, ENOUGH);
E 10
D 13
	if (read(fd, &c, 1) != 1) {
		perror("/dev/zero");
D 8
		exit(1);
E 8
I 8
		return;
E 13
I 13
D 14
	for (; iterations > 0; --iterations) {
E 14
I 14
	while (iterations-- > 0) {
E 14
		if (read(pState->fd, &c, 1) != 1) {
			perror("/dev/zero");
			return;
		}
E 13
E 8
	}
D 10
	LOOP_LAST(N, i, ENOUGH);
	micro("Simple read", N);
E 10
I 8
}
E 8
E 6

I 8
D 10

E 10
void
D 13
do_stat(char *s)
E 13
I 13
D 18
do_stat(uint64 iterations, void *cookie)
E 18
I 18
do_stat(iter_t iterations, void *cookie)
E 18
E 13
{
I 13
	struct _state *pState = (struct _state*)cookie;
E 13
D 10
	int	i, N;
E 10
	struct	stat sbuf;
D 10
	char	*file = s ? s : FILE;
E 10

E 8
I 6
D 10
	LOOP_FIRST(N, i, ENOUGH);
D 8
	if (stat("/usr/include/sys/types.h", &sbuf) == -1) {
		perror("types.h");
		exit(1);
E 8
I 8
	if (stat(file, &sbuf) == -1) {
		perror(file);
E 10
I 10
D 13
	if (stat(s, &sbuf) == -1) {
		perror(s);
E 10
		return;
E 13
I 13
D 14
	for (; iterations > 0; --iterations) {
E 14
I 14
	while (iterations-- > 0) {
E 14
		if (stat(pState->file, &sbuf) == -1) {
			perror(pState->file);
			return;
		}
E 13
E 8
	}
D 10
	LOOP_LAST(N, i, ENOUGH);
	micro("Simple stat", N);
E 10
I 8
}
E 8

I 8
void
D 10
do_fstat(char *s)
E 10
I 10
D 13
do_fstat(int fd)
E 13
I 13
D 18
do_fstat(uint64 iterations, void *cookie)
E 18
I 18
do_fstat(iter_t iterations, void *cookie)
E 18
E 13
E 10
{
I 13
	struct _state *pState = (struct _state*)cookie;
E 13
D 10
	int	i, N, fd;
E 10
	struct	stat sbuf;
D 10
	char	*file = s ? s : FILE;
E 10

D 10
	fd = open(file, 0);
E 8
	LOOP_FIRST(N, i, ENOUGH);
E 10
D 8
	fd = open("/usr/include/sys/types.h", 0);
E 8
I 8
D 13
	if (fstat(fd, &sbuf) == -1) {
D 10
		perror(file);
E 10
I 10
		perror("fstat");
E 10
		return;
E 13
I 13
D 14
	for (; iterations > 0; --iterations) {
E 14
I 14
	while (iterations-- > 0) {
E 14
		if (fstat(pState->fd, &sbuf) == -1) {
			perror("fstat");
			return;
		}
E 13
	}
D 10
	LOOP_LAST(N, i, ENOUGH);
D 9
	micro("Simple stat", N);
E 9
I 9
	micro("Simple fstat", N);
E 10
E 9
}

void
D 13
do_openclose(char *s)
E 13
I 13
D 18
do_openclose(uint64 iterations, void *cookie)
E 18
I 18
do_openclose(iter_t iterations, void *cookie)
E 18
E 13
{
I 13
	struct _state *pState = (struct _state*)cookie;
E 13
D 10
	int	i, N, fd;
	char	*file = s ? s : FILE;
	
	LOOP_FIRST(N, i, ENOUGH);
	fd = open(file, 0);
E 10
I 10
	int	fd;

D 13
	fd = open(s, 0);
E 10
E 8
	if (fd == -1) {
D 8
		perror("types.h");
		return(1);
E 8
I 8
D 10
		perror(file);
E 10
I 10
		perror(s);
E 10
		return;
E 13
I 13
D 18
	for (; iterations > 0; --iterations) {
E 18
I 18
	while (iterations-- > 0) {
E 18
		fd = open(pState->file, 0);
		if (fd == -1) {
			perror(pState->file);
			return;
		}
		close(fd);
E 13
E 8
	}
E 6
D 13
	close(fd);
E 13
D 6
	N = 1<<7;
	do {
		N <<= 2;
		start();
		for (i = 0; i < N; ++i) {
			if (stat("/usr/include/sys/types.h", &sbuf) == -1) {
				perror("types.h");
				return(1);
			}
		}
	} while (stop() < ENOUGH);
	nano("Null stat", N);
E 6
I 6
D 10
	LOOP_LAST(N, i, ENOUGH);
	micro("Simple open/close", N);
E 10
I 8
}
E 8
E 6

D 8
	return(0);
E 8
I 8
int
main(int ac, char **av)
{
I 14
	int parallel = 1;
I 15
	int warmup = 0;
	int repetitions = TRIES;
E 15
	int c;
E 14
I 10
D 13
	int	fd;
	char	*file;
E 13
I 13
	struct _state state;
I 14
D 15
	char* usage = "[-P <parallelism>] null|read|write|stat|open [file]\n";
E 15
I 15
D 19
	char* usage = "[-P <parallelism>] [-W <warmup>] [-N <repetitions>] null|read|write|stat|open [file]\n";
E 19
I 19
	char* usage = "[-P <parallelism>] [-W <warmup>] [-N <repetitions>] null|read|write|stat|fstat|open [file]\n";
E 19
E 15
E 14
E 13

E 10
D 14
	if (ac < 2) goto usage;
I 10
D 11
	file = av[2] ? av[2] : FILE;
E 11
I 11
D 13
	file = av[2] ? av[2] : FNAME;
E 13
I 13
	state.file = av[2] ? av[2] : FNAME;
E 14
I 14
D 15
	while (( c = getopt(ac, av, "P:")) != EOF) {
E 15
I 15
	while (( c = getopt(ac, av, "P:W:N:")) != EOF) {
E 15
		switch(c) {
		case 'P':
			parallel = atoi(optarg);
			if (parallel <= 0) lmbench_usage(ac, av, usage);
			break;
I 15
		case 'W':
			warmup = atoi(optarg);
			break;
		case 'N':
			repetitions = atoi(optarg);
			break;
E 15
		default:
			lmbench_usage(ac, av, usage);
			break;
		}
	}
	if (optind != ac - 1 && optind != ac - 2 ) {
		lmbench_usage(ac, av, usage);
	}
	
	state.file = FNAME;
	if (optind == ac - 2) 
		state.file = av[optind + 1];
E 14
E 13
E 11
E 10

D 14
	if (!strcmp("null", av[1])) {
D 10
		do_getppid();
E 10
I 10
D 13
		BENCH(getppid(), 0);
E 13
I 13
		benchmp(NULL, do_getppid, NULL, 0, 1, &state);
E 14
I 14
	if (!strcmp("null", av[optind])) {
D 15
		benchmp(NULL, do_getppid, NULL, 0, parallel, &state);
E 15
I 15
		benchmp(NULL, do_getppid, NULL, 0, parallel, 
			warmup, repetitions, &state);
E 15
E 14
E 13
		micro("Simple syscall", get_n());
E 10
D 14
	} else if (!strcmp("write", av[1])) {
E 14
I 14
	} else if (!strcmp("write", av[optind])) {
E 14
D 10
		do_write();
E 10
I 10
D 13
		fd = open("/dev/null", 1);
		BENCH(do_write(fd), 0);;
E 13
I 13
		state.fd = open("/dev/null", 1);
D 14
		benchmp(NULL, do_write, NULL, 0, 1, &state);
E 14
I 14
D 15
		benchmp(NULL, do_write, NULL, 0, parallel, &state);
E 15
I 15
		benchmp(NULL, do_write, NULL, 0, parallel, 
			warmup, repetitions, &state);
E 15
E 14
E 13
		micro("Simple write", get_n());
D 13
		close(fd);
E 13
I 13
		close(state.fd);
E 13
E 10
D 14
	} else if (!strcmp("read", av[1])) {
E 14
I 14
	} else if (!strcmp("read", av[optind])) {
E 14
D 10
		do_read();
E 10
I 10
D 13
		fd = open("/dev/zero", 0);
		if (fd == -1) {
E 13
I 13
		state.fd = open("/dev/zero", 0);
		if (state.fd == -1) {
E 13
D 16
			fprintf(stderr, "Read from /dev/zero: -1");
E 16
I 16
D 17
			fprintf(stderr, "Read from /dev/zero: -1\n");
E 17
I 17
			fprintf(stderr, "Simple read: -1\n");
E 17
E 16
			return(1);
		}
D 13
		BENCH(do_read(fd), 0);
E 13
I 13
D 14
		benchmp(NULL, do_read, NULL, 0, 1, &state);
E 14
I 14
D 15
		benchmp(NULL, do_read, NULL, 0, parallel, &state);
E 15
I 15
		benchmp(NULL, do_read, NULL, 0, parallel, 
			warmup, repetitions, &state);
E 15
E 14
E 13
		micro("Simple read", get_n());
D 13
		close(fd);
E 13
I 13
		close(state.fd);
E 13
E 10
D 14
	} else if (!strcmp("stat", av[1])) {
D 10
		do_stat(av[2]);
E 10
I 10
D 13
		BENCH(do_stat(file), 0);
E 13
I 13
		benchmp(NULL, do_stat, NULL, 0, 1, &state);
E 14
I 14
	} else if (!strcmp("stat", av[optind])) {
D 15
		benchmp(NULL, do_stat, NULL, 0, parallel, &state);
E 15
I 15
		benchmp(NULL, do_stat, NULL, 0, parallel, 
			warmup, repetitions, &state);
E 15
E 14
E 13
		micro("Simple stat", get_n());
E 10
D 14
	} else if (!strcmp("fstat", av[1])) {
E 14
I 14
	} else if (!strcmp("fstat", av[optind])) {
E 14
D 10
		do_fstat(av[2]);
E 10
I 10
D 13
		fd = open(file, 0);
		BENCH(do_fstat(fd), 0);
E 13
I 13
		state.fd = open(state.file, 0);
D 14
		benchmp(NULL, do_fstat, NULL, 0, 1, &state);
E 14
I 14
D 15
		benchmp(NULL, do_fstat, NULL, 0, parallel, &state);
E 15
I 15
		benchmp(NULL, do_fstat, NULL, 0, parallel, 
			warmup, repetitions, &state);
E 15
E 14
E 13
		micro("Simple fstat", get_n());
I 13
		close(state.fd);
E 13
E 10
D 14
	} else if (!strcmp("open", av[1])) {
D 10
		do_openclose(av[2]);
E 10
I 10
D 13
		BENCH(do_openclose(file), 0);
E 13
I 13
		benchmp(NULL, do_openclose, NULL, 0, 1, &state);
E 14
I 14
	} else if (!strcmp("open", av[optind])) {
D 15
		benchmp(NULL, do_openclose, NULL, 0, parallel, &state);
E 15
I 15
		benchmp(NULL, do_openclose, NULL, 0, parallel, 
			warmup, repetitions, &state);
E 15
E 14
E 13
		micro("Simple open/close", get_n());
E 10
	} else {
D 14
usage:		printf("Usage: %s null|read|write|stat|open\n", av[0]);
E 14
I 14
		lmbench_usage(ac, av, usage);
E 14
	}
D 12
	exit(0);
E 12
I 12
	return(0);
E 12
E 8
E 5
}
E 2
I 1
E 1
