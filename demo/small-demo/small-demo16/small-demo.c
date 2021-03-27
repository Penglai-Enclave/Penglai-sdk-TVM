#include "eapp.h"
#include "print.h"

const char data[16*1024*1024] = {1,};

int hello(unsigned long * args)
{
  //eapp_print("hello world!\n");
}

int EAPP_ENTRY main(){
  unsigned long * args;
  EAPP_RESERVE_REG;

  unsigned long boot_end;
  asm volatile("rdcycle %0" : "=r"(boot_end));

  hello(args);

  EAPP_RETURN(boot_end);
}
