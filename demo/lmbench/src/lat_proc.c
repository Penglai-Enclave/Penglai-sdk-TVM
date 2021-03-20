/*
 * lat_proc.c - process creation tests
 *
 * Usage: lat_proc [-P <parallelism] [-W <warmup>] [-N <repetitions>] procedure|fork|exec|shell
 *
 * TODO - linux clone, plan9 rfork, IRIX sproc().
 *
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
char	*id = "$Id$\n";

#include "bench.h"


#ifdef STATIC
#define	PROG "/tmp/hello-s"
#define STATIC_PREFIX "Static "
#else
#define	PROG "/tmp/hello"
#define STATIC_PREFIX ""
#endif

void do_shell(iter_t iterations, void* cookie);
void do_forkexec(iter_t iterations,void* cookie);
void do_fork(iter_t iterations, void* cookie);
void do_procedure(iter_t iterations, void* cookie);

pid_t child_pid;

void
initialize(void* cookie)
{
/*	signal(SIGCHLD, SIG_IGN); */
}

void
cleanup(void* cookie)
{
	if (child_pid)
		kill(SIGKILL, child_pid);
}
	
int
main(int ac, char **av)
{
	int parallel = 1;
	int warmup = 0;
	int repetitions = TRIES;
	int c;
	char* usage = "[-P <parallelism>] [-W <warmup>] [-N <repetitions>] procedure|fork|exec|shell\n";

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

	if (optind + 1 != ac) { /* should have one argument left */
		lmbench_usage(ac, av, usage);
	}

	if (!strcmp("procedure", av[optind])) {
		benchmp(initialize, do_procedure, cleanup, 0, parallel, 
			warmup, repetitions, &ac);
		micro("Procedure call", get_n());
	} else if (!strcmp("fork", av[optind])) {
		benchmp(initialize, do_fork, cleanup, 0, parallel, 
			warmup, repetitions, NULL);
		micro(STATIC_PREFIX "Process fork+exit", get_n());
	} else if (!strcmp("exec", av[optind])) {
		benchmp(initialize, do_forkexec, cleanup, 0, parallel,
			warmup, repetitions, NULL);
		micro(STATIC_PREFIX "Process fork+execve", get_n());
	} else if (!strcmp("shell", av[optind])) {
		benchmp(initialize, do_shell, cleanup, 0, parallel,
			warmup, repetitions, NULL);
		micro(STATIC_PREFIX "Process fork+/bin/sh -c", get_n());
	} else {
		lmbench_usage(ac, av, usage);
	}
	return(0);
}

void 
do_shell(iter_t iterations, void* cookie)
{
	while (iterations-- > 0) {
		switch (child_pid = fork()) {
		case -1:
			perror("fork");
			exit(1);
	    
		case 0:	/* child */
			close(1);
			execlp("/bin/sh", "sh", "-c", PROG, 0);
			exit(1);

		default:
			while (wait(0) != child_pid)
				;
		}
		child_pid = 0;
	}
}

void 
do_forkexec(iter_t iterations, void* cookie)
{
	char	*nav[2];

	while (iterations-- > 0) {
		nav[0] = PROG;
		nav[1] = 0;
		switch (child_pid = fork()) {
		case -1:
			perror("fork");
			exit(1);

		case 0: 	/* child */
			close(1);
			execve(PROG, nav, 0);
			exit(1);

		default:
			while (wait(0) != child_pid)
				;
		}
		child_pid = 0;
	}
}
	
void 
do_fork(iter_t iterations, void* cookie)
{
	while (iterations-- > 0) {
		switch (child_pid = fork()) {
		case -1:
			perror("fork");
			exit(1);
	
		case 0:	/* child */
			exit(1);
	
		default:
			while (wait(0) != child_pid)
				;
			child_pid = 0;
		}
	}
}
	
void 
do_procedure(iter_t iterations, void* cookie)
{
	int r = *(int *) cookie;
	while (iterations-- > 0) {
		use_int(r);
	}
}
