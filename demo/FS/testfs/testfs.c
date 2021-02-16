#include "eapp.h"
#include "print.h"
#include <string.h>
#include <fcntl.h>
#include "fscallargs.h"
#include <stdio.h>
#include<sys/stat.h>
#include<unistd.h>
int test(){
    // eapp_print("begin test file\n");
    // char* server_name = "filesystem";
    // unsigned long server_handle = acquire_enclave(server_name);
    // if(server_handle == -1UL){
    //     eapp_print("acquire handle failed\n");
    //     EAPP_RETURN(-1);
    // }
    // eapp_print("acquire handle succeed\n");
    // unsigned long type = 0;
    // unsigned long mode = O_CREAT|O_RDONLY;
    // int fd;
    // char* path = "/sub/test.txt";
    // void* buf = eapp_mmap(NULL, 4096);
    // struct open_arg *open_arg = (struct open_arg*)buf;
    // strcpy(open_arg->path,path);
    // open_arg->mode = mode;
    // eapp_print("begin to call server open\n");
    // int status = call_enclave(server_handle,FSOPEN,buf,4096,&fd);
    // if(!status){
    //     eapp_print("open succeed and fd is %d: \n",fd);
    //     struct read_arg *read_arg = (struct read_arg*)buf;
    //     read_arg->fd = fd;
    //     read_arg->size = 4096;
    //     int read_size;
    //     eapp_print("begin to call again\n");
    //     status = call_enclave(server_handle,FSREAD,buf,4096,&read_size);
    //     if(!status){
    //         eapp_print("read content: %s, length: %d\n",(char*)buf,read_size);
    //     }
    //     struct close_arg *close_arg = (struct close_arg*)buf;
    //     close_arg->fd = fd;
    //     int close_result;
    //     status = call_enclave(server_handle,FSCLOSE,buf,4096,&close_result);
    //     if(!status && !close_result){
    //         eapp_print("close file succeed\n");
    //     }
    // }
    // char* create_path = "/create.txt";
    // strcpy(open_arg->path,create_path);
    // open_arg->mode = O_CREAT|O_WRONLY;
    // int write_fd;
    // status = call_enclave(server_handle,FSOPEN,buf,4096,&write_fd);
    // if(!status){
    //     struct write_arg *write_arg = (struct write_arg*)buf;
    //     write_arg->fd = write_fd;
    //     char* write_buf = (char*)buf + sizeof(struct write_arg);
    //     strcpy(write_buf,"write test content");
    //     unsigned long write_size;
    //     write_arg->size = strlen("write test content") + 1;
    //     status = call_enclave(server_handle,FSWRITE,buf,4096,&write_size);
    //     eapp_print("client write_size: %d\n",write_size);
    //     unsigned long read_size;
    //     if(!status){
    //         eapp_print("client write size 2: %d\n",write_size);
    //         open_arg = (struct open_arg*)buf;
    //         strcpy(open_arg->path,create_path);
    //         open_arg->mode = O_CREAT|O_RDONLY;
    //         status = call_enclave(server_handle,FSOPEN,buf,4096,&fd);
    //         if(!status){
    //             eapp_print("reopen fs: %d\n",fd);
    //         }
    //         eapp_print("client write size 3: %d\n",write_size);
    //         struct read_arg *read_arg = (struct read_arg*)buf;
    //         read_arg->fd = fd;
    //         read_arg->size = 4096;
    //         eapp_print("client write size 4: %d\n",write_size);
    //         status = call_enclave(server_handle,FSREAD,buf,4096,&read_size);
    //         eapp_print("client write size 5: %d\n",write_size);
    //         eapp_print("read size: %d, write_size: %d\n",read_size,write_size);
    //         eapp_print("read content: %s\n",(char*)buf);
    //     }
    // }
    return 0;
}

int EAPP_ENTRY main(){
    unsigned long* args;
    EAPP_RESERVE_REG;
    FILE *f;
    int status;
    char buf[52] = {0};
    eapp_print("before fopen\n");
    f = fopen("/create.txt","w");
    char str[] = "just for create and write\ntest fgets";
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
    if ((fd = open("/sub/empty2.txt", O_RDWR| O_CREAT)) < 0) {
        eapp_print("open error\n");
     }
    struct stat stat_buf;
    eapp_print("stat begin\n");
    stat("/sub/empty.txt", &stat_buf);
    printf("/sub/empty.txt file size = %d/n", stat_buf.st_size);
    EAPP_RETURN(0);
}