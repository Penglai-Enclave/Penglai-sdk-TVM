h08811
s 00018/00012/00489
d D 1.19 00/09/13 12:43:31 staelin 20 19
c - Replace "mhz" custom command-line parsing code with getopt()-based command line parsing
cC
cK61554
e
s 00001/00002/00500
d D 1.18 00/08/01 09:21:27 staelin 19 18
c - Remove unnecessary test for time > 0 before call to insertsort()
cC
cK55858
e
s 00004/00002/00498
d D 1.17 00/06/25 13:33:26 staelin 18 17
c - fix bug in compute_mhz so that we don't check subsets with too few data points
cC
cK57221
e
s 00002/00002/00498
d D 1.16 00/06/25 13:20:19 staelin 17 16
c - fix buglet in median computation
cC
cK56470
e
s 00064/00000/00436
d D 1.15 00/06/21 19:28:44 staelin 16 15
c - Add '-d' flag to print out debugging information
cC
cK55476
cZ+03:00
e
s 00001/00001/00435
d D 1.14 00/02/23 11:15:41 staelin 15 14
c Update to the new result_t structure.
cC
cK21646
e
s 00005/00003/00431
d D 1.13 00/02/02 09:57:43 staelin 14 13
c Added some checks to ensure that bad measurements are handled properly
cC
cHhpli8.hpli.hpl.hp.com
cK21318
cZ+02:00
e
s 00003/00005/00431
d D 1.12 98/06/29 22:41:36 lm 13 12
c carl's Wall changes.
cC
cHlm.bitmover.com
cK16240
cSAlpha2.11
e
s 00002/00002/00434
d D 1.11 98/05/19 17:20:56 lm 12 11
c merge Carl's first diff set from Israel.
cHwork
cK16930
cZ-07:00
e
s 00087/00104/00349
d D 1.10 98/05/07 15:53:00 staelin 11 10
c - changed MHZ expression 8
c - changed the method for detecting too much variance;
c 	- used to examine median percent difference between min and
c 	  median experimental results for each experiment
c 	- now compute mhz using min data and nearly min data and if
c 	  the difference is less than 1% or 1MHz then we accept the result
c - we use the mode rather than the median result in super_gcd
c - modified MHZ() macro to match new BENCH() macro
cHhpisc8.lempel
cK19335
cZ-00:00
e
s 00192/00023/00261
d D 1.9 98/03/06 12:01:33 lm 10 9
c Carls latest.
cK18169
e
s 00011/00082/00273
d D 1.8 97/10/30 18:33:43 lm 9 8
c from Carl.
cK45666
cZ-08:00
e
s 00316/00037/00039
d D 1.7 97/10/25 10:53:29 lm 8 7
c Carl's new mhz.c
cK39985
e
s 00024/00022/00052
d D 1.6 97/06/15 22:38:58 lm 7 6
c lint
cK27276
e
s 00030/00015/00044
d D 1.5 97/06/13 20:27:23 lm 6 5
c more precision.
cK26388
e
s 00000/00004/00059
d D 1.4 97/06/12 21:30:06 lm 5 4
c new bench.h macros.
cK08170
cZ-07:00
e
s 00023/00033/00040
d D 1.3 96/11/11 03:36:51 lm 4 3
c Auto adjusting changes.
cK15459
cZ-08:00
e
s 00000/00001/00073
d D 1.2 96/05/30 00:33:07 lm 3 2
c no what strings
cK17750
cZ-07:00
e
s 00074/00000/00000
d D 1.1 94/11/18 00:51:55 lm 2 1
c Initial revision
cK19821
e
s 00000/00000/00000
d D 1.0 94/11/18 00:51:54 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK23994
cPsrc/mhz.c
cRa8a6d33bb26f366
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
 * mhz.c - calculate clock rate and megahertz
 *
 * Usage: mhz [-c]
 *
D 8
 * The sparc specific code is to get around a feature of SuperSPARC
 * that does two adds in one clock.  Apparently, only SuperSPARC does this.
 * Thanks to John Mashey (mash@sgi.com) for explaining SuperSPARC to me.
E 8
I 8
 *******************************************************************
E 8
 *
D 8
 * The AIX specific code is because the C compiler on rs6000s does not 
 * respect the register directive.  "a" below is a stack variable and 
 * there are two instructions per increment instead of one.
 * Please note that this may not be correct for other AIX systems.
E 8
I 8
 * Caveat emptor and other warnings
E 8
 *
I 8
 * This code must be compiled using the optimizer!  If you don't
 * compile this using the optimizer, then many compilers don't
 * make good use of the registers and your inner loops end up
 * using stack variables, which is SLOW.  
 *
 * Also, it is sensitive to other processor load.  When running
 * mhz with "rtprio" (real-time priority), I have never had mhz
 * make a mistake on my machine.  At other times mhz has been
 * wrong about 10% of the time.
 *
 * If there is too much noise/error in the data, then this program
 * will usually return a clock speed that is too high.
 *
 *******************************************************************
 * 
 * Constraints
 *
 * mhz.c is meant to be platform independent ANSI/C code, and it 
 * has as little platform dependent code as possible.  
 *
 * This version of mhz is designed to eliminate the variable 
 * instruction counts used by different compilers on different 
 * architectures and instruction sets.  It is also structured to
 * be tightly interlocked so processors with super-scalar elements
 * or dynamic instructure reorder buffers cannot overlap the
 * execution of the expressions.
 *
 * We have to try and make sure that the code in the various
 * inner loops does not fall out of the on-chip instruction cache
 * and that the inner loop variables fit inside the register set.
 * The i386 only has six addressable registers, so we had to make
 * sure that the inner loop procedures had fewer variables so they
 * would not spill onto the stack.
 *
 *******************************************************************
 *
 * Algorithm
 *
 * We can compute the CPU cycle time if we can get the compiler
 * to generate (at least) two instruction sequences inside loops
 * where the inner loop instruction counts are relatively prime.  
 * We have several different loops to increase the chance that 
 * two of them will be relatively prime on any given architecture.  
 *
 * This technique makes no assumptions about the cost of any single
 * instruction or the number of instructions used to implement a
 * given expression.  We just hope that the compiler gets at least
 * two inner loop instruction sequences with lengths that are
 * relatively prime.  The "relatively prime" makes the greatest
 * common divisor method work.  If all the instructions sequences
 * have a common factor (e.g. 2), then the apparent CPU speed will
 * be off by that common factor.  Also, if there is too much
 * variability in the data so there is no apparent least common
 * multiple within the error bounds set in multiple_approx, then
 * we simply return the maximum clock rate found in the loops.
 *
 * The processor's clock speed is the greatest common divisor
 * of the execution frequencies of the various loops.  For
 * example, suppose we are trying to compute the clock speed
 * for a 120Mhz processor, and we have two loops:
 *	SHR		--- two cycles to shift right
 *	SHR;ADD		--- three cycles to SHR and add
 * then the expression duration will be:
 *	SHR		11.1ns (2 cycles/SHR)
 *	SHR;ADD		16.6ns (3 cycles/SHR;ADD)
 * so the greatest common divisor is 5.55ns and the clock speed
 * is 120Mhz.  Aside from extraneous variability added by poor 
 * benchmarking hygiene, this method should always work when we 
 * are able to get loops with cycle counts that are relatively 
 * prime.
 *
 * Suppose we are unlucky, and we have our two loops do
 * not have relatively prime instruction counts.  Suppose
 * our two loops are:
 *	SHR		11.1ns (2 cycles/SHR)
 *	SHR;ADD;SUB	22.2ns (4 cycles/SHR;ADD;SUB)
 * then the greatest common divisor will be 11.1ns, so the clock
D 10
 * speed will be 60Mhz.
E 10
I 10
 * speed will appear to be 60Mhz.
E 10
 *
 * The loops provided so far should have at least two relatively 
 * prime loops on nearly all architectures.
 *
 *******************************************************************
 *
D 9
 * Copyright (c) 1997 Carl Staelin.  The new alg is Carl's - bugs to him.
E 9
E 8
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
I 6
 * Support for this development by Silicon Graphics is gratefully acknowledged.
 * Support for this development by Hewlett Packard is gratefully acknowledged.
E 6
 * Support for this development by Sun Microsystems is gratefully acknowledged.
I 8
 *
 *******************************************************************
E 8
 */
D 11
char	*id = "$Id$\n";
E 11
I 11
D 12
char	*id = "$Id: mhz.c,v 1.9 1998/03/06 20:01:33 lm Exp $\n";
E 12
I 12
char	*id = "$Id$\n";
E 12
E 11

D 4
#ifndef N
#define N       20000000
#endif
E 4
D 8

E 8
D 4
#include	"timing.c"
E 4
I 4
D 5
#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include "timing.h"
E 5
#include "bench.h"
I 8
#include <math.h>
E 8
E 4

D 4
main(ac, av)
        char  **av;
E 4
I 4
D 7
int
main(int ac, char **av)
E 4
{
D 4
	register a, i;
	int	result = 1024*1024*1024;
	int	tries = 0;
E 4
I 4
D 6
	int	a, usecs, N;
E 6
E 4
	double	mhz;
I 6
	double	overhead;
E 6

D 3
	write(2, id, strlen(id));
E 3
D 4
        for (tries = 0; tries < 5; ++tries) {
                /* time empty loop */
		i = N - 1000;
		a = 1024;
                start();
                while (i > 0) {
#ifdef sparc
#	define	FOUR	a >>= 1; a >>= 1; a >>= 1; a >>= 1;
#else
#	ifdef _AIX	/* really for the rs6000 only */
#		define	FOUR	a++; a++;
#	else
#		define	FOUR	a++; a++; a++; a++;
#	endif
E 4
I 4
D 6
	LOOP_FIRST(N, usecs, ENOUGH);
E 6
I 6
	BENCH(loop(ac), 0);
	overhead = usecs_spent();
	overhead /= get_n();
	BENCH(domhz(ac), 0);
	mhz = usecs_spent();
	mhz /= get_n();
	mhz -= overhead;
	mhz = 1000 / mhz;
	if (ac == 2 && !strcmp(av[1], "-c")) {
		printf("%.4f\n", 1000 / mhz);
	} else {
		printf("%.0f Mhz, %.2f nanosec clock\n", mhz, 1000 / mhz);
	}
	exit(0);
}

E 7
E 6
D 8
#ifdef _AIX	/* really for the rs6000 only */
#	define	FOUR	a++; a++;
E 4
#endif
I 4
#ifdef	sparc
#	define	FOUR	a >>= ac; a >>= ac; a >>= ac; a >>= ac;
#endif
#if	!defined(sparc) && !defined(_AIX)
#	define	FOUR	a += ac; a += ac; a += ac; a += ac;
#endif
E 4
#define TWENTY	FOUR FOUR FOUR FOUR FOUR
#define	H	TWENTY TWENTY TWENTY TWENTY TWENTY
D 4
			H H H H H
			H H H H H
			i -= 1000;
                }
		i = stop();
		if (i < result)
			result = i;
	}
E 4
I 4
D 6
	H H H H H H H H H H
	LOOP_LAST(N, usecs, ENOUGH);
E 6
I 6
#define	BODY	H H H H H H H H H H
E 8
I 8
typedef	long	TYPE;
E 8
E 6

I 8
D 11
#define TEN(_a)	_a _a _a _a _a _a _a _a _a _a
#define FIFTY(_a) TEN(_a) TEN(_a) TEN(_a) TEN(_a) TEN(_a)
#define HUNDRED(_a) FIFTY(_a) FIFTY(_a)
E 11
I 11
#define TEN(A)		A A A A A A A A A A
#define HUNDRED(A)	TEN(A) TEN(A) TEN(A) TEN(A) TEN(A) \
			TEN(A) TEN(A) TEN(A) TEN(A) TEN(A)
E 11

#define MHZ(M, contents)						\
I 16
char*									\
name_##M()								\
{									\
	return #contents;						\
}									\
									\
E 16
D 11
void									\
E 11
I 11
TYPE**									\
E 11
_mhz_##M (register long n, register TYPE **p, 				\
	  register TYPE a, register TYPE b)				\
{ 									\
I 9
D 10
	TYPE ** volatile sink;						\
E 10
E 9
	for (; n > 0; --n) {						\
		HUNDRED(contents)					\
	}								\
D 9
	use_result((uint64)p + a + b);					\
E 9
I 9
D 10
	sink = p + a + b;						\
E 10
I 10
D 11
	use_pointer(p + a + b);						\
E 11
I 11
	return p + a + b;						\
E 11
E 10
E 9
}									\
									\
D 10
double									\
mhz_##M(char **c)							\
E 10
I 10
void									\
mhz_##M(int enough)							\
E 10
{									\
	TYPE	__i = 1;						\
D 10
	double	r;							\
E 10
I 10
D 11
	double    tmp = l_overhead();					\
E 11
E 10
D 13
	long	__n = 1;						\
D 11
	TYPE	*__x=(TYPE *)&__x, **__p=(TYPE **)__x;			\
E 11
I 11
	TYPE	*__x=(TYPE *)&__x, **__p=(TYPE **)__x, **__q;		\
E 13
I 13
	TYPE	*__x=(TYPE *)&__x, **__p=(TYPE **)__x, **__q = NULL;	\
E 13
E 11
D 10
	BENCH(_mhz_##M(__n, __p, __i, __i); __n = 1;, 0)		\
	r = gettime() / (100. * (double)get_n());			\
	*c = #contents;							\
	return r;							\
E 10
I 10
	_mhz_##M(1, __p, 1, 1);						\
D 11
	BENCH1(_mhz_##M(__n, __p, __i, __i); __n = 1;, enough)		\
	tmp *= get_n(); /* loop overhead * number of iterations */	\
E 11
I 11
	BENCH1(__q = _mhz_##M(__n, __p, __i, __i); __n = 1;, enough)	\
	use_pointer((void*)__q);					\
E 11
	save_n(100 * get_n()); /* # of expressions executed */		\
D 11
	settime(gettime() - (uint64)tmp);				\
E 11
E 10
}

MHZ(1, p=(TYPE**)*p;)
MHZ(2, a^=a+a;)
MHZ(3, a^=a+a+a;)
MHZ(4, a>>=b;)
MHZ(5, a>>=a+a;)
I 9
D 10
#if 0
MHZ(6, a^=a+1;)
MHZ(7, a|=(a<<1);)
MHZ(8, a++;a^=1;)
E 10
I 10
MHZ(6, a^=a<<b;)
MHZ(7, a^=a+b;)
D 11
MHZ(8, a^=a+(b=a+1);)
E 11
I 11
MHZ(8, a+=(a+b)&07;)
E 11
E 10
MHZ(9, a++;a^=1;a<<=1;)
D 10
#endif /* 0 */
E 10
E 9

D 10
typedef double (*loop_f)(char **);
loop_f loops[] = { 
E 10
I 10
typedef void (*loop_f)(int);
loop_f loops[] = {
E 10
	mhz_1,
	mhz_2,
	mhz_3,
	mhz_4,
	mhz_5,
I 10
	mhz_6,
	mhz_7,
	mhz_8,
	mhz_9,
E 10
};

I 10

E 10
#define NTESTS	(sizeof(loops) / sizeof(loop_f))
I 10
#define BIT_SET(A,bit) ((A) & 1 << (bit))
E 10

I 10
D 11
int
n_ones(int a)
{
	int	result = 0;
E 11

D 11
	for (result = 0; a; a>>=1)
		if (a & 1) ++result;

	return result;
}

E 11
E 10
/*
I 10
D 11
 * estimate how much noise (error) is contained in the experimental data
 *
 * our estimate is based on the median percentage difference between the
 * minimum and median values of each experiment.
 */
double
error_estimate(result_t data[][TRIES])
{
	int i;
	double errors[NTESTS];

	for (i = 0; i < NTESTS; ++i) {
	  double median = data[i][TRIES/2].u / (double)data[i][TRIES/2].n;
	  double minimum = data[i][TRIES-1].u / (double)data[i][TRIES-1].n;
	  errors[i] = (median - minimum) / minimum;
	}
	qsort(errors, NTESTS, sizeof(double), double_compare);
	return 100. * errors[NTESTS/2];
}

/*
E 11
 * This is used to filter out bad points (mostly ones that have had
 * their inner loop optimized away).  Bad points are those with values
 * less than 1/20th of the median value and more than 20 times the
 * median value.
 *
 * filter_data returns the number of valid data points, and puts the
 * valid points in the lower part of the values[] array.
 */
int
filter_data(double values[], int size)
{
	int i;
	int tests;
	double median;
D 17
	double *d = (double *)malloc(size * sizeof(double));
E 17
I 17
	double *d = (double *)malloc((size + 1) * sizeof(double));
E 17

	for (i = 0; i < size; ++i) d[i] = values[i];
	qsort(d, size, sizeof(double), double_compare);

	median = d[size/2];
D 17
	if (size % 2 == 0) median = (median + d[size/2 - 1]) / 2.0;
E 17
I 17
	if (size > 0 && size % 2 == 0) median = (median + d[size/2 - 1]) / 2.0;
E 17

	free(d);

	/* if the data point is inside the envelope of acceptable 
	 * results, then keep it, otherwise discard it
	 */
	for (i = 0, tests = 0; i < size; ++i)
		if (0.05 * median < values[i] && values[i] < 20.0 * median) {
			if (i > tests) values[tests] = values[i];
			tests++;
		}

	return tests;
}

/*
 * make sure that there are enough points with significantly
 * different data values (greater than 5% difference) in the
 * data subset.
 */
int
classes(double values[], int size)
{
	int i;
	double median;
	double *d = (double *)malloc(size * sizeof(double));
	int classid;

	for (i = 0; i < size; ++i) d[i] = values[i];
	qsort(d, size, sizeof(double), double_compare);

	median = d[size/2];
	if (size % 2 == 0) median = (median + d[size/2 - 1]) / 2.0;

	/* if the difference is less than 1/20th of the median, then
	 * we assume that the two points are the same
	 */
	for (i = 1, classid = 1; i < size; ++i)
D 11
	    if ((d[i] - d[i-1]) < 0.05 * median) classid++;
E 11
I 11
	    if ((d[i] - d[i-1]) > 0.05 * median) classid++;
E 11

	free(d);
	return classid;
}

/*
I 11
 * mode
 *
 * return the most common value (within 1MHz)
 */
int
mode(double values[], int n)
{
	int	i, n_mode, n_curr;
	int	mode, curr;

	qsort(values, n, sizeof(double), double_compare);

	n_mode = 1;
	n_curr = 1;
	mode = (int)(values[0] + 0.5);
	curr = (int)(values[0] + 0.5);

	for (i = 1; i < n; ++i) {
		int v = (int)(values[i] + 0.5);
		if (curr != v) {
			curr = v;
			n_curr = 0;
		}
		n_curr++;
		if (n_curr > n_mode) {
			mode = curr;
			n_mode = n_curr;
		}
	}

	return mode;
}

/*
E 11
E 10
D 9
 * return the min value of an array of doubles
 */
double
double_min(double *values, int size)
{
	int	i;
	double	min = values[0];
	for (i = 1; i < size; ++i)
		if (values[i] < min) min = values[i];
	return min;
}

/*
 * regression(x, y, n, a, b, sig_a, sig_b, chi2)
 *
 * This routine is derived from equations in "Numerical Recipes in C" 
 * (second edition) by Press, et. al.,  pages 661-665.
 *
 * compute the linear regression y = a + bx for (x,y)
 *
 * returns the coefficients a and b, along with an estimation of their
 * error (standard deviation) in sig_a and sig_b.
 *
 * returns chi2 for "goodness of fit" information.
 */

E 8
I 7
void
E 7
E 4
D 6
	/*
	 * We figure that the loop overhead is about 5 instructions out of 1000.
	 * So we figure that we acually execute N * 1.005 instructions.
	 */
D 4
	mhz = (N * 1.005) / result;
E 4
I 4
	mhz = (N * 1000 * 1.005) / usecs;
E 4
	if (ac == 2 && !strcmp(av[1], "-c")) {
		printf("%.4f\n", 1000 / mhz);
	} else {
D 4
		printf("%.2f Mhz, %.0f nanosec clock\n", mhz, 1000 / mhz);
E 4
I 4
		printf("%.0f Mhz, %.2f nanosec clock\n", mhz, 1000 / mhz);
E 4
	}
E 6
I 6
D 8
domhz(register int ac)
E 8
I 8
mhz_regression(double *x, double *y, int n,
	   double *a, double *b, double *sig_a, double *sig_b, 
	   double *chi2)
E 8
{
D 8
	register int a;
E 8
I 8
	int	i;
	double	S = 0.0, Sx = 0.0, Sy = 0.0, Stt = 0.0, Sx_S;
E 8

D 8
	BODY;
E 6
I 4
	use_result(a);
E 8
I 8
	/* compute some basic statistics */
	for (i = 0; i < n; ++i) {
		Sx += x[i];
		Sy += y[i];
	}
	S = n;

	*b = 0.0;
	Sx_S = Sx / S;
	for (i = 0; i < n; ++i) {
		/* 
		 * Equation 15.2.15 for t
		 * Equation 15.2.16 for Stt
		 * Equation 15.2.17 for b, do summation portion of equation
		 *	compute Sum i=0,n-1 (t_i * y[i] / sig[i]))
		 */
		double t_i = x[i] - Sx_S;
		Stt += t_i * t_i;
		*b  += t_i * y[i];
	}

	/*
	 * Equation 15.2.17 for b, do 1/Stt * summation
	 * Equation 15.2.18 for a
	 * Equation 15.2.19 for sig_a
	 * Equation 15.2.20 for sig_b
	 */
	*b /= Stt;
	*a = (Sy - *b * Sx) / S;
	*sig_a = sqrt((1.0 + (Sx * Sx) / (S * Stt)) / S);
	*sig_b = sqrt(1.0 / Stt);

	/* Equation 15.2.2 for chi2, the merit function */
	*chi2 = 0.0;
	for (i = 0; i < n; ++i) {
		double merit = y[i] - (*a) - (*b) * x[i];
		*chi2 += merit * merit;
	}
	*sig_a *= sqrt((*chi2)/(n - 2));
	*sig_b *= sqrt((*chi2)/(n - 2));
E 8
E 4
D 6
	exit(0);
E 6
}
I 6

I 8
/*
E 9
 * cross_values
 *
 * This routine will create new data points by subtracting pairs
 * of data points.
 */
E 8
I 7
void
E 7
D 8
loop(register int ac)
E 8
I 8
cross_values(double values[], int size, double **cvalues, int *csize)
E 8
{
D 8
	use_result(ac);
E 8
I 8
	int	i, j;
D 13
	double	sig;
E 13

	*cvalues = (double *)malloc(size * size * sizeof(double));
	*csize = 0;

	for (i = 0; i < size; ++i) {
		(*cvalues)[(*csize)++] = values[i];
		/* create new points with the differences */
		for (j = i + 1; j < size; ++j) {
			(*cvalues)[(*csize)++] = ABS(values[i] - values[j]);
		}
	}
E 8
}
I 7

I 8

/*
 * gcd
 *
 * return the greatest common divisor of the passed values (within a
 * margin of error because these are experimental results, not
 * theoretical numbers).  We do this by guessing how many instructions
 * are in each loop, and then trying to fit a straight line through
 * the (instruction count, time) points.  The regression is of the
 * form:
 *
 *	y = a + b * x
 *
 * The time for an individual instruction is "b", while "a" should
 * be 0.  The trick is to figure out which guess is the right one!
 *
 * We assume that the gcd is the first value at which we have 
 * significantly improved regression fit (as measured by chi2).
 *
 * We increase the number of experimental points (and generate
 * more small points) by adding points for the differences between
 * measured values (and compute the standard error appropriately).
 *
 * We want the regression line to go through the origin, so we
 * add an artificial point at (0,0) with a tiny standard error.
 */
double 
D 11
gcd(double values[], int vsize)
E 11
I 11
gcd(double values[], int size)
E 11
{
/* assumption: shortest inner loop has no more than this many instructions */
#define	MAX_COUNT	6
D 11
	int	i, j, size, count;
	int	index = 1;
	double	min;
	double *x = (double *)malloc(vsize * vsize * sizeof(double));
	double *y;
	double	result, a, b, sig_a, sig_b, chi2;
	double	min_chi2 = 100.0;
E 11
I 11
	int	i, n, count;
D 13
	double	min, result, min_chi2, a, b, sig_a, sig_b, chi2;
E 13
I 13
	double	min, result, min_chi2 = 0.0, a, b, sig_a, sig_b, chi2;
E 13
	double *y, *x = (double *)malloc(size * size * sizeof(double));
E 11

	/* find the smallest value */
D 11
	min = double_min(values, vsize);
E 11
I 11
D 13
	min = double_min(values, size);
E 13
I 13
	result = min = double_min(values, size);
E 13
E 11

	/* create new points by subtracting each pair of values */
D 11
	cross_values(values, vsize, &y, &size);
E 11
I 11
	cross_values(values, size, &y, &n);
E 11

	/* make sure the regression goes through the origin */
D 11
	x[size] = 0.0;
	y[size] = 0.0;
	size++;
E 11
I 11
	y[n++] = 0.0;
E 11

	for (count = 1; count < MAX_COUNT; ++count) {
		/* 
		 * given the minimum loop has "count" instructions,
		 * guess how many instructions each other loop contains
		 */
D 11
		for (i = 0; i < size; ++i) {
E 11
I 11
		for (i = 0; i < n; ++i) {
E 11
			int m = (int)((double)count * y[i] / min + 0.5);
			x[i] = (double)m;
		}

		/* find the regression of the samples */
D 9
		mhz_regression(x, y, size, &a, &b, &sig_a, &sig_b, &chi2);
E 9
I 9
D 11
		regression(x, y, NULL, size, &a, &b, &sig_a, &sig_b, &chi2);
E 11
I 11
		regression(x, y, NULL, n, &a, &b, &sig_a, &sig_b, &chi2);
E 11
E 9

D 9
		if (count == 1 || count * chi2 < min_chi2) {
E 9
I 9
		if (count == 1 || count * count * chi2 < min_chi2) {
E 9
			result = b;
D 11
			index = count;
E 11
			min_chi2 = chi2;
		}
	}
	free(x);
	free(y);
	return result;
}

I 10
/*
 * compute the gcd of many possible combinations of experimental values
D 11
 * and return the median result.  This is intended to reduce the impact
E 11
I 11
 * and return the mode of the results to reduce the impact
E 11
 * of a few bad experimental measurements on the computed result.
I 11
 *
 * r	- pointer to the array of experimental results
 * off	- offset of the result we want.  TRIES-1 == minimum result.
E 11
 */
D 11
double
super_gcd(double values[], int vsize)
E 11
I 11
int
compute_mhz(result_t *r)
E 11
{
D 11
	int i;
	int subset,trials;
	int ntests = 0;
	double *data = (double*)malloc(vsize * sizeof(double));
	double *r = (double *)malloc((1 << vsize) * sizeof(double));
	double result;
E 11
I 11
	int	i, j, mhz[2], n, subset, ntests;
	double	data[NTESTS], results[1<<NTESTS];
E 11

D 11
	for (subset = 0; subset < (1<<vsize); ++subset) {
		for (i = 0, trials = 0; i < vsize; ++i)
			if (BIT_SET(subset, i))
				data[trials++] = values[i];
		if (trials < 2 || classes(data, trials) < 2) continue;
		r[ntests++] = gcd(data, trials);
E 11
I 11
	for (i = 0; i < 2; ++i) {
		for (subset = 0, ntests = 0; subset < (1<<NTESTS); ++subset) {
			for (j = 0, n = 0; j < NTESTS; ++j)
D 14
				if (BIT_SET(subset, j))
					data[n++] = r[j].u[TRIES-1-i] / (double)r[j].n[TRIES-1-i];
E 14
I 14
				if (BIT_SET(subset, j) && r[j].N > TRIES/2)
D 15
					data[n++] = r[j].u[r[j].N-1-i] / (double)r[j].n[r[j].N-1-i];
E 15
I 15
					data[n++] = r[j].v[r[j].N-1-i].u / (double)r[j].v[r[j].N-1-i].n;
E 15
D 18
			n = filter_data(data, n);
E 14
			if (n < 2 || classes(data, n) < 2) continue;
E 18
I 18
			if (n < 2
			    || (n = filter_data(data, n)) < 2
			    ||classes(data, n) < 2) 
				continue;
E 18
			results[ntests++] = 1.0 / gcd(data, n);
		}
		mhz[i] = mode(results, ntests);
E 11
	}
D 11
	qsort(r, ntests, sizeof(double), double_compare);
E 11
I 11
D 12
	// if the results agree within 1% or 1MHz, accept them
E 12
I 12
	/* if the results agree within 1% or 1MHz, accept them */
E 12
	if (ABS(mhz[0] - mhz[1]) / (double)mhz[0] <= 0.01 
	    || ABS(mhz[0] - mhz[1]) <= 1)
		return mhz[0];
E 11

D 11
	result = r[ntests/2];
	free(data);
	free(r);
	return result;
E 11
I 11
	return -1;
E 11
}

I 16
void
save_data(result_t* data, result_t* data_save)
{
	int	i;

	for (i = 0; i < NTESTS; ++i) {
		data_save[i] = data[i];
	}
}

void
print_data(double mhz, result_t* data)
{
	int	i, j;
	char	*CPU_name = "CPU";
	char	*uname = "uname";
	char	*email = "email";
	int	speed = -1;
	char	*names[NTESTS];

	names[0] = name_1();
	names[1] = name_2();
	names[2] = name_3();
	names[3] = name_4();
	names[4] = name_5();
	names[5] = name_6();
	names[6] = name_7();
	names[7] = name_8();
	names[8] = name_9();

	printf("/* \"%s\", \"%s\", \"%s\", %d, %.0f, %d, %f, %f */\n", 
	       CPU_name, uname, email, speed, 
	       mhz, get_enough(0), l_overhead(), t_overhead());
	printf("result_t* data[] = { \n");
	for (i = 0; i < NTESTS; ++i) {
	    printf("\t/* %s */ { %d, {", names[i], data[i].N);
	    for (j = 0; j < data[i].N; ++j) {
		printf("\n\t\t{ /* %f */ %lu, %lu}", data[i].v[j].u / (100. * data[i].v[j].n), (unsigned long)data[i].v[j].u, (unsigned long)data[i].v[j].n);
		if (j < TRIES - 1) printf(", ");
	    }
	    if (i < NTESTS - 1) printf("}},\n");
	    else printf("}}\n");
	}
	printf("};\n");
}

E 16
E 10
E 8
int
main(int ac, char **av)
{
I 8
D 10
	int	i;
E 10
I 10
D 11
	int	i, j, k, tests;
	uint	mask;
E 10
	char   *names[NTESTS];
	double	results[NTESTS];
E 8
D 10
	double	mhz;
E 10
I 10
	double	mhz, runtime;
	result_t data[NTESTS][TRIES];
E 11
I 11
D 20
	int	i, j, k, mhz = -1;
E 20
I 20
	int	c, i, j, k, mhz = -1;
E 20
	double	runtime;
	result_t data[NTESTS];
I 16
	result_t data_save[NTESTS];
I 20
	char   *usage = "[-d] [-c]\n";
E 20
E 16
E 11
E 10
D 8
	double	overhead;
E 8

D 8
	BENCH(loop(ac), 0);
	overhead = usecs_spent();
	overhead /= get_n();
	BENCH(domhz(ac), 0);
	mhz = usecs_spent();
	mhz /= get_n();
	mhz -= overhead;
	mhz = 1000 / mhz;
E 8
I 8
D 10
	putenv("LOOP_O=0.0");
E 10
I 10
	putenv("LOOP_O=0.0"); /* should be at most 1% */
E 10

D 10
	for (i = 0; i < NTESTS; ++i) {
		results[i] = (*loops[i])(&names[i]);
E 10
I 10
	runtime = (NTESTS * TRIES * 3 * get_enough(0)) / 1000000.;
	if (runtime > 3.) {
	  fprintf(stderr, "mhz: should take approximately %.0f seconds\n", runtime);
E 10
	}

D 10
	mhz = 1.0 / gcd(results, NTESTS);
E 10
I 10
	/* make three efforts to get reliable data */
D 11
	for (i = 0; i < 3; ++i) {
E 11
I 11
	for (i = 0; i < 3 && mhz < 0; ++i) {
E 11
	    /* initialize the data arrays */
	    for (j = 0; j < NTESTS; ++j)
D 11
		insertinit(data[j], TRIES);
E 11
I 11
		insertinit(&data[j]);
E 11
E 10

I 10
	    /*
	     * collect the data; try to minimize impact of activity bursts
	     * by putting NTESTS in the inner loop so a burst will affect
	     * one data point for all expressions first, rather than all
	     * data points for one expression.
	     */
	    for (j = 0; j < TRIES; ++j) {
		for (k = 0; k < NTESTS; ++k) {
		    (*loops[k])(0);
D 11
		    insertsort(gettime(), get_n(), data[k], TRIES);
E 11
I 11
D 14
		    insertsort(gettime(), get_n(), &data[k]);
E 14
I 14
D 19
		    if (gettime() > 0)
			insertsort(gettime(), get_n(), &data[k]);
E 19
I 19
		    insertsort(gettime(), get_n(), &data[k]);
E 19
E 14
E 11
		}
	    }
I 16
	    save_data(data, data_save);
E 16
D 11
	    /* median experimental variance is less than 3%, data is OK */
	    if (error_estimate(data) < 3.0) break;
E 11
I 11
	    mhz = compute_mhz(data);
I 16
	}

D 20
	if (ac > 1 && !strcmp(av[1], "-d")) {
		if (ac > 1) {
			ac --;
			for (i = 1; i < ac; ++i) {
				av[i] = av[i+1];
E 20
I 20
	while (( c = getopt(ac, av, "cd")) != EOF) {
		switch(c) {
		case 'c':
			if (mhz > 0) {
				printf("%.4f\n", 1000. / (double)mhz);
				mhz = 0;
E 20
			}
I 20
			break;
		case 'd':
			print_data(mhz, data_save);
			break;
		default:
			lmbench_usage(ac, av, usage);
			break;
E 20
		}
D 20
		print_data(mhz, data_save);
E 20
E 16
E 11
	}

D 11
	if (error_estimate(data) >= 3.0) {
E 11
I 11
D 20
	if (mhz < 0.) {
E 20
I 20
	if (mhz < 0) {
E 20
E 11
		printf("-1 System too busy\n");
		exit(1);
	}

D 11
	/* extract minimum experimental values */
	for (i = 0; i < NTESTS; ++i) 
		results[i] = data[i][TRIES-1].u / (double)data[i][TRIES-1].n;

	/* remove suspect experimental results */
	tests = filter_data(results, NTESTS);

	mhz = 1.0 / super_gcd(results, tests);

E 11
E 10
E 8
D 20
	if (ac == 2 && !strcmp(av[1], "-c")) {
D 8
		printf("%.4f\n", 1000 / mhz);
E 8
I 8
D 11
		printf("%.4f\n", 1000. / mhz);
E 11
I 11
		printf("%.4f\n", 1000. / (double)mhz);
E 11
E 8
	} else {
D 8
		printf("%.0f Mhz, %.2f nanosec clock\n", mhz, 1000 / mhz);
E 8
I 8
D 9
		printf("%.0f Mhz, %.2f nanosec clock\n", 
E 9
I 9
D 11
		printf("%.0f MHz, %.2f nanosec clock\n", 
E 9
		       mhz + 0.5, 1000. / mhz);
E 11
I 11
		printf("%d MHz, %.2f nanosec clock\n", 
E 20
I 20
	if (mhz > 0) {
		printf("%d MHz, %.4f nanosec clock\n", 
E 20
		       mhz, 1000. / (double)mhz);
E 11
E 8
	}
	exit(0);
}
E 7
E 6
E 2
I 1
E 1
