H56936
s 00000/00004/00185
d D 1.20 02/09/29 22:12:26 staelin 22 20
i 21
c - Merge changes with 32-bit size changes
cC
cHfirewall.staelin.co.il
cK03070
cM21
e
s 00031/00026/00141
d D 1.18.1.1 02/09/29 21:53:51 staelin 21 19
c - switch from 'int' to 'size_t' for better portability to large memory 
c   machines
cC
cHfirewall.staelin.co.il
cK42070
cZ+03:00
e
s 00017/00004/00163
d D 1.19 02/09/20 09:34:58 staelin 20 19
c bw_pipe: fixup buffer allocation so OS must copy data
cC
cHhpli69.hpli.hpl.hp.com
cK62300
cZ+03:00
e
s 00004/00000/00163
d D 1.18 01/01/07 15:32:47 staelin 19 18
c - bw_pipe: kill uneeded pipe file descriptors so child process dies
c   when parent dies
cC
cK35100
e
s 00004/00002/00159
d D 1.17 00/10/31 10:00:27 staelin 18 17
c - Only print any output if benchmark produces a valid result
c   (needed for mb() and micromb()-style outputs where prefix is
c   printed by main() and only the result is printed by the output
c   routine, and only then if the result is valid)
cC
cK26126
e
s 00031/00014/00130
d D 1.16 00/10/16 17:15:04 staelin 17 16
c - Add [-m <message size>] option to bw_pipe
cC
cK24464
cZ+02:00
e
s 00002/00002/00142
d D 1.15 00/07/30 11:46:03 staelin 16 15
c - Change type of "iterations" from uint64 to iter_t, which is a u_long
cC
cK29645
e
s 00013/00004/00131
d D 1.14 00/07/04 14:55:49 staelin 15 14
c - Update to incorporate new "-W <warmup>" and "-N <repetitions>" flags
cC
cK29459
cZ+03:00
e
s 00027/00026/00108
d D 1.13 00/03/01 17:23:37 staelin 14 13
c - Rename argc, argv to ac, av to match rest of lmbench
c - Re-indent main()
cC
cK10692
e
s 00022/00014/00112
d D 1.12 00/03/01 14:34:23 staelin 13 12
c - Tweak getopt harness
c - Adjust indentation
cC
cHhpli8.hpli.hpl.hp.com
cK15057
cZ+02:00
e
s 00071/00031/00055
d D 1.11 00/02/28 17:01:12 brucec 12 11
c Make changes to use new MP function in place of BENCH macro.
c Add getopt() handling of optional -P <parallelism> argument.
cC
cHrx7
cK03446
cZ-05:00
e
s 00004/00006/00082
d D 1.10 97/06/25 10:25:01 lm 11 10
c ifdef TOUCH
cC
cK55727
e
s 00005/00000/00083
d D 1.9 97/06/23 23:27:09 lm 10 9
c touch the data for dm.
cK03370
e
s 00001/00001/00082
d D 1.8 97/06/16 19:05:50 lm 9 8
c lint
cK53028
e
s 00007/00007/00076
d D 1.7 97/06/15 22:38:58 lm 8 7
c lint
cK52471
e
s 00020/00017/00063
d D 1.6 97/06/12 21:30:06 lm 7 6
c new bench.h macros.
cK48507
cZ-07:00
e
s 00041/00043/00039
d D 1.5 96/11/11 03:36:51 lm 6 5
c Auto adjusting changes.
cK40425
e
s 00002/00001/00080
d D 1.4 96/11/08 19:57:56 lm 5 4
c gcc -Wall cleanup.
cK39174
cZ-08:00
e
s 00027/00023/00054
d D 1.3 96/05/30 00:31:40 lm 4 3
c Make them auto time themselves.
cK35844
cZ-07:00
e
s 00004/00005/00073
d D 1.2 96/01/24 17:09:19 lm 3 2
c Make everything use XFERSIZE
cK31617
e
s 00078/00000/00000
d D 1.1 94/11/18 00:49:48 lm 2 1
c Initial revision
cK32537
e
s 00000/00000/00000
d D 1.0 94/11/18 00:49:47 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK54645
cPsrc/bw_pipe.c
cRfa12331757b8149c
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
 * bw_pipe.c - pipe bandwidth benchmark.
 *
D 12
 * Usage: bw_pipe
E 12
I 12
D 15
 * Usage: bw_pipe [-P <parallelism>]
E 15
I 15
D 17
 * Usage: bw_pipe [-P <parallelism>] [-W <warmup>] [-N <repetitions>]
E 17
I 17
D 21
 * Usage: bw_pipe [-m <message size>] [-M <total bytes>] [-P <parallelism>] [-W <warmup>] [-N <repetitions>]
E 21
I 21
 * Usage: bw_pipe [-m <message size>] [-M <total bytes>] \
 *		[-P <parallelism>] [-W <warmup>] [-N <repetitions>]
E 21
E 17
E 15
E 12
 *
D 21
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
E 21
I 21
 * Copyright (c) 1994 Larry McVoy.  
 * Copyright (c) 2002 Carl Staelin.
 * Distributed under the FSF GPL with additional restriction that results 
 * may published only if:
E 21
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
char	*id = "$Id$\n";

D 6
#include	"timing.c"
I 5
#include	<sys/types.h>
#include	<sys/wait.h>
E 6
I 6
D 7
#include "timing.h"
E 7
#include "bench.h"
D 7
#include <sys/types.h>
#include <sys/wait.h>
E 7
E 6
E 5

D 3
#define	BUFSIZE	(64*1024)
E 3
D 4
#define	XFER	(1024*1024*50)

E 4
D 8
extern	void	exit();		/* for lint on SunOS 4.x */
void		writer(), reader();
E 8
I 8
D 12
void	reader(int control[2], int pipes[2], int bytes);
void	writer(int control[2], int pipes[2]);
E 12
I 12
D 16
void	reader(uint64 iterations, void * cookie);
E 16
I 16
D 17
void	reader(iter_t iterations, void * cookie);
E 16
void	writer(int control[2], int pipes[2], char* buf);
E 17
I 17
void	reader(iter_t iterations, void* cookie);
D 21
void	writer(int control[2], int pipes[2], char* buf, void* cookie);
E 21
I 21
void	writer(int controlfd, int writefd, char* buf, void* cookie);
E 21
E 17
E 12
E 8

I 4
D 6
int	XFER	= 10*1024*1024;
E 6
I 6
D 7
int	XFER	= 100*1024*1024;
E 7
I 7
int	XFER	= 10*1024*1024;
E 7
D 12
int	pid;
char	*buf;
E 12

E 6
E 4
D 12
int
main()
{
E 12
I 12
struct _state {
	int	pid;
I 17
D 20
D 21
	int	xfer;	/* bytes to read/write per "packet" */
E 17
	int	bytes;	/* bytes to read/write in one iteration */
E 21
I 21
	size_t	xfer;	/* bytes to read/write per "packet" */
	size_t	bytes;	/* bytes to read/write in one iteration */
E 21
E 20
I 20
D 22
	size_t	xfer;	/* bytes to read/write per "packet" */
	size_t	bytes;	/* bytes to read/write in one iteration */
E 22
E 20
	char	*buf;	/* buffer memory space */
E 12
D 6
	int	pipes[2];
I 4
	int	usecs;
E 6
I 6
D 7
	int	i, N, pipes[2];
E 7
I 7
	int	pipes[2];
	int	control[2];
I 12
	int	initerr;
};

void initialize(void *cookie)
{
	struct _state* state = (struct _state*)cookie;
E 12
E 7
E 6
D 5
	char	c;
E 5
E 4

I 6
D 12
	buf = valloc(XFERSIZE);
D 9
	bzero(buf, XFERSIZE);
E 9
I 9
D 11
	bzero((void*)buf, XFERSIZE);
E 11
I 11
	touch(buf, XFERSIZE);
E 11
E 9
E 6
D 4
	write(2, id, strlen(id));
E 4
	if (pipe(pipes) == -1) {
E 12
I 12
D 17
	state->buf = valloc(XFERSIZE);
	touch(state->buf, XFERSIZE);
E 17
I 17
D 20
D 21
	state->buf = valloc(state->xfer);
	touch(state->buf, state->xfer);
E 21
E 20
E 17
	state->initerr = 0;
	if (pipe(state->pipes) == -1) {
E 12
		perror("pipe");
D 8
		exit(1);
E 8
I 8
D 12
		return(1);
E 12
I 12
		state->initerr = 1;
		return;
E 12
E 8
	}
I 7
D 12
	if (pipe(control) == -1) {
E 12
I 12
	if (pipe(state->control) == -1) {
E 12
		perror("pipe");
D 8
		exit(1);
E 8
I 8
D 12
		return(1);
E 12
I 12
		state->initerr = 2;
		return;
E 12
E 8
	}
E 7
D 4
	switch (fork()) {
	    case 0:
		reader(pipes[0]);
		exit(0);
		/*NOTREACHED*/
E 4
I 4
D 6
	do {
		switch (fork()) {
	    	case 0:
		    writer(pipes[1]);
		    exit(0);
		    /*NOTREACHED*/
E 4
	    	
D 4
	    case -1:
		perror("fork");
		exit(1);
		/*NOTREACHED*/
E 4
I 4
		    case -1:
			perror("fork");
			exit(1);
			/*NOTREACHED*/
E 6
I 6
D 12
	switch (pid = fork()) {
E 12
I 12
	switch (state->pid = fork()) {
E 12
	    case 0:
I 21
D 22
		state->buf = valloc(state->xfer);
		touch(state->buf, state->xfer);
E 22
E 21
I 19
		close(state->control[1]);
		close(state->pipes[0]);
I 20
		state->buf = valloc(state->xfer);
		if (state->buf == NULL) {
			perror("child: no memory");
			state->initerr = 4;
			return;
		}
		touch(state->buf, state->xfer);
E 20
E 19
D 7
		writer(pipes);
E 7
I 7
D 12
		writer(control, pipes);
E 7
D 8
		exit(0);
E 8
I 8
		return(0);
E 12
I 12
D 17
		writer(state->control, state->pipes, state->buf);
E 17
I 17
D 21
		writer(state->control, state->pipes, state->buf, state);
E 21
I 21
		writer(state->control[0], state->pipes[1], state->buf, state);
E 21
E 17
		return;
E 12
E 8
		/*NOTREACHED*/
	    
	    case -1:
		perror("fork");
D 8
		exit(1);
E 8
I 8
D 12
		return(1);
E 12
I 12
		state->initerr = 3;
		return;
E 12
E 8
		/*NOTREACHED*/
E 6
E 4

D 4
	    default:
	    	writer(pipes[1]);
		wait(0);
		exit(0);
		/*NOTREACHED*/
	}
E 4
I 4
D 6
		    default:
			sleep(1);
			start();
			reader(pipes[0]);
			usecs = stop();
			XFER <<= 2;
			wait(0);
		}
	} while (usecs < 1000000);
E 6
I 6
	    default:
I 21
		state->buf = valloc(state->xfer + 128) + 128;
		touch(state->buf, state->xfer);
E 21
I 19
		close(state->control[0]);
		close(state->pipes[1]);
E 19
		break;
	}
I 20
	state->buf = valloc(state->xfer + getpagesize());
	if (state->buf == NULL) {
		perror("parent: no memory");
		state->initerr = 4;
		return;
	}
	touch(state->buf, state->xfer + getpagesize());
	state->buf += 128; /* destroy page alignment */
E 20
D 7
	LOOP_FIRST(N, i, ENOUGH);
	reader(pipes);
	LOOP_LAST(N, i, ENOUGH);
E 7
I 7
D 12
	BENCH(reader(control, pipes, XFER), MEDIUM);
E 7
E 6
	fprintf(stderr, "Pipe bandwidth: ");
D 6
	mb(XFER >> 2);
E 6
I 6
D 7
	mb(N * XFER);
E 7
I 7
	mb(get_n() * XFER);
E 7
	kill(pid, 15);
E 6
D 8
	exit(0);
E 8
I 8
	return(0);
E 12
I 12
}
I 14

E 14
void cleanup(void * cookie)
{
	struct _state* state = (struct _state*)cookie;

	signal(SIGCHLD,SIG_IGN);
I 21
	close(state->control[1]);
	close(state->pipes[0]);
E 21
	kill(state->pid, 9);
}

D 16
void reader(uint64 iterations, void * cookie)
E 16
I 16
void reader(iter_t iterations, void * cookie)
E 16
{
	struct _state* state = (struct _state*)cookie;
D 21
	int	done, n;
	int	todo = state->bytes;
E 21
I 21
	size_t	done, n;
	size_t	todo = state->bytes;
E 21

	while (iterations-- > 0) {
		write(state->control[1], &todo, sizeof(todo));
		for (done = 0; done < todo; done += n) {
D 17
			if ((n = read(state->pipes[0], state->buf, XFERSIZE)) <= 0) {
E 17
I 17
			if ((n = read(state->pipes[0], state->buf, state->xfer)) <= 0) {
E 17
				/* error! */
D 21
				break;
E 21
I 21
				exit(1);
E 21
			}
		}
	}
E 12
E 8
E 4
}

void
D 6
writer(fd)
	int	fd;
E 6
I 6
D 7
writer(int pipes[2])
E 7
I 7
D 12
writer(int control[2], int pipes[2])
E 12
I 12
D 17
writer(int control[2], int pipes[2], char* buf)
E 17
I 17
D 21
writer(int control[2], int pipes[2], char* buf, void* cookie)
E 21
I 21
writer(int controlfd, int writefd, char* buf, void* cookie)
E 21
E 17
E 12
E 7
E 6
{
D 6
	int	todo = XFER;
	int	n, done = 0;
D 3
	char	buf[BUFSIZE];
E 3
I 3
	char	*buf = valloc(XFERSIZE);
E 6
I 6
D 7
	int	todo, done, n;
E 7
I 7
D 21
	int	todo, n;
E 21
I 21
	size_t	done, todo, n;
E 21
I 17
	struct _state* state = (struct _state*)cookie;
E 17
E 7
E 6
E 3

D 3
	while ((done < todo) && ((n = write(fd, buf, sizeof(buf))) > 0))
E 3
I 3
D 6
	while ((done < todo) && ((n = write(fd, buf, XFERSIZE)) > 0))
E 3
		done += n;
I 4
	free(buf);
E 6
I 6
	for ( ;; ) {
D 7
		done = 0;
		todo = XFER;
		while ((done < todo) && ((n = write(pipes[1], buf, XFERSIZE)) > 0))
			done += n;
E 7
I 7
D 21
		read(control[0], &todo, sizeof(todo));
		while (todo > 0) {
E 21
I 21
		read(controlfd, &todo, sizeof(todo));
		for (done = 0; done < todo; done += n) {
E 21
I 11
D 12
#ifdef	TOUCH
E 12
I 12
#ifdef TOUCH
E 12
D 17
			touch(buf, XFERSIZE);
E 17
I 17
			touch(buf, state->xfer);
E 17
#endif
E 11
D 17
			n = write(pipes[1], buf, XFERSIZE);
E 17
I 17
D 21
			n = write(pipes[1], buf, state->xfer);
E 17
			todo -= n;
E 21
I 21
			if ((n = write(writefd, buf, state->xfer)) < 0) {
				/* error! */
				exit(1);
			}
E 21
I 10
D 11
			buf[0] = buf[4<<10] = buf[8<<10] = buf[12<<10] =
			buf[16<<10] = buf[20<<10] = buf[24<<10] = buf[28<<10] =
			buf[32<<10] = buf[36<<10] = buf[40<<10] = buf[44<<10] =
			buf[48<<10] = buf[52<<10] = buf[56<<10] = buf[60<<10] =
			buf[63<<10] = 1;
E 11
E 10
		}
E 7
	}
E 6
E 4
}

D 12
void
D 6
reader(fd)
	int	fd;
E 6
I 6
D 7
reader(int pipes[2])
E 7
I 7
reader(int control[2], int pipes[2], int bytes)
E 12
I 12
int
D 14
main(int argc, char *argv[])
E 14
I 14
main(int ac, char *av[])
E 14
E 12
E 7
E 6
{
D 6
	int	todo = XFER;
	int	n, done = 0;
D 3
	char	buf[BUFSIZE];
E 3
I 3
	char	*buf = valloc(XFERSIZE);
E 3

D 4
	sleep(1);
	start();
E 4
D 3
	while ((done < todo) && ((n = read(fd, buf, sizeof(buf))) > 0))
E 3
I 3
	while ((done < todo) && ((n = read(fd, buf, XFERSIZE)) > 0))
E 6
I 6
D 12
	int	todo = XFER, done = 0, n;
E 12
I 12
D 13
	struct _state state;
	int parallel = 1;
	int c;
E 13
I 13
D 14
    struct _state state;
    int parallel = 1;
    int c;
    char* usage = "[-P <parallelism>]\n";
E 13
E 12
I 7

D 12
	write(control[1], &bytes, sizeof(bytes));
E 7
	while ((done < todo) && ((n = read(pipes[0], buf, XFERSIZE)) > 0)) {
E 6
E 3
		done += n;
E 12
I 12
D 13
	state.bytes = XFER;
E 13
I 13
    state.bytes = XFER;
E 13

D 13
	while (( c = getopt(argc,argv,"P:")) != EOF) {
	  if (c == 'P') parallel = atoi(optarg);
E 13
I 13
    while (( c = getopt(argc,argv,"P:")) != EOF) {
	switch(c) {
	case 'P':
	    parallel = atoi(optarg);
	    if (parallel <= 0) lmbench_usage(argc, argv, usage);
	    break;
	default:
	    lmbench_usage(argc, argv, usage);
	    break;
E 14
I 14
	struct _state state;
	int parallel = 1;
I 15
	int warmup = 0;
	int repetitions = TRIES;
E 15
	int c;
D 15
	char* usage = "[-P <parallelism>]\n";
E 15
I 15
D 17
	char* usage = "[-P <parallelism>] [-W <warmup>] [-N <repetitions>]\n";
E 17
I 17
	char* usage = "[-m <message size>] [-M <total bytes>] [-P <parallelism>] [-W <warmup>] [-N <repetitions>]\n";
E 17
E 15

D 17
	state.bytes = XFER;
E 17
I 17
	state.xfer = XFERSIZE;	/* per-packet size */
	state.bytes = XFER;	/* total bytes per call */
E 17

D 15
	while (( c = getopt(ac, av, "P:")) != EOF) {
E 15
I 15
D 17
	while (( c = getopt(ac, av, "P:W:N:")) != EOF) {
E 17
I 17
	while (( c = getopt(ac, av, "m:M:P:W:N:")) != EOF) {
E 17
E 15
		switch(c) {
I 17
		case 'm':
			state.xfer = bytes(optarg);
D 21
			/* round up total byte count to a multiple of xfer */
			if (state.bytes % state.xfer) {
				state.bytes += state.bytes - state.bytes % state.xfer;
			}
E 21
			break;
		case 'M':
			state.bytes = bytes(optarg);
D 21
			/* round up total byte count to a multiple of xfer */
			if (state.bytes % state.xfer) {
				state.bytes += state.bytes - state.bytes % state.xfer;
			}
E 21
			break;
E 17
		case 'P':
			parallel = atoi(optarg);
			if (parallel <= 0) lmbench_usage(ac, av, usage);
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
		}
E 14
E 13
	}
D 13
	if (optind < argc || parallel <= 0) {
	  fprintf(stderr,"Usage : %s [-P <parallelism>]\n",argv[0]);
	  exit(-1);
E 12
D 4
	stop();
	fprintf(stderr, "Pipe bandwidth: ");
	mb(todo);
E 4
I 4
D 6
	free(buf);
E 6
I 6
	}
I 12
	benchmp(initialize, reader, cleanup, MEDIUM, parallel, &state);
E 13
I 13
D 14
    }
    if (optind < argc) {
	lmbench_usage(argc, argv, usage);
    }
    benchmp(initialize, reader, cleanup, MEDIUM, parallel, &state);
E 13

D 13
	fprintf(stderr, "Pipe bandwidth: ");
	mb(get_n() * parallel * XFER);
	return(0);
E 13
I 13
    fprintf(stderr, "Pipe bandwidth: ");
    mb(get_n() * parallel * XFER);
    return(0);
E 14
I 14
	if (optind < ac) {
		lmbench_usage(ac, av, usage);
I 21
	}
	/* round up total byte count to a multiple of xfer */
	if (state.bytes % state.xfer) {
		state.bytes += state.bytes - state.bytes % state.xfer;
E 21
	}
D 15
	benchmp(initialize, reader, cleanup, MEDIUM, parallel, &state);
E 15
I 15
	benchmp(initialize, reader, cleanup, MEDIUM, parallel, 
		warmup, repetitions, &state);
E 15

D 18
	fprintf(stderr, "Pipe bandwidth: ");
D 17
	mb(get_n() * parallel * XFER);
E 17
I 17
	mb(get_n() * parallel * state.bytes);
E 18
I 18
	if (gettime() > 0) {
		fprintf(stderr, "Pipe bandwidth: ");
		mb(get_n() * parallel * state.bytes);
	}
E 18
E 17
	return(0);
E 14
E 13
E 12
E 6
E 4
}
E 2
I 1
E 1
