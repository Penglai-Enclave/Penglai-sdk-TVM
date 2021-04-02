#include "penglai-enclave.h"
#include <stdlib.h>
#include <stdlib.h>
#include <pthread.h>

unsigned long inst_pre_create;
unsigned long inst_pre_run;
unsigned long inst_post_run;

struct args
{
  unsigned long in;
  int i;
  int fd;
  int shmid;
  unsigned long shm_offset;
  unsigned long shm_size;
};

void* create_enclave(void* args0)
{
  struct args *args = (struct args*)args0;
  unsigned long eid = args->in;
  int i = args->i;
  int ret = 0;
  int fd = args->fd;
  int shmid = args->shmid;
  unsigned long shm_offset = args->shm_offset;
  unsigned long shm_size = args->shm_size;
  
  struct PLenclave* enclave = malloc(sizeof(struct PLenclave)); 
  enclave->fd = fd;
  printf("host:%d: enclave run\n", i);
  enclave->user_param.eid = eid;

  enclave->user_param.shmid = shmid;
  enclave->user_param.shm_offset = shm_offset;
  enclave->user_param.shm_size = shm_size;

  asm volatile("rdcycle %0":"=r"(inst_pre_run));
  PLenclave_run(enclave);
  pthread_exit((void*)0);
  free(enclave);
}

int main(int argc, char** argv)
{
  if(argc <= 1)
  {
    printf("Please input the enclave ELF file name\n");
  }

  int thread_num = 1;
  if(argc == 3)
  {
    thread_num = atoi(argv[2]);
    if(thread_num <= 0)
    {
      printf("error number\n");
      return -1;
    }
  }

  pthread_t* threads = (pthread_t*)malloc(thread_num * sizeof(pthread_t));
  struct args* args = (struct args*)malloc(thread_num * sizeof(struct args));

  struct elf_args* enclaveFile = malloc(sizeof(struct elf_args));
  char * eappfile = argv[1];
  elf_args_init(enclaveFile, eappfile);
  
  if(!elf_valid(enclaveFile))
  {
    printf("error when initializing enclaveFile\n");
    goto out;
  }
  struct PLenclave* enclave = malloc(sizeof(struct PLenclave)); 
  struct enclave_args* params = malloc(sizeof(struct enclave_args));
  PLenclave_init(enclave);
  enclave_args_init(params);

  unsigned long shm_size = 1024 * 1024;
  int shmid = PLenclave_shmget(shm_size);
  void* shm = PLenclave_shmat(shmid, 0);
  params->shmid = shmid;
  params->shm_offset = 0;
  params->shm_size = shm_size;
  params->type = SHADOW_ENCLAVE;


  if(PLenclave_create(enclave, enclaveFile, params) < 0 )
  {
    printf("host: failed to create enclave\n");
    pthread_exit((void*)0);
  }
  unsigned long eid = enclave->user_param.eid;
  int fd = enclave->fd;
  for(int i=0; i< thread_num; ++i)
  {
    args[i].in = eid;
    args[i].i = i + 1;
    args[i].fd = fd;
    args[i].shmid = enclave->user_param.shmid;
    args[i].shm_offset = enclave->user_param.shm_offset;
    args[i].shm_size = enclave->user_param.shm_size;
    pthread_create(&threads[i], NULL, create_enclave, (void*)&(args[i]));
  }

  for(int i =0; i< thread_num; ++i)
  {
    pthread_join(threads[i], (void**)0);
  }

  printf("inst_pre_run = %lu\n", inst_pre_run);

out:
  elf_args_destroy(enclaveFile);
  free(enclaveFile);
  free(threads);
  free(args);
  free(enclave);
  free(params);


  return 0;
}
