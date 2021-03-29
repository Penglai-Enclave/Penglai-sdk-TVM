#include "eapp.h"
#include "print.h"

int sleep_demo(unsigned long * args)
{
  int count = 0;
  EAPP_YIELD();
  EAPP_RETURN(count);
}

int EAPP_ENTRY main(){
  unsigned long * args;
  EAPP_RESERVE_REG;
  sleep_demo(args);
}
