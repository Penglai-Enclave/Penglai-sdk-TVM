h49129
s 00005/00007/00115
d D 1.14 00/10/16 17:21:27 staelin 15 14
c - Assorted code cleanups
cC
cK14728
cZ+02:00
e
s 00007/00018/00115
d D 1.13 00/08/16 09:29:18 staelin 14 13
c - Change/fix SIGTERM handling to make it more robust and generic
cC
cK21832
e
s 00016/00000/00117
d D 1.12 00/08/02 18:05:01 staelin 13 12
c - Add code to deal with killing child processes when signaled by the parent so we don't
c   leave zombies lying around...
cC
cK36895
e
s 00002/00002/00115
d D 1.11 00/07/30 11:46:15 staelin 12 11
c - Change type of "iterations" from uint64 to iter_t, which is a u_long
cC
cK19340
e
s 00005/00004/00112
d D 1.10 00/07/05 10:26:01 staelin 11 10
c - fix bug where data space was not allocated for client
cC
cK19154
e
s 00031/00013/00085
d D 1.9 00/07/04 14:56:00 staelin 10 9
c - Update to incorporate new "-W <warmup>" and "-N <repetitions>" flags
cC
cHhpli8.hpli.hpl.hp.com
cK17462
cZ+03:00
e
s 00019/00001/00079
d D 1.8 00/03/06 18:14:30 brucec 9 8
c Add command line parsing for parallel test case.
cC
cHrx7
cK34282
cZ-05:00
e
s 00046/00026/00034
d D 1.7 00/02/23 11:15:39 staelin 8 7
c Convert to use new draft benchmp() timing harness.
cC
cHhpli8.hpli.hpl.hp.com
cK08088
cZ+02:00
e
s 00001/00001/00059
d D 1.6 97/06/15 22:38:58 lm 7 6
c lint
cC
cK23557
cSAlpha2.11
e
s 00003/00008/00057
d D 1.5 97/06/12 21:30:06 lm 6 5
c new bench.h macros.
cK23327
cZ-07:00
e
s 00007/00012/00058
d D 1.4 96/11/11 03:36:51 lm 5 4
c Auto adjusting changes.
cK29884
e
s 00012/00006/00058
d D 1.3 96/11/08 20:04:09 lm 4 3
c gcc -Wall cleanup.
cK33166
cZ-08:00
e
s 00000/00001/00064
d D 1.2 96/05/30 00:33:07 lm 3 2
c no what strings
cK27161
e
s 00065/00000/00000
d D 1.1 96/05/22 00:33:03 lm 2 1
c Initial revision
cK29232
e
s 00000/00000/00000
d D 1.0 96/05/22 00:33:02 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK07499
cPsrc/lat_unix.c
cR60b40b303e5dd5e0
cV4
cX0x21
cZ-07:00
e
u
U
f e 0
f x 0x21
t
AF_UNIX measurements.
T
I 2
/*
D 15
 * tcp_xact.c - simple TCP transaction latency test
E 15
I 15
 * tcp_unix.c - simple UNIX socket transaction latency test
E 15
 *
D 15
 * Three programs in one -
D 10
 *	server usage:	tcp_xact -s
 *	client usage:	tcp_xact hostname
D 4
 *	shutdown:	tcp_xact -hostname
E 4
I 4
 *	shutwn:	tcp_xact -hostname
E 10
I 10
 *	server usage:	lat_unix -s
 *	client usage:	lat_unix [-P <parallelism>] [-W <warmup>] [-N <repetitions>] hostname
 *	shutdown:	lat_unix -S hostname
E 15
I 15
 *	lat_unix [-P <parallelism>] [-W <warmup>] [-N <repetitions>]
E 15
E 10
E 4
 *
D 15
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
E 15
I 15
 * Copyright (c) 1994-2000 Carl Staelin and Larry McVoy.  
 * Distributed under the FSF GPL with additional restriction that 
 * results may published only if
E 15
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
char	*id = "$Id$\n";
I 5
D 6
#include "timing.h"
E 6
E 5
#include "bench.h"
D 5
#include "timing.c"
E 5
D 6
#include <sys/socket.h>
E 6
D 5
#define	N	10000
E 5

D 4
main()
E 4
I 4
D 8
void	client(int sock);
void	server(int sock);
E 8
I 8
struct _state {
	int	sv[2];
	int	pid;
I 10
	int	msize;
	char*	buf;
E 10
};
void	initialize(void* cookie);
D 12
void	benchmark(uint64 iterations, void* cookie);
E 12
I 12
void	benchmark(iter_t iterations, void* cookie);
E 12
void	cleanup(void* cookie);
E 8

I 13
D 14
struct _state* pGlobalState;

void
sigterm_handler(int n)
{
	if (pGlobalState->pid) {
		kill(SIGKILL, pGlobalState->pid);
	}
	exit(0);
}

E 14
E 13
int
main(int ac, char **av)
E 4
{
I 9
	int parallel = 1;
I 10
	int warmup = 0;
	int repetitions = TRIES;
E 10
E 9
D 8
	int	sv[2];
E 8
I 8
	struct _state state;
I 9
	int c;
D 10
	char* usage = "[-P <parallelism>]\n";
E 10
I 10
	char* usage = "[-m <message size>] [-P <parallelism>] [-W <warmup>] [-N <repetitions>]\n";
E 10

D 10
	while (( c = getopt(ac, av, "P:")) != EOF) {
E 10
I 10
	state.msize = 1;
I 13
	state.pid = 0;
E 13

	while (( c = getopt(ac, av, "m:P:W:N:")) != EOF) {
E 10
		switch(c) {
I 10
		case 'm':
			state.msize = atoi(optarg);
			break;
E 10
		case 'P':
			parallel = atoi(optarg);
			if (parallel <= 0) lmbench_usage(ac, av, usage);
			break;
I 10
		case 'W':
			warmup = atoi(optarg);
			break;
		case 'N':
			repetitions = atoi(optarg);
			break;
E 10
		default:
			lmbench_usage(ac, av, usage);
			break;
		}
	}
	if (optind < ac) {
		lmbench_usage(ac, av, usage);
	}
I 13

D 14
	pGlobalState = &state;
	signal(SIGTERM, sigterm_handler);

E 14
E 13
D 10
	benchmp(initialize, benchmark, cleanup, 0, parallel, &state);
E 10
I 10
	benchmp(initialize, benchmark, cleanup, 0, parallel, 
		warmup, repetitions, &state);
E 10
E 9
E 8

D 3
	write(2, id, strlen(id));
E 3
D 8
	if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) == -1) {
		perror("socketpair");
	}
	if (fork() == 0) {
D 4
		doclient(sv[1]);
E 4
I 4
D 6
		client(sv[1]);
E 6
I 6
		BENCH(client(sv[1]), MEDIUM);
		micro("AF_UNIX sock stream latency", get_n());
		kill(getppid(), SIGTERM);
E 6
E 4
	} else {
D 4
		doserver(sv[0]);
E 4
I 4
		server(sv[0]);
E 4
	}
E 8
I 8
D 9
	benchmp(initialize, benchmark, cleanup, 0, 1, &state);
E 9
	micro("AF_UNIX sock stream latency", get_n());
E 8
D 7
	exit(0);
E 7
I 7
	return(0);
E 7
}

D 4
doclient(int sock)
E 4
I 4
D 8
void
client(int sock)
E 8
I 8
D 14
void initialize(void* cookie)
E 14
I 14
void
initialize(void* cookie)
E 14
E 8
E 4
{
I 8
	struct _state* pState = (struct _state*)cookie;
E 8
D 10
	char    c;
E 10
I 8
	void	exit();
E 8
D 5
	int     i;
	char	buf[100];
E 5
I 5
D 6
	int     i, N;
E 6
E 5

D 5
	start();
	for (i = 0; i < N; ++i) {
		write(sock, &c, 1);
		read(sock, &c, 1);
	}
	stop();
	sprintf(buf, "AF_UNIX sock stream latency");
	micro(buf, N);
E 5
I 5
D 6
	LOOP_FIRST(N, i, ENOUGH);
E 6
D 8
	write(sock, &c, 1);
	read(sock, &c, 1);
E 8
I 8
	if (socketpair(AF_UNIX, SOCK_STREAM, 0, pState->sv) == -1) {
		perror("socketpair");
	}

D 11
	if (pState->pid = fork())
		return;

E 11
I 10
	pState->buf = malloc(pState->msize);
	if (pState->buf == NULL) {
D 11
		perror("buffer allocation");
E 11
I 11
		fprintf(stderr, "buffer allocation\n");
		exit(1);
E 11
	}
I 11

	if (pState->pid = fork())
		return;
E 11

E 10
	/* Child sits and ping-pongs packets back to parent */
	signal(SIGTERM, exit);
D 10
	while (read(pState->sv[0], &c, 1) == 1) {
		write(pState->sv[0], &c, 1);
E 10
I 10
	while (read(pState->sv[0], pState->buf, pState->msize) == pState->msize) {
		write(pState->sv[0], pState->buf, pState->msize);
E 10
	}
	exit(0);
E 8
D 6
	LOOP_LAST(N, i, ENOUGH);
	micro("AF_UNIX sock stream latency", N);
E 5
	kill(getppid(), SIGTERM);
E 6
}

D 4
doserver(sock)
E 4
I 4
D 8
void
server(int sock)
E 8
I 8
D 12
void benchmark(uint64 iterations, void* cookie)
E 12
I 12
D 14
void benchmark(iter_t iterations, void* cookie)
E 14
I 14
void
benchmark(iter_t iterations, void* cookie)
E 14
E 12
E 8
E 4
{
D 8
	char    c;
	int	n = 0;
	void	exit();
E 8
I 8
	struct _state* pState = (struct _state*)cookie;
E 8

D 8
	signal(SIGTERM, exit);
	while (read(sock, &c, 1) == 1) {
		write(sock, &c, 1);
		n++;
E 8
I 8
	while (iterations-- > 0) {
D 10
		char    c;

		if (write(pState->sv[1], &c, 1) != 1
		    || read(pState->sv[1], &c, 1) != 1) {
E 10
I 10
		if (write(pState->sv[1], pState->buf, pState->msize) != pState->msize
		    || read(pState->sv[1], pState->buf, pState->msize) != pState->msize) {
E 10
			/* error handling: how do we signal failure? */
			cleanup(cookie);
			exit(0);
		}
E 8
	}
}
I 8

D 14
void cleanup(void* cookie)
E 14
I 14
void
cleanup(void* cookie)
E 14
{
	struct _state* pState = (struct _state*)cookie;

D 14
	kill(pState->pid, SIGTERM);
E 14
I 14
	if (pState->pid) kill(pState->pid, SIGKILL);
E 14
	wait(0);
}

E 8
E 2
I 1
E 1
