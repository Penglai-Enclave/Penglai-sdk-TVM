#include "penglai-enclave.h"
#include <stdlib.h>
#include <string.h>
#include "sod.h"

//#define EAPP_DEBUG_PRINT
#ifdef EAPP_DEBUG_PRINT
#define debug_printf(...) printf(__VA_ARGS__)
#else
#define debug_printf(...) 
#endif
unsigned long readcycle(void){
	unsigned long ret;
	asm volatile(
		     "rdcycle a1\n\t"
		     "mv %0,a1\n\t"
	:"=r"(ret));
	return ret;
}

int main(int argc, char** argv)
{
  struct elf_args* image1_enclaveFile = NULL;
  struct PLenclave* image1_enclave = NULL;
  struct enclave_args* image1_params = NULL;

  struct elf_args* image2_enclaveFile = NULL;
  struct PLenclave* image2_enclave = NULL;
  struct enclave_args* image2_params = NULL;

  struct elf_args* image3_enclaveFile = NULL;
  struct PLenclave* image3_enclave = NULL;
  struct enclave_args* image3_params = NULL;

  struct elf_args* caller_enclaveFile = NULL;
  struct PLenclave* caller_enclave = NULL;
  struct enclave_args* caller_params = NULL;

  int img_size;

  unsigned long start_cycle, mid_cycle, end_cycle;

  if(argc < 5)
  {
    printf("Usage: ./serverless-user [image_size] entry_enclave ...\n");
  }
  debug_printf("Start init image1 enclave\n");

  start_cycle = readcycle();

  img_size = atoi(argv[1]);
  if (img_size<32 || img_size>4096){
	printf("[Image Processing Serverless] Error img size:%d\n", img_size);
	return -1;
  }

server:
  image1_enclaveFile = malloc(sizeof(struct elf_args));
  char *image1_eappfile = argv[3];
  elf_args_init(image1_enclaveFile, image1_eappfile);
  
  if(!elf_valid(image1_enclaveFile))
  {
    printf("host:error when initializing server_enclaveFile\n");
    goto out;
  }

  image1_enclave = malloc(sizeof(struct PLenclave));
  image1_params = malloc(sizeof(struct enclave_args));
  enclave_args_init(image1_params);
  PLenclave_init(image1_enclave);

  strcpy(image1_params->name, image1_eappfile);
  image1_params->type = SERVER_ENCLAVE;

  if(PLenclave_create(image1_enclave, image1_enclaveFile, image1_params) < 0 )
  {
    printf("host:failed to create image1_enclave\n");
    goto out;
  }

//  if(argc == 3)
//    goto caller;

image2:
  debug_printf("Start init image2 enclave\n");
  image2_enclaveFile = malloc(sizeof(struct elf_args));
  char *image2_eappfile = argv[4];
  elf_args_init(image2_enclaveFile, image2_eappfile);
  
  if(!elf_valid(image2_enclaveFile))
  {
    printf("host:error when initializing image2_enclaveFile\n");
    goto out;
  }

  image2_enclave = malloc(sizeof(struct PLenclave));
  image2_params = malloc(sizeof(struct enclave_args));
  enclave_args_init(image2_params);
  PLenclave_init(image2_enclave);
  strcpy(image2_params->name, image2_eappfile);
  image2_params->type = SERVER_ENCLAVE;

  if(PLenclave_create(image2_enclave, image2_enclaveFile, image2_params) < 0 )
  {
    printf("host:failed to create image2_enclave\n");
    goto out;
  }

image3:
  debug_printf("Start init image3 enclave\n");
  image3_enclaveFile = malloc(sizeof(struct elf_args));
  char *image3_eappfile = argv[5];
  elf_args_init(image3_enclaveFile, image3_eappfile);
  
  if(!elf_valid(image3_enclaveFile))
  {
    printf("host:error when initializing image3_enclaveFile\n");
    goto out;
  }

  image3_enclave = malloc(sizeof(struct PLenclave));
  image3_params = malloc(sizeof(struct enclave_args));
  enclave_args_init(image3_params);
  PLenclave_init(image3_enclave);
  strcpy(image3_params->name, image3_eappfile);
  image3_params->type = SERVER_ENCLAVE;

  if(PLenclave_create(image3_enclave, image3_enclaveFile, image3_params) < 0 )
  {
    printf("host:failed to create image3_enclave\n");
    goto out;
  }

caller:
  debug_printf("Start init caller enclave\n");
  caller_enclaveFile = malloc(sizeof(struct elf_args));
  char *caller_eappfile = argv[2];
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
  //void* shm = PLenclave_shmget(caller_enclave, 0, shm_size);
  unsigned long shmid;
  void* shm;
  shmid = PLenclave_shmget(shm_size);
  debug_printf("After shmget");
  shm = PLenclave_shmat(shmid, 0);
  debug_printf("After shmat");
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
  debug_printf("Ready to run serverless enclaves\n");
  mid_cycle = readcycle();
  PLenclave_run(caller_enclave);
  end_cycle = readcycle();
  printf("[Serverless Test] Image Size: %dx%d (x3)\n\trun time:%ld cycles\n",
		  img_size, img_size, end_cycle-mid_cycle);

out:
  if(image1_enclaveFile)
  {
    elf_args_destroy(image1_enclaveFile);
    free(image1_enclaveFile);
  }
  if(image1_enclave)
  {
    PLenclave_destroy(image1_enclave);
    free(image1_enclave);
  }
  if(image1_params)
  {
    free(image1_params);
  }
  if(image2_enclaveFile)
  {
    elf_args_destroy(image2_enclaveFile);
    free(image2_enclaveFile);
  }
  if(image2_enclave)
  {
    PLenclave_destroy(image2_enclave);
    free(image2_enclave);
  }
  if(image2_params)
  {
    free(image2_params);
  }
  if(image3_enclaveFile)
  {
    elf_args_destroy(image3_enclaveFile);
    free(image3_enclaveFile);
  }
  if(image3_enclave)
  {
    PLenclave_destroy(image3_enclave);
    free(image3_enclave);
  }
  if(image3_params)
  {
    free(image3_params);
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
  PLenclave_shmdt(shmid, shm);

  return 0;
}
