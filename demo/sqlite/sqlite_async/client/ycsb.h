#ifndef __YCSB__



int generate_table(const char* prefix, int record_cnt, int field_cnt, int field_size, void*shm);

void performance_test(int record_cnt, int operation_cnt, const char* prefix, int read_proportion, int update_proportion, int insert_proportion, int scan_proportion, void* shm);

#define __YCSB__
#endif