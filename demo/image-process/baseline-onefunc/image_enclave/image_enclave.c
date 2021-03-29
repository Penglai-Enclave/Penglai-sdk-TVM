/*
 * Entry of Image Processing Serverless Application, for Penglai-Enclave
 * */
#include <string.h>
#include <stdio.h>
#include <eapp.h>
#include <print.h>
#include "sod.h"

#ifdef EAPP_DEBUG_PRINT
#define eapp_debug_print eapp_print
#else
void eapp_empty_print(const char*s, ...){}
#define eapp_debug_print eapp_empty_print
#endif

int EAPP_ENTRY main(){
  unsigned long * args;
  EAPP_RESERVE_REG;
  int* shm = (int*)args[10];
  unsigned long shm_size = args[11];

  eapp_debug_print("[Serverless] Entry_enclave begin to run\n");
  if (!shm || shm_size<0x1000){
  	eapp_debug_print("[Serverless] Error! Entry_enclave can not got shared memory (input)\n");
  	EAPP_RETURN(-1);
  }

  int run_server1 = 1;
  char server_name[16];
  strcpy(server_name, "placeholder");
#if 0
  unsigned long server_handle = acquire_enclave(server_name);
  if(server_handle == -1UL)
  {
    EAPP_RETURN(-1UL);
  }
#endif

  unsigned long arg0 = 0x19960000UL;
  unsigned long size = shm_size; //8*4*4096;
  int *nums = mmap(NULL, size);
  memset(nums, 0, size);
  sod_img imgIn = *((sod_img*)shm);
  imgIn.data = shm + sizeof(sod_img)*2;
  eapp_debug_print("[@%s] recover imgIn from caller imgIn.w(%d), imgIn.h(%d), imgIn.c(%d), imgIn.data(%x), shm(%x)\n", __func__,
			imgIn.w, imgIn.h, imgIn.c, (unsigned long) imgIn.data, (unsigned long) shm);
  //sod_img imgIn = 
  sod_copy_image_inplace(imgIn ,nums) ;//sod_make_image_inplace(64,64,3, nums);

  struct call_enclave_arg_t call_arg;
  call_arg.req_arg = arg0;
  call_arg.req_vaddr = nums;
  call_arg.req_size = size;
#if 0
  call_enclave(server_handle, &call_arg);
#endif

  /* Resize */
  int newWidth  = imgIn.w / 2;
  int newHeight = imgIn.h / 2;
  eapp_debug_print("[@%s] begin resize img\n", __func__);
  sod_img rz = sod_resize_image(imgIn, newWidth, newHeight);
  eapp_debug_print("[@%s] after resize img\n", __func__);

  /* Rotate */
  eapp_debug_print("[@%s] begin rotate img\n", __func__);
  sod_img rot = sod_rotate_image(rz, 180.0);
  eapp_debug_print("[@%s] after rotate img\n", __func__);
  
  /* Erode */
  eapp_debug_print("[@%s] begin Erode img\n", __func__);
  sod_img binImg = sod_binarize_image(imgIn, 0);
  sod_img erodeImg = sod_erode_image(binImg, 5);
  eapp_debug_print("[@%s] after Erode img\n", __func__);

  if(call_arg.req_vaddr)
  {
    unsigned long sum = 0;
    //nums = (int*)call_arg.req_vaddr;
#if 0
    for(int i=0; i<size/sizeof(int); ++i)
    {
      sum += nums[i];
    }
#endif
    eapp_debug_print("caller: read req_vaddr after calling server:0x%lx\n", sum);
    //imgIn = *((sod_img*)nums);
    //imgIn.data = nums + sizeof(sod_img)*2;
    //sod_copy_image_inplace(imgIn, shm);
    sod_copy_image_inplace(erodeImg, shm);
  }
  
  sod_free_image(erodeImg);
  sod_free_image(rot);
  sod_free_image(rz);

  EAPP_RETURN(0);
}
