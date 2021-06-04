#include "eapp.h"
#include "print.h"
#include <string.h>
#include <stdlib.h>

void printHex(unsigned int *c, int n)
{
	int i;
	for (i = 0; i < n; i++) {
    printf("0x%x\n", c[i]);
	}
}

int EAPP_ENTRY main(){
  unsigned long * args;
  EAPP_RESERVE_REG;

  eapp_print("caller begin to run...\n");

  int run_server1 = 1;
  char server_name[16];
  strcpy(server_name, "test-server1");

  unsigned long server_handle = acquire_enclave(server_name);
  if(server_handle == -1UL)
  {
    strcpy(server_name, "test-server");
    server_handle = acquire_enclave(server_name);
    run_server1 = 0;
  }

  // Get the server enclave report
  struct report_t *report = malloc(sizeof(struct report_t));
  get_report("test-server1", report, 1);
  printHex((unsigned int*)(report->enclave.signature), 16);


  if(server_handle == -1UL)
  {
    EAPP_RETURN(-1UL);
  }

  unsigned long arg0 = 0x19960000UL;
  unsigned long size = 4*4096;
  int *nums = eapp_mmap(NULL, size);
  // int *nums = malloc(size);
  for(int i=0; i<size/sizeof(int); ++i)
  {
    nums[i] = 1;
  }

  struct call_enclave_arg_t call_arg;
  call_arg.req_arg = arg0;
  call_arg.req_vaddr = (unsigned long)nums;
  call_arg.req_size = size;
  call_enclave(server_handle, &call_arg);

  if(call_arg.req_vaddr)
  {
    unsigned long sum = 0;
    //nums = (int*)call_arg.req_vaddr;
    for(int i=0; i<size/sizeof(int); ++i)
    {
      sum += nums[i];
    }
    eapp_print("caller: read req_vaddr after calling server:0x%lx\n", sum);
  }

  if(call_arg.resp_vaddr)
  {
    unsigned long sum = 0;
    nums = (int*)call_arg.resp_vaddr;
    for(int i=0; i<call_arg.resp_size/sizeof(int); ++i)
    {
      sum += nums[i];
    }
    eapp_print("caller: read resp_vaddr after calling server:0x%lx\n", sum);
  }

  if(run_server1)
    eapp_print("caller: get server1 retval:0x%lx\n", call_arg.resp_val);
  else
    eapp_print("caller: get server retval:0x%lx\n", call_arg.resp_val);
  EAPP_RETURN(0);
}
