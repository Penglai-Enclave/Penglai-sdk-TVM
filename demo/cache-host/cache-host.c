#include "penglai-enclave.h"
#include <stdlib.h>
#include <pthread.h>

#define MAGIC_SHM_VALUE 11111
#define MAGIC_RELAY_PAGE_VALUE 22222
#define SHM_SIZE 1024*1024*2

unsigned long *g_shm;
struct args
{
  void* in;
  int i;
};

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

  unsigned long shm_size = SHM_SIZE;
  int shmid = PLenclave_shmget(shm_size);
  void* shm = PLenclave_shmat(shmid, 0);
  g_shm = shm;
  if(shm != (void*)-1)
  {
    ((int*)shm)[0] = MAGIC_SHM_VALUE;
  }
  params->shmid = shmid;
  params->shm_offset = 0;
  params->shm_size = shm_size;
  
  // unsigned long mm_arg_size = 0x1000 * 1;
  // int mm_arg_id = PLenclave_schrodinger_get(mm_arg_size);
  // void* mm_arg = PLenclave_schrodinger_at(mm_arg_id, 0);
  // if(mm_arg != (void*)-1)
  // {
  //   ((int*)mm_arg)[0] = MAGIC_RELAY_PAGE_VALUE;
  // }
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
    // if(mm_arg_id > 0 && mm_arg)
    //   PLenclave_set_mem_arg(enclave, mm_arg_id, 0, mm_arg_size);
    while (result = PLenclave_run(enclave))
    {
      switch (result)
      {
        // case RETURN_USER_RELAY_PAGE:
        //   ((int*)mm_arg)[0] = 0;
        //   PLenclave_set_rerun_arg(enclave, RETURN_USER_RELAY_PAGE);
        //   break;
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
  // PLenclave_schrodinger_dt(mm_arg_id, mm_arg);
  // PLenclave_schrodinger_ctl(mm_arg_id);
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

  //probe the cache
  // unsigned long start_time, end_time;
  // asm volatile("rdcycle %0" : "=r"(start_time));
  // printf("host: start time %ld\n",start_time);

  //wait for the victim enclave to run
  // int value;
  // for (int j=0; j<10; j++) {
  //   for (int i=0; i<50000000/200; i++) {
  //     value++;
  //   }
  //   printf("iteration %d \n", j);
  // }

  //flush the cache with the attacker's value
  unsigned long *flush_cache = (unsigned long *)malloc(SHM_SIZE);
  for (int j=0; j<5; j++) {
    for (int i=0; i <SHM_SIZE/8; i++) {
      flush_cache[i] = 0;
    }
    printf("iteration %d \n", j);
  }

  // unsigned long *ptr0 = g_shm;
  // unsigned long *ptr1 = g_shm + 0x1000;
  // unsigned long value0=0, value1=0;

  // for (int i=0; i<10; i++) {
  //   asm volatile("rdcycle %0" : "=r"(start_time));
  //   asm volatile("rdcycle %0" : "=r"(end_time));
  // }
  // printf("host: delta %ld\n", end_time-start_time);

  // asm volatile("rdcycle %0" : "=r"(start_time));
  // value0 = *ptr0;
  // asm volatile("rdcycle %0" : "=r"(end_time));
  // printf("host: read g_shm[0] time %ld\n", end_time-start_time);

  // asm volatile("rdcycle %0" : "=r"(start_time));
  // value0 = *ptr1;
  // asm volatile("rdcycle %0" : "=r"(end_time));
  // printf("host: read g_shm[0x1000] time %ld\n", end_time-start_time);

  // // asm volatile("rdcycle %0" : "=r"(start_time));
  // // value1 = g_shm[0x1000];
  // // asm volatile("rdcycle %0" : "=r"(end_time));
  // // printf("host: read g_shm[0x1000] time %ld\n", end_time-start_time);
  // printf("value0 %lx value1 %lx\n", value0, value1);


  for(int i =0; i< thread_num; ++i)
  {
    pthread_join(threads[i], (void**)0);
  }
  printf("host: after exit the thread\n");
out:
  elf_args_destroy(enclaveFile);
  free(enclaveFile);
  free(threads);
  free(args);

  return 0;
}
