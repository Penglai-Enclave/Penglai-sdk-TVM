h59276
s 00004/00004/00098
d D 1.8 00/10/16 17:21:28 staelin 9 8
c - Assorted code cleanups
cC
cK34241
cZ+02:00
e
s 00001/00001/00101
d D 1.7 00/07/30 11:46:16 staelin 8 7
c - Change type of "iterations" from uint64 to iter_t, which is a u_long
cC
cK34363
e
s 00012/00004/00090
d D 1.6 00/07/04 14:56:01 staelin 7 6
c - Update to incorporate new "-W <warmup>" and "-N <repetitions>" flags
cC
cK34270
cZ+03:00
e
s 00001/00001/00093
d D 1.5 00/04/17 13:06:03 staelin 6 5
c - convert 'char c' to 'int c' for getopt()
cC
cHhpli8.hpli.hpl.hp.com
cK15531
cZ+02:00
e
s 00048/00036/00046
d D 1.4 00/03/10 18:02:25 brucec 5 4
c Start on changes so test can be run in parallel "-P <parallelism>"
cC
cHrx7
cK15614
cZ-05:00
e
s 00007/00008/00075
d D 1.3 00/02/23 11:15:40 staelin 4 3
c Convert to use new draft benchmp() timing harness.
cC
cHhpli8.hpli.hpl.hp.com
cK58689
cZ+02:00
e
s 00000/00001/00083
d D 1.2 98/06/29 23:50:59 lm 3 2
c lint
cC
cK53896
cSAlpha2.11
e
s 00084/00000/00000
d D 1.1 97/10/19 23:50:16 lm 2 1
c Initial revision
cK54897
e
s 00000/00000/00000
d D 1.0 97/10/19 23:50:15 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK47898
cPsrc/lat_unix_connect.c
cR993911110514ea9
cV4
cX0x21
cZ-07:00
e
u
U
f e 0
f x 0x21
t
lmbench lat_unix_connect.c
T
I 2
/*
 * lat_unix_connect.c - simple UNIX connection latency test
 *
 * Three programs in one -
 *	server usage:	lat_connect -s
D 5
 *	client usage:	lat_connect hostname [N]
 *	shutdown:	lat_connect -hostname
E 5
I 5
D 7
 *	client usage:	lat_connect [-P <parallelism>]
E 7
I 7
 *	client usage:	lat_connect [-P <parallelism>] [-W <warmup>] [-N <repetitions>]
E 7
 *	shutdown:	lat_connect -q
E 5
 *
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
char	*id = "$Id$\n";
#include "bench.h"

D 5
void	server_main(int ac, char **av);
void	client_main(int ac, char **av);
E 5
I 5
#define CONNAME "/tmp/af_unix"
E 5

D 5
void
D 4
doit()
E 4
I 4
benchmark(uint64 iterations, void* cookie)
E 5
I 5
void server_main(void);

D 8
void benchmark(uint64 iterations, void* cookie)
E 8
I 8
void benchmark(iter_t iterations, void* cookie)
E 8
E 5
E 4
{
D 4
	int	sock = unix_connect("/tmp/af_unix");
	close(sock);
E 4
I 4
	while (iterations-- > 0) {
D 5
		int	sock = unix_connect("/tmp/af_unix");
E 5
I 5
		int	sock = unix_connect(CONNAME);
		if (sock <= 0)
			printf("error on iteration %lu\n",iterations);
E 5
		close(sock);
	}
E 4
}

D 5
int
main(int ac, char **av)
E 5
I 5
int main(int ac, char **av)
E 5
{
D 5
	if (ac > 1 && !strcmp(av[1], "-s")) {
		if (fork() == 0) {
			server_main(ac, av);
E 5
I 5
	int parallel = 1;
D 7
	char	*usage = "-s\n OR [-P <parallelism>]\n OR -q\n";
E 7
I 7
	int warmup = 0;
	int repetitions = TRIES;
D 9
	char	*usage = "-s\n OR [-P <parallelism>] [-W <warmup>] [-N <repetitions>]\n OR -q\n";
E 9
I 9
	char	*usage = "-s\n OR [-P <parallelism>] [-W <warmup>] [-N <repetitions>]\n OR -S\n";
E 9
E 7
D 6
	char	c;
E 6
I 6
	int	c;
E 6

D 9
	/* Start the server "-s" or Shut down the server "-q" */
E 9
I 9
	/* Start the server "-s" or Shut down the server "-S" */
E 9
	if (ac == 2) {
		if (!strcmp(av[1], "-s")) {
			if (fork() == 0) {
				server_main();
			}
			exit(0);
		}
D 9
		if (!strcmp(av[1], "-q")) {
E 9
I 9
		if (!strcmp(av[1], "-S")) {
E 9
			int sock = unix_connect(CONNAME);
			write(sock, "0", 1);
			close(sock);
			exit(0);
E 5
		}
D 5
		exit(0);
	} else {
		client_main(ac, av);
E 5
	}
D 5
	exit(0);
	/* NOTREACHED */
}
E 5

D 5
void
client_main(int ac, char **av)
{
D 3
	int     sock;
E 3
D 4
	char	buf[256];

E 4
	if (ac != 1) {
		fprintf(stderr, "usage: %s\n", av[0]);
		exit(1);
E 5
I 5
	/*
	 * Rest is client
	 */
D 7
	while (( c = getopt(ac, av, "P:")) != EOF) {
E 7
I 7
	while (( c = getopt(ac, av, "P:W:N:")) != EOF) {
E 7
		switch(c) {
		case 'P':
			parallel = atoi(optarg);
			if (parallel <= 0) lmbench_usage(ac, av, usage);
			break;
I 7
		case 'W':
			warmup = atoi(optarg);
			break;
		case 'N':
			repetitions = atoi(optarg);
			break;
E 7
		default:
			lmbench_usage(ac, av, usage);
			break;
		}
E 5
	}

D 4
	BENCH(doit(), 100000);
	sprintf(buf, "UNIX connection cost ");
	micro(buf, get_n());
E 4
I 4
D 5
	benchmp(NULL, benchmark, NULL, 0, 1, NULL);
E 5
I 5
	if (optind != ac) {
		lmbench_usage(ac, av, usage);
	}

D 7
	benchmp(NULL, benchmark, NULL, 0, parallel, NULL);
E 7
I 7
	benchmp(NULL, benchmark, NULL, 0, parallel, warmup, repetitions, NULL);
E 7
E 5
D 9
	micro("UNIX connection cost ", get_n());
E 9
I 9
	micro("UNIX connection cost", get_n());
E 9
E 4
D 5
	exit(0);
	/* NOTREACHED */
E 5
}

D 5
void
server_main(int ac, char **av)
E 5
I 5
void server_main(void)
E 5
{
	int     newsock, sock;
	char	c;

D 5
	if (ac != 2) {
		fprintf(stderr, "usage: %s -s\n", av[0]);
		exit(1);
	}
E 5
	GO_AWAY;
D 5
	sock = unix_server("/tmp/af_unix");
E 5
I 5
	sock = unix_server(CONNAME);
E 5
	for (;;) {
		newsock = unix_accept(sock);
		c = 0;
		read(newsock, &c, 1);
		if (c && c == '0') {
D 5
			unix_done(sock, "/tmp/af_unix");
E 5
I 5
			unix_done(sock, CONNAME);
E 5
			exit(0);
		}
		close(newsock);
	}
D 5
	/* NOTREACHED */
E 5
}
E 2
I 1
E 1
