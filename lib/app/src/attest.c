#include "ocall.h"
#include "eapp.h"
#include "attest.h"

int get_report(char* name, struct report_t *report, unsigned long nonce)
{
  int ret = 0;
  ret = EAPP_GET_REPORT(name, report, nonce);
  return ret;
}