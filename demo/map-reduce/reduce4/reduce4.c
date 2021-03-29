#include "eapp.h"
#include "print.h"
#include <stdlib.h>
#include "util.h"

#define PAGE_SIZE 4096
#define MAP_NUM 4
#define REDUCE_PAGE_NUMBER (64/MAP_NUM)


int reduce(Keyvalue *reduce_keyvalue, Keyvalue *keyvalue)
{
    while(1)
    {
        int j = 0;

        if (!strcmp(reduce_keyvalue->key, "-end-"))
            break;

        while(1)
        {
            if(!strcmp(keyvalue[j].key, "-end-"))
            {
                memcpy(keyvalue[j].key, reduce_keyvalue->key, 10);
                keyvalue[j].value =  reduce_keyvalue->value;
                memcpy(keyvalue[j+1].key, "-end-", sizeof("-end-"));
                break;
            }
            else
            {
                if(!strcmp(keyvalue[j].key, reduce_keyvalue->key))
                {
                    keyvalue[j].value += 1;
                    break;
                }
                else
                    j++;  
            }            
        }
        reduce_keyvalue = (Keyvalue *)reduce_keyvalue + 1;
    }

    return 0;
}

int doreduce(unsigned long * args, int map_num)
{
    char * shm;
    Keyvalue *merge_data;
    Keyvalue ** reduce_keyvalue;
    reduce_keyvalue = (Keyvalue **)malloc(map_num * sizeof(Keyvalue *));
    shm = (char *)args[13];
    merge_data = (Keyvalue *)args[10];
    for (int i=0; i < map_num; i++)
    {
        reduce_keyvalue[i] = (Keyvalue *)(shm + REDUCE_PAGE_NUMBER * i * PAGE_SIZE);
    }
    Keyvalue *keyvalue = merge_data;
    memcpy(keyvalue->key, "-end-", sizeof("-end-"));
    for(int i = 0; i<map_num; i++)
        reduce(reduce_keyvalue[i], keyvalue);
    while(1)
    {
        char buf[50];
        if (!strcmp(merge_data->key, "-end-"))
            break;
        sprintf(buf, "%s:%d\n",merge_data->key,merge_data->value);
        // eapp_print(buf);
        merge_data = merge_data + 1;
    }
    EAPP_RETURN(0);
}
int EAPP_ENTRY main(){
  unsigned long * args;
  EAPP_RESERVE_REG;
  doreduce(args, MAP_NUM);
}