#include "eapp.h"
#include "print.h"

int EAPP_ENTRY main(){
  unsigned long* args;
  EAPP_RESERVE_REG;
  unsigned long IPC1_end;
  asm volatile("rdcycle %0" : "=r"(IPC1_end));
  eapp_print("[TEST] IPC 1 end. Current cycle:%ld.\n", IPC1_end);
  unsigned long arg0 = args[10];
  void* vaddr = (void*)args[11];
  unsigned long size = args[12];
  eapp_print("server-enclave1 begin to run\n");

  unsigned long sum = arg0;
  if(vaddr)
  {
    int* nums = (int*)vaddr;
    for(int i=0; i<size/sizeof(int); ++i)
    {
      sum += nums[i];
      nums[i] += 1;
    }
  }

  char server_name[16];
  strcpy(server_name, "test-server");
  unsigned long server_handle = acquire_enclave(server_name);
  struct call_enclave_arg_t call_arg;
  //commented by luxu
  //eapp_print("server_handle:0x%lx\n", server_handle);
  if(server_handle == -1UL)
  {
    call_arg.resp_val = -1;
    call_arg.req_vaddr = 0;
    call_arg.resp_vaddr = 0;
    SERVER_RETURN(&call_arg);
  }

  call_arg.req_arg = arg0;
  call_arg.req_vaddr = vaddr;
  call_arg.req_size = size;

  unsigned long IPC2_start;
  asm volatile("rdcycle %0" : "=r"(IPC2_start));
  eapp_print("[TEST] IPC 2 start. Current cycle: %ld.\n", IPC2_start);
  call_enclave(server_handle, &call_arg);

  //commented by luxu
  //eapp_print("server1: read req_vaddr:0x%lx\n", sum);

  if(call_arg.resp_vaddr)
  {
    int *nums = (int*)call_arg.resp_vaddr;
    size = call_arg.resp_size;
    sum = arg0;
    for(int i=0; i<size/sizeof(int); ++i)
    {
      sum += nums[i];
    }
    //commented by luxu
    //eapp_print("server1: read resp_vaddr:0x%lx\n", sum);
  }

  call_arg.resp_val = 3;
  //commented by luxu
  //eapp_print("server1 is exiting with retval:0x%lx\n", 3);
  SERVER_RETURN(&call_arg);
}