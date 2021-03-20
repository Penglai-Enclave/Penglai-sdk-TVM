h42481
s 00000/00003/00012
d D 1.4 00/09/24 12:52:43 staelin 5 4
c - Remove unnecessary function prototypes for pmap_*() functions
cC
cHhpli8.hpli.hpl.hp.com
cK28305
cZ+03:00
e
s 00001/00000/00014
d D 1.3 97/06/15 22:38:58 lm 4 3
c lint
cC
cK49958
cSAlpha2.11
cZ-07:00
e
s 00003/00003/00011
d D 1.2 96/12/16 12:30:01 lm 3 2
c positive/negative port numbers.
cK48105
e
s 00014/00000/00000
d D 1.1 96/11/13 16:15:00 lm 2 1
c Initial revision
cK49044
e
s 00000/00000/00000
d D 1.0 96/11/13 16:14:59 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK32750
cPsrc/lib_tcp.h
cRfae00e4b816a260
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
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<netdb.h>
#include	<arpa/inet.h>

D 3
int	tcp_server(u_long prog, int rdwr);
int	tcp_done(u_long prog);
E 3
I 3
int	tcp_server(int prog, int rdwr);
int	tcp_done(int prog);
E 3
int	tcp_accept(int sock, int rdwr);
D 3
int	tcp_connect(char *host, u_long prog, int rdwr);
E 3
I 3
int	tcp_connect(char *host, int prog, int rdwr);
E 3
void	sock_optimize(int sock, int rdwr);
I 4
int	sockport(int s);
E 4
D 5
u_short	pmap_getport(struct sockaddr_in *addr, u_long prognum, u_long versnum, u_int protocol);
bool_t	pmap_set(u_long prognum, u_long versnum, u_long protocol, u_short port);
bool_t	pmap_unset(u_long prognum, u_long versnum);
E 5
E 2
I 1
E 1
