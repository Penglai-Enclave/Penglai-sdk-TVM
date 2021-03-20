h19127
s 00014/00010/00161
d D 1.20 00/09/18 11:34:15 staelin 21 20
c - Fix bug in SIGCHLD handling which was causing an infinite loop in lat_proc
cC
cK15061
e
s 00061/00047/00110
d D 1.19 00/08/02 18:05:00 staelin 20 19
c - Add code to deal with killing child processes when signaled by the parent so we don't
c   leave zombies lying around...
cC
cK08930
e
s 00008/00008/00149
d D 1.18 00/07/30 11:46:11 staelin 19 18
c - Change type of "iterations" from uint64 to iter_t, which is a u_long
cC
cK61616
e
s 00019/00010/00138
d D 1.17 00/07/04 14:55:56 staelin 18 17
c - Update to incorporate new "-W <warmup>" and "-N <repetitions>" flags
cC
cHhpli8.hpli.hpl.hp.com
cK60872
cZ+03:00
e
s 00004/00004/00144
d D 1.16 00/03/09 18:24:53 brucec 17 16
c Fix incorrect argument handling introduced in last changeset.
cC
cK40809
e
s 00087/00062/00061
d D 1.15 00/03/06 18:14:30 brucec 16 15
c Make it a parallel ("-P <parallelism>") test case.
cC
cHrx7
cK38389
cZ-05:00
e
s 00009/00001/00114
d D 1.14 99/09/02 22:47:47 lm 15 14
c Add "procedure" test
cC
cHwork.bitmover.com
cK26654
e
s 00004/00004/00111
d D 1.13 97/06/15 22:38:58 lm 14 13
c lint
cK14545
cSAlpha2.11
e
s 00021/00032/00094
d D 1.12 97/06/12 21:30:06 lm 13 12
c new bench.h macros.
cK13013
e
s 00037/00023/00089
d D 1.11 97/04/23 22:06:38 lm 12 11
c new timing loop. New interface: lat_proc fork|exec|shell
cK25685
cZ-07:00
e
s 00013/00000/00099
d D 1.10 97/02/12 21:00:28 lm 11 10
c popen.
cK12020
e
s 00006/00006/00093
d D 1.9 96/11/21 17:48:04 lm 10 9
c 100 -> N
cK64372
e
s 00042/00047/00057
d D 1.8 96/11/11 03:36:51 lm 9 8
c Auto adjusting changes.
cK64784
e
s 00006/00002/00098
d D 1.7 96/11/08 20:00:28 lm 8 7
c gcc -Wall cleanup.
cK62554
cZ-08:00
e
s 00000/00001/00100
d D 1.6 96/05/30 00:33:07 lm 7 6
c no what strings
cK54208
cZ-07:00
e
s 00019/00026/00082
d D 1.5 95/11/07 17:40:21 lm 6 5
c static
cK56279
cZ-08:00
e
s 00002/00000/00106
d D 1.4 95/10/02 17:13:52 lm 5 4
c static isn't portable.
cK59946
e
s 00022/00000/00084
d D 1.3 95/09/25 22:52:07 lm 4 3
c adding statically linked version.
cK58026
cZ-07:00
e
s 00003/00003/00081
d D 1.2 95/02/14 10:59:54 lm 3 2
c Execute programs out of /tmp (should be local).
cK35353
e
s 00084/00000/00000
d D 1.1 94/11/18 00:49:48 lm 2 1
c Initial revision
cK34246
e
s 00000/00000/00000
d D 1.0 94/11/18 00:49:47 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK49449
cPsrc/lat_proc.c
cR67978a001d538da6
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
 * lat_proc.c - process creation tests
 *
D 16
 * Usage: lat_proc
E 16
I 16
D 18
 * Usage: lat_proc [-P <parallelism] procedure|fork|exec|shell
E 18
I 18
 * Usage: lat_proc [-P <parallelism] [-W <warmup>] [-N <repetitions>] procedure|fork|exec|shell
E 18
E 16
 *
I 8
 * TODO - linux clone, plan9 rfork, IRIX sproc().
 *
E 8
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
char	*id = "$Id$\n";

D 9
#include	"timing.c"
I 8
#include	<sys/types.h>
#include	<sys/wait.h>
E 9
I 9
D 13
#include "timing.h"
E 13
#include "bench.h"
D 13
#include <sys/types.h>
#include <sys/wait.h>
E 13
E 9
E 8

I 16

E 16
I 6
#ifdef STATIC
#define	PROG "/tmp/hello-s"
I 16
#define STATIC_PREFIX "Static "
E 16
#else
#define	PROG "/tmp/hello"
I 16
#define STATIC_PREFIX ""
E 16
#endif
E 6

D 8
main(ac, av)
	char	**av;
E 8
I 8
D 12
int
main(int ac, char **av)
E 12
I 12
D 14
void do_shell()
E 14
I 14
D 16
void do_shell(void)
E 16
I 16
D 19
void do_shell(uint64 iterations, void* cookie);
void do_forkexec(uint64 iterations,void* cookie);
void do_fork(uint64 iterations, void* cookie);
void do_procedure(uint64 iterations, void* cookie);
E 19
I 19
void do_shell(iter_t iterations, void* cookie);
void do_forkexec(iter_t iterations,void* cookie);
void do_fork(iter_t iterations, void* cookie);
void do_procedure(iter_t iterations, void* cookie);
I 20

pid_t child_pid;

void
D 21
sigterm_handler(int n)
E 21
I 21
initialize(void* cookie)
{
/*	signal(SIGCHLD, SIG_IGN); */
}

void
cleanup(void* cookie)
E 21
{
	if (child_pid)
		kill(SIGKILL, child_pid);
D 21
	exit(0);
E 21
}
E 20
E 19
	
int
main(int ac, char **av)
E 16
E 14
E 12
E 8
{
D 9
	int	i, pid;
E 9
I 9
D 13
	int	N, i, pid;
E 13
I 13
D 16
	int	pid;
E 16
I 16
	int parallel = 1;
I 18
	int warmup = 0;
	int repetitions = TRIES;
E 18
	int c;
D 18
	char* usage = "[-P <parallelism>] procedure|fork|exec|shell\n";
E 18
I 18
	char* usage = "[-P <parallelism>] [-W <warmup>] [-N <repetitions>] procedure|fork|exec|shell\n";
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
E 16
E 13
E 9
D 12
	char	*nav[2];
I 11
	FILE	*p;
	char	cmd[100];
E 12
E 11

D 7
	write(2, id, strlen(id));
E 7
D 9
	start();
	for (i = 0; i < 600; ++i) {
		switch (pid = fork()) {
		    case -1:
			perror("fork");
			exit(1);
E 9
I 9
D 13
	LOOP_FIRST(N, i, ENOUGH);
E 13
D 16
	switch (pid = fork()) {
	    case -1:
		perror("fork");
		exit(1);
E 16
I 16
	if (optind + 1 != ac) { /* should have one argument left */
		lmbench_usage(ac, av, usage);
	}

I 20
D 21
	signal(SIGTERM, sigterm_handler);

E 21
E 20
D 18
#define NOINIT NULL
#define NOCLEANUP NULL

E 18
D 17
	if (!strcmp("procedure", av[1])) {
E 17
I 17
	if (!strcmp("procedure", av[optind])) {
E 17
D 18
		benchmp(NOINIT,do_procedure,NOCLEANUP, 0, parallel, &ac);
E 18
I 18
D 21
		benchmp(NULL, do_procedure, NULL, 0, parallel, 
E 21
I 21
		benchmp(initialize, do_procedure, cleanup, 0, parallel, 
E 21
			warmup, repetitions, &ac);
E 18
		micro("Procedure call", get_n());
D 17
	} else if (!strcmp("fork", av[1])) {
E 17
I 17
	} else if (!strcmp("fork", av[optind])) {
E 17
D 18
		benchmp(NOINIT,do_fork,NOCLEANUP, 0, parallel, NULL);
E 18
I 18
D 21
		benchmp(NULL, do_fork, NULL, 0, parallel, 
E 21
I 21
		benchmp(initialize, do_fork, cleanup, 0, parallel, 
E 21
			warmup, repetitions, NULL);
E 18
		micro(STATIC_PREFIX "Process fork+exit", get_n());
D 17
	} else if (!strcmp("exec", av[1])) {
E 17
I 17
	} else if (!strcmp("exec", av[optind])) {
E 17
D 18
		benchmp(NOINIT,do_forkexec,NOCLEANUP,0,parallel,NULL);
E 18
I 18
D 21
		benchmp(NULL, do_forkexec, NULL, 0, parallel,
E 21
I 21
		benchmp(initialize, do_forkexec, cleanup, 0, parallel,
E 21
			warmup, repetitions, NULL);
E 18
		micro(STATIC_PREFIX "Process fork+execve", get_n());
D 17
	} else if (!strcmp("shell", av[1])) {
E 17
I 17
	} else if (!strcmp("shell", av[optind])) {
E 17
D 18
		benchmp(NOINIT,do_shell,NOCLEANUP,0,parallel,NULL);
E 18
I 18
D 21
		benchmp(NULL, do_shell, NULL, 0, parallel,
E 21
I 21
		benchmp(initialize, do_shell, cleanup, 0, parallel,
E 21
			warmup, repetitions, NULL);
E 18
		micro(STATIC_PREFIX "Process fork+/bin/sh -c", get_n());
	} else {
		lmbench_usage(ac, av, usage);
	}
	return(0);
}
E 16
E 9

I 16
D 19
void do_shell(uint64 iterations, void* cookie)
E 19
I 19
D 20
void do_shell(iter_t iterations, void* cookie)
E 20
I 20
void 
do_shell(iter_t iterations, void* cookie)
E 20
E 19
{
D 20
	int	pid;
E 20
	while (iterations-- > 0) {
D 20
	  switch (pid = fork()) {
	    case -1:
	      perror("fork");
	      exit(1);
E 20
I 20
		switch (child_pid = fork()) {
		case -1:
			perror("fork");
			exit(1);
E 20
	    
E 16
D 9
		    case 0:	/* child */
			exit(1);
E 9
I 9
D 20
	    case 0:	/* child */
I 12
D 16
		close(1);
		execlp("/bin/sh", "sh", "-c", PROG, 0);
E 12
		exit(1);
E 16
I 16
	      close(1);
	      execlp("/bin/sh", "sh", "-c", PROG, 0);
	      exit(1);
E 16
E 9

D 9
		    default:
			while (wait(0) != pid)
				;
		}
E 9
I 9
	    default:
D 16
		while (wait(0) != pid)
D 12
		    ;
E 12
I 12
			;
E 16
I 16
	      while (wait(0) != pid)
		;
	  }
E 20
I 20
		case 0:	/* child */
			close(1);
			execlp("/bin/sh", "sh", "-c", PROG, 0);
			exit(1);

		default:
			while (wait(0) != child_pid)
				;
		}
		child_pid = 0;
E 20
E 16
E 12
E 9
	}
D 9
	stop();
E 9
I 9
D 13
	LOOP_LAST(N, i, ENOUGH);
E 9
I 6
#ifdef STATIC
D 10
	micro("Static Process fork+exit", 600);
E 10
I 10
D 12
	micro("Static Process fork+exit", N);
E 12
I 12
	micro("Static Process fork+/bin/sh -c", N);
E 12
E 10
#else
E 6
D 10
	micro("Process fork+exit", 600);
E 10
I 10
D 12
	micro("Process fork+exit", N);
E 12
I 12
	micro("Process fork+/bin/sh -c", N);
E 12
E 10
D 6
	
I 5
#ifdef not_yet
E 5
I 4
	nav[0] = "/tmp/hello-s";
	nav[1] = 0;
	start();
	for (i = 0; i < 100; ++i) {
		switch (pid = fork()) {
		    case -1:
			perror("fork");
			exit(1);

		    case 0: 	/* child */
			close(1);
		    	execve("/tmp/hello-s", nav, 0);
			exit(1);

		    default:
			while (wait(0) != pid)
				;
		}
	}
	stop();
	micro("Process fork+execve static", 100);
E 6
I 5
#endif
E 5
D 12
	
E 12
I 12
	exit(0);
E 13
}

D 14
void do_forkexec()
E 14
I 14
D 16
void do_forkexec(void)
E 16
I 16
D 19
void do_forkexec(uint64 iterations,void* cookie)
E 19
I 19
D 20
void do_forkexec(iter_t iterations,void* cookie)
E 20
I 20
void 
do_forkexec(iter_t iterations, void* cookie)
E 20
E 19
E 16
E 14
{
D 13
	int	N, i, pid;
E 13
I 13
D 20
	int	pid;
E 20
E 13
	char	*nav[2];

E 12
E 4
D 3
	nav[0] = "hello";
E 3
I 3
D 6
	nav[0] = "/tmp/hello";
E 6
I 6
D 16
	nav[0] = PROG;
E 6
E 3
	nav[1] = 0;
D 9
	start();
	for (i = 0; i < 100; ++i) {
		switch (pid = fork()) {
		    case -1:
			perror("fork");
			exit(1);
E 9
I 9
D 13
	LOOP_FIRST(N, i, ENOUGH);
E 13
	switch (pid = fork()) {
E 16
I 16
	while (iterations-- > 0) {
D 20
	  nav[0] = PROG;
	  nav[1] = 0;
	  switch (pid = fork()) {
E 16
	    case -1:
		perror("fork");
		exit(1);
E 9

D 9
		    case 0: 	/* child */
			close(1);
D 3
		    	execve("./hello", nav, 0);
E 3
I 3
D 6
		    	execve("/tmp/hello", nav, 0);
E 6
I 6
		    	execve(PROG, nav, 0);
E 6
E 3
			exit(1);
E 9
I 9
	    case 0: 	/* child */
		close(1);
		execve(PROG, nav, 0);
		exit(1);
E 9

D 9
		    default:
			while (wait(0) != pid)
				;
		}
E 9
I 9
	    default:
		while (wait(0) != pid)
			;
I 16
	  }
E 20
I 20
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
E 20
E 16
E 9
	}
I 11
D 13

E 11
D 9
	stop();
E 9
I 9
	LOOP_LAST(N, i, ENOUGH);
E 9
I 6
#ifdef STATIC
D 10
	micro("Static Process fork+execve", 100);
E 10
I 10
	micro("Static Process fork+execve", N);
E 10
#else
E 6
D 10
	micro("Process fork+execve", 100);
E 10
I 10
	micro("Process fork+execve", N);
E 10
I 6
#endif
E 13
I 12
}
E 12
E 6
	
D 9
	start();
	for (i = 0; i < 100; ++i) {
		switch (pid = fork()) {
		    case -1:
			perror("fork");
			exit(1);
E 9
I 9
D 12
	LOOP_FIRST(N, i, ENOUGH);
I 11
	p = popen(PROG, "r");
	pclose(p);
	LOOP_LAST(N, i, ENOUGH);
#ifdef STATIC
	micro("Static popen", N);
#else
	micro("popen", N);
#endif
E 12
I 12
D 14
void do_fork()
E 14
I 14
D 16
void do_fork(void)
E 16
I 16
D 19
void do_fork(uint64 iterations, void* cookie)
E 19
I 19
D 20
void do_fork(iter_t iterations, void* cookie)
E 20
I 20
void 
do_fork(iter_t iterations, void* cookie)
E 20
E 19
E 16
E 14
{
D 13
	int	N, i, pid;
E 13
I 13
D 16
	int	pid;
E 16
I 16
D 20
	int pid;
	int i;
E 16
E 13
E 12

E 20
D 13
	LOOP_FIRST(N, i, ENOUGH);
E 13
E 11
D 16
	switch (pid = fork()) {
E 16
I 16
	while (iterations-- > 0) {
D 20
	  switch (pid = fork()) {
E 16
	    case -1:
D 16
		perror("fork");
		exit(1);
E 9

E 16
I 16
	      perror("fork");
	      exit(1);
E 20
I 20
		switch (child_pid = fork()) {
		case -1:
			perror("fork");
			exit(1);
E 20
	
E 16
D 9
		    case 0:	/* child */
			close(1);
D 3
		    	execlp("/bin/sh", "sh", "-c", "./hello", 0);
E 3
I 3
D 6
		    	execlp("/bin/sh", "sh", "-c", "/tmp/hello", 0);
E 6
I 6
		    	execlp("/bin/sh", "sh", "-c", PROG, 0);
E 6
E 3
			exit(1);
E 9
I 9
D 20
	    case 0:	/* child */
D 12
		close(1);
		execlp("/bin/sh", "sh", "-c", PROG, 0);
E 12
D 16
		exit(1);
E 9

E 16
I 16
	      exit(1);
E 20
I 20
		case 0:	/* child */
			exit(1);
E 20
	
E 16
D 9
		    default:
			while (wait(0) != pid)
				;
		}
E 9
I 9
D 20
	    default:
D 16
		while (wait(0) != pid)
D 12
			;
E 12
I 12
		    ;
E 16
I 16
	      while (wait(0) != pid);
	  }
E 20
I 20
		default:
D 21
			while (wait(0) != child_pid);
E 21
I 21
			while (wait(0) != child_pid)
				;
			child_pid = 0;
E 21
		}
D 21
		child_pid = 0;
E 21
E 20
E 16
E 12
E 9
	}
D 9
	stop();
E 9
I 9
D 13
	LOOP_LAST(N, i, ENOUGH);
E 9
I 6
#ifdef STATIC
D 10
	micro("Static Process fork+/bin/sh -c", 100);
E 10
I 10
D 12
	micro("Static Process fork+/bin/sh -c", N);
E 12
I 12
	micro("Static Process fork+exit", N);
E 12
E 10
#else
E 6
D 10
	micro("Process fork+/bin/sh -c", 100);
E 10
I 10
D 12
	micro("Process fork+/bin/sh -c", N);
E 12
I 12
	micro("Process fork+exit", N);
E 12
E 10
I 6
#endif
E 13
I 12
}
	
I 15
D 16
void do_procedure(int r)
E 16
I 16
D 19
void do_procedure(uint64 iterations, void* cookie)
E 19
I 19
D 20
void do_procedure(iter_t iterations, void* cookie)
E 20
I 20
void 
do_procedure(iter_t iterations, void* cookie)
E 20
E 19
E 16
{
D 16
	use_int(r);
}
	
E 15
int
main(int ac, char **av)
{
	if (ac < 2) goto usage;

D 15
	if (!strcmp("fork", av[1])) {
E 15
I 15
	if (!strcmp("procedure", av[1])) {
		BENCH(do_procedure(ac), 0);
		micro("Procedure call", get_n());
	} else if (!strcmp("fork", av[1])) {
E 15
D 13
		do_fork();
E 13
I 13
		BENCH(do_fork(), 0);
#ifdef STATIC
		micro("Static Process fork+exit", get_n());
#else
		micro("Process fork+exit", get_n());
#endif
E 13
	} else if (!strcmp("exec", av[1])) {
D 13
		do_forkexec();
E 13
I 13
		BENCH(do_forkexec(), 0);
#ifdef STATIC
		micro("Static Process fork+execve", get_n());
#else
		micro("Process fork+execve", get_n());
#endif
E 13
	} else if (!strcmp("shell", av[1])) {
D 13
		do_shell();
E 13
I 13
		BENCH(do_shell(), 0);
#ifdef STATIC
		micro("Static Process fork+/bin/sh -c", get_n());
#else
		micro("Process fork+/bin/sh -c", get_n());
#endif
E 13
	} else {
usage:		printf("Usage: %s fork|exec|shell\n", av[0]);
E 16
I 16
	int r = *(int *) cookie;
	while (iterations-- > 0) {
		use_int(r);
E 16
	}
E 12
E 6
D 14
	exit(0);
E 14
I 14
D 16
	return(0);
E 16
E 14
}
E 2
I 1
E 1
