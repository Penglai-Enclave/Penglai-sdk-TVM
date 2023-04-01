#include <stdlib.h>
#include <string.h>
#define LOG_LEVEL INFO
#include "eapp.h"
#include "async_ipc_lib.h"
#include "print.h"
#include "argument.h"
#include "log.h"
#define SUMINT (1)
#define PRODUCTINT (2)
#define END (3)
#define START (4)
#define ITERATION (10000)


unsigned long start_time[ITERATION];
unsigned long middle_time[ITERATION];
unsigned long end_time[ITERATION];

static inline unsigned long rdcycle(void)
{
	unsigned long ret;
  	asm volatile ("rdcycle %0" : "=r"(ret));
    return ret;
}

void test_func(int cmd, void* mem, unsigned long mem_sz)
{
    int iteration = 0;
    int initial = 1;
    int *result = NULL;
    int ret;
    unsigned int result_sz;
    struct argument* arg = async_client_get_request_mem(mem);
    async_submit_request(mem, START);
    ret = async_client_polling_ret(mem, &result, &result_sz);
    int* data = (char*)arg + sizeof(struct argument);
    while(iteration < ITERATION){
        int tmp = initial;
        data[0] = initial++;
        data[1] = initial++;
        start_time[iteration] = rdcycle();
        async_submit_request(mem, SUMINT);
        middle_time[iteration] = rdcycle();
        ret = async_client_polling_ret(mem, &result, &result_sz);
        end_time[iteration] = rdcycle();
        if(*result != tmp + tmp + 1 || ret != 0){
            LOG_ERROR("Some Error\n");
        }
        iteration++;
    }
    unsigned long ave_response_time = 0;
    unsigned long ave_e2e_time = 0;
    for(int i = 0; i < iteration;++i){
        ave_response_time += (middle_time[i] - start_time[i]);
        ave_e2e_time += (end_time[i] - start_time[i]);
    }
    LOG_INFO("message size: %ld, response_time: %ld, end_to_end_time: %ld\n", mem_sz, ave_response_time/ITERATION, ave_e2e_time/ITERATION);
}


int EAPP_ENTRY main()
{
    unsigned long *args;
    EAPP_RESERVE_REG;
    LOG_INFO("async_ipc_client initializing\n");
    char* mem;
    unsigned int key;
    int ret;
    //4K, 16K, 64K,256K, 1M
    unsigned long mem_sizes[] = {4096, 4096*4, 4096*16, 4096*64, 4096*256};
    int test_sz = sizeof(mem_sizes)/sizeof(unsigned long);
    for(int i = 0; i < test_sz; ++i){
        mem = connect_to_server("test_server", mem_sizes[i], &key);
        test_func(SUMINT,mem, mem_sizes[i]);
        struct shm_dsc dsc;
        ret = eapp_shmstat(key, &dsc);
        while(1){
            if(ret != 0){
                LOG_ERROR("shmstat failed\n");
                close_with_server("test_server", key); 
                EAPP_RETURN(0);
            }else{
                if(dsc.ref_count == 1){
                    break;
                }else{
                    ret = eapp_shmstat(key, &dsc);
                }
            }
        }
        ret = close_with_server("test_server", key);
        LOG_INFO("after close: %d\n", ret);
    }
    EAPP_RETURN(0);
}