#include "ocall.h"
#include "eapp.h"

void* eapp_shmget(unsigned long shm_key, unsigned long shm_size, unsigned long shm_flags)
{
    unsigned long ret;
    ret = EAPP_SHM_GET(OCALL_SHM_GET, shm_key, shm_size, shm_flags);
    while(ret == -1UL)
    {
        ret = EAPP_SHM_GET(OCALL_SHM_GET, shm_key, shm_size, shm_flags);
    }
    return (void*)ret;
}

void* eapp_shmat(unsigned long shm_key)
{
    return EAPP_SHM_ATTACH(shm_key);
}

int eapp_shmdt(unsigned long shm_key)
{
    return EAPP_SHM_DETACH(OCALL_SHM_DETACH, shm_key);
}
int eapp_shmdestroy(unsigned long shm_key)
{
    return EAPP_SHM_DESTROY(OCALL_SHM_DESTROY, shm_key);
}

int eapp_shmstat(unsigned long shm_key, struct shm_dsc *dsc)
{
    return EAPP_SHM_STAT(shm_key, dsc);
}