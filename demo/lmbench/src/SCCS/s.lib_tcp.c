h24478
s 00003/00001/00235
d D 1.13 00/10/31 10:00:55 staelin 14 13
c - Allow tcp_connect() to retry on EAGAIN
c - Add SOCKOPT_REUSE to tcp_server() call
cC
cHhpli8.hpli.hpl.hp.com
cK03317
cZ+02:00
e
s 00008/00007/00228
d D 1.12 97/06/16 19:05:50 lm 13 12
c lint
cC
cK01568
cSAlpha2.11
e
s 00005/00007/00230
d D 1.11 97/06/15 22:38:58 lm 12 11
c lint
cK00790
e
s 00000/00004/00237
d D 1.10 97/06/12 21:30:06 lm 11 10
c new bench.h macros.
cK64318
e
s 00018/00010/00223
d D 1.9 97/04/23 22:49:43 lm 10 9
c a bug and lint.
cK03959
cZ-07:00
e
s 00058/00037/00175
d D 1.8 97/02/07 22:19:47 lm 9 8
c listen backlog -> 100, getport(), options.
cK56710
e
s 00038/00037/00174
d D 1.7 96/12/16 12:29:42 lm 8 7
c positive/negative port numbers.
cK29412
e
s 00002/00011/00209
d D 1.6 96/11/11 03:36:51 lm 7 6
c Auto adjusting changes.
cK24507
e
s 00013/00003/00207
d D 1.5 96/11/08 20:04:16 lm 6 5
c gcc -Wall cleanup.
cK56211
cZ-08:00
e
s 00012/00009/00198
d D 1.4 95/09/25 22:52:27 lm 5 4
c caching looked busted to me.
cK31312
e
s 00044/00009/00163
d D 1.3 95/08/22 15:35:28 lm 4 3
c Looks like all LIBTCP_VERBOSE ifdefs.
cK22909
cZ-07:00
e
s 00038/00009/00134
d D 1.2 95/03/10 18:14:27 lm 3 2
c optimization cleanup.
cK17912
e
s 00143/00000/00000
d D 1.1 94/11/18 00:49:48 lm 2 1
c Initial revision
cK41711
e
s 00000/00000/00000
d D 1.0 94/11/18 00:49:47 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK22782
cPsrc/lib_tcp.c
cR70231aa7476519f5
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
 * tcp_lib.c - routines for managing TCP connections.
 *
D 8
 * Copyright (c) 1994 Larry McVoy.
E 8
I 8
 * Positive port/program numbers are RPC ports, negative ones are TCP ports.
 *
 * Copyright (c) 1994-1996 Larry McVoy.
E 8
 */
D 7
#include	"bench.h"
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<netdb.h>
#include	<arpa/inet.h>
E 7
I 6
D 11
#include	<rpc/rpc.h>
E 11
I 10
#define		_LIB /* bench.h needs this */
E 10
I 7
#include	"bench.h"
D 11
#include	"lib_tcp.h"
E 11
E 7
E 6

I 4
D 6
/* #define	LIBTCP_VERBOSE	/**/
E 6
I 6
D 11
#undef	LIBTCP_VERBOSE
E 6

E 11
E 4
D 6
u_short	pmap_getport();
E 6
I 6
D 7
u_short	pmap_getport(struct sockaddr_in *addr, u_long prognum, u_long versnum, u_int protocol);
bool_t	pmap_set(u_long prognum, u_long versnum, u_long protocol, u_short port);
bool_t	pmap_unset(u_long prognum, u_long versnum);
void	sock_optimize();
E 6

E 7
/*
 * Get a TCP socket, bind it, figure out the port,
 * and advertise the port as program "prog".
 *
 * XXX - it would be nice if you could advertise ascii strings.
 */
D 3
tcp_server(prog)
E 3
I 3
int
D 9
tcp_server(prog, rdwr)
E 3
D 8
	u_long	prog;
E 8
I 8
	int	prog;
E 8
I 3
	int	rdwr;
E 9
I 9
tcp_server(int prog, int rdwr)
E 9
E 3
{
D 10
	int	sock, namelen;
E 10
I 10
	int	sock;
E 10
	struct	sockaddr_in s;

I 9
#ifdef	LIBTCP_VERBOSE
	fprintf(stderr, "tcp_server(%u, %u)\n", prog, rdwr);
#endif
E 9
	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror("socket");
		exit(1);
	}
I 3
	sock_optimize(sock, rdwr);
E 3
D 13
	bzero((char*)&s, sizeof(s));
E 13
I 13
	bzero((void*)&s, sizeof(s));
E 13
	s.sin_family = AF_INET;
D 8
#ifdef	NO_PORTMAPPER
	s.sin_port = htons(prog);
#endif
E 8
I 8
	if (prog < 0) {
		s.sin_port = htons(-prog);
	}
E 8
	if (bind(sock, (struct sockaddr*)&s, sizeof(s)) < 0) {
		perror("bind");
		exit(2);
	}
D 9
	if (listen(sock, 1) < 0) {
E 9
I 9
	if (listen(sock, 100) < 0) {
E 9
		perror("listen");
		exit(4);
	}
D 8
#ifndef	NO_PORTMAPPER
	namelen = sizeof(s);
	if (getsockname(sock, (struct sockaddr *)&s, &namelen) < 0) {
		perror("getsockname");
		exit(3);
	}
E 8
I 8
	if (prog > 0) {
D 9
		namelen = sizeof(s);
		if (getsockname(sock, (struct sockaddr *)&s, &namelen) < 0) {
			perror("getsockname");
			exit(3);
		}
E 9
E 8
I 4
#ifdef	LIBTCP_VERBOSE
D 8
	fprintf(stderr, "Server port %d\n", ntohs(s.sin_port));
E 8
I 8
D 9
		fprintf(stderr, "Server port %d\n", ntohs(s.sin_port));
E 9
I 9
		fprintf(stderr, "Server port %d\n", sockport(sock));
E 9
E 8
#endif
E 4
D 8
	(void)pmap_unset(prog, (u_long)1);
	if (!pmap_set(prog, (u_long)1, (u_long)IPPROTO_TCP,
	    (u_long)ntohs(s.sin_port))) {
		perror("pmap_set");
		exit(5);
E 8
I 8
		(void)pmap_unset((u_long)prog, (u_long)1);
		if (!pmap_set((u_long)prog, (u_long)1, (u_long)IPPROTO_TCP,
D 9
		    (u_long)ntohs(s.sin_port))) {
E 9
I 9
D 10
		    (u_long)ntohs(sockport(sock)))) {
E 10
I 10
D 12
		    (u_long)sockport(sock))) {
E 12
I 12
		    (unsigned short)sockport(sock))) {
E 12
E 10
E 9
			perror("pmap_set");
			exit(5);
		}
E 8
	}
D 8
#endif
E 8
	return (sock);
}

/*
 * Unadvertise the socket
 */
I 6
int
E 6
D 12
tcp_done(prog)
I 3
D 8
	u_long	prog;
E 8
I 8
	int	prog;
E 12
I 12
tcp_done(int prog)
E 12
E 8
E 3
{
I 4
D 8
#ifndef	NO_PORTMAPPER
E 4
	pmap_unset((u_long)prog, (u_long)1);
I 4
#endif
E 8
I 8
	if (prog > 0) {
		pmap_unset((u_long)prog, (u_long)1);
	}
E 8
E 4
I 3
	return (0);
E 3
}

/*
 * Accept a connection and return it
 */
I 6
int
E 6
D 3
tcp_accept(sock)
E 3
I 3
D 12
tcp_accept(sock, rdwr)
	int	sock, rdwr;
E 12
I 12
tcp_accept(int sock, int rdwr)
E 12
E 3
{
	struct	sockaddr_in s;
	int	newsock, namelen;

	namelen = sizeof(s);
D 13
	bzero((char*)&s, namelen);
E 13
I 13
	bzero((void*)&s, namelen);
E 13

I 3
retry:
E 3
	if ((newsock = accept(sock, (struct sockaddr*)&s, &namelen)) < 0) {
I 3
		if (errno == EINTR)
			goto retry;
E 3
		perror("accept");
		exit(6);
	}
I 4
#ifdef	LIBTCP_VERBOSE
D 9
	namelen = sizeof(s);
	if (getsockname(newsock, (struct sockaddr *)&s, &namelen) < 0) {
		perror("getsockname");
		exit(3);
	}
	fprintf(stderr, "Server newsock port %d\n", ntohs(s.sin_port));
E 9
I 9
	fprintf(stderr, "Server newsock port %d\n", sockport(newsock));
E 9
#endif
E 4
I 3
	sock_optimize(newsock, rdwr);
E 3
	return (newsock);
}

/*
 * Connect to the TCP socket advertised as "prog" on "host" and
 * return the connected socket.
 *
 * Hacked Thu Oct 27 1994 to cache pmap_getport calls.  This saves
 * about 4000 usecs in loopback lat_connect calls.  I suppose we
 * should time gethostbyname() & pmap_getprot(), huh?
 */
I 6
int
E 6
D 3
tcp_connect(host, prog)
E 3
I 3
D 8
tcp_connect(host, prog, rdwr)
E 3
	char	*host;
	u_long	prog;
I 3
	int	rdwr;
E 8
I 8
tcp_connect(char *host, int prog, int rdwr)
E 8
E 3
{
	static	struct hostent *h;
D 4
	static	struct sockaddr_in sin;
E 4
I 4
	static	struct sockaddr_in s;
E 4
D 5
	static	u_short	port;
E 5
I 5
	static	u_short	save_port;
E 5
	static	u_long save_prog;
	static	char *save_host;
D 4
	int	sock;
E 4
I 4
D 6
	int	sock, namelen;
E 6
I 6
	int	sock;
I 10
	static	int tries = 0;
E 10
E 6
E 4
D 3
	int     sockbuf = SOCKBUF;
E 3

	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror("socket");
		exit(1);
	}
I 9
	if (rdwr & SOCKOPT_PID) {
		static	unsigned short port;
		struct sockaddr_in sin;

		if (!port) {
D 12
			port = getpid() << 4;
E 12
I 12
			port = (unsigned short)(getpid() << 4);
E 12
			if (port < 1024) {
				port += 1024;
			}
		}
		do {
			port++;
D 13
			bzero((char*)&sin, sizeof(sin));
E 13
I 13
			bzero((void*)&sin, sizeof(sin));
E 13
			sin.sin_family = AF_INET;
			sin.sin_port = htons(port);
		} while (bind(sock, (struct sockaddr*)&sin, sizeof(sin)) == -1);
	}
E 9
I 4
#ifdef	LIBTCP_VERBOSE
I 6
D 9
	{ int	namelen;
E 6
	bzero((char*)&s, sizeof(s));
	s.sin_family = AF_INET;
	if (bind(sock, (struct sockaddr*)&s, sizeof(s)) < 0) {
		perror("bind");
		exit(2);
E 9
I 9
	else {
		struct sockaddr_in sin;

D 13
		bzero((char*)&sin, sizeof(sin));
E 13
I 13
		bzero((void*)&sin, sizeof(sin));
E 13
		sin.sin_family = AF_INET;
		if (bind(sock, (struct sockaddr*)&sin, sizeof(sin)) < 0) {
			perror("bind");
			exit(2);
		}
E 9
	}
D 9
	namelen = sizeof(s);
	if (getsockname(sock, (struct sockaddr *)&s, &namelen) < 0) {
		perror("getsockname");
		exit(3);
	}
	fprintf(stderr, "Client port %d\n", ntohs(s.sin_port));
I 6
	}
E 9
I 9
	fprintf(stderr, "Client port %d\n", sockport(sock));
E 9
E 6
#endif
E 4
D 3
#ifndef	NO_SETSOCKOPT
	while (setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sockbuf, sizeof(int))) {
		sockbuf -= 128;
	}
#endif
E 3
I 3
	sock_optimize(sock, rdwr);
E 3
	if (!h || host != save_host || prog != save_prog) {
D 5
		save_host = host;	/* XXX - counting on their not
					 * changing it - benchmark only`
E 5
I 5
		save_host = host;	/* XXX - counting on them not
					 * changing it - benchmark only.
E 5
					 */
		save_prog = prog;
		if (!(h = gethostbyname(host))) {
			perror(host);
			exit(2);
		}
D 4
		bzero((char *) &sin, sizeof(sin));
		sin.sin_family = AF_INET;
		bcopy(h->h_addr, (char *) &sin.sin_addr, h->h_length);
E 4
I 4
D 13
		bzero((char *) &s, sizeof(s));
E 13
I 13
		bzero((void *) &s, sizeof(s));
E 13
		s.sin_family = AF_INET;
D 13
		bcopy(h->h_addr, (char *) &s.sin_addr, h->h_length);
E 13
I 13
		bcopy((void*)h->h_addr, (void *)&s.sin_addr, h->h_length);
E 13
E 4
D 5
#ifdef	NO_PORTMAPPER
D 4
		sin.sin_port = prog;
E 4
I 4
		s.sin_port = prog;
E 4
#else
D 4
		port = pmap_getport(&sin, prog, (u_long)1, IPPROTO_TCP);
E 4
I 4
		port = pmap_getport(&s, prog, (u_long)1, IPPROTO_TCP);
E 4
		if (!port) {
E 5
I 5
D 8
		save_port = pmap_getport(&s, prog, (u_long)1, IPPROTO_TCP);
		if (!save_port) {
E 5
			perror("lib TCP: No port found");
			exit(3);
		}
E 8
I 8
		if (prog > 0) {
D 13
			save_port = pmap_getport(&s, prog, (u_long)1, IPPROTO_TCP);
E 13
I 13
			save_port = pmap_getport(&s, prog,
			    (u_long)1, IPPROTO_TCP);
E 13
			if (!save_port) {
				perror("lib TCP: No port found");
				exit(3);
			}
E 8
D 4
		sin.sin_port = htons(port);
E 4
I 4
D 5
		s.sin_port = htons(port);
E 5
I 5
#ifdef	LIBTCP_VERBOSE
D 8
		fprintf(stderr, "Server port %d\n", save_port);
E 8
I 8
			fprintf(stderr, "Server port %d\n", save_port);
E 8
E 5
E 4
#endif
I 9
			s.sin_port = htons(save_port);
		} else {
			s.sin_port = htons(-prog);
E 9
I 8
		}
E 8
	}
I 5
D 8
#ifdef	NO_PORTMAPPER
	s.sin_port = prog;
#else
	s.sin_port = htons(save_port);
#endif
E 8
I 8
D 9
	if (prog < 0) {
		s.sin_port = htons(-prog);
	} else {
		s.sin_port = htons(save_port);
	}
E 9
E 8
E 5
D 4
	if (connect(sock, (struct sockaddr*)&sin, sizeof(sin)) < 0) {
E 4
I 4
	if (connect(sock, (struct sockaddr*)&s, sizeof(s)) < 0) {
I 9
D 14
		if (errno == ECONNRESET || errno == ECONNREFUSED) {
E 14
I 14
		if (errno == ECONNRESET 
		    || errno == ECONNREFUSED
		    || errno == EAGAIN) {
E 14
			close(sock);
I 10
			if (++tries > 10) return(errno);
E 10
			return (tcp_connect(host, prog, rdwr));
		}
E 9
E 4
		perror("connect");
		exit(4);
	}
I 10
	tries = 0;
E 10
	return (sock);
}
I 3

D 10
/*
 * This is identical in lib_tcp.c and lib_udp.c
 */
E 10
I 6
void
E 6
D 10
sock_optimize(sock, rdwr)
E 10
I 10
D 12
sock_optimize(sock, flags)
E 12
I 12
sock_optimize(int sock, int flags)
E 12
E 10
{
D 9
	if (rdwr == SOCKOPT_READ || rdwr == SOCKOPT_RDWR) {
E 9
I 9
D 10
	if (rdwr & SOCKOPT_READ) {
E 10
I 10
	if (flags & SOCKOPT_READ) {
E 10
E 9
		int	sockbuf = SOCKBUF;

		while (setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &sockbuf,
		    sizeof(int))) {
D 10
			sockbuf -= SOCKSTEP;
E 10
I 10
			sockbuf >>= 1;
E 10
		}
I 4
#ifdef	LIBTCP_VERBOSE
		fprintf(stderr, "sockopt %d: RCV: %dK\n", sock, sockbuf>>10);
#endif
E 4
	}
D 9
	if (rdwr == SOCKOPT_WRITE || rdwr == SOCKOPT_RDWR) {
E 9
I 9
D 10
	if (rdwr & SOCKOPT_WRITE) {
E 10
I 10
	if (flags & SOCKOPT_WRITE) {
E 10
E 9
		int	sockbuf = SOCKBUF;

		while (setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sockbuf,
		    sizeof(int))) {
D 10
			sockbuf -= SOCKSTEP;
E 10
I 10
			sockbuf >>= 1;
E 10
		}
I 4
#ifdef	LIBTCP_VERBOSE
		fprintf(stderr, "sockopt %d: SND: %dK\n", sock, sockbuf>>10);
#endif
E 4
	}
I 10
	if (flags & SOCKOPT_REUSE) {
		int	val = 1;
		if (setsockopt(sock, SOL_SOCKET,
		    SO_REUSEADDR, &val, sizeof(val)) == -1) {
			perror("SO_REUSEADDR");
		}
	}
E 10
}
I 9

int
sockport(int s)
{
	int	namelen;
	struct sockaddr_in sin;

	namelen = sizeof(sin);
	if (getsockname(s, (struct sockaddr *)&sin, &namelen) < 0) {
		perror("getsockname");
		return(-1);
	}
	return ((int)ntohs(sin.sin_port));
}
E 9
E 3
E 2
I 1
E 1
