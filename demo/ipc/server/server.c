#include "eapp.h"
#include "print.h"

int EAPP_ENTRY main(){
  unsigned long* args;
  EAPP_RESERVE_REG;
  unsigned long IPC2_end;
  asm volatile("rdcycle %0" : "=r"(IPC2_end));
  eapp_print("[TEST] IPC 2 end %ld\n", IPC2_end);
  unsigned long arg0 = args[10];
  void* vaddr = (void*)args[11];
  unsigned long size = args[12];
  eapp_print("server begin to run\n");

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
  //ret_arg.req_vaddr = 0;
  ret_arg.req_size = size;
  eapp_print("server read req_vaddr:0x%lx\n", sum);

  int *nums = eapp_mmap(0, size);
  // size = 4*4096;
  sum = arg0;
  for(int i=0; i<size/sizeof(int); ++i)
  {
    nums[i] = 2;
    sum += nums[i];
  }
  ret_arg.resp_vaddr = nums;
  //ret_arg.resp_vaddr = 0;
  ret_arg.resp_size = size;
  eapp_print("server read resp_vaddr:0x%lx\n", sum);

  ret_arg.resp_val = 2;
  eapp_print("server is exiting with ret:0x%lx\n", ret_arg.resp_val);
  SERVER_RETURN(&ret_arg);
}
