#include "penglai-enclave.h"
#include <stdlib.h>
#include <stdlib.h>
#include <pthread.h>
#include <linux/elf.h>

#define MAGIC_SHM_VALUE 11111
#define MAGIC_RELAY_PAGE_VALUE 22222
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
  int ret = 0, run_result = 0;
  
  struct PLenclave* enclave = malloc(sizeof(struct PLenclave));
  struct enclave_args* params = malloc(sizeof(struct enclave_args));
  PLenclave_init(enclave);
  enclave_args_init(params);

  struct elf_args *enclaveFile = (struct elf_args *)in;

  char str_num[15];
  sprintf(str_num, "test-enclave%d", i);
  strcpy(params->name, str_num);

  // Check the entry point
  if (((struct elf64_hdr *)(enclaveFile->ptr))->e_entry != 0x1000)
  {
    printf("host%d: failed ptr %lx\n", i, (enclaveFile->ptr));
  }

  printf("host%d: PLenclave begin to create\n", i);
    
  if(PLenclave_create(enclave, enclaveFile, params) < 0)
  {
    printf("host:%d: failed to create enclave\n", i);
  }
  else
  {
    while (run_result = PLenclave_run(enclave))
    {
      switch (run_result)
      {
        default:
          printf("[ERROR] host: run_result val is wrong!\n");
      }
    }
    //commented by luxu
    //printf("host: exit enclave is successful \n");
  }
  //commented by luxu
  printf("host%d: PLenclave run is finished \n", i);
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
  memset(args, 0, thread_num * sizeof(struct args));
  memset(threads, 0, thread_num * sizeof(pthread_t));

  struct elf_args* enclaveFile = malloc(sizeof(struct elf_args));
  char* eappfile = argv[1];
  elf_args_init(enclaveFile, eappfile);
  
  if(!elf_valid(enclaveFile))
  {
    printf("error when initializing enclaveFile\n");
    goto out;
  }

  for(int i=0; i< thread_num; i++)
  {
    args[i].in = (void*)enclaveFile;
    args[i].i = i;
    // printf("host%d: elf entry %lx ptr %lx\n", i, ((struct elf64_hdr *)(((struct elf_args *)(args[i].in))->ptr))->e_entry,
    // (((struct elf_args *)(args[i].in))->ptr));
    pthread_create(&threads[i], NULL, create_enclave, (void*)&(args[i]));
  }

  for(int i =0; i< thread_num; ++i)
  {
    pthread_join(threads[i], (void**)0);
  }
  //commented by luxu
  //printf("host: after exit the thread\n");
out:
  elf_args_destroy(enclaveFile);
  free(enclaveFile);
  free(threads);
  free(args);

  return 0;
}
