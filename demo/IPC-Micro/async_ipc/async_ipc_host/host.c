#define _GNU_SOURCE 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sched.h>

#include "penglai-enclave.h"

static void check_pointer_not_null(void *pointer)
{
    if(pointer == NULL)
    {
        printf("host: allocated memory failed\n");
        exit(0);
    }
}

struct func_arg{
    struct PLenclave* enclave;
    int core;
};

void* run_enclave(void * arg)
{
    struct PLenclave* enclave = ((struct func_arg*)arg)->enclave;
    int core = ((struct func_arg*)arg)->core;
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(core, &mask);
    if(sched_setaffinity(0, sizeof(mask), &mask) == -1){
        printf("warning: could not set CPU affinity\n");
    }
    else{
        printf("set CPU affinity successfully\n");
    }
    PLenclave_run(enclave);
    printf("enclave run successfully\n");
    pthread_exit((void*)0);
}

int main(int argc, char** argv)
{
    if(argc != 4)
    {
        printf("Usage: You should run the ipc_manager and 2 enclave to communication\n");
        exit(0);
    }

    struct elf_args *ipc_manager_elf = NULL;
    struct PLenclave * ipc_manager_enclave = NULL;
    struct enclave_args *ipc_manager_param = NULL;
    struct elf_args * ipc_clients_elf[2] = {NULL, NULL};
    struct PLenclave * ipc_clients_enclave[2] = {NULL, NULL};
    struct enclave_args *ipc_clients_params[2] = {NULL, NULL};
    pthread_t threads[2];
    ipc_manager_elf = malloc(sizeof(struct elf_args));
    check_pointer_not_null(ipc_manager_elf);
    elf_args_init(ipc_manager_elf, argv[1]);
    if(!elf_valid(ipc_manager_elf))
    {
        printf("host: error when initializing ipc_manager\n");
        exit(0);
    }
    ipc_manager_enclave = malloc(sizeof(struct PLenclave));
    check_pointer_not_null(ipc_manager_enclave);
    PLenclave_init(ipc_manager_enclave);
    ipc_manager_param = malloc(sizeof(struct enclave_args));
    check_pointer_not_null(ipc_manager_param);
    enclave_args_init(ipc_manager_param);
    strcpy(ipc_manager_param->name,"ipc_manager");
    ipc_manager_param->type = SERVER_ENCLAVE;
    if(PLenclave_create(ipc_manager_enclave, ipc_manager_elf, ipc_manager_param) < 0)
    {
        printf("host: failed to create ipc_manager, may have created\n");
    }
    struct func_arg args[2];
    for(int i = 0; i < 2; i++)
    {
        ipc_clients_elf[i] = malloc(sizeof(struct elf_args));
        check_pointer_not_null(ipc_clients_elf[i]);
        elf_args_init(ipc_clients_elf[i], argv[i + 2]);
        if(!elf_valid(ipc_clients_elf[i]))
        {
            printf("host: error when initializing client\n");
            exit(0);
        }
        ipc_clients_enclave[i] = malloc(sizeof(struct PLenclave));
        args[i].enclave = ipc_clients_enclave[i];
        args[i].core = i;
        check_pointer_not_null(ipc_clients_enclave[i]);
        PLenclave_init(ipc_clients_enclave[i]);
        ipc_clients_params[i] = malloc(sizeof(struct enclave_args));
        check_pointer_not_null(ipc_clients_params[i]);
        enclave_args_init(ipc_clients_params[i]);
        if(PLenclave_create(ipc_clients_enclave[i], ipc_clients_elf[i], ipc_clients_params[i]) < 0)
        {
            printf("host: failed to create ipc client enclave %d\n", i);
            exit(0);
        }
        pthread_create(&threads[i], NULL, run_enclave, &args[i]);
    }
    for(int i = 0; i < 2; i++)
    {
        pthread_join(threads[i], NULL);
    }
    PLenclave_destroy(ipc_manager_enclave);

}