h28782
s 00009/00008/00274
d D 1.22 00/09/26 16:00:20 staelin 23 22
c - Fix bug in command-line parsing for "-S <serverhost>" option
c - Fix bug in lat_rpc TIMEOUT which was too small and was causing lat_rpc to fail
c   too often
cC
cK24181
e
s 00000/00002/00282
d D 1.21 00/09/24 12:52:41 staelin 22 21
c - Remove unnecessary function prototypes for pmap_*() functions
cC
cK20829
e
s 00002/00002/00282
d D 1.20 00/07/30 11:46:12 staelin 21 20
c - Change type of "iterations" from uint64 to iter_t, which is a u_long
cC
cK33309
e
s 00001/00001/00283
d D 1.19 00/07/27 14:36:59 staelin 20 19
c - Change return type of main() from void to int (fix from Robert G. Brown)
cC
cK33123
e
s 00004/00004/00280
d D 1.18 00/07/25 13:48:37 staelin 19 18
c - fix reporting bug that prevented the server name from being reported properly
c - fix parameter cast for svc_getargs and svc_freeargs
cC
cK33226
e
s 00049/00021/00235
d D 1.17 00/07/04 14:55:56 staelin 18 17
c - Update to incorporate new "-W <warmup>" and "-N <repetitions>" flags
cC
cK31066
e
s 00083/00046/00173
d D 1.16 00/06/21 19:28:42 staelin 17 16
c - Fixed bug when tcp or udp is specified on command line
c - Changed behavior so it uses '-S server' to shutdown a server process, rather than
c   implicitly shutting down the server after running a benchmark
c - Cleaned up command line parsing
cC
cK37310
cZ+03:00
e
s 00002/00002/00217
d D 1.15 00/02/02 09:57:42 staelin 16 15
c Fix a bug in svc_getargs() and svc_freeargs() calls:  we intended
c to pass a function pointer, but instead we passed the result of
c calling the function.  Oops.  Thanks to David S. Miller for finding
c this bug.
cC
cHhpli8.hpli.hpl.hp.com
cK44033
cZ+02:00
e
s 00002/00002/00217
d D 1.14 98/06/29 22:37:37 lm 15 14
c Redo to compile clean with -Wall.
cC
cK44357
cSAlpha2.11
e
s 00002/00002/00217
d D 1.13 97/06/23 23:27:09 lm 14 13
c carl's diffs.
cK42887
e
s 00001/00001/00218
d D 1.12 97/06/16 19:05:50 lm 13 12
c lint
cK41813
e
s 00007/00007/00212
d D 1.11 97/06/15 22:38:58 lm 12 11
c lint
cK41825
e
s 00026/00020/00193
d D 1.10 97/06/15 14:22:46 lm 11 10
c THe RedHat 4.2 portmapper seems to get confused. I think there is a
c race condition somewhere; at any rate, this seems to fix it.
cK37082
e
s 00017/00016/00196
d D 1.9 97/06/13 20:39:50 lm 10 9
c lint
cK35528
e
s 00015/00017/00197
d D 1.8 97/06/12 21:30:06 lm 9 8
c new bench.h macros.
cK35084
cZ-07:00
e
s 00001/00001/00213
d D 1.7 96/11/21 17:48:04 lm 8 7
c typo
cK40130
e
s 00003/00002/00211
d D 1.6 96/11/13 16:09:37 lm 7 6
c timing.c interfaces.
cK40130
e
s 00015/00020/00198
d D 1.5 96/11/11 03:36:51 lm 6 5
c Auto adjusting changes.
cK40304
e
s 00017/00009/00201
d D 1.4 96/11/08 20:00:31 lm 5 4
c gcc -Wall cleanup.
cK40627
cZ-08:00
e
s 00000/00001/00210
d D 1.3 96/05/30 00:33:07 lm 4 3
c no what strings
cK14378
cZ-07:00
e
s 00001/00001/00210
d D 1.2 95/03/10 18:25:17 lm 3 2
c lint.
cK16449
e
s 00211/00000/00000
d D 1.1 94/11/18 00:49:48 lm 2 1
c Initial revision
cK17008
e
s 00000/00000/00000
d D 1.0 94/11/18 00:49:47 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK10025
cPsrc/lat_rpc.c
cR8144ca9d37f3411e
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
 * lat_rpc.c - simple RPC transaction latency test
 *
 * Four programs in one -
 *	server usage:	lat_rpc -s
 *	client usage:	lat_rpc hostname
D 23
 *	client usage:	lat_rpc hostname tcp
I 17
 *	client usage:	lat_rpc hostname udp
E 17
 *	shutdown:	lat_rpc -hostname
E 23
I 23
 *	client usage:	lat_rpc -p tcp hostname
 *	client usage:	lat_rpc -p udp hostname
 *	shutdown:	lat_rpc -S hostname
E 23
 *
I 23
 * Copyright (c) 2000 Carl Staelin.
E 23
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
char	*id = "$Id$\n";
D 6
#include "timing.c"
E 6
I 6
D 9
#include "timing.h"
E 9
#include "bench.h"
E 6
D 9
#include <ctype.h>
#include <stdio.h>
#include <rpc/rpc.h>
E 9
D 6
#ifndef	N
#define	N	5000
#endif
E 6

D 5
main(ac, av)
	char  **av;
E 5
I 5
void	client_main(int ac, char **av);
D 12
void	server_main();
E 12
I 12
D 17
void	server_main(void);
E 17
I 17
void	server_main();
D 18
void	benchmark(char *server, char* protocol);
E 18
I 18
D 21
void	benchmark(uint64 iterations, void* _state);
E 21
I 21
void	benchmark(iter_t iterations, void* _state);
E 21
E 18
E 17
char	*client_rpc_xact_1(char *argp, CLIENT *clnt);
E 12

I 10
void
doit(CLIENT *cl, char *server)
{
	char	c = 1;
	char	*resp;
	
	resp = client_rpc_xact_1(&c, cl);
	if (!resp) {
		clnt_perror(cl, server);
		exit(1);
	}
	if (*resp != 123) {
		fprintf(stderr, "lat_rpc: got bad data\n");
		exit(1);
	}
}

E 10
D 17
int
main(int ac, char **av)
E 5
{
D 4
	write(2, id, strlen(id));
E 4
	if (ac != 2 && ac != 3) {
		fprintf(stderr, "Usage: %s -s OR %s [-]serverhost [proto]\n",
		    av[0], av[0]);
		exit(1);
	}
	if (!strcmp(av[1], "-s")) {
		if (fork() == 0) {
D 12
			server_main(ac, av);
E 12
I 12
			server_main();
E 12
		}
		exit(0);
	} else {
		client_main(ac, av);
	}
D 12
	exit(0);
E 12
I 12
	return(0);
E 12
}
E 17

/* Default timeout can be changed using clnt_control() */
D 9
static struct timeval TIMEOUT = { 25, 0 };
E 9
I 9
D 23
static struct timeval TIMEOUT = { 0, 2500 };
E 23
I 23
static struct timeval TIMEOUT = { 0, 25000 };
E 23
E 9

I 11
char	*proto[] = { "tcp", "udp", 0 };

I 17
typedef struct state_ {
	int	msize;
	char	*server;
I 18
	char	*protocol;
	CLIENT	*cl;
E 18
} state_t;

E 17
E 11
D 5
client_main(ac, av)
     char  **av;
E 5
I 5
void
D 17
client_main(int ac, char **av)
E 17
I 17
D 18
benchmark(char *server, char* protocol)
E 18
I 18
initialize(void* _state)
E 18
E 17
E 5
{
D 18
	CLIENT *cl;
D 9
	char	c;
	char	*resp;
E 9
D 17
	struct	timeval tv;
D 6
	char	buf[100];
	int	i;
E 6
I 6
D 9
	int	N, i;
E 9
E 6
D 11
	char	*proto;
E 11
	char	*server;
E 17
I 7
	char	buf[256];
E 18
I 11
D 17
	int	i;
E 17
I 17
	struct	timeval tv;
I 18
	state_t *state = (state_t*)_state;
E 18
E 17
E 11
E 7

D 17
	if (ac != 2 && ac != 3) {
D 3
Usage:		fprintf(stderr, "Usage: %s hostname [protocol]\n", av[0]);
E 3
I 3
		fprintf(stderr, "Usage: %s hostname [protocol]\n", av[0]);
E 17
I 17
D 18
	cl = clnt_create(server, XACT_PROG, XACT_VERS, protocol);
	if (!cl) {
		clnt_pcreateerror(server);
E 18
I 18
	state->cl = clnt_create(state->server, XACT_PROG, XACT_VERS, 
				state->protocol);
	if (!state->cl) {
		clnt_pcreateerror(state->server);
E 18
E 17
E 3
		exit(1);
	}
D 11
	proto = ac == 3 ? av[2] : "udp";
E 11
D 17
	server = av[1][0] == '-' ? &av[1][1] : av[1];
D 11
	if (!(cl = clnt_create(server, XACT_PROG, XACT_VERS, proto))) {
		clnt_pcreateerror(server);
		exit(1);
	}
	if (av[1][0] == '-') {
D 5
		clnt_call(cl, RPC_EXIT, xdr_void, 0, xdr_void, 0, TIMEOUT);
E 5
I 5
		clnt_call(cl, RPC_EXIT, (xdrproc_t)xdr_void, 0, 
		    (xdrproc_t)xdr_void, 0, TIMEOUT);
E 5
		exit(0);
    	}
	if (strcmp(proto, "udp") == 0) {
		tv.tv_sec = 0;
D 9
		tv.tv_usec = 2000;
E 9
I 9
		tv.tv_usec = 2500;
E 9
		if (!clnt_control(cl, CLSET_RETRY_TIMEOUT, (char *)&tv)) {
			clnt_perror(cl, "setting timeout");
E 11
I 11
	for (i = 0; i < 2; ++i) {
		if (!(cl =
		    clnt_create(server, XACT_PROG, XACT_VERS, proto[i]))) {
			clnt_pcreateerror(server);
E 17
I 17
D 18
	if (strcasecmp(protocol, proto[1]) == 0) {
E 18
I 18
	if (strcasecmp(state->protocol, proto[1]) == 0) {
E 18
		tv.tv_sec = 0;
		tv.tv_usec = 2500;
D 18
		if (!clnt_control(cl, CLSET_RETRY_TIMEOUT, (char *)&tv)) {
			clnt_perror(cl, "setting timeout");
E 18
I 18
		if (!clnt_control(state->cl, CLSET_RETRY_TIMEOUT, (char *)&tv)) {
			clnt_perror(state->cl, "setting timeout");
E 18
E 17
E 11
			exit(1);
		}
I 11
D 17
		if (av[1][0] == '-') {
done:			clnt_call(cl, RPC_EXIT, (xdrproc_t)xdr_void, 0, 
			    (xdrproc_t)xdr_void, 0, TIMEOUT);
E 17
I 17
	}
D 18
	BENCH(doit(cl, server), MEDIUM);
	sprintf(buf, "RPC/%s latency using %s", protocol, server);
	micro(buf, get_n());
E 18
I 18
}

void
D 21
benchmark(uint64 iterations, void* _state)
E 21
I 21
benchmark(iter_t iterations, void* _state)
E 21
{
	state_t* state = (state_t*)_state;
	char	buf[256];

	while (iterations-- > 0) {
		doit(state->cl, state->server);
	}
E 18
}

D 20
void
E 20
I 20
int
E 20
main(int ac, char **av)
{
	int	i;
	int 	c;
	int	parallel = 1;
I 18
	int	warmup = 0;
	int	repetitions = TRIES;
E 18
	int	server = 0;
	int	shutdown = 0;
D 18
	CLIENT *cl;
E 18
	state_t	state;
I 18
	CLIENT	*cl;
	char	buf[1024];
E 18
	char	*protocol = NULL;
D 18
	char	*usage = "-s\n OR [-p <tcp|udp>] [-P parallel] serverhost\n OR -S serverhost\n";
E 18
I 18
	char	*usage = "-s\n OR [-p <tcp|udp>] [-P parallel] [-W <warmup>] [-N <repetitions>] serverhost\n OR -S serverhost\n";
E 18

	state.msize = 1;

D 18
	while (( c = getopt(ac, av, "sSm:p:P:")) != EOF) {
E 18
I 18
D 23
	while (( c = getopt(ac, av, "sSm:p:P:W:N:")) != EOF) {
E 23
I 23
	while (( c = getopt(ac, av, "sS:m:p:P:W:N:")) != EOF) {
E 23
E 18
		switch(c) {
		case 's': /* Server */
			if (fork() == 0) {
				server_main();
			}
E 17
			exit(0);
D 17
		}
		if (i == 1) {
			tv.tv_sec = 0;
			tv.tv_usec = 2500;
			if (!clnt_control(cl,
			    CLSET_RETRY_TIMEOUT, (char *)&tv)) {
				clnt_perror(cl, "setting timeout");
E 17
I 17
		case 'S': /* shutdown serverhost */
		{
D 23
			cl = clnt_create(av[ac-1], XACT_PROG, XACT_VERS, "udp");
E 23
I 23
			cl = clnt_create(optarg, XACT_PROG, XACT_VERS, "udp");
E 23
			if (!cl) {
				clnt_pcreateerror(state.server);
E 17
				exit(1);
			}
I 17
			clnt_call(cl, RPC_EXIT, (xdrproc_t)xdr_void, 0, 
				  (xdrproc_t)xdr_void, 0, TIMEOUT);
			exit(0);
		}
		case 'm':
			state.msize = atoi(optarg);
			break;
		case 'p':
			protocol = optarg;
			break;
		case 'P':
			parallel = atoi(optarg);
			if (parallel <= 0)
				lmbench_usage(ac, av, usage);
			break;
I 18
		case 'W':
			warmup = atoi(optarg);
			break;
		case 'N':
			repetitions = atoi(optarg);
			break;
E 18
		default:
			lmbench_usage(ac, av, usage);
			break;
E 17
		}
D 17
		BENCH(doit(cl, server), MEDIUM);
		sprintf(buf, "RPC/%s latency using %s", proto[i], server);
		micro(buf, get_n());
E 17
I 17
	}
E 17

I 17
	if (optind != ac - 1) {
		lmbench_usage(ac, av, usage);
	}

	state.server = av[optind++];

D 18
	if (protocol) {
		benchmark(state.server, protocol);
	} else {
		benchmark(state.server, proto[0]);
		benchmark(state.server, proto[1]);
E 18
I 18
D 23
	if (protocol == NULL || strcasecmp(protocol, proto[0])) {
E 23
I 23
	if (protocol == NULL || !strcasecmp(protocol, proto[0])) {
E 23
		state.protocol = proto[0];
		benchmp(initialize, benchmark, NULL, MEDIUM, parallel, 
			warmup, repetitions, &state);
D 19
		sprintf(buf, "RPC/%s latency using %s", proto[0], server);
E 19
I 19
		sprintf(buf, "RPC/%s latency using %s", proto[0], state.server);
E 19
		micro(buf, get_n());
	}

D 23
	if (protocol == NULL || strcasecmp(protocol, proto[1])) {
E 23
I 23
	if (protocol == NULL || !strcasecmp(protocol, proto[1])) {
E 23
		state.protocol = proto[1];
		benchmp(initialize, benchmark, NULL, MEDIUM, parallel, 
			warmup, repetitions, &state);
D 19
		sprintf(buf, "RPC/%s latency using %s", proto[1], server);
E 19
I 19
		sprintf(buf, "RPC/%s latency using %s", proto[1], state.server);
E 19
		micro(buf, get_n());
E 18
E 17
E 11
	}
D 9
	c = 1;
D 6
	start();
	for (i = 0; i < N; ++i) {
		resp = client_rpc_xact_1(&c, cl);
		if (!resp) {
			clnt_perror(cl, server);
			exit(1);
		}
		if (*resp != 123) {
			fprintf(stderr, "%s: got bad data\n", av[0]);
			exit(1);
		}
E 6
I 6
	LOOP_FIRST(N, i, ENOUGH);
E 9
I 9
D 11
	BENCH(doit(cl, server), MEDIUM);
	sprintf(buf, "RPC/%s latency using %s", proto, server);
	micro(buf, get_n());
	exit(0);
E 11
I 11
D 17
	goto done;
E 11
	/* NOTREACHED */
E 17
I 17
		
	exit(0);
E 17
}

D 10
doit(CLIENT *cl, char *server)
{
	char	c = 1;
	char	*resp;
	
E 9
	resp = client_rpc_xact_1(&c, cl);
	if (!resp) {
		clnt_perror(cl, server);
		exit(1);
E 6
	}
D 6
	i = stop();
	sprintf(buf, "RPC/%s latency using %s", proto, server);
	micro(buf, N);
E 6
I 6
	if (*resp != 123) {
D 9
		fprintf(stderr, "%s: got bad data\n", av[0]);
E 9
I 9
		fprintf(stderr, "lat_rpc: got bad data\n");
E 9
		exit(1);
	}
D 9
	LOOP_LAST(N, i, ENOUGH);
D 7
	fprintf(stderr,
	    "RPC/%s latency using %s: %d microseconds\n", proto, server, i/N);
E 7
I 7
D 8
	sprintf(buf", RPC/%s latency using %s", proto, server);
E 8
I 8
	sprintf(buf, "RPC/%s latency using %s", proto, server);
E 8
	micro(buf, N);
E 7
E 6
	exit(0);
	/* NOTREACHED */
E 9
}

E 10
char *
D 12
client_rpc_xact_1(argp, clnt)
	char *argp;
	CLIENT *clnt;
E 12
I 12
client_rpc_xact_1(char *argp, CLIENT *clnt)
E 12
{
	static char res;

D 13
	bzero((char *)&res, sizeof(res));
E 13
I 13
	bzero((void*)&res, sizeof(res));
E 13
D 5
	if (clnt_call(clnt, RPC_XACT, xdr_char, argp, xdr_char, &res, TIMEOUT) != RPC_SUCCESS) {
E 5
I 5
	if (clnt_call(clnt, RPC_XACT, (xdrproc_t)xdr_char,
	    argp, (xdrproc_t)xdr_char, &res, TIMEOUT) != RPC_SUCCESS) {
E 5
		return (NULL);
	}
	return (&res);
}

/*
 * The remote procedure[s] that will be called
 */
I 12
/* ARGSUSED */
E 12
char	*
rpc_xact_1(msg, transp)
     	char	*msg;
	register SVCXPRT *transp;
{
	static char r = 123;

	return &r;
}

static void xact_prog_1();
I 5
D 22
bool_t	pmap_set(u_long prognum, u_long versnum, u_long protocol, u_short port);
bool_t	pmap_unset(u_long prognum, u_long versnum);
E 22
E 5

I 5
void
E 5
D 12
server_main()
E 12
I 12
D 17
server_main(void)
E 17
I 17
server_main()
E 17
E 12
{
	register SVCXPRT *transp;

	GO_AWAY;

	(void) pmap_unset(XACT_PROG, XACT_VERS);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf(stderr, "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, XACT_PROG, XACT_VERS, xact_prog_1, IPPROTO_UDP)) {
		fprintf(stderr, "unable to register (XACT_PROG, XACT_VERS, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf(stderr, "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, XACT_PROG, XACT_VERS, xact_prog_1, IPPROTO_TCP)) {
		fprintf(stderr, "unable to register (XACT_PROG, XACT_VERS, tcp).");
		exit(1);
	}

	svc_run();
	fprintf(stderr, "svc_run returned");
	exit(1);
	/* NOTREACHED */
}

static void
xact_prog_1(rqstp, transp)
	struct svc_req *rqstp;
	register SVCXPRT *transp;
{
	union {
		char rpc_xact_1_arg;
	} argument;
	char *result;
	bool_t (*xdr_argument)(), (*xdr_result)();
	char *(*local)();

	switch (rqstp->rq_proc) {
	case NULLPROC:
D 5
		(void) svc_sendreply(transp, xdr_void, (char *)NULL);
E 5
I 5
		(void) svc_sendreply(transp, (xdrproc_t)xdr_void, (char *)NULL);
E 5
		return;

	case RPC_XACT:
		xdr_argument = xdr_char;
		xdr_result = xdr_char;
		local = (char *(*)()) rpc_xact_1;
		break;

	case RPC_EXIT:
D 5
		(void) svc_sendreply(transp, xdr_void, (char *)NULL);
E 5
I 5
		(void) svc_sendreply(transp, (xdrproc_t)xdr_void, (char *)NULL);
E 5
		(void) pmap_unset(XACT_PROG, XACT_VERS);
		exit(0);

	default:
		svcerr_noproc(transp);
		return;
	}
	bzero((char *)&argument, sizeof(argument));
D 14
	if (!svc_getargs(transp, xdr_argument, &argument)) {
E 14
I 14
D 15
	if (!svc_getargs(transp, xdr_argument, (char*)&argument)) {
E 15
I 15
D 16
	if (!svc_getargs(transp, (void *)(xdr_argument)(), (char*)&argument)) {
E 16
I 16
D 19
	if (!svc_getargs(transp, (void *)xdr_argument, (char*)&argument)) {
E 19
I 19
	if (!svc_getargs(transp, (xdrproc_t)xdr_argument, (char*)&argument)) {
E 19
E 16
E 15
E 14
		svcerr_decode(transp);
		return;
	}
	result = (*local)(&argument, rqstp);
D 5
	if (result != NULL && !svc_sendreply(transp, xdr_result, result)) {
E 5
I 5
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t)xdr_result, result)) {
E 5
		svcerr_systemerr(transp);
	}
D 14
	if (!svc_freeargs(transp, xdr_argument, &argument)) {
E 14
I 14
D 15
	if (!svc_freeargs(transp, xdr_argument, (char*)&argument)) {
E 15
I 15
D 16
	if (!svc_freeargs(transp, (void*)(xdr_argument)(), (char*)&argument)) {
E 16
I 16
D 19
	if (!svc_freeargs(transp, (void*)xdr_argument, (char*)&argument)) {
E 19
I 19
	if (!svc_freeargs(transp, (xdrproc_t)xdr_argument, (char*)&argument)) {
E 19
E 16
E 15
E 14
		fprintf(stderr, "unable to free arguments");
		exit(1);
	}
	return;
}
E 2
I 1
E 1
