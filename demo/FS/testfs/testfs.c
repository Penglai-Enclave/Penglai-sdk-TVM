#include "eapp.h"
#include "print.h"
#include <string.h>
#include <fcntl.h>
#include "fscallargs.h"
#include <stdio.h>
#include<sys/stat.h>
#include<unistd.h>

int EAPP_ENTRY main(){
    unsigned long* args;
    EAPP_RESERVE_REG;
    FILE *f;
    int status;
    char buf[52] = {0};
    eapp_print("before fopen\n");
    f = fopen("/create.txt","w");
    char str[] = "create file and write\n";
    fputs(str,f);
    eapp_print("after fwrite\n");
    struct stat st;
    fclose(f);
    status = stat("/create.txt", &st);
    if(!status){
        eapp_print("stat succeed: file length: %d\n",st.st_size);
    }
    f = fopen("/create.txt","r");
    memset(buf,0,52);
    eapp_print("fopen /create.txt for read\n");
    char* res = fgets(buf,52,f);
    if(res == NULL){
        eapp_print("fgets failed\n");
    }
    eapp_print("read writed content: %s\n",buf);
    fseek(f,0,SEEK_SET);
    memset(buf,0,53);
    fgets(buf,52,f);
    eapp_print("read after seek: %s\n",buf);
    fclose(f);
    f = fopen("/sub/empty.txt","w");
    if(!f){
        eapp_print("open file failed, directory does not exist\n");
        if(mkdir("/sub", 0) != 0){
            eapp_print("mkdir failed\n");
            EAPP_RETURN(0);  
        }
    }
    f = fopen("/sub/empty.txt","w");
    if(!f){
        eapp_print("open after mkdir failed\n");
        EAPP_RETURN(0);
    }
    fputs(str, f);
    fclose(f);
    eapp_print("write to empty file\n");
    f = fopen("/sub/empty.txt","r");
    fgets(buf,52,f);
    eapp_print("read from empty file, %s\n",buf);
    fclose(f);
    int fd;
    if ((fd = open("/sub/empty.txt", O_RDWR| O_CREAT)) < 0) {
        eapp_print("open error\n");
     }
    struct stat stat_buf;
    eapp_print("stat begin\n");
    fstat(fd, &stat_buf);
    printf("/sub/empty.txt file size = %ld/n", stat_buf.st_size);
    EAPP_RETURN(0);
}