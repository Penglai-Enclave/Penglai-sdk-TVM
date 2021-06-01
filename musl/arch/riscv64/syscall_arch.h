#ifndef _SYSCALL_ARCH
#define _SYSCALL_ARCH
#define __SYSCALL_LL_E(x) (x)
#define __SYSCALL_LL_O(x) (x)
#define UNTRUSTED_MEM_PTR 0x0000001000000000
#define SYS_eret             1 //ret to host
#define SYS_ocall            2 //OCALL
#define SYS_acquire_enclave  3
#define SYS_call_enclave     4
#define SYS_enclave_return   5
#define SYS_asyn_ecnlave_call 6
#define SYS_split_mem_region 7
#define SYS_get_caller_id    8
#define SYS_get_enclave_id   9
#define SYS_yield            10 //reserve space for other operation

#define SBI_EXT_PENGLAI_ENCLAVE	    0x100101 //penglai extension id

#define OCALL_MMAP          1 
#define OCALL_UNMAP         2
#define OCALL_SYS_WRITE     3
#define OCALL_SBRK          4

#define __asm_syscall(...) \
	__asm__ __volatile__ ("ecall\n\t" \
	: "=r"(a0) : __VA_ARGS__ : "memory"); \
	return a0; \

unsigned long musl_brk;

static inline long __syscall0(long n)
{
	register long a7 __asm__("a7") = n;
	register long a6 __asm__("a6") = SBI_EXT_PENGLAI_ENCLAVE;
	register long a0 __asm__("a0");
	__asm_syscall("r"(a7), "r"(a6))
}

static inline long __syscall1(long n, long a)
{
	register long a7 __asm__("a7") = n;
	register long a6 __asm__("a6") = SBI_EXT_PENGLAI_ENCLAVE;
	register long a0 __asm__("a0") = a;
	register long a1 __asm__("a1") = 0;
	switch(n)
 	{
		case SYS_brk:
		{
			if(a0 == 0)
			{
				a7 = SYS_ocall;
				a1 = a0;
				a0 = OCALL_SBRK;
				__asm__ __volatile__ ("ecall\n\t" : "=r"(a0) : "r"(a7), "r"(a6), "0"(a0), "r"(a1) : "memory"); 
				musl_brk = a0;
				return a0;
			}
			else
			{
				unsigned long offset;
				a7 = SYS_ocall;
				a1 = (a0 - musl_brk);
				a0 = OCALL_SBRK;
				__asm__ __volatile__ ("ecall\n\t" : "=r"(a0) : "r"(a7), "r"(a6), "0"(a0), "r"(a1) : "memory"); 
				musl_brk = a0;
				return a0;
			}
			
		}
	}
	__asm_syscall("r"(a7), "r"(a6), "0"(a0))
}

static inline long __syscall2(long n, long a, long b)
{
	register long a7 __asm__("a7") = n;
	register long a6 __asm__("a6") = SBI_EXT_PENGLAI_ENCLAVE;
	register long a0 __asm__("a0") = a;
	register long a1 __asm__("a1") = b;
	register long a2 __asm__("a2") = 0;
	switch(n)
	{
		case SYS_munmap:
		{
			a7 = SYS_ocall;
			a2 = a1;
			a1 = a0;
			a0 = OCALL_UNMAP;
			__asm_syscall("r"(a7), "r"(a6), "0"(a0), "r"(a1), "r"(a2))
		}
	}
	__asm_syscall("r"(a7), "r"(a6), "0"(a0), "r"(a1))
}

static inline long __syscall3(long n, long a, long b, long c)
{
	register long a7 __asm__("a7") = n;
	register long a6 __asm__("a6") = SBI_EXT_PENGLAI_ENCLAVE;
	register long a0 __asm__("a0") = a;
	register long a1 __asm__("a1") = b;
	register long a2 __asm__("a2") = c;
	__asm_syscall("r"(a7), "r"(a6), "0"(a0), "r"(a1), "r"(a2))
}

static inline long __syscall4(long n, long a, long b, long c, long d)
{
	register long a7 __asm__("a7") = n;
	register long a6 __asm__("a6") = SBI_EXT_PENGLAI_ENCLAVE;
	register long a0 __asm__("a0") = a;
	register long a1 __asm__("a1") = b;
	register long a2 __asm__("a2") = c;
	register long a3 __asm__("a3") = d;
	__asm_syscall("r"(a7), "r"(a6), "0"(a0), "r"(a1), "r"(a2), "r"(a3))
}

static inline long __syscall5(long n, long a, long b, long c, long d, long e)
{
	register long a7 __asm__("a7") = n;
	register long a6 __asm__("a6") = SBI_EXT_PENGLAI_ENCLAVE;
	register long a0 __asm__("a0") = a;
	register long a1 __asm__("a1") = b;
	register long a2 __asm__("a2") = c;
	register long a3 __asm__("a3") = d;
	register long a4 __asm__("a4") = e;
	__asm_syscall("r"(a7), "r"(a6), "0"(a0), "r"(a1), "r"(a2), "r"(a3), "r"(a4))
}

static inline long __syscall6(long n, long a, long b, long c, long d, long e, long f)
{
	register long a7 __asm__("a7") = n;
	register long a6 __asm__("a6") = SBI_EXT_PENGLAI_ENCLAVE;
	register long a0 __asm__("a0") = a;
	register long a1 __asm__("a1") = b;
	register long a2 __asm__("a2") = c;
	register long a3 __asm__("a3") = d;
	register long a4 __asm__("a4") = e;
	register long a5 __asm__("a5") = f;
	switch(n)
	{
		case SYS_mmap:
			a7 = SYS_ocall;
			a2 = a1;
			a1 = a0;
			a0 = OCALL_MMAP;
			break;
	}
	__asm_syscall("r"(a7), "r"(a6), "0"(a0), "r"(a1), "r"(a2), "r"(a3), "r"(a4), "r"(a5))
}

#define VDSO_USEFUL
/* We don't have a clock_gettime function.
#define VDSO_CGT_SYM "__vdso_clock_gettime"
#define VDSO_CGT_VER "LINUX_2.6" */

#define IPC_64 0
#endif
