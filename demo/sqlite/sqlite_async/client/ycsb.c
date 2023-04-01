#include <string.h>
#include <stdlib.h>
#include "ycsb.h"
// #define LOG_LEVEL DEBUG
#include "log.h"
#include "async_ipc_lib.h"
#define QUERY (1UL)
#define OTHER (2UL)
#define CLOSE (3UL)
struct query_result {
    int return_code;
    unsigned long row_count;
    unsigned long over;
};

enum request_type {
    READ,
    UPDATE,
    INSERT,
    SCAN
};

extern int parse_int(void** buf);
extern char* parse_text(void* buf);
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


int generate_table(const char *prefix, int record_cnt, int field_cnt, int field_sz, void*shm)
{
    // char key_name[101];
    struct query_result* result = NULL;
    unsigned int ret_sz;
    if(strlen(prefix) + 10 >= 100){
        LOG_ERROR("too large key\n");
        return -1;
    }
    char* sql = async_client_get_request_mem(shm);
    write_header(sql, field_cnt, field_sz);
    LOG_DEBUG("%s\n", sql);    
    int ret = async_call(shm, OTHER, &result, &ret_sz);
    if(ret != 0 || result->return_code != 0){
        LOG_ERROR("create table failed\n");
        return -1;
    }
    for(int i = 0; i < record_cnt; ++i){
        ret = init_insert(sql, i, field_cnt, field_sz, prefix);
        if(ret != 0){
            LOG_ERROR("init insert %d row failed\n", i);
            return -1;
        }
        LOG_DEBUG("%s\n", sql);
        ret = async_call(shm, OTHER, &result, &ret_sz);
        if(ret !=0 || result->return_code != 0){
            LOG_ERROR("Failed to insert %d row into table\n", i);
            return -1;
        }
    }
    return 0;
}


//just query k,v at this time, which means field_cnt = 1, otherwise insert or update will fail.
void performance_test(int record_cnt, int operation_cnt, const char* prefix, int read_proportion, int update_proportion, int insert_proportion, int scan_proportion, void*shm)
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
    char* sql = (char*)async_client_get_request_mem(shm);
    int prefix_len = strlen(prefix);
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
    struct query_result* result;
    unsigned int ret_size;
    for(int i = 0; i < operation_cnt; ++i){
        LOG_DEBUG("%d: ", i);
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
                async_call(shm, QUERY, &result, &ret_size);
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
                async_call(shm, OTHER, &result, &ret_size);
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
                async_call(shm, OTHER, &result, &ret_size);
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
                async_call(shm, QUERY, &result, &ret_size);
                // void* result_buf = (void*)result + sizeof(struct query_result);
                // LOG_INFO("%d\n", result->row_count);
                // for(unsigned long j = 0; j < result->row_count; ++j){
                // eapp_print("k: %s, v: %s\n", parse_text(&result_buf), parse_text(&result_buf));
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
