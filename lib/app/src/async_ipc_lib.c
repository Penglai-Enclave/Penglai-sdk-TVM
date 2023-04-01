#include <string.h>
#include "async_ipc_lib.h"
#include "eapp.h"
#include "enclave_error.h"
#include "barrier.h"
#include "log.h"
#define MAXRETRY (100)
static char* g_premmaped_buf;

static inline void* get_premapped_buf()
{
    if(!g_premmaped_buf)
    {
        g_premmaped_buf = eapp_mmap(NULL, 4096);
    }
    return g_premmaped_buf;
}

static inline void set_premapped_buf(const char* buf)
{
    g_premmaped_buf = buf;
}

// server should manually free the allocated buf using eapp_unmap. 

unsigned int* server_register(const char *server_name, unsigned int num, long * identifier)
{
    unsigned long handler = acquire_enclave("ipc_manager");
    unsigned long status;
    if(handler == -1UL || num > 4096/sizeof(unsigned int)) 
    {
        LOG_INFO("acquire ipc_manager handler failed\n");
        *identifier = -1;
        return NULL;
    }
    struct call_enclave_arg_t call_arg;
    call_arg.req_arg = IPC_SERVER_REGISTER;
    struct server_register_arg* arg = eapp_mmap(NULL,4096);
    if(arg == NULL)
    {
        *identifier = -1;
        return NULL;
    }
    strcpy(arg->server_name, server_name);
    arg->size = num;
    call_arg.req_vaddr = arg;
    call_arg.req_size = 4096;
    status = call_enclave(handler, &call_arg);
    while(status == -ESERVERBUSY)
    {
        status = call_enclave(handler, &call_arg);
    }

    if(status || call_arg.resp_val == -1UL)
    {
        eapp_unmap(arg, 4096);
        *identifier = -1;
        return NULL;
    }
    *identifier = call_arg.resp_val;
    return (unsigned int*)(call_arg.req_vaddr);
}

int server_close(const char* server_name, const long identifier)
{
    unsigned long handler = acquire_enclave("ipc_manager");
    unsigned long status;
    if(handler == -1UL)
    {
        return -1;
    }
    struct call_enclave_arg_t call_arg;
    call_arg.req_arg = IPC_SERVER_CLOSE;
    struct server_close_arg* arg = get_premapped_buf();
    if(arg == NULL)
    {
        return -1;
    }
    strcpy(arg->server_name, server_name);
    arg->identifier = identifier;
    call_arg.req_vaddr = arg;
    call_arg.req_size = 4096;
    status = call_enclave(handler,&call_arg);
    while(status == -ESERVERBUSY)
    {
        status = call_enclave(handler, &call_arg);
    }
    if(status)
    {
        return -1;
    }
    set_premapped_buf(call_arg.req_vaddr);
    return call_arg.resp_val;
}

void* connect_to_server(const char *server_name, unsigned long mem_size, unsigned int* key)
{
    unsigned long handler = acquire_enclave("ipc_manager");
    unsigned long status;
    if(handler == -1UL)
    {
        return NULL;
    }
    if(strlen(server_name) >= MAX_SERVER_NAME_LENGTH)
    {
        return NULL;
    }
    struct call_enclave_arg_t call_arg;
    call_arg.req_arg = IPC_CLIENT_CONNECT;
    struct client_connect_arg* arg = get_premapped_buf();
    strcpy(arg->server_name, server_name);
    call_arg.req_vaddr = arg;
    call_arg.req_size = 4096;
    status = call_enclave(handler, &call_arg);
    LOG_DEBUG("call_enclave status: %ld\n", status);
    int retried = 0;
    while(status == -ESERVERBUSY || call_arg.resp_val == -1U)
    {
        retried++;
        for(int i = 0; i < 1e5; i++); //delay for some time
        status = call_enclave(handler, &call_arg);
        if(retried == MAXRETRY){
            break;
        }
    }
    if(status)
    {
        LOG_INFO("connect_to_server failed\n");
        *key = -1;
        return NULL;
    }
    set_premapped_buf(call_arg.req_vaddr);
    if(call_arg.resp_val == -1U)
    {
        LOG_INFO("connect_to_server resp_val = -1\n");
        *key = -1;
        return NULL;
    }
    if(mem_size % PAGE_SIZE != 0)
    {
        mem_size >>= PAGE_SHIFT;
        mem_size += 1;
        mem_size <<= PAGE_SHIFT;
    }
    LOG_DEBUG("connect_to_server resp_val: %d\n", (int)call_arg.resp_val);
    void* shm_va = eapp_shmget(call_arg.resp_val, mem_size, 0);
    if(shm_va == NULL)
    {
        LOG_INFO("connect_to_server shmget failed\n");
        call_arg.req_arg = IPC_CLIENT_CLOSE;
        struct client_close_arg* close_arg = get_premapped_buf();
        strcpy(close_arg->server_name, server_name);
        close_arg->shm_key = call_arg.resp_val;
        call_arg.req_vaddr = close_arg;
        call_arg.req_size = PAGE_SIZE;
        status = call_enclave(handler, &call_arg);
        LOG_DEBUG("after call IPC_CLIENT_CLOSE\n");
        while(status == -ESERVERBUSY)
        {
            status = call_enclave(handler, &call_arg);
        }
        if(status || call_arg.resp_val == -1U)
        {
            LOG_INFO("failed to close the link after failing to create shared memory\n");
        }
        set_premapped_buf(call_arg.req_vaddr);
        LOG_DEBUG("before return to user enclave from library\n");
        *key = -1;
        return NULL;
    }
    *key = (unsigned int)call_arg.resp_val;
    return shm_va;
}


int close_with_server(const char* server_name, unsigned int key)
{
    int ret;
    unsigned long status;
    if(strlen(server_name) >= MAX_SERVER_NAME_LENGTH)
    {
        return -1;
    }
    unsigned long handler = acquire_enclave("ipc_manager");
    if(handler == -1UL)
    {
        return -1;
    }
    ret = eapp_shmdt((unsigned long)key);
    if(ret != 0)
    {
        LOG_INFO("shared memory detach failed\n");
        return -1;
    }
    ret = eapp_shmdestroy((unsigned long)key);
    if(ret != 0)
    {
        LOG_INFO("shared memory destroy failed\n");
        return -1;
    }
    LOG_DEBUG("after destroy\n");
    struct call_enclave_arg_t call_arg;
    call_arg.req_arg = IPC_CLIENT_CLOSE;
    struct client_close_arg* arg = get_premapped_buf();
    strcpy(arg->server_name, server_name);
    arg->shm_key = key;
    call_arg.req_vaddr = arg;
    call_arg.req_size = 4096;
    LOG_DEBUG("before call_enclave\n");
    status = call_enclave(handler, &call_arg);
    LOG_DEBUG("after call_enclave\n");
    while(status == -ESERVERBUSY)
    {
        LOG_DEBUG("before call_enclave\n");
        status = call_enclave(handler, &call_arg);
    }
    if(status)
    {
        LOG_INFO("close_with_server failed\n");
    }
    set_premapped_buf(call_arg.req_vaddr);
    return call_arg.resp_val;
}

void async_submit_request(void* shared_data, unsigned long cmd)
{
    struct async_ipc_param* param = (struct async_ipc_param*)shared_data;
    param->cmd = cmd;
    param->status = SUBMITTED;
    while(param->status == SUBMITTED){   
    }
    return 0;
}

int async_client_polling_ret(void* shared_data, void** result, unsigned int* ret_size)
{
    struct async_ipc_param* param = (struct async_ipc_param*)shared_data;
    while(param->status != COMPLETED){}
    mb();
    *result = (char*)shared_data + sizeof(struct async_ipc_param);
    *ret_size = param->ret_size;
    return param->ret_val;
}

int async_call(void* shared_data, unsigned long cmd, void** result, unsigned int*ret_sizep)
{
    struct async_ipc_param* parameter = (struct async_ipc_param *)shared_data;
    parameter->cmd = cmd;
    parameter->status = SUBMITTED;
    while(parameter->status != COMPLETED){
    }
    mb();
    *result = (char*)shared_data + sizeof(struct async_ipc_param);
    *ret_sizep = parameter->ret_size;
    return parameter->ret_val;
}

void* async_client_get_request_mem(void* shared_data)
{
    if(shared_data == NULL)
    {
        return NULL;
    }
    return (char*)shared_data + sizeof(struct async_ipc_param);
}

void async_ret(void* reqp, int ret_val, unsigned int ret_size)
{
    void* shared_data = (char*)reqp - sizeof(struct async_ipc_param);
    struct async_ipc_param* param = (struct async_ipc_param*)shared_data;
    param->ret_val = ret_val;
    param->ret_size = ret_size;
    mb();
    param->status = COMPLETED;
}

int async_server_polling_request(void* shared_data, void** reqp)
{
    struct async_ipc_param* param = (struct async_ipc_param*)shared_data;
    if(param->status == SUBMITTED)
    {
        param->status = PROCESSING;
        mb();
        *reqp = (char*)shared_data + sizeof(struct async_ipc_param);
        return param->cmd;
    }
    return -1;
}


