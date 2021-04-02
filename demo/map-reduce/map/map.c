#include "eapp.h"
#include "print.h"
#include <stdlib.h>
#include "util.h"

//page size in the RISCV
#define PAGE_SIZE 4096
#define REDUCE_OFFSET 16
#define MAP_NUM 1
#define REDUCE_NUM 1
#define REDUCE_PAGE_NUMBER (64/MAP_NUM)
#define FPGA_PENALTY 10000000


unsigned int ELFHash(char *str, int num)
{
    unsigned int hash = 0;
    unsigned int x = 0;

    for (int i = 0; i < num; i++)
    {
        hash = (hash << 4) + (*str++);
        if ((x = hash & 0xF0000000L) != 0)
        {
            for(int j=0; j < FPGA_PENALTY; j++)
            {
                hash ^= (x >> 24);
                hash &= ~x;
            }
        }
    }
    return (hash & 0x7FFFFFFF);
}

int map(char *f, Keyvalue** keyvalue, int reduce_num)
{
    char *ptr_begin;
    char *word_begin;
    word_begin = NULL;

    for (ptr_begin = f; *ptr_begin != 0; ++ptr_begin) {
        if ((word_begin ==NULL) && ( isspace(*ptr_begin) || (*ptr_begin == '\n')))
            continue;
        if (word_begin == NULL)
            word_begin = ptr_begin;
        if ( isspace(*ptr_begin) || (*ptr_begin == '\n'))
        {
            unsigned int hash = ELFHash(word_begin, ptr_begin - word_begin);
            int n = hash % reduce_num;
            memcpy(keyvalue[n]->key, word_begin, ptr_begin - word_begin);
            // eapp_print("intermediate entry %d key is %s\n", n, keyvalue[n]->key);
            keyvalue[n]->value = 1;
            word_begin = NULL;
            keyvalue[n] = keyvalue[n] + 1;
        }
    }

    for(int i = 0; i < reduce_num; i++)
        memcpy(keyvalue[i]->key, "-end-", sizeof("-end-"));

    return 0;
}

/*
 * reduce_num @ the number of reduce enclave
 * relay_page memory layout:
 * | origin data |map 1-1|map 1-2|map 2-1|map 2-2|
 */
int domap(unsigned long *args, int reduce_num)
{
    // eapp_print("begin domap \n");
    char *map_data;
    int map_index;
    unsigned long shm, shm_size;
    Keyvalue ** reduce_keyvalue;

    // Get the relay page address
    shm = args[13];
    shm_size = args[14];
    map_index = args[12] % MAP_NUM;
    map_data = (char *)shm ;
    split_mem_region(shm, shm_size, shm + REDUCE_OFFSET * PAGE_SIZE);
    
    // Divide relay page into reduce_num region, and each region contain several keyvalue pairs 
    reduce_keyvalue = (Keyvalue **)malloc(reduce_num * sizeof(Keyvalue *));
    for (int i=0; i < reduce_num; i++)
    {
        // REDUCE_OFFSET * PAGE_SZE is stored the original data, and map_index * reduce_num is the transfer relay page to the reducer enclave
        reduce_keyvalue[i] = (Keyvalue *)(shm + REDUCE_OFFSET * PAGE_SIZE + i * REDUCE_PAGE_NUMBER * PAGE_SIZE);
        // Split the relay page into sub relat page and treansfer them to different reduce enclaves
        split_mem_region(shm + (REDUCE_OFFSET + REDUCE_PAGE_NUMBER * i) * PAGE_SIZE, shm_size - REDUCE_OFFSET * PAGE_SIZE - REDUCE_PAGE_NUMBER * i * PAGE_SIZE, 
                        shm + (REDUCE_OFFSET + REDUCE_PAGE_NUMBER *(i + 1 )) * PAGE_SIZE);
    }

    map(map_data, reduce_keyvalue, reduce_num);
    char enclave_name[16];
    sprintf(enclave_name, "reduce%d", map_index);
    struct call_enclave_arg_t call_arg;
    for (int i = 0; i < reduce_num; i++)
    {
        sprintf(enclave_name, "reduce%d", i);
        call_arg.req_vaddr = (unsigned long)(shm + (REDUCE_OFFSET + REDUCE_PAGE_NUMBER *i) * PAGE_SIZE);
        call_arg.req_size = PAGE_SIZE * REDUCE_PAGE_NUMBER;
        asyn_enclave_call(enclave_name,  &call_arg);
    }
    // eapp_print("end domap\n");
    EAPP_RETURN(0);
}

int EAPP_ENTRY main(){
  unsigned long * args;
  EAPP_RESERVE_REG;
  domap(args, REDUCE_NUM);
}