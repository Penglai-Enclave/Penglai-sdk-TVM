H51447
s 00010/00000/00000
d D 1.1 02/10/01 09:48:25 staelin 2 1
cC
cF1
cK22250
cO-rw-rw-r--
e
s 00000/00000/00000
d D 1.0 02/10/01 09:48:25 staelin 1 0
c BitKeeper file /usr/WebPaper/users/staelin/src/LMbench3/src/lib_debug.h
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHhpli69.hpli.hpl.hp.com
cK33616
cPsrc/lib_debug.h
cRcc6fc1f0c7338ad8
cV4
cX0x821
cZ+03:00
e
u
U
f e 0
f x 0x821
t
T
I 2
#ifndef _LIB_DEBUG_H
#define _LIB_DEBUG_H

void	print_results(int details);
void	bw_quartile(uint64 bytes);
void	nano_quartile(uint64 n);
void	print_mem(char* addr, size_t size, size_t line);
void	check_mem(char* addr, size_t size);

#endif /* _LIB_DEBUG_H */
E 2
I 1
E 1
