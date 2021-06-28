#include "penglai-enclave.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char**argv){
    if(argc != 4 && argc != 5){
        printf("Usage: ./psahost psa_client psa_server filesystem | ./psahost psa_client psa_server filesystem");
        exit(0);
    }
    struct elf_args *server_enclaveFile = NULL;
    struct PLenclave *server_enclave = NULL;
    struct enclave_args *server_params = NULL;
    struct elf_args *server_enclaveFile2 = NULL;
    struct PLenclave *server_enclave2 = NULL;
    struct enclave_args *server_params2 = NULL;
    struct elf_args *caller_enclaveFile = NULL;
    struct PLenclave *caller_enclave = NULL;
    struct enclave_args *caller_params = NULL;
    struct elf_args *server_enclaveFile3 = NULL;
    struct PLenclave *server_enclave3 = NULL;
    struct enclave_args *server_params3 = NULL;


server:
    server_enclaveFile = malloc(sizeof(struct elf_args));
    char* server_eappfile = argv[2];
    elf_args_init(server_enclaveFile,server_eappfile);
    if(!elf_valid(server_eappfile)){
        printf("host: error when initializing server_enclaveFile");
        goto out1;
    }
    server_enclave = malloc(sizeof(struct PLenclave));
    PLenclave_init(server_enclave);
    server_params = malloc(sizeof(struct enclave_args));
    enclave_args_init(server_params);
    strcpy(server_params->name,"psa_server");
    server_params->type = SERVER_ENCLAVE;

    if(PLenclave_create(server_enclave,server_enclaveFile,server_params) < 0){
        printf("host: failed to create server_enclave\n");
        goto out1;
    }
server2:
    server_enclaveFile2 = malloc(sizeof(struct elf_args));
    char* server_eappfile2 = argv[3];
    elf_args_init(server_enclaveFile2,server_eappfile2);
    if(!elf_valid(server_eappfile2)){
        printf("host: error when initializing server_enclaveFile");
        goto out1;
    }
    server_enclave2 = malloc(sizeof(struct PLenclave));
    PLenclave_init(server_enclave2);
    server_params2 = malloc(sizeof(struct enclave_args));
    enclave_args_init(server_params2);
    strcpy(server_params2->name,"filesystem");
    server_params2->type = SERVER_ENCLAVE;

    if(PLenclave_create(server_enclave2,server_enclaveFile2,server_params2) < 0){
        printf("host: failed to create server_enclave\n");
        goto out1;
    }
    if (argc == 5)
    {
  server3:
      server_enclaveFile3 = malloc(sizeof(struct elf_args));
      char* server_eappfile3 = argv[4];
      elf_args_init(server_enclaveFile3,server_eappfile3);
      if(!elf_valid(server_eappfile3)){
          printf("host: error when initializing server_enclaveFile");
          goto out1;
      }
      server_enclave3 = malloc(sizeof(struct PLenclave));
      PLenclave_init(server_enclave3);
      server_params3 = malloc(sizeof(struct enclave_args));
      enclave_args_init(server_params3);
      strcpy(server_params3->name,"persistency");
      server_params3->type = SERVER_ENCLAVE;
      int shm_id = PLenclave_shmget(1024 * 128);
      printf("host: shm_id: %d\n",shm_id);
      PLenclave_fs_persistency_init(shm_id);
      server_params3->shmid = shm_id;
      server_params3->shm_offset = 0;
      server_params3->shm_size = 1024 * 128;
      if(PLenclave_create(server_enclave3,server_enclaveFile3,server_params3) < 0){
          printf("host: failed to create server_enclave\n");
          goto out1;
      }
    }
caller:
    caller_enclaveFile = malloc(sizeof(struct elf_args));
    char *caller_eappfile = argv[1];
    elf_args_init(caller_enclaveFile, caller_eappfile);
  
    if(!elf_valid(caller_enclaveFile))
    {
      printf("host:error when initializing caller_enclaveFile\n");
      goto out1;
    }

    caller_enclave = malloc(sizeof(struct PLenclave));
    PLenclave_init(caller_enclave);
    caller_params = malloc(sizeof(struct enclave_args));
    enclave_args_init(caller_params);

    if(PLenclave_create(caller_enclave, caller_enclaveFile, caller_params) < 0 )
    {
      printf("host: failed to create caller_enclave\n");
      goto out1;
    }
    PLenclave_run(caller_enclave);

out1:
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
if(server_enclaveFile2)
  {
    elf_args_destroy(server_enclaveFile2);
    free(server_enclaveFile2);
  }
  if(server_enclave2)
  {
    PLenclave_destroy(server_enclave2);
    free(server_enclave2);
  }
  if(server_params2)
  {
    free(server_params2);
  }
  if (argc ==5)
  {
    if(server_enclaveFile3)
    {
      elf_args_destroy(server_enclaveFile3);
      free(server_enclaveFile3);
    }
    if(server_enclave3)
    {
      PLenclave_destroy(server_enclave3);
      free(server_enclave3);
    }
    if(server_params3)
    {
      free(server_params3);
    }
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

  return 0;

}