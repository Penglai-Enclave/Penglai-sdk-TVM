#include "penglai-enclave.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
  struct elf_args* server_enclaveFile = NULL;
  struct PLenclave* server_enclave = NULL;
  struct enclave_args* server_params = NULL;
  struct elf_args* caller_enclaveFile = NULL;
  struct PLenclave* caller_enclave = NULL;
  struct enclave_args* caller_params = NULL;
  unsigned long shm_size = 0;
  void* shm = NULL;
  int shmid = 0;
  if(argc < 4)
  {
    printf("Usage: ./test-caller name_of_caller name_of_server shm_size(MB)\n");
    goto out;
  }

  //shared memory
  shm_size = atoi(argv[3]);
  if(shm_size == 0)
  {
    goto server;
  }
  if(shm_size > 64)
  {
    printf("shm_size too large!\n");
    goto out;
  }
  shm_size = 1024 * 1024 * shm_size;
  shmid = PLenclave_shmget(shm_size);
  shm = PLenclave_shmat(shmid, 0);
  if(shm == (void*)-1)
  {
    printf("failed to set shm!\n");
    goto out;
  }

server:
  server_enclaveFile = malloc(sizeof(struct elf_args));
  char *server_eappfile = argv[2];
  elf_args_init(server_enclaveFile, server_eappfile);

  if(!elf_valid(server_enclaveFile))
  {
    printf("host:error when initializing server_enclaveFile\n");
    goto out;
  }

  server_enclave = malloc(sizeof(struct PLenclave));
  server_params = malloc(sizeof(struct enclave_args));
  PLenclave_init(server_enclave);
  enclave_args_init(server_params);
  strcpy(server_params->name, "test-server");
  server_params->type = SERVER_ENCLAVE;

  server_params->shmid = shmid;
  server_params->shm_offset = 0;
  server_params->shm_size = shm_size;

  if(PLenclave_create(server_enclave, server_enclaveFile, server_params) < 0)
  {
    printf("host:failed to create server_enclave\n");
    goto out;
  }

caller:
  caller_enclaveFile = malloc(sizeof(struct elf_args));
  char *caller_eappfile = argv[1];
  elf_args_init(caller_enclaveFile, caller_eappfile);
  
  if(!elf_valid(caller_enclaveFile))
  {
    printf("host:error when initializing caller_enclaveFile\n");
    goto out;
  }

  caller_enclave = malloc(sizeof(struct PLenclave));
  caller_params = malloc(sizeof(struct enclave_args));
  PLenclave_init(caller_enclave);
  enclave_args_init(caller_params);

  caller_params->shmid = shmid;
  caller_params->shm_offset = 0;
  caller_params->shm_size = shm_size;

  if(PLenclave_create(caller_enclave, caller_enclaveFile, caller_params) < 0 )
  {
    printf("host: failed to create caller_enclave\n");
    goto out;
  }

  //printf("host is calling caller_enclave\n");
  unsigned long IPC0_start;
  asm volatile("rdcycle %0" : "=r"(IPC0_start));

  PLenclave_run(caller_enclave);

  printf("[TEST-BASELINE] host-enclave IPC cost %ld cycles for 0x%lx bytes.\n", caller_enclave->user_param.retval - IPC0_start, shm_size);

out:
  if(server_enclaveFile)
  {
    elf_args_destroy(server_enclaveFile);
    free(server_enclaveFile);
  }
  if(server_enclave)
  {
    PLenclave_destroy(server_enclave);
    free(server_enclave);
  }
  if(server_params)
  {
    free(server_params);
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

  if(shm != (void*)-1 &&  shm != NULL && shm_size >= 0)
  {
    PLenclave_shmdt(shmid, shm);
    PLenclave_shmctl(shmid);
  }

  return 0;
}
