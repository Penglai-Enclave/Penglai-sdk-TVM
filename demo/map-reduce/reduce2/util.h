
#include <stdio.h>
#include <string.h>
#define REDUCE_SIZE 500
typedef struct
{
  char key[10];
  int value;
}  Keyvalue;

typedef struct
{
  char* in;
  char* out;
  int keyvalue_num;
}  in_out_format;