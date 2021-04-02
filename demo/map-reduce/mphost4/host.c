#include "penglai-enclave.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <fcntl.h>
#include <string.h>
#define THREAD_NUM 4

unsigned long read_cycle()
{
  unsigned long cycle;
  asm volatile("rdcycle %0" : "=r"(cycle));
  return cycle;
}

unsigned long map_start = 0;
unsigned long map_end = 0;
unsigned long reduce_start = 0;
unsigned long reduce_end = 0;

struct args
{
  unsigned long in;
  int i;
  int fd;
  int shmid;
  unsigned long shm_offset;
  unsigned long shm_size;
};

int mm_arg_id[THREAD_NUM];
void * mm_arg[THREAD_NUM];
unsigned long mm_arg_size[THREAD_NUM];

void* create_enclave(void* args0)
{
  struct args *args = (struct args*)args0;
  unsigned long eid = args->in;
  int ii = args->i;
  int ret = 0;
  int fd = args->fd;
  //commented by luxu
  //printf("host:%d:begin create the thread\n", ii);
  struct PLenclave* enclave = malloc(sizeof(struct PLenclave));
  memset(enclave, 0, sizeof(struct PLenclave));
  enclave->fd = fd;
  enclave->user_param.eid = eid;
  enclave->eid = eid;
  // printf("host: fd is %d eid %d\n", enclave->fd, enclave->user_param.eid);
  
  sprintf(enclave->user_param.name, "map%d", ii);
  if(mm_arg_id[ii] > 0 && mm_arg[ii])
    PLenclave_set_mem_arg(enclave, mm_arg_id[ii], 0, mm_arg_size[ii]);
  // It should be atomic read/write
  if(map_start == 0)
    map_start = read_cycle();
  PLenclave_run(enclave);
  map_end = read_cycle();
  free(enclave);

  //commented by luxu
  //printf("host:%d:before exit thread \n",ii);
  pthread_exit((void*)0);
}

void* create_enclave2(void* args0)
{
  struct args *args = (struct args*)args0;
  unsigned long eid = args->in;
  int ii = args->i;
  int ret = 0;
  int fd = args->fd;
  // printf("host2:%d: begin create the thread\n", ii);
  struct PLenclave* enclave = malloc(sizeof(struct PLenclave)); 
  enclave->fd = fd;
  enclave->user_param.eid = eid;
  enclave->eid = eid;

  unsigned long shm_size = 0x10000;
  int shmid = PLenclave_shmget(shm_size);
  void* shm = PLenclave_shmat(shmid, 0);
  memset(shm,0,shm_size);

  enclave->user_param.shmid = shmid;
  enclave->user_param.shm_offset = 0;
  enclave->user_param.shm_size = shm_size;

  // printf("host2: fd is %d eid %d\n", enclave->fd, enclave->user_param.eid);
  sprintf(enclave->user_param.name, "reduce%d", ii);
  // strcpy(enclave->user_param.name, "test");
  PLenclave_set_mem_arg(enclave, 1,0,0);
  // It should be atomic read/write
  if(reduce_start == 0)
    reduce_start = read_cycle();
  PLenclave_run(enclave);
  reduce_end = read_cycle();
  free(enclave);
  // printf("host2:%d: before exit thread\n", ii);
  pthread_exit((void*)0);
}

int main(int argc, char** argv)
{
  if(argc <= 1)
  {
    printf("Please input the enclave ELF file name\n");
  }

  int thread_num = THREAD_NUM;
  if(argc != 3)
  {
    printf("hots: the usage of relay page test: ./srphost relay_page relay_page2\n");
  }

  pthread_t* threads = (pthread_t*)malloc(thread_num * sizeof(pthread_t));
  struct args* args = (struct args*)malloc(thread_num * sizeof(struct args));
  //-----------------------------------
  //Map enclave
  struct elf_args* enclaveFile = malloc(sizeof(struct elf_args));
  char* eappfile = argv[1];
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

  params->type = SHADOW_ENCLAVE;

  if(PLenclave_create(enclave, enclaveFile, params) < 0 )
  {
    printf("host: failed to create enclave\n");
    pthread_exit((void*)0);
  }

  unsigned long eid = enclave->user_param.eid;
  int fd = enclave->fd;

  for(int i=0; i<thread_num; ++i)
  {
    mm_arg_size[i] = 0x1000 * 128;
    mm_arg_id[i] = PLenclave_schrodinger_get(mm_arg_size[i]);
    mm_arg[i] = PLenclave_schrodinger_at(mm_arg_id[i], 0);
    memset(mm_arg[i], 0, mm_arg_size[i]);
    if(mm_arg[i] == (void*)-1)
        printf("PLenclave_schrodinger page get error \n");
  }

  FILE* f = fopen("./input.txt","r");
  char buf[512];
  int offset[THREAD_NUM] = {0,};
  int cnt = 0;
  while(fgets(buf, sizeof(buf), f))
  {
    int map_index = cnt % thread_num;
    // printf("orgin file context %s size %d\n",buf, strlen(buf));
    memcpy(mm_arg[map_index] + offset[map_index], buf, strlen(buf));
    offset[map_index] = offset[map_index] + strlen(buf);
    cnt = cnt + 1;
  }
  fclose(f);

  for(int i=0; i< thread_num; i++)
  {
    args[i].in = eid;
    args[i].i = i;
    args[i].fd = fd;
    pthread_create(&threads[i], NULL, create_enclave, (void*)&(args[i]));
  }
  for(int i =0; i< thread_num; i++)
  {
    pthread_join(threads[i], (void**)0);
  }

  //Reduce enclave
  struct elf_args* enclaveFile2 = malloc(sizeof(struct elf_args));
  char* eappfile2 = argv[2];
  elf_args_init(enclaveFile2, eappfile2);
  
  if(!elf_valid(enclaveFile2))
  {
    printf("error when initializing enclaveFile\n");
    goto out;
  }
  struct PLenclave* enclave2 = malloc(sizeof(struct PLenclave));
  struct enclave_args* params2 = malloc(sizeof(struct enclave_args));
  PLenclave_init(enclave2);
  enclave_args_init(params2);

  params2->type = SHADOW_ENCLAVE;

  if(PLenclave_create(enclave2, enclaveFile2, params2) < 0 )
  {
    printf("host: failed to create enclave\n");
    pthread_exit((void*)0);
  }

  unsigned long eid2 = enclave2->user_param.eid;
  int fd2 = enclave2->fd;
  for(int i=0; i< thread_num; i++)
  {
    args[i].in = eid2;
    args[i].i = i;
    args[i].fd = fd2;
    pthread_create(&threads[i], NULL, create_enclave2, (void*)&(args[i]));
  }

  for(int i =0; i< thread_num; i++)
  {
    pthread_join(threads[i], (void**)0);
  }
  for(int ii =0; ii < thread_num; ii++)
  {
    if(mm_arg_id[ii] > 0)
    {
      PLenclave_schrodinger_dt(mm_arg_id[ii], mm_arg[ii]);
      PLenclave_schrodinger_ctl(mm_arg_id[ii]);
    }
  }
  printf("Run map reduce with optimization: Total time: %ld, number of the mapper %d number of the reducer %d\n", 
          map_end-map_start+reduce_end-reduce_start, THREAD_NUM, THREAD_NUM);
  printf("host: after exit the thread\n");

out:
  elf_args_destroy(enclaveFile);
  free(enclaveFile);
  elf_args_destroy(enclaveFile2);
  free(enclaveFile2);
  free(threads);
  free(args);

  return 0;
}
