#include <string.h>
#include <stdlib.h>

#include "eapp.h"
// #define LOG_LEVEL DEBUG
#include "log.h"
#include "sqlite3.h"

#define WORKLOAD_ADE
enum request_type {
    READ,
    UPDATE,
    INSERT,
    SCAN
};

static inline unsigned long rdcycle(void)
{
    unsigned long ret;
    asm volatile ("rdcycle %0" : "=r"(ret));
    return ret;
}

struct request{
    enum request_type type;
    int row_id;
    int scan_cnt;
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

static char *itoa(char *p, unsigned int x)
{
	// number of digits in a uint32_t + NUL
	p += 11;
	*--p = 0;
	do {
		*--p = '0' + x % 10;
		x /= 10;
	} while (x);
	return p;
}

void write_header(char* pos, int field_cnt, int field_sz)
{
    const char* create = "CREATE TABLE IF NOT EXISTS test(key VARCHAR(100) PRIMARY KEY,"; 
    char property_buf[20] = {0};
    char str_buf[11];
    char* numstr;
    strcpy(property_buf, "VARCHAR(");
    numstr = itoa(str_buf, field_sz);
    strcpy(property_buf+strlen("VARCHAR("), numstr);
    *(property_buf + strlen("VARCHAR(") + strlen(numstr)) = ')';
    int property_len = strlen(property_buf);
    strcpy(pos, create);
    pos += strlen(create);
    for(int i = 0; i < field_cnt; ++i){
        *pos++ = 'v';
        numstr = itoa(str_buf, i);
        strcpy(pos, numstr);
        pos += strlen(numstr);
        *pos++ = ' ';
        strcpy(pos, property_buf);
        pos += property_len;
        if(field_cnt - 1 == i){
            *pos++ = ')';
        }else{
            *pos++ = ',';
        }
    }
    *pos++ = ';';
    *pos = '\0';

}
int init_insert(char* pos, int index, int field_cnt, int field_sz, const char* prefix)
{
    char field[field_sz + 1]; //may need to initialize to fill the string buffer.
    field[field_sz] = '\0';
    for(int i = 0; i < field_sz; ++i){
        field[i] = 'a';
    }
    char str_buf[11];
    char* numstr;
    int prefix_len = strlen(prefix);
    if(prefix_len >= 90){
        LOG_ERROR("too large key\n");
        return -1;
    }
    const char* insert = "INSERT INTO test VALUES(";
    int insert_len = strlen(insert);
    strcpy(pos, insert);
    pos += insert_len;
    *pos++ = '\"';
    strcpy(pos, prefix);
    pos += prefix_len;
    numstr = itoa(str_buf, index);
    strcpy(pos, numstr);
    pos += strlen(numstr);
    *pos++ = '\"';
    *pos++ = ',';
    int field_len = strlen(field);
    for(int i = 0; i < field_cnt; ++i){
        *pos++ = '\"';
        strcpy(pos, field);
        pos += field_len;
        *pos++ = '\"';
        if(field_cnt - 1 == i){
            *pos++ = ')';
        }else{
            *pos++ = ',';
        }
    }
    *pos++ = ';';
    *pos = '\0';
    return 0;
}


int generate_table(const char *prefix, int record_cnt, int field_cnt, int field_sz, void*sql, sqlite3* db)
{
    // char key_name[101];
    char* perror = NULL;
    int rc = 0;
    if(strlen(prefix) + 10 >= 100){
        LOG_ERROR("too large key\n");
        return -1;
    }
    write_header(sql, field_cnt, field_sz);
    LOG_DEBUG("%s\n", sql);
    rc = sqlite3_exec(db, sql, NULL, NULL, &perror);
    if(rc != SQLITE_OK){
        LOG_ERROR("create table failed\n");
        return rc;
    }
    for(int i = 0; i < record_cnt; ++i){
        rc = init_insert(sql, i, field_cnt, field_sz, prefix);
        if(rc != 0){
            LOG_ERROR("init insert %d row failed\n", i);
            return -1;
        }
        LOG_DEBUG("%s\n", sql);
        rc = sqlite3_exec(db, sql, NULL, NULL, &perror);
        if(rc != SQLITE_OK){
            LOG_ERROR("Insert into table failed at %d row\n", i);
            return rc;
        }
    }
    return 0;
}


//just query k,v at this time, which means field_cnt = 1, otherwise insert or update will fail.
int performance_test(int record_cnt, int operation_cnt, const char* prefix, int read_proportion, int update_proportion, int insert_proportion, int scan_proportion, void*sql, unsigned long mem_sz,  sqlite3* db)
{
    //"select * from test where key == prefixi"
    if(operation_cnt < 100 || operation_cnt % 100 != 0 || (read_proportion + update_proportion + insert_proportion + scan_proportion) != 100){
        LOG_ERROR("Invalid parameters\n");
        return;
    }
    LOG_INFO("record_cnt = %d, operation_cnt = %d, prefix = %s, read_proportion = %d, update_proportion = %d, insert_proportion = %d, scan_proportion = %d\n",record_cnt, operation_cnt, prefix, read_proportion, update_proportion, insert_proportion, scan_proportion);
    char read_buf[50] = {0};
    char update_buf[150] = {0};
    char insert_buf[150] = {0};
    char scan_buf[50] = {0};
    char num_buf[11] = {0};
    char* num_str;
    char* read_pos = read_buf;
    char* update_pos = update_buf;
    char* insert_pos = insert_buf;
    char* scan_pos = scan_buf;
    int prefix_len = strlen(prefix);
    int rc = 0;
    char* perror = NULL;
    strcpy(read_buf, "select * from test where key = ");
    read_pos += strlen("select * from test where key = ");
    *read_pos++ = '\"';
    strcpy(read_pos, prefix);
    read_pos += prefix_len;
    strcpy(update_buf, "update test set v0 = \"");
    update_pos += strlen("update test set v0 = \"");
    for(int i = 0; i < 100; ++i){
        *update_pos++ = 'b';
    }
    *update_pos++ = '\"';
    strcpy(update_pos, " where key = \"");
    update_pos += strlen(" where key = \"");
    strcpy(update_pos, prefix);
    update_pos += prefix_len;
    strcpy(insert_buf, "insert into test values(\"");
    insert_pos += strlen("insert into test values(\"");
    strcpy(insert_pos, prefix);
    insert_pos += prefix_len;
    strcpy(scan_buf, "select * from test where key between \"");
    scan_pos += strlen("select * from test where key between \"");
    strcpy(scan_pos, prefix);
    scan_pos += prefix_len;
    int request_page_cnt = (sizeof(struct request) * operation_cnt)/0x1000 + 1;
    struct request *requests = eapp_mmap(NULL, request_page_cnt * 0x1000);
    if(requests == NULL){
        LOG_ERROR("malloc requests failed\n");
        return;
    }
    const size_t read_prefix_len = strlen(read_buf);
    const size_t update_prefix_len = strlen(update_buf);
    const size_t insert_prefix_len = strlen(insert_buf);
    const size_t scan_prefix_len = strlen(scan_buf);
    update_proportion += read_proportion;
    insert_proportion += update_proportion;
    scan_proportion += insert_proportion;
    srand(0x1234); // using the same random seed;
    //initialize request sql before doing performance testing.
    for(int i = 0; i < operation_cnt; ++i){
        int random_type = rand() % 100;
        if(random_type < read_proportion){
            requests[i].type = READ;
        }else if(random_type < update_proportion){
            requests[i].type = UPDATE;
        }else if(random_type < insert_proportion){
            requests[i].type = INSERT;
        }else{
            requests[i].type = SCAN;
        }
        switch(requests[i].type){
            case READ: 
            {
                int random_index = rand() % record_cnt;
                LOG_DEBUG("read index: %d\n", random_index);
                requests[i].row_id = random_index;
                break;
            }
            case UPDATE: 
            {
                int random_index = rand() % record_cnt;
                LOG_DEBUG("update index: %d\n", random_index);
                requests[i].row_id = random_index;
                break;
            }
            case INSERT:
            {
                requests[i].row_id = record_cnt++;
                LOG_DEBUG("insert index: %d\n", requests[i].row_id);
                break;
            }
            case SCAN: 
            {
                requests[i].row_id = rand() % record_cnt;
                int max_len = record_cnt - requests[i].row_id;
                requests[i].scan_cnt = rand() % max_len;
                LOG_DEBUG("scan start: %d, max_len: %d\n", requests[i].row_id, requests[i].scan_cnt);
                break; 
            }
        }
    }
    unsigned long start_cycle = rdcycle();
    char* pos;
    LOG_DEBUG("Before Test\n");
    for(int i = 0; i < operation_cnt; ++i){
        switch(requests[i].type){
            case READ:
            {
                memcpy(sql, read_buf, read_prefix_len);
                num_str = itoa(num_buf, requests[i].row_id);
                strcpy(sql+read_prefix_len, num_str);
                pos = sql + read_prefix_len + strlen(num_str);
                *pos++ = '\"';
                *pos++ = ';';
                *pos++ = 0;
                LOG_DEBUG("%s\n", sql);
                sqlite3_stmt* stmt;
                rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
                if(rc != SQLITE_OK){
                    LOG_ERROR("sqlite query failed: %s\n", sql);
                    return rc;
                }
                void* ret_buf = sql;
                unsigned long remain_bytes = mem_sz;
                while(sqlite3_step(stmt) == SQLITE_ROW){
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
                                break;
                            }                        
                        }
                        column_type = sqlite3_column_type(stmt, column_num);
                    }
                    if(remain_bytes < 0){
                        break;
                    }
                }
                sqlite3_finalize(stmt);
                break;
            }
            case UPDATE:
            {
                memcpy(sql, update_buf, update_prefix_len);
                num_str = itoa(num_buf, requests[i].row_id);
                strcpy(sql + update_prefix_len, num_str);
                pos = sql + update_prefix_len + strlen(num_str);
                *pos++ = '\"';
                *pos++ = ';';
                *pos++ = 0;
                LOG_DEBUG("%s\n", sql);
                rc = sqlite3_exec(db, sql, NULL, NULL, &perror);
                if(rc != SQLITE_OK){
                    LOG_ERROR("%s failed\n", sql);
                    return rc;
                }
                break;
            }
            case INSERT: 
            {
                memcpy(sql,insert_buf, insert_prefix_len);
                num_str = itoa(num_buf, requests[i].row_id);
                strcpy(sql+insert_prefix_len, num_str);
                pos = sql + insert_prefix_len + strlen(num_str);
                *pos++ = '\"';
                *pos++ = ',';
                *pos++ = '\"';
                for(int j = 0; j < 100;++j){
                    *pos++ = 'a';
                }
                *pos++ ='\"';
                *pos++ = ')';
                *pos++ = ';';
                *pos++ = 0;
                LOG_DEBUG("%s\n", sql);
                rc = sqlite3_exec(db, sql, NULL, NULL, &perror);
                if(rc != SQLITE_OK){
                    LOG_ERROR("%s failed\n", sql);
                    return rc;
                }
                break;
            }
            case SCAN: 
            {
                memcpy(sql, scan_buf, scan_prefix_len);
                num_str = itoa(num_buf, requests[i].row_id);
                strcpy(sql+scan_prefix_len, num_str);
                pos = sql + scan_prefix_len + strlen(num_str);
                *pos++ = '\"';
                *pos++ = ' ';
                *pos++ = 'a';
                *pos++ = 'n';
                *pos++ = 'd';
                *pos++ = ' ';
                *pos++ = '\"';
                strcpy(pos, prefix);
                pos += prefix_len;
                num_str = itoa(num_buf, requests[i].row_id + requests[i].scan_cnt);
                strcpy(pos, num_str);
                pos += strlen(num_str);
                *pos++ = '\"';
                *pos++ = ';';
                *pos++ = 0;
                LOG_DEBUG("%s\n", sql);
                sqlite3_stmt* stmt;
                rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
                if(rc != SQLITE_OK){
                    LOG_ERROR("%s failed\n", sql);
                    return rc;
                }
                void* ret_buf = sql;
                unsigned long remain_bytes = mem_sz;
                while(sqlite3_step(stmt) == SQLITE_ROW){
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
                                break;
                            }                        
                        }
                        column_type = sqlite3_column_type(stmt, column_num);
                    }
                    if(remain_bytes < 0){
                        break;
                    }
                }
                sqlite3_finalize(stmt);
                // result = (struct query_result*)call_arg.req_vaddr;
                // void* result_buf = call_arg.req_vaddr + sizeof(struct query_result);
                // LOG_INFO("%d\n", result->row_count);
                // for(unsigned long j = 0; j < result->row_count; ++j){
                //     eapp_print("k: %s, v: %s\n", parse_text(&result_buf), parse_text(&result_buf));
                // }
                break;
            }
            default:
            {
                LOG_ERROR("Some bug!\n");
                break;
            }
        }
    }
    unsigned long end_cycle = rdcycle();
    LOG_INFO("test cycles: %ld\n", end_cycle - start_cycle); 
    eapp_unmap(requests, request_page_cnt * 0x1000);
}

int EAPP_ENTRY main()
{
    unsigned long * args;
    EAPP_RESERVE_REG;
    LOG_DEBUG("ycsb-baseline begin to run\n");
    sqlite3* db = NULL;
    if(sqlite3_open(":memory:", &db) != SQLITE_OK){
        LOG_ERROR("sqlite-open database failed\n");
        EAPP_RETURN(-1);
    }
#if (defined WORKLOAD_ADA)
    LOG_INFO("YCSB ada workload test");
    const unsigned long mem_sz = 4096*15UL;
#elif (defined WORKLOAD_ADB)
    LOG_INFO("YCSB adb workload test");
    const unsigned long mem_sz = 4096UL;
#elif (defined WORKLOAD_ADC)
    LOG_INFO("YCSB adc workload test");
    const unsigned long mem_sz = 4096UL;
#elif (defined WORKLOAD_ADD)
    LOG_INFO("YCSB add workload test");
    const unsigned long mem_sz = 4096UL;
#elif (defined WORKLOAD_ADE)
    LOG_INFO("YCSB ade workload test");
    const unsigned long mem_sz = 4096*31UL;
#endif
    void* mem = eapp_mmap(NULL, mem_sz);
    if(mem == NULL){
        LOG_ERROR("alloc memory failed\n");
        EAPP_RETURN(-1);
    }
    int ret;
    char* prefix = "jxq";
    ret = generate_table(prefix, 1000, 1, 100, mem, db);
    if(ret != 0){
        LOG_ERROR("generate table failed\n");
        eapp_unmap(mem, mem_sz);
        EAPP_RETURN(-1);
    }
    LOG_INFO("Table generated successfully\n");
#if (defined WORKLOAD_ADA)
    performance_test(1000,1000, prefix, 95, 2, 2, 1, mem, mem_sz, db);
#elif (defined WORKLOAD_ADB)
    performance_test(1000,1000, prefix, 95, 5, 0, 0, mem, mem_sz, db);
#elif (defined WORKLOAD_ADC)
    performance_test(1000,1000, prefix, 100, 0, 0, 0, mem, mem_sz, db);
#elif (defined WORKLOAD_ADD)
    performance_test(1000,1000, prefix, 95, 0, 5, 0, mem, mem_sz, db);
#elif (defined WORKLOAD_ADE)
    performance_test(1000,1000, prefix, 0, 0, 5, 95, mem, mem_sz, db);
#endif
    eapp_unmap(mem, mem_sz);
    EAPP_RETURN(0);
}