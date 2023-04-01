#ifndef __IPC_MANAGER__
#include "list.h"
#define MAX_KEY_NUMBER              (4096*8)
#define MAX_KEY_REGISTER_ONCE       (512)
#define MAX_SERVER_NAME_LENGTH      64
struct server_key_info 
{
    char server_name[MAX_SERVER_NAME_LENGTH];
    ssize_t size;
    ssize_t assigned;
    struct list_head link;
    long identifier;
    unsigned int *randoms;
};

#define __IPC_MANAGER__
#endif