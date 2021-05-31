#include "eapp.h"
#include "print.h"

int hello(unsigned long * args)
{
  printf("hello world! %d\n", get_enclave_id());
  EAPP_RETURN(0);
}

int EAPP_ENTRY main(){
  unsigned long * args;
  EAPP_RESERVE_REG;
  hello(args);
}
