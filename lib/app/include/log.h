#ifndef __ENCLAVE_LOG__
#define __ENCLAVE_LOG__
#include "print.h"


#define    FATAL   1
#define    ERROR   2
#define    WARNING 3
#define    INFO    4
#define    DEBUG   5


#ifndef LOG_LEVEL
#define LOG_LEVEL 4
#endif


#if LOG_LEVEL>= FATAL
#define LOG_FATAL(fmt, ...) eapp_print("[%s:%s:%d FATAL]: "fmt, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__ )
#else
#define LOG_FATAL(fmt, ...) 
#endif

#if LOG_LEVEL>=ERROR
#define LOG_ERROR(fmt, ...) eapp_print("[%s:%s:%d ERROR]: "fmt, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define LOG_ERROR(fmt, ...)
#endif

#if LOG_LEVEL>=WARNING
#define LOG_WARNING(fmt, ...) eapp_print("[%s:%s:%d WARNING]: "fmt, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define LOG_WARNING(fmt, ...)
#endif

#if LOG_LEVEL>=INFO
#define LOG_INFO(fmt, ...) eapp_print("[%s:%s:%d INFO]: "fmt, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define LOG_INFO(fmt, ...)
#endif

#if LOG_LEVEL>=DEBUG
#define LOG_DEBUG(fmt, ...) eapp_print("[%s:%s:%d DEBUG]: "fmt, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define LOG_DEBUG(fmt, ...)
#endif

#endif