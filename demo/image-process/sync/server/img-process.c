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

#define CMD_RESIZE (1)
#define CMD_CLOSE  (2)

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

int request_index = 0;
unsigned long response[REPEAT_CNT];

int EAPP_ENTRY main()
{
    unsigned long * args;
    EAPP_RESERVE_REG;
    unsigned long type = args[10];
    struct call_enclave_arg_t ret_arg;
    ret_arg.req_vaddr = args[11];
    ret_arg.req_size = args[12];
    ret_arg.resp_vaddr = 0;
    ret_arg.resp_size = 0;
    LOG_DEBUG("img-process server begin to run: %d at %d\n", type, request_index);
    LOG_DEBUG("req_mem_sz: %ld\n",ret_arg.req_size);
    switch(type){
        case CMD_RESIZE:
        {
	        response[request_index++] = rdcycle();
            struct img_resize_arg arg = *((struct img_resize_arg *)ret_arg.req_vaddr);
            sod_img img_in = *((sod_img*)(ret_arg.req_vaddr + sizeof(struct img_resize_arg)));
            img_in.data = ret_arg.req_vaddr + sizeof(sod_img) * 2 + sizeof(struct img_resize_arg);
            LOG_DEBUG("before resize data: %lx\n", img_in.data);
            if(img_in.data == 0){
                LOG_ERROR("Unknown input format\n");
            }else{
                sod_img rz = sod_resize_image(img_in, arg.new_width, arg.new_height);
            }
            break;
        }
	case CMD_CLOSE:
	{
		unsigned long* dst = (unsigned long*)ret_arg.req_vaddr;
		for(int i = 0; i < request_index; ++i){
			dst[i] = response[i];
		}
		request_index = 0;
		break;
	}
        default:
        LOG_ERROR("Unknown command\n");
    }
    LOG_DEBUG("Server return\n");
    SERVER_RETURN(&ret_arg);
}
