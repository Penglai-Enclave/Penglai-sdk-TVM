h50209
s 00001/00001/00095
d D 1.10 00/09/13 12:48:47 staelin 11 10
c - Add a missing htons() that was causing Intel arch to break.
cC
cHhpli8.hpli.hpl.hp.com
cK22286
cZ+03:00
e
s 00003/00003/00093
d D 1.9 97/06/16 19:05:50 lm 10 9
c lint
cC
cK21649
cSAlpha2.11
e
s 00004/00008/00092
d D 1.8 97/06/15 22:38:58 lm 9 8
c lint
cK21032
e
s 00000/00001/00100
d D 1.7 97/06/12 21:30:06 lm 8 7
c new bench.h macros.
cK22863
e
s 00003/00031/00098
d D 1.6 97/04/23 22:46:13 lm 7 6
c lint.
cK24610
cZ-07:00
e
s 00001/00009/00128
d D 1.5 96/11/11 03:36:51 lm 6 5
c Auto adjusting changes.
cK02598
e
s 00008/00000/00129
d D 1.4 96/11/08 20:04:21 lm 5 4
c gcc -Wall cleanup.
cK25127
e
s 00025/00021/00104
d D 1.3 95/03/10 18:14:27 lm 4 3
c optimization cleanup.
cK09066
e
s 00020/00000/00105
d D 1.2 95/02/14 11:01:06 lm 3 2
c HIPPI
cK61896
e
s 00105/00000/00000
d D 1.1 94/11/18 00:49:48 lm 2 1
c Initial revision
cK35332
e
s 00000/00000/00000
d D 1.0 94/11/18 00:49:47 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK37686
cPsrc/lib_udp.c
cR742df623760bb62f
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
 * udp_lib.c - routines for managing UDP connections
 *
 * %W% %G%
 *
 * Copyright (c) 1994 Larry McVoy.
 */
I 7
#define		_LIB /* bench.h needs this */
E 7
#include	"bench.h"
D 6
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<netdb.h>
#include	<arpa/inet.h>
E 6
I 6
D 8
#include	"lib_udp.h"
E 8
E 6

I 5
D 6
void	sock_optimize();
bool_t	pmap_set(u_long prognum, u_long versnum, u_long protocol, u_short port);
bool_t	pmap_unset(u_long prognum, u_long versnum);

E 6
E 5
/*
 * Get a UDP socket, bind it, figure out the port,
 * and advertise the port as program "prog".
 *
 * XXX - it would be nice if you could advertise ascii strings.
 */
I 5
int
E 5
D 4
udp_server(prog)
E 4
I 4
D 9
udp_server(prog, rdwr)
E 4
	u_long	prog;
E 9
I 9
udp_server(u_long prog, int rdwr)
E 9
{
D 7
	int	sock, namelen;
E 7
I 7
	int	sock;
E 7
	struct	sockaddr_in s;

	if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		perror("socket");
		exit(1);
	}
I 3
D 4
#ifdef HIPPI
#ifndef	NO_SETSOCKOPT
	{ int	sockbuf = 1024 * 1024;

	while (setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &sockbuf, sizeof(int))) {
		sockbuf >>= 1;
	}
	}
#endif
#endif
E 4
I 4
	sock_optimize(sock, rdwr);
E 4
E 3
D 10
	bzero((char*)&s, sizeof(s));
E 10
I 10
	bzero((void*)&s, sizeof(s));
E 10
	s.sin_family = AF_INET;
#ifdef	NO_PORTMAPPER
	s.sin_port = htons(prog);
#endif
	if (bind(sock, (struct sockaddr*)&s, sizeof(s)) < 0) {
		perror("bind");
		exit(2);
	}
#ifndef	NO_PORTMAPPER
D 7
	namelen = sizeof(s);
	if (getsockname(sock, (struct sockaddr *)&s, &namelen) < 0) {
		perror("getsockname");
		exit(3);
	}
E 7
	(void)pmap_unset(prog, (u_long)1);
	if (!pmap_set(prog, (u_long)1, (u_long)IPPROTO_UDP,
D 7
	    (u_long)ntohs(s.sin_port))) {
E 7
I 7
D 9
	    (u_long)sockport(sock))) {
E 9
I 9
	    (unsigned short)sockport(sock))) {
E 9
E 7
		perror("pmap_set");
		exit(5);
	}
#endif
	return (sock);
}

/*
 * Unadvertise the socket
 */
I 5
void
E 5
D 9
udp_done(prog)
E 9
I 9
udp_done(int prog)
E 9
{
	(void)pmap_unset((u_long)prog, (u_long)1);
}

/*
 * "Connect" to the UCP socket advertised as "prog" on "host" and
 * return the connected socket.
 */
I 5
int
E 5
D 4
udp_connect(host, prog)
E 4
I 4
D 9
udp_connect(host, prog, rdwr)
E 4
	char	*host;
	u_long	prog;
E 9
I 9
udp_connect(char *host, u_long prog, int rdwr)
E 9
{
	struct hostent *h;
	struct sockaddr_in sin;
D 4
	int     sockbuf = SOCKBUF;
E 4
	int	sock;
	u_short	port;
D 9
	u_short	pmap_getport();
E 9

	if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		perror("socket");
		exit(1);
	}
I 4
	sock_optimize(sock, rdwr);
E 4
	if (!(h = gethostbyname(host))) {
		perror(host);
		exit(2);
	}
D 10
	bzero((char *) &sin, sizeof(sin));
E 10
I 10
	bzero((void *) &sin, sizeof(sin));
E 10
	sin.sin_family = AF_INET;
D 10
	bcopy(h->h_addr, (char *) &sin.sin_addr, h->h_length);
E 10
I 10
	bcopy((void*)h->h_addr, (void *) &sin.sin_addr, h->h_length);
E 10
#ifdef	NO_PORTMAPPER
D 11
	sin.sin_port = prog;
E 11
I 11
	sin.sin_port = htons(prog);
E 11
#else
	port = pmap_getport(&sin, prog, (u_long)1, IPPROTO_UDP);
	if (!port) {
		perror("lib UDP: No port found");
		exit(3);
	}
	sin.sin_port = htons(port);
#endif
	if (connect(sock, (struct sockaddr*)&sin, sizeof(sin)) < 0) {
		perror("connect");
		exit(4);
	}
I 3
D 4
#ifdef HIPPI
#ifndef	NO_SETSOCKOPT
	{ int	sockbuf = 1024 * 1024;
E 4
I 4
	return (sock);
}
E 4
D 7

D 4
	while (setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sockbuf, sizeof(int))) {
		sockbuf >>= 1;
E 4
I 4
/*
 * This is identical in lib_tcp.c and lib_udp.c
 */
I 5
void
E 5
sock_optimize(sock, rdwr)
{
	if (rdwr == SOCKOPT_READ || rdwr == SOCKOPT_RDWR) {
		int	sockbuf = SOCKBUF;

		while (setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &sockbuf,
		    sizeof(int))) {
			sockbuf -= SOCKSTEP;
		}
E 4
	}
I 4
	if (rdwr == SOCKOPT_WRITE || rdwr == SOCKOPT_RDWR) {
		int	sockbuf = SOCKBUF;

		while (setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sockbuf,
		    sizeof(int))) {
			sockbuf -= SOCKSTEP;
		}
E 4
	}
D 4
#endif
#endif
E 3
	return (sock);
E 4
}
E 7
E 2
I 1
E 1
