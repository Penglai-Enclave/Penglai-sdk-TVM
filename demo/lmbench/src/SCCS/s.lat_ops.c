H64003
s 00008/00006/00430
d D 1.14 02/01/07 01:30:01 staelin 15 14
c fix bug in integer bitwise operation expressions, which
c were optimizable by smart compilers.  Oops.
cC
cHdisks.bitmover.com
cK42428
cZ+00:00
e
s 00061/00103/00375
d D 1.13 01/11/15 14:22:59 staelin 14 13
c Change statements used in various lat_ops operation kernels to
c remove extraneous operations.  Fixed do_integer_bitwise to remove
c a shift operation; it now just does XORs.  Changed do_integer_mul
c so that it only does a bit operation (XOR) every ten multiplications,
c which should reduce the scope for measurement error.  Fixed 
c do_integer_div so it only does division operations.  Did similar fixes
c and changes for int64 operations.
cC
cK36945
cZ+02:00
e
s 00045/00062/00433
d D 1.12 01/05/14 11:35:15 staelin 13 12
c Add typedef for int64
c Switch lat_ops and par_mem from using benchmp() to BENCH() for performance reasons
c Change expression used in lat_ops and par_mem for measuring int and int64 add performance
c   to one that only uses '+' operations
cC
cK13407
cZ+03:00
e
s 00009/00004/00486
d D 1.11 01/04/02 14:50:33 staelin 12 11
c Add parallelism to lat_ops for three sub-benchmarks: integer bit, bogomflops, and double bogomflops
cC
cHhpli69.hpli.hpl.hp.com
cK14962
cZ+02:00
e
s 00002/00002/00488
d D 1.10 00/09/26 16:23:32 staelin 11 10
c - Fix buglet in lat_ops; miscounted number of operations executed for both float and
c   double bogomips computations
cC
cK03409
e
s 00019/00034/00471
d D 1.9 00/09/26 16:01:55 staelin 10 9
c - Fix bugs in lat_ops and par_ops in float_add, float_mul, double_add, and double_mul
c   which were causing arithmetic overflows which caused the benchmarks to crash
cC
cK03411
e
s 00041/00021/00464
d D 1.8 00/08/16 13:11:45 staelin 9 8
c - Add command line arguments for warmup and repetitions to lat_ops
cC
cK22069
e
s 00001/00001/00484
d D 1.7 00/08/10 16:13:04 staelin 8 7
c - Fix code that reports "uint64 add" latencies so results are properly identified.  From Chris Ruemmler
cC
cK36044
e
s 00004/00004/00481
d D 1.6 00/07/30 15:34:05 staelin 7 6
c - Add yet another workaround for GCC bugs
cC
cK36240
e
s 00044/00020/00441
d D 1.5 00/07/30 11:46:10 staelin 6 5
c - Change type of "iterations" from uint64 to iter_t, which is a u_long
cC
cK36918
e
s 00008/00008/00453
d D 1.4 00/07/27 14:36:59 staelin 5 4
c - Change expression used in do_integer_bit and do_uint64_bit benchmarks so GCC doesn't
c   optimize-away the loops
c - Simplify expression used in do_uint64_add so we only have add operations
c - Reformat bogomflops expressions so they are slightly more readable
cC
cK54762
e
s 00056/00007/00405
d D 1.3 00/07/26 18:09:55 staelin 4 3
c - Added workaround for GCC infinite loop bug
c - Changed bogomips to bogomflops
cC
cK57579
e
s 00166/00019/00246
d D 1.2 00/07/25 13:48:36 staelin 3 2
c - add new benchmarks for uint64 arithmetic (bit, add, mul, div, mod)
c - add new benchmark for integer add
c - fix bug in floating point and double benchmarks which allowed processor to overlap
c   some operations resulting in non-integer clock-tick operation speeds
c - change bogomips equations to match Richard G. Brown's latest equations from cpu-rate
c   0.0.3pre
cC
cK07223
e
s 00265/00000/00000
d D 1.1 00/07/24 09:54:59 staelin 2 1
cF1
cK22848
cO-rwxrwxr--
e
s 00000/00000/00000
d D 1.0 00/07/24 09:54:59 staelin 1 0
c BitKeeper file /tmp_mnt/usr/WebPaper/users/staelin/src/LMbench/src/lat_ops.c
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHhpli8.hpli.hpl.hp.com
cK53784
cPsrc/lat_ops.c
cR3e526da011aa72da
cV4
cX0xa1
cZ+03:00
e
u
U
f e 0
f x 0xa1
t
T
I 2
/*
 * lat_ops.c - benchmark of simple operations
 *
 * Copyright (c) 1996-2000 Carl Staelin and Larry McVoy.  
 */
char	*id = "$Id$\n";

#include "bench.h"

struct _state {
	int	N;
	int	M;
I 10
	int	K;
E 10
	double*	data;
};

#define TEN(a) a a a a a a a a a a
#define HUNDRED(a) TEN(TEN(a))
I 4

E 4
void
D 6
do_integer_bitwise(uint64 iterations, void* cookie)
E 6
I 6
do_integer_bitwise(iter_t iterations, void* cookie)
E 6
{
	struct _state *pState = (struct _state*)cookie;
D 14
	register int i;
E 14
	register int r = pState->N;
I 14
	register int s = (int)iterations;
E 14

	while (iterations-- > 0) {
D 14
		for (i = 0; i < 1000; ++i) {
D 5
			HUNDRED(r^=i;r=~r;)
E 5
I 5
			HUNDRED(r^=i;r<<=1;)
E 5
		}
E 14
I 14
D 15
		HUNDRED(r^=s;s^=r;)
E 15
I 15
		HUNDRED(r^=iterations;s^=r;r|=s;)
E 15
E 14
	}
	use_int(r);
}

void
I 3
D 6
do_integer_add(uint64 iterations, void* cookie)
E 6
I 6
do_integer_add(iter_t iterations, void* cookie)
E 6
{
	struct _state *pState = (struct _state*)cookie;
D 14
	register int i;
E 14
D 13
	register int r = pState->N;
E 13
I 13
	register int a = pState->N;
	register int b = pState->N;
E 13

	while (iterations-- > 0) {
D 14
		for (i = 1; i < 1001; ++i) {
I 6
D 13
#ifndef __GNUC__
			/* required because of an HP ANSI/C compiler bug */
E 6
			HUNDRED(r=(r+i)^r;)
I 6
#else
D 7
			HUNDRED(r=r+r+i;)
E 7
I 7
			TEN(r=r+r+i;)
E 7
#endif
E 13
I 13
			HUNDRED(a+=b;b-=a;)
E 13
E 6
		}
E 14
I 14
		HUNDRED(a+=b;b-=a;)
E 14
	}
D 13
	use_int(r);
E 13
I 13
	use_int(a+b);
E 13
}

void
E 3
D 6
do_integer_mul(uint64 iterations, void* cookie)
E 6
I 6
do_integer_mul(iter_t iterations, void* cookie)
E 6
{
	struct _state *pState = (struct _state*)cookie;
D 14
	register int i;
E 14
	register int r = pState->N;
I 14
	register int s = (pState->N + 1) ^ r;
E 14

	while (iterations-- > 0) {
D 14
		for (i = 1; i < 1001; ++i) {
			HUNDRED(r=(r*i)^r;)
		}
E 14
I 14
		TEN(TEN(r=r*s;)r^=s;)
E 14
	}
	use_int(r);
}

void
D 6
do_integer_div(uint64 iterations, void* cookie)
E 6
I 6
do_integer_div(iter_t iterations, void* cookie)
E 6
{
	struct _state *pState = (struct _state*)cookie;
D 14
	register int i;
	register int r = pState->N;
E 14
I 14
	register int r = pState->N + 1;
	register int s = (r + 1) << 20;
E 14

	while (iterations-- > 0) {
D 14
		for (i = 1; i < 1001; ++i) {
			HUNDRED(r=(r/i)^r;)
		}
E 14
I 14
		HUNDRED(r=s/r;)
E 14
	}
D 3
		use_int(r);
E 3
I 3
	use_int(r);
E 3
}

void
D 6
do_integer_mod(uint64 iterations, void* cookie)
E 6
I 6
do_integer_mod(iter_t iterations, void* cookie)
E 6
{
	struct _state *pState = (struct _state*)cookie;
D 14
	register int i;
E 14
	register int r = pState->N;
I 14
	register int s = pState->N + iterations;
E 14

	while (iterations-- > 0) {
D 14
		for (i = 1; i < 1001; ++i) {
			HUNDRED(r=(r%i)^r;)
		}
E 14
I 14
		HUNDRED(r=r%s;r|=s;)
E 14
	}
	use_int(r);
}

void
I 3
D 6
do_uint64_bitwise(uint64 iterations, void* cookie)
E 6
I 6
D 13
do_uint64_bitwise(iter_t iterations, void* cookie)
E 13
I 13
do_int64_bitwise(iter_t iterations, void* cookie)
E 13
E 6
{
	struct _state *pState = (struct _state*)cookie;
D 13
	register uint64 i;
	register uint64 r = pState->N;
E 13
I 13
D 14
	register int64 i;
E 14
	register int64 r = pState->N;
I 14
	register int64 s = (int64)iterations;
I 15
	register int64 i = (int64)iterations;
E 15
E 14
E 13

	while (iterations-- > 0) {
D 14
		for (i = 0; i < 1000; ++i) {
D 5
			HUNDRED(r^=i;r=~r;)
E 5
I 5
			HUNDRED(r^=i;r<<=1;)
D 6
/*			HUNDRED(r=~(r^i);) */
E 6
E 5
		}
E 14
I 14
D 15
		HUNDRED(r^=s;s^=r;)
E 15
I 15
		HUNDRED(r^=i;s^=r;r|=s;)
		i--;
E 15
E 14
	}
	use_int((int)r);
}

void
D 6
do_uint64_add(uint64 iterations, void* cookie)
E 6
I 6
D 13
do_uint64_add(iter_t iterations, void* cookie)
E 13
I 13
do_int64_add(iter_t iterations, void* cookie)
E 13
E 6
{
	struct _state *pState = (struct _state*)cookie;
D 13
	register uint64 i;
	register uint64 r = pState->N;
E 13
I 13
D 14
	register int i;
E 14
	register int64 a = pState->N;
	register int64 b = pState->N;
E 13

	while (iterations-- > 0) {
D 14
		for (i = 1; i < 1001; ++i) {
D 5
			HUNDRED(r=(r+i)^r;)
E 5
I 5
D 6
			HUNDRED(r+=(r+i);)
E 6
I 6
D 13
#ifndef __GNUC__
			/* required because of an HP ANSI/C compiler bug */
			HUNDRED(r=(r+i)^r;)
#else
D 7
			HUNDRED(r=r+r+i;)
E 7
I 7
			TEN(r=r+r+i;)
E 7
#endif
E 13
I 13
			HUNDRED(a+=b;b-=a;)
E 13
E 6
E 5
		}
E 14
I 14
		HUNDRED(a+=b;b-=a;)
E 14
	}
D 13
	use_int((int)r);
E 13
I 13
	use_int((int)a+(int)b);
E 13
}

void
D 6
do_uint64_mul(uint64 iterations, void* cookie)
E 6
I 6
D 13
do_uint64_mul(iter_t iterations, void* cookie)
E 13
I 13
do_int64_mul(iter_t iterations, void* cookie)
E 13
E 6
{
	struct _state *pState = (struct _state*)cookie;
D 13
	register uint64 i;
	register uint64 r = pState->N;
E 13
I 13
D 14
	register int64 i;
E 14
	register int64 r = pState->N;
I 14
	register int64 s = (pState->N + 1) ^ r;
E 14
E 13

	while (iterations-- > 0) {
D 14
		for (i = 1; i < 1001; ++i) {
			HUNDRED(r=(r*i)^r;)
		}
E 14
I 14
		TEN(TEN(r=r*s;)r^=s;)
E 14
	}
	use_int((int)r);
}

void
D 6
do_uint64_div(uint64 iterations, void* cookie)
E 6
I 6
D 13
do_uint64_div(iter_t iterations, void* cookie)
E 13
I 13
do_int64_div(iter_t iterations, void* cookie)
E 13
E 6
{
	struct _state *pState = (struct _state*)cookie;
D 13
	register uint64 i;
	register uint64 r = pState->N;
E 13
I 13
D 14
	register int64 i;
E 14
	register int64 r = pState->N;
I 14
	register int64 s = (r + 1) << 20;
E 14
E 13

	while (iterations-- > 0) {
D 14
		for (i = 1; i < 1001; ++i) {
			HUNDRED(r=(r/i)^r;)
		}
E 14
I 14
		HUNDRED(r=s/r;)
E 14
	}
	use_int((int)r);
}

void
D 6
do_uint64_mod(uint64 iterations, void* cookie)
E 6
I 6
D 13
do_uint64_mod(iter_t iterations, void* cookie)
E 13
I 13
do_int64_mod(iter_t iterations, void* cookie)
E 13
E 6
{
	struct _state *pState = (struct _state*)cookie;
D 13
	register uint64 i;
	register uint64 r = pState->N;
E 13
I 13
D 14
	register int64 i;
E 14
	register int64 r = pState->N;
I 14
	register int64 s = pState->N + iterations;
E 14
E 13

	while (iterations-- > 0) {
D 14
		for (i = 1; i < 1001; ++i) {
			HUNDRED(r=(r%i)^r;)
		}
E 14
I 14
		HUNDRED(r=r%s;r|=s;)
E 14
	}
	use_int((int)r);
}

void
E 3
D 6
do_float_add(uint64 iterations, void* cookie)
E 6
I 6
do_float_add(iter_t iterations, void* cookie)
E 6
{
	struct _state *pState = (struct _state*)cookie;
D 14
	register int i;
E 14
	register float f = (float)pState->N;
D 10
	register float g = (float)pState->M;
E 10
I 10
	register float g = (float)pState->K;
E 10

	while (iterations-- > 0) {
D 14
		for (i = 0; i < 1000; ++i) {
I 4
D 10
#ifndef __GNUC__
E 4
D 3
			HUNDRED(f+=g;g+=g;)
E 3
I 3
			HUNDRED(f+=f;)
I 4
#else
I 6
			/* required because of GCC bug */
E 10
E 6
			TEN(f+=f;)
D 10
#endif
E 10
I 10
			f+=g;
E 10
E 4
E 3
		}
E 14
I 14
		TEN(f+=f;)
		f+=g;
E 14
	}
	use_int((int)f);
	use_int((int)g);
}

void
D 6
do_float_mul(uint64 iterations, void* cookie)
E 6
I 6
do_float_mul(iter_t iterations, void* cookie)
E 6
{
	struct _state *pState = (struct _state*)cookie;
D 14
	register int i;
E 14
	register float f = (float)pState->N;
	register float g = (float)pState->M;

	while (iterations-- > 0) {
D 14
		for (i = 0; i < 1000; ++i) {
E 14
I 4
#ifndef __GNUC__
E 4
D 3
			HUNDRED(f*=g;g*=g;)
E 3
I 3
D 14
			HUNDRED(f*=f;)
E 14
I 14
		HUNDRED(f*=f;)
E 14
I 4
#else
I 6
D 14
			/* required because of GCC bug */
E 6
			TEN(f*=f;)
E 14
I 14
		/* required because of GCC bug */
		TEN(f*=f;)
E 14
#endif
E 4
E 3
D 14
		}
E 14
	}
	use_int((int)f);
	use_int((int)g);
}

void
D 6
do_float_div(uint64 iterations, void* cookie)
E 6
I 6
do_float_div(iter_t iterations, void* cookie)
E 6
{
	struct _state *pState = (struct _state*)cookie;
D 14
	register int i;
E 14
	register float f = (float)pState->N;
	register float g = (float)pState->M;

	while (iterations-- > 0) {
D 14
		for (i = 0; i < 1000; ++i) {
E 14
I 4
#ifndef __GNUC__
E 4
D 3
			HUNDRED(f/=g;g/=f;)
E 3
I 3
D 14
			HUNDRED(f=g/f;)
E 14
I 14
		HUNDRED(f=g/f;)
E 14
I 4
#else
I 6
D 14
			/* required because of GCC bug */
E 6
			TEN(f=g/f;)
E 14
I 14
		/* required because of GCC bug */
		TEN(f=g/f;)
E 14
#endif
E 4
E 3
D 14
		}
E 14
	}
	use_int((int)f);
	use_int((int)g);
}

void
D 6
do_double_add(uint64 iterations, void* cookie)
E 6
I 6
do_double_add(iter_t iterations, void* cookie)
E 6
{
	struct _state *pState = (struct _state*)cookie;
D 14
	register int i;
E 14
	register double f = (double)pState->N;
D 10
	register double g = (double)pState->M;
E 10
I 10
	register double g = (double)pState->K;
E 10

	while (iterations-- > 0) {
D 14
		for (i = 0; i < 1000; ++i) {
I 4
D 10
#ifndef __GNUC__
E 4
D 3
			HUNDRED(f+=g;g+=g;)
E 3
I 3
			HUNDRED(f+=f;)
I 4
#else
I 6
			/* required because of GCC bug */
E 10
E 6
			TEN(f+=f;)
D 10
#endif
E 10
I 10
			f+=g;
E 10
E 4
E 3
		}
E 14
I 14
		TEN(f+=f;)
		f+=g;
E 14
	}
	use_int((int)f);
	use_int((int)g);
}

void
D 6
do_double_mul(uint64 iterations, void* cookie)
E 6
I 6
do_double_mul(iter_t iterations, void* cookie)
E 6
{
	struct _state *pState = (struct _state*)cookie;
D 14
	register int i;
E 14
	register double f = (double)pState->N;
	register double g = (double)pState->M;

	while (iterations-- > 0) {
D 14
		for (i = 0; i < 1000; ++i) {
E 14
I 4
#ifndef __GNUC__
E 4
D 3
			HUNDRED(f*=g;g*=g;)
E 3
I 3
D 14
			HUNDRED(f*=f;)
E 14
I 14
		HUNDRED(f*=f;)
E 14
I 4
#else
I 6
D 14
			/* required because of GCC bug */
E 6
			TEN(f*=f;)
E 14
I 14
		/* required because of GCC bug */
		TEN(f*=f;)
E 14
#endif
E 4
E 3
D 14
		}
E 14
	}
	use_int((int)f);
	use_int((int)g);
}

void
D 6
do_double_div(uint64 iterations, void* cookie)
E 6
I 6
do_double_div(iter_t iterations, void* cookie)
E 6
{
	struct _state *pState = (struct _state*)cookie;
D 14
	register int i;
E 14
	register double f = (double)pState->N;
	register double g = (double)pState->M;

	while (iterations-- > 0) {
D 14
		for (i = 0; i < 1000; ++i) {
E 14
I 4
#ifndef __GNUC__
E 4
D 3
			HUNDRED(f/=g;g/=f;)
E 3
I 3
D 14
			HUNDRED(f=g/f;)
E 14
I 14
		HUNDRED(f=g/f;)
E 14
I 4
#else
I 6
D 14
			/* required because of GCC bug */
E 6
			TEN(f=g/f;)
E 14
I 14
		/* required because of GCC bug */
		TEN(f=g/f;)
E 14
#endif
E 4
E 3
D 14
		}
E 14
	}
	use_int((int)f);
	use_int((int)g);
}

void
D 3
initialize(void* cookie)
E 3
I 3
float_initialize(void* cookie)
{
	struct _state *pState = (struct _state*)cookie;
	register int i;
D 10
	float* x = (float*)malloc(pState->N * sizeof(float));;
E 10
I 10
	float* x = (float*)malloc(pState->M * sizeof(float));;
E 10

	pState->data = (double*)x;
D 10
	for (i = 0; i < pState->N; ++i) {
E 10
I 10
	for (i = 0; i < pState->M; ++i) {
E 10
		x[i] = 1.;
	}
}

void
double_initialize(void* cookie)
E 3
{
	struct _state *pState = (struct _state*)cookie;
	register int i;

D 10
	pState->data = (double*)malloc(pState->N * sizeof(double));
	for (i = 0; i < pState->N; ++i) {
E 10
I 10
	pState->data = (double*)malloc(pState->M * sizeof(double));
	for (i = 0; i < pState->M; ++i) {
E 10
		pState->data[i] = 1.;
	}
}

void
cleanup(void* cookie)
{
	struct _state *pState = (struct _state*)cookie;

D 10
	free(pState->data);
E 10
I 10
	if (pState->data) 
		free(pState->data);
E 10
}

void
D 3
do_bogomips(uint64 iterations, void* cookie)
E 3
I 3
D 4
do_float_bogomips(uint64 iterations, void* cookie)
E 4
I 4
D 6
do_float_bogomflops(uint64 iterations, void* cookie)
E 6
I 6
do_float_bogomflops(iter_t iterations, void* cookie)
E 6
E 4
{
	struct _state *pState = (struct _state*)cookie;
	register int i;
D 4
	register float *x = (double*)pState->data;
E 4
I 4
	register float *x = (float*)pState->data;
E 4

	while (iterations-- > 0) {
D 10
		for (i = 0; i < pState->N; ++i) {
E 10
I 10
		for (i = 0; i < pState->M; ++i) {
E 10
D 5
			x[i] = (1.0 + x[i])*(1.5 - x[i])/x[i];
E 5
I 5
			x[i] = (1.0 + x[i]) * (1.5 - x[i]) / x[i];
E 5
		}
	}
}

void
D 4
do_double_bogomips(uint64 iterations, void* cookie)
E 4
I 4
D 6
do_double_bogomflops(uint64 iterations, void* cookie)
E 6
I 6
do_double_bogomflops(iter_t iterations, void* cookie)
E 6
E 4
E 3
{
	struct _state *pState = (struct _state*)cookie;
	register int i;
	register double *x = (double*)pState->data;

	while (iterations-- > 0) {
D 10
		for (i = 0; i < pState->N; ++i) {
E 10
I 10
		for (i = 0; i < pState->M; ++i) {
E 10
D 3
			x[i] = (1.0 + x[i])*(2.0 - x[i])/2.0;
E 3
I 3
D 5
			x[i] = (1.0 + x[i])*(1.5 - x[i])/x[i];
E 5
I 5
			x[i] = (1.0 + x[i]) * (1.5 - x[i]) / x[i];
E 5
E 3
		}
	}
}

int
main(int ac, char **av)
{
I 13
	int	__n = 1;
E 13
D 9
	int i, j;
	uint64 iop_time;
	uint64 iop_N;
E 9
I 9
	int	c, i, j;
	int	warmup = 0;
I 12
	int	parallel = 1;
E 12
	int	repetitions = TRIES;
	uint64	iop_time;
	uint64	iop_N;
E 9
	struct _state state;
I 9
	char   *usage = "[-W <warmup>] [-N <repetitions>]\n";
E 9

D 10
	state.N = 1000;
	state.M = 1;
E 10
I 10
	state.N = 1;
	state.M = 1000;
	state.K = -1023;
	state.data = NULL;
E 10

D 9
	benchmp(NULL, do_integer_bitwise, NULL, 0, 1, 0, TRIES, &state);
E 9
I 9
D 12
	while (( c = getopt(ac, av, "W:N:")) != EOF) {
E 12
I 12
	while (( c = getopt(ac, av, "W:N:P:")) != EOF) {
E 12
		switch(c) {
		case 'W':
			warmup = atoi(optarg);
			break;
		case 'N':
			repetitions = atoi(optarg);
			break;
I 12
		case 'P':
			parallel = atoi(optarg);
			if (parallel <= 0) lmbench_usage(ac, av, usage);
			break;
E 12
		default:
			lmbench_usage(ac, av, usage);
			break;
		}
	}

D 10
	state.N = 1000;
	state.M = 1;

E 10
D 12
	benchmp(NULL, do_integer_bitwise, NULL, 0, 1, warmup, repetitions, &state);
E 12
I 12
D 13
	benchmp(NULL, do_integer_bitwise, NULL, 0, parallel, warmup, repetitions, &state);
E 13
I 13
	BENCH((*do_integer_bitwise)(__n, &state); __n = 1;, 0);
E 13
E 12
E 9
D 3
	nano("integer bitwise", get_n() * 100000 * 2);
E 3
I 3
D 14
	nano("integer bit", get_n() * 100000 * 2);
E 14
I 14
D 15
	nano("integer bit", get_n() * 100 * 2);
E 15
I 15
	nano("integer bit", get_n() * 100 * 3);
E 15
E 14
E 3
	iop_time = gettime();
D 14
	iop_N = get_n() * 100000 * 2;
E 14
I 14
D 15
	iop_N = get_n() * 100 * 2;
E 15
I 15
	iop_N = get_n() * 100 * 3;
E 15
E 14
	
I 3
D 9
	benchmp(NULL, do_integer_add, NULL, 0, 1, 0, TRIES, &state);
E 9
I 9
D 13
	benchmp(NULL, do_integer_add, NULL, 0, 1, warmup, repetitions, &state);
E 9
I 6
#ifndef __GNUC__
E 6
	settime(gettime() - (get_n() * 100000 * iop_time) / iop_N);
	nano("integer add", get_n() * 100000);
I 6
#else
D 7
	nano("integer add", get_n() * 100000 * 2);
E 7
I 7
	nano("integer add", get_n() * 10000 * 2);
E 7
#endif
E 13
I 13
	BENCH((*do_integer_add)(__n, &state); __n = 1;, 0);
D 14
	nano("integer add", get_n() * 100000 * 2);
E 14
I 14
	nano("integer add", get_n() * 100 * 2);
E 14
E 13
E 6
	
E 3
D 9
	benchmp(NULL, do_integer_mul, NULL, 0, 1, 0, TRIES, &state);
E 9
I 9
D 13
	benchmp(NULL, do_integer_mul, NULL, 0, 1, warmup, repetitions, &state);
E 13
I 13
	BENCH((*do_integer_mul)(__n, &state); __n = 1;, 0);
E 13
E 9
D 14
	settime(gettime() - (get_n() * 100000 * iop_time) / iop_N);
	nano("integer mul", get_n() * 100000);
E 14
I 14
	settime(gettime() - (get_n() * 10 * iop_time) / iop_N);
	nano("integer mul", get_n() * 100);
E 14
	
D 9
	benchmp(NULL, do_integer_div, NULL, 0, 1, 0, TRIES, &state);
E 9
I 9
D 13
	benchmp(NULL, do_integer_div, NULL, 0, 1, warmup, repetitions, &state);
E 13
I 13
	BENCH((*do_integer_div)(__n, &state); __n = 1;, 0);
E 13
E 9
D 14
	settime(gettime() - (get_n() * 100000 * iop_time) / iop_N);
	nano("integer div", get_n() * 100000);
E 14
I 14
	nano("integer div", get_n() * 100);
E 14
	
D 9
	benchmp(NULL, do_integer_mod, NULL, 0, 1, 0, TRIES, &state);
E 9
I 9
D 13
	benchmp(NULL, do_integer_mod, NULL, 0, 1, warmup, repetitions, &state);
E 13
I 13
	BENCH((*do_integer_mod)(__n, &state); __n = 1;, 0);
E 13
E 9
D 14
	settime(gettime() - (get_n() * 100000 * iop_time) / iop_N);
	nano("integer mod", get_n() * 100000);
E 14
I 14
	settime(gettime() - (get_n() *  100 * iop_time) / iop_N);
	nano("integer mod", get_n() * 100);
E 14
	
I 3
D 9
	benchmp(NULL, do_uint64_bitwise, NULL, 0, 1, 0, TRIES, &state);
E 9
I 9
D 13
	benchmp(NULL, do_uint64_bitwise, NULL, 0, 1, warmup, repetitions, &state);
E 9
	nano("uint64 bit", get_n() * 100000 * 2);
E 13
I 13
	BENCH((*do_int64_bitwise)(__n, &state); __n = 1;, 0);
D 14
	nano("int64 bit", get_n() * 100000 * 2);
E 14
I 14
D 15
	nano("int64 bit", get_n() * 100 * 2);
E 15
I 15
	nano("int64 bit", get_n() * 100 * 3);
E 15
E 14
E 13
	iop_time = gettime();
D 14
	iop_N = get_n() * 100000 * 2;
E 14
I 14
D 15
	iop_N = get_n() * 100 * 2;
E 15
I 15
	iop_N = get_n() * 100 * 3;
E 15
E 14
D 5
	
E 5
I 5

E 5
D 9
	benchmp(NULL, do_uint64_add, NULL, 0, 1, 0, TRIES, &state);
E 9
I 9
D 13
	benchmp(NULL, do_uint64_add, NULL, 0, 1, warmup, repetitions, &state);
E 9
I 6
#ifndef __GNUC__
	settime(gettime() - (get_n() * 100000 * iop_time) / iop_N);
D 8
	nano("integer add", get_n() * 100000);
E 8
I 8
	nano("uint64 add", get_n() * 100000);
E 8
#else
E 6
D 5
	settime(gettime() - (get_n() * 100000 * iop_time) / iop_N);
	nano("uint64 add", get_n() * 100000);
E 5
I 5
D 7
	nano("uint64 add", get_n() * 100000 * 2);
E 7
I 7
	nano("uint64 add", get_n() * 10000 * 2);
E 7
I 6
#endif
E 13
I 13
	BENCH((*do_int64_add)(__n, &state); __n = 1;, 0);
D 14
	nano("int64 add", get_n() * 100000 * 2);
E 14
I 14
	nano("int64 add", get_n() * 100 * 2);
E 14
E 13
E 6
E 5
	
D 9
	benchmp(NULL, do_uint64_mul, NULL, 0, 1, 0, TRIES, &state);
E 9
I 9
D 13
	benchmp(NULL, do_uint64_mul, NULL, 0, 1, warmup, repetitions, &state);
E 13
I 13
	BENCH((*do_int64_mul)(__n, &state); __n = 1;, 0);
E 13
E 9
D 14
	settime(gettime() - (get_n() * 100000 * iop_time) / iop_N);
D 13
	nano("uint64 mul", get_n() * 100000);
E 13
I 13
	nano("int64 mul", get_n() * 100000);
E 14
I 14
	settime(gettime() - (get_n() * 10 * iop_time) / iop_N);
	nano("int64 mul", get_n() * 100);
E 14
E 13
	
D 9
	benchmp(NULL, do_uint64_div, NULL, 0, 1, 0, TRIES, &state);
E 9
I 9
D 13
	benchmp(NULL, do_uint64_div, NULL, 0, 1, warmup, repetitions, &state);
E 13
I 13
	BENCH((*do_int64_div)(__n, &state); __n = 1;, 0);
E 13
E 9
D 14
	settime(gettime() - (get_n() * 100000 * iop_time) / iop_N);
D 13
	nano("uint64 div", get_n() * 100000);
E 13
I 13
	nano("int64 div", get_n() * 100000);
E 14
I 14
	nano("int64 div", get_n() * 100);
E 14
E 13
	
D 9
	benchmp(NULL, do_uint64_mod, NULL, 0, 1, 0, TRIES, &state);
E 9
I 9
D 13
	benchmp(NULL, do_uint64_mod, NULL, 0, 1, warmup, repetitions, &state);
E 13
I 13
	BENCH((*do_int64_mod)(__n, &state); __n = 1;, 0);
E 13
E 9
D 14
	settime(gettime() - (get_n() * 100000 * iop_time) / iop_N);
D 13
	nano("uint64 mod", get_n() * 100000);
E 13
I 13
	nano("int64 mod", get_n() * 100000);
E 14
I 14
	settime(gettime() - (get_n() * 100 * iop_time) / iop_N);
	nano("int64 mod", get_n() * 100);
E 14
E 13
	
E 3
D 9
	benchmp(NULL, do_float_add, NULL, 0, 1, 0, TRIES, &state);
E 9
I 9
D 13
	benchmp(NULL, do_float_add, NULL, 0, 1, warmup, repetitions, &state);
E 13
I 13
	BENCH((*do_float_add)(__n, &state); __n = 1;, 0);
E 13
E 9
I 4
D 10
#ifndef __GNUC__
E 4
D 3
	nano("float add", get_n() * 100000 * 2);
E 3
I 3
	nano("float add", get_n() * 100000);
I 4
#else
	nano("float add", get_n() * 10000);
#endif
E 10
I 10
D 14
	nano("float add", get_n() * 1000 * 11);
E 14
I 14
	nano("float add", get_n() * 11);
E 14
E 10
E 4
E 3
	
D 9
	benchmp(NULL, do_float_mul, NULL, 0, 1, 0, TRIES, &state);
E 9
I 9
D 13
	benchmp(NULL, do_float_mul, NULL, 0, 1, warmup, repetitions, &state);
E 13
I 13
	BENCH((*do_float_mul)(__n, &state); __n = 1;, 0);
E 13
E 9
I 4
#ifndef __GNUC__
E 4
D 3
	nano("float mul", get_n() * 100000 * 2);
E 3
I 3
D 14
	nano("float mul", get_n() * 100000);
E 14
I 14
	nano("float mul", get_n() * 100);
E 14
I 4
#else
D 14
	nano("float mul", get_n() * 10000);
E 14
I 14
	nano("float mul", get_n() * 10);
E 14
#endif
E 4
E 3
	
D 9
	benchmp(NULL, do_float_div, NULL, 0, 1, 0, TRIES, &state);
E 9
I 9
D 13
	benchmp(NULL, do_float_div, NULL, 0, 1, warmup, repetitions, &state);
E 13
I 13
	BENCH((*do_float_div)(__n, &state); __n = 1;, 0);
E 13
E 9
I 4
#ifndef __GNUC__
E 4
D 3
	nano("float div", get_n() * 100000 * 2);
E 3
I 3
D 14
	nano("float div", get_n() * 100000);
E 14
I 14
	nano("float div", get_n() * 100);
E 14
I 4
#else
D 14
	nano("float div", get_n() * 10000);
E 14
I 14
	nano("float div", get_n() * 10);
E 14
#endif
E 4
E 3

D 9
	benchmp(NULL, do_double_add, NULL, 0, 1, 0, TRIES, &state);
E 9
I 9
D 13
	benchmp(NULL, do_double_add, NULL, 0, 1, warmup, repetitions, &state);
E 13
I 13
	BENCH((*do_double_add)(__n, &state); __n = 1;, 0);
E 13
E 9
I 4
D 10
#ifndef __GNUC__
E 4
D 3
	nano("double add", get_n() * 100000 * 2);
E 3
I 3
	nano("double add", get_n() * 100000);
I 4
#else
	nano("double add", get_n() * 10000);
#endif
E 10
I 10
D 14
	nano("double add", get_n() * 1000 * 11);
E 14
I 14
	nano("double add", get_n() * 11);
E 14
E 10
E 4
E 3
	
D 9
	benchmp(NULL, do_double_mul, NULL, 0, 1, 0, TRIES, &state);
E 9
I 9
D 13
	benchmp(NULL, do_double_mul, NULL, 0, 1, warmup, repetitions, &state);
E 13
I 13
	BENCH((*do_double_mul)(__n, &state); __n = 1;, 0);
E 13
E 9
I 4
#ifndef __GNUC__
E 4
D 3
	nano("double mul", get_n() * 100000 * 2);
E 3
I 3
D 14
	nano("double mul", get_n() * 100000);
E 14
I 14
	nano("double mul", get_n() * 100);
E 14
I 4
#else
D 14
	nano("double mul", get_n() * 10000);
E 14
I 14
	nano("double mul", get_n() * 10);
E 14
#endif
E 4
E 3
	
D 9
	benchmp(NULL, do_double_div, NULL, 0, 1, 0, TRIES, &state);
E 9
I 9
D 13
	benchmp(NULL, do_double_div, NULL, 0, 1, warmup, repetitions, &state);
E 13
I 13
	BENCH((*do_double_div)(__n, &state); __n = 1;, 0);
E 13
E 9
I 4
#ifndef __GNUC__
E 4
D 3
	nano("double div", get_n() * 100000 * 2);
E 3
I 3
D 14
	nano("double div", get_n() * 100000);
E 14
I 14
	nano("double div", get_n() * 100);
E 14
I 4
#else
D 14
	nano("double div", get_n() * 10000);
E 14
I 14
	nano("double div", get_n() * 10);
E 14
#endif
E 4
E 3

D 3
	benchmp(initialize, do_bogomips, cleanup, 0, 1, 0, TRIES, &state);
	nano("bogomips", get_n() * state.N);
E 3
I 3
	benchmp(float_initialize, 
D 4
		do_float_bogomips, cleanup, 0, 1, 0, TRIES, &state);
	nano("float bogomips", get_n() * state.N);
E 4
I 4
D 9
		do_float_bogomflops, cleanup, 0, 1, 0, TRIES, &state);
E 9
I 9
D 12
		do_float_bogomflops, cleanup, 0, 1, warmup, repetitions, &state);
E 12
I 12
		do_float_bogomflops, cleanup, 0, parallel, warmup, repetitions, &state);
E 12
E 9
D 11
	nano("float bogomflops", get_n() * state.N);
E 11
I 11
	nano("float bogomflops", get_n() * state.M);
E 11
E 4

	benchmp(double_initialize, 
D 4
		do_double_bogomips, cleanup, 0, 1, 0, TRIES, &state);
	nano("double bogomips", get_n() * state.N);
E 4
I 4
D 9
		do_double_bogomflops, cleanup, 0, 1, 0, TRIES, &state);
E 9
I 9
D 12
		do_double_bogomflops, cleanup, 0, 1, warmup, repetitions, &state);
E 12
I 12
		do_double_bogomflops, cleanup, 0, parallel, warmup, repetitions, &state);
E 12
E 9
D 11
	nano("double bogomflops", get_n() * state.N);
E 11
I 11
	nano("double bogomflops", get_n() * state.M);
E 11
E 4
E 3

	return(0);
}

E 2
I 1
E 1
