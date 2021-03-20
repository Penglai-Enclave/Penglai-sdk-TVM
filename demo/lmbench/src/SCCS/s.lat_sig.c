h23560
s 00001/00001/00210
d D 1.19 00/10/19 17:06:19 staelin 20 19
c - bugfix to lat_sig; fixed incorrect parameters to lmbench_usage()
cC
cK33840
cZ+02:00
e
s 00004/00004/00207
d D 1.18 00/07/30 11:46:13 staelin 19 18
c - Change type of "iterations" from uint64 to iter_t, which is a u_long
cC
cK34770
e
s 00024/00012/00187
d D 1.17 00/07/04 14:55:58 staelin 18 17
c - Update to incorporate new "-W <warmup>" and "-N <repetitions>" flags
cC
cK34398
cZ+03:00
e
s 00003/00004/00196
d D 1.16 00/04/17 13:06:02 staelin 17 16
c - rewrote lat_sig so that it didn't use longjmp() within a signal handler; it uses
c   the new functions benchmp_getstate() and benchmp_interval() to manage/report the
c   timing results.
cC
cK00475
e
s 00130/00079/00070
d D 1.15 00/03/01 17:23:38 staelin 16 15
c - Nearly a complete rewrite to convert it to the new benchmp harness.  As a
c   side-effect, the statistical harness for 'lat_sig prot' is now used properly
c   and *should* provide statistically more reliable results
cC
cHhpli8.hpli.hpl.hp.com
cK62978
cZ+02:00
e
s 00004/00004/00145
d D 1.14 97/06/15 22:38:58 lm 15 14
c lint
cC
cK20341
cSAlpha2.11
e
s 00001/00000/00148
d D 1.13 97/06/13 20:39:50 lm 14 13
c lint
cK18809
e
s 00001/00001/00147
d D 1.12 97/06/13 20:27:10 lm 13 12
c more bench.h.
cK18365
e
s 00028/00030/00120
d D 1.11 97/06/12 21:30:06 lm 12 11
c new bench.h macros.
cK18419
e
s 00001/00000/00149
d D 1.10 97/05/27 16:02:49 lm 11 10
c oops.
cK29082
e
s 00001/00000/00148
d D 1.9 97/04/28 17:26:00 lm 10 9
c sigbus.
cK28317
e
s 00073/00032/00075
d D 1.8 97/04/23 22:33:21 lm 9 8
c new interface: install|catch|prot file
cK26286
cZ-07:00
e
s 00061/00046/00046
d D 1.7 96/11/11 03:36:51 lm 8 7
c Auto adjusting changes.
cK45094
e
s 00004/00004/00088
d D 1.6 96/11/08 20:05:24 lm 7 6
c gcc -Wall cleanup.
cK31548
cZ-08:00
e
s 00000/00001/00092
d D 1.5 96/05/30 00:33:07 lm 6 5
c no what strings
cK31364
cZ-07:00
e
s 00038/00007/00055
d D 1.4 96/01/22 23:59:04 lm 5 4
c add protection fault.
cK33435
cZ-08:00
e
s 00007/00001/00055
d D 1.3 95/09/25 22:38:58 lm 4 3
c remove the overhead of the kill system call.
cK49148
e
s 00014/00007/00042
d D 1.2 95/08/22 15:40:56 lm 3 2
c Two numbers: installation & catching it.
cK41578
cZ-07:00
e
s 00049/00000/00000
d D 1.1 94/11/29 16:16:39 lm 2 1
c Initial revision
cK18896
e
s 00000/00000/00000
d D 1.0 94/11/29 16:16:38 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK06404
cPsrc/lat_sig.c
cRb8488b438b6e1c23
cV4
cX0x21
cZ-08:00
e
u
U
f e 0
f x 0x21
t
lmbench benchmark for signal handlers.
T
I 2
/*
 * lat_sig.c - signal handler test
 *
 * XXX - this benchmark requires the POSIX sigaction interface.  The reason
 * for that is that the signal handler stays installed with that interface.
 * The more portable signal() interface may or may not stay installed and
 * reinstalling it each time is expensive.
 *
I 8
 * XXX - should really do a two process version.
 *
E 8
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 */
char	*id = "$Id$\n";

D 5
#include <signal.h>
E 5
I 5
D 12
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/signal.h>
I 7
#include <fcntl.h>
E 7
E 5
D 8
#include "timing.c"
E 8
I 8
#include "timing.h"
E 12
#include "bench.h"
I 16
#include <setjmp.h>
E 16
E 8

D 5
#define N	50000
E 5
I 5
D 8
#define N	100000
E 8
E 5
D 16

D 8
int	caught = 0;
int	me;
I 5
int	sighandlecost;
E 8
I 8
D 9
int	n, caught;
double	adj;
E 9
E 8
E 5
D 12

E 12
I 9
int	caught, n;
E 16
I 16
uint64	caught, n;
E 16
double	adj;
E 9
D 3
void	
handler()
{
	caught++;
}
E 3
I 3
D 8
void	handler() { caught++; }
void	handler2() { caught++; }
I 5
D 7
void	
protection() 
E 7
I 7
void	protection() 
E 7
{
	if (++caught == N) {
		stop();
		(void)adjust(-sighandlecost);
		micro("Protection fault", N);
E 8
I 8
void	handler() { }
D 16
void	prot() {
	if (++caught == n) {
		double	u;

		u = stop(0,0);
		u /= n;
		u -= adj;
		fprintf(stderr, "Protection fault: %.3f microseconds\n", u);
E 8
		exit(0);
	}
}
E 16
I 16
jmp_buf	prot_env;
E 16
E 5
E 3

D 9
int
D 5
main()
E 5
I 5
main(int ac, char **av)
E 9
I 9
D 16
double
D 15
overhead()
E 15
I 15
overhead(void)
E 16
I 16
void
D 19
do_send(uint64 iterations, void* cookie)
E 19
I 19
do_send(iter_t iterations, void* cookie)
E 19
E 16
E 15
E 9
E 5
{
D 4
	int	i;
E 4
I 4
D 5
	int	i, overhead;
E 5
I 5
D 8
	int	i, fd, overhead;
E 8
I 8
D 9
	int	me, N, i, fd;
E 8
E 5
E 4
D 3
	struct	sigaction sa;
E 3
I 3
	struct	sigaction sa, old;
I 5
	char	*where;
I 8
	double	u, overhead;
E 9
I 9
D 12
	int	me = getpid(), N, i;
E 12
I 12
	int	me = getpid();
D 16
	double	o;
E 16
E 12
E 9
E 8
E 5
E 3

D 6
	write(2, id, strlen(id));
E 6
I 5
D 9
	if (ac != 2) {
		fprintf(stderr, "usage: %s file\n", av[0]);          
		exit(1);
	}
	fd = open(av[1], 0);
	where = mmap(0, 4096, PROT_READ, MAP_SHARED, fd, 0);
	if ((int)where == -1) {
		perror("mmap");
		exit(1);
	}
E 5
	me = getpid();
E 9
I 9
D 16
	/*
	 * OS cost of sending a signal without actually sending one
	 */
D 12
	LOOP_FIRST(N, i, ENOUGH);
	kill(me, 0);
	LOOP_LAST(N, i, ENOUGH);
	return ((double)i/N);
E 12
I 12
	BENCH(kill(me, 0), 0);
	o = usecs_spent();
	o /= get_n();
	return (o);
E 16
I 16
	while (--iterations > 0) {
		kill(me, 0);
	}
E 16
E 12
}
E 9
D 3
	sa.sa_handler = handler;
E 3
I 3
D 8
	sa.sa_handler = handler2;
E 3
	sigemptyset(&sa.sa_mask);	/* don't care */
	sa.sa_flags = 0;		/* don't care */
	sigaction(SIGUSR1, &sa, 0);
	start();
I 3
D 7
	for (i = 0; i < N/2; ++i) {
E 7
I 7
	for (i = 0; i < N; ++i) {
E 7
		sa.sa_handler = handler;
		sigemptyset(&sa.sa_mask);	/* don't care */
		sa.sa_flags = 0;		/* don't care */
		sigaction(SIGUSR1, &sa, &old);
D 7
		sigaction(SIGUSR1, &old, 0);
E 7
	}
	stop();
	micro("Signal handler installation", N);
	start();
E 3
	for (i = 0; i < N; ++i) {
I 4
		kill(me, 0);
	}
	overhead = stop();
	start();
	for (i = 0; i < N; ++i) {
E 4
		kill(me, SIGUSR1);
	}
	i = stop();
I 4
D 5
	adjust(-overhead);
E 4
	micro("Signal handler overhead", caught);
	exit(0);
E 5
I 5
	sighandlecost = adjust(-overhead);
	micro("Signal handler overhead", N);	/* XXX - was caught! */
	sa.sa_handler = protection;
	sigemptyset(&sa.sa_mask);	/* don't care */
	sa.sa_flags = 0;		/* don't care */
E 8
I 8

I 14
void
E 14
I 12
D 15
install()
E 15
I 15
D 16
install(void)
E 16
I 16
D 19
do_install(uint64 iterations, void* cookie)
E 19
I 19
do_install(iter_t iterations, void* cookie)
E 19
E 16
E 15
{
	struct	sigaction sa, old;

D 16
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);	
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, &old);
}
E 12
I 9
void
D 15
do_install()
E 15
I 15
do_install(void)
E 15
{
D 12
	int	N, i;
	struct	sigaction sa, old;
E 12
	double	u;

E 9
	/*
	 * Installation cost
	 */
D 12
	LOOP_FIRST(N, i, ENOUGH);
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);	
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, &old);
	LOOP_LAST(N, i, ENOUGH);
	u = i;
	u /= N;
	fprintf(stderr, "Signal handler installation: %.3f microseconds\n", u);
E 12
I 12
	BENCH(install(), 0);
	u = usecs_spent();
	u /= get_n();
	fprintf(stderr,
	    "Signal handler installation: %.3f microseconds\n", u);
E 16
I 16
	while (iterations-- > 0) {
		sa.sa_handler = handler;
		sigemptyset(&sa.sa_mask);	
		sa.sa_flags = 0;
		sigaction(SIGUSR1, &sa, &old);
	}
E 16
E 12
I 9
}
E 9

D 9
	/*
	 * OS cost of sending a signal without actually sending one
	 */
	LOOP_FIRST(N, i, ENOUGH);
	kill(me, 0);
	LOOP_LAST(N, i, ENOUGH);
	overhead = i;
	overhead /= N;
E 9
I 9
void
D 16
do_catch(int report)
E 16
I 16
D 19
do_catch(uint64 iterations, void* cookie)
E 19
I 19
do_catch(iter_t iterations, void* cookie)
E 19
E 16
{
D 12
	int	me = getpid(), N, i;
E 12
I 12
	int	me = getpid();
E 12
	struct	sigaction sa, old;
	double	u;
E 9

D 16
	/*
	 * Cost of catching the signal less the cost of sending it
	 */
E 16
I 9
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);	
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, &old);
E 9
D 12
	LOOP_FIRST(N, i, ENOUGH);
	kill(me, SIGUSR1);
	LOOP_LAST(N, i, ENOUGH);
	u = i;
	u /= N;
E 12
I 12
D 16
	BENCH(kill(me, SIGUSR1), 0);
	u = usecs_spent();
	u /= get_n();
E 12
D 9
	u -= overhead;
	fprintf(stderr, "Signal handler overhead: %.3f microseconds\n", u);
E 9
I 9
	u -= overhead();
	adj = u;
D 13
	n = ENOUGH/u;
E 13
I 13
	n = SHORT/u;
E 13
D 12
	if (report)
		fprintf(stderr, "Signal handler overhead: %.3f microseconds\n", u);
E 12
I 12
	if (report) {
		fprintf(stderr,
		    "Signal handler overhead: %.3f microseconds\n", u);
E 16
I 16

	while (--iterations > 0) {
		kill(me, SIGUSR1);
E 16
	}
E 12
}
E 9

I 16
struct _state {
	char*	fname;
	char*	where;
};

E 16
I 9
void
D 16
do_prot(int ac, char **av)
E 16
I 16
prot() {
	if (++caught == n) {
		caught = 0;
D 17
		longjmp(prot_env, 1);
E 17
I 17
		n = benchmp_interval(benchmp_getstate());
E 17
	}
}

void
initialize(void* cookie)
E 16
{
I 16
	struct _state* state = (struct _state*)cookie;
E 16
	int	fd;
	struct	sigaction sa;
D 16
	char	*where;
E 16

D 16
	if (ac != 3) {
		fprintf(stderr, "usage: %s prot file\n", av[0]);          
		exit(1);
	}
	fd = open(av[2], 0);
	where = mmap(0, 4096, PROT_READ, MAP_SHARED, fd, 0);
	if ((int)where == -1) {
E 16
I 16
	fd = open(state->fname, 0);
	state->where = mmap(0, 4096, PROT_READ, MAP_SHARED, fd, 0);
	if ((int)state->where == -1) {
E 16
		perror("mmap");
		exit(1);
	}
E 9
D 16
	/*
	 * Catch protection faults.
	 * Assume that they will cost the same as a normal catch.
	 */
D 9
	adj = u;
	n = ENOUGH/u;
E 9
I 9
	do_catch(0);
E 16
I 16

E 16
E 9
	sa.sa_handler = prot;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
E 8
	sigaction(SIGSEGV, &sa, 0);
I 10
	sigaction(SIGBUS, &sa, 0);
I 11
D 16
	start(0);
E 11
E 10
D 8
	caught = 0;
	start();
E 8
	*where = 1;
E 16
I 16
}

void
D 19
do_prot(uint64 iterations, void* cookie)
E 19
I 19
do_prot(iter_t iterations, void* cookie)
E 19
{
	struct _state* state = (struct _state*)cookie;

	n = iterations;
	caught = 0;

D 17
	if (setjmp(prot_env)) {
		return;
	}
E 17
I 17
	/* start the first timing interval */
	start(0);
E 17

	/* trigger the page fault, causing us to jump to prot() */
	*state->where = 1;
}

/*
 * Cost of catching the signal less the cost of sending it
 */
void
D 18
bench_catch(int parallel)
E 18
I 18
bench_catch(int parallel, int warmup, int repetitions)
E 18
{
	uint64 t, send_usecs, send_n;

	/* measure cost of sending signal */
D 18
	benchmp(NULL, do_send, NULL, 0, parallel, NULL);
E 18
I 18
	benchmp(NULL, do_send, NULL, 0, parallel, 
		warmup, repetitions, NULL);
E 18
	send_usecs = gettime();
	send_n = get_n();

	/* measure cost of sending & catching signal */
D 18
	benchmp(NULL, do_catch, NULL, 0, parallel, NULL);
E 18
I 18
	benchmp(NULL, do_catch, NULL, 0, parallel, 
		warmup, repetitions, NULL);
E 18

	/* subtract cost of sending signal */
	if (gettime() > (send_usecs * get_n()) / send_n) {
		settime(gettime() - (send_usecs * get_n()) / send_n);
	} else {
		settime(0);
	}
}

void
D 18
bench_prot(char* fname, int parallel)
E 18
I 18
bench_prot(char* fname, int parallel, int warmup, int repetitions)
E 18
{
	uint64 catch_usecs, catch_n;
	struct _state state;

	state.fname = fname;

	/*
	 * Catch protection faults.
	 * Assume that they will cost the same as a normal catch.
	 */
D 18
	bench_catch(parallel);
E 18
I 18
	bench_catch(parallel, warmup, repetitions);
E 18
	catch_usecs = gettime();
	catch_n = get_n();

D 18
	benchmp(initialize, do_prot, NULL, 0, parallel, &state);
E 18
I 18
	benchmp(initialize, do_prot, NULL, 0, parallel, 
		warmup, repetitions, &state);
E 18
	if (gettime() > (catch_usecs * get_n()) / catch_n) {
		settime(gettime() - (catch_usecs * get_n()) / catch_n);
	} else {
		settime(0);
	}
E 16
D 8
	/* NOTREACHED */
I 7
	return(0);
E 8
I 8
D 9
	return (0);
E 9
E 8
E 7
E 5
}
I 9


int
main(int ac, char **av)
{
D 16
	if (ac < 2) goto usage;
E 16
I 16
	int parallel = 1;
I 18
	int warmup = 0;
	int repetitions = TRIES;
E 18
	int c;
D 18
	char* usage = "[-P <parallelism>] install|catch|prot [file]\n";
E 18
I 18
	char* usage = "[-P <parallelism>] [-W <warmup>] [-N <repetitions>] install|catch|prot [file]\n";
E 18

D 18
	while (( c = getopt(ac, av, "P:")) != EOF) {
E 18
I 18
	while (( c = getopt(ac, av, "P:W:N:")) != EOF) {
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
E 18
		default:
			lmbench_usage(ac, av, usage);
			break;
		}
	}
	if (optind != ac - 1 && optind != ac - 2) {
		lmbench_usage(ac, av, usage);
	}
E 16

D 16
	if (!strcmp("install", av[1])) {
		do_install();
	} else if (!strcmp("catch", av[1])) {
		do_catch(1);
	} else if (!strcmp("prot", av[1])) {
		do_prot(ac, av);
E 16
I 16
	if (!strcmp("install", av[optind])) {
D 18
		benchmp(NULL, do_install, NULL, 0, parallel, NULL);
E 18
I 18
		benchmp(NULL, do_install, NULL, 0, parallel, 
			warmup, repetitions, NULL);
E 18
		micro("Signal handler installation", get_n());
	} else if (!strcmp("catch", av[optind])) {
D 18
		bench_catch(parallel);
E 18
I 18
		bench_catch(parallel, warmup, repetitions);
E 18
		micro("Signal handler overhead", get_n());
	} else if (!strcmp("prot", av[optind]) && optind == ac - 2) {
D 18
		bench_prot(av[optind+1], parallel);
E 18
I 18
		bench_prot(av[optind+1], parallel, warmup, repetitions);
E 18
		micro("Protection fault", get_n());
E 16
	} else {
D 16
usage:		printf("Usage: %s install|catch|prot file\n", av[0]);
E 16
I 16
D 18
		lmbench_usage(av[optind+1], usage);
E 18
I 18
D 20
		lmbench_usage(ac, av[optind+1], usage);
E 20
I 20
		lmbench_usage(ac, av, usage);
E 20
E 18
E 16
	}
D 15
	exit(0);
E 15
I 15
	return(0);
E 15
}
E 9
E 2
I 1
E 1
