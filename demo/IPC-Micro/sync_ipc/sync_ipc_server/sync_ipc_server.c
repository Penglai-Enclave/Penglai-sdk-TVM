#include "eapp.h"
#include "log.h"

#define SUMINT 1
static inline unsigned long rdcycle(void)
{
	unsigned long ret;
  	asm volatile ("rdcycle %0" : "=r"(ret));
    return ret;
}
int EAPP_ENTRY main(){
    unsigned long * args;
    EAPP_RESERVE_REG;
    unsigned long cmd = args[10];
    struct call_enclave_arg_t ret_arg;
    ret_arg.req_vaddr = args[11];
    ret_arg.req_size = args[12];
    ret_arg.resp_vaddr = 0;
    ret_arg.resp_size = 0;
    switch(cmd){
        case SUMINT:
        {
            int* nums = (int*)(ret_arg.req_vaddr);
            unsigned long* middle_time = (unsigned long*)nums;
            // int sum = 0;
            // for(int i = 0; i < 10; i++){
            //     sum += nums[i];
            // }
            int sum = nums[0] + nums[1];

            ret_arg.resp_val = sum;
            middle_time[0] = rdcycle();
            // ret_arg.resp_val = nums[0] + nums[1];
            SERVER_RETURN(&ret_arg);
        }
        default:
        {
            LOG_ERROR("Some bug\n");
            ret_arg.resp_val = -1;
            SERVER_RETURN(&ret_arg);
        }
    }
}