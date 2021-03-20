h21870
s 00003/00003/00193
d D 1.3 00/09/26 16:00:18 staelin 4 3
c - Fix bug in command-line parsing for "-S <serverhost>" option
cC
cK16678
e
s 00002/00002/00194
d D 1.2 00/07/30 11:46:05 staelin 3 2
c - Change type of "iterations" from uint64 to iter_t, which is a u_long
cC
cK16905
e
s 00196/00000/00000
d D 1.1 00/07/06 15:55:22 staelin 2 1
cC
cK16065
cO-rw-rw-r--
e
s 00000/00000/00000
d D 1.0 00/07/06 15:55:21 staelin 1 0
c BitKeeper file /tmp_mnt/usr/WebPaper/users/staelin/src/LMbench/src/bw_udp.c
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHhpli8.hpli.hpl.hp.com
cK29470
cPsrc/bw_udp.c
cR6a1328dc1b227a50
cV4
cX0xa1
cZ+03:00
e
u
U
f e 0
f x 0xa1
t
T
I 2
/*
 * bw_udp.c - simple UDP bandwidth test
 *
 * Three programs in one -
 *	server usage:	bw_tcp -s
 *	client usage:	bw_tcp [-m <message size>] [-P <parallelism>] [-W <warmup>] [-N <repetitions>] hostname [bytes]
D 4
 *	shutdown:	bw_tcp -hostname
E 4
I 4
 *	shutdown:	bw_tcp -S hostname
E 4
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

#define MAX_MSIZE (10 * 1024 * 1024)

typedef struct _state {
	int	sock;
	int	seq;
	long	move;
	long	msize;
	char	*server;
	int	fd;
	char	*buf;
} state_t;

void	server_main();
void	client_main(int parallel, state_t *state);
void	init(void *cookie);
void	cleanup(void *cookie);

D 3
void	loop_transfer(uint64 iter, void *cookie);
E 3
I 3
void	loop_transfer(iter_t iterations, void *cookie);
E 3

int main(int ac, char **av)
{
	int	parallel = 1;
	int	warmup = 0;
	int	repetitions = TRIES;
	int	server = 0;
	state_t state;
	char	*usage = "-s\n OR [-m <message size>] [-W <warmup>] [-N <repetitions>] server [size]\n OR -S serverhost\n";
	int	c;
	uint64	usecs;
	
	state.msize = 0;
	state.move = 10*1024*1024;

	/* Rest is client argument processing */
D 4
	while (( c = getopt(ac, av, "sSm:W:N:")) != EOF) {
E 4
I 4
	while (( c = getopt(ac, av, "sS:m:W:N:")) != EOF) {
E 4
		switch(c) {
		case 's': /* Server */
			if (fork() == 0) {
				server_main();
			}
			exit(0);
		case 'S': /* shutdown serverhost */
		{
			int seq, n;
D 4
			int sock = udp_connect(av[optind],
E 4
I 4
			int sock = udp_connect(optarg,
E 4
					       UDP_XACT,
					       SOCKOPT_NONE);
			for (n = -1; n > -5; --n) {
				seq = htonl(n);
				(void) send(sock, &seq, sizeof(int), 0);
			}
			close(sock);
			exit (0);
		}
		case 'm':
			state.msize = atoi(optarg);
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

	if (optind < ac - 2 || optind >= ac) {
		lmbench_usage(ac, av, usage);
	}

	state.server = av[optind++];
	if (optind < ac) {
		state.move = bytes(av[optind]);
	}
	if (state.msize == 0) {
		state.msize = state.move;
	}
	/* make the number of bytes to move a multiple of the message size */
	if (state.move % state.msize) {
		state.move += state.move - state.move % state.msize;
	}

	state.buf = valloc(state.msize);
	if (!state.buf) {
		perror("valloc");
		exit(1);
	}
	touch(state.buf, state.msize);

	/*
	 * Make one run take at least 5 seconds.
	 * This minimizes the effect of connect & reopening TCP windows.
	 */
	benchmp(init, loop_transfer, cleanup, LONGER, parallel, warmup, repetitions, &state );

out:	(void)fprintf(stderr, "socket UDP bandwidth using %s: ", state.server);
	mb(state.move * get_n() * parallel);
}

void init(void * cookie)
{
	state_t *state = (state_t *) cookie;

	state->sock = udp_connect(state->server, UDP_XACT, SOCKOPT_NONE);
	state->seq = 0;
	state->buf = (char*)malloc(state->msize);
}

D 3
void loop_transfer(uint64 iterations, void *cookie)
E 3
I 3
void loop_transfer(iter_t iterations, void *cookie)
E 3
{
	state_t *state = (state_t *) cookie;
	char	*server = state->server;
	int	sock = state->sock;
	long	control[2], nbytes;

	nbytes = state->move;
	control[0] = state->move;
	control[1] = state->msize;

	while (iterations-- > 0) {
		if (send(sock, control, 2 * sizeof(long), 0) != 2 * sizeof(long)) {
			perror("bw_udp client: send failed");
			exit(5);
		}
		while (nbytes > 0) {
			if (recv(sock, state->buf, state->msize, 0) != state->msize) {
				perror("bw_udp client: recv failed");
				exit(5);
			}
			nbytes -= state->msize;
		}
	}
}

void
cleanup(void * cookie)
{
	state_t *state = (state_t *) cookie;

	close(state->sock);
	free(state->buf);
}

void
server_main()
{
	char	*buf = (char*)valloc(MAX_MSIZE);
	int     sock, namelen, seq = 0;
	long	nbytes, msize;
	struct sockaddr_in it;

	GO_AWAY;

	sock = udp_server(UDP_XACT, SOCKOPT_NONE);

	while (1) {
		namelen = sizeof(it);
		if (recvfrom(sock, (void*)buf, 2 * sizeof(long), 0, 
		    (struct sockaddr*)&it, &namelen) < 0) {
			fprintf(stderr, "bw_udp server: recvfrom: got wrong size\n");
			exit(9);
		}
		nbytes = ntohl(*(long*)buf);
		msize = ntohl(*((long*)buf + 1));
		while (nbytes > 0) {
			if (sendto(sock, (void*)buf, msize, 0, 
				   (struct sockaddr*)&it, sizeof(it)) < 0) {
				perror("bw_udp sendto");
				exit(9);
			}
			nbytes -= msize;
		}
	}
}

E 2
I 1
E 1
