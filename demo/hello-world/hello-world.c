#include "eapp.h"
#include "print.h"

int hello(unsigned long * args)
{
  unsigned long i = args[12];
  eapp_print("hello world! %ld\n", i);
  EAPP_RETURN(0);
}

int EAPP_ENTRY main(){
  unsigned long * args;
  EAPP_RESERVE_REG;
  hello(args);
}
