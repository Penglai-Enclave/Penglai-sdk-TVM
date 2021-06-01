#define SYS_eret             1 //ret to host
#define SYS_ocall            2 //OCALL
#define SYS_acquire_enclave  3
#define SYS_call_enclave     4
#define SYS_enclave_return   5
#define SYS_asyn_ecnlave_call 6
#define SYS_split_mem_region 7
#define SYS_get_caller_id    8
#define SYS_get_enclave_id   9
#define SYS_yield            10 //reserve space for other operation

#define SBI_EXT_PENGLAI_ENCLAVE	    0x100101 //penglai extension id

.globl EAPP_RETURN
EAPP_RETURN:
	li a7, SYS_eret
    li a6, SBI_EXT_PENGLAI_ENCLAVE
	ecall

.globl EAPP_YIELD
EAPP_YIELD:
	li a7, SYS_yield
    li a6, SBI_EXT_PENGLAI_ENCLAVE
	ecall
    ret

.globl EAPP_OCALL
EAPP_OCALL:
	li a7, SYS_ocall
    li a6, SBI_EXT_PENGLAI_ENCLAVE
	ecall
    ret

.globl EAPP_MMAP
EAPP_MMAP:
    li a7, SYS_ocall
    li a6, SBI_EXT_PENGLAI_ENCLAVE
    ecall
    ret

.globl EAPP_UNMAP
EAPP_UNMAP:
    li a7, SYS_ocall
    li a6, SBI_EXT_PENGLAI_ENCLAVE
    ecall
    ret

.globl EAPP_RETURN_RELAY_PAGE
EAPP_RETURN_RELAY_PAGE:
    li a7, SYS_ocall
    li a6, SBI_EXT_PENGLAI_ENCLAVE
    ecall
    ret

.globl EAPP_PERSISTENCY_READ_SEC
EAPP_PERSISTENCY_READ_SEC:
    li a7, SYS_ocall
    li a6, SBI_EXT_PENGLAI_ENCLAVE
    ecall
    ret

.globl EAPP_PERSISTENCY_WRITE_SEC
EAPP_PERSISTENCY_WRITE_SEC:
    li a7, SYS_ocall
    li a6, SBI_EXT_PENGLAI_ENCLAVE
    ecall
    ret

.globl EAPP_ACQUIRE_ENCLAVE
EAPP_ACQUIRE_ENCLAVE:
    li a7, SYS_acquire_enclave
    li a6, SBI_EXT_PENGLAI_ENCLAVE
    ecall
    ret

.globl EAPP_GET_CALLER_ID
EAPP_GET_CALLER_ID:
    li a7, SYS_get_caller_id
    li a6, SBI_EXT_PENGLAI_ENCLAVE
    ecall
    ret

.globl EAPP_GET_ENCLAVE_ID
EAPP_GET_ENCLAVE_ID:
    li a7, SYS_get_enclave_id
    li a6, SBI_EXT_PENGLAI_ENCLAVE
    ecall
    ret

.globl EAPP_CALL_ENCLAVE
EAPP_CALL_ENCLAVE:
    li a7, SYS_call_enclave
    li a6, SBI_EXT_PENGLAI_ENCLAVE
    ecall
    ret

.globl SERVER_RETURN
SERVER_RETURN:
	li a7, SYS_enclave_return
    li a6, SBI_EXT_PENGLAI_ENCLAVE
	ecall

.globl EAPP_ASYN_ENCLAVE_CALL
EAPP_ASYN_ENCLAVE_CALL:
	li a7, SYS_asyn_ecnlave_call
    li a6, SBI_EXT_PENGLAI_ENCLAVE
	ecall
    ret

.globl EAPP_SPLIT_MEM_REGION
EAPP_SPLIT_MEM_REGION:
	li a7, SYS_split_mem_region
    li a6, SBI_EXT_PENGLAI_ENCLAVE
	ecall
    ret