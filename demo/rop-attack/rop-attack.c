#include "eapp.h"
#include "print.h"
#include <stdlib.h>
#include <string.h>

int buffer_overflow()
{
  long buf[1];
  long attack_address = 0x1150;
  eapp_print("return address %lx\n", *(long *)(buf+2));
  memcpy(buf+2, &attack_address, 8);
  nest_call();
  return 0; 
}

int nest_call()
{
    eapp_print("nest call\n");
    return 0;
}

int attack_code()
{
  // while(1) {}
  eapp_print("goto the attacker's code\n");
  EAPP_RETURN(0);
}


int hello(unsigned long * args)
{
  eapp_print("hello world!\n");
  buffer_overflow();
  EAPP_RETURN(0);
}

int EAPP_ENTRY main(){
  unsigned long * args;
  EAPP_RESERVE_REG;
  hello(args);
}
