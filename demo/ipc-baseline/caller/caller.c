#include "eapp.h"
#include "print.h"
#include <string.h>

#define ENCLAVE_DEFAULT_SHM_BASE 0x0000003900000000UL;

int EAPP_ENTRY main(){
  unsigned long * args;
  EAPP_RESERVE_REG;

  //copy shm
  void* shm_addr = args[10];
  unsigned long shm_size = args[11];
  void* dest_addr = eapp_mmap(0, shm_size);
  for(int i=0; i < shm_size/sizeof(int); ++i)
  {
    *(int*)dest_addr = *(int*)shm_addr;
    dest_addr += sizeof(int);
    shm_addr += sizeof(int);
  }

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

  unsigned long arg0 = 0x19960000UL;
  unsigned long size = 64*1024*1024;
  int *nums = eapp_mmap(NULL, size);
  for(int i=0; i<size/sizeof(int); ++i)
  {
    nums[i] = 1;
  }

  struct call_enclave_arg_t call_arg;
  call_arg.req_arg = arg0;
  call_arg.req_vaddr = nums;
  call_arg.req_size = size;

  unsigned long IPC1_start;
  asm volatile("rdcycle %0" : "=r"(IPC1_start));
  call_arg.req_arg = IPC1_start;
  call_enclave(server_handle, &call_arg);
  
  if(call_arg.req_vaddr)
  {
    unsigned long sum = 0;
    for(int i=0; i<size/sizeof(int); ++i)
    {
      sum += nums[i];
    }
  }

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
