#include <sys/random.h>
#include <stdlib.h>
#include <string.h>
// #define LOG_LEVEL DEBUG
#include "eapp.h"
#include "print.h"
#include "ipc_manager.h"
#include "ipc_callarg.h"
#include "log.h"
static char* key_used_bit_map;
static unsigned int allocated_key;
static char* key_assigned_bit_map;
static struct server_key_info dummy_meta_head;
static char initialized = 0;
static long global_server_identifier;
int ipc_manager_init()
{
    key_used_bit_map = (char*)eapp_mmap(NULL, MAX_KEY_NUMBER >> 3);
    key_assigned_bit_map = (char*)eapp_mmap(NULL, MAX_KEY_NUMBER >> 3);
    memset(key_used_bit_map, 0, MAX_KEY_NUMBER >> 3);
    memset(key_assigned_bit_map, 0, MAX_KEY_NUMBER >> 3);
    if(!key_used_bit_map || !key_assigned_bit_map)
    {
        LOG_INFO("failed to allocate metadata\n");
        return -1;
    }
    INIT_LIST_HEAD(&dummy_meta_head.link);
    initialized = 1;
    allocated_key = 0;
    global_server_identifier = 0x1234;// just a magic number.
    return 0;
}

static inline void set_bit_i(char* bitmap, unsigned int i)
{
    bitmap[i >> 3] |= (unsigned char)(128) >> (i % 8);
}

static inline int is_set_bit_i(const char *bitmap, unsigned int i)
{
    return bitmap[i >> 3] & ((unsigned char)(128) >> (i % 8));
}

static inline void clear_bit_i(char *bitmap, unsigned int i)
{
    bitmap[i >> 3] &= ~((unsigned char)(128) >> (i % 8));
}
/**
 * \brief Allocate random keys for server register. 
 * \param num the number of keys to allocate.
 * \param dst the destination address to place the allocated keys. 
 * \ret the identifier of the server, or -1 on failure.
*/
long allocate_keys(unsigned int num, const char* server_name, char* dst)
{
    ssize_t ret = 0;
    unsigned int local_allocated = 0;
    if(num > MAX_KEY_REGISTER_ONCE || num + allocated_key > MAX_KEY_NUMBER) // too many keys.
    {
        return -1;
    }
    struct server_key_info* info = (struct server_key_info*)malloc(sizeof(struct server_key_info));
    if(info == NULL)
    {
        LOG_INFO("malloc metadata failed\n");
        return -1;
    }
    strcpy(info->server_name, server_name);
    info->randoms = malloc(num * sizeof(unsigned int));
    if(info->randoms == NULL)
    {
        LOG_INFO("malloc random buffer failed\n");
        free(info);
        return -1;
    }
    info->assigned = 0;
    info->size = num;
    info->identifier = global_server_identifier++;
    while(local_allocated < num)
    {
        unsigned int * buf = info->randoms + local_allocated;
        // acquire double number of randoms from kernel in case collision.
        ret = getrandom(buf, sizeof(unsigned int)*(num - local_allocated), 0);
        if(ret > 0)
        {
            ret = ret / sizeof(unsigned int);
            ssize_t i = 0;
            for(ssize_t j = ret - 1, count = 0; count < ret; count++)
            {
                if(buf[i] != -1U && !is_set_bit_i(key_used_bit_map, buf[i] % MAX_KEY_NUMBER))
                {
                    set_bit_i(key_used_bit_map, buf[i] % MAX_KEY_NUMBER);
                    i += 1;
                    if(local_allocated + i == num)
                    {
                        break;
                    }
                }
                else
                {
                    // replace the i-th entry with the last unchecked entry.
                    buf[i] = buf[j--];
                }
            }
            local_allocated += i;
        }
        else
        {
            free(info->randoms);
            free(info);
            return -1;
        }
    }
    list_add(&info->link, &dummy_meta_head.link);
    allocated_key += num;
    memcpy(dst, info->randoms, num*sizeof(unsigned int));
    return info->identifier;
}



unsigned int assign_key(const char* server_name)
{
    struct server_key_info *loop_pos;
    int found = 0;
    list_for_each_entry(loop_pos, &(dummy_meta_head.link), link)
    {
        if(!strcmp(server_name, loop_pos->server_name))
        {
            found = 1;
            break;
        }
    }
    if(found)
    {
        if(loop_pos->assigned == loop_pos->size) // all keys of this server are assigned.
        {
            return -1U;
        }
        for(ssize_t i = 0; i < loop_pos->size; i++)
        {
            if(!is_set_bit_i(key_assigned_bit_map, loop_pos->randoms[i] % MAX_KEY_NUMBER))
            {
                set_bit_i(key_assigned_bit_map, loop_pos->randoms[i] % MAX_KEY_NUMBER);
                loop_pos->assigned += 1;
                return loop_pos->randoms[i];
            }
        }
        LOG_ERROR("bug in ipc_manager!\n");
        return -1U;
    }
    else
    {
        LOG_INFO("assign_key: does not find server %s\n", server_name);
        return -1U;
    }
}

int declaim_key(const char * server_name, unsigned int key)
{
    struct server_key_info *loop_pos;
    int found = 0;
    list_for_each_entry(loop_pos, &(dummy_meta_head.link), link)
    {
        if(!strcmp(server_name, loop_pos->server_name))
        {
            found = 1;
            break;
        }
    }
    if(found)
    {
        LOG_DEBUG("found server\n");
        for(ssize_t i = 0; i < loop_pos->size; i++)
        {
            if(loop_pos->randoms[i] == key)
            {
                if(!is_set_bit_i(key_assigned_bit_map, key % MAX_KEY_NUMBER))
                {
                    LOG_ERROR("bug in ipc_manager!\n");
                    return -1;
                }
                else
                {
                    clear_bit_i(key_assigned_bit_map, key % MAX_KEY_NUMBER);
                    loop_pos->assigned --;
                    return 0;
                }
            }
        }
        LOG_DEBUG("did not find key\n");
        return -1;
    }
    else
    {
        LOG_DEBUG("did not find server\n");
        return 0;
    }
}

int server_close(const char *server_name, const long identifier)
{
    struct server_key_info *loop_pos;
    int found = 0;
    list_for_each_entry(loop_pos, &(dummy_meta_head.link), link)
    {
        if(strcmp(server_name, loop_pos->server_name) == 0 && identifier == loop_pos->identifier)
        {
            found = 1;
            break;
        }
    }
    if(found)
    {
        for(ssize_t i = 0; i < loop_pos->size; i++)
        {
            clear_bit_i(key_assigned_bit_map, loop_pos->randoms[i] % MAX_KEY_NUMBER);
            clear_bit_i(key_used_bit_map, loop_pos->randoms[i] % MAX_KEY_NUMBER);
        }
        free(loop_pos->randoms);
        list_del(&loop_pos->link);
        free(loop_pos);
        return 0;
    }
    else
    {
        return -1;
    }
}

int EAPP_ENTRY main()
{
    unsigned long * args;
    EAPP_RESERVE_REG;
    int status = 0;
    unsigned long type = args[10];
    struct call_enclave_arg_t ret_arg;
    ret_arg.req_vaddr = args[11];
    ret_arg.req_size = args[12];
    ret_arg.resp_vaddr = 0;
    ret_arg.resp_size = 0;
    char server_name[MAX_SERVER_NAME_LENGTH];
    if(!initialized)
    {
        status = ipc_manager_init();
        if(status != 0)
        {
            LOG_INFO("init failed");
            ret_arg.resp_val = -1UL;
            SERVER_RETURN(&ret_arg);
        }
    }
    switch(type)
    {
        case IPC_SERVER_REGISTER:
        {
            struct server_register_arg* arg = (struct server_register_arg*)(ret_arg.req_vaddr);
            unsigned int size = arg->size;
            strcpy(server_name, arg->server_name);
            // zero the last byte in case of malicious client.
            server_name[MAX_SERVER_NAME_LENGTH - 1] = '\0';
            LOG_DEBUG("IPC_SERVER_REGISTER: %s", server_name);
            ret_arg.resp_val = allocate_keys(size, server_name, (char*)arg);
            SERVER_RETURN(&ret_arg);
            break;
        }
        case IPC_CLIENT_CONNECT:
        {
            struct client_connect_arg* arg = (struct client_connect_arg*)(ret_arg.req_vaddr);
            ret_arg.resp_val = assign_key(arg->server_name);
            LOG_DEBUG("IPC_CLIENT_CONNECT: assigned key %d\n", (int)ret_arg.resp_val);
            SERVER_RETURN(&ret_arg);
            break;
        }
        case IPC_CLIENT_CLOSE:
        {
            //TODO: in declaim_key, should update the reclaimed key with same regenerate-algorithm
            //TODO: as async-server, in case malicious client.
            struct client_close_arg *arg = (struct client_close_arg*)(ret_arg.req_vaddr);
            LOG_DEBUG("IPC_CLIENT_CLOSE: key %d\n", arg->shm_key);
            ret_arg.resp_val = declaim_key(arg->server_name, arg->shm_key);
            SERVER_RETURN(&ret_arg);
            break;
        }
        case IPC_SERVER_CLOSE:
        {
            struct server_close_arg *arg = (struct server_close_arg*)(ret_arg.req_vaddr);
            LOG_DEBUG("IPC_SERVER_CLOSE: server_name: %s, server_id: %d\n", arg->server_name, arg->identifier);
            ret_arg.resp_val = server_close(arg->server_name, arg->identifier);
            SERVER_RETURN(&ret_arg);
            break;
        }
    }

}
