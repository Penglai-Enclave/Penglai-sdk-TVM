#include "eapp.h"
#include "print.h"
#include <string.h>
#include "log.h"
static inline unsigned long rdcycle(void)
{
	unsigned long ret;
  	asm volatile ("rdcycle %0" : "=r"(ret));
    return ret;
}
#define SUMINT (1)
#define ITERATION (10000)

unsigned long begin_time[ITERATION];
unsigned long end_time[ITERATION];
unsigned long middle_time[ITERATION];

int EAPP_ENTRY main(){
    unsigned long * args;
    EAPP_RESERVE_REG;
    LOG_INFO("sync client begin to run\n");
    char server_name[16];
    strcpy(server_name,"test-server");
    unsigned long server_handle = acquire_enclave(server_name);
    if(server_handle == -1UL){
        LOG_INFO("get server handle failed\n");
        EAPP_RETURN(-1UL);
    }
    unsigned long mem_sz[] = {4096, 4096*4, 4096*16, 4096*64, 4096*256};
    int* mems[sizeof(mem_sz)/sizeof(unsigned long)];
    for(int i = 0; i < sizeof(mem_sz)/sizeof(unsigned long);++i){
        mems[i] = (int*)eapp_mmap(NULL, mem_sz[i]);
        if(mems[i] == NULL){
            LOG_ERROR("allocate secure memory failed\n");
            for(int j = 0; j < i;++j){
                eapp_unmap(mems[j], mem_sz[j]);
            }
            EAPP_RETURN(-1);
        }
    }
    struct call_enclave_arg_t call_arg;
    for(int i = 0; i < sizeof(mem_sz)/sizeof(unsigned long); ++i){
        int initial = 1;
        int j = 0;
        unsigned long* tmp_mid = (unsigned long*)mems[i];
        while(j < ITERATION){
            call_arg.req_arg = SUMINT;
            call_arg.req_vaddr = mems[i];
            call_arg.req_size = mem_sz[i];
            int tmp = initial;
            mems[i][0] = initial++;
            mems[i][1] = initial++;
            begin_time[j] = rdcycle();
            call_enclave(server_handle, &call_arg);
            end_time[j] = rdcycle();
            if(call_arg.resp_val != (tmp + tmp+1)){
                LOG_ERROR("Some Error\n");
            }
            middle_time[j] = tmp_mid[0];
            j++;
        }
        unsigned long ave_response_time = 0;
        unsigned long ave_e2e_time = 0;
        for(j = 0; j < ITERATION;j++){
            ave_response_time += (middle_time[j] - begin_time[j]);
            ave_e2e_time += (end_time[j] - begin_time[j]);
        }
        LOG_INFO("message size: %ld, response_time: %ld, end_to_end_time: %ld\n", mem_sz[i], ave_response_time/ITERATION, ave_e2e_time/ITERATION);
    }
    for(int i = 0; i < sizeof(mem_sz)/sizeof(unsigned long); ++i){
        eapp_unmap(mems[i], mem_sz[i]);
    }
    EAPP_RETURN(0);
}