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
    PLenclave_run(enclave);
    printf("enclave run successfully\n");
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
  pthread_t threads[2];
  int img_size = 512; // default image size.


  if (argc !=3 && argc != 4)
  {
    printf("Usage: ./host [image_size] server client\n");
    return -1;
  }
  int needed_argc = 1;
  if(argc == 4){
    img_size = atoi(argv[needed_argc++]);
  }
  if (img_size<32 || img_size>4096){
	  printf("Host: Error img size:%d\n", img_size);
	  return -1;
  }

callee:
    debug_printf("Start init callee enclave\n");
    callee_enclaveFile = (struct elf_args*)malloc(sizeof(struct elf_args));
    elf_args_init(callee_enclaveFile, argv[needed_argc++]);
    if(!elf_valid(callee_enclaveFile)){
      printf("host: error when initializing sync image processing\n");
      goto out;
    }
    callee_params = (struct enclave_args*)malloc(sizeof(struct enclave_args));
    enclave_args_init(callee_params);
    strcpy(callee_params->name,"img-process");
    callee_params->type = SERVER_ENCLAVE;
    callee_enclave = (struct PLenclave*)malloc(sizeof(struct PLenclave));
    PLenclave_init(callee_enclave);
    if(PLenclave_create(callee_enclave, callee_enclaveFile, callee_params) < 0){
      printf("host: failed to create sync image processing server, may have created\n");
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
  PLenclave_run(caller_enclave);
  debug_printf("After running enclave\n");
  // PLenclave_destroy(caller_enclave);
  PLenclave_destroy(callee_enclave);

out:
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
