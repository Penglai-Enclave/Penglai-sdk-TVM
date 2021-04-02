#include "eapp.h"
#include "print.h"

#define ENCLAVE_DEFAULT_SHM_BASE 0x0000003900000000UL;

int EAPP_ENTRY main(){
  unsigned long* args;
  EAPP_RESERVE_REG;

  //copy shm
  //void* shm_addr = ENCLAVE_DEFAULT_SHM_BASE;
  //unsigned long shm_size = *(unsigned long*)shm_addr;
  //eapp_print("caller: shm_addr: 0x%lx, shm_size: 0x%lx read num:0x%lx\n", shm_addr, args[14], shm_size);
  void* shm_addr = args[13];
  unsigned long shm_size = args[14];
  void* dest_addr = eapp_mmap(0, shm_size);
  //memcpy(dest_addr, shm_addr, shm_size);
  for(int i=0; i < shm_size/sizeof(int); ++i)
  {
    *(int*)dest_addr = *(int*)shm_addr;
    dest_addr += sizeof(int);
    shm_addr += sizeof(int);
  }

  unsigned long IPC2_end;
  asm volatile("rdcycle %0" : "=r"(IPC2_end));
  unsigned long arg0 = args[10];
  void* vaddr = (void*)args[11];
  unsigned long size = args[12];
  //eapp_print("server-enclave begin to run\n");
  eapp_print("[TEST-BASELINE] enclave-enclave IPC cost %ld cycles for 0x%lx bytes.\n", IPC2_end - arg0, shm_size);

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
  //commented by luxu
  //eapp_print("server read req_vaddr:0x%lx\n", sum);

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
  
  //commented by luxu
  //eapp_print("server read resp_vaddr:0x%lx\n", sum);

  ret_arg.resp_val = 2;
  //commented by luxu
  //eapp_print("server is exiting with ret:0x%lx\n", ret_arg.resp_val);
  SERVER_RETURN(&ret_arg);
}