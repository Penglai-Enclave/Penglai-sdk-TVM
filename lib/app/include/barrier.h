#ifndef __PENGLAI_BARRIER__
#define __PENGLAI_BARRIER__

#define RISCV_FENCE(p, s) \
	__asm__ __volatile__ ("fence " #p "," #s : : : "memory")

//These barriers do not enforce ordering on device, just order memory
#define mb()    RISCV_FENCE(rw,rw)
#define rmb()   RISCV_FENCE(r,r)
#define wmb()   RISCV_FENCE(w,w)

#define acquire_barrier() RISCV_FENCE(r, rw)
#define release_barrier() RISCV_FENCE(rw, w)
#endif