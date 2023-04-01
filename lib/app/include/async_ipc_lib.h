#ifndef __ASYC_IPC_LIB__
#define __ASYC_IPC_LIB__

#define IPC_SERVER_REGISTER         0
#define IPC_CLIENT_CONNECT          1
#define IPC_CLIENT_CLOSE            2
#define IPC_SERVER_CLOSE            3            
#define MAX_SERVER_NAME_LENGTH      64
#define PAGE_SIZE                   (4096)
#define PAGE_SHIFT                  (12)
#define EAIPC_SERVER_NOTFOUND (3)
//FIXME: Need to record which key assigned to which client or not?


typedef enum {
    FREE = 0,
    SUBMITTED = 1,
    PROCESSING = 2,
    COMPLETED = 3
} REQ_STATUS;

struct server_register_arg 
{
    char server_name[MAX_SERVER_NAME_LENGTH];
    unsigned int size;
};

struct client_connect_arg
{
    char server_name[MAX_SERVER_NAME_LENGTH];
};

struct client_close_arg
{
    char server_name[MAX_SERVER_NAME_LENGTH];
    unsigned int shm_key;
};

struct server_close_arg
{
    char server_name[MAX_SERVER_NAME_LENGTH];
    long identifier;
};


//TODO: check whether status modification needs to be atomic.
struct async_ipc_param{
    volatile REQ_STATUS status;
    unsigned long cmd; // cmd is dependent to applications
    int ret_val;
    unsigned int ret_size;
}__attribute__((align(64)));

#include <stddef.h>

unsigned int* server_register(const char *server_name, unsigned int num, long * identifier);

int server_close(const char* server_name, const long identifier);

//return the start virtual address of the memory.
void* connect_to_server(const char *server_name, unsigned long mem_size, unsigned int* key);

int close_with_server(const char * server_name, unsigned int key);

void async_submit_request(void* shared_data, unsigned long cmd);

int async_client_polling_ret(void* shared_data, void** result, unsigned int* ret_size);

int async_call(void* shared_data, unsigned long cmd,  void** result, unsigned int*ret_size);

void* async_client_get_request_mem(void* shared_data);


int async_server_polling_request(void* shared_data, void** req);

void async_ret(void* reqp, int ret_val, unsigned int ret_size);

// int issue_request(void* request, unsigned int size);

// int get_requset(unsigned int* keys, unsigned int num);

// int finish_request(void* request);



#endif