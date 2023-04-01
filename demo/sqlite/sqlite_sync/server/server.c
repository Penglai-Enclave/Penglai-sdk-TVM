#include <stdlib.h>
#include <string.h>

#include "sqlite3.h"
#include "eapp.h"
#include "print.h"
// #define LOG_LEVEL DEBUG
#include "log.h"
#define QUERY (1)
#define OTHER (2)
struct query_result {
    int return_code;
    unsigned long row_count;
    unsigned long over;
};
static inline unsigned long rdcycle(void)
{
    unsigned long ret;
    asm volatile ("rdcycle %0" : "=r"(ret));
    return ret;
}
void write_int(void** buf, int n)
{
    int* int_buf = (int*)(*buf);
    *int_buf = n;
    *buf += sizeof(int);
}

void write_text(void** buf, const char* str, unsigned long bytes){
    char* text_buf = (char*)(*buf);
    strcpy(text_buf, str);
    *buf += bytes;
}

unsigned int inited = 0;
sqlite3* db = NULL;
int EAPP_ENTRY main(){
    unsigned long * args;
    EAPP_RESERVE_REG;
    LOG_DEBUG("Begin to run sqlite3\n");
    int rc;
    struct call_enclave_arg_t ret_arg;
    if(!inited){
        rc = sqlite3_open(":memory:",&db);
        if(rc != SQLITE_OK){
            eapp_print("init sqlite3 server failed\n");
            ret_arg.resp_val = -1;
            SERVER_RETURN(&ret_arg);
        }
        inited = 1;
    }
    char* perror;
    ret_arg.req_vaddr = args[11];
    ret_arg.req_size = args[12];
    ret_arg.resp_vaddr = 0;
    ret_arg.resp_size = 0;
    // unsigned long end = rdcycle();
    char* sql = (char*)ret_arg.req_vaddr;
    struct query_result* result = (struct query_result*)ret_arg.req_vaddr;
    LOG_DEBUG("Before exec\n");
    unsigned long cmd = args[10];
    switch(cmd){
        case OTHER:
        {
            rc = sqlite3_exec(db, sql,NULL, NULL, &perror);
            if(rc != SQLITE_OK){
                LOG_ERROR("%s failed, %s\n", sql, perror);
                ret_arg.resp_val = -1;
                result->return_code = rc;
                break;
            }
            result->return_code = rc;
            result->over = 1;
            ret_arg.resp_val = 0;
            break;
        }
        case QUERY:
        {
            sqlite3_stmt* stmt;
            rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
            if(rc != SQLITE_OK){
                ret_arg.resp_val = -1;
                result->return_code = rc;
                break;
            }
            void* ret_buf = ret_arg.req_vaddr + sizeof(struct query_result);
            result->row_count = 0;
            result->return_code = rc;
            long remain_bytes = ret_arg.req_size - sizeof(struct query_result);
            LOG_DEBUG("Remaining bytes: %d\n", remain_bytes);
            while(sqlite3_step(stmt) == SQLITE_ROW){
                result->row_count ++;
                int column_type;
                int column_num = 0;
                column_type = sqlite3_column_type(stmt, column_num);
                while(column_type == SQLITE_INTEGER || column_type == SQLITE_TEXT){
                    if(column_type == SQLITE_INTEGER){
                        remain_bytes -= sizeof(int);
                        if(remain_bytes >= 0){
                            write_int(&ret_buf, sqlite3_column_int(stmt, column_num++));
                        }
                        else{
                            LOG_INFO("The buffer is too small to hold all the results\n");
                            result->over = 0;
                            result->row_count --;
                            LOG_DEBUG("server: %d\n", result->row_count);
                            break;
                        }
                    }else{
                        const char* str = sqlite3_column_text(stmt, column_num++);
                        unsigned long str_bytes = strlen(str) + 1;
                        remain_bytes -= str_bytes;
                        if(remain_bytes >= 0){
                            write_text(&ret_buf, str, str_bytes);
                        }else{
                            LOG_INFO("The buffer is too small to hold all the results\n");
                            result->over = 0;
                            result->row_count--;
                            LOG_DEBUG("server: %d\n", result->row_count);
                            break;
                        }                        
                    }
                    column_type = sqlite3_column_type(stmt, column_num);
                }
                if(remain_bytes < 0){
                    break;
                }
            }
            if(remain_bytes >= 0){
                result->over = 1;
            }
            sqlite3_finalize(stmt);

            break;
        }
        default:
            LOG_WARNING("Invalid cmd\n");
    }
    // LOG_INFO("end: %ld\n", end);
    SERVER_RETURN(&ret_arg);
}