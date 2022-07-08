#include "eapp.h"
#include "print.h"
#include <stdlib.h>
#include <string.h>

int hello(unsigned long * args)
{
  eapp_print("begin loop\n");
  while (1) {}
  EAPP_RETURN(0);
}

int EAPP_ENTRY main(){
  unsigned long * args;
  EAPP_RESERVE_REG;
  hello(args);
}
