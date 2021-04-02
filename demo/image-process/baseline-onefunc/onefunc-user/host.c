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
  struct elf_args* caller_enclaveFile = NULL;
  struct PLenclave* caller_enclave = NULL;
  struct enclave_args* caller_params = NULL;

  int img_size;

  unsigned long start_cycle, mid_cycle, end_cycle;

  if (argc !=3)
  {
    printf("Usage: ./onefunc-user [image_size] image_enclave ...\n");
  }
  debug_printf("Start init image1 enclave\n");

  start_cycle = readcycle();

  img_size = atoi(argv[1]);
  if (img_size<32 || img_size>4096){
	printf("[Image Processing Serverless] Error img size:%d\n", img_size);
	return -1;
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
  printf("[Serverless Onefunc Test] Image Size: %dx%d (x3)\n\trun time:%ld cycles\n",
		  img_size, img_size,
		  mid_cycle-start_cycle, end_cycle-mid_cycle, end_cycle-start_cycle);

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
  PLenclave_shmdt(shmid, shm);

  return 0;
}
