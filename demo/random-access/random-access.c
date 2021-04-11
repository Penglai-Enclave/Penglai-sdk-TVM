#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_ADDR (512*1024*1024)
#define loop 10000


int main()
{
	char* addr = malloc(MAX_ADDR);
    srand((unsigned)time(NULL));
    for (int i=0; i<loop; i++)
    {
        unsigned long r_addr = (unsigned long)(rand()%loop)*MAX_ADDR/loop;
        addr[r_addr] = 'c';
    }
	return 0;
}
