// #define LOG_LEVEL DEBUG

#include <string.h>

#include "eapp.h"
#include "log.h"
#include "async_ipc_lib.h"
#include "sqlite3.h"
#define CMD_RESIZE (1)

static inline unsigned long rdcycle(void)
{
    unsigned long ret;
    asm volatile("rdcycle %0"
                 : "=r"(ret));
    return ret;
}

#define QUERY (1)
#define OTHER (2)
#define CLOSE (3)
struct query_result {
    int return_code;
    unsigned long row_count;
    unsigned long over;
};

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

sqlite3* db = NULL;

void handle_request(int cmd, void* request, long remain_bytes)
{
    int rc;
    LOG_DEBUG("Remaining bytes: %d\n", remain_bytes);
    switch(cmd) {
        case QUERY:
        {
            char* sql = (char*)request;
            struct query_result* result = (struct query_result*)request;
            sqlite3_stmt* stmt;
            rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
            if(rc != SQLITE_OK){
                result->return_code = rc;
                async_ret(request,rc, 0);
                break;
            }
            void* ret_buf = request + sizeof(struct query_result);
            result->row_count = 0;
            result->return_code = rc;
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
                            result->row_count--;
                            result->over = 0;
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
                            result->row_count--;
                            result->over = 0;
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
            async_ret(request,0,0);
            sqlite3_finalize(stmt);
            break;  
        }
        case OTHER:
        {
            char* sql = (char*)request;
            char* perror;
            struct query_result* result = (struct query_result*)request;
            rc = sqlite3_exec(db, sql, NULL, NULL, &perror);
            result->return_code = rc;
            result->over = 1;
            async_ret(request,0,0);
            break;
        }
        default:
        {
            LOG_ERROR("invalid cmd\n");
            async_ret(request,-1,0);
            break;
        }
    }

}

int EAPP_ENTRY main()
{
    unsigned long * args;
    EAPP_RESERVE_REG;
    LOG_DEBUG("async sqlite server begin to run\n");
    unsigned int* keys;
    unsigned long server_identifier;
    void* shared_memory_regions[1] = {NULL};
    unsigned long* shared_memory_sz[1] = {0};
    void* reqp;
    if(sqlite3_open(":memory:", &db) != SQLITE_OK){
        LOG_ERROR("sqlite-server open database failed\n");
        EAPP_RETURN(-1);
    }
    keys = server_register("sqlite-server", 1, &server_identifier);
    if(keys == NULL){
        LOG_ERROR("Register sqlite-server failed\n");
        EAPP_RETURN(-1);
    }
    LOG_DEBUG("sqlite-server register succeeded\n");
    while(1){
        if(!shared_memory_regions[0]){
            shared_memory_regions[0] = eapp_shmat(keys[0]);
            if(!shared_memory_regions[0]){
                //delay some time.
                for(int i = 0; i <= 1e5; ++i);
            }
        }else{
            break;
        }
    }
    struct shm_dsc dsc;
    eapp_shmstat(keys[0], &dsc);
    long remain_bytes = dsc.size - sizeof(struct query_result) - sizeof(struct async_ipc_param);
    while(1){
        int cmd = async_server_polling_request(shared_memory_regions[0], &reqp);
        while(cmd == -1){
            cmd = async_server_polling_request(shared_memory_regions[0], &reqp);
        }
        LOG_DEBUG("sqlite-server cmd: %d\n", cmd);
        if(cmd == CLOSE){
            async_ret(reqp,0,0);
            break;
        }
        handle_request(cmd, reqp, remain_bytes);
    }
    server_close("sqlite-server", server_identifier);
    EAPP_RETURN(0);
}

