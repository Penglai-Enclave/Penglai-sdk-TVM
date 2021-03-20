H53326
s 00018/00016/00200
d D 1.19 02/09/29 21:54:50 staelin 20 19
c lat_select.c: avoid creating tempfiles for TCP pathway, and avoid creating
c 	TCP socket for file pathway
cC
cHfirewall.staelin.co.il
cK18357
cZ+03:00
e
s 00002/00002/00214
d D 1.18 00/10/31 09:53:16 staelin 19 18
c - Add protocol number for lat_select (TCP_SELECT)
cC
cK14114
e
s 00011/00008/00205
d D 1.17 00/10/25 12:38:37 staelin 18 17
c - Bug-fix lat_select it reports the right number of descriptors
cC
cK14178
e
s 00106/00012/00107
d D 1.16 00/10/19 17:04:11 staelin 17 16
c - Fix bug in lat_select that was reported by Lev Iserovich.  Lat_select
c   does a select() on dup()'ed copies of stdin.  Depending on how you have
c   logged into your machine, stdin might be a tty or a socket (but never a
c   file).  I have modified lat_select to take a new argument specifying
c   whether you want to select on a network TCP socket or a file.
cC
cK11878
cZ+02:00
e
s 00007/00003/00112
d D 1.15 00/09/25 13:21:51 staelin 16 15
c - For OpenBSD, add exit(0) to end of lat_select
cC
cK47663
e
s 00001/00002/00114
d D 1.14 00/09/24 12:54:07 staelin 15 14
c - Remove unnecessary status statement "num bumped"
cC
cK47080
e
s 00002/00002/00114
d D 1.13 00/07/30 11:46:12 staelin 14 13
c - Change type of "iterations" from uint64 to iter_t, which is a u_long
cC
cK48659
e
s 00013/00004/00103
d D 1.12 00/07/04 14:55:57 staelin 13 12
c - Update to incorporate new "-W <warmup>" and "-N <repetitions>" flags
cC
cK48441
e
s 00017/00009/00090
d D 1.11 00/05/31 16:16:18 staelin 12 11
c Fix lat_select so it keeps better track of the file descriptors it opens, and so it only
c close()'s file descriptors which it opened.  Before it was closing some of the lmbench
c timing harness file descriptors, which confused the timing harness...
cC
cHhpli8.hpli.hpl.hp.com
cK29348
cZ+03:00
e
s 00072/00019/00027
d D 1.10 00/03/14 18:03:54 brucec 11 10
c First pass at making this test MP "-P <parallelism>" ready (not working yet)
cC
cHrx7
cK24644
cZ-05:00
e
s 00002/00001/00044
d D 1.9 98/07/31 12:47:56 lm 10 9
c There was a hang if I didn't put a timeout in there when
c running in MP mode on IRIX 6.5 (Olson's machine).  XXX
cC
cK01851
e
s 00002/00001/00043
d D 1.8 98/06/29 22:37:39 lm 9 8
c Redo to compile clean with -Wall.
cK64699
e
s 00008/00006/00036
d D 1.7 97/10/19 23:47:45 lm 8 7
c *** empty log message ***
cK63471
e
s 00000/00001/00042
d D 1.6 97/06/15 22:38:58 lm 7 6
c lint
cK60745
e
s 00001/00000/00042
d D 1.5 97/06/14 12:20:51 lm 6 5
c morefds().
cK61345
e
s 00008/00007/00034
d D 1.4 97/06/13 20:39:50 lm 5 4
c lint
cK60434
e
s 00012/00015/00029
d D 1.3 97/06/12 21:30:06 lm 4 3
c new bench.h macros.
cK59990
cZ-07:00
e
s 00004/00002/00040
d D 1.2 96/11/21 17:48:04 lm 3 2
c timing.c interfaces.
cK03852
e
s 00042/00000/00000
d D 1.1 96/11/13 16:16:07 lm 2 1
c Initial revision
cK03500
e
s 00000/00000/00000
d D 1.0 96/11/13 16:16:06 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK65044
cPsrc/lat_select.c
cR97c296f6daba401d
cV4
cX0x21
cZ-08:00
e
u
U
f e 0
f x 0x21
t
T
I 2
/*
 * lat_select.c - time select system call
 *
D 11
 * usage: lat_select [n]
E 11
I 11
D 13
 * usage: lat_select [-P <parallelism>] [n]
E 13
I 13
 * usage: lat_select [-P <parallelism>] [-W <warmup>] [-N <repetitions>] [n]
E 13
E 11
 *
 * Copyright (c) 1996 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 */
char	*id = "$Id$\n";

D 4
#include "timing.h"
E 4
#include "bench.h"
D 4
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
E 4

I 5
D 11
void
doit(int n, fd_set *set)
E 11
I 11
void initialize(void *cookie);
void cleanup(void *cookie);
D 14
void doit(uint64 iterations,void *cookie);
E 14
I 14
void doit(iter_t iterations, void *cookie);
E 14
void writer(int w, int r);
I 17
void server(void* cookie);

typedef int (*open_f)(void* cookie);
int  open_file(void* cookie);
int  open_socket(void* cookie);
E 17

typedef struct _state {
I 17
	char	fname[L_tmpnam];
	open_f	fid_f;
	pid_t	pid;
	int	sock;
	int	fid;
E 17
	int	num;
I 12
	int	max;
E 12
	fd_set  set;
} state_t;

int main(int ac, char **av)
E 11
{
D 8
	fd_set	save = *set;
	select(n, 0, set, 0, 0);
	*set = save;
E 8
I 8
D 11
	fd_set	nosave = *set;
E 11
I 11
	state_t state;
	int parallel = 1;
I 13
	int warmup = 0;
	int repetitions = TRIES;
E 13
	int c;
D 13
	char* usage = "[-P <parallelism>]\n";
E 13
I 13
D 17
	char* usage = "[-P <parallelism>] [-W <warmup>] [-N <repetitions>] [n]\n";
E 17
I 17
	char* usage = "[-n <#descriptors>] [-P <parallelism>] [-W <warmup>] [-N <repetitions>] file|tcp\n";
E 17
E 13
	char	buf[256];

	morefds();  /* bump fd_cur to fd_max */
D 13
	while (( c = getopt(ac, av, "P:")) != EOF) {
E 13
I 13
D 17
	while (( c = getopt(ac, av, "P:W:N:")) != EOF) {
E 17
I 17
	state.num = 200;
	while (( c = getopt(ac, av, "P:W:N:n:")) != EOF) {
E 17
E 13
		switch(c) {
		case 'P':
			parallel = atoi(optarg);
			if (parallel <= 0) lmbench_usage(ac, av, usage);
			break;
I 13
		case 'W':
			warmup = atoi(optarg);
			break;
		case 'N':
			repetitions = atoi(optarg);
			break;
I 17
		case 'n':
D 18
			state.num = bytes(av[optind]);
E 18
I 18
			state.num = bytes(optarg);
E 18
			break;
E 17
E 13
		default:
			lmbench_usage(ac, av, usage);
			break;
		}
	}
D 17
	state.num = 200;
	if (optind + 1 == ac) {
D 15
		state.num = atoi(av[optind]);
		puts("num bumped");
E 15
I 15
		state.num = bytes(av[optind]);
E 15
	} else if (optind < ac) {
E 17
I 17

	if (optind + 1 != ac) {
		lmbench_usage(ac, av, usage);
	}

	if (streq("tcp", av[optind])) {
		state.fid_f = open_socket;
		server(&state);
		benchmp(initialize, doit, cleanup, 0, parallel, 
			warmup, repetitions, &state);
		sprintf(buf, "Select on %d tcp fd's", state.num);
I 20
		kill(state.pid, SIGKILL);
		waitpid(state.pid, NULL, 0);
E 20
		micro(buf, get_n());
	} else if (streq("file", av[optind])) {
		state.fid_f = open_file;
		server(&state);
		benchmp(initialize, doit, cleanup, 0, parallel, 
			warmup, repetitions, &state);
I 20
		unlink(state.fname);
E 20
		sprintf(buf, "Select on %d fd's", state.num);
		micro(buf, get_n());
	} else {
E 17
		lmbench_usage(ac, av, usage);
	}

D 13
	benchmp(initialize, doit, cleanup, 0, parallel, &state);
E 13
I 13
D 17
	benchmp(initialize, doit, cleanup, 0, parallel, 
		warmup, repetitions, &state);
E 13
	sprintf(buf, "Select on %d fd's", state.num);
	micro(buf, get_n());
E 17
I 17
D 20
	close(state.fid);
	unlink(state.fname);
	if (state.pid > 0)
		kill(state.pid, SIGKILL);

E 20
E 17
I 16
	exit(0);
E 16
}

I 17
void
server(void* cookie)
{
	int pid;
	state_t* state = (state_t*)cookie;

	pid = getpid();
I 20
	state->pid = 0;

	if (state->fid_f == open_file) {
		/* Create a temporary file for clients to open */
		sprintf(state->fname, "lat_selectXXXXXX");
		state->fid = mkstemp(state->fname);
		if (state->fid <= 0) {
			char buf[L_tmpnam+128];
			sprintf(buf, "lat_select: Could not create temp file %s", state->fname);
			perror(buf);
			exit(1);
		}
		close(state->fid);
		return;
	}
E 20

	/* Create a socket for clients to connect to */
D 19
	state->sock = tcp_server(TCP_CONNECT, SOCKOPT_NONE);
E 19
I 19
	state->sock = tcp_server(TCP_SELECT, SOCKOPT_REUSE);
E 19
	if (state->sock <= 0) {
		perror("lat_select: Could not open tcp server socket");
		exit(1);
	}

D 20
	/* Create a temporary file for clients to open */
	tmpnam(state->fname);
	state->fid = open(state->fname, O_RDWR|O_APPEND|O_CREAT, 0666);
	if (state->fid <= 0) {
		char buf[L_tmpnam+128];
		sprintf(buf, "lat_select: Could not create temp file %s", state->fname);
		perror(buf);
		exit(1);
	}

E 20
	/* Start a server process to accept client connections */
	switch(state->pid = fork()) {
	case 0:
		/* child server process */
D 20
		close(state->fid);
E 20
		while (pid == getppid()) {
			int newsock = tcp_accept(state->sock, SOCKOPT_NONE);
			read(newsock, &state->fid, 1);
			close(newsock);
		}
		exit(0);
	case -1:
		/* error */
		perror("lat_select::server(): fork() failed");
		exit(1);
	default:
		break;
	}
}

int
open_socket(void* cookie)
{
D 19
	return tcp_connect("localhost", TCP_CONNECT, SOCKOPT_NONE);
E 19
I 19
	return tcp_connect("localhost", TCP_SELECT, SOCKOPT_NONE);
E 19
}

int open_file(void* cookie)
{
	state_t* state = (state_t*)cookie;

	return open(state->fname, O_RDONLY);
}
E 17

D 14
void doit(uint64 iterations, void * cookie)
E 14
I 14
D 16
void doit(iter_t iterations, void * cookie)
E 16
I 16
void
doit(iter_t iterations, void * cookie)
E 16
E 14
{
	state_t * 	state = (state_t *)cookie;
D 12
	register int 	n = state->num;
	fd_set	nosave = state->set;
E 11
D 10
	select(n, 0, &nosave, 0, 0);
E 10
I 10
	static	struct timeval tv;
E 12
I 12
	fd_set		nosave;
	static struct timeval tv;
E 12
D 11
	select(n, 0, &nosave, 0, &tv);
E 11
I 11
	static count = 0;
	
I 12
	tv.tv_sec = 0;
	tv.tv_usec = 0;
E 12

D 12
	if (!(count++ % 100))
		printf("doit with iterations %d\n", (int) iterations);
E 12
	while (iterations-- > 0) {
D 12
		select(n, 0, &nosave, 0, &tv);
E 12
I 12
		nosave = state->set;
		select(state->num, 0, &nosave, 0, &tv);
E 12
	}
E 11
E 10
E 8
}

E 5
D 11
int
main(int ac, char **av)
E 11
I 11
D 16
void initialize(void *cookie)
E 16
I 16
void
initialize(void *cookie)
E 16
E 11
{
I 11
	char	c;
	state_t * state = (state_t *)cookie;

E 11
D 7
	char	c;
E 7
D 4
	int	N = 200, i, fd;
	fd_set	save, set;
E 4
I 4
D 8
	int	N = 200, fd;
E 8
I 8
D 9
	int	i, last, N = 200, fd;
E 9
I 9
D 18
	int	i, last = 0 /* lint */;
E 18
I 18
	int	n, last = 0 /* lint */;
E 18
D 11
	int	N = 200, fd;
E 9
E 8
	fd_set	set;
E 4
I 3
	char	buf[256];
E 11
I 11
D 17
	int	N = state->num, fd;
E 17
I 17
	int	N = state->num, fid, fd;
E 17
E 11
E 3

I 17
	fid = (*state->fid_f)(cookie);
	if (fid <= 0) {
		perror("Could not open device");
		exit(1);
	}
E 17
I 12
	state->max = 0;
E 12
I 6
D 11
	morefds();
E 6
	if (ac > 1) N = atoi(av[1]);
	FD_ZERO(&set);
E 11
I 11
	FD_ZERO(&(state->set));
E 11
I 8
D 12
	for (i = 3; i < 50; ++i) close(i);
E 12
E 8
D 18
	for (fd = 0; fd < N; fd++) {
D 4
		i = open("/dev/tty", 1);
E 4
I 4
D 8
		int i = open("/dev/tty", 1);
E 8
I 8
D 17
		i = dup(0);
E 17
I 17
		i = dup(fid);
E 17
E 8
E 4
I 3
		if (i == -1) break;
I 8
D 12
		last = i;
E 12
I 12
		if (i > state->max)
			state->max = i;
E 12
E 8
E 3
D 11
		FD_SET(i, &set);
E 11
I 11
		FD_SET(i, &(state->set));
E 18
I 18
	for (n = 0; n < N; n++) {
		fd = dup(fid);
		if (fd == -1) break;
		if (fd > state->max)
			state->max = fd;
		FD_SET(fd, &(state->set));
E 18
E 11
	}
I 18
	state->max++;
E 18
I 17
	close(fid);
I 18
	if (n != N)
		exit(1);
E 18
E 17
D 4
	LOOP_FIRST(N, i, ENOUGH);
	save = set;
	select(fd, 0, &set, 0, 0);
	set = save;
	LOOP_LAST(N, i, ENOUGH);
E 4
I 4
D 8
	BENCH(doit(fd, &set), 0);
E 8
I 8
D 11
	last++;
	BENCH(doit(last, &set), 0);
E 8
E 4
D 3
	fprintf(stderr,
	    "Select on %d fd's: %.3f microseconds\n", fd, (double)i/N);
E 3
I 3
	sprintf(buf, "Select on %d fd's", fd);
D 4
	micro(buf, N);
E 4
I 4
	micro(buf, get_n());
E 4
E 3
	return(0);
E 11
}
I 11

D 16
void cleanup(void *cookie)
E 16
I 16
void
cleanup(void *cookie)
E 16
{
D 12
	char	c;
E 12
I 12
	int	i;
E 12
	state_t * state = (state_t *)cookie;
I 12

	for (i = 0; i <= state->max; ++i) {
		if (FD_ISSET(i, &(state->set)))
			close(i);
	}
	FD_ZERO(&(state->set));
E 12
}

	     
E 11
I 4
D 5

doit(int n, fd_set *set)
{
	fd_set	save = *set;
	select(n, 0, set, 0, 0);
	*set = save;
}
E 5
E 4
E 2
I 1
E 1
