H04490
s 00001/00001/00463
d D 1.7 02/10/27 07:10:23 staelin 8 7
c par_ops: fixup initialization of double variables toOM
c   prevent arithmetic errors
cC
cHdisks.bitmover.com
cK50692
cZ-08:00
e
s 00001/00000/00463
d D 1.6 02/06/30 16:42:31 staelin 7 6
c Switch to minimum time from median time to make results more stable.
c (We don't want the representative time, we want the fastest possible
c time, so this should be OK.)
cC
cHhpli69.hpli.hpl.hp.com
cK51301
cZ+03:00
e
s 00002/00002/00461
d D 1.5 02/01/07 01:30:42 staelin 6 5
c fix bug in integer bitwise operation expressions, which
c were optimizable by smart compilers.  Oops.
cC
cHdisks.bitmover.com
cK49843
cZ+00:00
e
s 00059/00031/00404
d D 1.4 01/11/15 14:27:00 staelin 5 4
c Updated par_ops to improve accuracy of results by reducing the
c number of non-relevant operations inside various operation kernels.
c For example, integer_div used to use the statement r=(i/r)^r, which
c had an irrelevant XOR operation.  The new statement only uses DIV
c statements.  Fixed kernels for integer_bit, integer_mul, integer_div,
c int64_bit, int64_mul, int64_div.
cC
cK47783
cZ+02:00
e
s 00042/00050/00393
d D 1.3 01/05/14 11:35:16 staelin 4 3
c Add typedef for int64
c Switch lat_ops and par_mem from using benchmp() to BENCH() for performance reasons
c Change expression used in lat_ops and par_mem for measuring int and int64 add performance
c   to one that only uses '+' operations
cC
cHhpli69.hpli.hpl.hp.com
cK09209
e
s 00021/00021/00422
d D 1.2 00/09/26 16:01:56 staelin 3 2
c - Fix bugs in lat_ops and par_ops in float_add, float_mul, double_add, and double_mul
c   which were causing arithmetic overflows which caused the benchmarks to crash
cC
cK25435
e
s 00443/00000/00000
d D 1.1 00/08/16 13:10:18 staelin 2 1
cC
cF1
cK38540
cO-rw-rw-r--
e
s 00000/00000/00000
d D 1.0 00/08/16 13:10:18 staelin 1 0
c BitKeeper file /tmp_mnt/usr/WebPaper/users/staelin/src/LMbench/src/par_ops.c
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHhpli8.hpli.hpl.hp.com
cK16292
cPsrc/par_ops.c
cR3e0268b53182d2da
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
 * par_ops.c - benchmark of simple operation parallelism
 *
 * Copyright (c) 2000 Carl Staelin.
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
char	*id = "$Id$\n";

#include "bench.h"

struct _state {
	int	N;
	int	M;
	int*	int_data;
	double*	double_data;
};

void	initialize(void* cookie);
void	cleanup(void* cookie);

#define	FIVE(m)		m m m m m
#define	TEN(m)		FIVE(m) FIVE(m)
#define	FIFTY(m)	TEN(m) TEN(m) TEN(m) TEN(m) TEN(m)
#define	HUNDRED(m)	FIFTY(m) FIFTY(m)

#define MAX_LOAD_PARALLELISM 16

double
max_parallelism(bench_f* benchmarks, 
		int warmup, int repetitions, void* cookie)
{
D 4
	int		i, j, k;
E 4
I 4
	int		i, j, k, __n;
E 4
	double		baseline, max_load_parallelism, load_parallelism;
	result_t	*results, *r_save;

I 4
	__n = 1;
E 4
	max_load_parallelism = 1.;

I 4
	initialize(cookie);
E 4
	for (i = 0; i < MAX_LOAD_PARALLELISM; ++i) {
D 4
		benchmp(initialize, benchmarks[i], cleanup, 
			0, 1, warmup, repetitions, cookie);
E 4
I 4
		BENCH((*benchmarks[i])(__n, cookie); __n = 1;, 0);
I 7
		save_minimum();
E 7
E 4

		if (gettime() == 0)
			return -1.;

		if (i == 0) {
			baseline = (double)gettime() / (double)get_n();
		} else {
			load_parallelism = baseline;
			load_parallelism /= (double)gettime();
			load_parallelism *= (double)((i + 1) * get_n());
			if (load_parallelism > max_load_parallelism) {
				max_load_parallelism = load_parallelism;
			}
		}
	}
I 4
	cleanup(cookie);
E 4
	return max_load_parallelism;
}

#define REPEAT_0(m)	m(0)
#define REPEAT_1(m)	REPEAT_0(m) m(1)
#define REPEAT_2(m)	REPEAT_1(m) m(2)
#define REPEAT_3(m)	REPEAT_2(m) m(3)
#define REPEAT_4(m)	REPEAT_3(m) m(4)
#define REPEAT_5(m)	REPEAT_4(m) m(5)
#define REPEAT_6(m)	REPEAT_5(m) m(6)
#define REPEAT_7(m)	REPEAT_6(m) m(7)
#define REPEAT_8(m)	REPEAT_7(m) m(8)
#define REPEAT_9(m)	REPEAT_8(m) m(9)
#define REPEAT_10(m)	REPEAT_9(m) m(10)
#define REPEAT_11(m)	REPEAT_10(m) m(11)
#define REPEAT_12(m)	REPEAT_11(m) m(12)
#define REPEAT_13(m)	REPEAT_12(m) m(13)
#define REPEAT_14(m)	REPEAT_13(m) m(14)
#define REPEAT_15(m)	REPEAT_14(m) m(15)

D 5
#define BODY(N)		p##N = (char**)*p##N;
#define DECLARE(N)	static char **sp##N; register char **p##N;
#define INIT(N)		p##N = (addr_save==state->addr) ? sp##N : (char**)state->p[N];
#define SAVE(N)		sp##N = p##N;

E 5
#define BENCHMARK(benchmark,N,repeat)					\
void benchmark##_##N(iter_t iterations, void *cookie) 			\
{									\
	register iter_t i = iterations;					\
	struct _state* state = (struct _state*)cookie;			\
	repeat(DECLARE);						\
									\
	repeat(INIT);							\
	while (i-- > 0) {						\
I 5
		repeat(PREAMBLE);					\
E 5
		TEN(repeat(BODY));					\
	}								\
									\
	repeat(SAVE);							\
}

#define PARALLEL_BENCHMARKS(benchmark)					\
	BENCHMARK(benchmark, 0, REPEAT_0)				\
	BENCHMARK(benchmark, 1, REPEAT_1)				\
	BENCHMARK(benchmark, 2, REPEAT_2)				\
	BENCHMARK(benchmark, 3, REPEAT_3)				\
	BENCHMARK(benchmark, 4, REPEAT_4)				\
	BENCHMARK(benchmark, 5, REPEAT_5)				\
	BENCHMARK(benchmark, 6, REPEAT_6)				\
	BENCHMARK(benchmark, 7, REPEAT_7)				\
	BENCHMARK(benchmark, 8, REPEAT_8)				\
	BENCHMARK(benchmark, 9, REPEAT_9)				\
	BENCHMARK(benchmark, 10, REPEAT_10)				\
	BENCHMARK(benchmark, 11, REPEAT_11)				\
	BENCHMARK(benchmark, 12, REPEAT_12)				\
	BENCHMARK(benchmark, 13, REPEAT_13)				\
	BENCHMARK(benchmark, 14, REPEAT_14)				\
	BENCHMARK(benchmark, 15, REPEAT_15)				\
									\
	bench_f benchmark##_benchmarks[] = {				\
		benchmark##_0,						\
		benchmark##_1,						\
		benchmark##_2,						\
		benchmark##_3,						\
		benchmark##_4,						\
		benchmark##_5,						\
		benchmark##_6,						\
		benchmark##_7,						\
		benchmark##_8,						\
		benchmark##_9,						\
		benchmark##_10,						\
		benchmark##_11,						\
		benchmark##_12,						\
		benchmark##_13,						\
		benchmark##_14,						\
		benchmark##_15						\
	};

#undef	BODY
#undef	DECLARE
#undef	INIT
I 5
#undef	PREAMBLE
E 5
#undef	SAVE
D 5
#define BODY(N)		r##N ^= i; r##N<<=1;
#define DECLARE(N)	register int r##N;
#define INIT(N)		r##N = state->int_data[N];
E 5
I 5
D 6
#define BODY(N)		r##N ^= s##N; s##N ^= r##N;
E 6
I 6
#define BODY(N)		r##N ^= s##N; s##N ^= r##N; s##N |= (N+1)<<8;
E 6
#define DECLARE(N)	register int r##N, s##N;
#define INIT(N)		r##N = state->int_data[N] + 1; s##N = (N+1) + r##N;
#define PREAMBLE(N)	
E 5
D 3
#define SAVE(N)		state->int_data[N] = r##N;
E 3
I 3
#define SAVE(N)		use_int((int)r##N);
E 3
PARALLEL_BENCHMARKS(integer_bit)

#undef	BODY
#undef	DECLARE
#undef	INIT
I 5
#undef	PREAMBLE
E 5
#undef	SAVE
D 4
#ifndef __GNUC__
			/* required because of an HP ANSI/C compiler bug */
			r##N = ( r##N + i ) ^ r##N;
#else
#define BODY(N)		r##N = r##N + r##N + i;
#endif
#define DECLARE(N)	register int r##N;
#define INIT(N)		r##N = state->int_data[N];
D 3
#define SAVE(N)		state->int_data[N] = r##N;
E 3
I 3
#define SAVE(N)		use_int((int)r##N);
E 4
I 4
#define BODY(N)		a##N += b##N; b##N -= a##N;
#define DECLARE(N)	register int a##N, b##N;
#define INIT(N)		b##N = a##N = state->int_data[N];
I 5
#define PREAMBLE(N)
E 5
#define SAVE(N)		use_int(a##N + b##N);
E 4
E 3
PARALLEL_BENCHMARKS(integer_add)

#undef	BODY
#undef	DECLARE
#undef	INIT
I 5
#undef	PREAMBLE
E 5
#undef	SAVE
D 4
#define BODY(N)		r##N = ( r##N * i) ^ r##N;
E 4
I 4
D 5
#define BODY(N)		r##N = (r##N * i) ^ r##N;
E 4
#define DECLARE(N)	register int r##N;
#define INIT(N)		r##N = state->int_data[N];
E 5
I 5
#define BODY(N)		r##N = (r##N * s##N);
#define DECLARE(N)	register int r##N, s##N;
#define INIT(N)		r##N = state->int_data[N]; s##N = (N+1) ^ r##N;
#define PREAMBLE(N)	
E 5
D 3
#define SAVE(N)		state->int_data[N] = r##N;
E 3
I 3
#define SAVE(N)		use_int((int)r##N);
E 3
PARALLEL_BENCHMARKS(integer_mul)

#undef	BODY
#undef	DECLARE
#undef	INIT
I 5
#undef	PREAMBLE
E 5
#undef	SAVE
D 4
#define BODY(N)		r##N = ( r##N / i) ^ r##N;
E 4
I 4
D 5
#define BODY(N)		r##N = (i / r##N) ^ r##N;
E 4
#define DECLARE(N)	register int r##N;
#define INIT(N)		r##N = state->int_data[N];
E 5
I 5
#define BODY(N)		r##N = (s##N / r##N);
#define DECLARE(N)	register int r##N, s##N;
#define INIT(N)		r##N = state->int_data[N] + 1; s##N = (N+1)<<20;
#define PREAMBLE(N)	
E 5
D 3
#define SAVE(N)		state->int_data[N] = r##N;
E 3
I 3
#define SAVE(N)		use_int((int)r##N);
E 3
PARALLEL_BENCHMARKS(integer_div)

#undef	BODY
#undef	DECLARE
#undef	INIT
I 5
#undef	PREAMBLE
E 5
#undef	SAVE
D 4
#define BODY(N)		r##N = ( r##N % i) ^ r##N;
E 4
I 4
D 5
#define BODY(N)		r##N = (i % r##N) ^ r##N;
E 4
#define DECLARE(N)	register int r##N;
#define INIT(N)		r##N = state->int_data[N];
E 5
I 5
#define BODY(N)		r##N = (s##N % r##N) | r##N;
#define DECLARE(N)	register int r##N, s##N;
#define INIT(N)		r##N = state->int_data[N] + 1; s##N = 0;
#define PREAMBLE(N)	s##N++;	
E 5
D 3
#define SAVE(N)		state->int_data[N] = r##N;
E 3
I 3
#define SAVE(N)		use_int((int)r##N);
E 3
PARALLEL_BENCHMARKS(integer_mod)

#undef	BODY
#undef	DECLARE
#undef	INIT
I 5
#undef	PREAMBLE
E 5
#undef	SAVE
D 5
#define BODY(N)		r##N ^= i; r##N<<=1;
D 4
#define DECLARE(N)	register uint64 r##N;
#define INIT(N)		r##N = (uint64)state->int_data[N];
E 4
I 4
#define DECLARE(N)	register int64 r##N;
#define INIT(N)		r##N = (int64)state->int_data[N];
E 5
I 5
D 6
#define BODY(N)		r##N ^= s##N; s##N ^= r##N;
E 6
I 6
#define BODY(N)		r##N ^= s##N; s##N ^= r##N; s##N |= (N+1)<<8;
E 6
#define DECLARE(N)	register int64 r##N, s##N;
#define INIT(N)		r##N = (int64)state->int_data[N] + 1; s##N = (N+1) + r##N;
#define PREAMBLE(N)	
E 5
E 4
D 3
#define SAVE(N)		state->int_data[N] = (int)r##N;
E 3
I 3
#define SAVE(N)		use_int((int)r##N);
E 3
D 4
PARALLEL_BENCHMARKS(uint64_bit)
E 4
I 4
PARALLEL_BENCHMARKS(int64_bit)
E 4

#undef	BODY
#undef	DECLARE
#undef	INIT
I 5
#undef	PREAMBLE
E 5
#undef	SAVE
D 4
#ifndef __GNUC__
			/* required because of an HP ANSI/C compiler bug */
			r##N = ( r##N + i ) ^ r##N;
#else
#define BODY(N)		r##N = r##N + r##N + i;
#endif
#define DECLARE(N)	register uint64 r##N;
#define INIT(N)		r##N = (uint64)state->int_data[N];
D 3
#define SAVE(N)		state->int_data[N] = (int)r##N;
E 3
I 3
#define SAVE(N)		use_int((int)r##N);
E 3
PARALLEL_BENCHMARKS(uint64_add)
E 4
I 4
#define BODY(N)		a##N += b##N; b##N -= a##N;
#define DECLARE(N)	register int64 a##N, b##N;
#define INIT(N)		b##N = a##N = (int64)state->int_data[N];
I 5
#define PREAMBLE(N)
E 5
#define SAVE(N)		use_int((int)a##N + (int)b##N);
PARALLEL_BENCHMARKS(int64_add)
E 4

#undef	BODY
#undef	DECLARE
#undef	INIT
I 5
#undef	PREAMBLE
E 5
#undef	SAVE
D 4
#define BODY(N)		r##N = ( r##N * i) ^ r##N;
#define DECLARE(N)	register uint64 r##N;
#define INIT(N)		r##N = (uint64)state->int_data[N];
E 4
I 4
D 5
#define BODY(N)		r##N = (r##N * i) ^ r##N;
#define DECLARE(N)	register int64 r##N;
#define INIT(N)		r##N = (int64)state->int_data[N];
E 5
I 5
#define BODY(N)		r##N = (r##N * s##N);
#define DECLARE(N)	register int64 r##N, s##N;
#define INIT(N)		r##N = (int64)state->int_data[N]; s##N = (N+1) ^ r##N;
#define PREAMBLE(N)	
E 5
E 4
D 3
#define SAVE(N)		state->int_data[N] = (int)r##N;
E 3
I 3
#define SAVE(N)		use_int((int)r##N);
E 3
D 4
PARALLEL_BENCHMARKS(uint64_mul)
E 4
I 4
PARALLEL_BENCHMARKS(int64_mul)
E 4

#undef	BODY
#undef	DECLARE
#undef	INIT
I 5
#undef	PREAMBLE
E 5
#undef	SAVE
D 4
#define BODY(N)		r##N = ( r##N / i) ^ r##N;
#define DECLARE(N)	register uint64 r##N;
#define INIT(N)		r##N = (uint64)state->int_data[N];
E 4
I 4
D 5
#define BODY(N)		r##N = (i / r##N) ^ r##N;
#define DECLARE(N)	register int64 r##N;
#define INIT(N)		r##N = (int64)state->int_data[N];
E 5
I 5
#define BODY(N)		r##N = (s##N / r##N);
#define DECLARE(N)	register int64 r##N, s##N;
#define INIT(N)		r##N = (int64)state->int_data[N] + 1; s##N = (N+1)<<20;
#define PREAMBLE(N)	
E 5
E 4
D 3
#define SAVE(N)		state->int_data[N] = (int)r##N;
E 3
I 3
#define SAVE(N)		use_int((int)r##N);
E 3
D 4
PARALLEL_BENCHMARKS(uint64_div)
E 4
I 4
PARALLEL_BENCHMARKS(int64_div)
E 4

#undef	BODY
#undef	DECLARE
#undef	INIT
I 5
#undef	PREAMBLE
E 5
#undef	SAVE
D 4
#define BODY(N)		r##N = ( r##N % i) ^ r##N;
#define DECLARE(N)	register uint64 r##N;
#define INIT(N)		r##N = (uint64)state->int_data[N];
E 4
I 4
D 5
#define BODY(N)		r##N = (i % r##N) ^ r##N;
#define DECLARE(N)	register int64 r##N;
#define INIT(N)		r##N = (int64)state->int_data[N];
E 5
I 5
#define BODY(N)		r##N = (s##N % r##N) ^ r##N;
#define DECLARE(N)	register int64 r##N, s##N;
#define INIT(N)		r##N = (int64)state->int_data[N]; s##N = 0;
#define PREAMBLE(N)	s##N++;	
E 5
E 4
D 3
#define SAVE(N)		state->int_data[N] = (int)r##N;
E 3
I 3
#define SAVE(N)		use_int((int)r##N);
E 3
D 4
PARALLEL_BENCHMARKS(uint64_mod)
E 4
I 4
PARALLEL_BENCHMARKS(int64_mod)
E 4

#undef	BODY
#undef	DECLARE
#undef	INIT
I 5
#undef	PREAMBLE
E 5
#undef	SAVE
#define BODY(N)		r##N += r##N;
#define DECLARE(N)	register float r##N;
D 3
#define INIT(N)		r##N = (float)state->double_data[N];
#define SAVE(N)		state->double_data[N] = (double)r##N;
E 3
I 3
#define INIT(N)		r##N = (float)state->double_data[N] - 1.;
I 5
#define PREAMBLE(N)
E 5
#define SAVE(N)		use_int((int)r##N);
E 3
PARALLEL_BENCHMARKS(float_add)

#undef	BODY
#undef	DECLARE
#undef	INIT
I 5
#undef	PREAMBLE
E 5
#undef	SAVE
#define BODY(N)		r##N *= r##N;
#define DECLARE(N)	register float r##N;
#define INIT(N)		r##N = (float)state->double_data[N];
I 5
#define PREAMBLE(N)
E 5
D 3
#define SAVE(N)		state->double_data[N] = (double)r##N;
E 3
I 3
#define SAVE(N)		use_int((int)r##N);
E 3
PARALLEL_BENCHMARKS(float_mul)

#undef	BODY
#undef	DECLARE
#undef	INIT
I 5
#undef	PREAMBLE
E 5
#undef	SAVE
#define BODY(N)		r##N = s##N / r##N;
#define DECLARE(N)	register float r##N, s##N;
#define INIT(N)		r##N = (float)state->double_data[N]; s##N = (float)state->int_data[N];
I 5
#define PREAMBLE(N)
E 5
D 3
#define SAVE(N)		state->double_data[N] = (double)r##N;
E 3
I 3
#define SAVE(N)		use_int((int)r##N); use_int((int)s##N);
E 3
PARALLEL_BENCHMARKS(float_div)

#undef	BODY
#undef	DECLARE
#undef	INIT
I 5
#undef	PREAMBLE
E 5
#undef	SAVE
#define BODY(N)		r##N += r##N;
#define DECLARE(N)	register double r##N;
D 3
#define INIT(N)		r##N = state->double_data[N];
#define SAVE(N)		state->double_data[N] = r##N;
E 3
I 3
#define INIT(N)		r##N = state->double_data[N] - 1.;
I 5
#define PREAMBLE(N)
E 5
#define SAVE(N)		use_int((int)r##N);
E 3
PARALLEL_BENCHMARKS(double_add)

#undef	BODY
#undef	DECLARE
#undef	INIT
I 5
#undef	PREAMBLE
E 5
#undef	SAVE
#define BODY(N)		r##N *= r##N;
#define DECLARE(N)	register double r##N;
#define INIT(N)		r##N = state->double_data[N];
I 5
#define PREAMBLE(N)
E 5
D 3
#define SAVE(N)		state->double_data[N] = r##N;
E 3
I 3
#define SAVE(N)		use_int((int)r##N);
E 3
PARALLEL_BENCHMARKS(double_mul)

#undef	BODY
#undef	DECLARE
#undef	INIT
I 5
#undef	PREAMBLE
E 5
#undef	SAVE
#define BODY(N)		r##N = s##N / r##N;
#define DECLARE(N)	register double r##N, s##N;
#define INIT(N)		r##N = state->double_data[N]; s##N = (double)state->int_data[N];
I 5
#define PREAMBLE(N)
E 5
D 3
#define SAVE(N)		state->double_data[N] = r##N;
E 3
I 3
#define SAVE(N)		use_int((int)r##N); use_int((int)s##N);
E 3
PARALLEL_BENCHMARKS(double_div)


void
initialize(void* cookie)
{
	struct _state *state = (struct _state*)cookie;
	register int i;

	state->int_data = (int*)malloc(MAX_LOAD_PARALLELISM * sizeof(int));
	state->double_data = (double*)malloc(MAX_LOAD_PARALLELISM * sizeof(double));

	for (i = 0; i < MAX_LOAD_PARALLELISM; ++i) {
D 5
		state->int_data[i] = (double)(rand() + 1);
D 3
		state->double_data[i] = (double)(rand() + 1);
E 3
I 3
		state->double_data[i] = state->N;
E 5
I 5
		state->int_data[i] = i+1;
D 8
		state->double_data[i] = rand() + 1.;
E 8
I 8
		state->double_data[i] = 1.;
E 8
E 5
E 3
	}
}

void
cleanup(void* cookie)
{
	struct _state *state = (struct _state*)cookie;

	free(state->int_data);
	free(state->double_data);
}


int
main(int ac, char **av)
{
	int	c;
	int	warmup = 0;
	int	repetitions = TRIES;
	double	par;
	struct _state	state;
	char   *usage = "[-W <warmup>] [-N <repetitions>]\n";

D 3
	state.N = 1000;
	state.M = 1;
E 3
I 3
	state.N = 1;
	state.M = 1000;
E 3

	while (( c = getopt(ac, av, "W:N:")) != EOF) {
		switch(c) {
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

	par = max_parallelism(integer_bit_benchmarks, 
			      warmup, repetitions, &state);
	if (par > 0.)
		fprintf(stderr, "integer bit parallelism: %.2f\n", par);

	par = max_parallelism(integer_add_benchmarks, 
			      warmup, repetitions, &state);
	if (par > 0.)
		fprintf(stderr, "integer add parallelism: %.2f\n", par);

	par = max_parallelism(integer_mul_benchmarks, 
			      warmup, repetitions, &state);
	if (par > 0.)
		fprintf(stderr, "integer mul parallelism: %.2f\n", par);

	par = max_parallelism(integer_div_benchmarks, 
			      warmup, repetitions, &state);
	if (par > 0.)
		fprintf(stderr, "integer div parallelism: %.2f\n", par);

	par = max_parallelism(integer_mod_benchmarks, 
			      warmup, repetitions, &state);
	if (par > 0.)
		fprintf(stderr, "integer mod parallelism: %.2f\n", par);

D 4
	par = max_parallelism(uint64_bit_benchmarks, 
E 4
I 4
	par = max_parallelism(int64_bit_benchmarks, 
E 4
			      warmup, repetitions, &state);
	if (par > 0.)
D 4
		fprintf(stderr, "uint64 bit parallelism: %.2f\n", par);
E 4
I 4
		fprintf(stderr, "int64 bit parallelism: %.2f\n", par);
E 4

D 4
	par = max_parallelism(uint64_add_benchmarks, 
E 4
I 4
	par = max_parallelism(int64_add_benchmarks, 
E 4
			      warmup, repetitions, &state);
	if (par > 0.)
D 4
		fprintf(stderr, "uint64 add parallelism: %.2f\n", par);
E 4
I 4
		fprintf(stderr, "int64 add parallelism: %.2f\n", par);
E 4

D 4
	par = max_parallelism(uint64_mul_benchmarks, 
E 4
I 4
	par = max_parallelism(int64_mul_benchmarks, 
E 4
			      warmup, repetitions, &state);
	if (par > 0.)
D 4
		fprintf(stderr, "uint64 mul parallelism: %.2f\n", par);
E 4
I 4
		fprintf(stderr, "int64 mul parallelism: %.2f\n", par);
E 4

D 4
	par = max_parallelism(uint64_div_benchmarks, 
E 4
I 4
	par = max_parallelism(int64_div_benchmarks, 
E 4
			      warmup, repetitions, &state);
	if (par > 0.)
D 4
		fprintf(stderr, "uint64 div parallelism: %.2f\n", par);
E 4
I 4
		fprintf(stderr, "int64 div parallelism: %.2f\n", par);
E 4

D 4
	par = max_parallelism(uint64_mod_benchmarks, 
E 4
I 4
	par = max_parallelism(int64_mod_benchmarks, 
E 4
			      warmup, repetitions, &state);
	if (par > 0.)
D 4
		fprintf(stderr, "uint64 mod parallelism: %.2f\n", par);
E 4
I 4
		fprintf(stderr, "int64 mod parallelism: %.2f\n", par);
E 4

	par = max_parallelism(float_add_benchmarks, 
			      warmup, repetitions, &state);
	if (par > 0.)
		fprintf(stderr, "float add parallelism: %.2f\n", par);

	par = max_parallelism(float_mul_benchmarks, 
			      warmup, repetitions, &state);
	if (par > 0.)
		fprintf(stderr, "float mul parallelism: %.2f\n", par);

	par = max_parallelism(float_div_benchmarks, 
			      warmup, repetitions, &state);
	if (par > 0.)
		fprintf(stderr, "float div parallelism: %.2f\n", par);

	par = max_parallelism(double_add_benchmarks, 
			      warmup, repetitions, &state);
	if (par > 0.)
		fprintf(stderr, "double add parallelism: %.2f\n", par);

	par = max_parallelism(double_mul_benchmarks, 
			      warmup, repetitions, &state);
	if (par > 0.)
		fprintf(stderr, "double mul parallelism: %.2f\n", par);

	par = max_parallelism(double_div_benchmarks, 
			      warmup, repetitions, &state);
	if (par > 0.)
		fprintf(stderr, "double div parallelism: %.2f\n", par);


	return(0);
}

E 2
I 1
E 1
