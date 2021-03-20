h57968
s 00155/00000/00000
d D 1.1 00/10/16 17:23:03 staelin 2 1
cC
cF1
cK28712
cO-rw-rw-r--
e
s 00000/00000/00000
d D 1.0 00/10/16 17:23:03 staelin 1 0
c BitKeeper file /tmp_mnt/usr/WebPaper/users/staelin/src/LMbench/src/lat_sem.c
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHhpli8.hpli.hpl.hp.com
cK11351
cPsrc/lat_sem.c
cR2a13388119005bf8
cV4
cX0xa1
cZ+02:00
e
u
U
f e 0
f x 0xa1
t
T
I 2
/*
 * lat_sem.c - semaphore test
 *
 * usage: lat_sem [-P <parallelism>] [-W <warmup>] [-N <repetitions>]
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
#include <sys/sem.h>

void initialize(void *cookie);
void cleanup(void *cookie);
void doit(iter_t iterations, void *cookie);
void writer(int sid);

typedef struct _state {
	int	pid;
	int	semid;
} state_t;

int 
main(int ac, char **av)
{
	state_t state;
	int parallel = 1;
	int warmup = 0;
	int repetitions = TRIES;
	int c;
	char* usage = "[-P <parallelism>] [-W <warmup>] [-N <repetitions>]\n";

	while (( c = getopt(ac, av, "P:W:N:")) != EOF) {
		switch(c) {
		case 'P':
			parallel = atoi(optarg);
			if (parallel <= 0) lmbench_usage(ac, av, usage);
			break;
		case 'W':
			warmup = atoi(optarg);
			break;
		case 'N':
			repetitions = atoi(optarg);
			break;
		default:
			lmbench_usage(ac, av, usage);
			break;
		}
	}
	if (optind < ac) {
		lmbench_usage(ac, av, usage);
	}

	state.pid = 0;

	benchmp(initialize, doit, cleanup, SHORT, parallel, 
		warmup, repetitions, &state);
	micro("Semaphore latency", get_n() * 2);
	return (0);
}

void 
initialize(void *cookie)
{
	char	c;
	state_t * state = (state_t *)cookie;

	state->semid = semget(IPC_PRIVATE, 2, IPC_CREAT | IPC_EXCL | 0600);
	semctl(state->semid, 0, SETVAL, 0);
	semctl(state->semid, 1, SETVAL, 0);

	switch (state->pid = fork()) {
	    case 0:
		signal(SIGTERM, exit);
		writer(state->semid);
		return;

	    case -1:
		perror("fork");
		return;

	    default:
		break;
	}
}

void 
cleanup(void * cookie)
{
	state_t * state = (state_t *)cookie;

	signal(SIGCHLD, SIG_IGN);
	if (state->pid) {
		kill(state->pid, SIGKILL);
	}
	/* free the semaphores */
	semctl(state->semid, 0, IPC_RMID);
}

void 
doit(register iter_t iterations, void *cookie)
{
	state_t *state = (state_t *) cookie;
	struct sembuf sop[2];

	sop[0].sem_num = 1;
	sop[0].sem_op = -1;
	sop[0].sem_flg = 0;

	sop[1].sem_num = 0;
	sop[1].sem_op = 1;
	sop[1].sem_flg = 0;

	while (iterations-- > 0) {
		if (semop(state->semid, sop, 2) < 0) {
			perror("(r) error on semaphore");
			exit(1);
		}
	}
}

void 
writer(register int sid)
{
	struct sembuf sop[2];

	sop[0].sem_num = 1;
	sop[0].sem_op = 1;
	sop[0].sem_flg = 0;

	if (semop(sid, sop, 1) < 0) {
		perror("(w) error on initial semaphore");
		exit(1);
	}

	sop[0].sem_num = 0;
	sop[0].sem_op = -1;
	sop[0].sem_flg = 0;

	sop[1].sem_num = 1;
	sop[1].sem_op = 1;
	sop[1].sem_flg = 0;

	for ( ;; ) {
		if (semop(sid, sop, 2) < 0) {
			perror("(w) error on semaphore");
			exit(1);
		}
	}
}
E 2
I 1
E 1
