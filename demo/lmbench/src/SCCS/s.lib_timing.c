H53185
s 00000/00000/01743
d D 1.64 02/10/01 09:50:42 staelin 68 66
i 67
c Auto merged
cC
cHhpli69.hpli.hpl.hp.com
cK12420
cM67
e
s 00000/00025/01740
d D 1.62.1.1 02/10/01 09:50:06 staelin 67 64
c - move print_results to lib_debug
cC
cK09710
e
s 00000/00000/01768
d D 1.63 02/09/29 21:55:04 staelin 66 64
i 65
c Auto merged
cC
cHfirewall.staelin.co.il
cK52310
cM65
e
s 00005/00002/01706
d D 1.60.1.1 02/09/29 21:53:51 staelin 65 62
c - change return type for bytes() to uint64, and switch from atoi() to
c   sscanf() to convert from string to integer
cC
cHfirewall.staelin.co.il
cK00632
e
s 00016/00006/01749
d D 1.62 02/09/20 09:34:01 staelin 64 63
c lib_timing.c: Fixup bread() so it can handle all buffer sizes properly
cC
cK49600
e
s 00047/00000/01708
d D 1.61 02/07/15 09:30:14 staelin 63 62
c Add another routine to the benchmp() interface, which allows
c the child (worker) process to query the harness to find out
c its relative ID.  
cC
cK27487
e
s 00017/00009/01691
d D 1.60 02/06/30 16:39:50 staelin 62 61
c Fixup a bug in the benchmp() timing harness w/r to select(); we
c needed to reset the timeout values after each select() call, but
c we weren't so after the first call (typically) select() would not
c wait but would return immediately, adding a tremendous burden on
c the CPU.
cC
cK63458
cZ+03:00
e
s 00021/00000/01679
d D 1.59 01/11/13 16:34:33 staelin 61 60
c Add globally visible routine cp(char* src, char* dst, mode_t mode)
c which copies a file.  Required renaming a cp() routine in bw_mem
c to avoid name collisions.
cC
cK50740
cZ+02:00
e
s 00012/00001/01667
d D 1.58 01/09/11 09:41:19 staelin 60 59
c Optionally add more detail to print_results(); i.e. the 
c iteration count and timing details.
cC
cK24036
e
s 00000/00008/01668
d D 1.57 01/06/13 11:00:39 staelin 59 58
c Enhance/update portability system to deal with various flavors of
c random number generators available in unix: drand48/rand/random.
cC
cK04729
e
s 00008/00000/01668
d D 1.56 01/05/21 10:58:00 staelin 58 57
c Add tests for existence of srand48() and drand48(), and add replacements
c based on srand() and rand() if they aren't present.
cC
cK13332
e
s 00002/00000/01666
d D 1.55 01/04/09 16:46:38 staelin 57 56
c Error checking --- double-check that malloc() doesn't return NULL
cC
cHhpli69.hpli.hpl.hp.com
cK04729
e
s 00011/00008/01655
d D 1.54 00/09/26 16:03:55 staelin 56 55
c - Fixed a bug in benchmp_child where it could dereference a NULL function pointer
c - Added a variety of return-code checking around various malloc() statements
cC
cK02098
e
s 00008/00002/01655
d D 1.53 00/09/25 17:27:48 staelin 55 54
c - Update copyright message
c - Add new parameter to permutation() which allows the caller to scale the results by
c   some factor.
c - 
cC
cK56607
e
s 00005/00000/01652
d D 1.52 00/09/18 11:34:16 staelin 54 53
c - Fix bug in SIGCHLD handling which was causing an infinite loop in lat_proc
cC
cK26787
e
s 00036/00000/01616
d D 1.51 00/09/13 12:41:42 staelin 53 52
c - Add "int* permutation(int N);" which returns a permutation of N integers
cC
cK17145
e
s 00090/00021/01526
d D 1.50 00/08/16 09:29:19 staelin 52 51
c - Change/fix SIGTERM handling to make it more robust and generic
cC
cK34460
e
s 00231/00210/01316
d D 1.49 00/08/02 18:05:02 staelin 51 50
c - Lots of bugfixes to the timing harness to make it more reliable in the parallel case.
c - Make it so the harness sends SIGTERM to child processes when any child dies.  This 
c   allows the child process to cleanup any child processes of its own before it commits
c   suicide.
c - Added checks to benchmp() in the parallel case to ensure that the timing harness was
c   able to execute the parallel=1 subcase which is used to compute iterations for the
c   full parallel case.  It now exits when the parallel=1 case fails.
c - Rearrange the order of benchmp_child, benchmp_parent, and benchmp_interval to make it
c   easier to read the code through and understand the harness
c - Add checks to the result reporting routines so no results are printed if gettime() is
c   zero.
cC
cK03223
e
s 00010/00009/01516
d D 1.48 00/08/01 09:21:25 staelin 50 49
c - Remove unnecessary tests for time>0 before calls to insertsort()
c - Add check that time > 0 in insertsort()
c - In tvsub(), replace while (tdiff->tv_usec < 0 ...) with an 
c   if (tdiff->tv_usec < 0 ...) { ...; assert(tdiff->tv_usec >= 0); }
c 
cC
cK34948
e
s 00005/00001/01520
d D 1.47 00/07/31 11:31:12 staelin 49 48
c - Flesh out print_results() a little bit
cC
cK37497
e
s 00020/00020/01501
d D 1.46 00/07/30 11:46:17 staelin 48 47
c - Change type of "iterations" from uint64 to iter_t, which is a u_long
cC
cK28499
e
s 00081/00052/01440
d D 1.45 00/07/30 10:46:52 staelin 47 46
c - Change handshaking between parent and child processes.  All signals are now a single
c   character, which is guaranteed to be atomic in all pipes.  In addition, the parent
c   allows a single child to reports its results at a time, so there is no danger of
c   results vectors getting intermingled.
c - Added additional test in benchmp_interval to ensure that our times aren't negative;
c   and it we have done over a million iterations and the time is still negative, then
c   we give up.  (Time can become negative once you subtract off the expected overhead)
cC
cK28342
e
s 00009/00009/01483
d D 1.44 00/07/27 17:21:00 staelin 46 45
c - Some small cleanup to benchmp_interval to ensure things happen in the right order.
c - Small tweak to l_overhead and two_op to cleanup unnecessary complexity in the code.
cC
cK27463
e
s 00080/00160/01412
d D 1.43 00/07/26 18:09:56 staelin 45 44
c - Removed setjmp/longjmp with signal handling in benchmp.  Now signal handler sets
c   a global status parameter which is polled by benchmp_parent to see if it should exit.
c - Dramatically simplified benchmp_child by using benchmp_interval() internally instead
c   of duplicating code.  Removed measurement() and bench() routines, and gutted most of
c   benchmp_child().  No longer have two different sets of code which accomplish the
c   same task.
c - Changed "return value;" to "return (value);" as per Larry's request
cC
cK26460
e
s 00002/00005/01570
d D 1.42 00/07/25 13:48:38 staelin 44 43
c - fix printout of nanosecond values so we report some significant digits
c   (this is especially important as processor clock ticks become smaller than
c   one nanosecond and we report times that are small multiples of one clock tick)
c - remove #if !defined(hpux) ... test for #define RUSAGE since the check for
c   getrusage is now done in build
cC
cK18281
e
s 00124/00093/01451
d D 1.41 00/07/04 14:56:02 staelin 43 42
c - Change the result handling system to use a global pointer to a result_t structure
c   rather than a static global result_t structure.  This makes it easier for us to
c   have variable sized global results, which are needed to support the "repetitions"
c   argument of benchmp
c - Add new repetitions argument to benchmp which specifies the number of times the
c   experiment will be run.  The default is TRIES (11).
c - Add new warmup argument to benchmp which specifies the number of microseconds that
c   the parent sleeps after receiving all "ready" signals from children.  The default
c   is 0.
cC
cK24410
e
s 00008/00000/01536
d D 1.40 00/05/31 16:16:18 staelin 42 40
c Put unnecessary print statements in #ifdef _DEBUG so the extraneous output won't confuse
c the result parsing scripts during normal operation
cC
cK63338
cZ+03:00
e
s 00135/00007/01401
d D 1.39 00/04/17 13:06:04 staelin 40 39
c This version contains a lot of changes:
c - the timing harness has been updated to make the timing interval calculations
c   more stable:
c 	- use the minimum time during timing resolution calculations in time_N
c 	- fixed a bug in test_time which incorrectly calculated the absolute
c 	  value of the difference of two unsigned integers
c - the addition of a whole new interface to the benchmp timing harness for use
c   by benchmarks which cannot return in the normal fashion, such as the page fault
c   handler that infinite loops.  
cC
cK54010
e
s 00119/00076/01289
d D 1.38 00/03/01 14:34:24 staelin 39 38
c - Add alarm()-based harness to kill errant child processes so we don't
c   wait() forever.
c - Adjust indentation
c - Add lmbench_usage() to report program usage and error exit(-1)
cC
cK41066
e
s 00445/00017/00920
d D 1.37 00/02/23 11:15:40 staelin 38 37
c Draft benchmp() timing harness.  This new timing harness is implemented as a function
c rather than a macro.  Since the function cannot access local variables and other state
c as easily as a macro, we had to create the notion of a 'cookie' which is passed to the
c benchmark.  The system may store a pointer in the cookie which can access various bits
c of state that are used within the benchmark.  In addition, there are two optional parameters,
c initialize() and cleanup() which are used to initialize and cleanup any state required
c by the benchmark.  In addition, we made it so that the benchmarking is all done in child
c processes.  This should enable us to incorporate 'broken' benchmarks such as lat_pagefault
c which never terminate into the harness (we simply kill the child process after it has 
c reported the results).
c 
c Various changes to reflect the new result_t structure.
cC
cK20492
e
s 00115/00021/00822
d D 1.36 00/02/02 09:57:42 staelin 37 36
c - Added code to handle bad results in the various
c   result handling routines.
c - Cleaned up some variable/function types to keep
c   things uniform
c - Added some code for Windows timing
cC
cHhpli8.hpli.hpl.hp.com
cK16347
cZ+02:00
e
s 00010/00000/00833
d D 1.35 99/03/20 23:38:34 lm 36 35
c print_results() function.
cC
cK57041
cZ-08:00
e
s 00001/00001/00832
d D 1.34 98/07/21 18:41:28 lm 35 34
c ftiming bug caused core dumps.
cK45967
e
s 00014/00003/00819
d D 1.33 98/07/02 17:33:18 lm 34 33
c Glibc won't let you assign stderr to a global.
cK45976
e
s 00004/00003/00818
d D 1.32 98/06/29 22:37:42 lm 33 32
c Redo to compile clean with -Wall.
cHlm.bitmover.com
cK16719
e
s 00012/00020/00809
d D 1.31 98/06/26 10:01:23 lm 32 31
c Carl's bug fix for the alpha mhz.
cHwork
cK18041
cZ-07:00
e
s 00131/00112/00698
d D 1.30 98/05/07 15:34:47 staelin 31 30
c - changed result_t to a structure, and updated relevent routines
c - added saved state for results, and save_median() save_minimum() routines
c - fixed a bug in l_overhead() experimentation and calculation
c - changed #ifdef hpux to #if defined(hpux) || defined(__hpux)
cHhpisc8.lempel
cK30075
cZ-00:00
e
s 00020/00025/00790
d D 1.29 98/03/06 12:01:09 lm 30 29
c simplify; fix bug in sort. (Carl).
cK05444
e
s 00002/00003/00813
d D 1.28 97/11/19 21:10:51 lm 29 28
c some carl thing.
cK04882
e
s 00008/00007/00808
d D 1.27 97/10/31 18:06:23 lm 28 27
c use_result -> use_int/pointer
cK10037
e
s 00049/00038/00766
d D 1.26 97/10/30 18:37:23 lm 27 26
c From Carl.
cK03618
cZ-08:00
e
s 00002/00002/00802
d D 1.25 97/10/25 10:53:06 lm 26 25
c carl's stuff
cK39735
e
s 00044/00022/00760
d D 1.24 97/10/19 23:40:55 lm 25 24
c fix a few bugs.
cK37952
e
s 00029/00013/00753
d D 1.23 97/06/25 10:25:01 lm 24 23
c ifdef TOUCH
cK51056
e
s 00003/00008/00763
d D 1.22 97/06/23 23:27:09 lm 23 22
c carl's diffs.
cK34473
e
s 00001/00001/00770
d D 1.21 97/06/16 19:18:52 lm 22 21
c 5000
cK38651
e
s 00009/00003/00762
d D 1.20 97/06/16 19:05:50 lm 21 20
c lint
cK39733
e
s 00003/00003/00762
d D 1.19 97/06/15 23:13:12 lm 20 19
c namespace
cK28694
e
s 00011/00009/00754
d D 1.18 97/06/15 22:38:58 lm 19 18
c lint
cK29334
e
s 00224/00013/00539
d D 1.17 97/06/14 18:23:18 lm 18 17
c more loop junk.
cK26570
e
s 00044/00032/00508
d D 1.16 97/06/14 12:20:26 lm 17 16
c carl's changes.
cK25545
e
s 00046/00041/00494
d D 1.15 97/06/13 20:26:59 lm 16 15
c enough
cK11116
e
s 00111/00048/00424
d D 1.14 97/06/12 21:30:06 lm 15 14
c new bench.h macros.
cK09595
e
s 00031/00010/00441
d D 1.13 97/04/23 22:15:40 lm 14 13
c mostly just some stats in micro().
cK52190
cZ-07:00
e
s 00001/00000/00450
d D 1.12 97/01/27 14:06:50 lm 13 12
c lint
cK24509
e
s 00028/00004/00422
d D 1.11 96/12/16 12:32:12 lm 12 11
c *** empty log message ***
cK23598
e
s 00025/00003/00401
d D 1.10 96/11/13 16:09:37 lm 11 10
c tuning.
cK47690
e
s 00207/00138/00197
d D 1.9 96/11/11 03:36:51 lm 10 9
c Auto adjusting changes.
cK17037
e
s 00041/00003/00294
d D 1.8 96/11/08 20:06:19 lm 9 8
c gcc -Wall cleanup.
cK64643
e
s 00004/00001/00293
d D 1.7 96/01/22 23:58:23 lm 8 7
c make adjust return the new timespent.
cK24087
cZ-08:00
e
s 00031/00000/00263
d D 1.6 95/08/24 20:30:30 lm 7 6
c delta/Delta
cK14753
e
s 00007/00002/00256
d D 1.5 95/08/22 15:32:31 lm 6 5
c automagic adjustment of output.
cK40255
cZ-07:00
e
s 00006/00001/00252
d D 1.4 95/03/10 18:19:39 lm 5 4
c lint
cK31472
e
s 00014/00000/00239
d D 1.3 95/02/14 10:57:34 lm 4 3
c add nano interface.
cK24794
e
s 00212/00029/00027
d D 1.2 94/11/18 00:52:52 lm 3 2
c getting close to net release.
cK07298
cZ-08:00
e
s 00056/00000/00000
d D 1.1 92/06/24 14:09:15 lm 2 1
c date and time created 92/06/24 21:09:15 by lm
cK08376
e
s 00000/00000/00000
d D 1.0 92/06/24 14:09:14 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK13663
cPsrc/lib_timing.c
cR4ef3c93154a38206
cV4
cX0x21
cZ-07:00
e
u
U
f e 0
f x 0x21
t
T
I 2
/*
D 3
 * %W% %G%
E 3
I 3
D 10
 * $Id$
E 10
I 10
 * a timing utilities library
E 10
 *
D 10
 * Copyright (c) 1994 Larry McVoy.   
E 10
I 10
 * Requires 64bit integers to work.
E 10
 *
D 10
 * All output goes to stderr.
E 10
I 10
D 31
 * $Id$
E 31
I 31
D 32
 * $Id: lib_timing.c,v 1.29 1998/03/06 20:01:09 lm Exp $
E 32
I 32
 * %W% %@%
E 32
E 31
 *
I 55
 * Copyright (c) 2000 Carl Staelin.
E 55
D 32
 * Copyright (c) 1994-1996 Larry McVoy.
E 32
I 32
 * Copyright (c) 1994-1998 Larry McVoy.
I 55
 * Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
E 55
E 32
E 10
E 3
 */
I 3
D 10
#include "bench.h"
E 10
D 15
#include <stdio.h>
E 3
#include <signal.h>
I 3
#include <unistd.h>
E 3
#include <sys/types.h>
#include <sys/time.h>
I 10
#include "timing.h"
E 15
I 14
#define	 _LIB /* bench.h needs this */
E 14
#include "bench.h"
I 38
D 45
#include <setjmp.h>
E 45
E 38
E 10

I 43
/* #define _DEBUG */

E 43
I 5
D 10
#ifdef	sun
extern	int	gettimeofday();
extern	int	fprintf();
#endif

E 5
I 3
#ifdef	RUSAGE
#include <sys/resource.h>

#define	secs(tv)	(tv.tv_sec + tv.tv_usec / 1000000.0)
#endif

E 10
#define	nz(x)	((x) == 0 ? 1 : (x))
D 10
#define	MB	(1024*1024.0)
#define	KB	(1024.0)
E 10

D 10
#ifdef	RUSAGE
E 10
I 10
/*
 * I know you think these should be 2^10 and 2^20, but people are quoting
 * disk sizes in powers of 10, and bandwidths are all power of ten.
 * Deal with it.
 */
#define	MB	(1000*1000.0)
#define	KB	(1000.0)
E 10

D 10
#define	mine(f)		(ru_stop.f - ru_start.f)
E 10
I 10
D 15
static struct timeval start_tv, stop_tv;
E 15
I 15
D 33
static struct timeval start_tv, stop_tv, dummy_tv;
E 33
I 33
D 48
static struct timeval start_tv, stop_tv;
E 33
E 15
D 34
FILE	*ftiming = stderr;
E 34
I 34
FILE		*ftiming;
E 34
D 26
static	uint64	dummy;
E 26
I 26
D 27
uint64		use_result_dummy;
E 27
I 27
uint64		use_result_dummy;	/* !static for optimizers. */
E 27
E 26
I 15
D 19
static	double	timing_overhead = 0;
E 19
static	uint64	iterations;
I 19
static	void	init_timing(void);
E 48
I 48
static struct timeval 	start_tv, stop_tv;
FILE			*ftiming;
static volatile uint64	use_result_dummy;
static		uint64	iterations;
static		void	init_timing(void);
E 48
E 19
E 15
E 10

I 31
#if defined(hpux) || defined(__hpux)
#include <sys/mman.h>
#endif
E 31
I 15

I 21
D 30
#ifndef	hpux
E 30
I 30
D 37
#if !defined(hpux) && !defined(__hpux)
E 37
I 37
D 44
#if !defined(hpux) && !defined(__hpux) && !defined(WIN32)
E 37
E 30
E 21
#define RUSAGE
I 21
#endif
E 44
E 21
#ifdef	RUSAGE
#include <sys/resource.h>
D 20
#define	secs(tv)	(tv.tv_sec + tv.tv_usec / 1000000.0)
E 20
I 20
#define	SECS(tv)	(tv.tv_sec + tv.tv_usec / 1000000.0)
E 20
#define	mine(f)		(int)(ru_stop.f - ru_start.f)

D 19
static struct rusage ru_start, ru_stop, ru_dummy;
E 19
I 19
static struct rusage ru_start, ru_stop;
E 19

void
rusage(void)
{
	double  sys, user, idle;
	double  per;

D 20
	sys = secs(ru_stop.ru_stime) - secs(ru_start.ru_stime);
	user = secs(ru_stop.ru_utime) - secs(ru_start.ru_utime);
E 20
I 20
	sys = SECS(ru_stop.ru_stime) - SECS(ru_start.ru_stime);
	user = SECS(ru_stop.ru_utime) - SECS(ru_start.ru_utime);
E 20
	idle = timespent() - (sys + user);
	per = idle / timespent() * 100;
I 34
	if (!ftiming) ftiming = stderr;
E 34
	fprintf(ftiming, "real=%.2f sys=%.2f user=%.2f idle=%.2f stall=%.0f%% ",
	    timespent(), sys, user, idle, per);
	fprintf(ftiming, "rd=%d wr=%d min=%d maj=%d ctx=%d\n",
	    mine(ru_inblock), mine(ru_oublock),
	    mine(ru_minflt), mine(ru_majflt),
	    mine(ru_nvcsw) + mine(ru_nivcsw));
}

#endif	/* RUSAGE */
I 38

D 39
jmp_buf benchmp_sigchld_env;
E 39
I 39
void
lmbench_usage(int argc, char *argv[], char* usage)
{
	fprintf(stderr,"Usage: %s %s", argv[0], usage);
	exit(-1);
}

I 52
static int	benchmp_sigterm_received;
static int	benchmp_sigchld_received;
E 52
D 45
jmp_buf	benchmp_sigchld_env;
pid_t	benchmp_sigalrm_pid;
int	benchmp_sigalrm_timeout;
E 45
I 45
static pid_t	benchmp_sigalrm_pid;
static int	benchmp_sigalrm_timeout;
D 52
static int	benchmp_child_died;
E 52
I 52
void (*benchmp_sigterm_handler)(int);
E 52
E 45
E 39
void (*benchmp_sigchld_handler)(int);
I 39
void (*benchmp_sigalrm_handler)(int);

E 39
D 52
void benchmp_sigchld(int signo)
E 52
I 52
void
benchmp_sigterm(int signo)
{
	benchmp_sigterm_received = 1;
}

void
benchmp_sigchld(int signo)
E 52
{
	signal(SIGCHLD, SIG_IGN);
D 45
	longjmp(benchmp_sigchld_env, 1);
E 45
I 45
D 52
	benchmp_child_died = 1;
E 52
I 52
	benchmp_sigchld_received = 1;
I 54
#ifdef _DEBUG
	fprintf(stderr, "benchmp_sigchld handler\n");
#endif
E 54
E 52
E 45
}

I 39
D 52
void benchmp_sigalrm(int signo)
E 52
I 52
void
benchmp_sigalrm(int signo)
E 52
{
	signal(SIGALRM, SIG_IGN);
D 52
	kill(benchmp_sigalrm_pid, SIGKILL);
E 52
I 52
	kill(benchmp_sigalrm_pid, SIGTERM);
E 52
	/* 
	 * Since we already waited a full timeout period for the child
	 * to die, we only need to wait a little longer for subsequent
	 * children to die.
	 */
	benchmp_sigalrm_timeout = 1;
}

E 39
D 47
double bench(bench_f benchmark,
	     uint64 iterations,
I 43
	     int repetitions,
E 43
D 39
		int enough,
		void *cookie
		);
double measure(bench_f benchmark, uint64 iterations, void *cookie);
E 39
I 39
	     int enough,
	     void *cookie
	     );
double measure(bench_f benchmark, 
	       uint64 iterations, 
	       void *cookie
	       );

E 47
E 39
void 
benchmp_child(support_f initialize, 
D 39
		bench_f benchmark,
		support_f cleanup,
		int response, 
		int start_signal, 
		int exit_signal,
		int parallel, 
	        uint64 iterations,
		int enough,
		void* cookie
		);
E 39
I 39
	      bench_f benchmark,
	      support_f cleanup,
I 63
	      int childid,
E 63
	      int response, 
	      int start_signal, 
I 47
	      int result_signal, 
E 47
	      int exit_signal,
	      int parallel, 
D 48
	      uint64 iterations,
E 48
I 48
	      iter_t iterations,
E 48
I 43
	      int repetitions,
E 43
	      int enough,
	      void* cookie
	      );
E 39
void
D 39
benchmp_parent(	int response, 
		int start_signal, 
		int exit_signal, 
		int parallel, 
	        uint64 iterations,
		int enough
		);
E 39
I 39
benchmp_parent(int response, 
	       int start_signal, 
I 47
	       int result_signal, 
E 47
	       int exit_signal, 
I 51
	       pid_t* pids,
E 51
	       int parallel, 
D 48
	       uint64 iterations,
E 48
I 48
	       iter_t iterations,
E 48
I 43
	       int warmup,
	       int repetitions,
E 43
	       int enough
	       );
E 39

I 43
int
sizeof_result(int repetitions);

E 43
D 51
void benchmp(support_f initialize, 
D 39
		bench_f benchmark,
		support_f cleanup,
		int enough, 
		int parallel,
		void* cookie
		)
E 39
I 39
	     bench_f benchmark,
	     support_f cleanup,
	     int enough, 
	     int parallel,
I 43
	     int warmup,
	     int repetitions,
E 43
	     void* cookie)
E 51
I 51
void 
benchmp(support_f initialize, 
	bench_f benchmark,
	support_f cleanup,
	int enough, 
	int parallel,
	int warmup,
	int repetitions,
	void* cookie)
E 51
E 39
{
D 48
	uint64		iterations = 1;
E 48
I 48
	iter_t		iterations = 1;
E 48
	double		result = 0.;
	double		usecs;
D 51
	long		i;
E 51
I 51
	long		i, j;
E 51
	pid_t		pid;
	pid_t		*pids = NULL;
	int		response[2];
	int		start_signal[2];
I 47
	int		result_signal[2];
E 47
	int		exit_signal[2];
	int		need_warmup;
	fd_set		fds;
	struct timeval	timeout;

#ifdef _DEBUG
D 39
fprintf(stderr, "benchmp(0x%x, 0x%x, 0x%x, %d, %d, 0x%x): entering\n", (unsigned int)initialize, (unsigned int)benchmark, (unsigned int)cleanup, enough, parallel, (unsigned int)cookie);
E 39
I 39
	fprintf(stderr, "benchmp(0x%x, 0x%x, 0x%x, %d, %d, 0x%x): entering\n", (unsigned int)initialize, (unsigned int)benchmark, (unsigned int)cleanup, enough, parallel, (unsigned int)cookie);
E 39
#endif
	enough = get_enough(enough);

	/* initialize results */
	settime(0);
	save_n(1);

	if (parallel > 1) {
		/* Compute the baseline performance */
D 43
		benchmp(initialize, benchmark, cleanup, enough, 1, cookie);
E 43
I 43
D 51
		benchmp(initialize, benchmark, cleanup, enough, 1, warmup, repetitions, cookie);
E 51
I 51
		benchmp(initialize, benchmark, cleanup, 
			enough, 1, warmup, repetitions, cookie);

		/* if we can't even do a single job, then give up */
		if (gettime() == 0)
			return;
E 51
I 47

		/* calculate iterations for 1sec runtime */
		iterations = get_n();
		if (enough < SHORT) {
			double tmp = (double)SHORT * (double)get_n();
			tmp /= (double)gettime();
D 48
			iterations = (uint64)tmp + 1;
E 48
I 48
			iterations = (iter_t)tmp + 1;
E 48
		}
I 51
		settime(0);
		save_n(1);
E 51
E 47
E 43
	}

	/* Create the necessary pipes for control */
	if (pipe(response) < 0
	    || pipe(start_signal) < 0
I 47
	    || pipe(result_signal) < 0
E 47
	    || pipe(exit_signal) < 0) {
I 42
#ifdef _DEBUG
E 42
		fprintf(stderr, "BENCHMP: Could not create control pipes\n");
I 42
#endif /* _DEBUG */
E 42
		return;
	}
I 39

E 39
	/* fork the necessary children */
I 45
D 52
	benchmp_child_died = 0;
E 45
	signal(SIGTERM, SIG_IGN);
	benchmp_sigchld_handler = signal(SIGCHLD, benchmp_sigchld);
E 52
I 52
	benchmp_sigchld_received = 0;
	benchmp_sigterm_received = 0;
	benchmp_sigterm_handler = signal(SIGTERM, benchmp_sigterm);
	benchmp_sigterm_handler = signal(SIGCHLD, benchmp_sigchld);
E 52
	pids = (pid_t*)malloc(parallel * sizeof(pid_t));
I 56
	if (!pids) return;
E 56
I 51
	bzero((void*)pids, parallel * sizeof(pid_t));
E 51
D 45
	if (setjmp(benchmp_sigchld_env)) {
		/* error exit, child died unexpectedly */
I 42
#ifdef _DEBUG
E 42
		fprintf(stderr, "BENCHMP: Child died unexpectedly\n");
I 42
#endif /* _DEBUG */
E 42
		settime(0);
		save_n(1);
		return;
	}
E 45
I 39

E 39
	for (i = 0; i < parallel; ++i) {
I 52
		if (benchmp_sigterm_received)
			goto error_exit;
E 52
#ifdef _DEBUG
D 39
fprintf(stderr, "benchmp(0x%x, 0x%x, 0x%x, %d, %d, 0x%x): creating child %d\n", (unsigned int)initialize, (unsigned int)benchmark, (unsigned int)cleanup, enough, parallel, (unsigned int)cookie, i);
E 39
I 39
		fprintf(stderr, "benchmp(0x%x, 0x%x, 0x%x, %d, %d, 0x%x): creating child %d\n", (unsigned int)initialize, (unsigned int)benchmark, (unsigned int)cleanup, enough, parallel, (unsigned int)cookie, i);
E 39
#endif
D 52
		switch(pid = fork()) {
E 52
I 52
		switch(pids[i] = fork()) {
E 52
		case -1:
			/* could not open enough children! */
I 42
#ifdef _DEBUG
E 42
			fprintf(stderr, "BENCHMP: fork() failed!\n");
I 42
#endif /* _DEBUG */
E 42
D 51
			/* clean up and kill all children */
E 51
I 51
D 52
			/* give the children a chance to clean up gracefully */
E 51
			signal(SIGCHLD, SIG_IGN);
D 51
			while (i > 0) {
D 39
			  kill(pids[--i], SIGKILL);
			  waitpid(pids[i], NULL, 0);
E 39
I 39
				kill(pids[--i], SIGKILL);
				waitpid(pids[i], NULL, 0);
E 51
I 51
			for (j = 0; j < i; ++j) {
				kill(pids[j], SIGTERM);
E 51
E 39
			}
E 52
D 51
			if (cleanup)
D 39
			  (*cleanup)(cookie);
E 39
I 39
				(*cleanup)(cookie);
E 39
			if (pids) free(pids);
			exit(-1);
E 51
I 51
			goto error_exit;
E 51
		case 0:
			/* If child */
			close(response[0]);
			close(start_signal[1]);
I 47
			close(result_signal[1]);
E 47
			close(exit_signal[1]);
			benchmp_child(initialize, 
				      benchmark, 
				      cleanup, 
I 63
				      i,
E 63
				      response[1], 
				      start_signal[0], 
I 47
				      result_signal[0], 
E 47
				      exit_signal[0],
				      enough,
				      iterations,
				      parallel,
I 43
				      repetitions,
E 43
				      cookie
D 39
				      );
E 39
I 39
				);
I 40
			exit(0);
E 40
E 39
		default:
D 52
			pids[i] = pid;
E 52
			break;
		}
	}
	close(response[1]);
	close(start_signal[0]);
I 47
	close(result_signal[0]);
E 47
	close(exit_signal[0]);
	benchmp_parent(response[0], 
		       start_signal[1], 
I 47
		       result_signal[1], 
E 47
D 51
		       exit_signal[1], 
E 51
I 51
		       exit_signal[1],
		       pids,
E 51
		       parallel, 
		       iterations,
I 43
		       warmup,
		       repetitions,
E 43
		       enough
D 39
		       );
E 39
I 39
		);
I 52
	goto cleanup_exit;
E 52
E 39

I 51
error_exit:
I 52
	/* give the children a chance to clean up gracefully */
	signal(SIGCHLD, SIG_IGN);
	while (--i >= 0) {
		kill(pids[i], SIGTERM);
	}

cleanup_exit:
E 52
E 51
D 39
	/* clean up and kill all children */
	/*
	 * Note that children themselves SHOULD exit, and
	 * Killing them as below could prevent them from
	 * cleanup up subprocesses, etc... so this is
	 * commented out...should have some kind of timeout
	 * and eventually kill them if they seem hung.
E 39
I 39
	/* 
	 * Clean up and kill all children
	 *
	 * NOTE: the children themselves SHOULD exit, and
	 *   Killing them could prevent them from
	 *   cleanup up subprocesses, etc... So, we only
	 *   want to kill child processes when it appears
	 *   that they will not die of their own accord.
	 *   We wait twice the timing interval plus two seconds
	 *   for children to die.  If they haven't died by 
	 *   that time, then we start killing them.
E 39
	 */
I 39
D 48
	benchmp_sigalrm_timeout = (int)((2 * enough)/(uint64)1000000) + 2;
E 48
I 48
	benchmp_sigalrm_timeout = (int)((2 * enough)/1000000) + 2;
E 48
	if (benchmp_sigalrm_timeout < 5)
		benchmp_sigalrm_timeout = 5;
E 39
	signal(SIGCHLD, SIG_IGN);
I 39
	signal(SIGALRM, SIG_IGN);
E 39
D 51
	while (i > 0) {
D 39
	  i--;
	  /*	  kill(pids[i], SIGKILL); */
	  waitpid(pids[i], NULL, 0);
E 39
I 39
		i--;
E 51
I 51
	while (i-- > 0) {
E 51
		/* wait timeout seconds for child to die, then kill it */
		benchmp_sigalrm_pid = pids[i];
		signal(SIGALRM, benchmp_sigalrm);
		alarm(benchmp_sigalrm_timeout); 

		waitpid(pids[i], NULL, 0);

		alarm(0);
		signal(SIGALRM, SIG_IGN);
E 39
	}

	if (pids) free(pids);
#ifdef _DEBUG
D 39
fprintf(stderr, "benchmp(0x%x, 0x%x, 0x%x, %d, %d, 0x%x): exiting\n", (unsigned int)initialize, (unsigned int)benchmark, (unsigned int)cleanup, enough, parallel, (unsigned int)cookie);
E 39
I 39
	fprintf(stderr, "benchmp(0x%x, 0x%x, 0x%x, %d, %d, 0x%x): exiting\n", (unsigned int)initialize, (unsigned int)benchmark, (unsigned int)cleanup, enough, parallel, (unsigned int)cookie);
E 39
#endif
}

D 45
double bench(bench_f benchmark,
	     uint64 iterations,
D 43
		int enough,
		void *cookie
		)
E 43
I 43
	     int repetitions,
	     int enough,
	     void *cookie
	)
E 43
{
	long i, N;
	double result;
D 43
	result_t r;
E 43

#ifdef _DEBUG
D 39
fprintf(stderr, "bench(0x%x, %d, 0x%x): entering\n", (unsigned int)benchmark, enough, (unsigned int)cookie);
E 39
I 39
	fprintf(stderr, "bench(0x%x, %d, 0x%x): entering\n", (unsigned int)benchmark, enough, (unsigned int)cookie);
E 39
#endif
D 43
	insertinit(&r);
	N = (enough == 0 || get_enough(enough) <= 100000) ? TRIES : 1;
E 43
I 43
	N = (enough == 0 || get_enough(enough) <= 100000) ? repetitions : 1;
E 43
	/* warm the cache */
	if (enough < LONGER) {
		result = measure(benchmark, 1, cookie);
	}
	for (i = 0; i < N; ++i) {
		do {
			result = measure(benchmark, iterations, cookie);
			if (result < 0.99 * enough
			    || result > 1.2 * enough) {
				if (result > 150.) {
					double	tmp = iterations / result;
					tmp *= 1.1 * enough;
					iterations = (uint64)(tmp + 1);
				} else {
					if (iterations > (uint64)1<<40) {
						result = 0.;
						break;
					}
					iterations <<= 3;
				}
			}
		} while(result < 0.95 * enough);
		if (gettime() > 0)
D 43
			insertsort(gettime(), get_n(), &r);
E 43
I 43
			insertsort(gettime(), get_n(), get_results());
E 43
#ifdef _DEBUG
D 39
fprintf(stderr, "bench(0x%x, %d, 0x%x): i=%d, gettime()=%lu, get_n()=%d\n", (unsigned int)benchmark, enough, (unsigned int)cookie, i, (unsigned long)gettime(), (int)get_n());
E 39
I 39
		fprintf(stderr, "bench(0x%x, %d, 0x%x): i=%d, gettime()=%lu, get_n()=%d\n", (unsigned int)benchmark, enough, (unsigned int)cookie, i, (unsigned long)gettime(), (int)get_n());
E 39
#endif
	}
D 43
	save_results(&r);
E 43
}

double measure(bench_f benchmark, uint64 iterations, void *cookie)
{
D 39
  double result = 0.;
E 39
I 39
	double result = 0.;
E 39

D 39
  start(0);
  (*benchmark)(iterations, cookie);
  result = stop(0,0);
  save_n(iterations);
  result -= t_overhead() + get_n() * l_overhead();
  settime(result >= 0. ? (uint64)result : 0.);
E 39
I 39
	start(0);
	(*benchmark)(iterations, cookie);
	result = stop(0,0);
	save_n(iterations);
	result -= t_overhead() + get_n() * l_overhead();
	settime(result >= 0. ? (uint64)result : 0.);
E 39

#ifdef _DEBUG
D 39
fprintf(stderr, "measure(0x%x, %lu, 0x%x): result=%G\n", (unsigned int)benchmark, (unsigned long)iterations, (unsigned int)cookie, result);
E 39
I 39
	fprintf(stderr, "measure(0x%x, %lu, 0x%x): result=%G\n", (unsigned int)benchmark, (unsigned long)iterations, (unsigned int)cookie, result);
E 39
#endif

D 39
  return result;
E 39
I 39
	return result;
E 39
}
E 45
D 51

I 40
typedef enum { warmup, timing_interval, cooldown } benchmp_state;

typedef struct {
	benchmp_state	state;
	support_f	initialize;
	bench_f		benchmark;
	support_f	cleanup;
	int		response;
	int		start_signal;
I 47
	int		result_signal;
E 47
	int		exit_signal;
	int		enough;
D 48
        uint64		iterations;
E 48
I 48
        iter_t		iterations;
E 48
	int		parallel;
I 43
        int		repetitions;
E 43
	void*		cookie;
	int		iterations_batch;
	int		need_warmup;
	long		i;
D 43
	result_t	r;
E 43
I 43
	int		r_size;
	result_t*	r;
E 43
} benchmp_child_state;

static benchmp_child_state _benchmp_child_state;

void*
benchmp_getstate()
{
D 45
	return (void*)&_benchmp_child_state;
E 45
I 45
	return ((void*)&_benchmp_child_state);
E 45
}

D 48
uint64
E 48
I 48
iter_t
E 48
benchmp_interval(void* _state)
{
I 47
	char		c;
E 47
D 48
	uint64		iterations;
E 48
I 48
	iter_t		iterations;
E 48
	double		result;
	fd_set		fds;
	struct timeval	timeout;
	benchmp_child_state* state = (benchmp_child_state*)_state;

	result = stop(0,0);
	save_n(state->iterations);
	result -= t_overhead() + get_n() * l_overhead();
	settime(result >= 0. ? (uint64)result : 0.);

	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	FD_ZERO(&fds);
D 46
	iterations = state->iterations;
E 46

	switch (state->state) {
	case warmup:
		iterations = state->iterations_batch;
		if (state->need_warmup) {
			state->need_warmup = 0;
			/* send 'ready' */
D 47
			write(state->response, &state->i, sizeof(int));
E 47
I 47
			write(state->response, &c, sizeof(char));
E 47
		}
		FD_SET(state->start_signal, &fds);
		select(state->start_signal+1, &fds, NULL,
		       NULL, &timeout);
		if (FD_ISSET(state->start_signal, &fds)) {
			state->state = timing_interval;
I 43
D 47
			/* find out how much work to do */
			read(state->start_signal, &state->iterations, sizeof(uint64));
E 47
I 47
			read(state->start_signal, &c, sizeof(char));
E 47
			iterations = state->iterations;
E 43
		}
		break;
	case timing_interval:
I 46
		iterations = state->iterations;
E 46
		if (state->parallel > 1 || result > 0.95 * state->enough) {
D 50
			if (gettime() > 0)
D 43
				insertsort(gettime(), get_n(), &state->r);
E 43
I 43
				insertsort(gettime(), get_n(), get_results());
E 50
I 50
			insertsort(gettime(), get_n(), get_results());
E 50
E 43
			state->i++;
			/* we completed all the experiments, return results */
D 43
			if (state->i >= TRIES) {
E 43
I 43
			if (state->i >= state->repetitions) {
E 43
				state->state = cooldown;
			}
		}
		if (state->parallel == 1 
		    && (result < 0.99 * state->enough || result > 1.2 * state->enough)) {
			if (result > 150.) {
				double tmp = iterations / result;
				tmp *= 1.1 * state->enough;
D 48
				iterations = (uint64)(tmp + 1);
E 48
I 48
				iterations = (iter_t)(tmp + 1);
E 48
			} else {
D 46
				if (iterations > (uint64)1<<40) {
					result = 0.;
E 46
I 46
				iterations <<= 3;
D 47
				if (iterations > (uint64)1<<27) {
E 47
I 47
				if (iterations > 1<<27
				    || result < 0. && iterations > 1<<20) {
E 47
E 46
					state->state = cooldown;
				}
D 46
				iterations <<= 3;
E 46
			}
D 46
			state->iterations = iterations;
E 46
		}
D 47
		if (state->state == cooldown) {
			/* send results and 'done' */
D 43
			write(state->response, (void*)&state->r, sizeof(result_t));
E 43
I 43
			write(state->response, (void*)get_results(), state->r_size);
I 46
			iterations = state->iterations_batch;
E 46
E 43
		} else {
E 47
I 47
		if (state->state != cooldown) {
E 47
I 46
			state->iterations = iterations;
E 46
D 47
			break;
E 47
I 47
		} else {
			/* send 'done' */
			write(state->response, (void*)&c, sizeof(char));
			iterations = state->iterations_batch;
E 47
		}
I 47
		break;
E 47
	case cooldown:
		iterations = state->iterations_batch;
D 47
		FD_SET(state->exit_signal, &fds);
		select(state->exit_signal+1, &fds, NULL, NULL, &timeout);
		if (FD_ISSET(state->exit_signal, &fds)) {
			/* exit */
			close(state->response);
			close(state->start_signal);
			/* close(exit_signal); */
E 47
I 47
		FD_SET(state->result_signal, &fds);
		select(state->result_signal+1, &fds, NULL, NULL, &timeout);
		if (FD_ISSET(state->result_signal, &fds)) {
			/* 
			 * At this point all children have stopped their
			 * measurement loops, so we can block waiting for
			 * the parent to tell us to send our results back.
			 * From this point on, we will do no more "work".
			 */
			read(state->result_signal, (void*)&c, sizeof(char));
			write(state->response, (void*)get_results(), state->r_size);
E 47
			if (state->cleanup)
				(*state->cleanup)(state->cookie);
I 47

			/* Now wait for signal to exit */
			read(state->exit_signal, (void*)&c, sizeof(char));
E 47
			exit(0);
		}
	};
	start(0);
D 45
	return iterations;
E 45
I 45
	return (iterations);
E 45
}
E 40

void 
benchmp_child(support_f initialize, 
		bench_f benchmark,
		support_f cleanup,
		int response, 
		int start_signal, 
I 47
		int result_signal, 
E 47
		int exit_signal,
		int enough,
D 48
	        uint64 iterations,
E 48
I 48
	        iter_t iterations,
E 48
		int parallel, 
I 43
	        int repetitions,
E 43
		void* cookie
		)
{
D 48
	uint64		iterations_batch = (parallel > 1) ? get_n() : 1;
E 48
I 48
	iter_t		iterations_batch = (parallel > 1) ? get_n() : 1;
E 48
	double		result = 0.;
	double		usecs;
D 40
	long		i;
E 40
I 40
	long		i = 0;
E 40
D 43
	result_t 	r;
E 43
	int		need_warmup;
	fd_set		fds;
	struct timeval	timeout;

I 40
	_benchmp_child_state.state = warmup;
	_benchmp_child_state.initialize = initialize;
	_benchmp_child_state.benchmark = benchmark;
	_benchmp_child_state.cleanup = cleanup;
	_benchmp_child_state.response = response;
	_benchmp_child_state.start_signal = start_signal;
I 47
	_benchmp_child_state.result_signal = result_signal;
E 47
	_benchmp_child_state.exit_signal = exit_signal;
	_benchmp_child_state.enough = enough;
	_benchmp_child_state.iterations = iterations;
	_benchmp_child_state.iterations_batch = iterations_batch;
	_benchmp_child_state.parallel = parallel;
I 43
	_benchmp_child_state.repetitions = repetitions;
E 43
	_benchmp_child_state.cookie = cookie;
	_benchmp_child_state.need_warmup = 1;
	_benchmp_child_state.i = 0;
D 43
	insertinit(&_benchmp_child_state.r);
E 43
I 43
	_benchmp_child_state.r_size = sizeof_result(repetitions);
	_benchmp_child_state.r = (result_t*)malloc(_benchmp_child_state.r_size);

	insertinit(_benchmp_child_state.r);
	set_results(_benchmp_child_state.r);
E 43

E 40
	need_warmup = 1;
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;

	signal(SIGCHLD, SIG_DFL);

	if (initialize)
		(*initialize)(cookie);

D 45
	/* work, and poll for 'start'  */
	FD_ZERO(&fds);
	while (!FD_ISSET(start_signal, &fds)) {
		result = measure(benchmark, iterations_batch, cookie);
		if (need_warmup) {
			need_warmup = 0;
			/* send 'ready' */
			write(response, &i, sizeof(int));
		}
		FD_SET(start_signal, &fds);
		select(start_signal+1, &fds, NULL,
		       NULL, &timeout);
	}

	/* find out how much work to do */
	read(start_signal, &iterations, sizeof(uint64));

E 45
	/* start experiments, collecting results */
I 43
	insertinit(_benchmp_child_state.r);
E 43
D 45
	if (parallel > 1) {
D 43
		insertinit(&r);
		for (i = 0; i < TRIES; ++i) {
E 43
I 43
		for (i = 0; i < repetitions; ++i) {
E 43
			result = measure(benchmark, iterations, cookie);
D 43
			insertsort(gettime(), get_n(), &r);
E 43
I 43
			insertsort(gettime(), get_n(), _benchmp_child_state.r);
E 43
		}
	} else {
D 40
		bench(benchmark, iterations,enough, cookie);
E 40
I 40
D 43
		bench(benchmark, iterations, enough, cookie);
E 40
		get_results(&r);
E 43
I 43
		bench(benchmark, iterations, repetitions, enough, cookie);
E 43
	}

	/* send results and 'done' */
D 43
	write(response, (void*)&r, sizeof(result_t));
E 43
I 43
#ifdef _DEBUG
	fprintf(stderr, "\tchild results: N=%d, gettime()=%lu, get_n()=%lu\n", _benchmp_child_state.r->N, (unsigned long)gettime(), (unsigned long)get_n());
	if (_benchmp_child_state.r->N < 0 || _benchmp_child_state.r->N > repetitions) 
		fprintf(stderr, "***Bad results!***\n");
	{
		int k;
		for (k = 0; k < _benchmp_child_state.r->N; ++k) {
			fprintf(stderr, "\t\t{%lu, %lu}\n", (unsigned long)_benchmp_child_state.r->v[k].u, (unsigned long)_benchmp_child_state.r->v[k].n);
		}
	}
#endif //_DEBUG
	write(response, _benchmp_child_state.r, _benchmp_child_state.r_size);
E 45

E 43
D 45
	/* keep working, poll for 'exit' */
	FD_ZERO(&fds);
	while (!FD_ISSET(exit_signal, &fds)) {
		result = measure(benchmark, iterations_batch, cookie);
		FD_SET(exit_signal, &fds);
		select(exit_signal+1, &fds, NULL, NULL, &timeout);
E 45
I 45
	start(0);
	while (1) {
		(*benchmark)(benchmp_interval(&_benchmp_child_state), cookie);
E 45
	}
D 45

	/* exit */
	close(response);
	close(start_signal);
	/* close(exit_signal); */

	if (cleanup)
		(*cleanup)(cookie);

	exit(0);
E 45
}

E 51
void
benchmp_parent(	int response, 
		int start_signal, 
I 47
		int result_signal, 
E 47
D 51
		int exit_signal, 
E 51
I 51
		int exit_signal,
		pid_t* pids,
E 51
		int parallel, 
D 48
	        uint64 iterations,
E 48
I 48
	        iter_t iterations,
E 48
I 43
		int warmup,
		int repetitions,
E 43
		int enough
		)
{
	int		i,j,k,l;
	int		bytes_read;
D 56
	result_t*	results;
	result_t*	merged_results;
E 56
I 56
	result_t*	results = NULL;
	result_t*	merged_results = NULL;
E 56
D 43
	result_t	scratch_results;
E 43
	unsigned char*	buf;
I 45
	fd_set		fds_read, fds_error;
	struct timeval	timeout;

D 52
	if (benchmp_child_died) {
E 52
I 52
	if (benchmp_sigchld_received || benchmp_sigterm_received) {
#ifdef _DEBUG
		fprintf(stderr, "benchmp_parent: entering, benchmp_sigchld_received=%d\n", benchmp_sigchld_received);
#endif
E 52
		goto error_exit;
	}
E 45

D 43
	results = (result_t*)malloc(parallel * sizeof(result_t));;
	bzero(results, parallel * sizeof(result_t));
E 43
I 43
	results = (result_t*)malloc(parallel * sizeof_result(repetitions));;
I 56
	merged_results = (result_t*)malloc(sizeof_result(parallel * repetitions));
	if (!results || !merged_results) return;
E 56
	bzero(results, parallel * sizeof_result(repetitions));
I 56
	bzero(merged_results, sizeof_result(parallel * repetitions));
	insertinit(merged_results);

E 56
I 45
D 62
	FD_ZERO(&fds_read);
	FD_ZERO(&fds_error);
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
E 45
E 43

E 62
D 43
	merged_results = (result_t*)malloc(parallel * sizeof(result_t));;
	bzero(merged_results, parallel * sizeof(result_t));
E 43
I 43
D 56
	merged_results = (result_t*)malloc(sizeof_result(parallel * repetitions));
	bzero(merged_results, sizeof_result(parallel * repetitions));
I 47
	insertinit(merged_results);
E 47
E 43

E 56
	/* Collect 'ready' signals */
D 47
	for (i = 0; i < parallel * sizeof(int); i += bytes_read) {
E 47
I 47
	for (i = 0; i < parallel * sizeof(char); i += bytes_read) {
E 47
I 45
		bytes_read = 0;
I 62
		FD_ZERO(&fds_read);
		FD_ZERO(&fds_error);
E 62
		FD_SET(response, &fds_read);
		FD_SET(response, &fds_error);

I 62
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
E 62
		select(response+1, &fds_read, NULL, &fds_error, &timeout);
D 52
		if (benchmp_child_died || FD_ISSET(response, &fds_error)) {
E 52
I 52
		if (benchmp_sigchld_received 
		    || benchmp_sigterm_received
		    || FD_ISSET(response, &fds_error)) 
		{
#ifdef _DEBUG
			fprintf(stderr, "benchmp_parent: ready, benchmp_sigchld_received=%d\n", benchmp_sigchld_received);
#endif
E 52
			goto error_exit;
		}
		if (!FD_ISSET(response, &fds_read)) {
			continue;
		}

E 45
D 47
		bytes_read = read(response, results, parallel * sizeof(int) - i);
E 47
I 47
		bytes_read = read(response, results, parallel * sizeof(char) - i);
E 47
		if (bytes_read < 0) {
I 52
#ifdef _DEBUG
			fprintf(stderr, "benchmp_parent: ready, bytes_read=%d, %s\n", bytes_read, strerror(errno));
#endif
E 52
D 45
			/* error exit */
			break;
E 45
I 45
			goto error_exit;
E 45
		}
	}

I 43
	/* let the children run for warmup microseconds */
D 45
	if (warmup > 0) 
		usleep(warmup);
E 45
I 45
	if (warmup > 0) {
D 62
		struct timeval timeout;
		timeout.tv_sec = warmup / 1000000;
		timeout.tv_usec = warmup % 1000000;
E 62
I 62
		struct timeval delay;
		delay.tv_sec = warmup / 100000;
		delay.tv_usec = warmup % 100000;
E 62

D 62
		select(0, NULL, NULL, NULL, &timeout);
E 62
I 62
		select(0, NULL, NULL, NULL, &delay);
E 62
	}
E 45

E 43
D 47
	/* calculate iterations for 1sec runtime */
	iterations = get_n();
D 40
	if (enough < SHORT) {
E 40
I 40
	if (enough < SHORT && parallel > 1) {
E 40
		double tmp = (double)SHORT * (double)get_n();
		tmp /= (double)gettime();
		iterations = (uint64)tmp + 1;
	}

E 47
	/* send 'start' signal */
D 47
	for (i = 0; i < parallel; ++i) {
		((uint64*)results)[i] = iterations;
	}
	write(start_signal, results, parallel * sizeof(uint64));
E 47
I 47
	write(start_signal, results, parallel * sizeof(char));
E 47

D 47
	/* Collect results and 'done' signals */
	for (i = 0, buf = (unsigned char*)results; 
	     i < parallel * sizeof(result_t); 
	     i += bytes_read, buf += bytes_read) {
E 47
I 47
	/* Collect 'done' signals */
	for (i = 0; i < parallel * sizeof(char); i += bytes_read) {
E 47
I 45
		bytes_read = 0;
I 62
		FD_ZERO(&fds_read);
		FD_ZERO(&fds_error);
E 62
		FD_SET(response, &fds_read);
		FD_SET(response, &fds_error);

I 62
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
E 62
		select(response+1, &fds_read, NULL, &fds_error, &timeout);
D 52
		if (benchmp_child_died || FD_ISSET(response, &fds_error)) {
E 52
I 52
		if (benchmp_sigchld_received 
		    || benchmp_sigterm_received
		    || FD_ISSET(response, &fds_error)) 
		{
#ifdef _DEBUG
D 56
			fprintf(stderr, "benchmp_parent: done, benchmp_child_diied=%d\n", benchmp_sigchld_received);
E 56
I 56
			fprintf(stderr, "benchmp_parent: done, benchmp_child_died=%d\n", benchmp_sigchld_received);
E 56
#endif
E 52
			goto error_exit;
		}
		if (!FD_ISSET(response, &fds_read)) {
			continue;
		}

E 45
D 43
		bytes_read = read(response, buf, parallel * sizeof(result_t) - i);
E 43
I 43
D 47
		bytes_read = read(response, buf, parallel * sizeof_result(repetitions) - i);
E 47
I 47
		bytes_read = read(response, results, parallel * sizeof(char) - i);
E 47
E 43
		if (bytes_read < 0) {
I 52
#ifdef _DEBUG
			fprintf(stderr, "benchmp_parent: done, bytes_read=%d, %s\n", bytes_read, strerror(errno));
#endif
E 52
D 45
			/* error exit */
E 45
I 42
D 47
#ifdef _DEBUG
E 42
			fprintf(stderr, "Only read %d/%d bytes of results!\n", i, parallel * sizeof(result_t));
I 42
#endif /* _DEBUG */
E 47
E 42
D 45
			break;
E 45
I 45
			goto error_exit;
I 47
		}
	}
E 47

I 47
	/* collect results */
	for (i = 0; i < parallel; ++i) {
		int n = sizeof_result(repetitions);
		buf = (unsigned char*)results + i * n;

I 62
		FD_ZERO(&fds_read);
		FD_ZERO(&fds_error);

E 62
		/* tell one child to report its results */
		write(result_signal, buf, sizeof(char));

		for (; n > 0; n -= bytes_read, buf += bytes_read) {
			bytes_read = 0;
			FD_SET(response, &fds_read);
			FD_SET(response, &fds_error);

I 62
			timeout.tv_sec = 1;
			timeout.tv_usec = 0;
E 62
			select(response+1, &fds_read, NULL, &fds_error, &timeout);
D 52
			if (benchmp_child_died || FD_ISSET(response, &fds_error)) {
E 52
I 52
			if (benchmp_sigchld_received 
			    || benchmp_sigterm_received
			    || FD_ISSET(response, &fds_error)) 
			{
#ifdef _DEBUG
				fprintf(stderr, "benchmp_parent: results, benchmp_sigchld_received=%d\n", benchmp_sigchld_received);
#endif
E 52
				goto error_exit;
			}
			if (!FD_ISSET(response, &fds_read)) {
				continue;
			}

			bytes_read = read(response, buf, n);
			if (bytes_read < 0) {
I 52
#ifdef _DEBUG
				fprintf(stderr, "benchmp_parent: results, bytes_read=%d, %s\n", bytes_read, strerror(errno));
#endif
E 52
				goto error_exit;
			}
E 47
E 45
		}
	}

	/* we allow children to die now, without it causing an error */
	signal(SIGCHLD, SIG_IGN);
	
	/* send 'exit' signals */
D 47
	write(exit_signal, results, sizeof(int));
E 47
I 47
	write(exit_signal, results, parallel * sizeof(char));
E 47

	/* Compute median time; iterations is constant! */
D 47
	insertinit(merged_results);
E 47
	for (i = 0; i < parallel; ++i) {
I 43
		result_t* r = (result_t*)((char*)results + i * sizeof_result(repetitions));
E 43
#ifdef _DEBUG
D 39
fprintf(stderr, "\tresults[%d]: N=%d, gettime()=%lu, get_n()=%lu\n", i, results[i].N, (unsigned long)gettime(), (unsigned long)get_n());
if (results[i].N < 0 || results[i].N > TRIES) fprintf(stderr, "***Bad results!***\n");
{
for (k = 0; k < results[i].N; ++k) {
fprintf(stderr, "\t\t{%lu, %lu}\n", (unsigned long)results[i].v[k].u, (unsigned long)results[i].v[k].n);
}
}
E 39
I 39
D 43
		fprintf(stderr, "\tresults[%d]: N=%d, gettime()=%lu, get_n()=%lu\n", i, results[i].N, (unsigned long)gettime(), (unsigned long)get_n());
		if (results[i].N < 0 || results[i].N > TRIES) fprintf(stderr, "***Bad results!***\n");
E 43
I 43
		set_results(r);
		fprintf(stderr, "\tresults[%d]: N=%d, gettime()=%lu, get_n()=%lu\n", i, r->N, (unsigned long)gettime(), (unsigned long)get_n());
		if (r->N < 0 || r->N > repetitions) 
			fprintf(stderr, "***Bad results!***\n");
E 43
		{
D 43
			for (k = 0; k < results[i].N; ++k) {
				fprintf(stderr, "\t\t{%lu, %lu}\n", (unsigned long)results[i].v[k].u, (unsigned long)results[i].v[k].n);
E 43
I 43
			for (k = 0; k < r->N; ++k) {
				fprintf(stderr, "\t\t{%lu, %lu}\n", (unsigned long)r->v[k].u, (unsigned long)r->v[k].n);
E 43
			}
		}
E 39
#endif //_DEBUG
D 43
		scratch_results = results[i];
		for (j = 0; j < scratch_results.N; ++j) {
			insertsort(scratch_results.v[j].u,
				   scratch_results.v[j].n,
				   merged_results);
E 43
I 43
		for (j = 0; j < r->N; ++j) {
			insertsort(r->v[j].u, r->v[j].n, merged_results);
E 43
		}
	}
D 43
#ifdef _DEBUG
D 39
fprintf(stderr, "Merged results; N=%d\n", merged_results->N);
for (i = 0; i < merged_results->N; ++i) {
fprintf(stderr, "\t%lu\t%lu\n", (unsigned long)merged_results->v[i].u, (unsigned long)merged_results->v[i].n);
}
E 39
I 39
	fprintf(stderr, "Merged results; N=%d\n", merged_results->N);
	for (i = 0; i < merged_results->N; ++i) {
		fprintf(stderr, "\t%lu\t%lu\n", (unsigned long)merged_results->v[i].u, (unsigned long)merged_results->v[i].n);
	}
E 39
#endif //_DEBUG
	if (merged_results->N <= TRIES) {
		scratch_results = *merged_results;
	} else {
		scratch_results.N = TRIES;
		for (i = 0; i < TRIES/3; ++i) {
			scratch_results.v[i] = merged_results->v[i];
			scratch_results.v[TRIES - 1 - i] = merged_results->v[merged_results->N - 1 - i];
		}
		for (i = 0; i < TRIES - 2 * (TRIES/3); ++i) {
			scratch_results.v[TRIES/3 + i] = merged_results->v[merged_results->N/2 - (TRIES - 2 * (TRIES/3)) / 2 + i];
		}
	}
	save_results(&scratch_results);
E 43
I 43
	set_results(merged_results);
E 43

#ifdef _DEBUG
D 39
i = 0;
fprintf(stderr, "*** Saving scratch_results: N=%d, gettime()=%lu, get_n()=%lu\n", scratch_results.N, (unsigned long)gettime(), (unsigned long)get_n());
{
int k;
for (k = 0; k < scratch_results.N; ++k) {
fprintf(stderr, "\t\t{%lu, %lu}\n", (unsigned long)scratch_results.v[k].u, (unsigned long)scratch_results.v[k].n);
}
}
E 39
I 39
	i = 0;
D 43
	fprintf(stderr, "*** Saving scratch_results: N=%d, gettime()=%lu, get_n()=%lu\n", scratch_results.N, (unsigned long)gettime(), (unsigned long)get_n());
E 43
I 43
	fprintf(stderr, "*** Saving merged_results: N=%d, gettime()=%lu, get_n()=%lu\n", get_results()->N, (unsigned long)gettime(), (unsigned long)get_n());
E 43
	{
		int k;
D 43
		for (k = 0; k < scratch_results.N; ++k) {
			fprintf(stderr, "\t\t{%lu, %lu}\n", (unsigned long)scratch_results.v[k].u, (unsigned long)scratch_results.v[k].n);
E 43
I 43
		for (k = 0; k < get_results()->N; ++k) {
			fprintf(stderr, "\t{%lu, %lu}\n", (unsigned long)get_results()->v[k].u, (unsigned long)get_results()->v[k].n);
E 43
		}
	}
E 39
#endif
I 45
	goto cleanup_exit;
error_exit:
I 52
#ifdef _DEBUG
	fprintf(stderr, "benchmp_parent: error_exit!\n");
#endif
E 52
I 51
	signal(SIGCHLD, SIG_IGN);
	for (i = 0; i < parallel; ++i) {
		kill(pids[i], SIGTERM);
	}
E 51
	free(merged_results);
cleanup_exit:
E 45
	close(response);
	close(start_signal);
I 47
	close(result_signal);
E 47
	close(exit_signal);

	free(results);
}


I 51
typedef enum { warmup, timing_interval, cooldown } benchmp_state;

typedef struct {
	benchmp_state	state;
	support_f	initialize;
	bench_f		benchmark;
	support_f	cleanup;
I 63
	int		childid;
E 63
	int		response;
	int		start_signal;
	int		result_signal;
	int		exit_signal;
	int		enough;
        iter_t		iterations;
	int		parallel;
        int		repetitions;
	void*		cookie;
	int		iterations_batch;
	int		need_warmup;
	long		i;
	int		r_size;
	result_t*	r;
} benchmp_child_state;

static benchmp_child_state _benchmp_child_state;

I 63
int
benchmp_childid()
{
	return _benchmp_child_state.childid;
}

E 63
I 52
void
benchmp_child_sigterm(int signo)
{
	signal(SIGTERM, SIG_IGN);
	if (_benchmp_child_state.cleanup)
		(*_benchmp_child_state.cleanup)(&_benchmp_child_state);
	exit(0);
}

E 52
void*
benchmp_getstate()
{
	return ((void*)&_benchmp_child_state);
}

void 
benchmp_child(support_f initialize, 
		bench_f benchmark,
		support_f cleanup,
I 63
		int childid,
E 63
		int response, 
		int start_signal, 
		int result_signal, 
		int exit_signal,
		int enough,
	        iter_t iterations,
		int parallel, 
	        int repetitions,
		void* cookie
		)
{
	iter_t		iterations_batch = (parallel > 1) ? get_n() : 1;
	double		result = 0.;
	double		usecs;
	long		i = 0;
	int		need_warmup;
	fd_set		fds;
	struct timeval	timeout;

	_benchmp_child_state.state = warmup;
	_benchmp_child_state.initialize = initialize;
	_benchmp_child_state.benchmark = benchmark;
	_benchmp_child_state.cleanup = cleanup;
I 63
	_benchmp_child_state.childid = childid;
E 63
	_benchmp_child_state.response = response;
	_benchmp_child_state.start_signal = start_signal;
	_benchmp_child_state.result_signal = result_signal;
	_benchmp_child_state.exit_signal = exit_signal;
	_benchmp_child_state.enough = enough;
	_benchmp_child_state.iterations = iterations;
	_benchmp_child_state.iterations_batch = iterations_batch;
	_benchmp_child_state.parallel = parallel;
	_benchmp_child_state.repetitions = repetitions;
	_benchmp_child_state.cookie = cookie;
	_benchmp_child_state.need_warmup = 1;
	_benchmp_child_state.i = 0;
	_benchmp_child_state.r_size = sizeof_result(repetitions);
	_benchmp_child_state.r = (result_t*)malloc(_benchmp_child_state.r_size);

I 56
	if (!_benchmp_child_state.r) return;
E 56
	insertinit(_benchmp_child_state.r);
	set_results(_benchmp_child_state.r);

	need_warmup = 1;
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
I 54

	signal(SIGCHLD, benchmp_sigchld_handler);
E 54

D 52
	signal(SIGCHLD, SIG_DFL);

E 52
	if (initialize)
		(*initialize)(cookie);
I 52
	
	if (benchmp_sigterm_handler != SIG_DFL) {
		signal(SIGTERM, benchmp_sigterm_handler);
	} else {
		signal(SIGTERM, benchmp_child_sigterm);
	}
	if (benchmp_sigterm_received)
		benchmp_child_sigterm(SIGTERM);
E 52

	/* start experiments, collecting results */
	insertinit(_benchmp_child_state.r);

	start(0);
	while (1) {
		(*benchmark)(benchmp_interval(&_benchmp_child_state), cookie);
	}
}

iter_t
benchmp_interval(void* _state)
{
	char		c;
	iter_t		iterations;
	double		result;
	fd_set		fds;
	struct timeval	timeout;
	benchmp_child_state* state = (benchmp_child_state*)_state;

	result = stop(0,0);
	save_n(state->iterations);
	result -= t_overhead() + get_n() * l_overhead();
	settime(result >= 0. ? (uint64)result : 0.);
I 52

	/* if the parent died, then give up */
D 56
	if (getppid() == 1) {
E 56
I 56
	if (getppid() == 1 && state->cleanup) {
E 56
		(*state->cleanup)(state->cookie);
		exit(0);
	}
E 52

	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	FD_ZERO(&fds);

	switch (state->state) {
	case warmup:
		iterations = state->iterations_batch;
		if (state->need_warmup) {
			state->need_warmup = 0;
			/* send 'ready' */
			write(state->response, &c, sizeof(char));
		}
		FD_SET(state->start_signal, &fds);
		select(state->start_signal+1, &fds, NULL,
		       NULL, &timeout);
		if (FD_ISSET(state->start_signal, &fds)) {
			state->state = timing_interval;
			read(state->start_signal, &c, sizeof(char));
			iterations = state->iterations;
		}
		break;
	case timing_interval:
		iterations = state->iterations;
		if (state->parallel > 1 || result > 0.95 * state->enough) {
			insertsort(gettime(), get_n(), get_results());
			state->i++;
			/* we completed all the experiments, return results */
			if (state->i >= state->repetitions) {
				state->state = cooldown;
			}
		}
		if (state->parallel == 1 
		    && (result < 0.99 * state->enough || result > 1.2 * state->enough)) {
			if (result > 150.) {
				double tmp = iterations / result;
				tmp *= 1.1 * state->enough;
				iterations = (iter_t)(tmp + 1);
			} else {
				iterations <<= 3;
				if (iterations > 1<<27
				    || result < 0. && iterations > 1<<20) {
					state->state = cooldown;
				}
			}
		}
		if (state->state != cooldown) {
			state->iterations = iterations;
		} else {
			/* send 'done' */
			write(state->response, (void*)&c, sizeof(char));
			iterations = state->iterations_batch;
		}
		break;
	case cooldown:
		iterations = state->iterations_batch;
		FD_SET(state->result_signal, &fds);
		select(state->result_signal+1, &fds, NULL, NULL, &timeout);
		if (FD_ISSET(state->result_signal, &fds)) {
			/* 
			 * At this point all children have stopped their
			 * measurement loops, so we can block waiting for
			 * the parent to tell us to send our results back.
			 * From this point on, we will do no more "work".
			 */
			read(state->result_signal, (void*)&c, sizeof(char));
			write(state->response, (void*)get_results(), state->r_size);
			if (state->cleanup)
				(*state->cleanup)(state->cookie);

			/* Now wait for signal to exit */
			read(state->exit_signal, (void*)&c, sizeof(char));
			exit(0);
		}
	};
	start(0);
	return (iterations);
}


E 51
E 38
E 15
D 10
static struct rusage ru_start, ru_stop;

E 10
I 10
/*
 * Redirect output someplace else.
 */
E 10
void
D 10
rusage()
E 10
I 10
timing(FILE *out)
E 10
{
D 10
	struct rusage r;
	double  sys, user, idle;
	double  per;
	double  timespent();

	sys = secs(ru_stop.ru_stime) - secs(ru_start.ru_stime);
	user = secs(ru_stop.ru_utime) - secs(ru_start.ru_utime);
	idle = timespent() - (sys + user);
	per = idle / timespent() * 100;
	fprintf(stderr, "real=%.2f sys=%.2f user=%.2f idle=%.2f stall=%.0f%% ",
	    timespent(), sys, user, idle, per);
	fprintf(stderr, "rd=%d wr=%d min=%d maj=%d ctx=%d\n",
	    mine(ru_inblock), mine(ru_oublock),
	    mine(ru_minflt), mine(ru_majflt),
	    mine(ru_nvcsw) + mine(ru_nivcsw));
E 10
I 10
	ftiming = out;
E 10
}

D 10
#endif

static struct timeval start_tv, stop_tv;

E 10
E 3
/*
D 3
 * utilities for timing
E 3
I 3
D 10
 * Start timing now.
E 10
I 10
D 34
 * Start ftiming now.
E 34
I 34
 * Start timing now.
E 34
E 10
E 3
 */
D 3
#include "stdio.h"
#include "sys/types.h"
#include "sys/time.h"
E 3
I 3
void
D 10
start()
E 10
I 10
start(struct timeval *tv)
E 10
{
D 10
	(void) gettimeofday(&start_tv, (struct timezone *) 0);
E 10
I 10
	if (tv == NULL) {
		tv = &start_tv;
	}
D 15
	(void) gettimeofday(tv, (struct timezone *) 0);
E 15
E 10
#ifdef	RUSAGE
	getrusage(RUSAGE_SELF, &ru_start);
#endif
I 15
	(void) gettimeofday(tv, (struct timezone *) 0);
E 15
}
E 3

D 3
static struct timeval t1, t2;
E 3
I 3
/*
I 15
D 17
 * Fake one for timing_overhead
 */
static void
timing_start(struct timeval *tv)
{
	if (tv == NULL) {
		tv = &dummy_tv;
	}
	(void) gettimeofday(tv, (struct timezone *) 0);
}

/*
E 17
E 15
D 10
 * Stop timing and return real time in microseconds.
E 10
I 10
D 34
 * Stop ftiming and return real time in microseconds.
E 34
I 34
 * Stop timing and return real time in microseconds.
E 34
E 10
 */
D 10
ulong
stop()
E 10
I 10
uint64
stop(struct timeval *begin, struct timeval *end)
E 10
{
D 30
	struct timeval tdiff;
I 10
	uint64	m;
E 10
E 3

E 30
D 3
start() {
	gettimeofday(&t1, (struct timezone *) 0);
E 3
I 3
D 10
	(void) gettimeofday(&stop_tv, (struct timezone *) 0);
E 10
I 10
	if (end == NULL) {
		end = &stop_tv;
	}
	(void) gettimeofday(end, (struct timezone *) 0);
E 10
#ifdef	RUSAGE
	getrusage(RUSAGE_SELF, &ru_stop);
#endif

D 10
	tvsub(&tdiff, &stop_tv, &start_tv);
	return (tdiff.tv_sec * 1000000 + tdiff.tv_usec);
E 10
I 10
	if (begin == NULL) {
		begin = &start_tv;
	}
D 30
	tvsub(&tdiff, end, begin);
	m = tdiff.tv_sec;
	m *= 1000000;
	m += tdiff.tv_usec;
	return (m);
E 30
I 30
D 45
	return tvdelta(begin, end);
E 45
I 45
	return (tvdelta(begin, end));
E 45
E 30
E 10
E 3
}

I 15
D 16
/*
 * Figure out the timing overhead.  This has to track bench.h
 */
double
t_overhead()
{
	struct timeval foo;
	int	N, usecs;

	if (timing_overhead) return (timing_overhead);
	if (getenv("TIMING_O")) {
		timing_overhead = atof(getenv("TIMING_O"));
		return (timing_overhead);
	}
	timing_start(0);
	LOOP_FIRST(N, usecs, ENOUGH);
	timing_start(0);
	LOOP_LAST(N, usecs, ENOUGH);
	timing_overhead = usecs;
	timing_overhead /= N;
	return (timing_overhead);
}

/*
 * Figure out how long to run it.
 * If enough == 0, then they want us to figure it out.
 * If enough is !0 then return it unless we think it is too short.
 */
int
get_enough(int enough)
{
	if (!enough) {
		if (getenv("ENOUGH")) {
			return atoi(getenv("ENOUGH"));
		}
		return (SHORT);
	}
	if (enough < 50000) return (50000);
	return (enough);
}

E 16
E 15
D 3
stop() {
	gettimeofday(&t2, (struct timezone *) 0);
E 3
I 3
D 10
ulong
now()
E 10
I 10
uint64
now(void)
E 10
{
	struct timeval t;
I 10
	uint64	m;
E 10

	(void) gettimeofday(&t, (struct timezone *) 0);
D 10
	return (t.tv_usec / 100);
E 10
I 10
	m = t.tv_sec;
	m *= 1000000;
	m += t.tv_usec;
	return (m);
E 10
E 3
}

I 7
D 10
ulong
delta()
E 10
I 10
double
Now(void)
E 10
{
I 10
	struct timeval t;

	(void) gettimeofday(&t, (struct timezone *) 0);
	return (t.tv_sec * 1000000.0 + t.tv_usec);
}

uint64
delta(void)
{
E 10
	static struct timeval last;
	struct timeval t;
	struct timeval diff;
I 10
	uint64	m;
E 10
D 9
	ulong	tmp;
E 9

	(void) gettimeofday(&t, (struct timezone *) 0);
	if (last.tv_usec) {
		tvsub(&diff, &t, &last);
		last = t;
D 10
		return (diff.tv_sec * 1000000 + diff.tv_usec);
E 10
I 10
		m = diff.tv_sec;
		m *= 1000000;
		m += diff.tv_usec;
		return (m);
E 10
	} else {
		last = t;
		return (0);
	}
}

double
D 10
Delta()
E 10
I 10
Delta(void)
E 10
{
	struct timeval t;
	struct timeval diff;
D 9
	ulong	tmp;
E 9

	(void) gettimeofday(&t, (struct timezone *) 0);
	tvsub(&diff, &t, &start_tv);
	return (diff.tv_sec + diff.tv_usec / 1000000.0);
}

E 7
D 3
ptime(bytes) {
	ptransfer(bytes, &t1, &t2);
E 3
I 3
D 15
/*
 * Adjust time spent by usec amount.
 *
 * XXX - tv_usec may be too big after this.
 */
E 15
D 8
void
E 8
I 8
D 10
ulong
E 8
adjust(usec)
	int	usec;
E 10
I 10
void
D 15
adjust(int usec)
E 15
I 15
save_n(uint64 n)
E 15
E 10
{
I 8
D 10
	struct	timeval tdiff;
E 10
E 8
D 15
	int     sec = usec / 1000000;
E 15
I 15
	iterations = n;
}
E 15

D 15
	usec -= sec * 1000000;
	stop_tv.tv_sec += sec;
	stop_tv.tv_usec += usec;
E 15
I 15
uint64
get_n(void)
{
D 25
	return ((uint64)iterations);
E 25
I 25
	return (iterations);
E 25
E 15
I 8
D 10
	tvsub(&tdiff, &stop_tv, &start_tv);
	return (tdiff.tv_sec * 1000000 + tdiff.tv_usec);
E 10
E 8
E 3
}

I 12
/*
 * Make the time spend be usecs.
 */
I 14
void
E 14
settime(uint64 usecs)
{
D 21
	bzero(&start_tv, sizeof(start_tv));
E 21
I 21
	bzero((void*)&start_tv, sizeof(start_tv));
E 21
	stop_tv.tv_sec = usecs / 1000000;
	stop_tv.tv_usec = usecs % 1000000;
I 13
D 14
	return (0);
E 14
E 13
}

E 12
I 9
D 10
/*
 * Make the time spent be smaller by a factor of n.
 */
E 10
E 9
D 3
ptransfer(bytes, t0, t1)
	struct timeval *t0, *t1;
E 3
I 3
void
I 9
D 10
divide(int n)
E 10
I 10
bandwidth(uint64 bytes, uint64 times, int verbose)
E 10
{
D 10
	struct	timeval tdiff;
	ulong	usecs;
E 10
I 10
	struct timeval tdiff;
	double  mb, secs;
E 10

	tvsub(&tdiff, &stop_tv, &start_tv);
D 10
	start_tv.tv_sec = start_tv.tv_usec = 0;
	usecs = tdiff.tv_sec * 1000000 + tdiff.tv_usec;
	usecs /= n;
	stop_tv.tv_sec = usecs / 1000000;
	stop_tv.tv_usec = usecs % 1000000;
E 10
I 10
	secs = tdiff.tv_sec;
	secs *= 1000000;
	secs += tdiff.tv_usec;
	secs /= 1000000;
	secs /= times;
	mb = bytes / MB;
I 35
	if (!ftiming) ftiming = stderr;
E 35
	if (verbose) {
I 34
D 35
		if (!ftiming) ftiming = stderr;
E 35
E 34
		(void) fprintf(ftiming,
		    "%.4f MB in %.4f secs, %.4f MB/sec\n",
		    mb, secs, mb/secs);
	} else {
		if (mb < 1) {
D 11
			(void) fprintf(ftiming, "%.8f ", mb);
E 11
I 11
			(void) fprintf(ftiming, "%.6f ", mb);
E 11
		} else {
			(void) fprintf(ftiming, "%.2f ", mb);
		}
		if (mb / secs < 1) {
D 11
			(void) fprintf(ftiming, "%.8f\n", mb/secs);
E 11
I 11
			(void) fprintf(ftiming, "%.6f\n", mb/secs);
E 11
		} else {
			(void) fprintf(ftiming, "%.2f\n", mb/secs);
		}
	}
E 10
}

void
E 9
D 10
bandwidth(bytes, verbose)
D 5
	int	bytes;
E 5
I 5
	int	bytes, verbose;
E 10
I 10
kb(uint64 bytes)
E 10
E 5
E 3
{
	struct timeval td;
D 3
	double   s, bs;
E 3
I 3
	double  s, bs;
E 3

D 3
	tvsub(&td, t1, t0);
	s = td.tv_sec + td.tv_usec/1000000.0;
#define	nz(x)	((x) == 0 ? 1 : (x))
#define	MB	(1024*1024.0)
#define	KB	(1024.0)
E 3
I 3
	tvsub(&td, &stop_tv, &start_tv);
	s = td.tv_sec + td.tv_usec / 1000000.0;
E 3
	bs = bytes / nz(s);
I 51
	if (s == 0.0) return;
E 51
I 34
	if (!ftiming) ftiming = stderr;
E 34
D 3
	printf("%.2f MB in %.2f seconds (%.2f KB/sec)\n",
	    bytes / MB, s, bs / KB);
E 3
I 3
D 10
	if (verbose) {
D 6
		(void) fprintf(stderr, "%.2f MB in %.2f secs, %.2f KB/sec\n",
		    bytes / MB, s, bs / KB);
E 6
I 6
		if ((bs / KB) > 1024) {
			(void) fprintf(stderr, "%.2f MB in %.2f secs, %.2f MB/sec\n",
			    bytes / MB, s, bs / MB);
		} else {
			(void) fprintf(stderr, "%.2f MB in %.2f secs, %.2f KB/sec\n",
			    bytes / MB, s, bs / KB);
		}
E 6
	} else {
D 9
		(void) fprintf(stderr, "%.2f %.2f\n",
E 9
I 9
		(void) fprintf(stderr, "%.6f %.1f\n",
E 9
		    bytes / MB, bs / MB);
	}
E 10
I 10
	(void) fprintf(ftiming, "%.0f KB/sec\n", bs / KB);
E 10
E 3
}

I 3
void
D 10
kb(bytes)
	int	bytes;
E 10
I 10
mb(uint64 bytes)
E 10
{
	struct timeval td;
	double  s, bs;

	tvsub(&td, &stop_tv, &start_tv);
	s = td.tv_sec + td.tv_usec / 1000000.0;
	bs = bytes / nz(s);
I 51
	if (s == 0.0) return;
E 51
I 34
	if (!ftiming) ftiming = stderr;
E 34
D 10
	(void) fprintf(stderr, "%.0f KB/sec\n", bs / KB);
E 10
I 10
	(void) fprintf(ftiming, "%.2f MB/sec\n", bs / MB);
E 10
}

void
D 10
mb(bytes)
	int	bytes;
E 10
I 10
latency(uint64 xfers, uint64 size)
E 10
{
	struct timeval td;
D 10
	double  s, bs;
E 10
I 10
	double  s;
E 10

I 34
	if (!ftiming) ftiming = stderr;
E 34
	tvsub(&td, &stop_tv, &start_tv);
	s = td.tv_sec + td.tv_usec / 1000000.0;
I 51
	if (s == 0.0) return;
E 51
D 10
	bs = bytes / nz(s);
	(void) fprintf(stderr, "%.2f MB/sec\n", bs / MB);
}

void
latency(xfers, size)
	int	xfers, size;
{
	struct timeval td;
	double  s;

	tvsub(&td, &stop_tv, &start_tv);
	s = td.tv_sec + td.tv_usec / 1000000.0;
	fprintf(stderr,
	    "%d xfers in %.2f secs, %.4f millisec/xfer, %.2f KB/sec\n",
	    xfers, s, s * 1000 / xfers,
	    (xfers * size) / (1024. * s));
E 10
I 10
D 12
	fprintf(ftiming,
	    "%d %dKB xfers in %.2f secs, %.4f millisec/xfer, %.2f MB/sec\n",
	    (int) xfers, (int) (size / KB), s, s * 1000 / xfers,
	    (xfers * size) / (MB * s));
E 12
I 12
	if (xfers > 1) {
		fprintf(ftiming, "%d %dKB xfers in %.2f secs, ",
		    (int) xfers, (int) (size / KB), s);
	} else {
		fprintf(ftiming, "%.1fKB in ", size / KB);
	}
	if ((s * 1000 / xfers) > 100) {
		fprintf(ftiming, "%.0f millisec%s, ",
		    s * 1000 / xfers, xfers > 1 ? "/xfer" : "s");
	} else {
		fprintf(ftiming, "%.4f millisec%s, ",
		    s * 1000 / xfers, xfers > 1 ? "/xfer" : "s");
	}
	if (((xfers * size) / (MB * s)) > 1) {
		fprintf(ftiming, "%.2f MB/sec\n", (xfers * size) / (MB * s));
	} else {
		fprintf(ftiming, "%.2f KB/sec\n", (xfers * size) / (KB * s));
	}
E 12
E 10
}

void
D 10
context(xfers)
	int	xfers;
E 10
I 10
context(uint64 xfers)
E 10
{
	struct timeval td;
	double  s;

	tvsub(&td, &stop_tv, &start_tv);
	s = td.tv_sec + td.tv_usec / 1000000.0;
I 51
	if (s == 0.0) return;
E 51
I 34
	if (!ftiming) ftiming = stderr;
E 34
D 10
	fprintf(stderr,
E 10
I 10
	fprintf(ftiming,
E 10
	    "%d context switches in %.2f secs, %.0f microsec/switch\n",
D 10
	    xfers, s, s * 1000000 / xfers);
E 10
I 10
	    (int)xfers, s, s * 1000000 / xfers);
E 10
}

void
I 4
D 10
nano(s, n)
	char	*s;
	int	n;
E 10
I 10
nano(char *s, uint64 n)
E 10
{
	struct timeval td;
D 10
	double	micro;
E 10
I 10
	double  micro;
E 10

	tvsub(&td, &stop_tv, &start_tv);
	micro = td.tv_sec * 1000000 + td.tv_usec;
	micro *= 1000;
I 51
	if (micro == 0.0) return;
E 51
I 34
	if (!ftiming) ftiming = stderr;
E 34
D 10
	fprintf(stderr, "%s: %.0f nanoseconds\n", s, micro / n);
E 10
I 10
D 44
	fprintf(ftiming, "%s: %.0f nanoseconds\n", s, micro / n);
E 44
I 44
	fprintf(ftiming, "%s: %.2f nanoseconds\n", s, micro / n);
E 44
E 10
}

void
E 4
D 10
micro(s, n)
	char	*s;
	int	n;
E 10
I 10
micro(char *s, uint64 n)
E 10
{
	struct timeval td;
D 10
	int	micro;
E 10
I 10
	double	micro;
E 10

	tvsub(&td, &stop_tv, &start_tv);
	micro = td.tv_sec * 1000000 + td.tv_usec;
D 10
	fprintf(stderr, "%s: %d microseconds\n", s, micro / n);
E 10
I 10
	micro /= n;
I 51
	if (micro == 0.0) return;
E 51
I 34
	if (!ftiming) ftiming = stderr;
E 34
D 11
	fprintf(ftiming, "%s: %.3f microseconds\n", s, micro);
E 11
I 11
D 14
	if (micro >= 10) {
		fprintf(ftiming, "%s: %.0f microseconds\n", s, micro);
	} else {
E 14
I 14
	fprintf(ftiming, "%s: %.4f microseconds\n", s, micro);
#if 0
	if (micro >= 100) {
		fprintf(ftiming, "%s: %.1f microseconds\n", s, micro);
	} else if (micro >= 10) {
E 14
		fprintf(ftiming, "%s: %.3f microseconds\n", s, micro);
I 14
	} else {
		fprintf(ftiming, "%s: %.4f microseconds\n", s, micro);
E 14
	}
I 14
#endif
E 14
E 11
E 10
}

void
I 11
micromb(uint64 sz, uint64 n)
{
	struct timeval td;
	double	mb, micro;

	tvsub(&td, &stop_tv, &start_tv);
	micro = td.tv_sec * 1000000 + td.tv_usec;
	micro /= n;
	mb = sz;
	mb /= MB;
I 51
	if (micro == 0.0) return;
E 51
I 34
	if (!ftiming) ftiming = stderr;
E 34
	if (micro >= 10) {
		fprintf(ftiming, "%.6f %.0f\n", mb, micro);
	} else {
		fprintf(ftiming, "%.6f %.3f\n", mb, micro);
	}
}

void
E 11
D 10
milli(s, n)
	char	*s;
	int	n;
E 10
I 10
milli(char *s, uint64 n)
E 10
{
	struct timeval td;
D 10
	int	milli;
E 10
I 10
	uint64 milli;
E 10

	tvsub(&td, &stop_tv, &start_tv);
	milli = td.tv_sec * 1000 + td.tv_usec / 1000;
D 10
	fprintf(stderr, "%s: %d milliseconds\n", s, milli / n);
E 10
I 10
	milli /= n;
I 51
	if (milli == 0.0) return;
E 51
I 34
	if (!ftiming) ftiming = stderr;
E 34
	fprintf(ftiming, "%s: %d milliseconds\n", s, (int)milli);
E 10
}

void
D 10
ptime(n)
	int	n;
E 10
I 10
ptime(uint64 n)
E 10
{
	struct timeval td;
	double  s;

	tvsub(&td, &stop_tv, &start_tv);
	s = td.tv_sec + td.tv_usec / 1000000.0;
I 51
	if (s == 0.0) return;
E 51
I 34
	if (!ftiming) ftiming = stderr;
E 34
D 10
	fprintf(stderr,
	    "%d in %.2f secs, %.0f microseconds each\n", n, s, s * 1000000 / n);
E 10
I 10
	fprintf(ftiming,
	    "%d in %.2f secs, %.0f microseconds each\n",
	    (int)n, s, s * 1000000 / n);
E 10
}

I 15
uint64
tvdelta(struct timeval *start, struct timeval *stop)
{
	struct timeval td;
	uint64	usecs;

	tvsub(&td, stop, start);
	usecs = td.tv_sec;
	usecs *= 1000000;
	usecs += td.tv_usec;
D 37
	return (usecs);
E 37
I 37
D 44
	return usecs;
E 44
I 44
	return (usecs);
E 44
E 37
}

E 15
void
E 3
D 10
tvsub(tdiff, t1, t0)
	struct timeval *tdiff, *t1, *t0;
E 10
I 10
tvsub(struct timeval * tdiff, struct timeval * t1, struct timeval * t0)
E 10
{
D 3

E 3
	tdiff->tv_sec = t1->tv_sec - t0->tv_sec;
D 3
	if ( t0->tv_usec > t1->tv_usec ) {
		tdiff->tv_sec--; 
		tdiff->tv_usec = (1000000 - t0->tv_usec) + t1->tv_usec;
	} else
		tdiff->tv_usec = t1->tv_usec - t0->tv_usec;
	
E 3
I 3
	tdiff->tv_usec = t1->tv_usec - t0->tv_usec;
D 37
	if (tdiff->tv_usec < 0)
		tdiff->tv_sec--, tdiff->tv_usec += 1000000;
E 37
I 37
D 50
	while (tdiff->tv_usec < 0 && tdiff->tv_sec > 0) {
E 50
I 50
	if (tdiff->tv_usec < 0 && tdiff->tv_sec > 0) {
E 50
		tdiff->tv_sec--;
		tdiff->tv_usec += 1000000;
I 50
		assert(tdiff->tv_usec >= 0);
E 50
	}
I 50

E 50
	/* time shouldn't go backwards!!! */
	if (tdiff->tv_usec < 0 || t1->tv_sec < t0->tv_sec) {
		tdiff->tv_sec = 0;
		tdiff->tv_usec = 0;
	}
E 37
E 3
}
I 3

I 15
uint64
D 19
usecs_spent()
E 19
I 19
D 25
usecs_spent(void)
E 25
I 25
gettime(void)
E 25
E 19
{
	return (tvdelta(&start_tv, &stop_tv));
}

E 15
double
D 10
timespent()
E 10
I 10
D 14
timespent(void)
E 14
I 14
D 19
timespent()
E 19
I 19
timespent(void)
E 19
E 14
E 10
{
	struct timeval td;

	tvsub(&td, &stop_tv, &start_tv);
D 10
	return (td.tv_sec + td.tv_usec / 1000000);
E 10
I 10
	return (td.tv_sec + td.tv_usec / 1000000.0);
E 10
}
I 9

I 10
static	char	p64buf[10][20];
static	int	n;

char	*
p64(uint64 big)
{
	char	*s = p64buf[n++];

	if (n == 10) n = 0;
#ifdef  linux
	{
        int     *a = (int*)&big;

        if (a[1]) {
                sprintf(s, "0x%x%08x", a[1], a[0]);
        } else {
                sprintf(s, "0x%x", a[0]);
        }
	}
#endif
#ifdef	__sgi
        sprintf(s, "0x%llx", big);
#endif
	return (s);
}

char	*
p64sz(uint64 big)
{
	double	d = big;
	char	*tags = " KMGTPE";
	int	t = 0;
	char	*s = p64buf[n++];

	if (n == 10) n = 0;
	while (d > 512) t++, d /= 1024;
	if (d == 0) {
		return ("0");
	}
	if (d < 100) {
		sprintf(s, "%.4f%c", d, tags[t]);
	} else {
		sprintf(s, "%.2f%c", d, tags[t]);
	}
	return (s);
}

E 10
char
D 14
last(s)
	char	*s;
E 14
I 14
last(char *s)
E 14
{
	while (*s++)
		;
	return (s[-2]);
}

D 65
int
E 65
I 65
uint64
E 65
D 14
bytes(s)
	char	*s;
E 14
I 14
bytes(char *s)
E 14
{
D 65
	int	n = atoi(s);
E 65
I 65
	uint64	n;

	if (sscanf(s, "%llu", &n) < 1)
		return (0);
E 65

	if ((last(s) == 'k') || (last(s) == 'K'))
		n *= 1024;
	if ((last(s) == 'm') || (last(s) == 'M'))
		n *= (1024 * 1024);
	return (n);
}

I 10
D 27
void
E 27
D 28
use_result(uint64 result)
{
D 26
	dummy = result;
E 26
I 26
	use_result_dummy += result;
E 26
}
E 28
I 28
void
use_int(int result) { use_result_dummy += result; }
E 28

I 18
void
I 28
use_pointer(void *result) { use_result_dummy += (int)result; }

I 43
int
sizeof_result(int repetitions)
{
	if (repetitions <= TRIES)
D 45
		return sizeof(result_t);
	return sizeof(result_t) + (repetitions - TRIES) * sizeof(value_t);
E 45
I 45
		return (sizeof(result_t));
	return (sizeof(result_t) + (repetitions - TRIES) * sizeof(value_t));
E 45
}

E 43
void
E 28
D 31
insertinit(result_t *r, int n)
E 31
I 31
insertinit(result_t *r)
E 31
{
	int	i;

D 30
	for (i = 0; i < n; r[i++].u = 0);
E 30
I 30
D 31
	for (i = 0; i < n; i++) {
		r[i].u = 0;
		r[i].n = 1;
E 31
I 31
	r->N = 0;
D 43
	for (i = 0; i < TRIES; i++) {
D 38
		r->u[i] = 0;
		r->n[i] = 1;
E 38
I 38
		r->v[i].u = 0;
		r->v[i].n = 1;
E 38
E 31
	}
E 43
E 30
}

E 18
I 14
D 15
#if 0
E 15
/* biggest to smallest */
I 16
void
E 16
D 18
insertsort(double *d, int l, double val)
E 18
I 18
D 31
insertsort(uint64 u, uint64 n, result_t *r, int l)
E 31
I 31
insertsort(uint64 u, uint64 n, result_t *r)
E 31
E 18
{
	int	i, j;

I 50
	if (u == 0) return;

E 50
D 31
	for (i = 0; i < l; ++i) {
D 18
		if (val > d[i]) {
E 18
I 18
D 30
		if (u > r[i].u) {
E 30
I 30
		if (u/(double)n > r[i].u/(double)r[i].n) {
E 30
E 18
			for (j = l-1; j > i; --j) {
D 18
				d[j] = d[j-1];
E 18
I 18
				r[j] = r[j-1];
E 31
I 31
	for (i = 0; i < r->N; ++i) {
D 38
		if (u/(double)n > r->u[i]/(double)r->n[i]) {
E 38
I 38
		if (u/(double)n > r->v[i].u/(double)r->v[i].n) {
E 38
			for (j = r->N; j > i; --j) {
D 38
				r->u[j] = r->u[j-1];
				r->n[j] = r->n[j-1];
E 38
I 38
				r->v[j] = r->v[j - 1];
E 38
E 31
E 18
			}
D 18
			d[i] = val;
E 18
I 18
D 31
			r[i].u = u;
			r[i].n = n;
E 18
			return;
E 31
I 31
			break;
E 31
		}
	}
I 31
D 38
	r->u[i] = u;
	r->n[i] = n;
E 38
I 38
	r->v[i].u = u;
	r->v[i].n = n;
E 38
	r->N++;
E 31
}
I 16
D 24

I 17
D 19
morefds()
E 19
I 19
void
morefds(void)
E 19
{
#ifdef	RLIMIT_NOFILE
	struct	rlimit r;

	getrlimit(RLIMIT_NOFILE, &r);
	r.rlim_cur = r.rlim_max;
	setrlimit(RLIMIT_NOFILE, &r);
#endif
}

E 24
E 17
D 31
/*
I 17
 * Fake one for timing_overhead
 */
static void
timing_start(struct timeval *tv)
E 31
I 31

D 43
static result_t results;
E 43
I 43
static result_t  _results;
static result_t* results = &_results;
E 43

D 67
void
I 36
D 60
print_results(void)
E 60
I 60
print_results(int details)
E 60
{
	int	i;

I 49
	fprintf(stderr, "N=%d, t={", results->N);
E 49
D 43
	for (i = 0; i < results.N; ++i) {
D 38
		fprintf(stderr, "%.2f ", (double)results.u[i]/results.n[i]);
E 38
I 38
		fprintf(stderr, "%.2f ", (double)results.v[i].u/results.v[i].n);
E 43
I 43
	for (i = 0; i < results->N; ++i) {
D 49
		fprintf(stderr, "%.2f ", (double)results->v[i].u/results->v[i].n);
E 49
I 49
		fprintf(stderr, "%.2f", (double)results->v[i].u/results->v[i].n);
		if (i < results->N - 1) 
			fprintf(stderr, ", ");
E 49
E 43
E 38
	}
I 49
	fprintf(stderr, "}\n");
I 60
	if (details) {
		fprintf(stderr, "\t/* {", results->N);
		for (i = 0; i < results->N; ++i) {
			fprintf(stderr, 
				"%llu/%llu", results->v[i].u, results->v[i].n);
			if (i < results->N - 1)
				fprintf(stderr, ", ");
		}
		fprintf(stderr, "} */\n");
	}
		
E 60
E 49
}

E 67
D 43
void
E 36
get_results(result_t *r)
E 43
I 43
result_t*
get_results()
E 43
E 31
{
D 31
	if (tv == NULL) {
		tv = &dummy_tv;
E 31
I 31
D 43
	*r = results;
E 43
I 43
D 45
	return results;
E 45
I 45
	return (results);
E 45
E 43
}

void
D 43
save_results(result_t *r)
E 43
I 43
set_results(result_t *r)
E 43
{
D 43
	results = *r;
E 43
I 43
	results = r;
E 43
	save_median();
}

void
save_minimum()
{
D 37
	save_n(results.n[results.N - 1]);
	settime(results.u[results.N - 1]);
E 37
I 37
D 43
	if (results.N == 0) {
E 43
I 43
	if (results->N == 0) {
E 43
		save_n(1);
		settime(0);
	} else {
D 38
		save_n(results.n[results.N - 1]);
		settime(results.u[results.N - 1]);
E 38
I 38
D 43
		save_n(results.v[results.N - 1].n);
		settime(results.v[results.N - 1].u);
E 43
I 43
		save_n(results->v[results->N - 1].n);
		settime(results->v[results->N - 1].u);
E 43
E 38
	}
E 37
}

void
save_median()
{
D 43
	int	i = results.N / 2;
E 43
I 43
	int	i = results->N / 2;
E 43
	uint64	u, n;

D 37
	if (results.N % 2) {
E 37
I 37
D 43
	if (results.N == 0) {
E 43
I 43
	if (results->N == 0) {
E 43
		n = 1;
		u = 0;
D 43
	} else if (results.N % 2) {
E 37
D 38
		n = results.n[i];
		u = results.u[i];
E 38
I 38
		n = results.v[i].n;
		u = results.v[i].u;
E 43
I 43
	} else if (results->N % 2) {
		n = results->v[i].n;
		u = results->v[i].u;
E 43
E 38
	} else {
D 38
		n = (results.n[i] + results.n[i-1]) / 2;
		u = (results.u[i] + results.u[i-1]) / 2;
E 38
I 38
D 43
		n = (results.v[i].n + results.v[i-1].n) / 2;
		u = (results.v[i].u + results.v[i-1].u) / 2;
E 43
I 43
		n = (results->v[i].n + results->v[i-1].n) / 2;
		u = (results->v[i].u + results->v[i-1].u) / 2;
E 43
E 38
E 31
	}
I 43
#ifdef _DEBUG
	fprintf(stderr, "save_median: N=%d, n=%lu, u=%lu\n", results->N, (unsigned long)n, (unsigned long)u);
#endif /* _DEBUG */
E 43
D 31
	(void) gettimeofday(tv, (struct timezone *) 0);
E 31
I 31
	save_n(n); settime(u);
E 31
}

I 18
D 31
#define	LTRIES	(TRIES * 1)
E 31
E 18
/*
I 18
 * The inner loop tracks bench.h but uses a different results array.
 */
static long *
D 25
one_op(long *p)
E 25
I 25
one_op(register long *p)
E 25
{
D 31
	result_t r[LTRIES];
	int	i;

	insertinit(r, LTRIES);
	for (i = 0; i < LTRIES; ++i) {
		BENCH1(p = (long *)*p, 0);
D 25
		insertsort(usecs_spent(), get_n(), r, LTRIES);
E 25
I 25
		insertsort(gettime(), get_n(), r, LTRIES);
E 25
	}
D 25
	save_n(r[0].n); settime(r[0].u);
E 25
I 25
	/*
	for (i = 0; i < LTRIES; ++i) 
		printf("%d\t%d\t%f%s\n",
		    (int)r[i].n, (int)r[i].u, (double)r[i].u/r[i].n,
		    i==LTRIES/2?" *":"");
	*/
	save_n(r[LTRIES/2].n); settime(r[LTRIES/2].u);
E 31
I 31
D 46
	BENCH_INNER(p = (long *)*p, 0);
E 46
I 46
	BENCH_INNER(p = (long *)*p;, 0);
E 46
E 31
E 25
	return (p);
}

static long *
D 25
two_op(long *p)
E 25
I 25
D 46
two_op(register long *p, register long *q)
E 46
I 46
two_op(register long *p)
E 46
E 25
{
D 31
	result_t r[LTRIES];
	int	i;

	insertinit(r, LTRIES);
	for (i = 0; i < LTRIES; ++i) {
D 25
		BENCH1(p = (long *)*p; p = (long*)*p, 0);
		insertsort(usecs_spent(), get_n(), r, LTRIES);
E 25
I 25
		BENCH1(p = (long *)*q; q = (long*)*p, 0);
		insertsort(gettime(), get_n(), r, LTRIES);
E 25
	}
D 25
	save_n(r[0].n); settime(r[0].u);
E 25
I 25
	/*
	for (i = 0; i < LTRIES; ++i) 
		printf("%d\t%d\t%f%s\n",
		    (int)r[i].n, (int)r[i].u, (double)r[i].u/r[i].n,
		    i==LTRIES/2?" *":"");
	*/
	save_n(r[LTRIES/2].n); settime(r[LTRIES/2].u);
E 31
I 31
D 46
	BENCH_INNER(p = (long *)*q; q = (long*)*p, 0);
E 46
I 46
	BENCH_INNER(p = (long *)*p; p = (long*)*p;, 0);
E 46
E 31
E 25
	return (p);
}

I 25
static long	*p = (long *)&p;
static long	*q = (long *)&q;

D 31
/*
 * Carl - this was busted in the follwing ways:
 *	The compiler optimized the p = *, p = *p into one op.
 *	We want the variables to be statics at fixed addresses in each run.
D 27
 *	I also changed it to take the mean, not the min.
E 27
I 27
 *	I also changed it to take the median, not the min.
E 27
 */
E 31
E 25
double
D 19
l_overhead()
E 19
I 19
l_overhead(void)
E 19
{
D 31
	uint64	u1, u2, n1, n2;
D 25
	long	*p = (long *)&p;
E 25
	double	tmp;
	static	double o;
	static	int done = 0;
E 31
I 31
D 33
	int	i, j;
E 33
I 33
	int	i;
E 33
	uint64	N_save, u_save;
	static	double overhead;
	static	int initialized = 0;
D 43
	result_t one, two, r_save;
E 43
I 43
	result_t one, two, *r_save;
E 43
E 31

	init_timing();
D 31
	if (done) { return (o); }
E 31
I 31
D 45
	if (initialized) return overhead;
E 45
I 45
	if (initialized) return (overhead);
E 45
E 31

D 31
	done = 1;
E 31
I 31
	initialized = 1;
E 31
	if (getenv("LOOP_O")) {
D 31
		o = atof(getenv("LOOP_O"));
		return (o);
	}
D 27
	use_result((int)one_op(p));
E 27
I 27
D 28
	use_result((uint64)one_op(p));
E 28
I 28
	use_pointer((void *)one_op(p));
E 28
E 27
D 25
	u1 = usecs_spent();
E 25
I 25
	u1 = gettime();
E 25
	n1 = get_n();
D 25
	use_result((int)two_op(p));
	u2 = usecs_spent();
E 25
I 25
D 27
	use_result((int)two_op(p, q));
E 27
I 27
D 28
	use_result((uint64)two_op(p, q));
E 28
I 28
	use_pointer((void *)two_op(p, q));
E 28
E 27
	u2 = gettime();
E 25
	n2 = get_n();
I 25
	/*
	fprintf(stderr, "%lld %lld  %f  %lld  %lld  %f  ",
	    u1,n1,(double)u1/n1,u2,n2,(double)u2/n2);
	fprintf(stderr, "%f  %f  ", (double)u1/n1,(double)u2/n2);
    	*/
E 31
I 31
		overhead = atof(getenv("LOOP_O"));
	} else {
D 43
		get_results(&r_save); N_save = get_n(); u_save = gettime(); 
E 43
I 43
		r_save = get_results(); N_save = get_n(); u_save = gettime(); 
E 43
		insertinit(&one);
		insertinit(&two);
		for (i = 0; i < TRIES; ++i) {
			use_pointer((void*)one_op(p));
D 37
			insertsort(gettime() - t_overhead(), get_n(), &one);
E 37
I 37
D 50
			if (gettime() > 0 && gettime() > t_overhead())
E 50
I 50
			if (gettime() > t_overhead())
E 50
				insertsort(gettime() - t_overhead(), get_n(), &one);
E 37
D 46
			use_pointer((void *)two_op(p, q));
E 46
I 46
			use_pointer((void *)two_op(p));
E 46
D 37
			insertsort(gettime() - t_overhead(), get_n(), &two);
E 37
I 37
D 50
			if (gettime() > 0 && gettime() > t_overhead())
E 50
I 50
			if (gettime() > t_overhead())
E 50
				insertsort(gettime() - t_overhead(), get_n(), &two);
E 37
		}
		/*
		 * u1 = (n1 * (overhead + work))
		 * u2 = (n2 * (overhead + 2 * work))
		 * ==> overhead = 2. * u1 / n1 - u2 / n2
		 */
D 38
		save_results(&one); save_minimum();
E 38
I 38
D 43
		save_results(&one); 
E 43
I 43
		set_results(&one); 
E 43
		save_minimum();
E 38
		overhead = 2. * gettime() / (double)get_n();
		
D 38
		save_results(&two); save_minimum();
E 38
I 38
D 43
		save_results(&two); 
E 43
I 43
		set_results(&two); 
E 43
		save_minimum();
E 38
		overhead -= gettime() / (double)get_n();
		
		if (overhead < 0.) overhead = 0.;	/* Gag */
E 31
E 25

D 31
	/*
	 * u1 = (n1 * (overhead + work))
	 * u2 = (n2 * (overhead + 2 * work))
D 25
	 * this yields
	 * o = 2 * u1 / n1 - u2 / n2
E 25
	 */
	o = 2 * u1;
	o /= n1;
	tmp = u2;
	tmp /= n2;
	o -= tmp;
D 25
	if (o < 0) o = 0;

E 25
I 25
	if (o < 0) o = 0;	/* Gag */
E 25
	return (o);
E 31
I 31
D 43
		save_results(&r_save); save_n(N_save); settime(u_save); 
E 43
I 43
		set_results(r_save); save_n(N_save); settime(u_save); 
E 43
	}
D 45
	return overhead;
E 45
I 45
	return (overhead);
E 45
E 31
}
I 31

E 31
/*
E 18
E 17
 * Figure out the timing overhead.  This has to track bench.h
 */
D 31
double
E 31
I 31
uint64
E 31
D 19
t_overhead()
E 19
I 19
t_overhead(void)
E 19
{
D 17
	struct timeval foo;
	int	N, usecs;
E 17
I 17
D 25
	int		N, usecs;
E 25
I 25
D 31
	uint64		N, usecs;
E 31
I 31
	uint64		N_save, u_save;
E 31
E 25
	static int	initialized = 0;
D 31
	static double	overhead = 0.0;
E 31
I 31
	static uint64	overhead = 0;
	struct timeval	tv;
D 43
	result_t	r_save;
E 43
I 43
	result_t	*r_save;
E 43
E 31
E 17

I 18
	init_timing();
E 18
D 17
	if (timing_overhead) return (timing_overhead);
	if (getenv("TIMING_O")) {
		timing_overhead = atof(getenv("TIMING_O"));
		return (timing_overhead);
E 17
I 17
D 30
	if (overhead == 0.0) {
E 30
I 30
D 31
	if (!initialized) {
		initialized = 1;
E 30
		if (getenv("TIMING_O")) {
			overhead = atof(getenv("TIMING_O"));
D 30
		} else if (!initialized) {
			initialized = 1;
D 25
			N = get_n(); usecs = usecs_spent();
E 25
I 25
D 27
			N = get_n(); usecs = gettime();
E 25
			BENCH(timing_start(0), 0);
D 25
			overhead = usecs_spent();
E 25
I 25
			overhead = gettime();
E 25
			overhead /= get_n();
D 25
			save_n((uint64)N); settime(usecs);
E 25
I 25
			save_n(N); settime(usecs);
E 27
I 27
			if (get_enough(0) > 50000) {
				/* it is in the noise, so ignore it */
				overhead = 0.0;
			} else {
				N = get_n(); usecs = gettime();
				BENCH(timing_start(0), 0);
				overhead = gettime();
				overhead /= get_n();
				save_n(N); settime(usecs);
			}
E 30
I 30
		} else if (get_enough(0) <= 50000) {
			/* it is not in the noise, so compute it */
			N = get_n(); usecs = gettime();
E 31
I 31
D 45
	if (initialized) return overhead;
E 45
I 45
	if (initialized) return (overhead);
E 45

	initialized = 1;
	if (getenv("TIMING_O")) {
		overhead = atof(getenv("TIMING_O"));
	} else if (get_enough(0) <= 50000) {
		/* it is not in the noise, so compute it */
		int		i;
		result_t	r;

E 31
D 31
			BENCH(timing_start(0), 0);
			overhead = gettime();
			overhead /= get_n();
			save_n(N); settime(usecs);
E 31
I 31
D 43
		get_results(&r_save); N_save = get_n(); u_save = gettime(); 
E 43
I 43
		r_save = get_results(); N_save = get_n(); u_save = gettime(); 
E 43
		insertinit(&r);
		for (i = 0; i < TRIES; ++i) {
			BENCH_INNER(gettimeofday(&tv, 0), 0);
D 37
			insertsort(gettime(), get_n(), &r);
E 37
I 37
D 50
			if (gettime() > 0) 
				insertsort(gettime(), get_n(), &r);
E 50
I 50
			insertsort(gettime(), get_n(), &r);
E 50
E 37
E 31
E 30
E 27
E 25
		}
I 31
D 43
		save_results(&r);
E 43
I 43
		set_results(&r);
E 43
		save_minimum();
		overhead = gettime() / get_n();

D 43
		save_results(&r_save); save_n(N_save); settime(u_save); 
E 43
I 43
		set_results(r_save); save_n(N_save); settime(u_save); 
E 43
E 31
E 17
	}
D 17
	timing_start(0);
	LOOP_FIRST(N, usecs, SHORT);
	timing_start(0);
	LOOP_LAST(N, usecs, SHORT);
	timing_overhead = usecs;
	timing_overhead /= N;
	return (timing_overhead);
E 17
I 17
D 45
	return overhead;
E 45
I 45
	return (overhead);
E 45
E 17
}

/*
 * Figure out how long to run it.
 * If enough == 0, then they want us to figure it out.
 * If enough is !0 then return it unless we think it is too short.
 */
I 18
static	int	long_enough;
I 23
D 27
static	int	compute_enough(int tries);
E 27
I 27
static	int	compute_enough();
E 27
E 23

E 18
int
D 18
get_enough(int enough)
E 18
I 18
get_enough(int e)
E 18
{
D 17
	static	int e = 0;
E 17
I 17
D 18
	static	e = 0;
E 18
I 18
	init_timing();
	return (long_enough > e ? long_enough : e);
}
E 18
E 17

D 17
	if (!e) {
E 17
I 17
D 18
	if (!enough) {
		if (e) return (e);
E 17
		if (getenv("ENOUGH")) {
D 17
			e = atoi(getenv("ENOUGH"));
E 17
I 17
			return e = atoi(getenv("ENOUGH"));
E 18
I 18

D 19
init_timing()
E 19
I 19
static void
init_timing(void)
E 19
{
	static	int done = 0;
D 23
	static int compute_enough(int tries);
E 23

	if (done) return;
	done = 1;
D 27
	long_enough = compute_enough(9);
E 27
I 27
	long_enough = compute_enough();
E 27
	t_overhead();
	l_overhead();
}

typedef long TYPE;

static TYPE **
enough_duration(register long N, register TYPE ** p)
{
#define	ENOUGH_DURATION_TEN(one)	one one one one one one one one one one
	while (N-- > 0) {
		ENOUGH_DURATION_TEN(p = (TYPE **) *p;);
	}
D 45
	return p;
E 45
I 45
	return (p);
E 45
}

D 37
static int
duration(int N)
E 37
I 37
static uint64
duration(long N)
E 37
{
D 37
	int     usecs;
E 37
I 37
	uint64	usecs;
E 37
	TYPE   *x = (TYPE *)&x;
	TYPE  **p = (TYPE **)&x;

	start(0);
	p = enough_duration(N, p);
	usecs = stop(0, 0);
D 27
	use_result((int)p);
E 27
I 27
D 28
	use_result((uint64)p);
E 28
I 28
	use_pointer((void *)p);
E 28
E 27
D 45
	return usecs;
E 45
I 45
	return (usecs);
E 45
}

/*
D 27
 * find the minimum time that work "N" takes in "tries" tests
E 27
I 27
D 31
 * find the median time that work "N" takes in "tries" tests
E 31
I 31
 * find the minimum time that work "N" takes in "tries" tests
E 31
E 27
 */
D 37
static int
E 37
I 37
static uint64
E 37
D 27
time_N(int tries, long N)
E 27
I 27
D 48
time_N(long N)
E 48
I 48
time_N(iter_t N)
E 48
E 27
{
D 33
	int     i, usecs;
E 33
I 33
	int     i;
I 37
	uint64	usecs;
E 37
E 33
I 27
D 31
	result_t r[LTRIES];
E 31
I 31
D 43
	result_t r;
E 43
I 43
	result_t r, *r_save;
E 43
E 31
E 27

I 43
	r_save = get_results();
E 43
D 27
	usecs = duration(N);
	for (i = 1; i < tries; ++i) {
		int     tmp = duration(N);

		if (tmp < usecs)
			usecs = tmp;
E 27
I 27
D 31
	insertinit(r, LTRIES);
	for (i = 1; i < LTRIES; ++i) {
		insertsort(duration(N), N, r, LTRIES);
E 31
I 31
	insertinit(&r);
	for (i = 1; i < TRIES; ++i) {
D 37
		insertsort(duration(N), N, &r);
E 37
I 37
		usecs = duration(N);
D 50
		if (usecs > 0)
			insertsort(usecs, N, &r);
E 50
I 50
		insertsort(usecs, N, &r);
E 50
E 37
E 31
E 27
	}
D 27
	return usecs;
E 27
I 27
D 31
	return r[TRIES/2].u;
E 31
I 31
D 43
	save_results(&r);
E 43
I 43
	set_results(&r);
E 43
D 38
	save_minimum();
E 38
I 38
D 40
	/*save_minimum();*/
E 40
I 40
	save_minimum();
E 40
E 38
D 43
	return gettime();
E 43
I 43
	usecs = gettime();
	set_results(r_save);
D 45
	return usecs;
E 45
I 45
	return (usecs);
E 45
E 43
E 31
E 27
}

/*
 * return the amount of work needed to run "enough" microseconds
 */
D 37
static int
E 37
I 37
static long
E 37
find_N(int enough)
{
D 19
	int     i, N;
E 19
I 19
D 21
	int     N;
E 21
I 21
D 27
	int     N, tries;
E 27
I 27
D 37
	int	tries;
	static int N = 10000;
	static int usecs = 0;
E 37
I 37
	int		tries;
D 48
	static long	N = 10000;
E 48
I 48
	static iter_t	N = 10000;
E 48
	static uint64	usecs = 0;
E 37
E 27
E 21
E 19

D 21
	for (N = 1;;) {
E 21
I 21
D 27
	for (N = 1, tries = 0; ; tries++) {
E 21
		/*
		 * XXX - prevent infinite loops? 
		 */
		int     usecs = duration(N);
E 27
I 27
D 30
	if (usecs = 0) usecs = time_N(N);
E 30
I 30
	if (!usecs) usecs = time_N(N);
E 30
E 27

I 27
	for (tries = 0; tries < 10; ++tries) {
E 27
		if (0.98 * enough < usecs && usecs < 1.02 * enough)
D 27
			break;
		if (usecs < 150)
E 27
I 27
D 45
			return N;
E 45
I 45
			return (N);
E 45
		if (usecs < 1000)
E 27
			N *= 10;
		else {
			double  n = N;

			n /= usecs;
			n *= enough;
			N = n + 1;
E 18
E 17
		}
I 21
D 27
		if (tries > 100) return (-1);
E 27
I 27
		usecs = time_N(N);
E 27
E 21
D 17
		e = REAL_SHORT;
E 17
I 17
D 18
		return (e = SHORT);
E 18
E 17
	}
D 17
	if (!enough || enough < e) {
		return (e);
	}
E 17
I 17
D 18
	if (enough < 50000) return (50000);
E 17
	return (enough);
E 18
I 18
D 27
	return N;
E 27
I 27
D 45
	return -1;
E 45
I 45
	return (-1);
E 45
E 27
E 18
}
I 18

/*
 * We want to verify that small modifications proportionally affect the runtime
 */
D 32
#define	POINTS	4
E 32
I 32
static double test_points[] = {1.015, 1.02, 1.035};
E 32
static int
D 27
test_time(int tries, int enough)
E 27
I 27
test_time(int enough)
E 27
{
D 32
	int     i, j, N = find_N(enough);
	int     n[POINTS], usecs[POINTS];
I 27
	int	expected[POINTS];
E 27
	double  rate[POINTS];
E 32
I 32
D 37
	int     i, N, usecs, expected, baseline;
E 37
I 37
	int     i;
D 48
	long	N;
E 48
I 48
	iter_t	N;
E 48
D 40
	uint64	usecs, expected, baseline;
E 40
I 40
	uint64	usecs, expected, baseline, diff;
E 40
E 37
E 32

D 32
	if (N <= 0)
E 32
I 32
	if ((N = find_N(enough)) <= 0)
E 32
D 45
		return 0;
E 45
I 45
		return (0);
E 45

D 32
	for (i = 0; i < POINTS; ++i) {
D 27
		n[i] = (int) ((double) N * (1.0 + (double) i * 0.01));
		usecs[i] = time_N(tries, n[i]);
E 27
I 27
		double fraction = 1.0 + (double) i * 0.005;
		n[i] = (int)((double) N * fraction);
		usecs[i] = time_N(n[i]);
		expected[i] = (int)((double)usecs[0] * fraction);
E 27
		rate[i] = (double) usecs[i] / n[i];
I 27
D 29
		if (ABS(usecs[i] - expected[i]) / (double)expected[i] > 0.001 ||
		    ABS(enough - usecs[i]) * fraction / (double)enough > 0.03)
				return 0;
E 29
I 29
		if (ABS(enough - usecs[i]) * fraction / (double)enough > 0.03)
E 32
I 32
D 40
	baseline = time_N(N);
E 40
I 40
D 43
	baseline = gettime();
E 43
I 43
	baseline = time_N(N);
E 43
E 40

	for (i = 0; i < sizeof(test_points) / sizeof(double); ++i) {
		usecs = time_N((int)((double) N * test_points[i]));
D 37
		expected = (int)((double)baseline * test_points[i]);
E 37
I 37
		expected = (uint64)((double)baseline * test_points[i]);
E 37
D 40
		if (ABS(expected - usecs) / (double)expected > 0.0025)
E 40
I 40
		diff = expected > usecs ? expected - usecs : usecs - expected;
		if (diff / (double)expected > 0.0025)
E 40
E 32
D 45
			return 0;
E 45
I 45
			return (0);
E 45
E 29
E 27
D 32
		for (j = 0; j < i; ++j) {
D 23
			if (ABS(rate[i] - rate[j]) > 0.01)
E 23
I 23
			if (ABS(rate[i] - rate[j]) > 0.001)
E 23
				return 0;
		}
E 32
	}
D 45
	return 1;
E 45
I 45
	return (1);
E 45
}

D 23
int     possibilities[] =
{
D 22
    1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000,
E 22
I 22
    5000, 6000, 7000, 8000, 9000,
E 22
    10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000,
    100000, 200000, 300000, 400000, 500000
};
E 23
I 23
D 25
static	int     possibilities[] = { 1000, 5000, 10000, 50000, 100000 };
E 25
I 25
D 32
static	int     possibilities[] = { 5000, 10000, 50000, 100000 };
E 32
E 25
E 23

/*
 * We want to find the smallest timing interval that has accurate timing
 */
I 32
static int     possibilities[] = { 5000, 10000, 50000, 100000 };
E 32
static int
D 27
compute_enough(int tries)
E 27
I 27
compute_enough()
E 27
{
	int     i;

I 21
	if (getenv("ENOUGH")) {
		return (atoi(getenv("ENOUGH")));
	}
E 21
	for (i = 0; i < sizeof(possibilities) / sizeof(int); ++i) {
D 27
		if (test_time(tries, possibilities[i]))
E 27
I 27
		if (test_time(possibilities[i]))
E 27
D 45
			return possibilities[i];
E 45
I 45
			return (possibilities[i]);
E 45
	}

D 27
	return possibilities[sizeof(possibilities) / sizeof(int) - 1];
E 27
I 27
	/* 
	 * if we can't find a timing interval that is sufficient, 
	 * then use SHORT as a default.
	 */
D 45
	return SHORT;
E 45
I 45
	return (SHORT);
E 45
E 27
}
I 24

/*
 * This stuff isn't really lib_timing, but ...
 */
void
morefds(void)
{
#ifdef	RLIMIT_NOFILE
	struct	rlimit r;

	getrlimit(RLIMIT_NOFILE, &r);
	r.rlim_cur = r.rlim_max;
	setrlimit(RLIMIT_NOFILE, &r);
#endif
I 63
}

D 64
/* analogous to bzero, bcopy, etc. */
E 64
I 64
/* analogous to bzero, bcopy, etc., except that it just reads
 * data into the processor
 */
E 64
long
D 64
bread(char* buf, long nbytes)
E 64
I 64
bread(void* buf, long nbytes)
E 64
{
	long sum = 0;
D 64
	register long *p, *next, *end;
E 64
I 64
	register long *p, *next;
	register char *end;
E 64

D 64
	end = buf + nbytes;
	for (p = buf, next = p + 128; next <= end; p = next, next += 128) {
E 64
I 64
	p = (long*)buf;
	end = (char*)buf + nbytes;
	for (next = p + 128; (void*)next <= (void*)end; p = next, next += 128) {
E 64
		sum +=
			p[0]+p[1]+p[2]+p[3]+p[4]+p[5]+p[6]+p[7]+
			p[8]+p[9]+p[10]+p[11]+p[12]+p[13]+p[14]+
			p[15]+p[16]+p[17]+p[18]+p[19]+p[20]+p[21]+
			p[22]+p[23]+p[24]+p[25]+p[26]+p[27]+p[28]+
			p[29]+p[30]+p[31]+p[32]+p[33]+p[34]+p[35]+
			p[36]+p[37]+p[38]+p[39]+p[40]+p[41]+p[42]+
			p[43]+p[44]+p[45]+p[46]+p[47]+p[48]+p[49]+
			p[50]+p[51]+p[52]+p[53]+p[54]+p[55]+p[56]+
			p[57]+p[58]+p[59]+p[60]+p[61]+p[62]+p[63]+
			p[64]+p[65]+p[66]+p[67]+p[68]+p[69]+p[70]+
			p[71]+p[72]+p[73]+p[74]+p[75]+p[76]+p[77]+
			p[78]+p[79]+p[80]+p[81]+p[82]+p[83]+p[84]+
			p[85]+p[86]+p[87]+p[88]+p[89]+p[90]+p[91]+
			p[92]+p[93]+p[94]+p[95]+p[96]+p[97]+p[98]+
			p[99]+p[100]+p[101]+p[102]+p[103]+p[104]+
			p[105]+p[106]+p[107]+p[108]+p[109]+p[110]+
			p[111]+p[112]+p[113]+p[114]+p[115]+p[116]+
			p[117]+p[118]+p[119]+p[120]+p[121]+p[122]+
			p[123]+p[124]+p[125]+p[126]+p[127];
	}
D 64
	for (next = p + 1; next <= end; p = next, next++) {
E 64
I 64
	for (next = p + 16; (void*)next <= (void*)end; p = next, next += 16) {
		sum +=
			p[0]+p[1]+p[2]+p[3]+p[4]+p[5]+p[6]+p[7]+
			p[8]+p[9]+p[10]+p[11]+p[12]+p[13]+p[14]+
			p[15];
	}
	for (next = p + 1; (void*)next <= (void*)end; p = next, next++) {
E 64
		sum += *p;
	}
	return sum;
E 63
}

I 33
void
E 33
touch(char *buf, int nbytes)
{
	static	psize;

	if (!psize) {
I 30
D 31
#if defined(hpux) || defined(__hpux)
#define getpagesize()	4096
#endif
E 31
E 30
		psize = getpagesize();
	}
	while (nbytes > 0) {
		*buf = 1;
		buf += psize;
		nbytes -= psize;
	}
}
I 31

I 53
int*
D 55
permutation(int max)
E 55
I 55
permutation(int max, int scale)
E 55
{
	int	i, v;
	static unsigned int r = 0;
	int*	result = (int*)malloc(max * sizeof(int));

I 57
	if (result == NULL) return NULL;

E 57
	for (i = 0; i < max; ++i) {
D 55
		result[i] = i;
E 55
I 55
		result[i] = i * scale;
E 55
	}

	if (r == 0)
		r = (getpid()<<6) ^ getppid() ^ rand() ^ (rand()<<10);

	/* randomize the sequence */
	for (i = max - 1; i > 0; --i) {
		r = (r << 1) ^ rand();
		v = result[r % (i + 1)];
		result[r % (i + 1)] = result[i];
		result[i] = v;
	}

#ifdef _DEBUG
	fprintf(stderr, "permutation(%d): {", max);
	for (i = 0; i < max; ++i) {
	  fprintf(stderr, "%d", result[i]);
	  if (i < max - 1) 
	    fprintf(stderr, ",");
	}
	fprintf(stderr, "}\n");
	fflush(stderr);
#endif /* _DEBUG */

	return (result);
}

I 61
int
cp(char* src, char* dst, mode_t mode)
{
	int sfd, dfd;
	char buf[8192];
	ssize_t size;

	if ((sfd = open(src, O_RDONLY)) < 0) {
		return -1;
	}
	if ((dfd = open(dst, O_CREAT|O_TRUNC|O_RDWR, mode)) < 0) {
		return -1;
	}
	while ((size = read(sfd, buf, 8192)) > 0) {
		if (write(dfd, buf, size) < size) return -1;
	}
	fsync(dfd);
	close(sfd);
	close(dfd);
}

E 61
I 58
D 59
#if defined(srand48) && srand48 == srand
double
drand48(void)
{
	return (double)rand() / RAND_MAX;
}
#endif

E 59
E 58
E 53
#if defined(hpux) || defined(__hpux)
int
getpagesize()
{
D 45
	return sysconf(_SC_PAGE_SIZE);
E 45
I 45
	return (sysconf(_SC_PAGE_SIZE));
E 45
I 37
}
#endif

#ifdef WIN32
int
getpagesize()
{
	SYSTEM_INFO s;

	GetSystemInfo(&s);
D 45
	return (int)s.dwPageSize;
E 45
I 45
	return ((int)s.dwPageSize);
E 45
}

LARGE_INTEGER
getFILETIMEoffset()
{
	SYSTEMTIME s;
	FILETIME f;
	LARGE_INTEGER t;

	s.wYear = 1970;
	s.wMonth = 1;
	s.wDay = 1;
	s.wHour = 0;
	s.wMinute = 0;
	s.wSecond = 0;
	s.wMilliseconds = 0;
	SystemTimeToFileTime(&s, &f);
	t.QuadPart = f.dwHighDateTime;
	t.QuadPart <<= 32;
	t.QuadPart |= f.dwLowDateTime;
D 45
	return t;
E 45
I 45
	return (t);
E 45
}

int
gettimeofday(struct timeval *tv, struct timezone *tz)
{
	LARGE_INTEGER			t;
	FILETIME			f;
	double					microseconds;
	static LARGE_INTEGER	offset;
	static double			frequencyToMicroseconds;
	static int				initialized = 0;
	static BOOL				usePerformanceCounter = 0;

	if (!initialized) {
		LARGE_INTEGER performanceFrequency;
		initialized = 1;
		usePerformanceCounter = QueryPerformanceFrequency(&performanceFrequency);
		if (usePerformanceCounter) {
			QueryPerformanceCounter(&offset);
			frequencyToMicroseconds = (double)performanceFrequency.QuadPart / 1000000.;
		} else {
			offset = getFILETIMEoffset();
			frequencyToMicroseconds = 10.;
		}
	}
	if (usePerformanceCounter) QueryPerformanceCounter(&t);
	else {
		GetSystemTimeAsFileTime(&f);
		t.QuadPart = f.dwHighDateTime;
		t.QuadPart <<= 32;
		t.QuadPart |= f.dwLowDateTime;
	}

	t.QuadPart -= offset.QuadPart;
	microseconds = (double)t.QuadPart / frequencyToMicroseconds;
	t.QuadPart = microseconds;
	tv->tv_sec = t.QuadPart / 1000000;
	tv->tv_usec = t.QuadPart % 1000000;
D 45
	return 0;
E 45
I 45
	return (0);
E 45
E 37
}
#endif
E 31
E 24
E 18
E 16
D 15
#endif

E 14
#define RUSAGE
#ifdef	RUSAGE
#include <sys/resource.h>
#define	secs(tv)	(tv.tv_sec + tv.tv_usec / 1000000.0)
#define	mine(f)		(int)(ru_stop.f - ru_start.f)

static struct rusage ru_start, ru_stop;

void
rusage(void)
{
	double  sys, user, idle;
	double  per;
D 14
	double  timespent();
E 14

	sys = secs(ru_stop.ru_stime) - secs(ru_start.ru_stime);
	user = secs(ru_stop.ru_utime) - secs(ru_start.ru_utime);
	idle = timespent() - (sys + user);
	per = idle / timespent() * 100;
	fprintf(ftiming, "real=%.2f sys=%.2f user=%.2f idle=%.2f stall=%.0f%% ",
	    timespent(), sys, user, idle, per);
	fprintf(ftiming, "rd=%d wr=%d min=%d maj=%d ctx=%d\n",
	    mine(ru_inblock), mine(ru_oublock),
	    mine(ru_minflt), mine(ru_majflt),
	    mine(ru_nvcsw) + mine(ru_nivcsw));
}

#endif	/* RUSAGE */
E 15
E 10
E 9
E 3
E 2
I 1
E 1
