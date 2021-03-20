H60785
s 00013/00013/00045
d D 1.6 02/09/29 21:53:51 staelin 7 6
c - switch from 'int' to 'size_t' for better portability to large memory 
c   machines
cC
cHfirewall.staelin.co.il
cK61676
e
s 00010/00001/00048
d D 1.5 01/04/09 16:45:50 staelin 6 5
c Add a number of new fields to mem_state to support some of the new
c capabilities added to lib_mem.c
cC
cK57154
cZ+03:00
e
s 00002/00002/00047
d D 1.4 01/04/02 14:51:23 staelin 5 4
c Fix buglets in MEM_BENCHMARK_DECL(N) macro and #endif in lib_mem.h
cC
cHhpli69.hpli.hpl.hp.com
cK40037
cZ+02:00
e
s 00002/00000/00047
d D 1.3 00/09/25 17:27:47 staelin 4 3
c - Add definition for par_mem
cC
cK39865
e
s 00002/00000/00045
d D 1.2 00/09/19 16:52:53 staelin 3 2
c - Migrate line_find and line_test from line.c to lib_mem.c
cC
cK31685
e
s 00045/00000/00000
d D 1.1 00/09/18 16:42:54 staelin 2 1
cC
cF1
cK17326
cO-rw-rw-r--
e
s 00000/00000/00000
d D 1.0 00/09/18 16:42:54 staelin 1 0
c BitKeeper file /tmp_mnt/usr/WebPaper/users/staelin/src/LMbench/src/lib_mem.h
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHhpli8.hpli.hpl.hp.com
cK08772
cPsrc/lib_mem.h
cR6f167d6111805b18
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
#ifndef LMBENCH_MEM_H
#define LMBENCH_MEM_H


#define MAX_MEM_PARALLELISM 16
#define MEM_BENCHMARK_DECL(N) \
D 5
	void mem_benchmark_##N##(iter_t iterations, void* cookie);
E 5
I 5
	void mem_benchmark_##N(iter_t iterations, void* cookie);
E 5

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

struct mem_state {
D 6
	char*	addr;
E 6
I 6
	char*	addr;	/* raw pointer returned by malloc */
	char*	base;	/* page-aligned pointer */
E 6
	char*	p[MAX_MEM_PARALLELISM];
I 6
	int	initialized;
E 6
	int	width;
D 7
	int	len;
I 4
	int	maxlen;
E 4
	int	line;
	int	pagesize;
I 6
	int	nlines;
	int	npages;
	int	nwords;
	int*	pages;
	int*	lines;
	int*	words;
E 7
I 7
	size_t	len;
	size_t	maxlen;
	size_t	line;
	size_t	pagesize;
	size_t	nlines;
	size_t	npages;
	size_t	nwords;
	size_t*	pages;
	size_t*	lines;
	size_t*	words;
E 7
E 6
};

void mem_initialize(void* cookie);
void line_initialize(void* cookie);
void tlb_initialize(void* cookie);
void mem_cleanup(void* cookie);
I 6
void tlb_cleanup(void* cookie);
E 6

REPEAT_15(MEM_BENCHMARK_DECL)
extern bench_f mem_benchmarks[];

I 3
D 7
int	line_find(int l, int warmup, int repetitions, struct mem_state* state);
double	line_test(int l, int warmup, int repetitions, struct mem_state* state);
I 4
double	par_mem(int l, int warmup, int repetitions, struct mem_state* state);
E 7
I 7
size_t	line_find(size_t l, int warmup, int repetitions, struct mem_state* state);
double	line_test(size_t l, int warmup, int repetitions, struct mem_state* state);
double	par_mem(size_t l, int warmup, int repetitions, struct mem_state* state);
E 7
E 4
E 3

D 5
#endif LMBENCH_MEM_H
E 5
I 5
#endif /* LMBENCH_MEM_H */
E 5

E 2
I 1
E 1
