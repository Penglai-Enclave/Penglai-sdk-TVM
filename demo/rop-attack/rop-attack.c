#include "eapp.h"
#include "print.h"
#include <stdlib.h>

int buffer_overflow()
{
  long buf[1];
  long attack_address = 0;
  memcpy(buf+2, &attack_address, 8);
  nest_call();
  return 0; 
}

int nest_call()
{
    printf("nest call\n");
    return 0;
}


int hello(unsigned long * args)
{
  printf("hello world!\n");
  buffer_overflow();
  EAPP_RETURN(0);
}

int EAPP_ENTRY main(){
  unsigned long * args;
  EAPP_RESERVE_REG;
  hello(args);
}
