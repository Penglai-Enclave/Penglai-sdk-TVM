#define _GNU_SOURCE 1
#include "penglai-enclave.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sched.h>
#include <pthread.h>
#include "sod.h"
#define EAPP_DEBUG_PRINT
#ifdef EAPP_DEBUG_PRINT
#define debug_printf(...) printf(__VA_ARGS__)
#else
#define debug_printf(...) 
#endif
static inline unsigned long rdcycle(void)
{
    unsigned long ret;
    asm volatile("rdcycle %0"
                 : "=r"(ret));
    return ret;
}

struct func_arg {
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
    int ret = PLenclave_run(enclave);
    printf("enclave run successfully: %d, ret: %d\n", core, ret);
    pthread_exit((void*)0);
}

int main(int argc, char** argv)
{
  struct elf_args* caller_enclaveFile = NULL;
  struct PLenclave* caller_enclave = NULL;
  struct enclave_args* caller_params = NULL;
  struct elf_args* callee_enclaveFile = NULL;
  struct PLenclave* callee_enclave = NULL;
  struct enclave_args* callee_params = NULL;
  struct elf_args* ipc_manager_elf = NULL;
  struct PLenclave* ipc_manager_enclave = NULL;
  struct enclave_args* ipc_manager_param = NULL;
  pthread_t threads[2];
  int img_size = 512; // default image size.


  if (argc !=4 && argc != 5)
  {
    printf("Usage: ./host [image_size] ipc_manager server client\n");
    return -1;
  }
  int needed_argc = 1;
  if(argc == 5){
    img_size = atoi(argv[needed_argc++]);
  }
  if (img_size<32 || img_size>4096){
	  printf("Host: Error img size:%d\n", img_size);
	  return -1;
  }

ipc_mnager:
    debug_printf("Start init ipc_mnager enclave\n");
    ipc_manager_elf = (struct elf_args*)malloc(sizeof(struct elf_args));
    elf_args_init(ipc_manager_elf, argv[needed_argc++]);
    if(!elf_valid(ipc_manager_elf)){
      printf("host: error when initializing ipc-manager\n");
      goto out;
    }
    ipc_manager_param = (struct enclave_args*)malloc(sizeof(struct enclave_args));
    enclave_args_init(ipc_manager_param);
    strcpy(ipc_manager_param->name, "ipc_manager");
    ipc_manager_param->type = SERVER_ENCLAVE;
    ipc_manager_enclave = (struct PLenclave*)malloc(sizeof(struct PLenclave));
    PLenclave_init(ipc_manager_enclave);
    if(PLenclave_create(ipc_manager_enclave, ipc_manager_elf, ipc_manager_param) < 0){
      printf("host: failed to create ipc-manager, may have been created\n");
    }
callee:
    debug_printf("Start init callee enclave\n");
    callee_enclaveFile = (struct elf_args*)malloc(sizeof(struct elf_args));
    elf_args_init(callee_enclaveFile, argv[needed_argc++]);
    if(!elf_valid(callee_enclaveFile)){
      printf("host: error when initializing async image processing\n");
      goto out;
    }
    callee_params = (struct enclave_args*)malloc(sizeof(struct enclave_args));
    enclave_args_init(callee_params);
    strcpy(callee_params->name,"img-process");
    callee_enclave = (struct PLenclave*)malloc(sizeof(struct PLenclave));
    PLenclave_init(callee_enclave);
    if(PLenclave_create(callee_enclave, callee_enclaveFile, callee_params) < 0){
      printf("host: failed to create async image processing server, may have been created\n");
    }
caller:
  debug_printf("Start init caller enclave\n");
  caller_enclaveFile = malloc(sizeof(struct elf_args));
  char *caller_eappfile = argv[needed_argc++];
  elf_args_init(caller_enclaveFile, caller_eappfile);
  
  if(!elf_valid(caller_enclaveFile))
  {
    printf("host:error when initializing caller_enclaveFile\n");
    goto out;
  }

  caller_enclave = malloc(sizeof(struct PLenclave));
  caller_params = malloc(sizeof(struct enclave_args));
  enclave_args_init(caller_params);
  PLenclave_init(caller_enclave);

  unsigned long shm_size = img_size * img_size * 3 * sizeof(float) + 0x1000;  //0x1000 * 8 * 4;
  unsigned long shmid;
  void* shm;
  shmid = PLenclave_shmget(shm_size);
  debug_printf("After shmget\n");
  shm = PLenclave_shmat(shmid, 0);
  debug_printf("After shmat\n");
  memset(shm, 0, shm_size);
  sod_img imgIn = sod_make_image_inplace(img_size,img_size, 3, shm);

  caller_params->shmid = shmid;
  caller_params->shm_offset = 0;
  caller_params->shm_size = shm_size;

  if(PLenclave_create(caller_enclave, caller_enclaveFile, caller_params) < 0 )
  {
    printf("host: failed to create caller_enclave\n");
    goto out;
  }
  debug_printf("Ready to run enclave\n");
  struct func_arg thread_arg[2];
  for(int i = 0; i < 2; i++){
    thread_arg[i].core = i;
    if(i == 1){
      thread_arg[i].enclave = caller_enclave;
      pthread_create(&threads[i], NULL, run_enclave, (void*)(&(thread_arg[i])));
    }else{
      thread_arg[i].enclave = callee_enclave;
      pthread_create(&threads[i], NULL, run_enclave, (void*)(&(thread_arg[i])));
    }
  }
  for(int i = 0; i < 2; i++){
    pthread_join(threads[i],NULL);
  }
  debug_printf("async img-processing test finished\n");
out:
  if(ipc_manager_elf){
    elf_args_destroy(ipc_manager_elf);
    free(ipc_manager_elf);
  }
  if(ipc_manager_enclave)
  {
    PLenclave_destroy(ipc_manager_enclave);
    free(ipc_manager_enclave);
  }
  if(ipc_manager_param){
    free(ipc_manager_param);
  }
  if(caller_enclaveFile)
  {
    elf_args_destroy(caller_enclaveFile);
    free(caller_enclaveFile);
  }
  if(caller_enclave)
  {
    free(caller_enclave);
  }
  if(caller_params)
  {
    free(caller_params);
  }
  if(callee_enclave){
    free(callee_enclave);
  }
  if(callee_enclaveFile){
    free(callee_enclaveFile);
  }
  if(callee_params){
    free(callee_params);
  }
  PLenclave_shmdt(shmid, shm);

  return 0;
}
