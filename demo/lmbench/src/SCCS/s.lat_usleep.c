H31242
s 00019/00009/00232
d D 1.4 02/10/18 10:59:34 staelin 5 4
c lat_usleep.c:
c   - portability fixes, at least for HP-UX
c   - add visible notification to the output as to whether realtime 
c     scheduling was used or not
c   - cleanup output generation code a bit
cC
cK10126
e
s 00111/00020/00130
d D 1.3 02/10/18 10:04:52 staelin 4 3
c lat_usleep.c:
c   - add support for more sleep interfaces, namely nanosleep, select
c     and pselect
c   - also add ability to specify realtime scheduling (if run as root)
cC
cK62713
e
s 00017/00007/00133
d D 1.2 02/10/17 14:36:08 staelin 3 2
c lat_usleep.c: cleanup the code a bit.
cC
cK26884
e
s 00140/00000/00000
d D 1.1 02/10/17 14:15:33 staelin 2 1
cC
cF1
cK12852
cO-rwxrwxr--
e
s 00000/00000/00000
d D 1.0 02/10/17 14:15:33 staelin 1 0
c BitKeeper file /usr/WebPaper/users/staelin/src/LMbench3/src/lat_usleep.c
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHhpli69.hpli.hpl.hp.com
cK15344
cPsrc/lat_usleep.c
cR9253b2da8ef3ceda
cV4
cX0x821
cZ+02:00
e
u
U
f e 0
f x 0x821
t
T
I 2
/*
 * lat_usleep.c - usleep duration/latency
 *
D 4
 * The interval API for usleep(3) and the getitimer(2) and 
 * setitimer(2) interval timers support resolutions down to 
 * a micro-second.  However, implementations do not support 
E 4
I 4
 * The APIs for usleep(3), nanosleep(2), select(2), pselect(2),
 * getitimer(2) and setitimer(2) support resolutions down to 
 * a micro-second.  However, many implementations do not support 
E 4
 * such resolution.  Most current implementations (as of Fall 
 * 2002) simply put the process back on the run queue and the 
 * process may get run on the next scheduler time slice (10-20 
 * milli-second resolution).
 *
 * This benchmark measures the true latency from the timer/sleep
 * call to the resumption of program execution.  If the timers
 * actually worked properly, then the latency would be identical
 * to the requested duration, or a little longer, so the input
 * and output figures would be nearly identical.  In most current
 * implementations the value is rounded up to the next scheduler
 * timeslice (e.g., a resolution of 20 milli-seconds, with all
 * values rounded up).
 *
 * usage: lat_usleep [-u | -i] [-W <warmup>] [-N <repetitions>] usecs
 *
 * Copyright (c) 2002 Carl Staelin.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
char           *id = "$Id$\n";

#include "bench.h"
I 4
#include <sched.h>
D 5
#include <sys/select.h>
E 5
E 4

I 3
D 4
typedef     enum {ITIMER, USLEEP} timer_e;
E 4
I 4
typedef     enum {USLEEP, NANOSLEEP, SELECT, PSELECT, ITIMER} timer_e;
E 4

E 3
uint64          caught,
                n;
struct itimerval value;

I 4
typedef struct _state {
    unsigned long usecs;
} state_t;

E 4
void
bench_usleep(iter_t iterations, void *cookie)
{
D 4
    unsigned long  *usecs = (unsigned long *) cookie;
E 4
I 4
    state_t        *state = (state_t*)cookie;

    while (iterations-- > 0) {
	usleep(state->usecs);
    }
}

void
bench_nanosleep(iter_t iterations, void *cookie)
{
    state_t        *state = (state_t*)cookie;
    struct timespec req;
    struct timespec rem;

    req.tv_sec = 0;
    req.tv_nsec = state->usecs * 1000;

    while (iterations-- > 0) {
	if (nanosleep(&req, &rem) < 0) {
	    while (nanosleep(&rem, &rem) < 0)
		;
	}
    }
}

void
bench_select(iter_t iterations, void *cookie)
{
    state_t        *state = (state_t*)cookie;
    struct timeval  tv;
E 4

    while (iterations-- > 0) {
D 4
	usleep(*usecs);
E 4
I 4
	tv.tv_sec = 0;
	tv.tv_usec = state->usecs;
	select(0, NULL, NULL, NULL, &tv);
    }
}

I 5
#ifdef _POSIX_SELECT
E 5
void
bench_pselect(iter_t iterations, void *cookie)
{
    state_t        *state = (state_t*)cookie;
    struct timespec ts;

    while (iterations-- > 0) {
	ts.tv_sec = 0;
	ts.tv_nsec = state->usecs * 1000;
	pselect(0, NULL, NULL, NULL, &ts, NULL);
E 4
    }
}
I 5
#endif /* _POSIX_SELECT */
E 5

void
interval()
{
    if (++caught == n) {
	caught = 0;
	n = benchmp_interval(benchmp_getstate());
    }

    setitimer(ITIMER_REAL, &value, NULL);
}

void
initialize(void *cookie)
{
D 4
    unsigned long  *usecs = (unsigned long *) cookie;
E 4
I 4
    state_t        *state = (state_t*)cookie;
E 4
    struct sigaction sa;

    value.it_interval.tv_sec = 0;
D 4
    value.it_interval.tv_usec = *usecs;
E 4
I 4
    value.it_interval.tv_usec = state->usecs;
E 4
    value.it_value.tv_sec = 0;
D 4
    value.it_value.tv_usec = *usecs;
E 4
I 4
    value.it_value.tv_usec = state->usecs;
E 4

    sa.sa_handler = interval;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGALRM, &sa, 0);
}

void
bench_itimer(iter_t iterations, void *cookie)
{
    n = iterations;
    caught = 0;

    /*
     * start the first timing interval 
     */
    start(0);

    /*
     * create the first timer, causing us to jump to interval() 
     */
    setitimer(ITIMER_REAL, &value, NULL);

    while (1) {
	sleep(100000);
    }
}

I 4
D 5
void
E 5
I 5
int
E 5
set_realtime()
{
    struct sched_param sp;

    sp.sched_priority = sched_get_priority_max(SCHED_RR);
D 5
    sched_setscheduler(0, SCHED_RR, &sp);
E 5
I 5
    if (sched_setscheduler(0, SCHED_RR, &sp) >= 0) return TRUE;
    perror("sched_setscheduler");
    return FALSE;
E 5
}

E 4
int
main(int ac, char **av)
{
I 4
    int             realtime = 0;
E 4
D 3
    int             u = 1;
E 3
    int             warmup = 0;
    int             repetitions = TRIES;
    int             c;
    char            buf[512];
I 3
    timer_e	    what = USLEEP;
E 3
D 4
    char           *usage = "[-u|i] [-W <warmup>] [-N <repetitions>] usecs\n";
    unsigned long   usecs;
E 4
I 4
    state_t         state;
I 5
    char           *scheduler = "";
    char           *mechanism = "usleep";
E 5
    char           *usage = "[-r] [-u <method>] [-W <warmup>] [-N <repetitions>] usecs\nmethod=usleep|nanosleep|select|pselect|itimer\n";

    realtime = 0;
E 4

D 4
    while ((c = getopt(ac, av, "iuW:N:")) != EOF) {
E 4
I 4
    while ((c = getopt(ac, av, "ru:W:N:")) != EOF) {
E 4
	switch (c) {
D 4
	case 'i':
D 3
	    u = 0;
E 3
I 3
	    what = ITIMER;
E 4
I 4
	case 'r':
	    realtime = 1;
E 4
E 3
	    break;
	case 'u':
D 3
	    u = 1;
E 3
I 3
D 4
	    what = USLEEP;
E 4
I 4
	    if (strcmp(optarg, "usleep") == 0) {
		what = USLEEP;
I 5
		mechanism = "usleep";
E 5
	    } else if (strcmp(optarg, "nanosleep") == 0) {
		what = NANOSLEEP;
I 5
		mechanism = "nanosleep";
E 5
	    } else if (strcmp(optarg, "select") == 0) {
		what = SELECT;
I 5
		mechanism = "select";
#ifdef _POSIX_SELECT
E 5
	    } else if (strcmp(optarg, "pselect") == 0) {
		what = PSELECT;
I 5
		mechanism = "pselect";
#endif /* _POSIX_SELECT */
E 5
	    } else if (strcmp(optarg, "itimer") == 0) {
		what = ITIMER;
I 5
		mechanism = "itimer";
E 5
	    } else {
		lmbench_usage(ac, av, usage);
	    }
E 4
E 3
	    break;
	case 'W':
	    warmup = atoi(optarg);
	    break;
	case 'N':
	    repetitions = atoi(optarg);
	    break;
	default:
	    lmbench_usage(ac, av, usage);
	    break;
	}
    }
    if (optind != ac - 1) {
	lmbench_usage(ac, av, usage);
    }

D 4
    usecs = bytes(av[optind]);
E 4
I 4
    state.usecs = bytes(av[optind]);
D 5
    if (realtime) set_realtime();
E 5
I 5
    if (realtime && set_realtime()) scheduler = "realtime ";
E 5

E 4
D 3
    if (u) {
	benchmp(NULL, bench_usleep, NULL, 0, 1, warmup, repetitions, &usecs);
E 3
I 3
    switch (what) {
    case USLEEP:
	benchmp(NULL, bench_usleep, NULL, 
D 4
		0, 1, warmup, repetitions, &usecs);
E 3
	sprintf(buf, "usleep %lu microseconds", usecs);
E 4
I 4
		0, 1, warmup, repetitions, &state);
D 5
	sprintf(buf, "usleep %lu microseconds", state.usecs);
E 5
	break;
    case NANOSLEEP:
	benchmp(NULL, bench_nanosleep, NULL, 
		0, 1, warmup, repetitions, &state);
D 5
	sprintf(buf, "nanosleep %lu microseconds", state.usecs);
E 5
	break;
    case SELECT:
	benchmp(NULL, bench_select, NULL, 
		0, 1, warmup, repetitions, &state);
D 5
	sprintf(buf, "select %lu microseconds", state.usecs);
E 5
	break;
I 5
#ifdef _POSIX_SELECT
E 5
    case PSELECT:
	benchmp(NULL, bench_pselect, NULL, 
		0, 1, warmup, repetitions, &state);
D 5
	sprintf(buf, "pselect %lu microseconds", state.usecs);
E 5
E 4
D 3
    } else {
	benchmp(initialize, bench, NULL, 0, 1, warmup, repetitions, &usecs);
E 3
I 3
	break;
I 5
#endif /* _POSIX_SELECT */
E 5
    case ITIMER:
	benchmp(initialize, bench_itimer, NULL, 
D 4
		0, 1, warmup, repetitions, &usecs);
E 3
	sprintf(buf, "itimer %lu microseconds", usecs);
E 4
I 4
		0, 1, warmup, repetitions, &state);
D 5
	sprintf(buf, "itimer %lu microseconds", state.usecs);
E 5
E 4
I 3
	break;
    default:
	lmbench_usage(ac, av, usage);
	break;
E 3
    }
I 5
    sprintf(buf, "%s%s %lu microseconds", scheduler, mechanism, state.usecs);
E 5
    micro(buf, get_n());
    return (0);
}
E 2
I 1
E 1
