#include "eapp.h"
#include "print.h"
#include <string.h>

int EAPP_ENTRY main(){
  unsigned long * args;
  EAPP_RESERVE_REG;

  //test mm_arg
  void* mm_arg = args[13];
  void* mm_arg_size = args[14];
  unsigned long read_num = *(unsigned long*)mm_arg;

  //calculate host-enclave ipc cost
  unsigned long IPC0_end;
  asm volatile("rdcycle %0" : "=r"(IPC0_end));

  int run_server1 = 1;
  char server_name[16];

  strcpy(server_name, "test-server");
  unsigned long server_handle = acquire_enclave(server_name);
  if(server_handle == -1UL)
  {
    EAPP_RETURN(-1UL);
  }

  unsigned long size = mm_arg_size;
  int *nums = eapp_mmap(NULL, size);

  struct call_enclave_arg_t call_arg;
  call_arg.req_arg = 0;
  call_arg.req_vaddr = nums;
  call_arg.req_size = size;

  unsigned long IPC1_start;
  asm volatile("rdcycle %0" : "=r"(IPC1_start));
  call_arg.req_arg = IPC1_start;
  call_enclave(server_handle, &call_arg);
  
  if(call_arg.resp_vaddr)
  {
    unsigned long sum = 0;
    nums = (int*)call_arg.resp_vaddr;
    for(int i=0; i<call_arg.resp_size/sizeof(int); ++i)
    {
      sum += nums[i];
    }
  }

  EAPP_RETURN(IPC0_end);
}
