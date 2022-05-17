#include "eapp.h"
#include "print.h"
#include <stdlib.h>
#include <string.h>

#define SHM_SIZE 1024*1024*2

#ifdef __ASSEMBLY__
#define __ASM_STR(x)	x
#else
#define __ASM_STR(x)	#x
#endif

#define csr_read(csr)                                           \
	({                                                      \
		register unsigned long __v;                     \
		__asm__ __volatile__("csrr %0, " __ASM_STR(csr) \
				     : "=r"(__v)                \
				     :                          \
				     : "memory");               \
		__v;                                            \
	})

#define csr_write(csr, val)                                        \
	({                                                         \
		unsigned long __v = (unsigned long)(val);          \
		__asm__ __volatile__("csrw " __ASM_STR(csr) ", %0" \
				     :                             \
				     : "rK"(__v)                   \
				     : "memory");                  \
	})


int hello(unsigned long * args)
{
  long *shm = args[10];
  long value = 0;
  for(int i=0; i<(0x1000/8); i++) {
    value += shm[i];
  }

  eapp_print("enclave: enable cache side channel detection\n");
  csr_write(0x7B4, 2);

  for (int j=0; j<10; j++) {
    for(int i=0; i<(SHM_SIZE/8); i++) {
      value += shm[i];
    }
  }
  
  csr_write(0x7B4, 0);

  eapp_print("enclave: value %ld\n", value);

  EAPP_RETURN(0);
}

int EAPP_ENTRY main(){
  unsigned long * args;
  EAPP_RESERVE_REG;
  hello(args);
}
