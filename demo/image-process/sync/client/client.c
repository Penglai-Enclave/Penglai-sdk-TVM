/*
 * Programming introduction with the SOD Embedded Image Processing API.
 * Copyright (C) PixLab | Symisc Systems, https://sod.pixlab.io
 */
/*
* Compile this file together with the SOD embedded source code to generate
* the executable. For example:
*
*  gcc sod.c resize_image.c -lm -Ofast -march=native -Wall -std=c99 -o sod_img_proc
*  
* Under Microsoft Visual Studio (>= 2015), just drop `sod.c` and its accompanying
* header files on your source tree and you're done. If you have any trouble
* integrating SOD in your project, please submit a support request at:
* https://sod.pixlab.io/support.html
*/
/*
* This simple program is a quick introduction on how to embed and start
* experimenting with SOD without having to do a lot of tedious
* reading and configuration.
*
* Make sure you have the latest release of SOD from:
*  https://pixlab.io/downloads
* The SOD Embedded C/C++ documentation is available at:
*  https://sod.pixlab.io/api.html
*/
#define LOG_LEVEL INFO
#include <string.h>
#include "eapp.h"
#include "sod.h"
#include "print.h"
#include "log.h"
#include "async_ipc_lib.h"
#define CMD_RESIZE (1)
#define CMD_CLOSE (2)

#define REPEAT_CNT (100)

static inline unsigned long rdcycle(void)
{
    unsigned long ret;
    asm volatile("rdcycle %0"
                 : "=r"(ret));
    return ret;
}

struct img_resize_arg{
    int new_width;
    int new_height;
};

unsigned long start_time[REPEAT_CNT], end_time[REPEAT_CNT];

int EAPP_ENTRY main()
{
    unsigned long * args;
    EAPP_RESERVE_REG;
    int*shm = (int*)args[10];
    unsigned long shm_size = args[11];
    LOG_DEBUG("[Sync Image-Process-Client begin to run\n");
    if(!shm || shm_size < 0x1000){
        LOG_ERROR("Cannot get valid image input\n");
        EAPP_RETURN(-1);
    }
    char server_name[16];
    strcpy(server_name, "img-process");
    unsigned long server_handle = acquire_enclave(server_name);
    if(server_handle == -1UL){
        LOG_ERROR("Cannot acquire server enclave handle\n");
        EAPP_RETURN(-1);
    }
    unsigned long param_mem_sz = shm_size;
    LOG_DEBUG("mem_size: %d\n", param_mem_sz);
    void* param_mem = eapp_mmap(NULL, param_mem_sz);
    memset(param_mem, 0, param_mem_sz);
    sod_img image_in = *((sod_img*)shm);
    image_in.data = (float*)((void*)shm + sizeof(sod_img)*2);
    struct call_enclave_arg_t call_arg;
    unsigned long ret = 0;
    for(int i = 0; i < REPEAT_CNT; ++i){
    	sod_copy_image_inplace(image_in, param_mem + sizeof(struct img_resize_arg)); //deep copy
   	struct img_resize_arg* resize_arg = (struct img_resize_arg*)param_mem;
    	resize_arg->new_width = image_in.w / 2;
    	resize_arg->new_height = image_in.h / 2;
    	call_arg.req_arg = CMD_RESIZE;
    	call_arg.req_vaddr = param_mem;
    	call_arg.req_size = param_mem_sz;
	start_time[i] = rdcycle();
	ret = call_enclave(server_handle, &call_arg);
	end_time[i] = rdcycle();
    	if(ret != 0){
        	LOG_ERROR("call img-process failed\n");
		eapp_unmap(param_mem, param_mem_sz);
        	EAPP_RETURN(-1);
    	}
	param_mem = call_arg.req_vaddr;
    }
    call_arg.req_arg = CMD_CLOSE;
    call_arg.req_vaddr = param_mem;
    call_arg.req_size = param_mem_sz;
    ret = call_enclave(server_handle, &call_arg);
    if(ret != 0){
        LOG_ERROR("call img-process failed\n");
	eapp_unmap(param_mem, param_mem_sz);
        EAPP_RETURN(-1);
    }
    param_mem = call_arg.req_vaddr;
    unsigned long* response_time = (unsigned long*)param_mem;
    unsigned long response = 0, processing = 0;
    for(int i = 0; i < REPEAT_CNT; ++i){
	    response += response_time[i] - start_time[i];
	    processing += end_time[i] - response_time[i];
    }
    eapp_print("Sync image processing: response time: %ld, process time: %ld\n",response/REPEAT_CNT, processing/REPEAT_CNT);
    eapp_unmap(param_mem, param_mem_sz);
    EAPP_RETURN(0);
}
