h27156
s 00006/00000/00597
d D 1.5 00/06/25 13:20:18 staelin 6 5
c - fix buglet in median computations
cC
cK17429
e
s 00196/00013/00401
d D 1.4 00/06/21 19:28:44 staelin 5 4
c - Added routines to compute skew and kurtosis
c - Fixed bug in stderr computation
cC
cHhpli8.hpli.hpl.hp.com
cK11684
cZ+03:00
e
s 00001/00000/00413
d D 1.3 97/10/31 18:07:01 lm 4 3
c math.h
cC
cK08249
cSAlpha2.11
e
s 00011/00108/00402
d D 1.2 97/10/30 18:32:53 lm 3 2
c from Carl.
cK06734
cZ-08:00
e
s 00510/00000/00000
d D 1.1 97/06/12 21:33:48 lm 2 1
c Initial revision
cK04254
e
s 00000/00000/00000
d D 1.0 97/06/12 21:33:47 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK45129
cPsrc/lib_stats.c
cR6b0974d3d98b42e9
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
I 4
#include <math.h>
E 4
I 2
#include "bench.h"

#define BOOTSTRAP_COUNT	200

/*
 * a comparison function used by qsort
 */
int
int_compare(const void *a, const void *b)
{
	if (*(int*)a < *(int*)b) return -1;
	if (*(int*)a > *(int*)b) return 1;
	return 0;
}

/*
 * a comparison function used by qsort
 */
int
uint64_compare(const void *a, const void *b)
{
	if (*(uint64*)a < *(uint64*)b) return -1;
	if (*(uint64*)a > *(uint64*)b) return  1;
	return 0;
}

/*
 * a comparison function used by qsort
 */
int
double_compare(const void *a, const void *b)
{
	if (*(double*)a < *(double*)b) return -1;
	if (*(double*)a > *(double*)b) return 1;
	return 0;
}

/*
 * return the median value of an array of int
 */
int
int_median(int *values, int size)
{
	qsort(values, size, sizeof(int), int_compare);
I 5

I 6
	if (size == 0) return 0.;

E 6
E 5
	if (size % 2) {
	    return values[size/2];
	}
I 5

E 5
	return (values[size/2 - 1] + values[size/2]) / 2;
}

/*
 * return the median value of an array of int
 */
uint64
uint64_median(uint64 *values, int size)
{
	qsort(values, size, sizeof(uint64), uint64_compare);
I 5

I 6
	if (size == 0) return 0.;

E 6
E 5
	if (size % 2) {
	    return values[size/2];
	}
I 5

E 5
	return (values[size/2 - 1] + values[size/2]) / 2;
}

/*
 * return the median value of an array of doubles
 */
double
double_median(double *values, int size)
{
	qsort(values, size, sizeof(double), double_compare);
I 6

	if (size == 0) return 0.;
E 6
I 5

E 5
	if (size % 2) {
	    return values[size/2];
	}
I 5

E 5
	return (values[size/2 - 1] + values[size/2]) / 2.0;
}

/*
 * return the mean value of an array of int
 */
int
int_mean(int *values, int size)
{
	int	i;
	int	sum = 0;
I 5

E 5
	for (i = 0; i < size; ++i)
		sum += values[i];
I 5

E 5
	return sum / size;
}

/*
 * return the mean value of an array of int
 */
uint64
uint64_mean(uint64 *values, int size)
{
	int	i;
	uint64	sum = 0;
I 5

E 5
	for (i = 0; i < size; ++i)
		sum += values[i];
I 5

E 5
	return sum / size;
}

/*
 * return the mean value of an array of doubles
 */
double
double_mean(double *values, int size)
{
	int	i;
	double	sum = 0.0;
I 5

E 5
	for (i = 0; i < size; ++i)
		sum += values[i];
I 5

E 5
	return sum / (double)size;
}

/*
 * return the min value of an array of int
 */
int
int_min(int *values, int size)
{
	int	i;
	int	min = values[0];
I 5

E 5
	for (i = 1; i < size; ++i)
		if (values[i] < min) min = values[i];
I 5

E 5
	return min;
}

/*
 * return the min value of an array of int
 */
uint64
uint64_min(uint64 *values, int size)
{
	int	i;
	uint64	min = values[0];
I 5

E 5
	for (i = 1; i < size; ++i)
		if (values[i] < min) min = values[i];
I 5

E 5
	return min;
}

/*
 * return the min value of an array of doubles
 */
double
double_min(double *values, int size)
{
	int	i;
	double	min = values[0];
I 5

E 5
	for (i = 1; i < size; ++i)
		if (values[i] < min) min = values[i];
I 5

E 5
	return min;
}

/*
 * return the max value of an array of int
 */
int
int_max(int *values, int size)
{
	int	i;
	int	max = values[0];
I 5

E 5
	for (i = 1; i < size; ++i)
		if (values[i] > max) max = values[i];
I 5

E 5
	return max;
}

/*
 * return the max value of an array of int
 */
uint64
uint64_max(uint64 *values, int size)
{
	int	i;
	uint64	max = values[0];
I 5

E 5
	for (i = 1; i < size; ++i)
		if (values[i] > max) max = values[i];
I 5

E 5
	return max;
}

/*
 * return the max value of an array of doubles
 */
double
double_max(double *values, int size)
{
	int	i;
	double	max = values[0];
I 5

E 5
	for (i = 1; i < size; ++i)
		if (values[i] > max) max = values[i];
I 5

E 5
	return max;
}

/*
D 5
 * return the standard error of an array of ints
E 5
I 5
 * return the variance of an array of ints
 *
 * Reference: "Statistics for Experimenters" by
 * 	George E.P. Box et. al., page 41
E 5
 */
D 5
double	int_stderr(int *values, int size)
E 5
I 5
double	int_variance(int *values, int size)
E 5
{
	int	i;
	double	sum = 0.0;
	int	mean = int_mean(values, size);

	for (i = 0; i < size; ++i)
		sum += (double)((values[i] - mean) * (values[i] - mean));
D 5
	sum /= (double)(size * size);
E 5

D 5
	return sqrt(sum);
E 5
I 5
	return sum / (double)(size - 1);
E 5
}

/*
D 5
 * return the standard error of an array of uint64s
E 5
I 5
 * return the variance of an array of uint64s
E 5
 */
D 5
double	uint64_stderr(uint64 *values, int size)
E 5
I 5
double	uint64_variance(uint64 *values, int size)
E 5
{
	int	i;
	double	sum = 0.0;
	uint64	mean = uint64_mean(values, size);

	for (i = 0; i < size; ++i)
		sum += (double)((values[i] - mean) * (values[i] - mean));
D 5
	sum /= (double)(size * size);

	return sqrt(sum);
E 5
I 5
	return sum / (double)(size - 1);
E 5
}

/*
D 5
 * return the standard error of an array of doubles
E 5
I 5
 * return the variance of an array of doubles
E 5
 */
D 5
double	double_stderr(double *values, int size)
E 5
I 5
double	double_variance(double *values, int size)
E 5
{
	int	i;
	double	sum = 0.0;
	double	mean = double_mean(values, size);

	for (i = 0; i < size; ++i)
		sum += (double)((values[i] - mean) * (values[i] - mean));
D 5
	sum /= (double)(size * size);
E 5

D 5
	return sqrt(sum);
E 5
I 5
	return sum / (double)(size - 1);
}

/*
 * return the moment of an array of ints
 *
 * Reference: "Statistics for Experimenters" by
 * 	George E.P. Box et. al., page 41, 90
 */
double	int_moment(int moment, int *values, int size)
{
	int	i, j;
	double	sum = 0.0;
	int	mean = int_mean(values, size);

	for (i = 0; i < size; ++i) {
		double diff = values[i] - mean;
		double m = diff;
		for (j = 1; j < moment; ++j)
			m *= diff;
		sum += m;
	}

	return sum / (double)size;
}

/*
 * return the moment of an array of uint64s
 */
double	uint64_moment(int moment, uint64 *values, int size)
{
	int	i, j;
	double	sum = 0.0;
	uint64	mean = uint64_mean(values, size);

	for (i = 0; i < size; ++i) {
		double diff = values[i] - mean;
		double m = diff;
		for (j = 1; j < moment; ++j)
			m *= diff;
		sum += m;
	}

	return sum / (double)size;
}

/*
 * return the moment of an array of doubles
 */
double	double_moment(int moment, double *values, int size)
{
	int	i, j;
	double	sum = 0.0;
	double	mean = double_mean(values, size);

	for (i = 0; i < size; ++i) {
		double diff = values[i] - mean;
		double m = diff;
		for (j = 1; j < moment; ++j)
			m *= diff;
		sum += m;
	}

	return sum / (double)size;
}

/*
 * return the standard error of an array of ints
 *
 * Reference: "Statistics for Experimenters" by
 * 	George E.P. Box et. al., page 41
 */
double	int_stderr(int *values, int size)
{
	return sqrt(int_variance(values, size));
}

/*
 * return the standard error of an array of uint64s
 */
double	uint64_stderr(uint64 *values, int size)
{
	return sqrt(uint64_variance(values, size));
}

/*
 * return the standard error of an array of doubles
 */
double	double_stderr(double *values, int size)
{
	return sqrt(double_variance(values, size));
}

/*
 * return the skew of an array of ints
 *
 */
double	int_skew(int *values, int size)
{
	double	sigma = int_stderr(values, size);
	double	moment3 = int_moment(3, values, size);

	return moment3 / (sigma * sigma * sigma);
}

/*
 * return the skew of an array of uint64s
 */
double	uint64_skew(uint64 *values, int size)
{
	double	sigma = uint64_stderr(values, size);
	double	moment3 = uint64_moment(3, values, size);

	return moment3 / (sigma * sigma * sigma);
}

/*
 * return the skew of an array of doubles
 */
double	double_skew(double *values, int size)
{
	double	sigma = double_stderr(values, size);
	double	moment3 = double_moment(3, values, size);

	return moment3 / (sigma * sigma * sigma);
}

/*
 * return the kurtosis of an array of ints
 *
 * Reference: "Statistics for Experimenters" by
 * 	George E.P. Box et. al., page 90;
 */
double	int_kurtosis(int *values, int size)
{
	double	variance = int_variance(values, size);
	double	moment4 = int_moment(4, values, size);

	return moment4 / (variance * variance) - 3;
}

/*
 * return the kurtosis of an array of uint64s
 */
double	uint64_kurtosis(uint64 *values, int size)
{
	double	variance = uint64_variance(values, size);
	double	moment4 = uint64_moment(4, values, size);

	return moment4 / (variance * variance) - 3;
}

/*
 * return the kurtosis of an array of doubles
 */
double	double_kurtosis(double *values, int size)
{
	double	variance = double_variance(values, size);
	double	moment4 = double_moment(4, values, size);

	return moment4 / (variance * variance) - 3;
E 5
}

/*
 * BOOTSTRAP:
 *
 * stderr = sqrt(sum_i(s[i] - sum_j(s[j])/B)**2 / (B - 1))
 *
 * Reference: "An Introduction to the Bootstrap" by Bradley
 *	Efron and Robert J. Tibshirani, page 12.
 */

/*
 * return the bootstrap estimation of the standard error 
 * of an array of ints
 */
double	int_bootstrap_stderr(int *values, int size, int_stat f)
{
	int	i, j;
	int    *samples = (int*)malloc(size * sizeof(int));
	double *s = (double*)malloc(BOOTSTRAP_COUNT * sizeof(double));
	double	s_sum = 0;
	double	sum = 0;

	/* generate the stderr for each of the bootstrap samples */
	for (i = 0; i < BOOTSTRAP_COUNT; ++i) {
		for (j = 0; j < size; ++j)
			samples[j] = values[rand() % size];
		s[i] = (double)(*f)(samples, size);
		s_sum += s[i];	/* CHS: worry about overflow */
	}
	s_sum /= (double)BOOTSTRAP_COUNT;
	
	for (i = 0; i < BOOTSTRAP_COUNT; ++i) 
		sum += (s[i] - s_sum) * (s[i] - s_sum);

	sum /= (double)(BOOTSTRAP_COUNT - 1);

	free(samples);
	free(s);

	return sqrt(sum);
}

/*
 * return the bootstrap estimation of the standard error 
 * of an array of uint64s
 */
double	uint64_bootstrap_stderr(uint64 *values, int size, uint64_stat f)
{
	int	i, j;
	uint64 *samples = (uint64*)malloc(size * sizeof(uint64));
	double *s = (double*)malloc(BOOTSTRAP_COUNT * sizeof(double));
	double	s_sum;
	double	sum;

	/* generate the stderr for each of the bootstrap samples */
	for (i = 0, s_sum = 0.0; i < BOOTSTRAP_COUNT; ++i) {
		for (j = 0; j < size; ++j) 
			samples[j] = values[rand() % size];
		s[i] = (double)(*f)(samples, size);
		s_sum += s[i];	/* CHS: worry about overflow */
	}
	s_sum /= (double)BOOTSTRAP_COUNT;
	
	for (i = 0, sum = 0.0; i < BOOTSTRAP_COUNT; ++i) 
		sum += (s[i] - s_sum) * (s[i] - s_sum);

	free(samples);
	free(s);

	return sqrt(sum/(double)(BOOTSTRAP_COUNT - 1));
}

/*
 * return the bootstrap estimation of the standard error 
 * of an array of doubles
 */
double	double_bootstrap_stderr(double *values, int size, double_stat f)
{
	int	i, j;
	double *samples = (double*)malloc(size * sizeof(double));
	double *s = (double*)malloc(BOOTSTRAP_COUNT * sizeof(double));
	double	s_sum = 0;
	double	sum = 0;

	/* generate the stderr for each of the bootstrap samples */
	for (i = 0; i < BOOTSTRAP_COUNT; ++i) {
		for (j = 0; j < size; ++j) 
			samples[j] = values[rand() % size];
		s[i] = (*f)(samples, size);
		s_sum += (double)s[i];	/* CHS: worry about overflow */
	}
	s_sum /= (double)BOOTSTRAP_COUNT;
	
	for (i = 0; i < BOOTSTRAP_COUNT; ++i) 
		sum += (s[i] - s_sum) * (s[i] - s_sum);

	sum /= (double)(BOOTSTRAP_COUNT - 1);

	free(samples);
	free(s);

	return sqrt(sum);
}

D 3
/* this routine is from "Numerical Recipes in C" pp. 214 */
double 
gammln(double xx)
{
	int	j;
	double	x, y, tmp, ser;
	static double cof[6] = {
		76.18009172947146,
		-86.50532032941677,
		24.01409824083091,
		-1.231739572450155,
		0.1208650973866179e-2,
		-0.5395239384953e-5};

	y = x = xx;
	tmp = x + 5.5 - (x + 0.5) * log(x + 5.5);
	ser = 1.000000000190015;
	for (j = 0; j < 6; ++j) {
		y += 1.0;
		ser += cof[j] / y;
	}
	return log(2.5066282746310005 * ser / x) - tmp;
}

/* these routines are from "Numerical Recipes in C" pp. 217-219 */
#define	ITMAX	200
#define	EPS	3.0e-7
#define FPMIN	1.0e-30

double
gser(double a, double x)
{
	int	n;
	double	gln, sum, del, ap;

	if (x <= 0.0) {
		if (x < 0) {
			fprintf(stderr, "gser(%f, %f): bad value %f\n", a, x, x);
			return -1.0;
		}
		return 0.0;
	}
	gln = gammln(a);
	ap = a;
	del = sum = 1.0 / a;
	for (n = 0; n < ITMAX; ++n) {
		++ap;
		del *= x / ap;
		sum += del;
		if (ABS(del) < ABS(sum) * EPS)
			return sum * exp(-x + a * log(x) - gln);
	}
	fprintf(stderr, "gser(%f, %f): could not converge in %d iterations\n",
		a, x, ITMAX);
	/* ERROR */
	return -1.0;
}

double
gcf(double a, double x)
{
	int	i;
	double	an, b, c, d, del, h;

	b = x + 1.0 - a;
	c = 1.0 / FPMIN;
	d = 1.0 / b;
	h = d;
	for (i = 1; i <= ITMAX; ++i) {
		an = -i * (i - a);
		b += 2.0;
		d = b + an * d;
		c = b + an / c;
		if (ABS(d) < FPMIN) d = FPMIN;
		if (ABS(c) < FPMIN) c = FPMIN;
		d = 1.0 / d;
		del = d * c;
		h *= del;
		if (ABS(del - 1.0) < EPS) break;
	}
	if (i > ITMAX) {
		fprintf(stderr, "gcf(%f, %f): could not converge in %d iterations\n", a, x, ITMAX);
		return -1.0; /* ERROR */
	}
	return exp(-x + a * log(x) - gammln(a)) * h;
}

double 
gammq(double a, double x)
{
	if (x < a || a <= 0.0) {
		if (a < 0) fprintf(stderr, "gammq(%f, %f): invalid arguments\n", a, x);
		return 0.0;
	}
	if (x < a + 1.0) return 1.0 - gser(a, x);
	return gcf(a, x);
}

E 3
/*
D 3
 * regression(x, y, sig, n, a, b, sig_a, sig_b, chi2, q)
E 3
I 3
 * regression(x, y, sig, n, a, b, sig_a, sig_b, chi2)
E 3
 *
 * This routine is derived from equations in "Numerical Recipes in C" 
 * (second edition) by Press, et. al.,  pages 661-665.
 *
 * compute the linear regression y = a + bx for (x,y), where y[i] has 
 * standard deviation sig[i].
 *
 * returns the coefficients a and b, along with an estimation of their
 * error (standard deviation) in sig_a and sig_b.
 *
D 3
 * returns chi2 and incomplete gamma function Q for "goodness of fit"
 * information.
E 3
I 3
 * returns chi2 for "goodness of fit" information.
E 3
 */

void
regression(double *x, double *y, double *sig, int n,
	   double *a, double *b, double *sig_a, double *sig_b, 
D 3
	   double *chi2, double *q)
E 3
I 3
	   double *chi2)
E 3
{
	int	i;
	double	S = 0.0, Sx = 0.0, Sy = 0.0, Stt = 0.0, Sx_S;

	/* compute some basic statistics */
	for (i = 0; i < n; ++i) {
		/* Equations 15.2.4: for S, Sx, Sy */
D 3
		double	weight = 1.0 / (sig[i] * sig[i]);
E 3
I 3
		double	weight = 1.0 / (sig ? sig[i] * sig[i] : 1.0);
E 3
		S += weight;
		Sx += weight * x[i];
		Sy += weight * y[i];
	}

	*b = 0.0;
	Sx_S = Sx / S;
	for (i = 0; i < n; ++i) {
		/* 
		 * Equation 15.2.15 for t
		 * Equation 15.2.16 for Stt
		 * Equation 15.2.17 for b, do summation portion of equation
		 *	compute Sum i=0,n-1 (t_i * y[i] / sig[i]))
		 */
D 3
		double t_i = (x[i] - Sx_S) / sig[i];
E 3
I 3
		double t_i = (x[i] - Sx_S) / (sig ? sig[i] : 1.0);
E 3
		Stt += t_i * t_i;
D 3
		*b  += t_i * y[i] / sig[i];
E 3
I 3
		*b  += t_i * y[i] / (sig ? sig[i] : 1.0);
E 3
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
D 3
		double merit = (y[i] - ((*a) + (*b) * x[i])) / sig[i];
E 3
I 3
		double merit = (y[i] - ((*a) + (*b) * x[i])) / (sig ? sig[i] : 1.0);
E 3
		*chi2 += merit * merit;
	}
D 3
	/* Equation 15.2.12 for Q, the incomplete gamma function */
	*q = gammq(((double)n - 2.0) / 2.0, (*chi2) / 2.0);
E 3
I 3
	if (sig == NULL) {
	  *sig_a *= sqrt((*chi2) / (n - 2));
	  *sig_b *= sqrt((*chi2) / (n - 2));
	}
E 3
}

E 2
I 1
E 1
