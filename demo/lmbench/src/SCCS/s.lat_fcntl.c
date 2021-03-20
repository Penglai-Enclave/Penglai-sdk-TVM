h53166
s 00004/00004/00207
d D 1.7 01/01/07 15:34:00 staelin 8 7
c - lat_fcntl: unlink tmp files as soon as possible so they disappear
c   even if the program dies or is killed.
cC
cK52452
cZ+02:00
e
s 00004/00019/00207
d D 1.6 00/08/16 09:29:17 staelin 7 6
c - Change/fix SIGTERM handling to make it more robust and generic
cC
cK51657
e
s 00018/00002/00208
d D 1.5 00/08/02 18:04:58 staelin 6 5
c - Add code to deal with killing child processes when signaled by the parent so we don't
c   leave zombies lying around...
cC
cK04669
e
s 00003/00004/00207
d D 1.4 00/07/30 11:46:08 staelin 5 4
c - Change type of "iterations" from uint64 to iter_t, which is a u_long
cC
cK51326
e
s 00012/00003/00199
d D 1.3 00/07/04 14:55:53 staelin 4 3
c - Update to incorporate new "-W <warmup>" and "-N <repetitions>" flags
cC
cK52292
cZ+03:00
e
s 00110/00038/00092
d D 1.2 00/04/17 13:06:01 staelin 3 2
c - debugged a deadlock in the benchmark (wrong execution order in procB)
c - rewrote the benchmark to fit the new benchmp timing harness
c - added getopt() parameter handling
cC
cHhpli8.hpli.hpl.hp.com
cK36440
cZ+02:00
e
s 00130/00000/00000
d D 1.1 99/12/08 09:18:19 lm 2 1
cC
cF1
cK45595
cO-rw-r--r--
e
s 00000/00000/00000
d D 1.0 99/12/08 09:18:19 lm 1 0
c BitKeeper file /home/lm/lmbench/src/lat_fcntl.c
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHwork.bitmover.com
cK08698
cPsrc/lat_fcntl.c
cR13b82230576b9707
cV4
cX0x21
cZ-08:00
e
u
U
f e 0
f x 0x21
t
T
I 2
#include "bench.h"

/*
D 6
 * lat_pipe.c - pipe transaction test
E 6
I 6
 * lat_fcntl.c - file locking test
E 6
 *
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
char	*id = "$Id: lat_pipe.c,v 1.8 1997/06/16 05:38:58 lm Exp $\n";

#include "bench.h"

struct	flock lock, unlock;
struct	flock s1, s2;
D 3
int	fd1, fd2;
E 3

/*
 * Create two files, use them as a ping pong test.
 * Process A:
 *	lock(1)
 *	unlock(2)
 * Process B:
 *	unlock(1)
 *	lock(2)
 * Initial state:
 *	lock is locked
 *	lock2 is locked
 */

#define	waiton(fd)	fcntl(fd, F_SETLKW, &lock)
#define	release(fd)	fcntl(fd, F_SETLK, &unlock)

I 3
struct _state {
	char filename1[2048];
	char filename2[2048];
	int	pid;
	int	fd1;
	int	fd2;
};

void initialize(void* cookie);
D 5
void benchmark(uint64 iterations, void* cookie);
E 5
I 5
void benchmark(iter_t iterations, void* cookie);
E 5
void cleanup(void* cookie);

I 6
D 7
struct _state* pGlobalState;

void
sigterm_handler(int n)
{
	if (pGlobalState->pid) {
		kill(SIGKILL, pGlobalState->pid);
	}
	exit(0);
}

E 7
E 6
E 3
void
D 3
procA()
E 3
I 3
procA(struct _state *state)
E 3
{
D 3
	if (waiton(fd1) == -1) {
E 3
I 3
	if (waiton(state->fd1) == -1) {
E 3
		perror("lock of fd1 failed\n");
I 3
		cleanup(state);
E 3
		exit(1);
	}
D 3
	if (release(fd2) == -1) {
E 3
I 3
	if (release(state->fd2) == -1) {
E 3
		perror("unlock of fd2 failed\n");
I 3
		cleanup(state);
E 3
		exit(1);
	}
D 3
	if (waiton(fd2) == -1) {
E 3
I 3
	if (waiton(state->fd2) == -1) {
E 3
		perror("lock of fd2 failed\n");
I 3
		cleanup(state);
E 3
		exit(1);
	}
D 3
	if (release(fd1) == -1) {
E 3
I 3
	if (release(state->fd1) == -1) {
E 3
		perror("unlock of fd1 failed\n");
I 3
		cleanup(state);
E 3
		exit(1);
	}
}

void
D 3
procB()
E 3
I 3
procB(struct _state *state)
E 3
{
D 3
	if (release(fd1) == -1) {
E 3
I 3
	if (release(state->fd1) == -1) {
E 3
		perror("unlock of fd1 failed\n");
I 3
		cleanup(state);
E 3
		exit(1);
	}
D 3
	if (waiton(fd2) == -1) {
E 3
I 3
	if (waiton(state->fd2) == -1) {
E 3
		perror("lock of fd2 failed\n");
I 3
		cleanup(state);
E 3
		exit(1);
	}
D 3
	if (waiton(fd1) == -1) {
		perror("lock of fd1 failed\n");
E 3
I 3
	if (release(state->fd2) == -1) {
		perror("unlock of fd2 failed\n");
		cleanup(state);
E 3
		exit(1);
	}
D 3
	if (release(fd2) == -1) {
		perror("unlock of fd2 failed\n");
E 3
I 3
	if (waiton(state->fd1) == -1) {
		perror("lock of fd1 failed\n");
		cleanup(state);
E 3
		exit(1);
	}
}

D 3
int
main()
E 3
I 3
void 
initialize(void* cookie)
E 3
{
D 3
	char	buf[10000];
E 3
D 7
	int	pid;
E 7
I 3
	char	buf[10000];
	struct _state* state = (struct _state*)cookie;

	sprintf(state->filename1, "/tmp/lmbench-fcntl%d.1", getpid());
	sprintf(state->filename2, "/tmp/lmbench-fcntl%d.2", getpid());
E 3

D 3
	unlink("/tmp/lmbench-fcntl.1");
	unlink("/tmp/lmbench-fcntl.2");
	if ((fd1 = open("/tmp/lmbench-fcntl.1", O_CREAT|O_RDWR, 0666)) == -1) {
E 3
I 3
	unlink(state->filename1);
	unlink(state->filename2);
	if ((state->fd1 = open(state->filename1, O_CREAT|O_RDWR, 0666)) == -1) {
E 3
		perror("create");
		exit(1);
	}
D 3
	if ((fd2 = open("/tmp/lmbench-fcntl.2", O_CREAT|O_RDWR, 0666)) == -1) {
E 3
I 3
	if ((state->fd2 = open(state->filename2, O_CREAT|O_RDWR, 0666)) == -1) {
E 3
		perror("create");
		exit(1);
	}
I 8
	unlink(state->filename1);
	unlink(state->filename2);
E 8
D 3
	write(fd1, buf, sizeof(buf));
	write(fd2, buf, sizeof(buf));
E 3
I 3
	write(state->fd1, buf, sizeof(buf));
	write(state->fd2, buf, sizeof(buf));
E 3
	lock.l_type = F_WRLCK;
	lock.l_whence = 0;
	lock.l_start = 0;
	lock.l_len = 1;
	unlock = lock;
	unlock.l_type = F_UNLCK;
D 3
	if (waiton(fd1) == -1) {
E 3
I 3
	if (waiton(state->fd1) == -1) {
E 3
		perror("lock1");
		exit(1);
	}
D 3
	if (waiton(fd2) == -1) {
E 3
I 3
	if (waiton(state->fd2) == -1) {
E 3
		perror("lock2");
		exit(1);
	}
D 3
	if (fork()) {
		wait(0);
	}
	pid = fork();
	if (pid == -1) {
E 3
I 3
D 7
	state->pid = getpid();
	switch (pid = fork()) {
E 7
I 7
	switch (state->pid = fork()) {
E 7
	case -1:
E 3
		perror("fork");
		exit(1);
D 3
	}
	if (pid > 0) {
		waiton(fd1);
		BENCH(procA(), SHORT);
		micro("Fcntl lock latency", get_n());
		kill(pid, 15);
	} else {
		waiton(fd2);
E 3
I 3
	case 0:
E 3
		for ( ;; ) {
D 3
			procB();
E 3
I 3
			procB(state);
E 3
		}
I 3
		exit(0);
	default:
D 7
		state->pid = pid;
E 7
		break;
E 3
	}
I 8
	exit(0);
E 8
I 3
}

void
D 5
benchmark(uint64 iterations, void* cookie)
E 5
I 5
benchmark(iter_t iterations, void* cookie)
E 5
{
	struct _state* state = (struct _state*)cookie;
D 5
	uint64	i;
E 5
	
D 5
	for (i = 0; i < iterations; ++i) {
E 5
I 5
	while (iterations-- > 0) {
E 5
		procA(state);
	}
}

D 7
void cleanup(void* cookie)
E 7
I 7
void
cleanup(void* cookie)
E 7
{
	int i;
	struct _state* state = (struct _state*)cookie;

	close(state->fd1);
	close(state->fd2);

D 8
	unlink(state->filename1);
	unlink(state->filename2);

E 8
D 6
	kill(state->pid, 9);
E 6
I 6
D 7
	kill(state->pid, SIGKILL);
E 7
I 7
	if (state->pid) kill(state->pid, SIGKILL);
E 7
	state->pid = 0;
E 6
}

int
main(int ac, char **av)
{
	int	i;
	int	c;
	int	parallel = 1;
I 4
	int	warmup = 0;
	int	repetitions = TRIES;
E 4
	struct _state state;
D 4
	char *usage = "[-P <parallelism>]\n";
E 4
I 4
	char *usage = "[-P <parallelism>] [-W <warmup>] [-N <repetitions>]\n";
E 4

	/*
	 * If they specified a parallelism level, get it.
	 */
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
I 6

	state.pid = 0;
D 7
	pGlobalState = &state;
	signal(SIGTERM, sigterm_handler);
E 7
E 6

D 4
	benchmp(initialize, benchmark, cleanup, 0, parallel, &state);
E 4
I 4
	benchmp(initialize, benchmark, cleanup, 0, parallel, 
		warmup, repetitions, &state);
E 4
D 8
	micro("Fcntl lock latency", get_n());
E 8
I 8
	micro("Fcntl lock latency", 2 * get_n());
E 8

E 3
	return (0);
}
E 2
I 1
E 1
