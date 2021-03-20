H26378
s 00013/00015/00095
d D 1.20 01/09/11 09:24:42 staelin 21 20
c Fix lat_connect so that it cannot measure parallelism, since
c lat_connect has some special issues if the benchmark attempts
c to create too many TCP connections in too short a period.
cC
cHhpli69.hpli.hpl.hp.com
cK14455
cZ+03:00
e
s 00001/00001/00109
d D 1.19 00/10/31 10:00:37 staelin 20 19
c - Add SOCKOPT_REUSE to tcp_server() call
cC
cK54812
cZ+02:00
e
s 00002/00002/00108
d D 1.18 00/07/30 11:46:06 staelin 19 18
c - Change type of "iterations" from uint64 to iter_t, which is a u_long
cC
cK54728
e
s 00013/00004/00097
d D 1.17 00/07/04 14:55:51 staelin 18 17
c - Update to incorporate new "-W <warmup>" and "-N <repetitions>" flags
cC
cK54542
e
s 00015/00025/00086
d D 1.16 00/06/21 19:28:40 staelin 17 16
c - Updated command line parsing to use '-S server' to shutdown server process
cC
cK35728
cZ+03:00
e
s 00001/00001/00110
d D 1.15 00/04/17 13:06:00 staelin 16 15
c - convert 'char c' to 'int c' for getopt()
cC
cHhpli8.hpli.hpl.hp.com
cK45089
cZ+02:00
e
s 00063/00058/00048
d D 1.14 00/03/16 18:07:47 brucec 15 14
c Make changes for parallel runs ("-P <parallelism>").  Need to
c expand this test to have multiple server processes listening on
c multiple ports for the parallel cases
cC
cHrx7
cK45172
cZ-05:00
e
s 00001/00001/00105
d D 1.13 98/07/30 22:04:11 lm 14 13
c XXX - a bandaid hack for running out of sockets.
cC
cK28543
e
s 00000/00001/00106
d D 1.12 97/06/15 22:38:58 lm 13 12
c lint
cK28585
e
s 00001/00000/00106
d D 1.11 97/06/14 12:20:39 lm 12 11
c it wasn't cleaning up after itself.
cK29262
e
s 00007/00006/00099
d D 1.10 97/06/13 20:39:50 lm 11 10
c lint
cK27393
e
s 00009/00007/00096
d D 1.9 97/06/12 21:30:06 lm 10 9
c new bench.h macros.
cK26949
e
s 00001/00002/00102
d D 1.8 97/04/23 22:40:47 lm 9 8
c ?
cK24081
cZ-07:00
e
s 00003/00003/00101
d D 1.7 96/11/13 16:09:37 lm 8 7
c timing.c interfaces.
cK25784
e
s 00011/00019/00093
d D 1.6 96/11/11 03:36:51 lm 7 6
c Auto adjusting changes.
cK26000
e
s 00009/00006/00103
d D 1.5 96/11/08 19:58:39 lm 6 5
c gcc -Wall cleanup.
cK34823
cZ-08:00
e
s 00002/00004/00107
d D 1.4 96/05/30 00:33:07 lm 5 4
c no what strings
cK27190
e
s 00001/00001/00110
d D 1.3 95/09/25 22:42:08 lm 4 3
c Add a sleep so that the other side is finished.
c Get rid of the write(), it added needless overhead.
cK36722
cZ-07:00
e
s 00004/00004/00107
d D 1.2 95/03/10 18:25:01 lm 3 2
c lint & sockopt.
cK34180
e
s 00111/00000/00000
d D 1.1 94/11/18 00:49:48 lm 2 1
c Initial revision
cK30092
e
s 00000/00000/00000
d D 1.0 94/11/18 00:49:47 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK14665
cPsrc/lat_connect.c
cR86372c4fec5b6e34
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
 * lat_connect.c - simple TCP connection latency test
 *
 * Three programs in one -
 *	server usage:	lat_connect -s
D 15
 *	client usage:	lat_connect hostname [N]
E 15
I 15
D 18
 *	client usage:	lat_connect [-P <parallelism> hostname
E 18
I 18
D 21
 *	client usage:	lat_connect [-P <parallelism>] [-W <warmup>] [-N <repetitions>] hostname
E 21
I 21
 *	client usage:	lat_connect [-N <repetitions>] hostname
E 21
E 18
E 15
 *	shutdown:	lat_connect -hostname
 *
I 21
 * lat_connect may not be parallelized because of idiosyncracies
 * with TCP connection creation.  Basically, if the client tries
 * to create too many connections too quickly, the system fills
 * up the set of available connections with TIME_WAIT connections.
 * We can only measure the TCP connection cost accurately if we
 * do just a few connections.  Since the parallel harness needs
 * each child to run for a second, this guarantees that the 
 * parallel version will generate inaccurate results.
 *
E 21
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
char	*id = "$Id$\n";
D 7
#include "bench.h"
E 7
D 9
#define	NO_SETSOCKOPT
#include "lib_tcp.c"
E 9
D 7
#include "timing.c"
E 7
I 7
D 10
#include "timing.h"
E 10
#include "bench.h"
I 9
D 10
#include "lib_tcp.h"
E 10
E 9
E 7

D 7
/*
 * A small N is used because the connections hang around even after the
D 5
 * socket has been closed.  XXX - is this a TCP (implementation) bug?
E 5
I 5
 * socket has been closed.  
E 5
 */
D 5
#define	N	20
E 5
I 5
#define	N	100
E 5

E 7
D 6
main(ac, av)
	char  **av;
E 6
I 6
D 15
void	server_main(int ac, char **av);
void	client_main(int ac, char **av);
E 15
I 15
typedef struct _state {
	char	*server;
} state_t;
E 15

I 11
D 15
void
doit(char *server)
{
	int	sock = tcp_connect(server, TCP_CONNECT, SOCKOPT_NONE);
	close(sock);
}
E 15
I 15
D 19
void	doclient(uint64 iterations, void * cookie);
E 19
I 19
void	doclient(iter_t iterations, void * cookie);
E 19
void	server_main();
E 15

E 11
D 15
int
main(int ac, char **av)
E 15
I 15
int main(int ac, char **av)
E 15
E 6
{
D 5
	write(2, id, strlen(id));
E 5
D 15
	if (ac != 2) {
		fprintf(stderr, "Usage: %s -s OR %s [-]serverhost\n",
		    av[0], av[0]);
		exit(1);
	}
	if (!strcmp(av[1], "-s")) {
E 15
I 15
	state_t state;
D 21
	int	parallel = 1;
I 18
	int	warmup = 0;
E 21
	int	repetitions = TRIES;
E 18
D 16
	char 	c;
E 16
I 16
	int 	c;
E 16
	char	buf[256];
D 17
	char	*usage = "-s\n OR [-P <parallelism>] server\n OR [-]serverhost\n";
E 17
I 17
D 18
	char	*usage = "-s\n OR [-S] [-P <parallelism>] server\n";
E 18
I 18
D 21
	char	*usage = "-s\n OR [-S] [-P <parallelism>] [-W <warmup>] [-N <repetitions>] server\n";
E 21
I 21
	char	*usage = "-s\n OR [-S] [-N <repetitions>] server\n";
E 21
E 18
E 17

D 17
	if (ac == 2 && !strcmp(av[1], "-s")) { /* Server */
E 15
		if (fork() == 0) {
D 15
			server_main(ac, av);
E 15
I 15
			server_main();
E 15
		}
		exit(0);
D 15
	} else {
		client_main(ac, av);
E 15
	}
D 15
	exit(0);
	/* NOTREACHED */
}
E 15
I 15
       /*
	* Client
	*/

	if (ac == 2) {
		if (!strcmp(av[1],"-"))
			lmbench_usage(ac, av, usage);
		if (av[1][0] == '-') { /* shut down server */
			int sock = tcp_connect(&av[1][1],
E 17
I 17
D 18
	while (( c = getopt(ac, av, "sSP:")) != EOF) {
E 18
I 18
	while (( c = getopt(ac, av, "sSP:W:N:")) != EOF) {
E 18
		switch(c) {
		case 's': /* Server */
			if (fork() == 0) {
				server_main();
			}
			exit(0);
		case 'S': /* shutdown serverhost */
		{
			int sock = tcp_connect(av[optind],
E 17
					       TCP_CONNECT,
					       SOCKOPT_NONE);
			write(sock, "0", 1);
			close(sock);
			exit(0);
		}
D 17
	}
E 15

I 10
D 11
doit(char *server)
{
	int	sock = tcp_connect(server, TCP_CONNECT, SOCKOPT_NONE);
	close(sock);
}

E 11
E 10
D 6
client_main(ac, av)
	char  **av;
E 6
I 6
D 15
void
client_main(int ac, char **av)
E 6
{
	int     sock;
	char	*server;
D 7
	int	i, tmp, cost;
E 7
I 7
D 13
	int	i, N;
E 13
I 8
	char	buf[256];
E 15
I 15
	while (( c = getopt(ac, av, "P:")) != EOF) {
		switch(c) {
E 17
D 21
		case 'P':
			parallel = atoi(optarg);
			if (parallel <= 0)
				lmbench_usage(ac, av, usage);
			break;
I 18
		case 'W':
			warmup = atoi(optarg);
			break;
E 21
		case 'N':
			repetitions = atoi(optarg);
			break;
E 18
		default:
			lmbench_usage(ac, av, usage);
			break;
		}
	}
E 15
E 8
E 7

D 15
	if (ac != 2) {
		fprintf(stderr, "usage: %s host\n", av[0]);
		exit(1);
E 15
I 15
	if (optind + 1 != ac) {
		lmbench_usage(ac, av, usage);
E 15
	}
D 15
	server = av[1][0] == '-' ? &av[1][1] : av[1];
E 15
I 15
D 17
	state.server = av[optind];
E 17

D 17
	benchmp(NULL, doclient, NULL,
		REAL_SHORT, parallel, &state);
E 17
I 17
	state.server = av[optind];
D 18
	benchmp(NULL, doclient, NULL, REAL_SHORT, parallel, &state);
E 18
I 18
D 21
	benchmp(NULL, doclient, NULL, REAL_SHORT, parallel, 
		warmup, repetitions, &state);
E 21
I 21
	benchmp(NULL, doclient, NULL, 0, 1, 0, repetitions, &state);
E 21
E 18
E 17

	sprintf(buf, "TCP/IP connection cost to %s", state.server);
	micro(buf, get_n());
I 17
	exit(0);
E 17
}
E 15

D 15
	/*
	 * Stop server code.
	 */
	if (av[1][0] == '-') {
E 15
I 15
D 19
void doclient(uint64 iterations, void *cookie)
E 19
I 19
void doclient(iter_t iterations, void *cookie)
E 19
{
	state_t *state = (state_t *) cookie;
	register char	*server = state->server;
	register int 	sock;
	
	while (iterations-- > 0) {
E 15
D 3
		sock = tcp_connect(server, TCP_CONNECT);
E 3
I 3
D 20
		sock = tcp_connect(server, TCP_CONNECT, SOCKOPT_NONE);
E 20
I 20
		sock = tcp_connect(server, TCP_CONNECT, SOCKOPT_REUSE);
E 20
E 3
D 15
		write(sock, "0", 1);
E 15
		close(sock);
D 15
		exit(0);
		/* NOTREACHED */
E 15
	}
D 15

D 7
	cost = 0x7fffffff;
	for (i = 0; i < N; ++i) {
		start();
D 3
		sock = tcp_connect(server, TCP_CONNECT);
E 3
I 3
		sock = tcp_connect(server, TCP_CONNECT, SOCKOPT_NONE);
E 3
		tmp = stop();
		if (tmp < cost)
			cost = tmp;
D 4
		write(sock, "1", 1);
E 4
		close(sock);
I 4
D 5
		sleep(1);	/* give the sockets time to go away */
E 5
E 4
	}
E 7
I 7
	/*
	 * We don't want more than a few of these, they stack up in time wait.
I 10
	 * XXX - report an error if the clock is too shitty?
E 10
	 */
D 10
	LOOP_FIRST(N, i, 200000);
	sock = tcp_connect(server, TCP_CONNECT, SOCKOPT_NONE);
	close(sock);
	LOOP_LAST(N, i, 200000);
E 10
I 10
D 14
	BENCH(doit(server), 100000);
E 14
I 14
	BENCH(doit(server), 25000);
E 14
E 10
E 7
D 8
	fprintf(stderr, "TCP/IP connection cost to %s: %d microseconds\n", 
D 7
	    server, cost);
E 7
I 7
	    server, i/N);
E 7

E 8
I 8
	sprintf(buf, "TCP/IP connection cost to %s", server);
D 10
	micro(buf, N);
E 10
I 10
	micro(buf, get_n());
E 10
E 8
	exit(0);
	/* NOTREACHED */
E 15
}

D 6
server_main(ac, av)
	char  **av;
E 6
I 6
void
D 15
server_main(int ac, char **av)
E 15
I 15
server_main()
E 15
E 6
{
	int     newsock, sock;
D 15
	char	c;
E 15
I 15
	char	c ='1';
E 15

D 15
	if (ac != 2) {
		fprintf(stderr, "usage: %s -s\n", av[0]);
		exit(1);
	}
E 15
	GO_AWAY;
D 3
	sock = tcp_server(TCP_CONNECT);
E 3
I 3
D 21
	sock = tcp_server(TCP_CONNECT, SOCKOPT_NONE);
E 21
I 21
	sock = tcp_server(TCP_CONNECT, SOCKOPT_NONE|SOCKOPT_REUSE);
E 21
E 3
	for (;;) {
D 3
		newsock = tcp_accept(sock);
E 3
I 3
		newsock = tcp_accept(sock, SOCKOPT_NONE);
E 3
D 15
		c = 0;
E 15
D 17
		read(newsock, &c, 1);
D 15
		if (c && c == '0') {
E 15
I 15
		if (c == '0') {
E 17
I 17
		if (read(newsock, &c, 1) > 0) {
E 17
E 15
I 12
			tcp_done(TCP_CONNECT);
E 12
			exit(0);
		}
		close(newsock);
	}
	/* NOTREACHED */
}
E 2
I 1
E 1
