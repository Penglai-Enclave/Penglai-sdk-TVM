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
#include "log.h"
#include "async_ipc_lib.h"
#include "sod.h"

#define CMD_RESIZE (1)
#define CMD_CLOSE (2)
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


void handle_request(int cmd, void*request)
{
    switch (cmd){
        case CMD_RESIZE:
        {
            struct img_resize_arg* img_resize_arg = (struct img_resize_arg*)request;
            sod_img img_in = *((sod_img*)(request + sizeof(struct img_resize_arg)));
            img_in.data = request + sizeof(struct img_resize_arg) + 2*sizeof(sod_img);
            sod_img rz = sod_resize_image(img_in, img_resize_arg->new_width, img_resize_arg->new_height);
            LOG_DEBUG("After resize data: %lx\n", rz.data);
            async_ret(request, 0, 0);
            break;
        }
        default:
        {
            LOG_WARNING("Invalid request type\n");
            async_ret(request, -1 , 0);
        }
    }
    LOG_DEBUG("After handle_request\n");
}

int EAPP_ENTRY main()
{
    unsigned long * args;
    EAPP_RESERVE_REG;
    LOG_DEBUG("async img-process server starting\n");
    unsigned int* keys;
    unsigned long server_identifier;
    void* shared_memory_regions[1] = {NULL};
    void* reqp;
    keys = server_register("img-process", 1, &server_identifier);
    if(keys == NULL){
        LOG_ERROR("Register img-process failed\n");
        EAPP_RETURN(-1);
    }
    LOG_DEBUG("async img-process register succeeded\n");
    while(1){
        if(!shared_memory_regions[0]){
            shared_memory_regions[0] = eapp_shmat(keys[0]);
            if(!shared_memory_regions[0]){
                // delay some time.
                for(int i = 0; i <= 1e5; ++i);
            }
        }else{
            break;
        }
    }
    while(1){
        int cmd = async_server_polling_request(shared_memory_regions[0], &reqp);
        while(cmd == -1){
            cmd = async_server_polling_request(shared_memory_regions[0], &reqp);
        }
        LOG_DEBUG("img-processing server cmd: %d\n", cmd);
        if(cmd != CMD_CLOSE){
            handle_request(cmd, reqp);
        }else{
            async_ret(reqp, 0, 0);
            break;
        }
    }
    server_close("img-process", server_identifier);
    EAPP_RETURN(0);
}
