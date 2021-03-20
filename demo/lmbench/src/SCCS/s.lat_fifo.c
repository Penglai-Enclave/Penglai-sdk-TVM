h08126
s 00005/00016/00151
d D 1.6 00/08/16 09:29:17 staelin 7 6
c - Change/fix SIGTERM handling to make it more robust and generic
cC
cK51584
e
s 00025/00005/00142
d D 1.5 00/08/02 18:04:59 staelin 6 5
c - Add code to deal with killing child processes when signaled by the parent so we don't
c   leave zombies lying around...
cC
cK61919
e
s 00002/00002/00145
d D 1.4 00/07/30 11:46:08 staelin 5 4
c - Change type of "iterations" from uint64 to iter_t, which is a u_long
cC
cK44917
e
s 00013/00004/00134
d D 1.3 00/07/04 14:55:53 staelin 4 3
c - Update to incorporate new "-W <warmup>" and "-N <repetitions>" flags
cC
cHhpli8.hpli.hpl.hp.com
cK44699
cZ+03:00
e
s 00107/00037/00031
d D 1.2 00/03/14 18:03:54 brucec 3 2
c Make this test MP "-P <parallelism>" ready.
cC
cHrx7
cK25932
cZ-05:00
e
s 00068/00000/00000
d D 1.1 97/10/19 23:48:44 lm 2 1
c Initial revision
cC
cK28664
cSAlpha2.11
e
s 00000/00000/00000
d D 1.0 97/10/19 23:48:43 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK03898
cPsrc/lat_fifo.c
cRe79b9fced992184a
cV4
cX0x21
cZ-07:00
e
u
U
f e 0
f x 0x21
t
time fifos.
T
I 2
/*
 * lat_fifo.c - named pipe transaction test
 *
I 3
D 4
 * usage: lat_fifo [-P <parallelism>]
E 4
I 4
 * usage: lat_fifo [-P <parallelism>] [-W <warmup>] [-N <repetitions>]
E 4
 *
E 3
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 */
char	*id = "$Id$\n";

#include "bench.h"

D 3
#define	F1	"/tmp/lmbench_f1"
#define	F2	"/tmp/lmbench_f2"
E 3
I 3
#define	F1	"/tmp/lmbench_f1.%d"
#define	F2	"/tmp/lmbench_f2.%d"
E 3

D 3
void
doit(int r, int w)
{
	char	c;
E 3
I 3
void initialize(void *cookie);
void cleanup(void *cookie);
D 5
void doit(uint64 iterations,void *cookie);
E 5
I 5
void doit(iter_t iterations, void *cookie);
E 5
void writer(int wr, int rd);

typedef struct _state {
	char	filename1[256];
	char	filename2[256];
	int	pid;
	int	wr;
	int	rd;
} state_t;
E 3

D 3
	if (write(w, &c, 1) != 1 || read(r, &c, 1) != 1) {
			perror("read/write on pipe");
			exit(1);
E 3
I 3
D 6
int main(int ac, char **av)
E 6
I 6
D 7
state_t* pGlobalState;

void
sigterm_handler(int n)
{
	if (pGlobalState->pid) {
		kill(SIGKILL, pGlobalState->pid);
	}
	exit(0);
}

E 7
int 
main(int ac, char **av)
E 6
{
	state_t state;
	int parallel = 1;
I 4
	int warmup = 0;
	int repetitions = TRIES;
E 4
	int c;
D 4
	char* usage = "[-P <parallelism>]\n";
E 4
I 4
	char* usage = "[-P <parallelism>] [-W <warmup>] [-N <repetitions>]\n";
E 4

D 4
	while (( c = getopt(ac, av, "P:")) != EOF) {
E 4
I 4
	while (( c = getopt(ac, av, "P:W:N:")) != EOF) {
E 4
		switch(c) {
		case 'P':
			parallel = atoi(optarg);
			if (parallel <= 0) lmbench_usage(ac, av, usage);
			break;
I 4
		case 'W':
			warmup = atoi(optarg);
			break;
		case 'N':
			repetitions = atoi(optarg);
			break;
E 4
		default:
			lmbench_usage(ac, av, usage);
			break;
		}
	}
	if (optind < ac) {
		lmbench_usage(ac, av, usage);
E 3
	}
I 3

I 6
	state.pid = 0;
D 7
	pGlobalState = &state;
	signal(SIGTERM, sigterm_handler);
E 7

E 6
D 4
	benchmp(initialize, doit, cleanup, SHORT, parallel, &state);
E 4
I 4
	benchmp(initialize, doit, cleanup, SHORT, parallel, 
		warmup, repetitions, &state);
E 4
	micro("Fifo latency", get_n());
I 7
	return (0);
E 7
E 3
}

D 3
int
main()
E 3
I 3
D 6
void initialize(void *cookie)
E 6
I 6
void 
initialize(void *cookie)
E 6
E 3
{
D 3
	int	pid, rd, wr;
E 3
	char	c;
I 3
	state_t * state = (state_t *)cookie;
E 3

D 3
	unlink(F1); unlink(F2);
	if (mknod(F1, S_IFIFO|0664, 0) || mknod(F2, S_IFIFO|0664, 0)) {
E 3
I 3
	sprintf(state->filename1,F1,getpid());
	sprintf(state->filename2,F2,getpid());
	
	unlink(state->filename1); unlink(state->filename2);
	if (mknod(state->filename1, S_IFIFO|0664, 0) ||
	    mknod(state->filename2, S_IFIFO|0664, 0)) {
E 3
		perror("mknod");
		exit(1);
	}
D 3
	pid = fork();
	if (pid == -1) {
E 3
I 3
	switch (state->pid = fork()) {
	    case 0:
I 7
		signal(SIGTERM, exit);
E 7
		state->rd = open(state->filename1, O_RDONLY);
		state->wr = open(state->filename2, O_WRONLY);
		writer(state->wr, state->rd);
		return;

	    case -1:
E 3
		perror("fork");
I 3
		return;

	    default:
		state->wr = open(state->filename1, O_WRONLY);
		state->rd = open(state->filename2, O_RDONLY);
		break;
	}

	/*
	 * One time around to make sure both processes are started.
	 */
	if (write(state->wr, &c, 1) != 1 ||read(state->rd, &c, 1) != 1) {
		perror("(i) read/write on pipe");
E 3
		exit(1);
	}
D 3
	if (pid > 0) {
		rd = open(F1, O_RDONLY);
		wr = open(F2, O_WRONLY);
		/*
		 * One time around to make sure both processes are started.
		 */
		if (write(wr, &c, 1) != 1 || read(rd, &c, 1) != 1) {
			perror("read/write on pipe");
E 3
I 3
}

D 6
void cleanup(void * cookie)
E 6
I 6
void 
cleanup(void * cookie)
E 6
{
	state_t * state = (state_t *)cookie;

D 7
	signal(SIGCHLD,SIG_IGN);
	kill(state->pid, 15);
E 7
I 7
	signal(SIGCHLD, SIG_IGN);
	if (state->pid) kill(state->pid, 15);
E 7
	unlink(state->filename1);
	unlink(state->filename2);
D 7
	kill(state->pid, 9);
E 7
I 7
	if (state->pid) kill(state->pid, 9);
E 7
	close(state->wr);
	close(state->rd);
}

D 5
void doit(register uint64 iterations, void *cookie)
E 5
I 5
D 6
void doit(register iter_t iterations, void *cookie)
E 6
I 6
void 
doit(register iter_t iterations, void *cookie)
E 6
E 5
{
	state_t *state = (state_t *) cookie;
	char		c;
	register int	w = state->wr;
	register int	r = state->rd;
	register char	*cptr = &c;

	while (iterations-- > 0) {
		if (write(w, cptr, 1) != 1 ||
		    read(r, cptr, 1) != 1) {
			perror("(r) read/write on pipe");
E 3
			exit(1);
		}
D 3
		BENCH(doit(rd, wr), SHORT);
		micro("Pipe latency", get_n());
		kill(pid, 15);
	} else {
		wr = open(F1, O_WRONLY);
		rd = open(F2, O_RDONLY);
		for ( ;; ) {
			if (read(rd, &c, 1) != 1 ||
			    write(wr, &c, 1) != 1) {
				perror("read/write on pipe");
				exit(1);
			}
E 3
I 3
	}
}

D 6
void writer(register int w, register int r)
E 6
I 6
void 
writer(register int w, register int r)
E 6
{
	char		c;
	register char	*cptr = &c;

	for ( ;; ) {
		if (read(r, cptr, 1) != 1 ||
			write(w, cptr, 1) != 1) {
			    perror("(w) read/write on pipe");
E 3
		}
	}
D 3
	return (0);
E 3
}
E 2
I 1
E 1
