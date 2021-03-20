h23850
s 00016/00000/00045
d D 1.3 00/06/21 19:28:45 staelin 4 3
c - Added routines to compute skew and kurtosis
cC
cHhpli8.hpli.hpl.hp.com
cK48418
cZ+03:00
e
s 00001/00001/00044
d D 1.2 97/10/30 18:33:02 lm 3 2
c from Carl.
cC
cK59940
cSAlpha2.11
cZ-08:00
e
s 00045/00000/00000
d D 1.1 97/06/12 21:33:53 lm 2 1
c Initial revision
cK60838
e
s 00000/00000/00000
d D 1.0 97/06/12 21:33:52 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK32183
cPsrc/stats.h
cR7340c05fd9766fd9
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
#ifndef _STATS_H
#define _STATS_H

#include "bench.h"
#include "timing.h"

#define ABS(x)	((x) < 0 ? -(x) : (x))

int	int_compare(const void *a, const void *b);
int	uint64_compare(const void *a, const void *b);
int	double_compare(const void *a, const void *b);

typedef	int (*int_stat)(int *values, int size);
typedef	uint64 (*uint64_stat)(uint64 *values, int size);
typedef	double (*double_stat)(double *values, int size);

int	int_median(int *values, int size);
uint64	uint64_median(uint64 *values, int size);
double	double_median(double *values, int size);

int	int_mean(int *values, int size);
uint64	uint64_mean(uint64 *values, int size);
double	double_mean(double *values, int size);

int	int_min(int *values, int size);
uint64	uint64_min(uint64 *values, int size);
double	double_min(double *values, int size);

int	int_max(int *values, int size);
uint64	uint64_max(uint64 *values, int size);
double	double_max(double *values, int size);

I 4
double	int_variance(int *values, int size);
double	uint64_variance(uint64 *values, int size);
double	double_variance(double *values, int size);

double	int_moment(int moment, int *values, int size);
double	uint64_moment(int moment, uint64 *values, int size);
double	double_moment(int moment, double *values, int size);

E 4
double	int_stderr(int *values, int size);
double	uint64_stderr(uint64 *values, int size);
double	double_stderr(double *values, int size);
I 4

double	int_skew(int *values, int size);
double	uint64_skew(uint64 *values, int size);
double	double_skew(double *values, int size);

double	int_kurtosis(int *values, int size);
double	uint64_kurtosis(uint64 *values, int size);
double	double_kurtosis(double *values, int size);
E 4

double	int_bootstrap_stderr(int *values, int size, int_stat f);
double	uint64_bootstrap_stderr(uint64 *values, int size, uint64_stat f);
double	double_bootstrap_stderr(double *values, int size, double_stat f);

void	regression(double *x, double *y, double *sig, int n,
		   double *a, double *b, double *sig_a, double *sig_b, 
D 3
		   double *chi2, double *q);
E 3
I 3
		   double *chi2);
E 3

#endif /* _STATS_H */
E 2
I 1
E 1
