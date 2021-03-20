# $Id$

# Make targets:
#
# lmbench	[default] builds the benchmark suite for the current os/arch
# results	builds, configures run parameters, and runs the benchmark
# rerun		reruns the benchmark using the same parameters as last time
# scaling	reruns the benchmark using same parameters as last time,
#		except it asks what scaling value to use
# hardware	reruns the hardware benchmarks using the same parameters
# os		reruns the OS benchmarks using the same parameters
# clean		cleans out sources and run configuration
# clobber	clean and removes the bin directories
# shar		obsolete, use cd .. && make shar
# depend	builds make dependencies (needs gcc)
#
# This is largely self configuring.  Most stuff is pretty portable.  You
# may have problems with the mhz program.  
#

# I finally know why Larry Wall's Makefile says "Grrrr".
SHELL=/bin/sh

CC = `../scripts/compiler`
MAKE = `../scripts/make`
AR = ar
ARCREATE = cr
BASE=/usr/local		# base of installation location
O= ../bin/unknown
D= ../doc
TRUE=/bin/true
OS=`../scripts/os`
TARGET=`../scripts/target`
BINDIR=../bin/$(OS)
CONFIG=../bin/$(OS)/`../scripts/config`
UTILS=../scripts/target ../scripts/os ../scripts/gnu-os ../scripts/compiler \
	../scripts/info ../scripts/info-template ../scripts/version \
	../scripts/config ../scripts/config-run ../scripts/results \
	../scripts/lmbench ../scripts/make ../scripts/build
INSTALL=cp
RESULTS=Results/$(OS)
SAMPLES=lmbench/Results/aix/rs6000 lmbench/Results/hpux/snake \
	lmbench/Results/irix/indigo2 lmbench/Results/linux/pentium \
	lmbench/Results/osf1/alpha lmbench/Results/solaris/ss20* 

COMPILE=$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)

INCS =	bench.h lib_mem.h lib_tcp.h lib_udp.h stats.h timing.h

SRCS =  bw_file_rd.c bw_mem.c bw_mmap_rd.c bw_pipe.c bw_tcp.c bw_udp.c	\
	bw_unix.c							\
	cache.c clock.c disk.c enough.c flushdisk.c getopt.c hello.c	\
	lat_connect.c lat_ctx.c	lat_fcntl.c lat_fifo.c lat_fs.c 	\
	lat_mem_rd.c lat_mmap.c lat_ops.c lat_pagefault.c lat_pipe.c 	\
	lat_proc.c lat_rpc.c lat_select.c lat_sig.c lat_syscall.c	\
	lat_tcp.c lat_udp.c lat_unix.c lat_unix_connect.c lat_sem.c	\
	lat_usleep.c 							\
	lib_debug.c lib_mem.c lib_stats.c lib_tcp.c lib_timing.c 	\
	lib_udp.c lib_unix.c						\
	line.c lmdd.c lmhttp.c par_mem.c par_ops.c loop_o.c memsize.c 	\
	mhz.c msleep.c rhttp.c seek.c timing_o.c tlb.c stream.c		\
	bench.h lib_debug.h lib_tcp.h lib_udp.h lib_unix.h names.h 	\
	stats.h timing.h version.h

EXES =	$O/bw_file_rd $O/bw_mem $O/bw_mmap_rd $O/bw_pipe $O/bw_tcp 	\
	$O/bw_unix $O/hello						\
	$O/lat_select $O/lat_pipe $O/lat_rpc $O/lat_syscall $O/lat_tcp	\
	$O/lat_udp $O/lat_mmap $O/mhz $O/lat_proc $O/lat_pagefault	\
	$O/lat_connect $O/lat_fs $O/lat_sig $O/lat_mem_rd $O/lat_ctx	\
	$O/lat_sem 							\
	$O/memsize $O/lat_unix $O/lmdd $O/timing_o $O/enough		\
	$O/msleep $O/loop_o $O/lat_fifo $O/lmhttp $O/lat_http		\
	$O/lat_fcntl $O/disk $O/lat_unix_connect $O/flushdisk		\
	$O/lat_ops $O/line $O/tlb $O/par_mem $O/par_ops 		\
	$O/stream 
OPT_EXES=$O/lat_dram_page $O/lat_usleep $O/cache 

MAN1 =	lmdd.1 $D/bargraph.1 $D/graph.1 $D/pgraph.1 $D/rccs.1

MAN3 =	$D/lmbench.3 $D/reporting.3 $D/results.3 $D/timing.3

MAN8 =	$D/bw_file_rd.8 $D/bw_mem.8 $D/bw_mmap_rd.8 \
	$D/bw_pipe.8 $D/bw_tcp.8 $D/bw_unix.8 $D/lat_connect.8	\
	$D/lat_ctx.8 $D/lat_fs.8 $D/lat_mem_rd.8 $D/lat_mmap.8		\
	$D/lat_pagefault.8 $D/lat_pipe.8 $D/lat_proc.8 $D/lat_rpc.8 	\
	$D/lat_syscall.8 $D/lat_tcp.8 $D/lat_udp.8 $D/lmbench.8 	\
	$D/lat_select.8 $D/lat_unix.8 $D/lat_unix_connect.8		\
	$D/lat_fifo.8 $D/lat_fcntl.8 $D/lat_http.8 $D/lat_sig.8		\
	$D/lat_ops.8 $D/par_ops.8 $D/par_mem.8				\
	$D/lmdd.8 $D/mhz.8 $D/cache.8 $D/tlb.8 $D/line.8
LIBOBJS= $O/lib_tcp.o $O/lib_udp.o $O/lib_unix.o $O/lib_timing.o 	\
	$O/lib_mem.o $O/lib_stats.o $O/lib_debug.o $O/getopt.o

lmbench: $(UTILS)
	@env CFLAGS=-O MAKE="$(MAKE)" MAKEFLAGS="$(MAKEFLAGS)" ../scripts/build all
	-@env CFLAGS=-O MAKE="$(MAKE)" MAKEFLAGS="-k $(MAKEFLAGS)" ../scripts/build opt

results: lmbench
	@../scripts/config-run
	@BENCHMARK_HARDWARE=YES BENCHMARK_OS=YES ../scripts/results

rerun: lmbench
	@if [ ! -f $(CONFIG) ]; then ../scripts/config-run; fi
	@../scripts/results

scaling: lmbench
	@if [ ! -f $(CONFIG) ]; then ../scripts/config-run; \
	 else ../scripts/config-scaling $(CONFIG); fi
	@../scripts/results

hardware: lmbench
	@if [ ! -f $(CONFIG) ]; then ../scripts/config-run; fi
	@BENCHMARK_HARDWARE=YES BENCHMARK_OS=NO  ../scripts/results

os: lmbench
	@if [ ! -f $(CONFIG) ]; then ../scripts/config-run; fi
	@BENCHMARK_HARDWARE=NO  BENCHMARK_OS=YES ../scripts/results

install: lmbench
	@env CFLAGS=-O MAKE="$(MAKE)"  MAKEFLAGS="$(MAKEFLAGS)" ../scripts/build install-target

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


# No special handling for all these
all: $(EXES)
opt: $(OPT_EXES)

Wall:
	@env CFLAGS="-Wall -ansi" MAKE="$(MAKE)" MAKEFLAGS="$(MAKEFLAGS)" ../scripts/build all

debug:
	@env CFLAGS=-g MAKE="$(MAKE)" MAKEFLAGS="$(MAKEFLAGS)" ../scripts/build all

bk.ver: ../SCCS/s.ChangeSet
	rm -f bk.ver
	-echo `bk prs -hr+ -d'$$if(:SYMBOL:){:SYMBOL: }:UTC:' ../ChangeSet;` > bk.ver
	touch bk.ver

dist: bk.ver
	@if [ "X`cd ..; bk sfiles -c`" != "X" ]; then \
		echo "modified files!"; \
		false; \
	 fi
	@if [ "X`cd ..; bk pending`" != "X" ]; then \
		echo "pending changes!"; \
		false; \
	 fi
	cd ..; \
		SRCDIR=`pwd`; \
		DIR=`basename $${SRCDIR}`; \
		VERSION=`cat src/bk.ver| awk '{print $$1;}' | sed -e 's/Version-//g'`; \
		cd ..; \
		bk clone $${DIR} /tmp/lmbench-$${VERSION}; \
		cd /tmp/lmbench-$${VERSION}; \
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
		tar czf $${SRCDIR}/../lmbench-$${VERSION}.tgz \
			lmbench-$${VERSION}; \
		rm -rf /tmp/lmbench-$${VERSION};

get $(SRCS):
	-get -s $(SRCS)

edit get-e:
	get -e -s $(SRCS)

clean:
	/bin/rm -f ../bin/*/CONFIG ../bin/*/*.[oa]
	-bk clean

clobber:
	/bin/rm -rf ../bin* SHAR
	-bk clean

shar:
	cd ../.. && shar lmbench/Results/Makefile $(SAMPLES) lmbench/scripts/* lmbench/src/Makefile lmbench/src/*.[ch] > lmbench/SHAR

depend: ../scripts/depend
	../scripts/depend

testmake: $(SRCS) $(UTILS) # used by scripts/make to test gmake
	@true

.PHONY: lmbench results rerun hardware os install all Wall debug \
	install install-target dist get edit get-e clean clobber \
	share depend testmake

$O/lmbench.a: $(LIBOBJS)
	/bin/rm -f $O/lmbench.a
	$(AR) $(ARCREATE) $O/lmbench.a $(LIBOBJS)
	-ranlib $O/lmbench.a

$O/lib_timing.o : lib_timing.c $(INCS)
	$(COMPILE) -c lib_timing.c -o $O/lib_timing.o
$O/lib_mem.o : lib_mem.c $(INCS)
	$(COMPILE) -c lib_mem.c -o $O/lib_mem.o
$O/lib_tcp.o : lib_tcp.c $(INCS)
	$(COMPILE) -c lib_tcp.c -o $O/lib_tcp.o
$O/lib_udp.o : lib_udp.c $(INCS)
	$(COMPILE) -c lib_udp.c -o $O/lib_udp.o
$O/lib_unix.o : lib_unix.c $(INCS)
	$(COMPILE) -c lib_unix.c -o $O/lib_unix.o
$O/lib_debug.o : lib_debug.c $(INCS)
	$(COMPILE) -c lib_debug.c -o $O/lib_debug.o
$O/lib_stats.o : lib_stats.c $(INCS)
	$(COMPILE) -c lib_stats.c -o $O/lib_stats.o
$O/getopt.o : getopt.c $(INCS)
	$(COMPILE) -c getopt.c -o $O/getopt.o

$(UTILS) :
	-cd ../scripts; make get

# Do not remove the next line, $(MAKE) depend needs it
# MAKEDEPEND follows
$O/rhttp:  rhttp.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/rhttp rhttp.c $O/lmbench.a $(LDLIBS)

$O/http:  http.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/http http.c $O/lmbench.a $(LDLIBS)

$O/flushdisk:  flushdisk.c 
	$(COMPILE) -DMAIN -o $O/flushdisk flushdisk.c

$O/mhz: mhz.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/mhz mhz.c $O/lmbench.a $(LDLIBS) -lm

$O/lat_ctx: lat_ctx.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_ctx lat_ctx.c $O/lmbench.a $(LDLIBS)

$O/lmhttp:  lmhttp.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lmhttp lmhttp.c $O/lmbench.a $(LDLIBS)

$O/lat_http:  lat_http.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_http lat_http.c $O/lmbench.a $(LDLIBS)

$O/bw_file_rd:  bw_file_rd.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/bw_file_rd bw_file_rd.c $O/lmbench.a $(LDLIBS)

$O/bw_mem:  bw_mem.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/bw_mem bw_mem.c $O/lmbench.a $(LDLIBS)

$O/bw_mmap_rd:  bw_mmap_rd.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/bw_mmap_rd bw_mmap_rd.c $O/lmbench.a $(LDLIBS)

$O/bw_pipe:  bw_pipe.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/bw_pipe bw_pipe.c $O/lmbench.a $(LDLIBS)

$O/bw_tcp:  bw_tcp.c bench.h timing.h stats.h lib_tcp.h $O/lmbench.a
	$(COMPILE) -o $O/bw_tcp bw_tcp.c $O/lmbench.a $(LDLIBS)

$O/bw_udp:  bw_udp.c bench.h timing.h stats.h lib_udp.h $O/lmbench.a
	$(COMPILE) -o $O/bw_udp bw_udp.c $O/lmbench.a $(LDLIBS)

$O/bw_unix:  bw_unix.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/bw_unix bw_unix.c $O/lmbench.a $(LDLIBS)

$O/disk:  disk.c flushdisk.c bench.h timing.h stats.h lib_tcp.h $O/lmbench.a
	$(COMPILE) -o $O/disk disk.c $O/lmbench.a $(LDLIBS)

$O/clock:  clock.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/clock clock.c $O/lmbench.a $(LDLIBS)

$O/hello:  hello.c $O/lmbench.a
	$(COMPILE) -o $O/hello hello.c $O/lmbench.a $(LDLIBS)

$O/lat_alarm:  lat_alarm.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_alarm lat_alarm.c $O/lmbench.a $(LDLIBS)

$O/lat_connect:  lat_connect.c lib_tcp.c bench.h lib_tcp.h timing.h stats.h $O/lmbench.a
	$(COMPILE) -o $O/lat_connect lat_connect.c $O/lmbench.a $(LDLIBS)

$O/lat_unix_connect:  lat_unix_connect.c lib_tcp.c bench.h lib_tcp.h timing.h stats.h $O/lmbench.a
	$(COMPILE) -o $O/lat_unix_connect lat_unix_connect.c $O/lmbench.a $(LDLIBS)

$O/lat_fs:  lat_fs.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_fs lat_fs.c $O/lmbench.a $(LDLIBS)

$O/lat_fcntl:  lat_fcntl.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_fcntl lat_fcntl.c $O/lmbench.a $(LDLIBS)

$O/lat_mem_rd:  lat_mem_rd.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_mem_rd lat_mem_rd.c $O/lmbench.a $(LDLIBS)

$O/lat_mem_rd2:  lat_mem_rd2.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_mem_rd2 lat_mem_rd2.c $O/lmbench.a $(LDLIBS)

$O/lat_mem_wr:  lat_mem_wr.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_mem_wr lat_mem_wr.c $O/lmbench.a $(LDLIBS)

$O/lat_mem_wr2:  lat_mem_wr2.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_mem_wr2 lat_mem_wr2.c $O/lmbench.a $(LDLIBS)

$O/lat_mmap:  lat_mmap.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_mmap lat_mmap.c $O/lmbench.a $(LDLIBS)

$O/lat_mmaprd:  lat_mmaprd.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_mmaprd lat_mmaprd.c $O/lmbench.a $(LDLIBS)

$O/lat_ops:  lat_ops.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_ops lat_ops.c $O/lmbench.a $(LDLIBS)

$O/lat_pagefault:  lat_pagefault.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_pagefault lat_pagefault.c $O/lmbench.a $(LDLIBS)

$O/lat_pipe:  lat_pipe.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_pipe lat_pipe.c $O/lmbench.a $(LDLIBS)

$O/lat_fifo:  lat_fifo.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_fifo lat_fifo.c $O/lmbench.a $(LDLIBS)

$O/lat_proc:  lat_proc.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_proc lat_proc.c $O/lmbench.a $(LDLIBS)

$O/lat_rpc:  lat_rpc.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_rpc lat_rpc.c $O/lmbench.a $(LDLIBS)

$O/lat_sig:  lat_sig.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_sig lat_sig.c $O/lmbench.a $(LDLIBS)

$O/lat_syscall:  lat_syscall.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_syscall lat_syscall.c $O/lmbench.a $(LDLIBS)

$O/lat_select:  lat_select.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_select lat_select.c $O/lmbench.a $(LDLIBS)

$O/lat_tcp:  lat_tcp.c timing.h stats.h bench.h lib_tcp.h $O/lmbench.a
	$(COMPILE) -o $O/lat_tcp lat_tcp.c $O/lmbench.a $(LDLIBS)

$O/lat_udp:  lat_udp.c timing.h stats.h bench.h lib_udp.h $O/lmbench.a
	$(COMPILE) -o $O/lat_udp lat_udp.c $O/lmbench.a $(LDLIBS)

$O/lat_unix:  lat_unix.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_unix lat_unix.c $O/lmbench.a $(LDLIBS)

$O/lib_tcp:  lib_tcp.c bench.h lib_tcp.h $O/lmbench.a
	$(COMPILE) -o $O/lib_tcp lib_tcp.c $O/lmbench.a $(LDLIBS)

$O/lib_udp:  lib_udp.c bench.h lib_udp.h $O/lmbench.a
	$(COMPILE) -o $O/lib_udp lib_udp.c $O/lmbench.a $(LDLIBS)

$O/lmdd:  lmdd.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lmdd lmdd.c $O/lmbench.a $(LDLIBS)

$O/enough:  enough.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/enough enough.c $O/lmbench.a $(LDLIBS)

$O/loop_o:  loop_o.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/loop_o loop_o.c $O/lmbench.a $(LDLIBS)

$O/timing_o:  timing_o.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/timing_o timing_o.c $O/lmbench.a $(LDLIBS)

$O/memsize:  memsize.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/memsize memsize.c $O/lmbench.a $(LDLIBS)

$O/msleep:  msleep.c timing.h stats.h bench.h 
	$(COMPILE) -o $O/msleep msleep.c

$O/line:  line.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/line line.c $O/lmbench.a $(LDLIBS)

$O/tlb:  tlb.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/tlb tlb.c $O/lmbench.a $(LDLIBS)

$O/cache:  cache.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/cache cache.c $O/lmbench.a $(LDLIBS)

$O/par_mem:  par_mem.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/par_mem par_mem.c $O/lmbench.a $(LDLIBS)

$O/par_ops:  par_ops.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/par_ops par_ops.c $O/lmbench.a $(LDLIBS)

$O/stream:  stream.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/stream stream.c $O/lmbench.a $(LDLIBS)

$O/lat_sem:  lat_sem.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_sem lat_sem.c $O/lmbench.a $(LDLIBS)

$O/par_list:  par_list.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/par_list par_list.c $O/lmbench.a $(LDLIBS)

$O/lat_dram_page:  lat_dram_page.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_dram_page lat_dram_page.c $O/lmbench.a $(LDLIBS)

$O/lat_usleep:  lat_usleep.c timing.h stats.h bench.h $O/lmbench.a
	$(COMPILE) -o $O/lat_usleep lat_usleep.c $O/lmbench.a $(LDLIBS)
