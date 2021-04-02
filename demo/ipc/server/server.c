#include "eapp.h"
#include "print.h"

int EAPP_ENTRY main(){
  unsigned long* args;
  EAPP_RESERVE_REG;
  unsigned long IPC2_end;
  asm volatile("rdcycle %0" : "=r"(IPC2_end));
  unsigned long arg0 = args[10];
  void* vaddr = (void*)args[11];
  unsigned long size = args[12];
  eapp_print("[TEST] enclave-enclave IPC cost %ld cycles for 0x%lx bytes.\n", IPC2_end - arg0, size);

  struct call_enclave_arg_t ret_arg;
  unsigned long sum = arg0;
  if(vaddr)
  {
    int* nums = (int*)vaddr;
    for(int i=0; i<size/sizeof(int); ++i)
    {
      sum += nums[i];
    }
  }
  ret_arg.req_vaddr = vaddr;
  ret_arg.req_size = size;

  int *nums = eapp_mmap(0, size);
  sum = arg0;
  for(int i=0; i<size/sizeof(int); ++i)
  {
    nums[i] = 2;
    sum += nums[i];
  }
  ret_arg.resp_vaddr = nums;
  ret_arg.resp_size = size;
  
  ret_arg.resp_val = 2;
  SERVER_RETURN(&ret_arg);
}
