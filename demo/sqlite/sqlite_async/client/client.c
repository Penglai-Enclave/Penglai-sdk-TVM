// #define LOG_LEVEL DEBUG
#include "eapp.h"
#include "print.h"
#include "log.h"
#include "async_ipc_lib.h"
#include "ycsb.h"

#include <stdlib.h>
#include <string.h>
#define QUERY (1UL)
#define OTHER (2UL)
#define CLOSE (3UL)
#define WORKLOAD_ADE
struct query_result {
    int return_code;
    unsigned long row_count;
    unsigned long over;
};

static inline unsigned long rdcycle(void)
{
    unsigned long ret;
    asm volatile ("rdcycle %0" : "=r"(ret));
    return ret;
}

int parse_int(void** buf){
    if(buf==NULL || *buf == NULL){
        LOG_ERROR("Invalid parser buffer\n");
        return 0;
    }
    int* int_buf = (int*)(*buf);
    *buf += sizeof(int);
    return *int_buf;
}

char* parse_text(void** buf){
    if(buf==NULL || *buf == NULL){
        LOG_ERROR("Invalid parser buffer\n");
        return 0;
    }
    char* str = (char*)(*buf);
    *buf += strlen(str) + 1;
    return str;
}

int EAPP_ENTRY main()
{
    unsigned long * args;
    EAPP_RESERVE_REG;
    void* shm;
    unsigned int key;
#if (defined WORKLOAD_ADA)
    LOG_INFO("YCSB ada workload test");
    const unsigned long shm_size = 4096*15UL;
#elif (defined WORKLOAD_ADB)
    LOG_INFO("YCSB adb workload test");
    const unsigned long shm_size = 4096UL;
#elif (defined WORKLOAD_ADC)
    LOG_INFO("YCSB adc workload test");
    const unsigned long shm_size = 4096UL;
#elif (defined WORKLOAD_ADD)
    LOG_INFO("YCSB add workload test");
    const unsigned long shm_size = 4096UL;
#elif (defined WORKLOAD_ADE)
    LOG_INFO("YCSB ade workload test");
    const unsigned long shm_size = 4096*31UL;
#endif
    shm = connect_to_server("sqlite-server",shm_size, &key);
    if(shm == NULL){
        LOG_ERROR("Failed to connect to sqlite server\n");
        EAPP_RETURN(-1);
    }
    const char* prefix = "jxq";
    int ret = generate_table(prefix, 1000, 1, 100, shm);
    struct query_result* result;
    unsigned int ret_sz;
    if(ret != 0){
        LOG_ERROR("Failed to generate table\n");
        if(async_call(shm, CLOSE, &result, &ret_sz) != 0){
            LOG_ERROR("Failed to database close\n");
        }
        if(close_with_server("sqlite-server", key) != 0){
            LOG_ERROR("Failed to ipc close\n");
        }
        EAPP_RETURN(-1);
    }
    LOG_INFO("Table generated successfully\n");
#if (defined WORKLOAD_ADA)
    performance_test(1000,1000, prefix, 95, 2, 2, 1, shm);
#elif (defined WORKLOAD_ADB)
    performance_test(1000,1000, prefix, 95, 5, 0, 0, shm);
#elif (defined WORKLOAD_ADC)
    performance_test(1000,1000, prefix, 100, 0, 0, 0, shm);
#elif (defined WORKLOAD_ADD)
    performance_test(1000,1000, prefix, 95, 0, 5, 0, shm);
#elif (defined WORKLOAD_ADE)
    performance_test(1000,1000, prefix, 0, 0, 5,95, shm);
#endif
    if(async_call(shm, CLOSE, &result, &ret_sz) != 0){
        LOG_ERROR("Failed to database close\n");
    }
    if(close_with_server("sqlite-server", key) != 0){
        LOG_ERROR("Failed to ipc close\n");
    }

#if 0
    struct query_result* result;
    unsigned int result_sz;
    char* sql = (char*)async_client_get_request_mem(shm);
    strcpy((char*)sql,"CREATE TABLE IF NOT EXISTS test(id INTEGER PRIMARY KEY, name VARCHAR(16));");
    async_submit_request(shm, OTHER);
    int ret = async_client_polling_ret(shm, &result, &result_sz);
    if(ret != 0 || result->return_code != 0){
        LOG_ERROR("Failed to create table\n");
        async_submit_request(shm, CLOSE);
        EAPP_RETURN(-1);
    }
    strcpy(sql, "INSERT INTO test VALUES(1, \"jxq\");");
    async_submit_request(shm, OTHER);
    ret = async_client_polling_ret(shm, &result, &result_sz);
    if(ret != 0 || result->return_code != 0){
        LOG_ERROR("Failed to insert\n");
        async_submit_request(shm, CLOSE);
        EAPP_RETURN(-1);
    }
    strcpy(sql, "select * from test;");
    unsigned long start = rdcycle();
    async_submit_request(shm, QUERY);
    unsigned long middle = rdcycle();
    ret = async_client_polling_ret(shm, &result, &result_sz);
    unsigned long end = rdcycle();
    if(ret != 0 || result->return_code != 0){
        LOG_ERROR("Failed to query\n");
        async_submit_request(shm, CLOSE);
        EAPP_RETURN(-1);
    }
    void* result_buf = (void*)result + sizeof(struct query_result);
    for(unsigned long i = 0; i < result->row_count; ++i){
        eapp_print("id: %d, name: %s\n", parse_int(&result_buf), parse_text(&result_buf));
    }
    LOG_INFO("response: %ld, ret: %ld\n", middle - start, end - start);
    async_submit_request(shm, CLOSE);
#endif
    EAPP_RETURN(0);
}