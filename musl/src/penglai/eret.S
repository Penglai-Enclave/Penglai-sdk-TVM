#define SYS_eret             1 //ret to host
#define SYS_ocall            2 //OCALL
#define SYS_acquire_enclave  3
#define SYS_call_enclave     4
#define SYS_enclave_return   5
.globl EAPP_RETURN
EAPP_RETURN:
	li a7, SYS_eret
	ecall

.globl EAPP_OCALL
EAPP_OCALL:
	li a7, SYS_ocall
	ecall
    ret

.globl EAPP_MMAP
EAPP_MMAP:
    li a7, SYS_ocall
    ecall
    ret

.globl EAPP_UNMAP
EAPP_UNMAP:
    li a7, SYS_ocall
    ecall
    ret

.globl EAPP_ACQUIRE_ENCLAVE
EAPP_ACQUIRE_ENCLAVE:
    li a7, SYS_acquire_enclave
    ecall
    ret

.globl EAPP_CALL_ENCLAVE
EAPP_CALL_ENCLAVE:
    li a7, SYS_call_enclave
    ecall
    ret

.globl SERVER_RETURN
SERVER_RETURN:
	li a7, SYS_enclave_return
	ecall
