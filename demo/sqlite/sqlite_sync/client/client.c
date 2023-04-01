// #define LOG_LEVEL DEBUG
#include "eapp.h"
#include "print.h"
#include "log.h"
#include "ycsb.h"
#include <stdlib.h>
#include <string.h>
#define QUERY (1UL)
#define OTHER (2UL)

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

int EAPP_ENTRY main(){
    unsigned long * args;
    EAPP_RESERVE_REG;
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
    void* mem = eapp_mmap(NULL, shm_size);
    if(mem==NULL){
        LOG_ERROR("Memory allocation failed\n");
        EAPP_RETURN(-1);
    }
    // unsigned long ret;
    unsigned long server_handler = acquire_enclave("sqlite-server");
    if(server_handler == -1UL){
        LOG_ERROR("Acquire sqlite-server handle failed\n");
        EAPP_RETURN(-1);
    }
    const char* prefix = "jxq";
    int ret = generate_table(prefix, 1000, 1, 100, mem, shm_size, server_handler);
    if(ret != 0){
        LOG_ERROR("Failed to generate table\n");
        eapp_unmap(mem, shm_size);
        EAPP_RETURN(-1);
    }
    LOG_INFO("Table generated successfully\n");
#if  (defined WORKLOAD_ADA)
    performance_test(1000,1000, prefix, 95, 2, 2, 1, mem, shm_size, server_handler);
#elif (defined WORKLOAD_ADB)
    performance_test(1000,1000, prefix, 95, 5, 0, 0, mem, shm_size, server_handler);
#elif (defined WORKLOAD_ADC)
    performance_test(1000,1000, prefix,100, 0, 0, 0, mem, shm_size, server_handler);
#elif (defined WORKLOAD_ADD)
    performance_test(1000,1000, prefix, 95, 0, 5, 0, mem, shm_size, server_handler);
#elif (defined WORKLOAD_ADE)
    performance_test(1000,1000, prefix, 0, 0, 5, 95, mem, shm_size, server_handler);
#endif
    eapp_unmap(mem, shm_size);
#if 0
    strcpy((char*)mem,"CREATE TABLE IF NOT EXISTS test(id INTEGER PRIMARY KEY, name VARCHAR(16));");
    struct call_enclave_arg_t call_arg;
    call_arg.req_vaddr = mem;
    call_arg.req_size = 0x1000;
    call_arg.req_arg = OTHER;
    ret = call_enclave(server_handle, &call_arg);
    struct query_result* result= (struct query_result*)call_arg.req_vaddr;
    if(result->return_code != 0 || ret != 0){
        LOG_ERROR("create test table failed\n");
        EAPP_RETURN(-1);
    }
    mem = call_arg.req_vaddr;
    strcpy((char*)mem, "INSERT INTO test VALUES(1, \"jxq\");");
    call_arg.req_arg = OTHER;
    ret = call_enclave(server_handle, &call_arg);
    result = (struct query_result*)call_arg.req_vaddr;
    if(result->return_code != 0 || ret != 0){
        LOG_ERROR("insert into table failed\n");
        EAPP_RETURN(-1);
    }
    mem = call_arg.req_vaddr;
    strcpy((char*)mem, "select * from test;");
    call_arg.req_arg = QUERY;
    unsigned long start = rdcycle();
    ret = call_enclave(server_handle, &call_arg);
    unsigned long end = rdcycle();
    result = (struct query_result*)call_arg.req_vaddr;
    if(result->return_code != 0 || ret != 0){
        LOG_ERROR("select from table failed\n");
    }
    if(result->over == 0){
        LOG_WARNING("should make large buffer to test\n");
        EAPP_RETURN(-1);
    }
    void* result_buf = call_arg.req_vaddr + sizeof(struct query_result);
    for(unsigned long i = 0; i < result->row_count; ++i){
        eapp_print("id: %d, name: %s\n", parse_int(&result_buf), parse_text(&result_buf));
    }
    LOG_INFO("ret: %ld\n", start);
#endif
    EAPP_RETURN(0);
}