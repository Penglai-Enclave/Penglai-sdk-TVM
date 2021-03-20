H64361
s 00041/00020/00150
d D 1.19 02/09/29 21:53:51 staelin 20 19
c - switch from 'int' to 'size_t' for better portability to large memory 
c   machines
cC
cHfirewall.staelin.co.il
cK57014
cZ+03:00
e
s 00004/00002/00166
d D 1.18 00/10/31 10:00:31 staelin 19 18
c - Only print any output if benchmark produces a valid result
c   (needed for mb() and micromb()-style outputs where prefix is
c   printed by main() and only the result is printed by the output
c   routine, and only then if the result is valid)
cC
cK64130
e
s 00001/00001/00167
d D 1.17 00/10/25 12:41:10 staelin 18 17
c - Bug-fix bw_unix's command line parsing
cC
cK62468
e
s 00004/00002/00164
d D 1.16 00/10/16 17:22:21 staelin 17 16
c - Assorted code cleanups
cC
cK60767
cZ+02:00
e
s 00024/00004/00142
d D 1.15 00/08/02 18:04:56 staelin 16 15
c - Add code to deal with killing child processes when signaled by the parent so we don't
c   leave zombies lying around...
cC
cK55876
e
s 00002/00002/00144
d D 1.14 00/07/30 11:46:05 staelin 15 14
c - Change type of "iterations" from uint64 to iter_t, which is a u_long
cC
cK36601
e
s 00013/00004/00133
d D 1.13 00/07/04 14:55:50 staelin 14 13
c - Update to incorporate new "-W <warmup>" and "-N <repetitions>" flags
cC
cK36415
cZ+03:00
e
s 00013/00004/00124
d D 1.12 00/03/01 14:34:23 staelin 13 12
c - Tweak getopt harness
cC
cHhpli8.hpli.hpl.hp.com
cK17648
cZ+02:00
e
s 00011/00004/00117
d D 1.11 00/02/28 17:01:12 brucec 12 11
c Add getopt() handling of optional -P <parallelism> argument.
cC
cHrx7
cK09297
cZ-05:00
e
s 00068/00031/00053
d D 1.10 00/02/23 11:15:38 staelin 11 10
c Convert system to use new draft benchmp() timing harness.
cC
cHhpli8.hpli.hpl.hp.com
cK63927
cZ+02:00
e
s 00004/00001/00080
d D 1.9 97/06/25 10:25:01 lm 10 9
c ifdef TOUCH
cC
cK60058
e
s 00001/00001/00080
d D 1.8 97/06/16 19:05:50 lm 9 8
c lint
cK57336
e
s 00006/00006/00075
d D 1.7 97/06/15 22:38:58 lm 8 7
c lint
cK56779
e
s 00026/00021/00055
d D 1.6 97/06/12 21:30:06 lm 7 6
c new bench.h macros.
cK53045
cZ-07:00
e
s 00003/00003/00073
d D 1.5 96/11/13 16:09:37 lm 6 5
c bugs.
cK46477
e
s 00042/00095/00034
d D 1.4 96/11/11 03:36:51 lm 5 4
c Auto adjusting changes.
cK45183
e
s 00015/00006/00114
d D 1.3 96/11/08 19:58:18 lm 4 3
c gcc -Wall cleanup.
cK37765
cZ-08:00
e
s 00020/00011/00100
d D 1.2 96/05/30 00:32:16 lm 3 2
c autotiming
cK21975
e
s 00111/00000/00000
d D 1.1 96/05/22 00:33:03 lm 2 1
c Initial revision
cK15440
e
s 00000/00000/00000
d D 1.0 96/05/22 00:33:02 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK32506
cPsrc/bw_unix.c
cR3ecbff5984316fe
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
 * bw_unix.c - simple Unix stream socket bandwidth test
 *
I 12
D 14
 * Usage: bw_unix [-P <parallelism>]
E 14
I 14
D 20
 * Usage: bw_unix [-P <parallelism>] [-W <warmup>] [-N <repetitions>]
E 20
I 20
 * Usage: bw_unix [-m <message size>] [-M <total bytes>] \
 *		[-P <parallelism>] [-W <warmup>] [-N <repetitions>]
E 20
E 14
 *
E 12
D 20
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
E 20
I 20
 * Copyright (c) 1994 Larry McVoy.  
 * Copyright (c) 2002 Carl Staelin.
 * Distributed under the FSF GPL with additional restriction that results 
 * may published only if:
E 20
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
D 11
char	*id = "$Id$\n";
E 11
I 11
D 12
char	*id = "$Id: s.bw_unix.c 1.9 97/06/25 10:25:01-07:00 lm $\n";
E 12
I 12
char	*id = "$Id$\n";
E 12
E 11
D 5
#include "timing.c"
E 5
I 5
D 7
#include "timing.h"
E 7
I 7

E 7
#include "bench.h"
E 5
D 7
#include <sys/socket.h>
I 4
#include <sys/types.h>
#include <sys/wait.h>
E 7
E 4
D 3
#define	N	1000
E 3

I 3
D 5
int	N = 100;
int	notdone = 1;
I 4
void	client(int sock);
void	server(int sock);
int	writen(int fd, char *buf, int n);
int	readn(int fd, char *buf, int n);
E 5
I 5
D 7
int	XFER	= 100*1024*1024;
E 7
I 7
D 8
extern	void	exit();		/* for lint on SunOS 4.x */
void		writer(), reader();
E 8
I 8
D 11
void	reader(int control[2], int pipes[2], int bytes);
void	writer(int control[2], int pipes[2]);
E 11
I 11
D 15
void	reader(uint64 iterations, void * cookie);
E 15
I 15
void	reader(iter_t iterations, void * cookie);
E 15
D 20
void	writer(int control[2], int pipes[2], char* buf);
E 20
I 20
void	writer(int controlfd, int writefd, char* buf, void* cookie);
E 20
E 11
E 8

D 20
int	XFER	= 10*1024*1024;
E 20
I 20
size_t	XFER	= 10*1024*1024;
E 20
D 11
int	pid;
E 7
char	*buf;
E 11
D 7
void	reader(int pipes[2]);
void	writer(int pipes[2]);
E 7
E 5
E 4

E 3
D 4
main()
E 4
I 4
D 11
int
D 7
main(int ac, char **av)
E 7
I 7
main()
E 7
E 4
{
E 11
I 11
struct _state {
	int	pid;
D 20
	int	bytes;	/* bytes to read/write in one iteration */
E 20
I 20
	size_t	xfer;	/* bytes to read/write per "packet" */
	size_t	bytes;	/* bytes to read/write in one iteration */
E 20
	char	*buf;	/* buffer memory space */
E 11
D 5
	int	sv[2];
E 5
I 5
	int	pipes[2];
D 7
	int	pid, N, i;
E 7
I 7
	int	control[2];
I 11
	int	initerr;
};

D 16
void initialize(void *cookie)
E 16
I 16
struct _state* pGlobalState;

void
sigterm_handler(int n)
{
	if (pGlobalState->pid) {
		kill(SIGKILL, pGlobalState->pid);
	}
	exit(0);
}

void 
initialize(void *cookie)
E 16
{
	struct _state* state = (struct _state*)cookie;
E 11
E 7
E 5

D 3
	write(2, id, strlen(id));
E 3
D 5
	if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) == -1) {
E 5
I 5
D 11
	buf = valloc(XFERSIZE);
D 9
	bzero(buf, XFERSIZE);
E 9
I 9
D 10
	bzero((void*)buf, XFERSIZE);
E 10
I 10
	touch(buf, XFERSIZE);
E 10
E 9
	if (socketpair(AF_UNIX, SOCK_STREAM, 0, pipes) == -1) {
E 11
I 11
	state->buf = valloc(XFERSIZE);
	touch(state->buf, XFERSIZE);
	state->initerr = 0;
	if (socketpair(AF_UNIX, SOCK_STREAM, 0, state->pipes) == -1) {
E 11
E 5
		perror("socketpair");
I 7
D 11
		return (1);
E 11
I 11
		state->initerr = 1;
		return;
E 11
E 7
	}
I 7
D 11
	if (pipe(control) == -1) {
E 11
I 11
	if (pipe(state->control) == -1) {
E 11
		perror("pipe");
D 8
		exit(1);
E 8
I 8
D 11
		return(1);
E 11
I 11
		state->initerr = 2;
		return;
E 11
E 8
	}
E 7
D 3
	if (fork() == 0) {
		doserver(sv[0]);
	} else {
		doclient(sv[1]);
	}
E 3
I 3
D 5
	do {
		if (fork() == 0) {
D 4
			doserver(sv[0]);
E 4
I 4
			server(sv[0]);
E 4
		} else {
D 4
			doclient(sv[1]);
E 4
I 4
			client(sv[1]);
E 4
		}
	} while (notdone);
E 5
I 5
D 11
	switch (pid = fork()) {
E 11
I 11
	switch (state->pid = fork()) {
E 11
	    case 0:
D 7
		writer(pipes);
E 7
I 7
D 11
		writer(control, pipes);
E 7
D 8
		exit(0);
E 8
I 8
		return(0);
E 11
I 11
D 20
		writer(state->control, state->pipes, state->buf);
E 20
I 20
		writer(state->control[0], state->pipes[1], state->buf, state);
E 20
		return;
E 11
E 8
		/*NOTREACHED*/
	    
	    case -1:
		perror("fork");
D 8
		exit(1);
E 8
I 8
D 11
		return(1);
E 11
I 11
		state->initerr = 3;
		return;
E 11
E 8
		/*NOTREACHED*/

	    default:
		break;
	}
D 6
	LOOP_FIRST(N, i, ENOUGH);
E 6
I 6
D 7
	LOOP_FIRST(N, i, MEDIUM);
E 6
	reader(pipes);
D 6
	LOOP_LAST(N, i, ENOUGH);
	fprintf(stderr, "Pipe bandwidth: ");
E 6
I 6
	LOOP_LAST(N, i, MEDIUM);
E 7
I 7
D 11
	BENCH(reader(control, pipes, XFER), MEDIUM);
E 7
	fprintf(stderr, "AF_UNIX sock stream bandwidth: ");
E 6
D 7
	mb(N * XFER);
E 7
I 7
	mb(get_n() * XFER);
E 7
	kill(pid, 15);
E 5
E 3
D 8
	exit(0);
E 8
I 8
	return(0);
E 11
I 11
}
D 16
void cleanup(void * cookie)
E 16
I 16
void 
cleanup(void * cookie)
E 16
{
	struct _state* state = (struct _state*)cookie;

	signal(SIGCHLD,SIG_IGN);
I 20
	close(state->control[1]);
	close(state->pipes[0]);
E 20
D 16
	kill(state->pid, 9);
E 16
I 16
	kill(state->pid, SIGKILL);
	state->pid = 0;
E 16
}

D 15
void reader(uint64 iterations, void * cookie)
E 15
I 15
D 16
void reader(iter_t iterations, void * cookie)
E 16
I 16
void 
reader(iter_t iterations, void * cookie)
E 16
E 15
{
	struct _state* state = (struct _state*)cookie;
D 20
	int	done, n;
	int	todo = state->bytes;
E 20
I 20
	size_t	done, n;
	size_t	todo = state->bytes;
E 20

	while (iterations-- > 0) {
		write(state->control[1], &todo, sizeof(todo));
		for (done = 0; done < todo; done += n) {
D 20
			if ((n = read(state->pipes[0], state->buf, XFERSIZE)) <= 0) {
E 20
I 20
			if ((n = read(state->pipes[0], state->buf, state->xfer)) <= 0) {
E 20
				/* error! */
D 20
				break;
E 20
I 20
				exit(1);
E 20
			}
		}
	}
E 11
E 8
}

D 4
doclient(int sock)
E 4
I 4
void
D 5
client(int sock)
E 5
I 5
D 7
writer(int pipes[2])
E 7
I 7
D 11
writer(int control[2], int pipes[2])
E 11
I 11
D 20
writer(int control[2], int pipes[2], char* buf)
E 20
I 20
writer(int controlfd, int writefd, char* buf, void* cookie)
E 20
E 11
E 7
E 5
E 4
{
D 3
	int     i, n;
E 3
I 3
D 4
	int     usecs, i, n;
E 4
I 4
D 5
	int     usecs, i;
E 4
E 3
	char	*buf = valloc(XFERSIZE);
E 5
I 5
D 7
	int	todo, done, n;
E 7
I 7
D 20
	int	todo, n;
E 20
I 20
	size_t	todo, n, done;
	struct _state* state = (struct _state*)cookie;
E 20
E 7
E 5

D 5
	start();
	for (i = 0; i < N; ++i) {
		if (writen(sock, buf, XFERSIZE) != XFERSIZE) {
			perror("write on socket");
			kill(getppid(), SIGTERM);
			exit(1);
		}
E 5
I 5
	for ( ;; ) {
D 7
		done = 0;
		todo = XFER;
		while ((done < todo) && ((n = write(pipes[1], buf, XFERSIZE)) > 0))
			done += n;
E 7
I 7
D 20
		read(control[0], &todo, sizeof(todo));
		while (todo > 0) {
E 20
I 20
		read(controlfd, &todo, sizeof(todo));
		for (done = 0; done < todo; done += n) {
E 20
I 10
#ifdef TOUCH
			touch(buf, XFERSIZE);
#endif
E 10
D 20
			n = write(pipes[1], buf, XFERSIZE);
			todo -= n;
E 20
I 20
			if ((n = write(writefd, buf, state->xfer)) < 0) {
				/* error! */
				exit(1);
			}
E 20
		}
E 7
E 5
	}
D 5
	if (read(sock, buf, 1) != 1) {
		perror("can't read on socket");
		kill(getppid(), SIGTERM);
		exit(1);
	}
D 3
	stop();
	sprintf(buf, "AF_UNIX sock stream bandwidth");
	bandwidth(N * XFERSIZE, 1);
E 3
I 3
	usecs = stop();
	if (usecs < 1000000) {
		N <<= 2;
		wait(0);
		return;
	}
	notdone = 0;
	fprintf(stderr, "AF_UNIX sock stream bandwidth: ");
	mb(N * XFERSIZE);
E 5
E 3
}

D 4
doserver(sock)
E 4
I 4
D 11
void
D 5
server(sock)
E 5
I 5
D 7
reader(int pipes[2])
E 7
I 7
reader(int control[2], int pipes[2], int bytes)
E 11
I 11
int
main(int argc, char *argv[])
E 11
E 7
E 5
E 4
{
D 5
	int	i;
	char	*buf = valloc(XFERSIZE);
	void	exit();

	signal(SIGTERM, exit);
	for (i = 0; i < N; ++i) {
		if (readn(sock, buf, XFERSIZE) != XFERSIZE) {
			perror("read on socket");
			kill(getppid(), SIGTERM);
			exit(1);
		}
E 5
I 5
D 11
	int	todo = XFER, done = 0, n;
E 11
I 11
	struct _state state;
	int parallel = 1;
I 14
	int warmup = 0;
	int repetitions = TRIES;
E 14
I 12
	int c;
I 13
D 14
	char* usage = "[-P <parallelism>]\n";
E 14
I 14
D 17
	char* usage = "[-P <parallelism>] [-W <warmup>] [-N <repetitions>]\n";
E 17
I 17
D 20
	char* usage = "[-P <parallelism>] [-W <warmup>] [-N <repetitions>] [size]\n";
E 20
I 20
	char* usage = "[-m <message size>] [-M <total bytes>] [-P <parallelism>] [-W <warmup>] [-N <repetitions>]\n";
E 20
E 17
E 14
E 13
E 12
E 11
I 7

D 11
	write(control[1], &bytes, sizeof(bytes));
E 7
	while ((done < todo) && ((n = read(pipes[0], buf, XFERSIZE)) > 0)) {
		done += n;
E 5
	}
E 11
I 11
D 20
	state.bytes = XFER;
E 20
I 20
	state.xfer = XFERSIZE;	/* per-packet size */
	state.bytes = XFER;	/* total bytes per call */
E 20

D 12
	if (argc == 2) parallel = atoi(argv[1]);
	if (parallel <= 0) parallel = 1;

E 12
I 12
D 14
	while (( c = getopt(argc,argv,"P:")) != EOF) {
E 14
I 14
D 20
	while (( c = getopt(argc,argv,"P:W:N:")) != EOF) {
E 20
I 20
	while (( c = getopt(argc,argv,"m:M:P:W:N:")) != EOF) {
E 20
E 14
D 13
	  if (c == 'P') parallel = atoi(optarg);
E 13
I 13
		switch(c) {
I 20
		case 'm':
			state.xfer = bytes(optarg);
			break;
		case 'M':
			state.bytes = bytes(optarg);
			break;
E 20
		case 'P':
			parallel = atoi(optarg);
			if (parallel <= 0) lmbench_usage(argc, argv, usage);
			break;
I 14
		case 'W':
			warmup = atoi(optarg);
			break;
		case 'N':
			repetitions = atoi(optarg);
			break;
E 14
		default:
			lmbench_usage(argc, argv);
			break;
		}
E 13
	}
D 13
	if (optind < argc || parallel <= 0) {
	  fprintf(stderr,"Usage : %s [-P <parallelism>]\n",argv[0]);
	  exit(-1);
E 13
I 13
D 17
	if (optind < argc) {
E 17
I 17
	if (optind == argc - 1) {
		state.bytes = bytes(argv[optind]);
D 18
	} else {
E 18
I 18
	} else if (optind < argc - 1) {
E 18
E 17
		lmbench_usage(argc, argv);
E 13
	}
I 16

	state.pid = 0;
	pGlobalState = &state;
	signal(SIGTERM, sigterm_handler);
I 20

	/* round up total byte count to a multiple of xfer */
	if (state.bytes % state.xfer) {
		state.bytes += state.bytes - state.bytes % state.xfer;
	}
E 20

E 16
E 12
D 14
	benchmp(initialize, reader, cleanup, MEDIUM, parallel, &state);
E 14
I 14
	benchmp(initialize, reader, cleanup, MEDIUM, parallel, 
		warmup, repetitions, &state);
E 14

D 19
	fprintf(stderr, "AF_UNIX sock stream bandwidth: ");
	mb(get_n() * parallel * XFER);
E 19
I 19
	if (gettime() > 0) {
		fprintf(stderr, "AF_UNIX sock stream bandwidth: ");
		mb(get_n() * parallel * XFER);
	}
E 19
	return(0);
E 11
D 5
	if (write(sock, buf, 1) != 1) {
		perror("can't read on socket");
		exit(1);
	}
	exit(0);
E 5
}
I 13

E 13
I 11


E 11
D 5

int
writen(int fd, char *buf, int n)
{
	int	done = 0, ret;

	do {
		ret = write(fd, buf + done, n - done);
		switch (ret) {
		    case -1:
		    case 0:
			perror("write");
			return (-1);
		    default:
			done += ret;
		}
	} while (done < n);
	return (done);
}

int
readn(int fd, char *buf, int n)
{
	int	done = 0, ret;

	do {
		ret = read(fd, buf + done, n - done);
		switch (ret) {
		    case -1:
		    case 0:
			perror("read");
			return (-1);
		    default:
			done += ret;
		}
	} while (done < n);
	return (done);
}
E 5
E 2
I 1
E 1
