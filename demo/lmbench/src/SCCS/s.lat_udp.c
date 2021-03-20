h20430
s 00001/00001/00201
d D 1.21 00/10/31 10:00:49 staelin 22 21
c - Add SOCKOPT_REUSE to tcp_server() call
cC
cK60003
e
s 00001/00001/00201
d D 1.20 00/10/16 17:18:09 staelin 21 20
c - Add "-W" and "-N" flags to lat_udp's getopt call
cC
cK59919
cZ+02:00
e
s 00001/00001/00201
d D 1.19 00/09/28 12:14:49 staelin 20 19
c - Adjust lat_udp's timeout so you only run Alarm() once per timing interval
cC
cK59638
e
s 00003/00002/00199
d D 1.18 00/09/26 16:00:22 staelin 19 18
c - Fix bug in command-line parsing for "-S <serverhost>" option
cC
cK61569
e
s 00017/00003/00184
d D 1.17 00/09/13 14:45:40 staelin 18 17
c - Add a timeout in lat_udp since HP-UX seems to drop packets
cC
cK59194
e
s 00002/00002/00185
d D 1.16 00/07/30 11:46:15 staelin 17 16
c - Change type of "iterations" from uint64 to iter_t, which is a u_long
cC
cK49409
e
s 00004/00009/00183
d D 1.15 00/07/06 15:51:19 staelin 16 15
c - Move server start up into getopt() loop to simplify code a little
cC
cK48569
e
s 00028/00012/00164
d D 1.14 00/07/04 14:56:00 staelin 15 14
c - Update to incorporate new "-W <warmup>" and "-N <repetitions>" flags
cC
cK51390
e
s 00084/00073/00092
d D 1.13 00/06/21 19:28:43 staelin 14 13
c - Cleaned up command line parsing
cC
cK21274
cZ+03:00
e
s 00001/00001/00164
d D 1.12 00/04/17 13:06:03 staelin 13 12
c - convert 'char c' to 'int c' for getopt()
cC
cHhpli8.hpli.hpl.hp.com
cK02104
cZ+02:00
e
s 00088/00050/00077
d D 1.11 00/03/16 18:07:49 brucec 12 11
c Make changes for parallel runs ("-P <parallelism>").  Need to
c expand this test to have multiple server processes listening on
c multiple ports for the parallel cases.
c 
cC
cHrx7
cK02187
cZ-05:00
e
s 00005/00005/00122
d D 1.10 97/06/15 22:38:58 lm 11 10
c lint
cC
cK65433
cSAlpha2.11
e
s 00017/00015/00110
d D 1.9 97/06/13 20:39:50 lm 10 9
c lint
cK65293
e
s 00011/00010/00114
d D 1.8 97/06/12 21:30:06 lm 9 8
c new bench.h macros.
cK64839
cZ-07:00
e
s 00003/00001/00121
d D 1.7 96/11/13 16:09:37 lm 8 7
c timing.c interfaces.
cK00108
e
s 00016/00025/00106
d D 1.6 96/11/11 03:36:51 lm 7 6
c Auto adjusting changes.
cK00167
e
s 00013/00008/00118
d D 1.5 96/11/08 20:04:05 lm 6 5
c gcc -Wall cleanup.
cK08729
cZ-08:00
e
s 00000/00001/00126
d D 1.4 96/05/30 00:33:07 lm 5 4
c no what strings
cK61856
e
s 00015/00004/00112
d D 1.3 96/05/21 23:15:50 lm 4 3
c network byte order on the sequence number. Thanks Davem.
cK63927
cZ-07:00
e
s 00002/00002/00114
d D 1.2 95/03/10 18:15:39 lm 3 2
c sockopt stuff.
cK47871
e
s 00116/00000/00000
d D 1.1 94/11/18 00:49:48 lm 2 1
c Initial revision
cK45827
e
s 00000/00000/00000
d D 1.0 94/11/18 00:49:47 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK24062
cPsrc/lat_udp.c
cR7459a472444854ce
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
 * udp_xact.c - simple UDP transaction latency test
 *
 * Three programs in one -
D 15
 *	server usage:	udp_xact -s
 *	client usage:	udp_xact hostname
 *	shutdown:	udp_xact -hostname
E 15
I 15
 *	server usage:	lat_udp -s
 *	client usage:	lat_udp [-P <parallelism>] [-W <warmup>] [-N <repetitions>] hostname
 *	shutdown:	lat_udp -S hostname
E 15
 *
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
char	*id = "$Id$\n";
I 7
D 9
#include "timing.h"
E 9
E 7
#include "bench.h"
D 7
#include "lib_udp.c"
#include "timing.c"
E 7
I 7
D 9
#include "lib_udp.h"
E 9
E 7

I 15
#define MAX_MSIZE (10 * 1024 * 1024)

E 15
D 6
main(ac, av)
	char  **av;
E 6
I 6
void	client_main(int ac, char **av);
D 12
void	server_main(int ac, char **av);
E 12
I 12
D 14
void	server_main();
E 14
I 14
D 15
void	server_main(int msize);
E 15
I 15
void	server_main();
I 18
void	timeout();
E 18
E 15
E 14
void	init(void *cookie);
void	cleanup(void *cookie);
D 17
void    doit(uint64 iter, void *cookie);
E 17
I 17
void    doit(iter_t iterations, void *cookie);
E 17

typedef struct _state {
	int	sock;
	int	seq;
I 14
	int	msize;
E 14
	char	*server;
I 14
	char	*buf;
E 14
} state_t;
E 12

I 10

D 12
void
doit(int sock, int seq)
E 12
I 12
D 14
void doit(uint64 iterations, void *cookie)
E 12
{
I 12
	state_t *state = (state_t *) cookie;
	int seq = state->seq;
E 12
	int net = htonl(seq);
I 12
	int sock = state->sock;
E 12
	int ret;

D 12
	if (send(sock, &net, sizeof(net), 0) != sizeof(net)) {
		perror("lat_udp client: send failed");
		exit(5);
	}
	if (recv(sock, &ret, sizeof(ret), 0) != sizeof(ret)) {
		perror("lat_udp client: recv failed");
		exit(5);
E 12
I 12

	while (iterations-- > 0) {
		seq++;
		if (send(sock, &net, sizeof(net), 0) != sizeof(net)) {
			perror("lat_udp client: send failed");
			exit(5);
		}
		if (recv(sock, &ret, sizeof(ret), 0) != sizeof(ret)) {
			perror("lat_udp client: recv failed");
			exit(5);
		}
E 12
	}
I 12
	state->seq = seq;
E 12
}

E 14
E 10
D 12
int
main(int ac, char **av)
E 12
I 12
int main(int ac, char **av)
E 12
E 6
{
I 12
	state_t state;
D 14
	int parallel = 1;
E 14
I 14
	int	c;
	int	parallel = 1;
I 15
	int	warmup = 0;
	int	repetitions = TRIES;
E 15
	int	server = 0;
	int	shutdown = 0;
	int	msize = 4;
E 14
 	char	buf[256];
D 14
	char	*usage = "-s\n OR [-P <parallelism>] server\n OR [-]serverhost\n";
E 14
I 14
D 15
	char	*usage = "-s\n OR [-S] [-P <parallelism>] server\n NOTE: message size must be >= 4\n";
E 15
I 15
	char	*usage = "-s\n OR [-S] [-m <message size>] [-P <parallelism>] [-W <warmup>] [-N <repetitions>] server\n NOTE: message size must be >= 4\n";
E 15

E 14
E 12
D 5
	write(2, id, strlen(id));
E 5
I 4
	if (sizeof(int) != 4) {
		fprintf(stderr, "lat_udp: Wrong sequence size\n");
D 11
		exit(1);
E 11
I 11
		return(1);
E 11
	}
E 4
D 12
	if (ac != 2 && ac != 3) {
		fprintf(stderr, "Usage: %s -s OR %s [-]serverhost [proto]\n",
		    av[0], av[0]);
D 11
		exit(1);
E 11
I 11
		return(1);
E 11
	}
E 12
I 12
D 14
	if (ac == 1)
		lmbench_usage(ac, av, usage);
E 12
	if (!strcmp(av[1], "-s")) {
		if (fork() == 0) {
D 12
			server_main(ac, av);
E 12
I 12
			server_main();
E 12
		}
D 11
		exit(0);
E 11
I 11
		return(0);
E 11
D 12
	} else {
		client_main(ac, av);
E 12
I 12
	} else { /*
		  * Client args are -server OR [-P <parallelism>] server
		  */
D 13
		char c;
E 13
I 13
		int c;
E 13
		if (ac == 2) {
			if (!strcmp(av[1],"-"))
				lmbench_usage(ac, av, usage);
			if (av[1][0] == '-') { /* shut down server */
				int seq = -1;
				int sock = udp_connect(&av[1][1],
						       UDP_XACT,
						       SOCKOPT_NONE);
				while (seq-- > -5) {
					int	net = htonl(seq);
					(void) send(sock, &net,
						    sizeof(net), 0);
				}
				close(sock);
				exit(0);
E 14
I 14

D 19
	while (( c = getopt(ac, av, "sSm:P:")) != EOF) {
E 19
I 19
D 21
	while (( c = getopt(ac, av, "sS:m:P:")) != EOF) {
E 21
I 21
	while (( c = getopt(ac, av, "sS:m:P:W:N:")) != EOF) {
E 21
E 19
		switch(c) {
		case 's': /* Server */
D 16
			server = 1;
			break;
E 16
I 16
			if (fork() == 0) {
				server_main();
			}
			exit(0);
E 16
		case 'S': /* shutdown serverhost */
		{
			int seq, n;
D 19
			int sock = udp_connect(av[optind],
E 19
I 19
			int sock = udp_connect(optarg,
E 19
					       UDP_XACT,
					       SOCKOPT_NONE);
			for (n = -1; n > -5; --n) {
				seq = htonl(n);
				(void) send(sock, &seq, sizeof(int), 0);
E 14
			}
I 14
			close(sock);
			exit (0);
E 14
		}
D 14

		while (( c = getopt(ac, av, "P:")) != EOF) {
			switch(c) {
			case 'P':
				parallel = atoi(optarg);
				if (parallel <= 0)
					lmbench_usage(ac, av, usage);
				break;
			default:
E 14
I 14
		case 'm':
			msize = atoi(optarg);
			if (msize < sizeof(int)) {
E 14
				lmbench_usage(ac, av, usage);
D 14
				break;
E 14
I 14
				msize = 4;
E 14
			}
I 15
			if (msize > MAX_MSIZE) {
				lmbench_usage(ac, av, usage);
				msize = MAX_MSIZE;
			}
E 15
I 14
			break;
		case 'P':
			parallel = atoi(optarg);
			if (parallel <= 0)
				lmbench_usage(ac, av, usage);
			break;
I 15
		case 'W':
			warmup = atoi(optarg);
			break;
		case 'N':
			repetitions = atoi(optarg);
			break;
E 15
		default:
			lmbench_usage(ac, av, usage);
			break;
E 14
		}
I 14
D 16
	}
E 14

D 14
		if (optind + 1 != ac) {
			lmbench_usage(ac, av, usage);
E 14
I 14
	if (server) {
		if (fork() == 0) {
D 15
			server_main(msize);
E 15
I 15
			server_main();
E 15
E 14
		}
D 14
		state.server = av[optind];
E 14
I 14
		exit(0);
E 16
	}

	if (optind + 1 != ac) {
		lmbench_usage(ac, av, usage);
E 14
E 12
	}
D 11
	exit(0);
E 11
I 11
D 12
	return(0);
E 12
I 12

D 14
	benchmp(init, doit, cleanup,
		SHORT, parallel, &state);
E 14
I 14
	state.server = av[optind];
	state.msize = msize;
D 15
	benchmp(init, doit, cleanup, SHORT, parallel, &state);
E 15
I 15
	benchmp(init, doit, cleanup, SHORT, parallel, 
		warmup, repetitions, &state);
E 15
E 14
	sprintf(buf, "UDP latency using %s", state.server);
	micro(buf, get_n());
I 14
	exit(0);
E 14
E 12
E 11
}

D 6
client_main(ac, av)
	char  **av;
E 6
I 6
D 12
void
client_main(int ac, char **av)
E 12
I 12
D 18
void init(void * cookie)
E 18
I 18
void
init(void * cookie)
E 18
E 12
E 6
{
D 12
	int     sock;
D 9
	int     seq = 0;
E 9
I 9
	int     seq = -1;
E 9
D 7
	int     ret;
	int     n = 0;
	char    buf[200];
E 7
I 7
D 11
	int     i, N, net, ret;
E 11
E 7
	char   *server;
I 8
	char	buf[256];
E 8

	if (ac != 2) {
		fprintf(stderr, "Usage: %s hostname\n", av[0]);
		exit(1);
	}
E 12
I 12
	state_t *state = (state_t *) cookie;
E 12

D 12
	server = av[1][0] == '-' ? &av[1][1] : av[1];
D 3
	sock = udp_connect(server, UDP_XACT);
E 3
I 3
	sock = udp_connect(server, UDP_XACT, SOCKOPT_NONE);
E 12
I 12
	state->sock = udp_connect(state->server, UDP_XACT, SOCKOPT_NONE);
	state->seq = 0;
I 14
	state->buf = (char*)malloc(state->msize);
I 18
	
	signal(SIGALRM, timeout);
	alarm(15);
E 18
}

D 17
void doit(uint64 iterations, void *cookie)
E 17
I 17
D 18
void doit(iter_t iterations, void *cookie)
E 18
I 18
void
doit(iter_t iterations, void *cookie)
E 18
E 17
{
	state_t *state = (state_t *) cookie;
	int seq = state->seq;
	int net = htonl(seq);
	int sock = state->sock;
	int ret;

I 20
	alarm(15);
E 20
	while (iterations-- > 0) {
I 19
D 20
		if (iterations % 100 == 0) alarm(15);
E 20
E 19
		*(int*)state->buf = htonl(seq++);
		if (send(sock, state->buf, state->msize, 0) != state->msize) {
			perror("lat_udp client: send failed");
			exit(5);
		}
		if (recv(sock, state->buf, state->msize, 0) != state->msize) {
			perror("lat_udp client: recv failed");
			exit(5);
		}
	}
	state->seq = seq;
E 14
}
E 12
E 3

D 12
	/*
	 * Stop server code.
	 */
	if (av[1][0] == '-') {
		while (seq-- > -5) {
D 4
			(void) send(sock, &seq, sizeof(seq), 0);
E 4
I 4
			int	net = htonl(seq);
E 12
I 12
D 18
void cleanup(void * cookie)
E 18
I 18
void
cleanup(void * cookie)
E 18
{
	state_t *state = (state_t *) cookie;
E 12

D 12
			(void) send(sock, &net, sizeof(net), 0);
E 4
		}
		exit(0);
	}
I 9
	BENCH(doit(sock, ++seq), MEDIUM);
	sprintf(buf, "UDP latency using %s", server);
	micro(buf, get_n());
	exit(0);
E 12
I 12
	close(state->sock);
I 14
	free(state->buf);
I 18
}

void
timeout()
{
	fprintf(stderr, "Recv timed out\n");
	exit(1);
E 18
E 14
E 12
}
E 9

I 11
D 12
/* ARGSUSED */
E 12
E 11
D 7
	start();
	while (seq++ < 5000) {
D 4
		if (send(sock, &seq, sizeof(seq), 0) != sizeof(seq)) {
E 4
I 4
		int	net = htonl(seq);

		if (send(sock, &net, sizeof(net), 0) != sizeof(net)) {
E 4
			perror("lat_udp client: send failed");
			exit(5);
		}
		if (recv(sock, &ret, sizeof(ret), 0) != sizeof(ret)) {
			perror("lat_udp client: recv failed");
			exit(5);
		}
I 4
		ret = ntohl(ret);
E 4
		if (seq == ret) {
			n++;
		}
E 7
I 7
D 9
	LOOP_FIRST(N, i, MEDIUM);
	net = htonl(seq);
	seq++;
E 9
I 9
D 10
doit(int sock, int seq)
{
	int net = htonl(seq);
	int ret;

E 9
	if (send(sock, &net, sizeof(net), 0) != sizeof(net)) {
		perror("lat_udp client: send failed");
		exit(5);
E 7
	}
D 7
	stop();
	sprintf(buf, "UDP latency using %s", server);
	micro(buf, n);
E 7
I 7
	if (recv(sock, &ret, sizeof(ret), 0) != sizeof(ret)) {
		perror("lat_udp client: recv failed");
		exit(5);
	}
D 9
	LOOP_LAST(N, i, MEDIUM);
D 8
	fprintf(stderr, "UDP latency using %s: %d microseconds\n", server, i/N);
E 8
I 8
	sprintf(buf, "UDP latency using %s", server);
	micro(buf, N);
E 8
	exit(0);
E 9
E 7
}

E 10
D 6
server_main(ac, av)
	char  **av;
E 6
I 6
void
D 12
server_main(int ac, char **av)
E 12
I 12
D 14
server_main()
E 14
I 14
D 15
server_main(int msize)
E 15
I 15
server_main()
E 15
E 14
E 12
E 6
{
D 4
	int     sock, sent, namelen, seq = 0;
E 4
I 4
D 14
	int     net, sock, sent, namelen, seq = 0;
E 14
I 14
D 15
	char	*buf = (char*)valloc(msize);
E 15
I 15
	char	*buf = (char*)valloc(MAX_MSIZE);
E 15
	int     sock, sent, namelen, seq = 0;
E 14
E 4
	struct sockaddr_in it;

	GO_AWAY;

D 3
	sock = udp_server(UDP_XACT);
E 3
I 3
D 22
	sock = udp_server(UDP_XACT, SOCKOPT_NONE);
E 22
I 22
	sock = udp_server(UDP_XACT, SOCKOPT_REUSE);
E 22
E 3

	while (1) {
I 15
		int nbytes;
E 15
		namelen = sizeof(it);
D 6
		if (recvfrom(sock, &sent, sizeof(sent), 0, &it, &namelen) < 0) {
E 6
I 6
D 14
		if (recvfrom(sock, (void*)&sent, sizeof(sent), 0, 
E 14
I 14
D 15
		if (recvfrom(sock, (void*)buf, msize, 0, 
E 14
		    (struct sockaddr*)&it, &namelen) < 0) {
E 15
I 15
		if ((nbytes = recvfrom(sock, (void*)buf, MAX_MSIZE, 0, 
		    (struct sockaddr*)&it, &namelen)) < 0) {
E 15
E 6
			fprintf(stderr, "lat_udp server: recvfrom: got wrong size\n");
			exit(9);
		}
I 4
D 14
		sent = ntohl(sent);
E 14
I 14
		sent = ntohl(*(int*)buf);
E 14
E 4
		if (sent < 0) {
			udp_done(UDP_XACT);
			exit(0);
		}
		if (sent != ++seq) {
D 7
printf("lat_udp server: wanted %d, got %d, resyncing\n", seq, sent);	/**/
E 7
			seq = sent;
		}
D 4
		if (sendto(sock, &seq, sizeof(seq), 0, &it, sizeof(it)) < 0) {
E 4
I 4
D 14
		net = htonl(seq);
D 6
		if (sendto(sock, &net, sizeof(net), 0, &it, sizeof(it)) < 0) {
E 6
I 6
		if (sendto(sock, (void*)&net, sizeof(net), 0, 
E 14
I 14
		*(int*)buf = htonl(seq);
D 15
		if (sendto(sock, (void*)buf, msize, 0, 
E 15
I 15
		if (sendto(sock, (void*)buf, nbytes, 0, 
E 15
E 14
		    (struct sockaddr*)&it, sizeof(it)) < 0) {
E 6
E 4
			perror("lat_udp sendto");
			exit(9);
		}
	}
}
E 2
I 1
E 1
