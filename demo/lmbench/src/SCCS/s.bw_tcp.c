H29077
s 00004/00004/00247
d D 1.28 02/10/17 15:05:20 staelin 29 28
c bw_tcp.c: change it so the default warmup is LONGER, but the user
c   can override is they choose.
cC
cK07272
e
s 00007/00005/00244
d D 1.27 02/10/17 14:38:29 staelin 28 27
c bw_tcp.c: 
c   - fix some potential 32/64 bit problems
c   - change default message size back to XFERSIZE
cC
cK07969
cZ+02:00
e
s 00024/00013/00225
d D 1.26 01/09/11 09:36:39 staelin 27 26
c Fix buglets in bw_tcp to ensure that the server keeps
c sending data to clients, and that it sends data in the
c right message sizes.
cC
cHhpli69.hpli.hpl.hp.com
cK02684
cZ+03:00
e
s 00005/00004/00233
d D 1.25 00/10/31 10:00:30 staelin 26 25
c - Only print any output if benchmark produces a valid result
c   (needed for mb() and micromb()-style outputs where prefix is
c   printed by main() and only the result is printed by the output
c   routine, and only then if the result is valid)
c - Add SOCKOPT_REUSE to tcp_server() call
cC
cK51740
e
s 00001/00001/00236
d D 1.24 00/10/16 17:22:20 staelin 25 24
c - Assorted code cleanups
cC
cK55301
cZ+02:00
e
s 00002/00002/00235
d D 1.23 00/07/30 11:46:04 staelin 24 23
c - Change type of "iterations" from uint64 to iter_t, which is a u_long
cC
cK54413
e
s 00001/00001/00236
d D 1.22 00/07/27 14:36:58 staelin 23 22
c - Decrease TCP warmup time from 7.5 seconds to 1.0 seconds
cC
cK53573
e
s 00083/00087/00154
d D 1.21 00/07/26 18:09:54 staelin 22 21
c - Rewrite of experimental method; use a single connection for all experiments, with
c   a single warmup period preceding all measurements.  Previously created a new connection
c   with a warmup period for each measurement (slow, slow, slow)
c - Moved initialization and cleanup to new initialize() and cleanup() routines
c - Only pass msize to server, since it will keep writing data until the connection is
c   closed.  Previously also passed "move"
cC
cK53628
e
s 00001/00000/00240
d D 1.20 00/07/05 10:26:01 staelin 21 20
c - fix memory leak on server side
cC
cK50923
e
s 00013/00005/00227
d D 1.19 00/07/04 14:55:49 staelin 20 19
c - Update to incorporate new "-W <warmup>" and "-N <repetitions>" flags
cC
cK50029
e
s 00092/00073/00140
d D 1.18 00/06/21 19:28:40 staelin 19 18
c - Added '-m <message size>' command line argument
c - Updated command line parsing to use '-S server' to shutdown server processes
cC
cK29619
cZ+03:00
e
s 00001/00001/00212
d D 1.17 00/04/17 13:06:00 staelin 18 17
c - convert 'char c' to 'int c' for getopt()
cC
cHhpli8.hpli.hpl.hp.com
cK19566
cZ+02:00
e
s 00117/00097/00096
d D 1.16 00/03/10 18:02:24 brucec 17 16
c Make changes so test can be run in parallel "-P <parallelism>"
cC
cHrx7
cK19649
cZ-05:00
e
s 00001/00001/00192
d D 1.15 97/10/19 23:40:11 lm 16 15
c *** empty log message ***
cC
cK01142
e
s 00007/00008/00186
d D 1.14 97/06/25 10:25:01 lm 15 14
c ifdef TOUCH
cK01089
e
s 00004/00004/00190
d D 1.13 97/06/16 19:05:50 lm 14 13
c lint
cK05198
e
s 00004/00002/00190
d D 1.12 97/06/15 22:38:58 lm 13 12
c lint
cK02970
e
s 00024/00022/00168
d D 1.11 97/06/13 20:39:50 lm 12 11
c lint
cK02317
e
s 00013/00016/00177
d D 1.10 97/06/12 21:30:06 lm 11 10
c new bench.h macros.
cK02007
e
s 00038/00019/00155
d D 1.9 97/05/27 16:01:56 lm 10 9
c make it work witht he new timing loop.
cK01621
e
s 00017/00029/00157
d D 1.8 97/04/23 22:10:09 lm 9 8
c 10 second loop.
cK46000
cZ-07:00
e
s 00054/00060/00132
d D 1.7 96/11/11 03:36:51 lm 8 7
c Auto adjusting changes.
cK57455
e
s 00022/00025/00170
d D 1.6 96/11/08 19:58:07 lm 7 6
c gcc -Wall cleanup & new timing.c integration.
cK22746
cZ-08:00
e
s 00036/00027/00159
d D 1.5 96/05/30 00:32:36 lm 6 5
c autotiming
cK19272
cZ-07:00
e
s 00007/00007/00179
d D 1.4 96/01/24 17:09:19 lm 5 4
c Make everything use XFERSIZE
cK11890
cZ-08:00
e
s 00019/00004/00167
d D 1.3 95/06/21 14:02:49 lm 4 3
c Use valloc for buffer.
cK11250
cZ-07:00
e
s 00027/00014/00144
d D 1.2 95/03/10 18:18:06 lm 3 2
c sockopt stuff and make it so that I can wrap a script around it to do N.
cK62334
e
s 00158/00000/00000
d D 1.1 94/11/18 00:49:48 lm 2 1
c Initial revision
cK49052
e
s 00000/00000/00000
d D 1.0 94/11/18 00:49:47 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK19070
cPsrc/bw_tcp.c
cR7051c2802eae1cf3
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
 * bw_tcp.c - simple TCP bandwidth test
 *
 * Three programs in one -
 *	server usage:	bw_tcp -s
D 17
 *	client usage:	bw_tcp hostname
E 17
I 17
D 20
 *	client usage:	bw_tcp [-P <parallelism>] hostname [bytes]
E 20
I 20
D 25
 *	client usage:	bw_tcp [-m <message size>] [-P <parallelism>] [-W <warmup>] [-N <repetitions>] hostname [bytes]
E 25
I 25
 *	client usage:	bw_tcp [-m <message size>] [-M <total bytes>] [-P <parallelism>] [-W <warmup>] [-N <repetitions>] hostname 
E 25
E 20
E 17
 *	shutdown:	bw_tcp -hostname
 *
I 22
 * Copyright (c) 2000 Carl Staelin.
E 22
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
char	*id = "$Id$\n";
D 8
#include "lib_tcp.c"
#include "timing.c"
I 7
#include	<sys/types.h>
#include	<sys/wait.h>
E 8
I 8
D 11
#include <sys/types.h>
#include <sys/wait.h>
E 11
#include "bench.h"
D 11
#include "timing.h"
#include "lib_tcp.h"
E 11
E 8
E 7

D 7
main(ac, av)
	char  **av;
E 7
I 7
D 17
int	server_main(int ac, char **av);
int	client_main(int ac, char **av);
D 8
void	absorb(int control, int data);
E 8
I 8
void	source(int data);
E 8

I 8
char	*buf;

E 8
D 12
int
main(int ac, char **av)
E 7
{
D 6
	write(2, id, strlen(id));
E 6
	if (ac != 2 && ac != 3) {
		fprintf(stderr, "Usage: %s -s OR %s [-]serverhost\n",
		    av[0], av[0]);
		exit(1);
	}
I 8
	buf = valloc(XFERSIZE);
	bzero(buf, XFERSIZE);
E 8
	if (!strcmp(av[1], "-s")) {
		if (fork() == 0) {
			server_main(ac, av);
		}
		exit(0);
	} else {
		client_main(ac, av);
	}
D 3
	exit(0);
E 3
I 3
	return(0);
E 3
}

E 12
I 12
void
E 12
I 10
transfer(uint64 move, char *server)
{
	int	data, c;
	uint64	todo;

	todo = move;
D 11
	/* printf("Move %lu MB\n", (unsigned long)(move>>20)); */
E 11
I 11
D 12
	/*printf("Move %lu MB\n", (unsigned long)(move>>20)); /* */
E 12
I 12
	/*printf("Move %lu MB\n", (unsigned long)(move>>20));
	*/
E 12
E 11
	data = tcp_connect(server, TCP_DATA, SOCKOPT_READ);
	(void)sprintf(buf, "%lu", (unsigned long)move);
	if (write(data, buf, strlen(buf)) != strlen(buf)) {
		perror("control write");
		exit(1);
	}
	while (todo > 0 && (c = read(data, buf, XFERSIZE)) > 0) {
		todo -= c;
D 15
#ifdef	TOUCH
D 14
		bzero(buf, c);
E 14
I 14
		bzero((void*)buf, c);
E 14
#endif
E 15
	}
	(void)close(data);
}

I 13
/* ARGSUSED */
E 13
E 10
D 7
client_main(ac, av)
	char  **av;
E 7
I 7
int
client_main(int ac, char **av)
E 7
{
E 17
I 17
typedef struct _state {
E 17
D 4
	char    buf[SOCKBUF];
E 4
I 4
D 5
	char    *buf = valloc(SOCKBUF);
E 5
I 5
D 8
	char    *buf = valloc(XFERSIZE);
E 5
E 4
	int     data, control;
	int     c;
D 7
	int     bytes;
E 7
I 7
	int     move;
E 7
I 6
	int	usecs;
	int	todo;
E 8
I 8
D 10
	int	data;
	int	c;
D 9
	uint64	move, usecs, todo;
E 9
I 9
	uint64	move, N, usecs, todo;
E 10
I 10
D 22
	uint64	move;
E 22
I 22
	int	sock;
D 27
	long	move;
E 27
I 27
	uint64	move;
E 27
E 22
D 11
	int	N, usecs;
E 11
E 10
E 9
E 8
E 6
D 17
	char   *server;
E 17
I 17
D 19
	char	server[256];
E 19
I 19
	int	msize;
	char	*server;
E 19
	int	fd;
	char	*buf;
} state_t;

D 19
void	server_main(state_t *state);
E 19
I 19
void	server_main();
E 19
void	client_main(int parallel, state_t *state);
D 19
void	source(int data, state_t *state);
void	transfer(uint64 move, char *server, char *buf);
E 19
I 19
void	source(int data);
D 22
void	transfer(state_t* state);
E 22
E 19

I 22
void	initialize(void* cookie);
E 22
D 24
void	loop_transfer(uint64 iter, void *cookie);
E 24
I 24
void	loop_transfer(iter_t iterations, void *cookie);
E 24
I 22
void	cleanup(void* cookie);
E 22

int main(int ac, char **av)
{
D 20
	int parallel = 1;
E 20
I 20
	int	parallel = 1;
D 29
	int	warmup = 0;
E 29
I 29
	int	warmup = LONGER;
E 29
	int	repetitions = TRIES;
E 20
I 19
D 22
	int	server = 0;
E 22
	int	shutdown = 0;
E 19
	state_t state;
D 19
	char	*usage = "-s\n OR [-P <parallelism>] server [size]\n OR [-]serverhost\n";
	char	*server;
E 19
I 19
D 20
	char	*usage = "-s\n OR [-m <message size>] [-P <parallelism>] server [size]\n OR -S serverhost\n";
E 20
I 20
D 22
	char	*usage = "-s\n OR [-m <message size>] [-P <parallelism>] [-W <warmup>] [-N <repetitions>] server [size]\n OR -S serverhost\n";
E 22
I 22
	char	*usage = "-s\n OR [-m <message size>] [-M <bytes to move>] [-P <parallelism>] [-W <warmup>] [-N <repetitions>] server\n OR -S serverhost\n";
E 22
E 20
E 19
D 18
	char	c;
E 18
I 18
	int	c;
E 18
E 17
I 11
D 22
	uint64	usecs;
E 22
I 17
	
D 19
	state.buf = valloc(XFERSIZE);
	touch(state.buf, XFERSIZE);
E 17
E 11

D 17
	if (ac != 2 && ac != 3) {
D 8
		(void)fprintf(stderr, "usage: %s remotehost [count]\n",
E 8
I 8
		(void)fprintf(stderr, "usage: %s remotehost [bytes]\n",
E 8
		    av[0]);
E 17
I 17
	/* Start the server */
	if (!strcmp(av[1], "-s")) {
		if (fork() == 0) {
			server_main(&state);
		}
E 17
		exit(0);
	}
E 19
I 19
	state.msize = 0;
D 22
	state.move = 10*1024*1024;
E 22
I 22
	state.move = 0;
E 22
E 19
I 4
D 17
	if (!buf) {
		perror("valloc");
		exit(1);
E 17
I 17

D 19
	/* Shut down the server */
	if ((ac == 2) && (av[1][0] == '-')) {
		int	conn;
		server = &av[1][1];
		conn = tcp_connect(server, TCP_DATA, SOCKOPT_NONE);
		write(conn, "0", 1);
		exit(0);
E 17
	}
E 4
D 17
	if (ac == 3) {
D 7
		bytes = atoi(av[2]);
		if ((last(av[2]) == 'k') || (last(av[2]) == 'K'))
			bytes *= 1024;
		if ((last(av[2]) == 'm') || (last(av[2]) == 'M'))
			bytes *= (1024 * 1024);
E 7
I 7
		move = bytes(av[2]);
E 7
	} else {
D 5
		bytes = 3*1024*1024;
E 5
I 5
D 7
		bytes = 10*1024*1024;
E 7
I 7
D 9
		move = 10*1024*1024;
E 9
I 9
D 11
		move = 25*1024*1024;
E 11
I 11
		move = 10*1024*1024;
E 17
I 17
	
		
E 19
	/* Rest is client argument processing */
D 19
	while (( c = getopt(ac, av, "P:")) != EOF) {
E 19
I 19
D 20
	while (( c = getopt(ac, av, "sSm:P:")) != EOF) {
E 20
I 20
D 22
	while (( c = getopt(ac, av, "sSm:P:W:N:")) != EOF) {
E 22
I 22
	while (( c = getopt(ac, av, "sS:m:M:P:W:N:")) != EOF) {
E 22
E 20
E 19
		switch(c) {
I 19
		case 's': /* Server */
D 22
			server = 1;
E 22
I 22
			if (fork() == 0) {
				server_main();
			}
			exit(0);
E 22
			break;
		case 'S': /* shutdown serverhost */
D 22
			shutdown = 1;
			break;
E 22
I 22
		{
			int	conn;
D 27
			int	n = htonl(0);
E 27
			conn = tcp_connect(optarg, TCP_DATA, SOCKOPT_NONE);
D 27
			write(conn, &n, sizeof(int));
E 27
I 27
			write(conn, "0", 1);
E 27
			exit(0);
		}
E 22
		case 'm':
D 22
			state.msize = atoi(optarg);
E 22
I 22
			state.msize = bytes(optarg);
			break;
		case 'M':
			state.move = bytes(optarg);
E 22
			break;
E 19
		case 'P':
			parallel = atoi(optarg);
			if (parallel <= 0) lmbench_usage(ac, av, usage);
			break;
I 20
		case 'W':
			warmup = atoi(optarg);
			break;
		case 'N':
			repetitions = atoi(optarg);
			break;
E 20
		default:
			lmbench_usage(ac, av, usage);
			break;
		}
E 17
E 11
E 9
E 7
E 5
	}
I 17

E 17
I 8
D 19
	/*
D 17
	 * Disabler message to other side.
E 17
I 17
	 * Client should have one, possibly two [indicates size] arguments left
E 17
	 */
E 8
D 17
	if (av[1][0] == '-') {
I 10
		int	data;

E 10
D 7
		bytes = 0;
E 7
I 7
		move = 0;
E 7
		server = &av[1][1];
I 8
		data = tcp_connect(server, TCP_DATA, SOCKOPT_NONE);
		write(data, "0", 1);
		exit(0);
E 17
I 17
	state.move = 10*1024*1024;
	if (optind + 2 == ac) {
		state.move = bytes(av[optind+1]);
		strcpy(state.server,av[optind]);
	} else if (optind + 1 == ac) {
		strcpy(state.server,av[optind]);
E 17
E 8
	} else {
E 19
I 19
D 22
	if (server && shutdown
	    || !server && (optind < ac - 2 || optind >= ac)) {
E 22
I 22
	if (optind < ac - 2 || optind >= ac) {
E 22
E 19
D 17
		server = av[1];
E 17
I 17
		lmbench_usage(ac, av, usage);
E 17
	}
I 17

I 19
D 22
	if (server) {
		if (fork() == 0) {
			server_main();
		}
		exit(0);
	}

E 22
	state.server = av[optind++];
D 22
	if (optind < ac) {
		state.move = bytes(av[optind]);
	}
	if (state.msize == 0) {
E 22
I 22

	if (state.msize == 0 && state.move == 0) {
D 28
		state.msize = state.move = 10 * 1024 * 1024;
E 28
I 28
		state.msize = state.move = XFERSIZE;
E 28
	} else if (state.msize == 0) {
E 22
		state.msize = state.move;
I 22
	} else if (state.move == 0) {
		state.move = state.msize;
E 22
	}
I 22

E 22
	/* make the number of bytes to move a multiple of the message size */
	if (state.move % state.msize) {
D 22
		state.move += state.move - state.move % state.msize;
	}

	if (shutdown) {
		int	conn;
		int	n = htonl(0);
		conn = tcp_connect(state.server, TCP_DATA, SOCKOPT_NONE);
		write(conn, &n, sizeof(int));
		exit(0);
E 22
I 22
		state.move += state.msize - state.move % state.msize;
E 22
	}

D 22
	state.buf = valloc(state.msize);
E 19
	if (!state.buf) {
		perror("valloc");
		exit(1);
	}
I 19
	touch(state.buf, state.msize);
E 19

E 22
E 17
I 11
	/*
D 22
	 * Make one run take at least 5 seconds.
	 * This minimizes the effect of connect & reopening TCP windows.
E 22
I 22
D 29
	 * Initialize connection by running warming up for at least
	 * five seconds, then measure performance over one second.
E 29
I 29
	 * Default is to warmup the connection for seven seconds, 
	 * then measure performance over each timing interval.
E 29
	 * This minimizes the effect of opening and initializing TCP 
	 * connections.
E 22
	 */
E 11
D 3
	control = tcp_connect(server, TCP_CONTROL);
	data = tcp_connect(server, TCP_DATA);
E 3
I 3
D 6
	control = tcp_connect(server, TCP_CONTROL, SOCKOPT_NONE);
	data = tcp_connect(server, TCP_DATA, SOCKOPT_WRITE);
E 3
	(void)sprintf(buf, "%d", bytes);
	if (write(control, buf, strlen(buf)) != strlen(buf)) {
		perror("control write");
		exit(1);
	}
	/*
	 * Disabler message to other side.
	 */
	if (bytes == 0) {
		exit(0);
	}
D 4
	while (bytes > 0 && (c = write(data, buf, sizeof(buf))) > 0)
E 4
I 4
D 5
	while (bytes > 0 && (c = write(data, buf, SOCKBUF)) > 0) {
E 5
I 5
	while (bytes > 0 && (c = write(data, buf, XFERSIZE)) > 0) {
E 5
E 4
		bytes -= c;
I 4
#if 0
E 6
I 6
D 8
	do {
E 8
I 8
D 9
	for (;;) {
E 8
D 7
		todo = bytes;
E 7
I 7
		todo = move;
E 7
D 8
		start();
		control = tcp_connect(server, TCP_CONTROL, SOCKOPT_NONE);
		data = tcp_connect(server, TCP_DATA, SOCKOPT_WRITE);
D 7
		(void)sprintf(buf, "%d", bytes);
E 7
I 7
		(void)sprintf(buf, "%d", move);
E 7
		if (write(control, buf, strlen(buf)) != strlen(buf)) {
E 8
I 8
		/* printf("Move %lu MB\n", (unsigned long)(move>>20)); */
		data = tcp_connect(server, TCP_DATA, SOCKOPT_READ);
		(void)sprintf(buf, "%lu", (unsigned long)move);
		if (write(data, buf, strlen(buf)) != strlen(buf)) {
E 8
			perror("control write");
			exit(1);
		}
E 6
D 8
		/*
D 6
		 * On IRIX/Hippi, this slows things down from 89 to 42MB/sec.
E 6
I 6
		 * Disabler message to other side.
E 6
		 */
D 6
		bzero(buf, c);
#endif
	}
E 4
	(void)close(data);
	(void)fprintf(stderr, "Socket bandwidth using %s: ", server);
	while (read(control, buf, 1) == 1) {
		(void)fprintf(stderr, "%c", buf[0]);
		if (buf[0] == '\n') {
E 6
I 6
		if (todo == 0) {
E 6
			exit(0);
		}
D 6
	}
E 6
I 6
		while (todo > 0 && (c = write(data, buf, XFERSIZE)) > 0) {
E 8
I 8
		start(0);
		while (todo > 0 && (c = read(data, buf, XFERSIZE)) > 0) {
E 8
			todo -= c;
E 9
I 9
D 10
	LOOP_FIRST(N, usecs, LONGER);
	todo = move;
	/* printf("Move %lu MB\n", (unsigned long)(move>>20)); */
	data = tcp_connect(server, TCP_DATA, SOCKOPT_READ);
	(void)sprintf(buf, "%lu", (unsigned long)move);
	if (write(data, buf, strlen(buf)) != strlen(buf)) {
		perror("control write");
		exit(1);
E 10
I 10
D 19
	start(0);
D 17
	transfer(move, server);
E 17
I 17
	transfer(state.move, state.server, state.buf);
E 17
	usecs = stop(0,0);
D 11
	if (usecs >= LONGER) {	/* slow friggin machine */
		N = 1;
E 11
I 11
	if (usecs >= LONGER) {	/* must be 10Mbit ether or sloooow box */
		save_n(1);
E 11
D 17
		goto out;
E 17
I 17
		if (parallel == 1)
			goto out; /* can't skip next step for MP tests! */
E 17
E 10
	}
D 10
	while (todo > 0 && (c = read(data, buf, XFERSIZE)) > 0) {
		todo -= c;
E 9
D 8
#if 0
			/*
			 * On IRIX/Hippi, this slows things down from 89 to 42MB/sec.
			 */
E 8
I 8
#ifdef	TOUCH
E 8
D 9
			bzero(buf, c);
E 9
I 9
		bzero(buf, c);
E 9
#endif
D 9
		}
		(void)close(data);
D 8
		c = 0;
		while (read(control, &buf[c++], 1) == 1) {
			if (buf[c-1] == '\n') {
				buf[c] = 0;
				break;
			}
E 8
I 8
		usecs = stop(0,0);
		/*
		 * Flat out refuse to report results for less than 10 sec runs.
		 */
		if (usecs < 10000000) {
			double	adj;
			adj = (10000000 * 1.2)/usecs;
			move *= adj;
		} else {
			break;
E 8
		}
E 9
D 8
		usecs = stop();
		(void)close(control);
D 7
		bytes <<= 2;
E 7
I 7
		move <<= 2;
E 7
	} while (usecs < 10000000);
	(void)fprintf(stderr, "Socket bandwidth using %s: %s", server, buf);
E 8
I 8
	}
I 9
	(void)close(data);
E 10
I 10
D 11
	usecs = LONGER / usecs;
	usecs *= 2;
	move *= usecs;
	LOOP_FIRST(N, usecs, LONGER);
	transfer(move, server);
E 10
	LOOP_LAST(N, usecs, LONGER);
E 11
I 11
	usecs = 5000000 / usecs;
D 16
	move *= usecs * 1.2;
E 16
I 16
D 17
	move *= usecs * 1.25;
E 16
	BENCH(transfer(move, server), LONGER);
E 11
E 9
D 10
	(void)fprintf(stderr, "Socket bandwidth using %s: ", server);
E 10
I 10
out:	(void)fprintf(stderr, "Socket bandwidth using %s: ", server);
E 10
D 9
	mb(move);
E 9
I 9
D 11
	mb(move * N);
E 11
I 11
	mb(move * get_n());
E 11
E 9
E 8
E 6
	exit(0);
	/*NOTREACHED*/
E 17
I 17
	state.move  *= usecs * 1.25;

	benchmp(NULL, loop_transfer, NULL,
		LONGER, parallel, &state );
E 19
I 19
D 20
	benchmp(NULL, loop_transfer, NULL, LONGER, parallel, &state );
E 20
I 20
D 22
	benchmp(NULL, loop_transfer, NULL, LONGER, parallel, warmup, repetitions, &state );
E 20
E 19

out:	(void)fprintf(stderr, "Socket bandwidth using %s: ", state.server);
E 22
I 22
	benchmp(initialize, loop_transfer, cleanup, 
D 23
		SHORT, parallel, LONGER + warmup, repetitions, &state );
E 23
I 23
D 28
		SHORT, parallel, SHORT + warmup, repetitions, &state );
E 28
I 28
D 29
		0, parallel, LONGER + warmup, repetitions, &state);
E 29
I 29
		0, parallel, warmup, repetitions, &state);
E 29
E 28
E 23
D 26
	/* (void)fprintf(stderr, "Socket bandwidth using %s\n", state.server); */
	fprintf(stderr, "%.6f ", state.msize / (1000. * 1000.));
E 22
	mb(state.move * get_n() * parallel);
E 26
I 26
	if (gettime() > 0) {
		fprintf(stderr, "%.6f ", state.msize / (1000. * 1000.));
		mb(state.move * get_n() * parallel);
	}
E 26
}

D 22
void loop_transfer(uint64 iterations, void *cookie)
E 22
I 22
void
initialize(void *cookie)
E 22
{
I 22
	int	c;
I 27
	char	buf[100];
E 27
E 22
	state_t *state = (state_t *) cookie;
D 22
	uint64	move = state->move;
	char	*server = state->server;
D 19
	char	*buf    = state->buf;
E 19

	while (iterations-- > 0) {
D 19
		transfer(move,server,buf);
E 19
I 19
		transfer(state);
E 19
	}
}
E 22

D 19
void transfer(uint64 move, char *server, char *buf)
E 19
I 19
D 22
void transfer(state_t* state)
E 19
{
	int	data, c;
	uint64	todo;
I 19
	char	*buf    = state->buf;
E 19

D 19
	todo = move;
E 19
	/*printf("Move %lu MB\n", (unsigned long)(move>>20)); */
	
D 19
	data = tcp_connect(server, TCP_DATA, SOCKOPT_READ);
	(void)sprintf(buf, "%lu", (unsigned long)move);
	if (write(data, buf, strlen(buf)) != strlen(buf)) {
E 19
I 19
	data = tcp_connect(state->server, TCP_DATA, SOCKOPT_READ);
	c = htonl(state->move);
	if (write(data, &c, sizeof(int)) != sizeof(int)) {
E 19
		perror("control write");
E 22
I 22
	state->buf = valloc(state->msize);
	if (!state->buf) {
		perror("valloc");
E 22
		exit(1);
	}
I 22
	touch(state->buf, state->msize);

D 28
	state->sock = tcp_connect(state->server, TCP_DATA, SOCKOPT_READ);
E 28
I 28
	state->sock = tcp_connect(state->server, TCP_DATA, SOCKOPT_READ|SOCKOPT_WRITE|SOCKOPT_REUSE);
E 28
E 22
D 19
	while (todo > 0 && (c = read(data, buf, XFERSIZE)) > 0) {
		todo -= c;
E 19
I 19
D 27
	c = htonl(state->msize);
D 22
	if (write(data, &c, sizeof(int)) != sizeof(int)) {
E 22
I 22
	if (write(state->sock, &c, sizeof(int)) != sizeof(int)) {
E 27
I 27
	if (state->sock < 0) {
		perror("socket connection");
		exit(1);
	}
D 28
	sprintf(buf, "%llu", state->msize);
E 28
I 28
	sprintf(buf, "%lu", state->msize);
E 28
	if (write(state->sock, buf, strlen(buf) + 1) != strlen(buf) + 1) {
E 27
E 22
		perror("control write");
		exit(1);
	}
D 22
	for (todo = state->move; todo > 0; todo -= c) {
		if (c = read(data, state->buf, state->msize) <= 0) {
			break;
E 22
I 22
}

void 
D 24
loop_transfer(uint64 iterations, void *cookie)
E 24
I 24
loop_transfer(iter_t iterations, void *cookie)
E 24
{
	int	c;
D 27
	long	todo;
E 27
I 27
	uint64	todo;
E 27
	state_t *state = (state_t *) cookie;

	while (iterations-- > 0) {
		for (todo = state->move; todo > 0; todo -= c) {
			if ((c = read(state->sock, state->buf, state->msize)) <= 0) {
				exit(1);
			}
I 27
			if (c > todo) c = todo;
E 27
E 22
		}
E 19
	}
D 22
	(void)close(data);
E 22
E 17
}

I 22
void
cleanup(void* cookie)
{
	state_t *state = (state_t *) cookie;

	/* close connection */
	(void)close(state->sock);
}


E 22
D 7
last(s)
	char	*s;
{
	while (*s++)
		;
	return (s[-2]);
}

E 7
I 7
D 17
void
E 7
I 3
child()
E 17
I 17
void child()
E 17
{
	wait(0);
	signal(SIGCHLD, child);
}

I 13
D 17
/* ARGSUSED */
E 13
E 3
D 7
server_main()
E 7
I 7
int
server_main(int ac, char **av)
E 17
I 17
D 19
void server_main(state_t *state)
E 19
I 19
void server_main()
E 19
E 17
E 7
{
D 8
	int	data, control, newdata, newcontrol;
E 8
I 8
	int	data, newdata;
E 8

	GO_AWAY;

D 3
	data = tcp_server(TCP_DATA);
	control = tcp_server(TCP_CONTROL);
E 3
I 3
	signal(SIGCHLD, child);
D 8
	data = tcp_server(TCP_DATA, SOCKOPT_READ);
	control = tcp_server(TCP_CONTROL, SOCKOPT_NONE);
E 8
I 8
D 26
	data = tcp_server(TCP_DATA, SOCKOPT_WRITE);
E 26
I 26
	data = tcp_server(TCP_DATA, SOCKOPT_WRITE|SOCKOPT_REUSE);
I 27
	if (data < 0) {
		perror("server socket creation");
		exit(1);
	}
E 27
E 26
E 8
E 3

	for ( ;; ) {
D 3
		newcontrol = tcp_accept(control);
		newdata = tcp_accept(data);
		absorb(newcontrol, newdata);
E 3
I 3
D 8
		newcontrol = tcp_accept(control, SOCKOPT_NONE);
		newdata = tcp_accept(data, SOCKOPT_READ);
E 8
I 8
		newdata = tcp_accept(data, SOCKOPT_WRITE);
E 8
		switch (fork()) {
		    case -1:
			perror("fork");
			break;
		    case 0:
D 8
			absorb(newcontrol, newdata);
E 8
I 8
D 17
			source(newdata);
E 17
I 17
D 19
			source(newdata, state);
E 19
I 19
			source(newdata);
E 19
E 17
E 8
			exit(0);
		    default:
D 8
			close(newcontrol);
E 8
			close(newdata);
			break;
		}
E 3
	}
}

/*
D 8
 * Read the number of bytes to be transfered on the control socket.
 * Read that many bytes on the data socket.
 * Write the performance results on the control socket.
E 8
I 8
D 27
 * Read the number of bytes to be transfered.
 * Write that many bytes on the data socket.
E 27
I 27
 * Read the message size.  Keep transferring 
 * data in message-size sized packets until
 * the socket goes away.
E 27
E 8
 */
D 7
absorb(control, data)
E 7
I 7
D 17
void
D 8
absorb(int control, int data)
E 8
I 8
source(int data)
E 17
I 17
D 19
void source(int data, state_t *state)
E 19
I 19
void source(int data)
E 19
E 17
E 8
E 7
{
D 13
	int	nread, save, nbytes;
E 13
I 13
D 15
	int	nread, nbytes;
E 15
I 15
D 19
	int	n, nbytes;
E 19
I 19
D 27
	int	tmp, n, m, nbytes;
	char	*buf;
E 27
I 27
	size_t	count, m;
I 28
	unsigned long	nbytes;
E 28
	char	*buf, scratch[100];
E 27
E 19
E 15
E 13
D 3
#ifdef	SO_RCVBUF
E 3
D 4
	char	buf[SOCKBUF];
E 4
I 4
D 5
	char	*buf = valloc(SOCKBUF);
E 5
I 5
D 8
	char	*buf = valloc(XFERSIZE);
E 8
E 5
E 4
D 3
	int	sockbuf = SOCKBUF;
E 3

I 22
	/*
	 * read the message size
	 */
E 22
I 4
D 17
	if (!buf) {
E 17
I 17
D 19
	if (!state->buf) {
E 17
		perror("valloc");
		exit(1);
	}
E 4
D 3
	while (setsockopt(data, SOL_SOCKET, SO_RCVBUF, &sockbuf, sizeof(int))) {
		sockbuf -= 128;
	}
#endif
E 3
D 5
	bzero(buf, SOCKBUF);
	if (read(control, buf, SOCKBUF) <= 0) {
E 5
I 5
D 14
	bzero(buf, XFERSIZE);
E 14
I 14
D 17
	bzero((void*)buf, XFERSIZE);
E 14
D 8
	if (read(control, buf, XFERSIZE) <= 0) {
E 8
I 8
	if (read(data, buf, XFERSIZE) <= 0) {
E 17
I 17
	bzero((void*)state->buf, XFERSIZE);
	if (read(data, state->buf, XFERSIZE) <= 0) {
E 19
I 19
D 27
	if (read(data, &tmp, sizeof(int)) != sizeof(int)) {
E 27
I 27
	bzero(scratch, 100);
	if (read(data, scratch, 100) <= 0) {
E 27
E 19
E 17
E 8
E 5
		perror("control nbytes");
		exit(7);
	}
D 13
	nbytes = save = atoi(buf);
E 13
I 13
D 17
	nbytes = atoi(buf);
E 17
I 17
D 19
	nbytes = atoi(state->buf);
E 19
I 19
D 22
	nbytes = ntohl(tmp);
E 22
I 22
D 27
	m = ntohl(tmp);
E 27
I 27
D 28
	sscanf(scratch, "%llu", &m);
E 28
I 28
	sscanf(scratch, "%lu", &nbytes);
	m = nbytes;
E 28
E 27
E 22
E 19
E 17
E 13

	/*
	 * A hack to allow turning off the absorb daemon.
	 */
D 22
     	if (nbytes == 0) {
E 22
I 22
     	if (m == 0) {
E 22
		tcp_done(TCP_DATA);
D 8
		tcp_done(TCP_CONTROL);
E 8
I 3
		kill(getppid(), SIGTERM);
E 3
		exit(0);
	}
I 19

D 22
	/*
	 * Now read the message size
	 */
	if (read(data, &tmp, sizeof(int)) != sizeof(int)) {
		perror("control msize");
		exit(7);
	}
	m = ntohl(tmp);
E 22
	buf = valloc(m);
	bzero(buf, m);

E 19
D 8
	start();
D 4
	while (nbytes > 0 && (nread = read(data, buf, sizeof(buf))) > 0)
E 4
I 4
D 5
	while (nbytes > 0 && (nread = read(data, buf, SOCKBUF)) > 0)
E 5
I 5
	while (nbytes > 0 && (nread = read(data, buf, XFERSIZE)) > 0)
E 8
I 8
D 15
	while (nbytes > 0 && (nread = write(data, buf, XFERSIZE)) > 0) {
E 8
E 5
E 4
		nbytes -= nread;
E 15
I 15
D 22
	while (nbytes > 0) {
E 22
I 22
	/*
	 * Keep sending messages until the connection is closed
	 */
D 27
	while (write(data, buf, m) > 0) {
E 27
I 27
	while (write(data, buf, m) == m) {
E 27
E 22
E 15
D 8
	stop();
	(void)close(2);		/* stderr - timing stats go to stderr */
	(void)dup(control);	/* stderr == control now */
	mb(save);
E 8
I 8
#ifdef	TOUCH
D 14
		bzero(buf, c);
E 14
I 14
D 15
		bzero((void*)buf, c);
E 15
I 15
D 17
		touch(buf, XFERSIZE);
E 17
I 17
D 19
		touch(state->buf, XFERSIZE);
E 19
I 19
		touch(buf, m);
E 19
E 17
E 15
E 14
#endif
I 15
D 17
		n = write(data, buf, XFERSIZE);
E 17
I 17
D 19
		n = write(data, state->buf, XFERSIZE);
E 17
		if (n <= 0) break;
E 19
I 19
D 22
		n = write(data, buf, m);
		if (n <= 0) {
			perror("data write");
			exit(1);
		}
E 19
		nbytes -= n;
E 22
E 15
	}
I 21
	free(buf);
E 21
E 8
D 17
}

I 12

int
main(int ac, char **av)
{
	if (ac != 2 && ac != 3) {
		fprintf(stderr, "Usage: %s -s OR %s [-]serverhost\n",
		    av[0], av[0]);
		exit(1);
	}
	buf = valloc(XFERSIZE);
D 14
	bzero(buf, XFERSIZE);
E 14
I 14
D 15
	bzero((void*)buf, XFERSIZE);
E 15
I 15
	touch(buf, XFERSIZE);
E 15
E 14
	if (!strcmp(av[1], "-s")) {
		if (fork() == 0) {
			server_main(ac, av);
		}
		exit(0);
	} else {
		client_main(ac, av);
	}
	return(0);
E 17
}
E 12
E 2
I 1
E 1
