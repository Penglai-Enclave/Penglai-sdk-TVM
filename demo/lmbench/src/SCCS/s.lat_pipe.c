h29808
s 00004/00000/00144
d D 1.14 01/04/02 14:52:53 staelin 15 14
c Fix buglets in lat_pipe; unused pipe fids were not closed 
c properly after fork, so lat_pipe could leave zombie processes.
cC
cHhpli69.hpli.hpl.hp.com
cK20120
cZ+02:00
e
s 00006/00016/00138
d D 1.13 00/08/16 09:29:18 staelin 14 13
c - Change/fix SIGTERM handling to make it more robust and generic
cC
cK13128
e
s 00025/00005/00129
d D 1.12 00/08/02 18:05:00 staelin 13 12
c - Add code to deal with killing child processes when signaled by the parent so we don't
c   leave zombies lying around...
cC
cK25753
e
s 00002/00002/00132
d D 1.11 00/07/30 11:46:10 staelin 12 11
c - Change type of "iterations" from uint64 to iter_t, which is a u_long
cC
cK08751
e
s 00013/00004/00121
d D 1.10 00/07/04 14:55:55 staelin 11 10
c - Update to incorporate new "-W <warmup>" and "-N <repetitions>" flags
cC
cHhpli8.hpli.hpl.hp.com
cK08533
cZ+03:00
e
s 00093/00030/00032
d D 1.9 00/03/14 18:03:54 brucec 10 9
c Make this test MP "-P <parallelism>" ready.
cC
cHrx7
cK55302
cZ-05:00
e
s 00001/00002/00061
d D 1.8 97/06/15 22:38:58 lm 9 8
c lint
cC
cK21742
e
s 00011/00010/00052
d D 1.7 97/06/13 20:39:50 lm 8 7
c lint
cK22419
e
s 00013/00011/00049
d D 1.6 97/06/12 21:30:06 lm 7 6
c new bench.h macros.
cK21975
cZ-07:00
e
s 00001/00001/00059
d D 1.5 96/11/13 16:09:37 lm 6 5
c timing.c interfaces.
cK24451
e
s 00009/00022/00051
d D 1.4 96/11/11 03:36:51 lm 5 4
c Auto adjusting changes.
cK27376
e
s 00001/00000/00072
d D 1.3 96/11/08 20:00:24 lm 4 3
c gcc -Wall cleanup.
cK35168
cZ-08:00
e
s 00000/00001/00072
d D 1.2 96/05/30 00:33:07 lm 3 2
c no what strings
cK34257
cZ-07:00
e
s 00073/00000/00000
d D 1.1 94/11/18 00:49:48 lm 2 1
c Initial revision
cK36328
e
s 00000/00000/00000
d D 1.0 94/11/18 00:49:47 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK42508
cPsrc/lat_pipe.c
cRb08317879cd9d375
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
 * lat_pipe.c - pipe transaction test
 *
I 10
D 11
 * usage: lat_pipe [-P <parallelism>]
E 11
I 11
 * usage: lat_pipe [-P <parallelism>] [-W <warmup>] [-N <repetitions>]
E 11
 *
E 10
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
char	*id = "$Id$\n";

D 5
#include "timing.c"
E 5
I 5
D 7
#include "timing.h"
E 7
#include "bench.h"
E 5

I 8
D 10
void
doit(int r, int w)
{
	char	c;
E 10
I 10
void initialize(void *cookie);
void cleanup(void *cookie);
D 12
void doit(uint64 iterations,void *cookie);
E 12
I 12
void doit(iter_t iterations, void *cookie);
E 12
void writer(int w, int r);

typedef struct _state {
	int	pid;
	int	p1[2];
	int	p2[2];
} state_t;
E 10

D 10
	if (write(w, &c, 1) != 1 || read(r, &c, 1) != 1) {
			perror("read/write on pipe");
			exit(1);
E 10
I 10
D 13
int main(int ac, char **av)
E 13
I 13
D 14
state_t* pGlobalState;

void
sigterm_handler(int n)
{
	if (pGlobalState->pid) {
		kill(SIGKILL, pGlobalState->pid);
	}
	exit(0);
}

E 14
int 
main(int ac, char **av)
E 13
{
	state_t state;
	int parallel = 1;
I 11
	int warmup = 0;
	int repetitions = TRIES;
E 11
	int c;
D 11
	char* usage = "[-P <parallelism>]\n";
E 11
I 11
	char* usage = "[-P <parallelism>] [-W <warmup>] [-N <repetitions>]\n";
E 11

D 11
	while (( c = getopt(ac, av, "P:")) != EOF) {
E 11
I 11
	while (( c = getopt(ac, av, "P:W:N:")) != EOF) {
E 11
		switch(c) {
		case 'P':
			parallel = atoi(optarg);
			if (parallel <= 0) lmbench_usage(ac, av, usage);
			break;
I 11
		case 'W':
			warmup = atoi(optarg);
			break;
		case 'N':
			repetitions = atoi(optarg);
			break;
E 11
		default:
			lmbench_usage(ac, av, usage);
			break;
		}
	}
	if (optind < ac) {
		lmbench_usage(ac, av, usage);
E 10
	}
I 10

I 13
	state.pid = 0;
D 14
	pGlobalState = &state;
	signal(SIGTERM, sigterm_handler);
E 14

E 13
D 11
	benchmp(initialize, doit, cleanup, SHORT, parallel, &state);
E 11
I 11
	benchmp(initialize, doit, cleanup, SHORT, parallel, 
		warmup, repetitions, &state);
E 11
	micro("Pipe latency", get_n());
I 14
	return (0);
E 14
E 10
}

E 8
D 5
#define N	2000
#define	TRIES	5

E 5
D 10
int
main()
E 10
I 10
D 13
void initialize(void *cookie)
E 13
I 13
void 
initialize(void *cookie)
E 13
E 10
{
D 9
	int	p1[2], p2[2];
D 5
	int	i;
	int	time = 0x7fffffff;
E 5
I 5
	int	i, N, pid;
E 9
I 9
D 10
	int	pid, p1[2], p2[2];
E 10
E 9
E 5
	char	c;
I 10
	state_t * state = (state_t *)cookie;
E 10
D 5
	int	pid;
	int	j;
E 5

D 3
	write(2, id, strlen(id));
E 3
D 10
     	if (pipe(p1) == -1 || pipe(p2) == -1) {
E 10
I 10
	if (pipe(state->p1) == -1) {
E 10
		perror("pipe");
		exit(1);
	}
I 10
	if (pipe(state->p2) == -1) {
		perror("pipe");
		exit(1);
	}
	switch (state->pid = fork()) {
	    case 0:
I 14
		signal(SIGTERM, exit);
I 15
		close(state->p1[1]);
		close(state->p2[0]);
E 15
E 14
		writer(state->p2[1], state->p1[0]);
		return;
E 10

D 10
	pid = fork();
	if (pid == -1) {
E 10
I 10
	    case -1:
E 10
		perror("fork");
I 10
		return;

	    default:
I 15
		close(state->p1[0]);
		close(state->p2[1]);
E 15
		break;
	}

	/*
	 * One time around to make sure both processes are started.
	 */
	if (write(state->p1[1], &c, 1) != 1 ||read(state->p2[0], &c, 1) != 1) {
		perror("(i) read/write on pipe");
E 10
		exit(1);
	}
D 10
	if (pid > 0) {
		/*
		 * One time around to make sure both processes are started.
		 */
D 7
		if (write(p1[1], &c, 1) != 1 ||
		    read(p2[0], &c, 1) != 1 ||
		    write(p1[1], &c, 1) != 1) {
E 7
I 7
		if (write(p1[1], &c, 1) != 1 || read(p2[0], &c, 1) != 1) {
E 7
			perror("read/write on pipe");
E 10
I 10
}

D 13
void cleanup(void * cookie)
E 13
I 13
void 
cleanup(void * cookie)
E 13
{
	state_t * state = (state_t *)cookie;

D 14
	kill(state->pid, 15);
	signal(SIGCHLD,SIG_IGN);
	kill(state->pid, 9);
E 14
I 14
	signal(SIGCHLD, SIG_IGN);
	if (state->pid) {
		kill(state->pid, SIGKILL);
	}
E 14
}

D 12
void doit(register uint64 iterations, void *cookie)
E 12
I 12
D 13
void doit(register iter_t iterations, void *cookie)
E 13
I 13
void 
doit(register iter_t iterations, void *cookie)
E 13
E 12
{
	state_t *state = (state_t *) cookie;
	char		c;
	register int	w = state->p1[1];
	register int	r = state->p2[0];
	register char	*cptr = &c;

	while (iterations-- > 0) {
		if (write(w, cptr, 1) != 1 ||
		    read(r, cptr, 1) != 1) {
			perror("(r) read/write on pipe");
E 10
			exit(1);
		}
D 5
		for (j = 0; j < TRIES; ++j) {
			start();
			for (i = 0; i < N; ++i) {
				if (read(p2[0], &c, 1) != 1 ||
				    write(p1[1], &c, 1) != 1) {
					perror("read/write on pipe");
					exit(1);
				}
			}
			i = stop();
			if (time > i) {
				time = i;
			}
E 5
I 5
D 7
		LOOP_FIRST(N, i, ENOUGH);
		if (read(p2[0], &c, 1) != 1 || write(p1[1], &c, 1) != 1) {
			perror("read/write on pipe");
			exit(1);
E 5
		}
D 5
		fprintf(stderr, "Pipe latency: %d microseconds\n", time / N);
E 5
I 5
		LOOP_LAST(N, i, ENOUGH);
D 6
		fprintf(stderr, "Pipe latency: %d microseconds\n", i / N);
E 6
I 6
		micro("Pipe latency", N);
E 7
I 7
D 10
		BENCH(doit(p2[0], p1[1]), SHORT);
		micro("Pipe latency", get_n());
E 7
E 6
E 5
		kill(pid, 15);
	} else {
		for ( ;; ) {
			if (read(p1[0], &c, 1) != 1 ||
			    write(p2[1], &c, 1) != 1) {
				perror("read/write on pipe");
				exit(1);
			}
E 10
I 10
	}
}

D 13
void writer(register int w, register int r)
E 13
I 13
void 
writer(register int w, register int r)
E 13
{
	char		c;
	register char	*cptr = &c;

	for ( ;; ) {
		if (read(r, cptr, 1) != 1 ||
			write(w, cptr, 1) != 1) {
			    perror("(w) read/write on pipe");
E 10
		}
	}
I 4
D 10
	return (0);
E 10
E 4
}
I 7
D 8

doit(int r, int w)
{
	char	c;

	if (write(w, &c, 1) != 1 || read(r, &c, 1) != 1) {
			perror("read/write on pipe");
			exit(1);
	}
}
E 8
E 7
E 2
I 1
E 1
