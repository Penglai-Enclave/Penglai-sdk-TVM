#include <stdlib.h>
#include <string.h>

#include "eapp.h"
#include "print.h"
#include "async_ipc_lib.h"
#include "argument.h"
#define LOG_LEVEL 4
#include "log.h"
#define SUMINT (1)
#define PRODUCTINT (2)
#define END (3)
#define START (4)
#define ITERATION (10000)

void handle_request(int cmd, void *request)
{
    struct argument *arg = (struct argument *)request;
    switch (cmd)
    {
    case SUMINT:
    {
        // int sum = 0;
        int *data = (char *)arg + sizeof(struct argument);
        // for (int i = 0; i < 10; i++){
        //     sum += data[i];
        // }
        // int* data = (char*)arg + sizeof(struct argument);
        int sum = data[0] + data[1];
        *(int *)(request) = sum;
        async_ret(request, 0, sizeof(int));
        return;
    }
    default:
    {
        LOG_ERROR("Some Error\n");
        async_ret(request, -1, sizeof(int));
    }
    }
}

int EAPP_ENTRY main()
{
    unsigned long *args;
    EAPP_RESERVE_REG;
    LOG_INFO("async_ipc_server initializing\n");
    unsigned int *keys;
    unsigned long server_identifier;
    keys = server_register("test_server", 1, &server_identifier);
    void *reqp;
    int cmd, ret;
    char *shared_memory_regions[1] = {NULL};
    if (keys == NULL)
    {
        LOG_INFO("[eapp]: async_ipc_server registration failed\n");
        EAPP_RETURN(0);
    }
    else
    {
        LOG_INFO("[eapp]: async_ipc_server registration successful\n");
    }
    for (int i = 0; i < 5; i++)
    {
        while (1)
        {
            if (!shared_memory_regions[0])
            {
                shared_memory_regions[0] = eapp_shmat(keys[0]);
            }
            if (shared_memory_regions[0])
            {
                break;
            }
        }
        while(1){
            cmd = async_server_polling_request(shared_memory_regions[0], &reqp);
            if(cmd != START){
                continue;
            }
            async_ret(reqp, 0, sizeof(int));
            break;
        }
        int iteration = 0;
        while (iteration < 10000)
        {
            cmd = async_server_polling_request(shared_memory_regions[0], &reqp);
            if(cmd != -1){
                handle_request(cmd, reqp);
                iteration++;
            }
        }
        ret = eapp_shmdt(keys[0]);
        if(ret != 0){
            LOG_INFO("async server detach failed\n");
        }       
        ret = eapp_shmdestroy(keys[0]);
        shared_memory_regions[0] = NULL;
        if(ret != 0){
            LOG_INFO("async server destroy failed\n");
        }
    }

done:
    eapp_print("[eapp]: async_ipc_server done\n");
    server_close("test_server", server_identifier);
    EAPP_RETURN(0);
}