H16013
s 00001/00001/00409
d D 1.79 02/10/28 14:19:54 staelin 80 79
c src/Makefile: fix typo in updated distribution generation target
cC
cK16912
e
s 00007/00006/00403
d D 1.78 02/10/28 14:16:32 staelin 79 78
c src/Makefile: fixup the distribution generation target so it will
c   create a tarball which more accurately reflects current standards
c   for software distribution.  E.g., the files are under lmbench-vers
c   rather than LMbench, and so forth.
cC
cK16634
e
s 00006/00003/00403
d D 1.77 02/10/20 11:04:54 staelin 78 77
c src/Makefile: move optional programs to a separate make target and
c   don't make benchmark build depend upon them
cC
cHhpli69.hpli.hpl.hp.com
cK07376
e
s 00002/00005/00404
d D 1.76 02/10/20 09:29:18 staelin 77 76
c src/Makefile: remove references to bw_shm
cC
cK65287
e
s 00007/00007/00402
d D 1.75 02/10/20 09:23:35 staelin 76 75
c src/Makefile: remove references to lat_itimer (which was merged
c   into lat_usleep)
cC
cHhpliclu3.hpli.hpl.hp.com
cK10606
e
s 00005/00001/00404
d D 1.74 02/10/17 14:15:32 staelin 75 74
c lat_usleep.c: Add new benchmark to measure usleep(3) and setitimer(2)
c   sleep resolution.
cC
cK12897
cZ+02:00
e
s 00015/00007/00390
d D 1.73 02/10/01 09:48:46 staelin 74 73
c - Add new lib_debug.[ch] for various debugging routines
cC
cHhpli69.hpli.hpl.hp.com
cK62389
cZ+03:00
e
s 00007/00000/00390
d D 1.72 02/02/22 09:20:41 staelin 73 72
c Add a new target 'scaling' which is like 'rerun' except 
c it asks you what scaling factor you want to use during this
c run, leaving the remaining parameters fixed.
cC
cHfirewall.staelin.co.il
cK28196
cZ+02:00
e
s 00005/00005/00385
d D 1.71 01/06/19 12:09:17 staelin 72 71
c Add a fix to scripts/make which verifies that gmake actually works
cC
cK06892
e
s 00019/00008/00371
d D 1.70 01/06/19 10:28:05 staelin 71 70
c Update 'make dist' target so it does the right thing
cC
cK10180
e
s 00005/00000/00374
d D 1.69 01/06/13 12:29:44 staelin 70 69
c Fixup Makefile so gmake won't complain so much
cC
cK61272
e
s 00001/00001/00373
d D 1.68 01/06/12 17:37:15 staelin 69 68
c Remove bw_udp from build list; it hasn't been written yet...
cC
cHhpli69.hpli.hpl.hp.com
cK47496
cZ+03:00
e
s 00017/00008/00357
d D 1.67 01/01/07 15:30:05 staelin 68 67
c - Update Makefile so we can use gmake's parallel build capability
cC
cK48331
e
s 00003/00002/00362
d D 1.66 00/10/16 17:24:49 staelin 67 66
c - Add lat_sem benchmark to measure semaphore latency
cC
cK28056
e
s 00020/00007/00344
d D 1.65 00/10/16 17:13:56 staelin 66 65
c - update 'make install' target to include new man pages
cC
cK29826
cZ+02:00
e
s 00008/00006/00343
d D 1.64 00/09/18 16:44:06 staelin 65 64
c - Create lib_mem.h and lib_mem.c to hold common routines for memory subsystem analysis
cC
cK48943
e
s 00001/00001/00348
d D 1.63 00/09/18 11:33:10 staelin 64 63
c - Add ability for user to select which subset of benchmarks to run, including ability
c   to select (almost) individual benchmarks
cC
cK41121
e
s 00005/00002/00344
d D 1.62 00/08/16 13:10:07 staelin 63 62
c - Add par_ops
cC
cK44033
e
s 00004/00004/00342
d D 1.61 00/08/16 09:33:12 staelin 62 61
c - Rename loads to par_mem
cC
cK32473
e
s 00020/00014/00326
d D 1.60 00/08/03 14:26:15 staelin 61 60
c - Add targets for hardware and os benchmark subsets
cC
cK31237
e
s 00020/00001/00320
d D 1.59 00/08/02 18:04:55 staelin 60 59
c - Add bk.ver target which extracts the BK tag/version from the ChangeSet
c - Change disk.c so it does #include "flushdisk.c" and doesn't need flushdisk.c on the
c   compiler's command line (which means that the compiler doesn't generate .o files in
c   the src directory, which can cause problems in a cluster environment)
cC
cK17300
e
s 00005/00002/00316
d D 1.58 00/07/31 10:07:15 staelin 59 58
c Add stream, an lmbench clone of John McCalpin's STREAM benchmark
cC
cK52474
e
s 00013/00008/00305
d D 1.57 00/07/25 13:48:36 staelin 58 57
c - add new lat_ops benchmark
cC
cK41579
e
s 00005/00002/00308
d D 1.56 00/07/06 15:49:10 staelin 57 56
c - Add hooks for bw_udp to Makefile so it will be built
cC
cK29777
e
s 00015/00012/00295
d D 1.55 00/07/05 14:37:16 staelin 56 55
c - Add new benchmark loads which attempts to deduce the number of LOAD instructions
c   which may execute in parallel on a system
cC
cK17990
e
s 00003/00003/00304
d D 1.54 00/07/04 14:55:45 staelin 55 54
c - Add dependencies on $O/lmbench.a to line, tlb, and cache
cC
cK06036
e
s 00012/00001/00295
d D 1.53 00/07/02 18:34:21 staelin 54 53
c - Add three new benchmarks: line, tlb, and cache, which measure cache line size,
c   tlb size, and cache size
cC
cK02934
e
s 00010/00034/00286
d D 1.52 00/06/27 17:47:39 staelin 53 52
c - Switch to using a build script to automagically identify compile flags
cC
cK42816
cZ+03:00
e
s 00018/00011/00302
d D 1.51 00/04/17 13:05:58 staelin 52 51
c - add a script to figure out which make to use
c - add lat_fcntl to the list of available benchmarks
c - add a target to 'build' the various scripts
cC
cK31956
e
s 00004/00003/00309
d D 1.50 00/02/23 11:15:35 staelin 51 50
c Add getopt to lmbench.a
cC
cHhpli8.hpli.hpl.hp.com
cK12500
cZ+02:00
e
s 00012/00008/00300
d D 1.49 00/01/31 16:29:28 lm 50 49
c Updates for BitKeeper.
cC
cHlm.bitmover.com
cK07677
cZ-08:00
e
s 00001/00001/00307
d D 1.48 99/09/02 10:38:42 lm 49 48
c MP stuff
cC
cHwork.bitmover.com
cK47824
cZ-07:00
e
s 00001/00001/00307
d D 1.47 99/03/20 23:38:34 lm 48 47
c -ansi as part of Wall.
cK49051
cZ-08:00
e
s 00005/00001/00303
d D 1.46 98/07/31 12:47:42 lm 47 46
c Wall target.
cK48479
e
s 00010/00003/00294
d D 1.45 98/07/21 18:41:14 lm 46 45
c An attempt to make things work on other OS's.
cK41968
e
s 00001/00001/00296
d D 1.44 98/06/29 22:36:52 lm 45 44
c Compile with -Wall.
cHlm.bitmover.com
cK23959
e
s 00001/00001/00296
d D 1.43 98/06/26 17:34:48 staelin 44 43
c remove duplicantte entry for loop_o.c
cHbitmover
cK23482
e
s 00005/00005/00292
d D 1.42 98/05/24 20:01:00 lmcvoy 43 42
c SCCS stuff that Carl forgot.
cHwork
cK24307
cZ-07:00
e
s 00045/00008/00252
d D 1.41 98/05/07 15:48:20 staelin 42 41
c - added "install" target
c - minor tweaks to dependencies
c - added loop_o to EXES
cHhpisc8.lempel
cK29735
cZ-00:00
e
s 00004/00005/00256
d D 1.40 98/03/30 01:02:28 lm 41 40
c SCCS
cHwork.home
cK53642
e
s 00008/00004/00253
d D 1.39 97/12/01 15:48:31 lm 40 39
c some carl stuff I think.
cK57046
cZ-08:00
e
s 00005/00018/00252
d D 1.38 97/10/25 10:53:20 lm 39 38
c Carl/s new mhz.c
cK42773
e
s 00010/00009/00260
d D 1.37 97/10/24 13:49:37 lm 38 37
c lib_unix
cK20067
e
s 00025/00018/00244
d D 1.36 97/10/19 23:47:56 lm 37 36
c added this, removed that.
cK02685
e
s 00001/00001/00261
d D 1.35 97/06/24 00:03:26 lm 36 35
c Carl's stuff.
cK47402
e
s 00001/00001/00261
d D 1.34 97/06/23 23:29:25 lm 35 34
c *** empty log message ***
cK45874
e
s 00009/00008/00253
d D 1.33 97/06/23 23:27:09 lm 34 33
c carl's diffs.
cK46697
e
s 00004/00002/00257
d D 1.32 97/06/19 13:51:14 lm 33 32
c *** empty log message ***
cK43276
e
s 00003/00000/00256
d D 1.31 97/06/16 19:05:50 lm 32 31
c lint
cK38265
e
s 00005/00017/00251
d D 1.30 97/06/15 23:12:58 lm 31 30
c compiler script
cK29051
e
s 00006/00003/00262
d D 1.29 97/06/15 22:38:58 lm 30 29
c lint
cK46536
e
s 00017/00014/00248
d D 1.28 97/06/15 19:59:22 lm 29 28
c *** empty log message ***
cK46645
e
s 00039/00037/00223
d D 1.27 97/06/13 20:39:50 lm 28 27
c lint
cK34607
e
s 00002/00002/00258
d D 1.26 97/06/13 20:28:08 lm 27 26
c *** empty log message ***
cK01755
e
s 00011/00005/00249
d D 1.25 97/06/12 21:30:06 lm 26 25
c new bench.h macros.
cK01630
e
s 00011/00008/00243
d D 1.24 97/05/27 16:03:35 lm 25 24
c who knows.
cK47054
cZ-07:00
e
s 00012/00008/00239
d D 1.23 97/02/12 19:29:07 lm 24 23
c put lmdd back, add http stuff.
cK42115
e
s 00005/00023/00242
d D 1.22 96/12/16 12:33:02 lm 23 22
c http
cK33008
e
s 00001/00001/00264
d D 1.21 96/11/21 17:48:04 lm 22 21
c ar flags.
cK12086
e
s 00013/00013/00252
d D 1.20 96/11/13 16:09:37 lm 21 20
c add select, clean up the makefile a bit.
cK12200
e
s 00115/00092/00150
d D 1.19 96/11/11 03:36:51 lm 20 19
c Auto adjusting changes.
cK07473
cZ-08:00
e
s 00051/00027/00191
d D 1.18 96/05/22 00:35:26 lm 19 18
c unix measurements.
cK53163
e
s 00004/00000/00214
d D 1.17 96/05/21 23:15:13 lm 18 17
c bsdi.
cK53680
cZ-07:00
e
s 00003/00003/00211
d D 1.16 95/11/07 17:40:53 lm 17 16
c *** empty log message ***
cK49232
cZ-08:00
e
s 00001/00001/00213
d D 1.15 95/10/25 21:03:18 lm 16 15
c hpux.
cK51978
e
s 00006/00006/00208
d D 1.14 95/10/25 18:03:42 lm 15 14
c bsd.
cK50499
e
s 00006/00002/00208
d D 1.13 95/08/30 20:41:53 lm 14 13
c *** empty log message ***
cK49227
e
s 00012/00008/00198
d D 1.12 95/08/22 15:40:15 lm 13 12
c various stuff.
cK40421
cZ-07:00
e
s 00004/00004/00202
d D 1.11 95/03/10 18:26:21 lm 12 11
c Make it so that it does the long compiling stuff last.
cK30073
e
s 00008/00002/00198
d D 1.10 95/02/14 10:59:10 lm 11 10
c IRIX mhz && lt_pagefault fix for Linux.
cK30014
e
s 00001/00001/00199
d D 1.9 94/12/05 15:24:55 lm 10 9
c $(MAKE)
cK17487
e
s 00005/00002/00195
d D 1.8 94/11/30 13:40:51 lm 9 8
c mhz. irix
cK17498
e
s 00005/00002/00192
d D 1.7 94/11/29 16:21:05 lm 8 7
c lat_sig.c
cK10303
e
s 00001/00001/00193
d D 1.6 94/11/29 11:52:20 lm 7 6
c changes from Alain Durand for NetBSD
cK01723
e
s 00058/00035/00136
d D 1.5 94/11/25 16:42:09 lm 6 5
c added config support.
cK01280
e
s 00000/00001/00171
d D 1.4 94/11/23 18:08:09 lm 5 4
c *** empty log message ***
cK35634
e
s 00001/00000/00171
d D 1.3 94/11/20 17:08:00 lm 4 3
c sunos
cK40675
e
s 00016/00006/00155
d D 1.2 94/11/20 17:03:27 lm 3 2
c *** empty log message ***
cK35634
e
s 00161/00000/00000
d D 1.1 94/11/18 00:55:14 lm 2 1
c Initial revision
cK11311
e
s 00000/00000/00000
d D 1.0 94/11/18 00:55:13 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK37692
cPsrc/Makefile
cRbce1823a10fe7d49
cV4
cX0x21
cZ-08:00
e
u
U
f e 0
f x 0x21
t
lmbench src.
T
I 2
D 6
#
E 6
D 42
# $Id$
E 42
I 42
D 43
# $Id: Makefile,v 1.39 1997/12/01 23:48:31 lm Exp $
E 43
I 43
# $Id$
E 43
E 42
I 6

# Make targets:
E 6
#
I 6
# lmbench	[default] builds the benchmark suite for the current os/arch
# results	builds, configures run parameters, and runs the benchmark
# rerun		reruns the benchmark using the same parameters as last time
I 73
# scaling	reruns the benchmark using same parameters as last time,
#		except it asks what scaling value to use
E 73
I 61
# hardware	reruns the hardware benchmarks using the same parameters
# os		reruns the OS benchmarks using the same parameters
E 61
# clean		cleans out sources and run configuration
# clobber	clean and removes the bin directories
# shar		obsolete, use cd .. && make shar
# depend	builds make dependencies (needs gcc)
#
# This is largely self configuring.  Most stuff is pretty portable.  You
D 39
# may have problems with the mhz program.  It needs a C compiler smart
# enough to use "register" when running in unoptimized mode.  gcc does
# this.  cc may not.  Look at the output of mhz and see if it is close
# (within a few percent).  If not, try a different compiler and send me
# mail with the info.
E 39
I 39
# may have problems with the mhz program.  
E 39
#
D 61
# OS config.  If you aren't one of the known OS's (see ../scripts/os)
# then you need to make a target in this makefile with the flags that
# you need.  First fix os to spit out your os and then create a target
# here.  Please mail me that info so I can update the makefile.
#
# If you don't have gcc, try make CC=cc and see if that works.
E 61
E 6

# I finally know why Larry Wall's Makefile says "Grrrr".
SHELL=/bin/sh

D 20
CC = gcc
E 20
I 20
D 31
CC = gcc 
E 31
I 31
CC = `../scripts/compiler`
I 52
MAKE = `../scripts/make`
E 52
E 31
AR = ar
D 22
ARCREATE = cqs
E 22
I 22
ARCREATE = cr
I 42
BASE=/usr/local		# base of installation location
E 42
E 22
E 20
O= ../bin/unknown
I 42
D= ../doc
E 42
I 18
TRUE=/bin/true
E 18
OS=`../scripts/os`
I 29
TARGET=`../scripts/target`
E 29
BINDIR=../bin/$(OS)
I 29
CONFIG=../bin/$(OS)/`../scripts/config`
I 42
D 50
RCCS=../rccs
E 50
I 50
UTILS=../scripts/target ../scripts/os ../scripts/gnu-os ../scripts/compiler \
	../scripts/info ../scripts/info-template ../scripts/version \
	../scripts/config ../scripts/config-run ../scripts/results \
D 52
	../scripts/lmbench
E 52
I 52
D 53
	../scripts/lmbench ../scripts/make
E 53
I 53
	../scripts/lmbench ../scripts/make ../scripts/build
E 53
E 52
E 50
INSTALL=cp
E 42
I 34
D 35
RCCS=../scripts/rccs
E 35
I 35
D 41
RCCS=../rccs
E 41
E 35
E 34
E 29
RESULTS=Results/$(OS)
SAMPLES=lmbench/Results/aix/rs6000 lmbench/Results/hpux/snake \
	lmbench/Results/irix/indigo2 lmbench/Results/linux/pentium \
	lmbench/Results/osf1/alpha lmbench/Results/solaris/ss20* 

D 53
SYS5=
D 33
CFLAGS = -O $(SYS5)
E 33
I 33
D 45
CFLAGS = -O $(SYS5) $(CF)
E 45
I 45
D 47
CFLAGS = -Wall -O $(SYS5) $(CF)
E 47
I 47
CFLAGS = -O $(SYS5) $(CF)
E 47
E 45
E 33

E 53
COMPILE=$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)

I 42
D 65
INCS =	bench.h lib_tcp.h lib_udp.h stats.h timing.h
E 65
I 65
INCS =	bench.h lib_mem.h lib_tcp.h lib_udp.h stats.h timing.h
E 65

E 42
I 3
D 37
SRCS =  bench.h bw_file_rd.c bw_mem_cp.c bw_mem_rd.c bw_mem_wr.c	\
	bw_mmap_rd.c bw_pipe.c bw_tcp.c hello.c lat_connect.c lat_ctx.c	\
E 37
I 37
D 56
SRCS =  bench.h bw_file_rd.c bw_mmap_rd.c 				\
	bw_pipe.c bw_tcp.c hello.c lat_connect.c lat_ctx.c		\
E 37
	lat_fs.c lat_mem_rd.c lat_mmap.c lat_pagefault.c lat_pipe.c	\
	lat_proc.c lat_rpc.c lat_syscall.c lat_tcp.c lat_udp.c		\
D 8
	lib_tcp.c lib_udp.c lmdd.c mhz.c timing.c
E 8
I 8
D 9
	lib_tcp.c lib_udp.c lmdd.c mhz.c timing.c lat_sig.c
E 9
I 9
D 14
	lib_tcp.c lib_udp.c lmdd.c mhz.c timing.c lat_sig.c mhz.irix
E 14
I 14
D 20
	lib_tcp.c lib_udp.c lmdd.c mhz.c timing.c lat_sig.c mhz.irix	\
E 20
I 20
D 25
	lib_tcp.c lib_udp.c mhz.c timing.c lat_sig.c mhz.irix	\
E 25
I 25
D 39
	lib_tcp.c lib_udp.c mhz.c lib_timing.c lat_sig.c mhz.irix	\
E 39
I 39
	lib_tcp.c lib_udp.c mhz.c lib_timing.c lat_sig.c 		\
E 39
E 25
E 20
D 19
	memsize.c
E 19
I 19
D 24
	memsize.c bw_unix.c lat_unix.c
E 24
I 24
D 26
	memsize.c bw_unix.c lat_unix.c lmdd.c
E 26
I 26
D 28
	memsize.c bw_unix.c lat_unix.c lmdd.c timing_o.c enough.c
E 28
I 28
D 42
	memsize.c bw_unix.c lat_unix.c lmdd.c timing_o.c enough.c	\
D 30
	timing.h stats.h lib_tcp.h lib_udp.h lat_select.c http.c	\
D 29
	rhttp.c
E 29
I 29
	rhttp.c msleep.c loop_o.c
E 30
I 30
D 37
	timing.h stats.h lib_tcp.h lib_udp.h lat_select.c \
	msleep.c loop_o.c
E 37
I 37
	timing.h stats.h lib_tcp.h lib_udp.h lat_select.c 		\
E 42
I 42
	memsize.c bw_unix.c lat_unix.c lmdd.c loop_o.c timing_o.c	\
	timing.h stats.h lib_tcp.h lib_udp.h  enough.c lat_select.c	\
E 42
D 44
	msleep.c loop_o.c bw_mem.c lat_fifo.c lmhttp.c lat_http.c	\
E 44
I 44
	msleep.c bw_mem.c lat_fifo.c lmhttp.c lat_http.c	\
E 44
D 38
	accept.c disk.c
E 38
I 38
D 40
	disk.c flushdisk.c lat_unix_connect.c lib_unix.c
E 40
I 40
D 50
	disk.c flushdisk.c lat_unix_connect.c lib_unix.c lib_stats.c
E 50
I 50
D 52
	disk.c flushdisk.c lat_unix_connect.c lib_unix.c lib_stats.c \
	lib_unix.h names.h version.h
E 52
I 52
	disk.c flushdisk.c lat_unix_connect.c lat_fcntl.c \
I 54
	line.c tlb.c cache.c \
E 54
	lib_unix.c lib_stats.c lib_unix.h names.h version.h
E 56
I 56
D 57
SRCS =  bw_file_rd.c bw_mem.c bw_mmap_rd.c bw_pipe.c bw_tcp.c bw_unix.c	\
E 57
I 57
D 58
SRCS =  bw_file_rd.c bw_mem.c bw_mmap_rd.c bw_pipe.c bw_tcp.c bw_udp.c bw_unix.c	\
E 58
I 58
SRCS =  bw_file_rd.c bw_mem.c bw_mmap_rd.c bw_pipe.c bw_tcp.c bw_udp.c	\
D 66
	bw_unix.c	\
E 66
I 66
D 72
	bw_unix.c bw_shm.c	\
E 72
I 72
D 74
	bw_unix.c \
E 74
I 74
D 76
	bw_unix.c bw_shm.c\
E 76
I 76
D 77
	bw_unix.c bw_shm.c						\
E 77
I 77
	bw_unix.c							\
E 77
E 76
E 74
E 72
E 66
E 58
E 57
	cache.c clock.c disk.c enough.c flushdisk.c getopt.c hello.c	\
	lat_connect.c lat_ctx.c	lat_fcntl.c lat_fifo.c lat_fs.c 	\
D 58
	lat_mem_rd.c lat_mmap.c lat_pagefault.c lat_pipe.c lat_proc.c	\
	lat_rpc.c lat_select.c lat_sig.c lat_syscall.c lat_tcp.c	\
	lat_udp.c lat_unix.c lat_unix_connect.c				\
E 58
I 58
	lat_mem_rd.c lat_mmap.c lat_ops.c lat_pagefault.c lat_pipe.c 	\
	lat_proc.c lat_rpc.c lat_select.c lat_sig.c lat_syscall.c	\
D 66
	lat_tcp.c lat_udp.c lat_unix.c lat_unix_connect.c		\
E 66
I 66
	lat_tcp.c lat_udp.c lat_unix.c lat_unix_connect.c lat_sem.c	\
I 75
D 76
	lat_usleep.c lat_itimer.c					\
E 76
I 76
	lat_usleep.c 							\
E 76
E 75
E 66
E 58
D 65
	lib_stats.c lib_tcp.c lib_timing.c lib_udp.c lib_unix.c		\
D 62
	line.c lmdd.c lmhttp.c loads.c loop_o.c memsize.c mhz.c 	\
E 62
I 62
D 63
	line.c lmdd.c lmhttp.c par_mem.c loop_o.c memsize.c mhz.c 	\
E 63
I 63
	line.c lmdd.c lmhttp.c par_mem.c par_ops.c loop_o.c memsize.c mhz.c 	\
E 63
E 62
D 59
	msleep.c rhttp.c seek.c timing_o.c tlb.c			\
E 59
I 59
	msleep.c rhttp.c seek.c timing_o.c tlb.c stream.c		\
E 65
I 65
D 74
	lib_mem.c lib_stats.c lib_tcp.c lib_timing.c lib_udp.c 		\
	lib_unix.c		\
E 74
I 74
	lib_debug.c lib_mem.c lib_stats.c lib_tcp.c lib_timing.c 	\
D 76
	lib_udp.c lib_unix.c		\
E 76
I 76
	lib_udp.c lib_unix.c						\
E 76
E 74
	line.c lmdd.c lmhttp.c par_mem.c par_ops.c loop_o.c memsize.c 	\
	mhz.c msleep.c rhttp.c seek.c timing_o.c tlb.c stream.c		\
E 65
E 59
D 74
	bench.h lib_tcp.h lib_udp.h lib_unix.h names.h stats.h		\
	timing.h version.h
E 74
I 74
	bench.h lib_debug.h lib_tcp.h lib_udp.h lib_unix.h names.h 	\
	stats.h timing.h version.h
E 74
E 56
E 52
E 50
E 40
E 38
E 37
E 30
E 29
E 28
E 26
E 24
E 19
E 14
E 9
E 8

E 3
D 37
EXES = 	$O/bw_file_rd $O/bw_mem_cp $O/bw_mem_rd $O/bw_mem_wr		\
D 12
	$O/bw_mmap_rd $O/bw_pipe $O/bw_tcp $O/hello $O/lmdd $O/lat_ctx	\
	$O/lat_mem_rd $O/lat_pipe $O/lat_rpc $O/lat_syscall $O/lat_tcp	\
	$O/lat_udp $O/lat_mmap $O/mhz $O/lat_proc $O/lat_pagefault \
D 8
	$O/lat_connect $O/lat_fs
E 8
I 8
	$O/lat_connect $O/lat_fs $O/lat_sig
E 12
I 12
D 20
	$O/bw_mmap_rd $O/bw_pipe $O/bw_tcp $O/hello $O/lmdd 		\
E 20
I 20
	$O/bw_mmap_rd $O/bw_pipe $O/bw_tcp $O/hello  			\
E 37
I 37
D 58
EXES =	$O/bw_file_rd $O/bw_mmap_rd $O/bw_pipe $O/bw_tcp $O/hello	\
E 58
I 58
EXES =	$O/bw_file_rd $O/bw_mem $O/bw_mmap_rd $O/bw_pipe $O/bw_tcp 	\
D 66
	$O/bw_udp $O/bw_unix $O/hello	\
E 66
I 66
D 67
	$O/bw_udp $O/bw_unix $O/bw_shm $O/hello	\
E 67
I 67
D 69
	$O/bw_udp $O/bw_unix $O/hello	\
E 69
I 69
D 76
	$O/bw_unix $O/hello	\
E 76
I 76
	$O/bw_unix $O/hello						\
E 76
E 69
E 67
E 66
E 58
E 37
E 20
D 21
	$O/lat_pipe $O/lat_rpc $O/lat_syscall $O/lat_tcp		\
E 21
I 21
D 29
	$O/lat_select $O/lat_pipe $O/lat_rpc $O/lat_syscall $O/lat_tcp		\
E 29
I 29
	$O/lat_select $O/lat_pipe $O/lat_rpc $O/lat_syscall $O/lat_tcp	\
E 29
E 21
D 37
	$O/lat_udp $O/lat_mmap $O/mhz $O/lat_proc $O/lat_pagefault 	\
D 13
	$O/lat_connect $O/lat_fs $O/lat_sig $O/lat_mem_rd $O/lat_ctx
E 13
I 13
	$O/lat_connect $O/lat_fs $O/lat_sig $O/lat_mem_rd 	\
D 14
	$O/lat_ctx
E 14
I 14
D 19
	$O/lat_ctx $O/memsize
E 19
I 19
D 23
	$O/lat_ctx $O/memsize $O/lat_unix $O/bw_unix
E 23
I 23
D 24
	$O/lat_ctx $O/memsize $O/lat_unix $O/bw_unix $O/http $O/http_srv
E 24
I 24
D 30
	$O/lat_ctx $O/memsize $O/lat_unix $O/bw_unix $O/http $O/rhttp \
E 30
I 30
	$O/lat_ctx $O/memsize $O/lat_unix $O/bw_unix \
E 30
D 25
	$O/lmhttp $O/lmdd
E 25
I 25
D 26
	$O/lmdd
E 26
I 26
D 29
	$O/lmdd $O/timing_o $O/enough
E 29
I 29
	$O/lmdd $O/timing_o $O/enough $O/msleep $O/loop_o
E 37
I 37
	$O/lat_udp $O/lat_mmap $O/mhz $O/lat_proc $O/lat_pagefault	\
	$O/lat_connect $O/lat_fs $O/lat_sig $O/lat_mem_rd $O/lat_ctx	\
I 66
D 75
	$O/lat_sem							\
E 75
I 75
D 76
	$O/lat_sem $O/lat_usleep $O/lat_itimer				\
E 75
E 66
D 58
	$O/memsize $O/lat_unix $O/bw_unix $O/lmdd $O/timing_o $O/enough	\
	$O/msleep $O/loop_o $O/bw_mem $O/lat_fifo $O/lmhttp $O/lat_http	\
E 58
I 58
	$O/memsize $O/lat_unix $O/lmdd $O/timing_o $O/enough	\
	$O/msleep $O/loop_o $O/lat_fifo $O/lmhttp $O/lat_http	\
E 76
I 76
D 78
	$O/lat_sem $O/lat_usleep					\
E 78
I 78
	$O/lat_sem 							\
E 78
	$O/memsize $O/lat_unix $O/lmdd $O/timing_o $O/enough		\
	$O/msleep $O/loop_o $O/lat_fifo $O/lmhttp $O/lat_http		\
E 76
E 58
D 38
	$O/accept $O/disk
E 38
I 38
D 40
	$O/disk $O/lat_unix_connect
E 40
I 40
D 52
	$O/disk $O/lat_unix_connect $O/flushdisk
E 52
I 52
D 54
	$O/lat_fcntl $O/disk $O/lat_unix_connect $O/flushdisk
E 54
I 54
	$O/lat_fcntl $O/disk $O/lat_unix_connect $O/flushdisk		\
D 56
	$O/line $O/tlb $O/cache
E 56
I 56
D 57
	$O/line $O/tlb $O/cache $O/loads
E 57
I 57
D 58
	$O/line $O/tlb $O/cache $O/loads $O/bw_udp
E 58
I 58
D 59
	$O/lat_ops $O/line $O/tlb $O/cache $O/loads 
E 59
I 59
D 62
	$O/lat_ops $O/line $O/tlb $O/cache $O/loads $O/stream
E 62
I 62
D 63
	$O/lat_ops $O/line $O/tlb $O/cache $O/par_mem $O/stream
E 63
I 63
D 66
	$O/lat_ops $O/line $O/tlb $O/cache $O/par_mem $O/par_ops $O/stream
E 66
I 66
D 67
	$O/lat_ops $O/line $O/tlb $O/cache $O/par_mem $O/par_ops $O/stream $O/par_list
E 67
I 67
D 78
	$O/lat_ops $O/line $O/tlb $O/cache $O/par_mem $O/par_ops 	\
D 74
	$O/stream
E 74
I 74
D 77
	$O/stream $O/lat_dram_page $O/bw_shm
E 77
I 77
	$O/stream $O/lat_dram_page
E 78
I 78
	$O/lat_ops $O/line $O/tlb $O/par_mem $O/par_ops 		\
	$O/stream 
OPT_EXES=$O/lat_dram_page $O/lat_usleep $O/cache 
E 78
E 77
E 74
E 67
E 66
E 63
E 62
E 59
E 58
E 57
E 56
E 54
E 52
E 40
E 38
E 37
E 29
E 26
E 25
E 24
E 23
E 19
E 14
E 13
E 12
E 8

I 42
MAN1 =	lmdd.1 $D/bargraph.1 $D/graph.1 $D/pgraph.1 $D/rccs.1

MAN3 =	$D/lmbench.3 $D/reporting.3 $D/results.3 $D/timing.3

D 66
MAN8 =	$D/bw_file_rd.8 $D/bw_mem_cp.8 $D/bw_mem_rd.8 $D/bw_mem_wr.8	\
	$D/bw_mmap_rd.8 $D/bw_pipe.8 $D/bw_tcp.8 $D/lat_connect.8	\
E 66
I 66
MAN8 =	$D/bw_file_rd.8 $D/bw_mem.8 $D/bw_mmap_rd.8 \
	$D/bw_pipe.8 $D/bw_tcp.8 $D/bw_unix.8 $D/lat_connect.8	\
E 66
	$D/lat_ctx.8 $D/lat_fs.8 $D/lat_mem_rd.8 $D/lat_mmap.8		\
	$D/lat_pagefault.8 $D/lat_pipe.8 $D/lat_proc.8 $D/lat_rpc.8 	\
	$D/lat_syscall.8 $D/lat_tcp.8 $D/lat_udp.8 $D/lmbench.8 	\
D 66
	$D/lmdd.8 $D/mhz.8 
E 66
I 66
	$D/lat_select.8 $D/lat_unix.8 $D/lat_unix_connect.8		\
	$D/lat_fifo.8 $D/lat_fcntl.8 $D/lat_http.8 $D/lat_sig.8		\
	$D/lat_ops.8 $D/par_ops.8 $D/par_mem.8				\
	$D/lmdd.8 $D/mhz.8 $D/cache.8 $D/tlb.8 $D/line.8
E 66
D 51

E 42
I 20
D 25
LIBOBJS= $O/lib_tcp.o $O/lib_udp.o $O/timing.o
E 25
I 25
D 38
LIBOBJS= $O/lib_tcp.o $O/lib_udp.o $O/lib_timing.o
E 38
I 38
D 40
LIBOBJS= $O/lib_tcp.o $O/lib_udp.o $O/lib_unix.o $O/lib_timing.o
E 40
I 40
LIBOBJS= $O/lib_tcp.o $O/lib_udp.o $O/lib_unix.o $O/lib_timing.o $O/lib_stats.o
E 51
I 51
LIBOBJS= $O/lib_tcp.o $O/lib_udp.o $O/lib_unix.o $O/lib_timing.o 	\
D 65
	$O/lib_stats.o $O/getopt.o
E 65
I 65
D 74
	$O/lib_mem.o $O/lib_stats.o $O/getopt.o
E 74
I 74
	$O/lib_mem.o $O/lib_stats.o $O/lib_debug.o $O/getopt.o
E 74
E 65
E 51
E 40
E 38
E 25

E 20
D 50
lmbench:
E 50
I 50
lmbench: $(UTILS)
E 50
D 29
	@echo Building for $(OS)
E 29
I 29
D 53
	@echo Building for $(TARGET)
E 29
	@if [ ! -d $(BINDIR) ]; then mkdir -p $(BINDIR); fi
D 29
	$(MAKE) CC=$(CC) O=$(BINDIR) $(OS)
E 29
I 29
D 34
	$(MAKE) CC=$(CC) O=$(BINDIR) $(TARGET)
E 34
I 34
	$(MAKE) CC="$(CC)" O=$(BINDIR) $(TARGET)
E 53
I 53
D 68
	@env CFLAGS=-O ../scripts/build all
E 68
I 68
	@env CFLAGS=-O MAKE="$(MAKE)" MAKEFLAGS="$(MAKEFLAGS)" ../scripts/build all
I 78
	-@env CFLAGS=-O MAKE="$(MAKE)" MAKEFLAGS="-k $(MAKEFLAGS)" ../scripts/build opt
E 78
E 68
E 53
E 34
E 29

D 6
results:
E 6
I 6
D 50
results: 
E 50
I 50
D 53
results: $(UTILS)
E 50
E 6
D 29
	@$(MAKE) lmbench CC=$(CC) O=$(BINDIR) $(OS)
D 6
	@if [ ! -d ../$(RESULTS) ]; then mkdir -p ../$(RESULTS); fi
	@BASE=../$(RESULTS)/`uname -n`; OUT=$$BASE; EXT=0; \
	while [ -f $$OUT ]; \
	do	EXT=`expr $$EXT + 1`; \
		OUT=$$BASE.$$EXT; \
	done; \
	echo Results going to $$OUT; \
	cd $(BINDIR) && ../../scripts/lmbench 2>../$$OUT
	
E 6
I 6
	@../scripts/config-run $(BINDIR)/CONFIG
E 29
I 29
	@$(MAKE) lmbench CC=$(CC) O=$(BINDIR) $(TARGET)
E 53
I 53
results: lmbench
E 53
	@../scripts/config-run
E 29
D 61
	@../scripts/results
E 61
I 61
	@BENCHMARK_HARDWARE=YES BENCHMARK_OS=YES ../scripts/results
E 61

D 50
rerun: 
E 50
I 50
D 53
rerun: $(UTILS)
E 53
I 53
rerun: lmbench
E 53
E 50
D 29
	@if [ ! -f $(BINDIR)/CONFIG ]; \
	then	../scripts/config-run $(BINDIR)/CONFIG; \
	fi
E 29
I 29
	@if [ ! -f $(CONFIG) ]; then ../scripts/config-run; fi
I 73
	@../scripts/results

scaling: lmbench
	@if [ ! -f $(CONFIG) ]; then ../scripts/config-run; \
	 else ../scripts/config-scaling $(CONFIG); fi
E 73
E 29
D 61
	@../scripts/results
E 61
I 61
D 64
	@BENCHMARK_HARDWARE=YES BENCHMARK_OS=YES ../scripts/results
E 64
I 64
	@../scripts/results
E 64

hardware: lmbench
	@if [ ! -f $(CONFIG) ]; then ../scripts/config-run; fi
	@BENCHMARK_HARDWARE=YES BENCHMARK_OS=NO  ../scripts/results

os: lmbench
	@if [ ! -f $(CONFIG) ]; then ../scripts/config-run; fi
	@BENCHMARK_HARDWARE=NO  BENCHMARK_OS=YES ../scripts/results
E 61

I 42
install: lmbench
D 53
	$(MAKE) O=$(BINDIR) install-target
E 53
I 53
D 68
	@env CFLAGS=-O ../scripts/build install-target
E 68
I 68
	@env CFLAGS=-O MAKE="$(MAKE)"  MAKEFLAGS="$(MAKEFLAGS)" ../scripts/build install-target
E 68
E 53

install-target:
	if [ ! -d $(BASE) ]; then mkdir $(BASE); fi
	if [ ! -d $(BASE)/bin ]; then mkdir $(BASE)/bin; fi
	if [ ! -d $(BASE)/include ]; then mkdir $(BASE)/include; fi
	if [ ! -d $(BASE)/lib ]; then mkdir $(BASE)/lib; fi
	if [ ! -d $(BASE)/man ]; then mkdir $(BASE)/man; fi
	if [ ! -d $(BASE)/man/man1 ]; then mkdir $(BASE)/man/man1; fi
	if [ ! -d $(BASE)/man/man3 ]; then mkdir $(BASE)/man/man3; fi
	if [ ! -d $(BASE)/man/man8 ]; then mkdir $(BASE)/man/man8; fi
	cp $(EXES) $(BASE)/bin
	cp $(INCS) $(BASE)/include
	cp $O/lmbench.a $(BASE)/lib/libmbench.a
	cp $(MAN1) $(BASE)/man/man1
	cp $(MAN3) $(BASE)/man/man3
	cp $(MAN8) $(BASE)/man/man8


E 42
E 6
# No special handling for all these
D 20
all linux sunos: $(EXES)
E 20
I 20
D 31
all bsdi linux sunos: $(EXES)
E 31
I 31
D 36
all irix osf1 aix bsdi linux sunos: $(EXES)
E 36
I 36
D 52
all irix osf1 aix bsdi linux ultrix sunos unknown: $(EXES)
E 52
I 52
D 53
all irix osf1 bsd bsdi linux ultrix sunos unknown: $(EXES)
E 52
E 36
E 31
E 20

# System specific stuff.
solaris:
D 31
	$(MAKE) O=$O CC=cc LDLIBS="-lnsl -lsocket" SYS5=-DSYS5 all
E 31
I 31
D 34
	$(MAKE) O=$O LDLIBS="-lnsl -lsocket" SYS5=-DSYS5 all
E 34
I 34
D 46
	$(MAKE) CC="$(CC)" O=$O LDLIBS="-lnsl -lsocket" SYS5=-DSYS5 all
E 46
I 46
	@if [ ! -d $(BINDIR) ]; then mkdir -p $(BINDIR); fi
D 52
	$(MAKE) CC="$(CC)" O=$(BINDIR) LDLIBS="-lnsl -lsocket" SYS5=-DSYS5 all
E 52
I 52
	$(MAKE) CC="$(CC)" O=$(BINDIR) CF="-DSOLARIS" LDLIBS="-lnsl -lsocket" SYS5=-DSYS5 all

aix:
	@if [ ! -d $(BINDIR) ]; then mkdir -p $(BINDIR); fi
	$(MAKE) CC="$(CC)" CF="-Dvalloc=malloc" O=$(BINDIR) all
E 52
E 46
E 34
E 31

D 31
# HPUX needs gcc; their C compiler screws up mhz.c.
E 31
hpux:
I 32
	@echo ======================================
	@echo If you have gcc, try "make -e CC=gcc"
	@echo ======================================
E 32
D 13
	$(MAKE) CC=$(CC) O=$O CFLAGS="$(CFLAGS)" all
E 13
I 13
D 16
	$(MAKE) CC="$(CC)" O=$O CFLAGS="$(CFLAGS)" all
E 16
I 16
D 31
	$(MAKE) CC="$(CC)" O=$O CFLAGS="$(CFLAGS) -Dvalloc=malloc" all
E 31
I 31
D 34
	$(MAKE) O=$O CFLAGS="$(CFLAGS) -Dvalloc=malloc" all
E 34
I 34
D 46
	$(MAKE) CC="$(CC)" O=$O CFLAGS="$(CFLAGS) -Dvalloc=malloc" all
E 46
I 46
	@if [ ! -d $(BINDIR) ]; then mkdir -p $(BINDIR); fi
D 52
	$(MAKE) CC="$(CC)" O=$(BINDIR) CFLAGS="$(CFLAGS) -Dvalloc=malloc" all
E 46
E 34
E 31
E 16
E 13

D 20
# Really specific to the alpha, not osf.
osf1:
E 20
I 20
D 25
irix osf1 aix:
E 25
I 25
D 31
irix:
D 27
	$(MAKE) O=$O CC=cc CFLAGS="$(CFLAGS) -o32" all
E 27
I 27
	$(MAKE) O=$O CC=cc CFLAGS="$(CFLAGS) $(SGI)" all
E 27

osf1 aix:
E 25
E 20
	$(MAKE) O=$O CC=cc CFLAGS="$(CFLAGS)" all

E 31
D 20
irix:
D 13
	$(MAKE) O=$O CC=$(CC) CFLAGS="$(CFLAGS) -Dvfork=fork" all
E 13
I 13
D 17
	$(MAKE) O=$O CC=cc CFLAGS="$(CFLAGS) -32 -Dvfork=fork" all
E 17
I 17
	$(MAKE) O=$O CC=cc CFLAGS="$(CFLAGS) -32" all
E 17
E 13

aix:
D 17
	$(MAKE) O=$O CC=cc CFLAGS="$(CFLAGS) -Dvfork=fork" all
E 17
I 17
	$(MAKE) O=$O CC=cc CFLAGS="$(CFLAGS)" all
E 17

E 20
bsd:
D 7
	$(MAKE) O=$O CC=$(CC) CFLAGS="$CFLAGS -Duint='unsigned int'" all
E 7
I 7
D 17
	$(MAKE) O=$O CC=$(CC) CFLAGS="$(CFLAGS) -DBSD -Duint='unsigned int'" all
E 17
I 17
D 31
	$(MAKE) O=$O CC=$(CC) CFLAGS="$(CFLAGS) -Duint='unsigned int'" all
E 31
I 31
D 34
	$(MAKE) O=$O CFLAGS="$(CFLAGS) -Duint='unsigned int'" all
E 34
I 34
D 46
	$(MAKE) CC="$(CC)" O=$O CFLAGS="$(CFLAGS) -Duint='unsigned int'" all
E 46
I 46
	@if [ ! -d $(BINDIR) ]; then mkdir -p $(BINDIR); fi
D 49
	$(MAKE) CC="$(CC)" CFLAGS="$(CFLAGS) -Duint='unsigned int'" all
E 49
I 49
	$(MAKE) CC="$(CC)" CFLAGS="$(CFLAGS)" O=$(BINDIR) all
E 52
I 52
	$(MAKE) CC="$(CC)" CF="-Dvalloc=malloc" O=$(BINDIR) all
E 53
I 53
all: $(EXES)
I 78
opt: $(OPT_EXES)
E 78
E 53
E 52
E 49
I 47

Wall:
D 53
	@if [ ! -d $(BINDIR) ]; then mkdir -p $(BINDIR); fi
D 48
	$(MAKE) CC="$(CC)" CF=-Wall O=$(BINDIR) $(TARGET)
E 48
I 48
	$(MAKE) CC="$(CC)" CF="-Wall -ansi" O=$(BINDIR) $(TARGET)
E 53
I 53
D 68
	@env CFLAGS="-Wall -ansi" ../scripts/build all
E 68
I 68
	@env CFLAGS="-Wall -ansi" MAKE="$(MAKE)" MAKEFLAGS="$(MAKEFLAGS)" ../scripts/build all
E 68
E 53
E 48
E 47

debug:
D 53
	@if [ ! -d $(BINDIR) ]; then mkdir -p $(BINDIR); fi
	$(MAKE) CC="$(CC)" CF=-g O=$(BINDIR) $(TARGET)
E 53
I 53
D 68
	@env CFLAGS=-g ../scripts/build all
E 68
I 68
	@env CFLAGS=-g MAKE="$(MAKE)" MAKEFLAGS="$(MAKEFLAGS)" ../scripts/build all
E 68
E 53
E 46
E 34
E 31
E 17
E 7

I 60
bk.ver: ../SCCS/s.ChangeSet
I 70
	rm -f bk.ver
E 70
D 61
	echo `bk prs -hr+ -d'$$if(:SYMBOL:){:SYMBOL: }:UTC:' ../ChangeSet;` \
		> bk.ver
E 61
I 61
	-echo `bk prs -hr+ -d'$$if(:SYMBOL:){:SYMBOL: }:UTC:' ../ChangeSet;` > bk.ver
	touch bk.ver
E 61

D 79
dist:
E 79
I 79
dist: bk.ver
E 79
	@if [ "X`cd ..; bk sfiles -c`" != "X" ]; then \
		echo "modified files!"; \
		false; \
	 fi
	@if [ "X`cd ..; bk pending`" != "X" ]; then \
		echo "pending changes!"; \
		false; \
	 fi
D 61
	rm -rf ../bin/* bk.ver
	cd ..; bk clean
	cd ..; bk get
	cd ..; for d in doc results scripts src; do bk get; done
E 61
I 61
D 71
	cd ..; for d in . doc results scripts src; do \
		(cd $$d; bk clean; bk get -s); \
	done
	rm -rf bk.ver
E 61
	make bk.ver
I 61
	cp -rp .. ../../lmbench-3dist
	rm -rf ../../lmbench-3dist/bin/*
I 68
	rm -rf ../../lmbench-3dist/results/[a-su-z]*
E 71
I 71
	cd ..; \
		SRCDIR=`pwd`; \
		DIR=`basename $${SRCDIR}`; \
D 79
		TODAY=`date '+%Y%m%d'`; \
E 79
I 79
		VERSION=`cat src/bk.ver| awk '{print $$1;}' | sed -e 's/Version-//g'`; \
E 79
		cd ..; \
D 79
		bk clone $${DIR} /tmp/$${DIR}; \
		cd /tmp/$${DIR}; \
E 79
I 79
		bk clone $${DIR} /tmp/lmbench-$${VERSION}; \
		cd /tmp/lmbench-$${VERSION}; \
E 79
		bk sfiles | xargs touch; \
		sleep 5; \
		bk get -s; \
		for d in doc results scripts src; do \
			cd $$d; bk get -s; cd ..; \
		done; \
		bk sfiles -U -g | xargs touch; \
		cd src; \
		make bk.ver; \
		cd /tmp; \
D 79
		tar czf $${SRCDIR}/../$${DIR}-$${TODAY}.tgz $${DIR}; \
		rm -rf /tmp/$${DIR};
E 79
I 79
D 80
		tar czf $${SRCDIR}/../$${DIR}-$${VERSION}.tgz 
E 80
I 80
		tar czf $${SRCDIR}/../lmbench-$${VERSION}.tgz \
E 80
			lmbench-$${VERSION}; \
		rm -rf /tmp/lmbench-$${VERSION};
E 79
E 71
E 68
E 61

E 60
I 18
D 20
bsdi:
	$(MAKE) O=$O CC=$(CC) CFLAGS="$(CFLAGS) " all

E 20
E 18
D 31
Wall:
D 20
	@$(MAKE) clean
	@$(MAKE) CFLAGS=-Wall 
E 20
I 20
	#Too much work for now.
	#@$(MAKE) CFLAGS="-Wall -Wstrict-prototypes"
	@$(MAKE) CFLAGS=-Wall
E 20

E 31
I 3
D 6
$(SRCS):
E 6
I 6
get $(SRCS):
E 6
D 34
	rccs get -s $(SRCS)
E 34
I 34
D 41
	$(RCCS) get -s $(SRCS)
E 41
I 41
D 42
	get -s $(SRCS)
E 42
I 42
D 43
	$(RCCS) get -s $(SRCS)
E 43
I 43
D 53
	get -s $(SRCS)
E 53
I 53
	-get -s $(SRCS)
E 53
E 43
E 42
E 41
E 34

I 30
edit get-e:
D 34
	rccs get -e -s $(SRCS)
E 34
I 34
D 41
	$(RCCS) get -e -s $(SRCS)
E 41
I 41
D 42
	get -e -s $(SRCS)
E 42
I 42
D 43
	$(RCCS) get -e -s $(SRCS)
E 43
I 43
	get -e -s $(SRCS)
E 43
E 42
E 41
E 34

E 30
clean:
I 6
D 20
	/bin/rm -f ../bin/*/CONFIG
E 20
I 20
D 21
	/bin/rm -f ../bin/*/CONFIG ../bin/*/*.o
E 21
I 21
	/bin/rm -f ../bin/*/CONFIG ../bin/*/*.[oa]
E 21
E 20
E 6
D 34
	rccs clean -e -s
E 34
I 34
D 41
	$(RCCS) clean -e -s
E 41
I 41
D 42
	clean 
E 42
I 42
D 43
	$(RCCS) clean -e -s
E 43
I 43
D 50
	clean
E 50
I 50
	-bk clean
E 50
E 43
E 42
E 41
E 34
I 4
D 5
	rccs get -s Makefile	# For SunOS' make that groks only SCCS
E 5
E 4

E 3
clobber:
	/bin/rm -rf ../bin* SHAR
I 3
D 34
	rccs clean -e -s
E 34
I 34
D 41
	$(RCCS) clean -e -s
E 41
I 41
D 42
	clean 
E 42
I 42
D 43
	$(RCCS) clean -e -s
E 43
I 43
D 50
	clean
E 50
I 50
	-bk clean
E 50
E 43
E 42
E 41
E 34
E 3

shar:
	cd ../.. && shar lmbench/Results/Makefile $(SAMPLES) lmbench/scripts/* lmbench/src/Makefile lmbench/src/*.[ch] > lmbench/SHAR

D 50
depend:
E 50
I 50
depend: ../scripts/depend
E 50
	../scripts/depend
I 70

I 72
testmake: $(SRCS) $(UTILS) # used by scripts/make to test gmake
	@true

E 72
.PHONY: lmbench results rerun hardware os install all Wall debug \
	install install-target dist get edit get-e clean clobber \
D 72
	share depend
E 72
I 72
	share depend testmake
E 72
E 70

D 39
# No optimization for these.
D 21
$O/mhz: mhz.c timing.c bench.h
D 9
	$(CC) $(SYS5) -o $O/mhz mhz.c
E 9
I 9
	if [ $O = ../bin/irix ]; \
E 21
I 21
D 25
$O/mhz: mhz.c timing.c bench.h $O/lmbench.a
E 25
I 25
$O/mhz: mhz.c lib_timing.c bench.h $O/lmbench.a
E 25
D 29
	if [ $(OS) = irix ]; \
E 29
I 29
	if [ $(TARGET) = irix ]; \
E 29
E 21
D 13
	then cp mhz.irix $O/mhz; chmod +x $O/mhz; \
E 13
I 13
	then cp mhz.irix $O/mhz; chmod +xw $O/mhz; \
E 13
D 20
	else $(CC) $(SYS5) -o $O/mhz mhz.c; \
E 20
I 20
D 26
	else $(CC) $(SYS5) $(CFLAGS) -o $O/mhz mhz.c $O/lmbench.a; \
E 26
I 26
	else $(CC) $(SYS5) -o $O/mhz mhz.c $O/lmbench.a; \
E 26
E 20
	fi
E 9

D 21
$O/lat_ctx: lat_ctx.c timing.c bench.h
D 11
	$(CC) $(SYS5) -o $O/lat_ctx lat_ctx.c
E 11
I 11
	if [ $O = ../bin/irix ]; 				\
E 21
I 21
D 25
$O/lat_ctx: lat_ctx.c timing.c bench.h $O/lmbench.a
E 25
I 25
D 33
$O/lat_ctx: lat_ctx.c lib_timing.c bench.h $O/lmbench.a
E 33
E 25
	if [ $(OS) = irix ]; 				\
E 21
D 13
	then	$(CC) $(SYS5) -O1 -o $O/lat_ctx lat_ctx.c; 	\
E 13
I 13
D 20
	then	$(CC) $(SYS5) -32 -O1 -o $O/lat_ctx lat_ctx.c; 	\
E 13
	else	$(CC) $(SYS5) -o $O/lat_ctx lat_ctx.c;		\
E 20
I 20
D 26
	then	$(CC) $(CFLAGS) $(SYS5) -O1 -o $O/lat_ctx lat_ctx.c $O/lmbench.a; 	\
	else	$(CC) $(CFLAGS) $(SYS5) -o $O/lat_ctx lat_ctx.c $O/lmbench.a;		\
E 26
I 26
D 27
	then	$(CC) $(SYS5) -o32 -O1 -o $O/lat_ctx lat_ctx.c $O/lmbench.a; 	\
E 27
I 27
	then	$(CC) $(SYS5) $(SGI) -O -o $O/lat_ctx lat_ctx.c $O/lmbench.a; 	\
E 27
	else	$(CC) $(SYS5) -o $O/lat_ctx lat_ctx.c $O/lmbench.a;		\
E 26
E 20
	fi
E 11

E 39
I 15
D 20
$O/lat_pagefault:  lat_pagefault.c timing.c bench.h
	if [ $O = ../bin/linux -o $O = ../bin/bsd ];                               \
	then    cp /bin/true $O/lat_pagefault;                  \
	else    $(COMPILE) -o $O/lat_pagefault lat_pagefault.c $(LDLIBS); \
	fi
E 20
I 20
D 21
$O/lmbench.a lmbench.a: timing.c lib_tcp.c lib_udp.c timing.h lib_tcp.h lib_udp.h
E 21
I 21
D 25
$O/lmbench.a: timing.c lib_tcp.c lib_udp.c 
E 21
	$(COMPILE) -c timing.c -o $O/timing.o
E 25
I 25
D 38
$O/lmbench.a: lib_timing.c lib_tcp.c lib_udp.c 
E 38
I 38
D 40
$O/lmbench.a: lib_timing.c lib_tcp.c lib_udp.c lib_unix.c
E 40
I 40
D 42
$O/lmbench.a: lib_timing.c lib_tcp.c lib_udp.c lib_unix.c lib_stats.c
E 42
I 42
D 51
$O/lmbench.a: lib_timing.c lib_tcp.c lib_udp.c lib_unix.c lib_stats.c bench.h timing.h stats.h lib_tcp.h lib_udp.h names.h
E 51
I 51
D 65
$O/lmbench.a: lib_timing.c lib_tcp.c lib_udp.c lib_unix.c lib_stats.c getopt.c bench.h timing.h stats.h lib_tcp.h lib_udp.h names.h
E 65
I 65
D 68
$O/lmbench.a: lib_mem.c lib_timing.c lib_tcp.c lib_udp.c lib_unix.c lib_stats.c getopt.c bench.h timing.h stats.h lib_mem.h lib_tcp.h lib_udp.h names.h
E 68
I 68
$O/lmbench.a: $(LIBOBJS)
	/bin/rm -f $O/lmbench.a
	$(AR) $(ARCREATE) $O/lmbench.a $(LIBOBJS)
	-ranlib $O/lmbench.a

$O/lib_timing.o : lib_timing.c $(INCS)
E 68
E 65
E 51
E 42
E 40
E 38
	$(COMPILE) -c lib_timing.c -o $O/lib_timing.o
I 68
$O/lib_mem.o : lib_mem.c $(INCS)
E 68
I 65
	$(COMPILE) -c lib_mem.c -o $O/lib_mem.o
I 68
$O/lib_tcp.o : lib_tcp.c $(INCS)
E 68
E 65
E 25
	$(COMPILE) -c lib_tcp.c -o $O/lib_tcp.o
I 68
$O/lib_udp.o : lib_udp.c $(INCS)
E 68
	$(COMPILE) -c lib_udp.c -o $O/lib_udp.o
I 68
$O/lib_unix.o : lib_unix.c $(INCS)
E 68
I 38
	$(COMPILE) -c lib_unix.c -o $O/lib_unix.o
I 74
$O/lib_debug.o : lib_debug.c $(INCS)
	$(COMPILE) -c lib_debug.c -o $O/lib_debug.o
E 74
I 68
$O/lib_stats.o : lib_stats.c $(INCS)
E 68
I 40
	$(COMPILE) -c lib_stats.c -o $O/lib_stats.o
I 68
$O/getopt.o : getopt.c $(INCS)
E 68
I 51
	$(COMPILE) -c getopt.c -o $O/getopt.o
E 51
E 40
E 38
D 68
	/bin/rm -f $O/lmbench.a
	$(AR) $(ARCREATE) $O/lmbench.a $(LIBOBJS)
I 29
	-ranlib $O/lmbench.a
E 68
E 29
E 20

I 52
$(UTILS) :
D 53
	cd ../scripts; make get
E 53
I 53
	-cd ../scripts; make get
E 53

E 52
E 15
D 10
# Do not remove the next line, make depend needs it
E 10
I 10
# Do not remove the next line, $(MAKE) depend needs it
E 10
# MAKEDEPEND follows
I 24
D 28
$O/rhttp:  rhttp.c timing.h bench.h $O/lmbench.a
E 28
I 28
$O/rhttp:  rhttp.c timing.h stats.h bench.h $O/lmbench.a
E 28
	$(COMPILE) -o $O/rhttp rhttp.c $O/lmbench.a $(LDLIBS)

D 28
$O/http:  http.c timing.h bench.h $O/lmbench.a
E 28
I 28
$O/http:  http.c timing.h stats.h bench.h $O/lmbench.a
E 28
	$(COMPILE) -o $O/http http.c $O/lmbench.a $(LDLIBS)

I 40
$O/flushdisk:  flushdisk.c 
	$(COMPILE) -DMAIN -o $O/flushdisk flushdisk.c

E 40
I 39
$O/mhz: mhz.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/mhz mhz.c $O/lmbench.a $(LDLIBS) -lm

E 39
I 33
$O/lat_ctx: lat_ctx.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_ctx lat_ctx.c $O/lmbench.a $(LDLIBS)

E 33
D 28
$O/lmhttp:  lmhttp.c timing.h bench.h $O/lmbench.a
E 28
I 28
$O/lmhttp:  lmhttp.c timing.h stats.h bench.h $O/lmbench.a
E 28
	$(COMPILE) -o $O/lmhttp lmhttp.c $O/lmbench.a $(LDLIBS)

I 37
$O/lat_http:  lat_http.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_http lat_http.c $O/lmbench.a $(LDLIBS)

E 37
E 24
D 6
$O/bw_file_rd:  bw_file_rd.c timing.c bench.h 
E 6
I 6
D 19
$O/bw_file_rd:  bw_file_rd.c timing.c bench.h
E 19
I 19
D 20
$O/bw_file_rd:  bw_file_rd.c timing.c bench.h 
E 19
E 6
	$(COMPILE) -o $O/bw_file_rd bw_file_rd.c $(LDLIBS)
E 20
I 20
D 28
$O/bw_file_rd:  bw_file_rd.c timing.h bench.h $O/lmbench.a
E 28
I 28
$O/bw_file_rd:  bw_file_rd.c timing.h stats.h bench.h $O/lmbench.a
E 28
	$(COMPILE) -o $O/bw_file_rd bw_file_rd.c $O/lmbench.a $(LDLIBS)
E 20

D 6
$O/bw_mem_cp:  bw_mem_cp.c timing.c bench.h 
E 6
I 6
D 19
$O/bw_mem_cp:  bw_mem_cp.c timing.c bench.h
E 19
I 19
D 20
$O/bw_mem_cp:  bw_mem_cp.c timing.c bench.h 
E 19
E 6
	$(COMPILE) -o $O/bw_mem_cp bw_mem_cp.c $(LDLIBS)
E 20
I 20
D 28
$O/bw_mem_cp:  bw_mem_cp.c timing.h bench.h $O/lmbench.a
E 28
I 28
D 37
$O/bw_mem_cp:  bw_mem_cp.c timing.h stats.h bench.h $O/lmbench.a
E 28
	$(COMPILE) -o $O/bw_mem_cp bw_mem_cp.c $O/lmbench.a $(LDLIBS)
E 37
I 37
$O/bw_mem:  bw_mem.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/bw_mem bw_mem.c $O/lmbench.a $(LDLIBS)
E 37
E 20

D 6
$O/bw_mem_rd:  bw_mem_rd.c timing.c bench.h 
E 6
I 6
D 19
$O/bw_mem_rd:  bw_mem_rd.c timing.c bench.h
E 19
I 19
D 20
$O/bw_mem_rd:  bw_mem_rd.c timing.c bench.h 
E 19
E 6
	$(COMPILE) -o $O/bw_mem_rd bw_mem_rd.c $(LDLIBS)
E 20
I 20
D 28
$O/bw_mem_rd:  bw_mem_rd.c timing.h bench.h $O/lmbench.a
E 28
I 28
D 37
$O/bw_mem_rd:  bw_mem_rd.c timing.h stats.h bench.h $O/lmbench.a
E 28
	$(COMPILE) -o $O/bw_mem_rd bw_mem_rd.c $O/lmbench.a $(LDLIBS)
E 20

D 6
$O/bw_mem_wr:  bw_mem_wr.c timing.c bench.h 
E 6
I 6
D 19
$O/bw_mem_wr:  bw_mem_wr.c timing.c bench.h
E 19
I 19
D 20
$O/bw_mem_wr:  bw_mem_wr.c timing.c bench.h 
E 19
E 6
	$(COMPILE) -o $O/bw_mem_wr bw_mem_wr.c $(LDLIBS)
E 20
I 20
D 28
$O/bw_mem_wr:  bw_mem_wr.c timing.h bench.h $O/lmbench.a
E 28
I 28
$O/bw_mem_wr:  bw_mem_wr.c timing.h stats.h bench.h $O/lmbench.a
E 28
	$(COMPILE) -o $O/bw_mem_wr bw_mem_wr.c $O/lmbench.a $(LDLIBS)
E 20

E 37
D 6
$O/bw_mmap_rd:  bw_mmap_rd.c timing.c bench.h 
E 6
I 6
D 19
$O/bw_mmap_rd:  bw_mmap_rd.c timing.c bench.h
E 19
I 19
D 20
$O/bw_mmap_rd:  bw_mmap_rd.c timing.c bench.h 
E 19
E 6
	$(COMPILE) -o $O/bw_mmap_rd bw_mmap_rd.c $(LDLIBS)
E 20
I 20
D 28
$O/bw_mmap_rd:  bw_mmap_rd.c timing.h bench.h $O/lmbench.a
E 28
I 28
$O/bw_mmap_rd:  bw_mmap_rd.c timing.h stats.h bench.h $O/lmbench.a
E 28
	$(COMPILE) -o $O/bw_mmap_rd bw_mmap_rd.c $O/lmbench.a $(LDLIBS)
E 20

D 6
$O/bw_pipe:  bw_pipe.c timing.c bench.h 
E 6
I 6
D 19
$O/bw_pipe:  bw_pipe.c timing.c bench.h
E 19
I 19
D 20
$O/bw_pipe:  bw_pipe.c timing.c bench.h 
E 19
E 6
	$(COMPILE) -o $O/bw_pipe bw_pipe.c $(LDLIBS)
E 20
I 20
D 28
$O/bw_pipe:  bw_pipe.c timing.h bench.h $O/lmbench.a
E 28
I 28
$O/bw_pipe:  bw_pipe.c timing.h stats.h bench.h $O/lmbench.a
E 28
	$(COMPILE) -o $O/bw_pipe bw_pipe.c $O/lmbench.a $(LDLIBS)
E 20
D 77

I 74
$O/bw_shm:  bw_shm.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/bw_shm bw_shm.c $O/lmbench.a $(LDLIBS)
E 77

E 74
D 6
$O/bw_tcp:  bw_tcp.c lib_tcp.c bench.h timing.c 
E 6
I 6
D 19
$O/bw_tcp:  bw_tcp.c lib_tcp.c bench.h timing.c
E 19
I 19
D 20
$O/bw_tcp:  bw_tcp.c lib_tcp.c bench.h timing.c 
E 19
E 6
	$(COMPILE) -o $O/bw_tcp bw_tcp.c $(LDLIBS)
E 20
I 20
D 21
$O/bw_tcp:  bw_tcp.c lib_tcp.h timing.h bench.h $O/lmbench.a
E 21
I 21
D 28
$O/bw_tcp:  bw_tcp.c bench.h timing.h lib_tcp.h $O/lmbench.a
E 28
I 28
$O/bw_tcp:  bw_tcp.c bench.h timing.h stats.h lib_tcp.h $O/lmbench.a
E 28
E 21
	$(COMPILE) -o $O/bw_tcp bw_tcp.c $O/lmbench.a $(LDLIBS)
I 57

$O/bw_udp:  bw_udp.c bench.h timing.h stats.h lib_udp.h $O/lmbench.a
	$(COMPILE) -o $O/bw_udp bw_udp.c $O/lmbench.a $(LDLIBS)
E 57
E 20

D 6
$O/hello:  hello.c 
E 6
I 6
D 19
$O/hello:  hello.c
E 19
I 19
D 20
$O/bw_udp:  bw_udp.c bench.h lib_udp.c timing.c 
	$(COMPILE) -o $O/bw_udp bw_udp.c $(LDLIBS)
E 20
I 20
D 28
$O/bw_unix:  bw_unix.c timing.h bench.h $O/lmbench.a
E 28
I 28
$O/bw_unix:  bw_unix.c timing.h stats.h bench.h $O/lmbench.a
E 28
	$(COMPILE) -o $O/bw_unix bw_unix.c $O/lmbench.a $(LDLIBS)
E 20

I 37
D 38
$O/accept:  accept.c bench.h timing.h stats.h lib_tcp.h $O/lmbench.a
	$(COMPILE) -o $O/accept accept.c $O/lmbench.a $(LDLIBS)
E 38
I 38
$O/disk:  disk.c flushdisk.c bench.h timing.h stats.h lib_tcp.h $O/lmbench.a
D 60
	$(COMPILE) -o $O/disk disk.c flushdisk.c $O/lmbench.a $(LDLIBS)
E 60
I 60
	$(COMPILE) -o $O/disk disk.c $O/lmbench.a $(LDLIBS)
E 60
E 38

D 38
$O/disk:  disk.c bench.h timing.h stats.h lib_tcp.h $O/lmbench.a
	$(COMPILE) -o $O/disk disk.c $O/lmbench.a $(LDLIBS)

E 38
E 37
D 20
$O/bw_unix:  bw_unix.c timing.c bench.h 
	$(COMPILE) -o $O/bw_unix bw_unix.c $(LDLIBS)
E 20
I 20
D 28
$O/clock:  clock.c timing.h bench.h $O/lmbench.a
E 28
I 28
$O/clock:  clock.c timing.h stats.h bench.h $O/lmbench.a
E 28
	$(COMPILE) -o $O/clock clock.c $O/lmbench.a $(LDLIBS)
E 20

D 20
$O/hello:  hello.c 
E 19
E 6
	$(COMPILE) -o $O/hello hello.c $(LDLIBS)
E 20
I 20
$O/hello:  hello.c $O/lmbench.a
	$(COMPILE) -o $O/hello hello.c $O/lmbench.a $(LDLIBS)
E 20

D 6
$O/lat_connect:  lat_connect.c bench.h lib_tcp.c timing.c 
E 6
I 6
D 19
$O/lat_connect:  lat_connect.c bench.h lib_tcp.c timing.c
E 19
I 19
D 20
$O/lat_connect:  lat_connect.c bench.h lib_tcp.c timing.c 
E 19
E 6
	$(COMPILE) -o $O/lat_connect lat_connect.c $(LDLIBS)
E 20
I 20
D 28
$O/lat_alarm:  lat_alarm.c timing.h bench.h $O/lmbench.a
E 28
I 28
$O/lat_alarm:  lat_alarm.c timing.h stats.h bench.h $O/lmbench.a
E 28
	$(COMPILE) -o $O/lat_alarm lat_alarm.c $O/lmbench.a $(LDLIBS)
E 20

I 3
D 6
$O/lat_fs:  lat_fs.c 
E 6
I 6
D 19
$O/lat_fs:  lat_fs.c timing.c bench.h
E 19
I 19
D 20
$O/lat_fs:  lat_fs.c timing.c bench.h 
E 19
E 6
	$(COMPILE) -o $O/lat_fs lat_fs.c $(LDLIBS)
E 20
I 20
D 28
$O/lat_connect:  lat_connect.c lib_tcp.c bench.h lib_tcp.h timing.h $O/lmbench.a
E 28
I 28
$O/lat_connect:  lat_connect.c lib_tcp.c bench.h lib_tcp.h timing.h stats.h $O/lmbench.a
E 28
	$(COMPILE) -o $O/lat_connect lat_connect.c $O/lmbench.a $(LDLIBS)
E 20

I 38
$O/lat_unix_connect:  lat_unix_connect.c lib_tcp.c bench.h lib_tcp.h timing.h stats.h $O/lmbench.a
	$(COMPILE) -o $O/lat_unix_connect lat_unix_connect.c $O/lmbench.a $(LDLIBS)

E 38
E 3
D 6
$O/lat_mem_rd:  lat_mem_rd.c timing.c bench.h 
E 6
I 6
D 19
$O/lat_mem_rd:  lat_mem_rd.c timing.c bench.h
E 19
I 19
D 20
$O/lat_mem_rd:  lat_mem_rd.c timing.c bench.h 
E 19
E 6
	$(COMPILE) -o $O/lat_mem_rd lat_mem_rd.c $(LDLIBS)
E 20
I 20
D 28
$O/lat_fs:  lat_fs.c timing.h bench.h $O/lmbench.a
E 28
I 28
$O/lat_fs:  lat_fs.c timing.h stats.h bench.h $O/lmbench.a
E 28
	$(COMPILE) -o $O/lat_fs lat_fs.c $O/lmbench.a $(LDLIBS)
I 52

$O/lat_fcntl:  lat_fcntl.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_fcntl lat_fcntl.c $O/lmbench.a $(LDLIBS)
E 52
E 20

I 13
D 19
$O/lat_mem_wr:  lat_mem_wr.c timing.c bench.h
E 19
I 19
D 20
$O/lat_mem_wr:  lat_mem_wr.c timing.c bench.h 
E 19
	$(COMPILE) -o $O/lat_mem_wr lat_mem_wr.c $(LDLIBS)
E 20
I 20
D 28
$O/lat_mem_rd:  lat_mem_rd.c timing.h bench.h $O/lmbench.a
E 28
I 28
$O/lat_mem_rd:  lat_mem_rd.c timing.h stats.h bench.h $O/lmbench.a
E 28
	$(COMPILE) -o $O/lat_mem_rd lat_mem_rd.c $O/lmbench.a $(LDLIBS)
E 20

E 13
D 3
$O/lat_mem_wr:  lat_mem_wr.c timing.c bench.h 
	$(COMPILE) -o $O/lat_mem_wr lat_mem_wr.c $(LDLIBS)

E 3
D 6
$O/lat_mmap:  lat_mmap.c timing.c bench.h 
E 6
I 6
D 19
$O/lat_mmap:  lat_mmap.c timing.c bench.h
E 19
I 19
D 20
$O/lat_mem_wr2:  lat_mem_wr2.c timing.c bench.h 
	$(COMPILE) -o $O/lat_mem_wr2 lat_mem_wr2.c $(LDLIBS)
E 20
I 20
D 28
$O/lat_mem_rd2:  lat_mem_rd2.c timing.h bench.h $O/lmbench.a
E 28
I 28
$O/lat_mem_rd2:  lat_mem_rd2.c timing.h stats.h bench.h $O/lmbench.a
E 28
	$(COMPILE) -o $O/lat_mem_rd2 lat_mem_rd2.c $O/lmbench.a $(LDLIBS)
E 20

D 20
$O/lat_mmap:  lat_mmap.c timing.c bench.h 
E 19
E 6
	$(COMPILE) -o $O/lat_mmap lat_mmap.c $(LDLIBS)
E 20
I 20
D 28
$O/lat_mem_wr:  lat_mem_wr.c timing.h bench.h $O/lmbench.a
E 28
I 28
$O/lat_mem_wr:  lat_mem_wr.c timing.h stats.h bench.h $O/lmbench.a
E 28
	$(COMPILE) -o $O/lat_mem_wr lat_mem_wr.c $O/lmbench.a $(LDLIBS)
E 20

D 6
$O/lat_pagefault:  lat_pagefault.c timing.c bench.h 
E 6
I 6
D 15
$O/lat_pagefault:  lat_pagefault.c timing.c bench.h
E 6
D 11
	$(COMPILE) -o $O/lat_pagefault lat_pagefault.c $(LDLIBS)
E 11
I 11
D 13
	if [ $O = ../bin/linux ]; 				\
	then	cp /bin/true $O/lat_pagefault;			\
	else	$(COMPILE) -o $O/lat_pagefault lat_pagefault.c $(LDLIBS); \
E 13
I 13
	if [ $O = ../bin/linux ];                               \
	then    cp /bin/true $O/lat_pagefault;                  \
	else    $(COMPILE) -o $O/lat_pagefault lat_pagefault.c $(LDLIBS); \
E 13
	fi
E 11

E 15
D 6
$O/lat_pipe:  lat_pipe.c timing.c bench.h 
E 6
I 6
D 19
$O/lat_pipe:  lat_pipe.c timing.c bench.h
E 19
I 19
D 20
$O/lat_pipe:  lat_pipe.c timing.c bench.h 
E 19
E 6
	$(COMPILE) -o $O/lat_pipe lat_pipe.c $(LDLIBS)
E 20
I 20
D 28
$O/lat_mem_wr2:  lat_mem_wr2.c timing.h bench.h $O/lmbench.a
E 28
I 28
$O/lat_mem_wr2:  lat_mem_wr2.c timing.h stats.h bench.h $O/lmbench.a
E 28
	$(COMPILE) -o $O/lat_mem_wr2 lat_mem_wr2.c $O/lmbench.a $(LDLIBS)
E 20

D 6
$O/lat_proc:  lat_proc.c timing.c bench.h 
E 6
I 6
D 19
$O/lat_proc:  lat_proc.c timing.c bench.h
E 19
I 19
D 20
$O/lat_pkt:  lat_pkt.c bench.h lib_udp.c timing.c 
	$(COMPILE) -o $O/lat_pkt lat_pkt.c $(LDLIBS)
E 20
I 20
D 28
$O/lat_mmap:  lat_mmap.c timing.h bench.h $O/lmbench.a
E 28
I 28
$O/lat_mmap:  lat_mmap.c timing.h stats.h bench.h $O/lmbench.a
E 28
	$(COMPILE) -o $O/lat_mmap lat_mmap.c $O/lmbench.a $(LDLIBS)
E 20

D 20
$O/lat_proc:  lat_proc.c timing.c bench.h 
E 19
E 6
	$(COMPILE) -o $O/lat_proc lat_proc.c $(LDLIBS)
E 20
I 20
D 28
$O/lat_mmaprd:  lat_mmaprd.c timing.h bench.h $O/lmbench.a
E 28
I 28
$O/lat_mmaprd:  lat_mmaprd.c timing.h stats.h bench.h $O/lmbench.a
E 28
	$(COMPILE) -o $O/lat_mmaprd lat_mmaprd.c $O/lmbench.a $(LDLIBS)
I 58

$O/lat_ops:  lat_ops.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_ops lat_ops.c $O/lmbench.a $(LDLIBS)
E 58
E 20

D 6
$O/lat_rpc:  lat_rpc.c timing.c bench.h 
E 6
I 6
D 19
$O/lat_rpc:  lat_rpc.c timing.c bench.h
E 19
I 19
D 20
$O/lat_protfault:  lat_protfault.c timing.c bench.h 
	$(COMPILE) -o $O/lat_protfault lat_protfault.c $(LDLIBS)
E 20
I 20
D 28
$O/lat_pagefault:  lat_pagefault.c timing.h bench.h $O/lmbench.a
E 28
I 28
$O/lat_pagefault:  lat_pagefault.c timing.h stats.h bench.h $O/lmbench.a
E 28
	$(COMPILE) -o $O/lat_pagefault lat_pagefault.c $O/lmbench.a $(LDLIBS)
E 20

D 20
$O/lat_rpc:  lat_rpc.c timing.c bench.h 
E 19
E 6
	$(COMPILE) -o $O/lat_rpc lat_rpc.c $(LDLIBS)
E 20
I 20
D 28
$O/lat_pipe:  lat_pipe.c timing.h bench.h $O/lmbench.a
E 28
I 28
$O/lat_pipe:  lat_pipe.c timing.h stats.h bench.h $O/lmbench.a
E 28
	$(COMPILE) -o $O/lat_pipe lat_pipe.c $O/lmbench.a $(LDLIBS)
E 20

I 37
$O/lat_fifo:  lat_fifo.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_fifo lat_fifo.c $O/lmbench.a $(LDLIBS)

E 37
I 8
D 19
$O/lat_sig:  lat_sig.c timing.c bench.h
E 19
I 19
D 20
$O/lat_sig:  lat_sig.c timing.c bench.h 
E 19
	$(COMPILE) -o $O/lat_sig lat_sig.c $(LDLIBS)
E 20
I 20
D 28
$O/lat_proc:  lat_proc.c timing.h bench.h $O/lmbench.a
E 28
I 28
$O/lat_proc:  lat_proc.c timing.h stats.h bench.h $O/lmbench.a
E 28
	$(COMPILE) -o $O/lat_proc lat_proc.c $O/lmbench.a $(LDLIBS)
E 20

E 8
D 6
$O/lat_syscall:  lat_syscall.c timing.c bench.h 
E 6
I 6
D 19
$O/lat_syscall:  lat_syscall.c timing.c bench.h
E 19
I 19
D 20
$O/lat_syscall:  lat_syscall.c timing.c bench.h 
E 19
E 6
	$(COMPILE) -o $O/lat_syscall lat_syscall.c $(LDLIBS)
E 20
I 20
D 28
$O/lat_rpc:  lat_rpc.c timing.h bench.h $O/lmbench.a
E 28
I 28
$O/lat_rpc:  lat_rpc.c timing.h stats.h bench.h $O/lmbench.a
E 28
	$(COMPILE) -o $O/lat_rpc lat_rpc.c $O/lmbench.a $(LDLIBS)
E 20

D 6
$O/lat_tcp:  lat_tcp.c bench.h lib_tcp.c timing.c 
E 6
I 6
D 19
$O/lat_tcp:  lat_tcp.c bench.h lib_tcp.c timing.c
E 19
I 19
D 20
$O/lat_tcp:  lat_tcp.c bench.h lib_tcp.c timing.c 
E 19
E 6
	$(COMPILE) -o $O/lat_tcp lat_tcp.c $(LDLIBS)
E 20
I 20
D 28
$O/lat_sig:  lat_sig.c timing.h bench.h $O/lmbench.a
E 28
I 28
$O/lat_sig:  lat_sig.c timing.h stats.h bench.h $O/lmbench.a
E 28
	$(COMPILE) -o $O/lat_sig lat_sig.c $O/lmbench.a $(LDLIBS)
E 20

D 6
$O/lat_udp:  lat_udp.c bench.h lib_udp.c timing.c 
E 6
I 6
D 19
$O/lat_udp:  lat_udp.c bench.h lib_udp.c timing.c
E 19
I 19
D 20
$O/lat_udp:  lat_udp.c bench.h lib_udp.c timing.c 
E 19
E 6
	$(COMPILE) -o $O/lat_udp lat_udp.c $(LDLIBS)
E 20
I 20
D 28
$O/lat_syscall:  lat_syscall.c timing.h bench.h $O/lmbench.a
E 28
I 28
$O/lat_syscall:  lat_syscall.c timing.h stats.h bench.h $O/lmbench.a
E 28
	$(COMPILE) -o $O/lat_syscall lat_syscall.c $O/lmbench.a $(LDLIBS)
E 20

D 6
$O/lib_tcp:  lib_tcp.c bench.h 
E 6
I 6
D 19
$O/lib_tcp:  lib_tcp.c bench.h
E 19
I 19
D 20
$O/lat_unix:  lat_unix.c bench.h timing.c 
	$(COMPILE) -o $O/lat_unix lat_unix.c $(LDLIBS)
E 20
I 20
D 21
$O/lat_tcp:  lat_tcp.c lib_tcp.h timing.h bench.h $O/lmbench.a
E 21
I 21
D 28
$O/lat_select:  lat_select.c timing.h bench.h $O/lmbench.a
E 28
I 28
$O/lat_select:  lat_select.c timing.h stats.h bench.h $O/lmbench.a
E 28
	$(COMPILE) -o $O/lat_select lat_select.c $O/lmbench.a $(LDLIBS)

D 28
$O/lat_tcp:  lat_tcp.c timing.h bench.h lib_tcp.h $O/lmbench.a
E 28
I 28
$O/lat_tcp:  lat_tcp.c timing.h stats.h bench.h lib_tcp.h $O/lmbench.a
E 28
E 21
	$(COMPILE) -o $O/lat_tcp lat_tcp.c $O/lmbench.a $(LDLIBS)
E 20

D 20
$O/lib_tcp:  lib_tcp.c bench.h 
E 19
E 6
	$(COMPILE) -o $O/lib_tcp lib_tcp.c $(LDLIBS)
E 20
I 20
D 21
$O/lat_udp:  lat_udp.c lib_udp.h timing.h bench.h $O/lmbench.a
E 21
I 21
D 28
$O/lat_udp:  lat_udp.c timing.h bench.h lib_udp.h $O/lmbench.a
E 28
I 28
$O/lat_udp:  lat_udp.c timing.h stats.h bench.h lib_udp.h $O/lmbench.a
E 28
E 21
	$(COMPILE) -o $O/lat_udp lat_udp.c $O/lmbench.a $(LDLIBS)
E 20

D 6
$O/lib_udp:  lib_udp.c bench.h 
E 6
I 6
D 19
$O/lib_udp:  lib_udp.c bench.h
E 19
I 19
D 20
$O/lib_udp:  lib_udp.c bench.h 
E 19
E 6
	$(COMPILE) -o $O/lib_udp lib_udp.c $(LDLIBS)
E 20
I 20
D 28
$O/lat_unix:  lat_unix.c timing.h bench.h $O/lmbench.a
E 28
I 28
$O/lat_unix:  lat_unix.c timing.h stats.h bench.h $O/lmbench.a
E 28
	$(COMPILE) -o $O/lat_unix lat_unix.c $O/lmbench.a $(LDLIBS)
E 20

D 6
$O/lmdd:  lmdd.c timing.c bench.h 
E 6
I 6
D 19
$O/lmdd:  lmdd.c timing.c bench.h
E 19
I 19
D 20
$O/lmdd:  lmdd.c timing.c bench.h 
E 19
E 6
	$(COMPILE) -o $O/lmdd lmdd.c $(LDLIBS)
E 20
I 20
$O/lib_tcp:  lib_tcp.c bench.h lib_tcp.h $O/lmbench.a
	$(COMPILE) -o $O/lib_tcp lib_tcp.c $O/lmbench.a $(LDLIBS)
E 20

I 14
D 19
$O/memsize:  memsize.c timing.c bench.h
E 19
I 19
D 20
$O/memsize:  memsize.c timing.c bench.h 
E 19
	$(COMPILE) -o $O/memsize memsize.c $(LDLIBS)
E 20
I 20
$O/lib_udp:  lib_udp.c bench.h lib_udp.h $O/lmbench.a
	$(COMPILE) -o $O/lib_udp lib_udp.c $O/lmbench.a $(LDLIBS)
E 20

E 14
D 3
$O/t:  t.c timing.c bench.h 
	$(COMPILE) -o $O/t t.c $(LDLIBS)

E 3
D 6
$O/timing:  timing.c bench.h 
E 6
I 6
D 19
$O/timing:  timing.c bench.h
E 19
I 19
D 20
$O/memsize_malloc:  memsize_malloc.c timing.c bench.h 
	$(COMPILE) -o $O/memsize_malloc memsize_malloc.c $(LDLIBS)
E 20
I 20
D 28
$O/lmdd:  lmdd.c timing.h bench.h $O/lmbench.a
E 28
I 28
$O/lmdd:  lmdd.c timing.h stats.h bench.h $O/lmbench.a
E 28
	$(COMPILE) -o $O/lmdd lmdd.c $O/lmbench.a $(LDLIBS)
E 20

I 26
D 28
$O/enough:  enough.c timing.h bench.h $O/lmbench.a
E 28
I 28
$O/enough:  enough.c timing.h stats.h bench.h $O/lmbench.a
E 28
	$(COMPILE) -o $O/enough enough.c $O/lmbench.a $(LDLIBS)

I 29
$O/loop_o:  loop_o.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/loop_o loop_o.c $O/lmbench.a $(LDLIBS)

E 29
D 28
$O/timing_o:  timing_o.c timing.h bench.h $O/lmbench.a
E 28
I 28
$O/timing_o:  timing_o.c timing.h stats.h bench.h $O/lmbench.a
E 28
	$(COMPILE) -o $O/timing_o timing_o.c $O/lmbench.a $(LDLIBS)

E 26
D 20
$O/nmm:  nmm.c 
	$(COMPILE) -o $O/nmm nmm.c $(LDLIBS)
E 20
I 20
D 28
$O/memsize:  memsize.c timing.h bench.h $O/lmbench.a
E 28
I 28
$O/memsize:  memsize.c timing.h stats.h bench.h $O/lmbench.a
E 28
	$(COMPILE) -o $O/memsize memsize.c $O/lmbench.a $(LDLIBS)
E 20

D 20
$O/timing:  timing.c bench.h 
E 19
E 6
	$(COMPILE) -o $O/timing timing.c $(LDLIBS)
E 20
I 20
D 28
$O/memsize_malloc:  memsize_malloc.c timing.h bench.h $O/lmbench.a
E 28
I 28
D 29
$O/memsize_malloc:  memsize_malloc.c timing.h stats.h bench.h $O/lmbench.a
E 28
	$(COMPILE) -o $O/memsize_malloc memsize_malloc.c $O/lmbench.a $(LDLIBS)
E 20

E 29
I 29
$O/msleep:  msleep.c timing.h stats.h bench.h 
	$(COMPILE) -o $O/msleep msleep.c
I 54

D 55
$O/line:  line.c timing.h stats.h bench.h 
E 55
I 55
$O/line:  line.c timing.h stats.h bench.h $O/lmbench.a
E 55
	$(COMPILE) -o $O/line line.c $O/lmbench.a $(LDLIBS)

D 55
$O/tlb:  tlb.c timing.h stats.h bench.h 
E 55
I 55
$O/tlb:  tlb.c timing.h stats.h bench.h $O/lmbench.a
E 55
	$(COMPILE) -o $O/tlb tlb.c $O/lmbench.a $(LDLIBS)

D 55
$O/cache:  cache.c timing.h stats.h bench.h 
E 55
I 55
$O/cache:  cache.c timing.h stats.h bench.h $O/lmbench.a
E 55
	$(COMPILE) -o $O/cache cache.c $O/lmbench.a $(LDLIBS)
I 56

D 62
$O/loads:  loads.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/loads loads.c $O/lmbench.a $(LDLIBS)
E 62
I 62
$O/par_mem:  par_mem.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/par_mem par_mem.c $O/lmbench.a $(LDLIBS)
I 63

$O/par_ops:  par_ops.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/par_ops par_ops.c $O/lmbench.a $(LDLIBS)
E 63
E 62
I 59

$O/stream:  stream.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/stream stream.c $O/lmbench.a $(LDLIBS)
I 66

$O/lat_sem:  lat_sem.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_sem lat_sem.c $O/lmbench.a $(LDLIBS)
D 72

$O/bw_shm:  bw_shm.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/bw_shm bw_shm.c $O/lmbench.a $(LDLIBS)
E 72

$O/par_list:  par_list.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/par_list par_list.c $O/lmbench.a $(LDLIBS)
I 74

$O/lat_dram_page:  lat_dram_page.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_dram_page lat_dram_page.c $O/lmbench.a $(LDLIBS)
I 75

$O/lat_usleep:  lat_usleep.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_usleep lat_usleep.c $O/lmbench.a $(LDLIBS)
E 75
E 74
E 66
E 59
E 56
E 54
E 29
I 20
D 23
$O/open:  open.c timing.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/open open.c $O/lmbench.a $(LDLIBS)
E 23
I 23
D 24
$O/http:  http.c timing.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/http http.c $O/lmbench.a $(LDLIBS)
E 23

D 23
$O/seek:  seek.c timing.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/seek seek.c $O/lmbench.a $(LDLIBS)
E 23
I 23
$O/http_srv:  http_srv.c timing.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/http_srv http_srv.c $O/lmbench.a $(LDLIBS)
E 23

E 24
D 23
$O/seek2:  seek2.c timing.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/seek2 seek2.c $O/lmbench.a $(LDLIBS)

$O/seekp:  seekp.c timing.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/seekp seekp.c $O/lmbench.a $(LDLIBS)

$O/shuffle:  shuffle.c timing.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/shuffle shuffle.c $O/lmbench.a $(LDLIBS)

$O/timing:  timing.c timing.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/timing timing.c $O/lmbench.a $(LDLIBS)

D 21
$O/x:  x.c $O/lmbench.a
	$(COMPILE) -o $O/x x.c $O/lmbench.a $(LDLIBS)

E 21
$O/xlv:  xlv.c timing.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/xlv xlv.c $O/lmbench.a $(LDLIBS)

$O/zone:  zone.c timing.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/zone zone.c $O/lmbench.a $(LDLIBS)

E 23
E 20
E 2
I 1
E 1
