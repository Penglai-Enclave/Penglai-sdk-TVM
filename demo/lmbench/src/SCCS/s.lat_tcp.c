h37758
s 00001/00001/00175
d D 1.15 00/10/31 10:00:48 staelin 16 15
c - Add SOCKOPT_REUSE to tcp_server() call
cC
cK04619
cZ+02:00
e
s 00003/00003/00173
d D 1.14 00/09/26 16:00:21 staelin 15 14
c - Fix bug in command-line parsing for "-S <serverhost>" option
cC
cK04535
e
s 00002/00002/00174
d D 1.13 00/07/30 11:46:14 staelin 14 13
c - Change type of "iterations" from uint64 to iter_t, which is a u_long
cC
cK04462
e
s 00013/00004/00163
d D 1.12 00/07/04 14:55:59 staelin 13 12
c - Update to incorporate new "-W <warmup>" and "-N <repetitions>" flags
cC
cK04276
e
s 00039/00035/00128
d D 1.11 00/06/21 19:28:43 staelin 12 11
c - Cleaned up command line parsing
c - Added '-m <message size>' flag
c - Changed to use '-S server' to shutdown server process
cC
cK49351
cZ+03:00
e
s 00001/00001/00162
d D 1.10 00/04/17 13:06:03 staelin 11 10
c - convert 'char c' to 'int c' for getopt()
cC
cHhpli8.hpli.hpl.hp.com
cK28488
cZ+02:00
e
s 00031/00035/00132
d D 1.9 00/03/16 18:07:48 brucec 10 9
c Make changes for parallel runs ("-P <parallelism>").  
c 
cC
cK28571
e
s 00076/00046/00091
d D 1.8 00/03/14 18:03:55 brucec 9 8
c Make this test MP "-P <parallelism>" ready.
cC
cHrx7
cK32707
cZ-05:00
e
s 00001/00001/00136
d D 1.7 97/06/15 22:38:58 lm 8 7
c lint
cC
cK42655
cSAlpha2.11
e
s 00006/00013/00131
d D 1.6 97/06/12 21:30:06 lm 7 6
c new bench.h macros.
cK42425
cZ-07:00
e
s 00008/00012/00136
d D 1.5 96/11/11 03:36:51 lm 6 5
c Auto adjusting changes.
cK55355
e
s 00021/00009/00127
d D 1.4 96/11/08 20:03:43 lm 5 4
c gcc -Wall cleanup.
cK55818
cZ-08:00
e
s 00000/00001/00136
d D 1.3 96/05/30 00:33:07 lm 4 3
c no what strings
cK34860
cZ-07:00
e
s 00024/00006/00113
d D 1.2 95/03/10 18:25:31 lm 3 2
c lint, sockopt, & make it N way capable.
cK36931
e
s 00119/00000/00000
d D 1.1 94/11/18 00:49:48 lm 2 1
c Initial revision
cK19319
e
s 00000/00000/00000
d D 1.0 94/11/18 00:49:47 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK17274
cPsrc/lat_tcp.c
cR403c1dd2be70f174
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
D 9
 * tcp_xact.c - simple TCP transaction latency test
E 9
I 9
 * lat_tcp.c - simple TCP transaction latency test
E 9
 *
 * Three programs in one -
 *	server usage:	tcp_xact -s
D 9
 *	client usage:	tcp_xact hostname
E 9
I 9
D 13
 *	client usage:	tcp_xact [-P <parallelism>] hostname
E 13
I 13
 *	client usage:	tcp_xact [-m <message size>] [-P <parallelism>] [-W <warmup>] [-N <repetitions>] hostname
E 13
E 9
D 15
 *	shutdown:	tcp_xact -hostname
E 15
I 15
 *	shutdown:	tcp_xact -S hostname
E 15
 *
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
char	*id = "$Id$\n";
I 5

E 5
D 6
#include "bench.h"
#include "lib_tcp.c"
#include "timing.c"
E 6
I 5
D 7
#include <sys/types.h>
#include <sys/wait.h>
I 6
#include "timing.h"
E 7
#include "bench.h"
D 7
#include "lib_tcp.h"
E 7
E 6

E 5
D 6
#define	N	5000

E 6
D 5
main(ac, av)
	char  **av;
E 5
I 5
D 9
void	client_main(int ac, char **av);
E 9
I 9
typedef struct _state {
I 12
	int	msize;
E 12
	int	sock;
	char	*server;
I 12
	char	*buf;
E 12
} state_t;

void	init(void *cookie);
void	cleanup(void *cookie);
E 9
D 10
void	doserver(int sock);
E 10
D 7
void	doclient(int sock, char *host);
E 7
I 7
D 9
void	doclient(int sock);
E 7
void	server_main(int ac, char **av);
E 9
I 9
D 14
void	doclient(uint64 iterations, void * cookie);
E 14
I 14
void	doclient(iter_t iterations, void * cookie);
E 14
void	server_main();
E 9
void	doserver(int sock);

int
main(int ac, char **av)
E 5
{
D 4
	write(2, id, strlen(id));
E 4
D 9
	if (ac != 2) {
		fprintf(stderr, "Usage: %s -s OR %s [-]serverhost\n",
		    av[0], av[0]);
		exit(1);
	}
	if (!strcmp(av[1], "-s")) {
E 9
I 9
	state_t state;
	int	parallel = 1;
I 13
	int	warmup = 0;
	int	repetitions = TRIES;
E 13
I 10
D 11
	char 	c;
E 11
I 11
	int 	c;
E 11
E 10
	char	buf[256];
D 10
	char	*usage = "-s\n OR [-P <parallelism>] server [size]\n OR [-]serverhost\n";
E 10
I 10
D 12
	char	*usage = "-s\n OR [-P <parallelism>] server\n OR [-]serverhost\n";
E 12
I 12
D 13
	char	*usage = "-s\n OR [-m <message size>] [-P <parallelism>] server\n OR -S server\n";
E 13
I 13
	char	*usage = "-s\n OR [-m <message size>] [-P <parallelism>] [-W <warmup>] [-N <repetitions>] server\n OR -S server\n";
E 13
E 12
E 10

D 12
	if (ac == 2 && !strcmp(av[1], "-s")) { /* Server */
E 9
		if (fork() == 0) {
D 9
			server_main(ac, av);
E 9
I 9
			server_main();
E 9
		}
		exit(0);
D 9
	} else {
		client_main(ac, av);
E 9
I 9
D 10
		
	} else { /* Client */
		char c;
		if (ac == 2) {
			if (av[1][0] == '-') { /* shut down server */
				if (!strcmp(av[1],"-"))
					lmbench_usage(ac, av, usage);
				else {
					state.sock = tcp_connect(&av[1][1],
								 TCP_XACT,
								 SOCKOPT_NONE);
					close(state.sock);
					exit(0);
				}
			}
		}
E 10
I 10
	}
E 12
I 12
	state.msize = 1;
E 12
E 10

D 10
		while (( c = getopt(ac, av, "P:")) != EOF) {
			switch(c) {
			case 'P':
				parallel = atoi(optarg);
				if (parallel <= 0)
					lmbench_usage(ac, av, usage);
				break;
			default:
				lmbench_usage(ac, av, usage);
				break;
			}
E 10
I 10
D 12
       /*
	* Client args are -server OR [-P <parallelism>] server
	*/
	if (ac == 2) {
		if (!strcmp(av[1],"-"))
			lmbench_usage(ac, av, usage);
		if (av[1][0] == '-') { /* shut down server */
			state.sock = tcp_connect(&av[1][1],
E 12
I 12
D 13
	while (( c = getopt(ac, av, "sSP:m:")) != EOF) {
E 13
I 13
D 15
	while (( c = getopt(ac, av, "sSm:P:W:N:")) != EOF) {
E 15
I 15
	while (( c = getopt(ac, av, "sS:m:P:W:N:")) != EOF) {
E 15
E 13
		switch(c) {
		case 's': /* Server */
			if (fork() == 0) {
				server_main();
			}
			exit(0);
		case 'S': /* shutdown serverhost */
D 15
			state.sock = tcp_connect(av[ac - 1],
E 15
I 15
			state.sock = tcp_connect(optarg,
E 15
E 12
						 TCP_XACT,
						 SOCKOPT_NONE);
			close(state.sock);
			exit(0);
E 10
D 12
		}
I 10
	}
E 10

D 10
		if (optind + 1 != ac) {
E 10
I 10
	while (( c = getopt(ac, av, "P:")) != EOF) {
		switch(c) {
E 12
I 12
		case 'm':
			state.msize = atoi(optarg);
			break;
E 12
		case 'P':
			parallel = atoi(optarg);
			if (parallel <= 0)
				lmbench_usage(ac, av, usage);
			break;
I 13
		case 'W':
			warmup = atoi(optarg);
			break;
		case 'N':
			repetitions = atoi(optarg);
			break;
E 13
		default:
E 10
			lmbench_usage(ac, av, usage);
I 10
			break;
E 10
		}
I 10
	}
E 10

D 10
		state.server = av[optind][0] == '-' ?
			                  &av[optind][1] : av[optind];

E 10
I 10
D 12
	if (optind + 1 != ac) {
E 12
I 12
	if (optind != ac - 1) {
E 12
		lmbench_usage(ac, av, usage);
E 10
E 9
	}
I 10
D 12
	state.server = av[optind];
E 12

I 12
	state.server = av[optind];
E 12
D 13
	benchmp(init, doclient, cleanup, MEDIUM, parallel, &state);
E 13
I 13
	benchmp(init, doclient, cleanup, MEDIUM, parallel, 
		warmup, repetitions, &state);
E 13
E 10
D 8
	exit(0);
E 8
I 8
D 9
	return(0);
E 9
I 9

D 10
	benchmp(init,doclient,cleanup,
		MEDIUM, parallel, &state);
E 10
	sprintf(buf, "TCP latency using %s", state.server);
	micro(buf, get_n());
I 12

	exit(0);
E 12
E 9
E 8
}

D 5
client_main(ac, av)
	char  **av;
E 5
I 5
D 9
void
client_main(int ac, char **av)
E 9
I 9
void init(void * cookie)
E 9
E 5
{
D 3
	int     newsock, sock;
E 3
I 3
D 9
	int     sock;
E 3
	char	*server;
I 7
	char	buf[100];
E 9
I 9
	state_t *state = (state_t *) cookie;
I 12
	int	msize  = htonl(state->msize);
E 12
E 9
E 7

D 9
	if (ac != 2) {
		fprintf(stderr, "usage: %s host\n", av[0]);
		exit(1);
	}
	server = av[1][0] == '-' ? &av[1][1] : av[1];
D 3
	sock = tcp_connect(server, TCP_XACT);
E 3
I 3
	sock = tcp_connect(server, TCP_XACT, SOCKOPT_NONE);
E 9
I 9
	state->sock = tcp_connect(state->server, TCP_XACT, SOCKOPT_NONE);
I 12
	state->buf = malloc(state->msize);

	write(state->sock, &msize, sizeof(int));
E 12
}
E 9
E 3

D 9
	/*
	 * Stop server code.
	 */
	if (av[1][0] == '-') {
		close(sock);
		exit(0);
	}
E 9
I 9
void cleanup(void * cookie)
{
	state_t *state = (state_t *) cookie;
E 9

D 7
	doclient(sock, server);
E 7
I 7
D 9
	BENCH(doclient(sock), MEDIUM);
	sprintf(buf, "TCP latency using %s", av[1]);
	micro(buf, get_n());
E 7
	exit(0);
	/* NOTREACHED */
E 9
I 9
	close(state->sock);
I 12
	free(state->buf);
E 12
E 9
}

D 5
doclient(sock, host)
	char	*host;
E 5
I 5
void
D 7
doclient(int sock, char *host)
E 7
I 7
D 9
doclient(int sock)
E 9
I 9
D 14
doclient(uint64 iterations, void *cookie)
E 14
I 14
doclient(iter_t iterations, void *cookie)
E 14
E 9
E 7
E 5
{
I 9
	state_t *state = (state_t *) cookie;
	int 	sock   = state->sock;
E 9
D 12
	char    c;
E 12
D 6
	int     i;
E 6
I 6
D 7
	int     i, N;
E 6
	char	buf[100];
E 7

D 6
	start();
	for (i = 0; i < N; ++i) {
		write(sock, &c, 1);
		read(sock, &c, 1);
	}
	stop();
E 6
I 6
D 7
	LOOP_FIRST(N, i, MEDIUM);
E 7
D 9
	write(sock, &c, 1);
	read(sock, &c, 1);
E 9
I 9
	while (iterations-- > 0) {
D 12
		write(sock, &c, 1);
		read(sock, &c, 1);
E 12
I 12
		write(sock, state->buf, state->msize);
		read(sock, state->buf, state->msize);
E 12
	}
E 9
D 7
	LOOP_LAST(N, i, MEDIUM);
E 6
	sprintf(buf, "TCP latency using %s", host);
	micro(buf, N);
E 7
}

I 5
void
E 5
I 3
child()
{
	wait(0);
	signal(SIGCHLD, child);
}

E 3
D 5
server_main(ac, av)
	char  **av;
E 5
I 5
void
D 9
server_main(int ac, char **av)
E 9
I 9
server_main()
E 9
E 5
{
D 3
	int     server, newsock, sock;
E 3
I 3
	int     newsock, sock;
E 3

D 9
	if (ac != 2) {
		fprintf(stderr, "usage: %s -s\n", av[0]);
		exit(1);
	}
E 9
	GO_AWAY;
D 3
	sock = tcp_server(TCP_XACT);
E 3
I 3
	signal(SIGCHLD, child);
D 16
	sock = tcp_server(TCP_XACT, SOCKOPT_NONE);
E 16
I 16
	sock = tcp_server(TCP_XACT, SOCKOPT_REUSE);
E 16
E 3
	for (;;) {
D 3
		newsock = tcp_accept(sock);
		doserver(newsock);
E 3
I 3
		newsock = tcp_accept(sock, SOCKOPT_NONE);
		switch (fork()) {
		    case -1:
			perror("fork");
			break;
		    case 0:
			doserver(newsock);
			exit(0);
		    default:
			close(newsock);
			break;
		}
E 3
	}
	/* NOTREACHED */
}

D 5
doserver(sock)
E 5
I 5
void
doserver(int sock)
E 5
{
D 12
	char    c;
	int	n = 0;
E 12
I 12
	int	n;
E 12

D 12
	while (read(sock, &c, 1) == 1) {
		write(sock, &c, 1);
		n++;
	}
E 12
I 12
	if (read(sock, &n, sizeof(int)) == sizeof(int)) {
		int	msize = ntohl(n);
		char*   buf = (char*)malloc(msize);
E 12

D 12
	/*
	 * A connection with no data means shut down.
	 */
	if (n == 0) {
E 12
I 12
		for (n = 0; read(sock, buf, msize) > 0; n++) {
			write(sock, buf, msize);
		}
		free(buf);
	} else {
		/*
		 * A connection with no data means shut down.
		 */
E 12
		tcp_done(TCP_XACT);
I 3
		kill(getppid(), SIGTERM);
E 3
		exit(0);
	}
}
E 2
I 1
E 1
