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
#include <stdlib.h>

#include "log.h"
#include "eapp.h"
#include "print.h"
#include "sod.h"
#include "async_ipc_lib.h"

#define CMD_RESIZE (1)
#define CMD_CLOSE  (2)
static inline unsigned long rdcycle(void)
{
    unsigned long ret;
    asm volatile ("rdcycle %0" : "=r"(ret));
    return ret;
}

struct img_resize_arg{
    int new_width;
    int new_height;  
};
unsigned long start_cycle[100], response_cycle[100], end_cycle[100];
int EAPP_ENTRY main()
{
    unsigned long * args;
    EAPP_RESERVE_REG;
    void * shm = args[10];
    unsigned long shm_sz = args[11];
    LOG_DEBUG("Async Image-Process-Client begin to run\n");
    if(!shm || shm_sz < 0x1000){
        LOG_ERROR("Cannot get valid image input\b");
        EAPP_RETURN(-1);
    }
    sod_img img_in = *((sod_img*)shm);
    img_in.data = (float*)(shm + sizeof(sod_img)*2);
    void* mem;
    unsigned int key;
    mem = connect_to_server("img-process", shm_sz, &key);
    if(mem == NULL){
        LOG_ERROR("Failed to connect to img-process server\n");
        EAPP_RETURN(-1);
    }
    void* result;
    unsigned int result_sz;
    for(int i = 0; i < 100; ++i){
       struct img_resize_arg* img_resize_arg = (struct img_resize_arg*)async_client_get_request_mem(mem);
        sod_copy_image_inplace(img_in, (void*)img_resize_arg + sizeof(struct img_resize_arg));
        img_resize_arg->new_width = img_in.w / 2;
        img_resize_arg->new_height = img_in.h / 2;
        start_cycle[i] = rdcycle();
        async_submit_request(mem, CMD_RESIZE);
        response_cycle[i] = rdcycle();
        int ret = async_client_polling_ret(mem, &result, &result_sz);
        end_cycle[i] = rdcycle();
        if(ret != 0){
            LOG_ERROR("async ipc polling failed, may server failed to process\n");
        }
}
    async_call(mem, CMD_CLOSE, &result, &result_sz);
    unsigned long response_time = 0, processing_time = 0;
    close_with_server("img-process", key);
    LOG_DEBUG("After close_with_server\n");
    for(int i = 0; i < 100; ++i){
        response_time += response_cycle[i] - start_cycle[i];
        processing_time += end_cycle[i] - response_cycle[i];
    }
    LOG_INFO("Async Image processing: response time: %ld, process time: %ld\n", response_time/100, processing_time/100);
    EAPP_RETURN(0);
}
