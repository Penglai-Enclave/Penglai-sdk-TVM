#include "penglai-enclave.h"
#include <stdlib.h>
#include <pthread.h>

#define MAGIC_SHM_VALUE 11111
#define MAGIC_RELAY_PAGE_VALUE 22222

#define SHM_SIZE 1024*1024*2

void* global_mm_arg;

struct args
{
  void* in;
  int i;
};

void* detect_enclave(void)
{
  printf("Host try to access enclave's memory\n");

  ((int*)global_mm_arg)[0] = MAGIC_RELAY_PAGE_VALUE;

  printf("Host accesses enclave's memory successfully\n");
}

void* create_enclave(void* args0)
{
  struct args *args = (struct args*)args0;
  void* in = args->in;
  int i = args->i;
  int ret = 0, result = 0;
  
  struct PLenclave* enclave = malloc(sizeof(struct PLenclave));
  struct enclave_args* params = malloc(sizeof(struct enclave_args));
  PLenclave_init(enclave);
  enclave_args_init(params);

  struct elf_args *enclaveFile = (struct elf_args *)in;

  unsigned long shm_size = 0x1000 * 1;
  int shmid = PLenclave_shmget(shm_size);
  void* shm = PLenclave_shmat(shmid, 0);
  if(shm != (void*)-1)
  {
    ((int*)shm)[0] = MAGIC_SHM_VALUE;
  }
  params->shmid = shmid;
  params->shm_offset = 0;
  params->shm_size = shm_size;
  
  unsigned long mm_arg_size = 0x1000 * 1;
  int mm_arg_id = PLenclave_schrodinger_get(mm_arg_size);
  void* mm_arg = PLenclave_schrodinger_at(mm_arg_id, 0);
  global_mm_arg = mm_arg;
  if(mm_arg != (void*)-1)
  {
    ((int*)mm_arg)[0] = MAGIC_RELAY_PAGE_VALUE;
  }
  char str_num[15];
  sprintf(str_num, "test-enclave%d", i);
  strcpy(params->name, str_num);
  
  if(PLenclave_create(enclave, enclaveFile, params) < 0)
  {
    printf("host:%d: failed to create enclave\n", i);
  }
  else
  {
    PLenclave_attest(enclave, 0);
    if(mm_arg_id > 0 && mm_arg)
      PLenclave_set_mem_arg(enclave, mm_arg_id, 0, mm_arg_size);

    printf("enclave begins to run\n");
    while (result = PLenclave_run(enclave))
    {
      switch (result)
      {
        case RETURN_USER_RELAY_PAGE:
          ((int*)mm_arg)[0] = 0;
          PLenclave_set_rerun_arg(enclave, RETURN_USER_RELAY_PAGE);
          break;
        default:
        {
          printf("[ERROR] host: result %d val is wrong!\n", result);
          goto free_enclave;
        }
      }
    }
  }
  PLenclave_destruct(enclave);
  printf("host: PLenclave run is finish \n");

free_enclave:  
  PLenclave_shmdt(shmid, shm);
  PLenclave_shmctl(shmid);
  PLenclave_schrodinger_dt(mm_arg_id, mm_arg);
  PLenclave_schrodinger_ctl(mm_arg_id);
  free(enclave);
  free(params);
  pthread_exit((void*)0);
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
  pthread_t* detect_threads = (pthread_t*)malloc(sizeof(pthread_t));

  struct elf_args* enclaveFile = malloc(sizeof(struct elf_args));
  char* eappfile = argv[1];
  elf_args_init(enclaveFile, eappfile);
  
  if(!elf_valid(enclaveFile))
  {
    printf("error when initializing enclaveFile\n");
    goto out;
  }

  for(int i=0; i< thread_num; ++i)
  {
    args[i].in = (void*)enclaveFile;
    args[i].i = i + 1;
    pthread_create(&threads[i], NULL, create_enclave, (void*)&(args[i]));
  }

  unsigned long *flush_cache = (unsigned long *)malloc(SHM_SIZE);
  for (int j=0; j<10; j++) {
    for (int i=0; i <SHM_SIZE/8; i++) {
      flush_cache[i] = 0;
    }
    printf("iteration %d \n", j);
  }

  printf("Host try to access enclave's memory\n");

  ((int*)global_mm_arg)[0] = MAGIC_RELAY_PAGE_VALUE;

  printf("Host accesses enclave's memory successfully\n");

  // pthread_create(detect_threads, NULL, detect_enclave, NULL);

  // for (int j=0; j<10; j++) {
  //   for (int i=0; i <SHM_SIZE/8; i++) {
  //     flush_cache[i] = 0;
  //   }
  //   printf("iteration %d \n", j);
  // }

  // printf("Host cannot access enclave's memory\n");

  // pthread_join(detect_threads, (void**)0);

  // for(int i =0; i< thread_num; ++i)
  // {
  //   pthread_join(threads[i], (void**)0);
  // }
  printf("host: after exit the thread\n");
out:
  elf_args_destroy(enclaveFile);
  free(enclaveFile);
  free(threads);
  free(args);

  return 0;
}
