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
	int	K;
	double*	data;
};

#define TEN(a) a a a a a a a a a a
#define HUNDRED(a) TEN(TEN(a))

void
do_integer_bitwise(iter_t iterations, void* cookie)
{
	struct _state *pState = (struct _state*)cookie;
	register int r = pState->N;
	register int s = (int)iterations;

	while (iterations-- > 0) {
		HUNDRED(r^=iterations;s^=r;r|=s;)
	}
	use_int(r);
}

void
do_integer_add(iter_t iterations, void* cookie)
{
	struct _state *pState = (struct _state*)cookie;
	register int a = pState->N;
	register int b = pState->N;

	while (iterations-- > 0) {
		HUNDRED(a+=b;b-=a;)
	}
	use_int(a+b);
}

void
do_integer_mul(iter_t iterations, void* cookie)
{
	struct _state *pState = (struct _state*)cookie;
	register int r = pState->N;
	register int s = (pState->N + 1) ^ r;

	while (iterations-- > 0) {
		TEN(TEN(r=r*s;)r^=s;)
	}
	use_int(r);
}

void
do_integer_div(iter_t iterations, void* cookie)
{
	struct _state *pState = (struct _state*)cookie;
	register int r = pState->N + 1;
	register int s = (r + 1) << 20;

	while (iterations-- > 0) {
		HUNDRED(r=s/r;)
	}
	use_int(r);
}

void
do_integer_mod(iter_t iterations, void* cookie)
{
	struct _state *pState = (struct _state*)cookie;
	register int r = pState->N;
	register int s = pState->N + iterations;

	while (iterations-- > 0) {
		HUNDRED(r=r%s;r|=s;)
	}
	use_int(r);
}

void
do_int64_bitwise(iter_t iterations, void* cookie)
{
	struct _state *pState = (struct _state*)cookie;
	register int64 r = pState->N;
	register int64 s = (int64)iterations;
	register int64 i = (int64)iterations;

	while (iterations-- > 0) {
		HUNDRED(r^=i;s^=r;r|=s;)
		i--;
	}
	use_int((int)r);
}

void
do_int64_add(iter_t iterations, void* cookie)
{
	struct _state *pState = (struct _state*)cookie;
	register int64 a = pState->N;
	register int64 b = pState->N;

	while (iterations-- > 0) {
		HUNDRED(a+=b;b-=a;)
	}
	use_int((int)a+(int)b);
}

void
do_int64_mul(iter_t iterations, void* cookie)
{
	struct _state *pState = (struct _state*)cookie;
	register int64 r = pState->N;
	register int64 s = (pState->N + 1) ^ r;

	while (iterations-- > 0) {
		TEN(TEN(r=r*s;)r^=s;)
	}
	use_int((int)r);
}

void
do_int64_div(iter_t iterations, void* cookie)
{
	struct _state *pState = (struct _state*)cookie;
	register int64 r = pState->N;
	register int64 s = (r + 1) << 20;

	while (iterations-- > 0) {
		HUNDRED(r=s/r;)
	}
	use_int((int)r);
}

void
do_int64_mod(iter_t iterations, void* cookie)
{
	struct _state *pState = (struct _state*)cookie;
	register int64 r = pState->N;
	register int64 s = pState->N + iterations;

	while (iterations-- > 0) {
		HUNDRED(r=r%s;r|=s;)
	}
	use_int((int)r);
}

void
do_float_add(iter_t iterations, void* cookie)
{
	struct _state *pState = (struct _state*)cookie;
	register float f = (float)pState->N;
	register float g = (float)pState->K;

	while (iterations-- > 0) {
		TEN(f+=f;)
		f+=g;
	}
	use_int((int)f);
	use_int((int)g);
}

void
do_float_mul(iter_t iterations, void* cookie)
{
	struct _state *pState = (struct _state*)cookie;
	register float f = (float)pState->N;
	register float g = (float)pState->M;

	while (iterations-- > 0) {
#ifndef __GNUC__
		HUNDRED(f*=f;)
#else
		/* required because of GCC bug */
		TEN(f*=f;)
#endif
	}
	use_int((int)f);
	use_int((int)g);
}

void
do_float_div(iter_t iterations, void* cookie)
{
	struct _state *pState = (struct _state*)cookie;
	register float f = (float)pState->N;
	register float g = (float)pState->M;

	while (iterations-- > 0) {
#ifndef __GNUC__
		HUNDRED(f=g/f;)
#else
		/* required because of GCC bug */
		TEN(f=g/f;)
#endif
	}
	use_int((int)f);
	use_int((int)g);
}

void
do_double_add(iter_t iterations, void* cookie)
{
	struct _state *pState = (struct _state*)cookie;
	register double f = (double)pState->N;
	register double g = (double)pState->K;

	while (iterations-- > 0) {
		TEN(f+=f;)
		f+=g;
	}
	use_int((int)f);
	use_int((int)g);
}

void
do_double_mul(iter_t iterations, void* cookie)
{
	struct _state *pState = (struct _state*)cookie;
	register double f = (double)pState->N;
	register double g = (double)pState->M;

	while (iterations-- > 0) {
#ifndef __GNUC__
		HUNDRED(f*=f;)
#else
		/* required because of GCC bug */
		TEN(f*=f;)
#endif
	}
	use_int((int)f);
	use_int((int)g);
}

void
do_double_div(iter_t iterations, void* cookie)
{
	struct _state *pState = (struct _state*)cookie;
	register double f = (double)pState->N;
	register double g = (double)pState->M;

	while (iterations-- > 0) {
#ifndef __GNUC__
		HUNDRED(f=g/f;)
#else
		/* required because of GCC bug */
		TEN(f=g/f;)
#endif
	}
	use_int((int)f);
	use_int((int)g);
}

void
float_initialize(void* cookie)
{
	struct _state *pState = (struct _state*)cookie;
	register int i;
	float* x = (float*)malloc(pState->M * sizeof(float));;

	pState->data = (double*)x;
	for (i = 0; i < pState->M; ++i) {
		x[i] = 1.;
	}
}

void
double_initialize(void* cookie)
{
	struct _state *pState = (struct _state*)cookie;
	register int i;

	pState->data = (double*)malloc(pState->M * sizeof(double));
	for (i = 0; i < pState->M; ++i) {
		pState->data[i] = 1.;
	}
}

void
cleanup(void* cookie)
{
	struct _state *pState = (struct _state*)cookie;

	if (pState->data) 
		free(pState->data);
}

void
do_float_bogomflops(iter_t iterations, void* cookie)
{
	struct _state *pState = (struct _state*)cookie;
	register int i;
	register float *x = (float*)pState->data;

	while (iterations-- > 0) {
		for (i = 0; i < pState->M; ++i) {
			x[i] = (1.0 + x[i]) * (1.5 - x[i]) / x[i];
		}
	}
}

void
do_double_bogomflops(iter_t iterations, void* cookie)
{
	struct _state *pState = (struct _state*)cookie;
	register int i;
	register double *x = (double*)pState->data;

	while (iterations-- > 0) {
		for (i = 0; i < pState->M; ++i) {
			x[i] = (1.0 + x[i]) * (1.5 - x[i]) / x[i];
		}
	}
}

int
main(int ac, char **av)
{
	int	__n = 1;
	int	c, i, j;
	int	warmup = 0;
	int	parallel = 1;
	int	repetitions = TRIES;
	uint64	iop_time;
	uint64	iop_N;
	struct _state state;
	char   *usage = "[-W <warmup>] [-N <repetitions>]\n";

	state.N = 1;
	state.M = 1000;
	state.K = -1023;
	state.data = NULL;

	while (( c = getopt(ac, av, "W:N:P:")) != EOF) {
		switch(c) {
		case 'W':
			warmup = atoi(optarg);
			break;
		case 'N':
			repetitions = atoi(optarg);
			break;
		case 'P':
			parallel = atoi(optarg);
			if (parallel <= 0) lmbench_usage(ac, av, usage);
			break;
		default:
			lmbench_usage(ac, av, usage);
			break;
		}
	}

	BENCH((*do_integer_bitwise)(__n, &state); __n = 1;, 0);
	nano("integer bit", get_n() * 100 * 3);
	iop_time = gettime();
	iop_N = get_n() * 100 * 3;
	
	BENCH((*do_integer_add)(__n, &state); __n = 1;, 0);
	nano("integer add", get_n() * 100 * 2);
	
	BENCH((*do_integer_mul)(__n, &state); __n = 1;, 0);
	settime(gettime() - (get_n() * 10 * iop_time) / iop_N);
	nano("integer mul", get_n() * 100);
	
	BENCH((*do_integer_div)(__n, &state); __n = 1;, 0);
	nano("integer div", get_n() * 100);
	
	BENCH((*do_integer_mod)(__n, &state); __n = 1;, 0);
	settime(gettime() - (get_n() *  100 * iop_time) / iop_N);
	nano("integer mod", get_n() * 100);
	
	BENCH((*do_int64_bitwise)(__n, &state); __n = 1;, 0);
	nano("int64 bit", get_n() * 100 * 3);
	iop_time = gettime();
	iop_N = get_n() * 100 * 3;

	BENCH((*do_int64_add)(__n, &state); __n = 1;, 0);
	nano("int64 add", get_n() * 100 * 2);
	
	BENCH((*do_int64_mul)(__n, &state); __n = 1;, 0);
	settime(gettime() - (get_n() * 10 * iop_time) / iop_N);
	nano("int64 mul", get_n() * 100);
	
	BENCH((*do_int64_div)(__n, &state); __n = 1;, 0);
	nano("int64 div", get_n() * 100);
	
	BENCH((*do_int64_mod)(__n, &state); __n = 1;, 0);
	settime(gettime() - (get_n() * 100 * iop_time) / iop_N);
	nano("int64 mod", get_n() * 100);
	
	BENCH((*do_float_add)(__n, &state); __n = 1;, 0);
	nano("float add", get_n() * 11);
	
	BENCH((*do_float_mul)(__n, &state); __n = 1;, 0);
#ifndef __GNUC__
	nano("float mul", get_n() * 100);
#else
	nano("float mul", get_n() * 10);
#endif
	
	BENCH((*do_float_div)(__n, &state); __n = 1;, 0);
#ifndef __GNUC__
	nano("float div", get_n() * 100);
#else
	nano("float div", get_n() * 10);
#endif

	BENCH((*do_double_add)(__n, &state); __n = 1;, 0);
	nano("double add", get_n() * 11);
	
	BENCH((*do_double_mul)(__n, &state); __n = 1;, 0);
#ifndef __GNUC__
	nano("double mul", get_n() * 100);
#else
	nano("double mul", get_n() * 10);
#endif
	
	BENCH((*do_double_div)(__n, &state); __n = 1;, 0);
#ifndef __GNUC__
	nano("double div", get_n() * 100);
#else
	nano("double div", get_n() * 10);
#endif

	benchmp(float_initialize, 
		do_float_bogomflops, cleanup, 0, parallel, warmup, repetitions, &state);
	nano("float bogomflops", get_n() * state.M);

	benchmp(double_initialize, 
		do_double_bogomflops, cleanup, 0, parallel, warmup, repetitions, &state);
	nano("double bogomflops", get_n() * state.M);

	return(0);
}

