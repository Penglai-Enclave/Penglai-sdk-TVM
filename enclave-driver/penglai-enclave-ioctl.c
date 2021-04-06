#include "penglai-enclave-ioctl.h"
#include "penglai-enclave-driver.h"
#include "penglai-shm.h"
#include "penglai-schrodinger.h"
#include "penglai-enclave-persistency.h"
#include <linux/delay.h>

//TODO: improve concurrency
//now we just acqure a big clock before allocating enclave mem, and release the lock
//after initializing mem and returning it back to sm
DEFINE_SPINLOCK(enclave_create_lock);

unsigned int total_enclave_page(int elf_size, int stack_size)
{
  unsigned int total_pages;
  total_pages = PAGE_UP(elf_size) / RISCV_PGSIZE + PAGE_UP(stack_size) / RISCV_PGSIZE + 256;
  return total_pages;
}

int create_sbi_param(enclave_t* enclave, struct penglai_enclave_sbi_param * enclave_sbi_param,
    unsigned long paddr, unsigned long size, unsigned long entry_point,
    unsigned long free_mem,
    unsigned long shm_vaddr, unsigned long shm_size)
{
  enclave_sbi_param->eid_ptr = (unsigned int* )__pa(&enclave->eid);
  enclave_sbi_param->ecall_arg0 = (unsigned long* )__pa(&enclave->ocall_func_id);
  enclave_sbi_param->ecall_arg1 = (unsigned long* )__pa(&enclave->ocall_arg0);
  enclave_sbi_param->ecall_arg2 = (unsigned long* )__pa(&enclave->ocall_arg1);
  enclave_sbi_param->ecall_arg3 = (unsigned long* )__pa(&enclave->ocall_syscall_num);
  enclave_sbi_param->retval = (unsigned long* )__pa(&enclave->retval);
  enclave_sbi_param->paddr = paddr;
  enclave_sbi_param->size = size;
  enclave_sbi_param->entry_point = entry_point;
  enclave_sbi_param->free_mem = free_mem;

  //enclave share mem with kernel
  enclave_sbi_param->kbuffer = __pa(enclave->kbuffer);
  enclave_sbi_param->kbuffer_size = enclave->kbuffer_size;

  //enclave share mem with host
  if((enclave->type == NORMAL_ENCLAVE || enclave->type == SERVER_ENCLAVE)&& shm_vaddr && shm_size)
  {
    enclave_sbi_param->shm_paddr = __pa(shm_vaddr);
    enclave_sbi_param->shm_size = shm_size;
  }

  enclave_sbi_param->type = enclave->type;
  memcpy(enclave_sbi_param->name, enclave->name, NAME_LEN);
  return 0;
}

int check_eapp_memory_size(int elf_size, int stack_size)
{
  if((elf_size > MAX_ELF_SIZE) || (stack_size > MAX_STACK_SIZE))
    return -1;
  return 0;
}

unsigned long get_shm(int shmid, unsigned long offset, unsigned long size)
{
  unsigned long shm_vaddr = 0;
  struct penglai_shm* shm;

  if(offset < 0 || offset & (RISCV_PGSIZE-1)
      || size < RISCV_PGSIZE || size & (RISCV_PGSIZE-1))
    return 0;

  shm = penglai_shm_find(shmid);
  if(!shm || (offset + size) > shm->size)
    return 0;
  shm_vaddr = shm->vaddr + offset;

  return shm_vaddr;
}

unsigned long get_schrodinger(int id, unsigned long offset, unsigned long size)
{
  unsigned long vaddr = 0;
  struct penglai_schrodinger* p;

  if(offset < 0 || offset & (RISCV_PGSIZE-1)
      || size < RISCV_PGSIZE || size & (RISCV_PGSIZE-1))
    return 0;

  p = penglai_schrodinger_find(id);
  if(!p || (offset + size) > p->size)
    return 0;
  vaddr = p->vaddr + offset;

  return vaddr;
}

int penglai_extend_secure_memory(void)
{
  int ii, ret_expand_monitor_memory;
  for (ii = 0; ii<DEFAULT_MEMORY_EXTEND_NUM; ii++)
  {
    unsigned long addr = penglai_get_free_pages(GFP_KERNEL, DEFAULT_SECURE_PAGES_ORDER);
    if(!addr)
    {
      penglai_eprintf("can not get free page which order is 0x%x", DEFAULT_SECURE_PAGES_ORDER);
      return DEFAULT_DESTROY_ENCLAVE;
    }

    memset(addr, 0, RISCV_PGSIZE* (1<<DEFAULT_SECURE_PAGES_ORDER));
    ret_expand_monitor_memory = SBI_PENGLAI_2(SBI_SM_MEMORY_EXTEND, __pa(addr), 1 << (DEFAULT_SECURE_PAGES_ORDER + RISCV_PGSHIFT));
    if(ret_expand_monitor_memory < 0)
    {
      penglai_eprintf("sbi call mm_init is failed\n");
      return DEFAULT_DESTROY_ENCLAVE;
    }
  }
  return 0;
}

int penglai_enclave_create(struct file *filep, unsigned long args)
{
  struct penglai_enclave_user_param* enclave_param = (struct penglai_enclave_user_param*)args;
  struct penglai_enclave_sbi_param enclave_sbi_param;
  enclave_t* enclave;
  void *elf_ptr = (void*)enclave_param->elf_ptr;
  int ret, total_pages, elf_size = 0, stack_size = enclave_param->stack_size;
  unsigned long free_mem = 0, elf_entry = 0, shm_vaddr = 0, shm_size = 0, order = 0;
  //FIXME: remove elf_size in enclave_param 
  penglai_enclave_elfmemsize(elf_ptr,  &elf_size);
  if(enclave_param->type == SHADOW_ENCLAVE)
    stack_size = 0;

  order = ilog2(total_enclave_page(elf_size, stack_size)- 1) + 1;
  total_pages = 0x1 << order;

  // penglai_dprintf("elf size %lx stack_size %lx\n", elf_size, stack_size);

  if(check_eapp_memory_size(elf_size, stack_size) < 0)
  {
    penglai_eprintf("eapp memory is out of bound \n");
    return -1;
  }
  spin_lock(&enclave_create_lock);

  enclave = create_enclave(total_pages, enclave_param->name, enclave_param->type);
  if(!enclave)
  {
    penglai_eprintf("cannot create enclave\n");
    goto destroy_enclave;
  }

  if(penglai_enclave_eapp_loading(enclave->enclave_mem, elf_ptr, elf_size, 
        &elf_entry, STACK_POINT, stack_size, enclave->type))
  {
    penglai_eprintf("penglai_enclave_eapp_loading is failed\n");;
    goto destroy_enclave;
  }

  if(elf_entry == 0)
  {
    penglai_eprintf("elf_entry reset is failed \n");
    goto destroy_enclave;
  }

  free_mem = get_free_mem(&(enclave->enclave_mem->free_mem));
  shm_vaddr = get_shm(enclave_param->shmid, enclave_param->shm_offset, enclave_param->shm_size);
  shm_size = enclave_param->shm_size;

  create_sbi_param(enclave, &enclave_sbi_param,
      (unsigned long)(enclave->enclave_mem->paddr),
      enclave->enclave_mem->size, elf_entry, __pa(free_mem),
      shm_vaddr, shm_size);

  if(enclave_sbi_param.type == SERVER_ENCLAVE)
    ret = SBI_PENGLAI_1(SBI_SM_CREATE_SERVER_ENCLAVE, __pa(&enclave_sbi_param));
  else if(enclave_sbi_param.type == SHADOW_ENCLAVE)
    ret = SBI_PENGLAI_1(SBI_SM_CREATE_SHADOW_ENCLAVE, __pa(&enclave_sbi_param));
  else
    ret = SBI_PENGLAI_1(SBI_SM_CREATE_ENCLAVE, __pa(&enclave_sbi_param));

  while(ret == ENCLAVE_NO_MEM)
  {
    if ((ret = penglai_extend_secure_memory()) < 0)
      goto destroy_enclave;

    if(enclave_sbi_param.type == SERVER_ENCLAVE)
      ret = SBI_PENGLAI_1(SBI_SM_CREATE_SERVER_ENCLAVE, __pa(&enclave_sbi_param));
    else if(enclave_sbi_param.type == SHADOW_ENCLAVE)
      ret = SBI_PENGLAI_1(SBI_SM_CREATE_SHADOW_ENCLAVE, __pa(&enclave_sbi_param));
    else
      ret = SBI_PENGLAI_1(SBI_SM_CREATE_ENCLAVE, __pa(&enclave_sbi_param));
  }
  if(ret < 0)
  {
    penglai_eprintf("SBI_SM_CREATE_ENCLAVE is failed \n");
    goto destroy_enclave;
  }
  enclave_param->eid = enclave_idr_alloc(enclave);

  spin_unlock(&enclave_create_lock);
  return ret;

destroy_enclave:

  spin_unlock(&enclave_create_lock);

  if(enclave)
    destroy_enclave(enclave);

  return -EFAULT;
}

int penglai_enclave_destroy(struct file * filep, unsigned long args)
{
  struct penglai_enclave_user_param * enclave_param = (struct penglai_enclave_user_param*) args;
  unsigned long eid = enclave_param->eid;
  enclave_t *enclave;
  unsigned long satp;
  int ret =0;
  
  enclave = get_enclave_by_id(eid);
  if(!enclave)
  {
    penglai_eprintf("enclave is not exist \n");
    return -EINVAL;
  }
  satp =  enclave->satp;
  //FIXME: 
  if(enclave->type == SERVER_ENCLAVE)
    ret = SBI_PENGLAI_1(SBI_SM_DESTROY_SERVER_ENCLAVE, enclave->eid);
  else
    ret = SBI_PENGLAI_1(SBI_SM_DESTROY_ENCLAVE, enclave->eid);
  spin_lock(&enclave_create_lock);
  if(get_enclave_by_id(eid) && get_enclave_by_id(eid)->satp == satp)
  {
    destroy_enclave(enclave);
    enclave_idr_remove(eid);
  }
  spin_unlock(&enclave_create_lock);

  return ret;
}

int handle_memory_extend(enclave_t * enclave)
{
  unsigned long pages = enclave ->ocall_arg0;
  unsigned long order = ilog2(pages - 1) + 1;
  unsigned long count = 0x1 << order;
  unsigned long addr;
  int ret = 0;

  addr = penglai_get_free_pages(GFP_KERNEL,order);
  if (!addr)
  {
    penglai_eprintf("can not get free pages which order is 0x%lx", order );
    return -1;
  }
  ret = SBI_PENGLAI_2(SBI_SM_MEMORY_EXTEND, __pa(addr), count << RISCV_PGSHIFT);

  return ret;
}

int handle_memory_free(enclave_t* enclave)
{
  unsigned long pages = enclave ->ocall_arg0;
  unsigned long paddr = enclave ->ocall_arg1;
  unsigned long order = ilog2(pages - 1) + 1;
  unsigned long count = 0x1 << order;

  if(count != pages)
    return -1;
  free_pages((long unsigned int)__va(paddr), order);

  return 0;
}

int penglai_enclave_resume_for_rerun(enclave_instance_t *enclave_instance, enclave_t *enclave, int resume_id, int isShadow)
{
  unsigned int ocall_func_id;
  int ret;
  unsigned long schrodinger_size, schrodinger_paddr;
  if (enclave)
  {
    ocall_func_id = enclave->ocall_func_id;
    schrodinger_paddr = enclave->ocall_arg0;
    schrodinger_size = enclave->ocall_arg1;
  }
  else
  {
    ocall_func_id = enclave_instance->ocall_func_id;
    schrodinger_paddr = enclave_instance->ocall_arg0;
    schrodinger_size = enclave_instance->ocall_arg1;
  }

  switch(ocall_func_id)
  {
    case OCALL_RETURN_RELAY_PAGE:
    {
      ret = SBI_PENGLAI_5(SBI_SM_RESUME_ENCLAVE, resume_id, RESUME_FROM_OCALL, OCALL_RETURN_RELAY_PAGE, schrodinger_paddr, schrodinger_size);
      
      if(ret == ENCLAVE_NO_MEM)
      {
        if ((ret = penglai_extend_secure_memory()) < 0)
          return ret;
        ret = SBI_PENGLAI_5(SBI_SM_RESUME_ENCLAVE, resume_id, RESUME_FROM_OCALL, OCALL_RETURN_RELAY_PAGE, schrodinger_paddr, schrodinger_size);
      }
      break;
    }
    default:
    {
      penglai_eprintf("penglai_enclave_resume_for_rerun: ocall func id is error\n");
      ret = SBI_PENGLAI_2(SBI_SM_RESUME_ENCLAVE, resume_id, RESUME_FROM_OCALL);
    }
  }
  return ret;
}

int penglai_enclave_ocall(enclave_instance_t *enclave_instance, enclave_t *enclave, int resume_id, int isShadow)
{
  unsigned int ocall_func_id;
  int ret;
  ocall_func_id = enclave->ocall_func_id;
  if(isShadow)
    ocall_func_id = enclave_instance->ocall_func_id;
  switch(ocall_func_id)
  {
    case OCALL_MMAP:
    {
      uintptr_t order, vaddr;
      if(isShadow)
        order = ilog2((enclave_instance->ocall_arg1 >> RISCV_PGSHIFT) - 1) + 1;
      else
        order = ilog2((enclave->ocall_arg1 >> RISCV_PGSHIFT) - 1) + 1;
      vaddr = penglai_get_free_pages(GFP_KERNEL, order);
      if(!vaddr)
      {
        ret = -1;
        penglai_eprintf("penglai_enclave_ocall: OCALL_MMAP  is failed\r\n");
        break;
      }
      ret = SBI_PENGLAI_5(SBI_SM_RESUME_ENCLAVE, resume_id, RESUME_FROM_OCALL, OCALL_MMAP, __pa(vaddr), (1<<order)*RISCV_PGSIZE);
      break;
    }
    case OCALL_UNMAP:
    {
      uintptr_t vaddr, order;
      if(isShadow)
      {
        vaddr = (uintptr_t)__va(enclave_instance->ocall_arg0);
        order = ilog2((enclave_instance->ocall_arg1 >> RISCV_PGSHIFT) - 1) + 1;
      }
      else
      {
        vaddr = (uintptr_t)__va(enclave->ocall_arg0);
        order = ilog2((enclave->ocall_arg1 >> RISCV_PGSHIFT) - 1) + 1;
      }
      
      free_pages(vaddr, order);
      ret = SBI_PENGLAI_3(SBI_SM_RESUME_ENCLAVE, resume_id, RESUME_FROM_OCALL, OCALL_UNMAP);
      break;
    }
    case OCALL_SYS_WRITE:
    {
      if(isShadow)
      {
        ((char*)(enclave_instance->kbuffer))[511] = '\0';
        printk((void*)(enclave_instance->kbuffer));
      }
      else
      {
        ((char*)(enclave->kbuffer))[511] = '\0';
        printk((void*)(enclave->kbuffer));
      }
      ret = SBI_PENGLAI_3(SBI_SM_RESUME_ENCLAVE, resume_id, RESUME_FROM_OCALL, OCALL_SYS_WRITE);
      break;
    }
    case OCALL_SBRK:
    {
      long size;
      uintptr_t vaddr = 0;
      uintptr_t order = 0;
      struct pm_area_struct *pma;
      if(isShadow)
      {
        size = (long)(enclave_instance->ocall_arg1);
        pma = (struct pm_area_struct*)(enclave_instance->ocall_arg0);
      }
      else
      {
        pma = (struct pm_area_struct*)(enclave->ocall_arg0);
        size = (long)(enclave->ocall_arg1);
      }
      
      if(size < 0)
      {
        while(pma)
        {
          pma = (struct pm_area_struct*)__va(pma);
          vaddr = (uintptr_t)__va(pma->paddr);

          order = ilog2((pma->size >> RISCV_PGSHIFT) - 1) + 1;
          pma = pma->pm_next;
          //should be freed after set pma to its next
          free_pages(vaddr, order);
        }
      }
      else
      {
        order = ilog2((size >> RISCV_PGSHIFT) - 1) + 1;
        vaddr = penglai_get_free_pages(GFP_KERNEL, order);
        if(!vaddr)
        {
          penglai_eprintf("penglai_enclave_ocall: OCALL_SBRK is failed\r\n"); 
          ret = -1;
          break;
        }
      }
      ret = SBI_PENGLAI_5(SBI_SM_RESUME_ENCLAVE, resume_id, RESUME_FROM_OCALL, OCALL_SBRK, __pa(vaddr), (1<<order)*RISCV_PGSIZE);
      break;
    }
    default:
    {
      if(ocall_func_id == OCALL_READ_SECT)
      {
        int read;
        if (isShadow)
          read = penglai_outer_read(enclave_instance->ocall_arg0);
        else
          read = penglai_outer_read(enclave->ocall_arg0);
        
        ret = SBI_PENGLAI_4(SBI_SM_RESUME_ENCLAVE, resume_id,RESUME_FROM_OCALL, OCALL_READ_SECT, read);
      }
      else if(ocall_func_id == OCALL_WRITE_SECT)
      {
        int write;
        if (isShadow)
        write = penglai_outer_write(enclave_instance->ocall_arg0);
        else
          write = penglai_outer_write(enclave->ocall_arg0);
        
        ret = SBI_PENGLAI_4(SBI_SM_RESUME_ENCLAVE, resume_id, RESUME_FROM_OCALL, OCALL_WRITE_SECT,write);
      }
      else if (ocall_func_id == OCALL_RETURN_RELAY_PAGE)
      {
        ret = ENCLAVE_RETURN_USER_MODE;
        break;
      }
      else{
        ret = SBI_PENGLAI_2(SBI_SM_RESUME_ENCLAVE, resume_id, RESUME_FROM_OCALL);
      }
    }
  }
  return ret;
}


int penglai_instantiate_enclave_instance(enclave_instance_t **enclave_instance, enclave_t *enclave, struct penglai_enclave_user_param *enclave_param, unsigned long schrodinger_vaddr,
                                        unsigned long schrodinger_size, unsigned long *shadow_eid, int *resume_id)
{
  unsigned long addr, kbuffer;
  unsigned long shm_vaddr, shm_size, schrodinger_paddr;
  int ret;
  struct penglai_enclave_instance_sbi_param enclave_instance_sbi_param;
  spin_lock(&enclave_create_lock);
  *enclave_instance = (enclave_instance_t* )kmalloc(sizeof(enclave_instance_t), GFP_KERNEL);
  // penglai_dprintf("shadow run: get free page\n");
  addr = penglai_get_free_pages(GFP_KERNEL, DEFAULT_SHADOW_ENCLAVE_ORDER);
  if(!addr)
  {
    penglai_eprintf("failed to run enclave: no enough page for enclave stack%x\n", 1<<DEFAULT_SHADOW_ENCLAVE_ORDER);
    return DEFAULT_FREE_ENCLAVE;
  }

  kbuffer = penglai_get_free_pages(GFP_KERNEL, ENCLAVE_DEFAULT_KBUFFER_ORDER);
  if(!kbuffer)
  {
    penglai_eprintf("failed to allocate kbuffer\n");
    return DEFAULT_FREE_ENCLAVE;
  }
  memset((void*)kbuffer, 0, ENCLAVE_DEFAULT_KBUFFER_SIZE);

  // penglai_dprintf("shadow run: get shm page\n");
  shm_vaddr = get_shm(enclave_param->shmid, enclave_param->shm_offset, enclave_param->shm_size);
  shm_size = enclave_param->shm_size;

  enclave_instance_sbi_param.free_page = __pa(addr);
  enclave_instance_sbi_param.sptbr = csr_read(sptbr);
  enclave_instance_sbi_param.size = RISCV_PGSIZE*(1 << DEFAULT_SHADOW_ENCLAVE_ORDER);
  enclave_instance_sbi_param.kbuffer = __pa(kbuffer);
  enclave_instance_sbi_param.kbuffer_size = ENCLAVE_DEFAULT_KBUFFER_SIZE;
  if(shm_vaddr && shm_size)
  {
    enclave_instance_sbi_param.shm_paddr = __pa(shm_vaddr);
    enclave_instance_sbi_param.shm_size = shm_size;
  }
  if(schrodinger_vaddr && schrodinger_size)
  {
    enclave_instance_sbi_param.schrodinger_paddr = __pa(schrodinger_vaddr);
    enclave_instance_sbi_param.schrodinger_size = schrodinger_size;
  }

  /* initialize */
  memset((void*)addr, 0, RISCV_PGSIZE*(1 << DEFAULT_SHADOW_ENCLAVE_ORDER));
  (*enclave_instance)->addr = addr;
  (*enclave_instance)->order = DEFAULT_SHADOW_ENCLAVE_ORDER;
  (*enclave_instance)->kbuffer = kbuffer;
  (*enclave_instance)->kbuffer_size = ENCLAVE_DEFAULT_KBUFFER_SIZE;
  *shadow_eid = enclave_instance_idr_alloc((*enclave_instance));
  enclave_instance_sbi_param.eid_ptr = (unsigned int* )__pa(&(*enclave_instance)->eid);
  enclave_instance_sbi_param.ecall_arg0 = (unsigned long* )__pa(&(*enclave_instance)->ocall_func_id);
  enclave_instance_sbi_param.ecall_arg1 = (unsigned long* )__pa(&(*enclave_instance)->ocall_arg0);
  enclave_instance_sbi_param.ecall_arg2 = (unsigned long* )__pa(&(*enclave_instance)->ocall_arg1);
  enclave_instance_sbi_param.ecall_arg3 = (unsigned long* )__pa(&(*enclave_instance)->ocall_syscall_num);
  enclave_instance_sbi_param.retval = (unsigned long* )__pa(&(*enclave_instance)->retval);
  memcpy(enclave_instance_sbi_param.name, enclave_param->name, NAME_LEN);
  
  schrodinger_paddr = 0;
  if(schrodinger_vaddr && schrodinger_size)
    schrodinger_paddr = __pa(schrodinger_vaddr);
  if(schrodinger_vaddr && !schrodinger_size)
    schrodinger_paddr = DEFAULT_MAGIC_NUMBER; //magic number

  spin_unlock(&enclave_create_lock);
  // penglai_dprintf("shadow run: run enclave\n");
  ret = SBI_PENGLAI_4(SBI_SM_RUN_SHADOW_ENCLAVE, enclave->eid,  __pa(&enclave_instance_sbi_param), schrodinger_paddr, schrodinger_size);
  // penglai_dprintf("shadow run: end run enclave\n");
  while(ret == ENCLAVE_NO_MEM)
  {
    if ((ret = penglai_extend_secure_memory()) < 0)
          return ret;
    ret = SBI_PENGLAI_4(SBI_SM_RUN_SHADOW_ENCLAVE, enclave->eid,  __pa(&enclave_instance_sbi_param), schrodinger_paddr, schrodinger_size);
  }
  *resume_id = (*enclave_instance)->eid;
  return ret;
}

int penglai_enclave_run(struct file *filep, unsigned long args)
{
  struct penglai_enclave_user_param *enclave_param = (struct penglai_enclave_user_param*) args;
  unsigned long eid = enclave_param->eid;
  enclave_t *enclave = NULL;
  enclave_instance_t *enclave_instance = NULL;
  unsigned long satp = 0, shadow_eid = 0, schrodinger_vaddr = 0, schrodinger_size = 0;
  int ret =0, resume_id = 0;

  if(enclave_param->rerun_reason > 0)
  {
    //Re-run shadow enclave
    if(enclave_param->isShadow == 1)
    {
      enclave_instance = get_enclave_instance_by_id(eid);
      if(!enclave_instance)
      {
        penglai_eprintf("rerun enclave: enclave_instance is not exist \n");
        return -EINVAL;
      }
      resume_id = enclave_instance->eid;
    }
    else
    { //Re-run enclave
      enclave = get_enclave_by_id(eid);
      if(!enclave)
      {
        penglai_eprintf("rerun enclave: enclave is not exist \n");
        return -EINVAL;
      }
      satp = enclave->satp;
      resume_id = enclave->eid;
    }
    switch (enclave_param->rerun_reason)
    {
      case RETURN_USER_RELAY_PAGE:
        ret = ENCLAVE_RETURN_MONITOR_MODE;
        break;
      default:
        penglai_eprintf("penglai_enclave_run: rerun reason is error %d\n", enclave_param->rerun_reason);
    }
    goto resume_for_rerun;
  }
  else
  {
    //First time run enclave
    enclave = get_enclave_by_id(eid);
    if(!enclave)
    {
      penglai_eprintf("enclave is not exist \n");
      return -EINVAL;
    }
  }

  // penglai_dprintf("run: begin get get_schrodinger\n");
  //if schrodinger is not zero but size remains zero, it means relay page is transferred from other enclave
  if((enclave_param->schrodinger_id > 0) && (enclave_param->schrodinger_size == 0))
    schrodinger_vaddr = DEFAULT_MAGIC_NUMBER; //magic number just set address is not zero, so the monitor will know relay page is transferred from other enclave
  else
    schrodinger_vaddr = get_schrodinger(enclave_param->schrodinger_id, enclave_param->schrodinger_offset, enclave_param->schrodinger_size);
  schrodinger_size = enclave_param->schrodinger_size;
  if(enclave->type == SHADOW_ENCLAVE)
  {
    // penglai_dprintf("run: begin penglai_instantiate_enclave_instance\n");
    ret = penglai_instantiate_enclave_instance(&enclave_instance, enclave, enclave_param, schrodinger_vaddr,
                                        schrodinger_size, &shadow_eid, &resume_id);
    // penglai_dprintf("run: end penglai_instantiate_enclave_instance\n");
    if (ret == DEFAULT_FREE_ENCLAVE)
    {
      ret = -1;
      goto free_enclave;
    }
    else if (ret == DEFAULT_DESTROY_ENCLAVE)
    {
      ret = -1;
      goto destroy_enclave;
    }
    enclave_param->eid = shadow_eid;
    enclave_param->isShadow = 1;
  }
  else
  {
    uintptr_t schrodinger_paddr = 0;
    satp = enclave->satp;
    if(schrodinger_vaddr && schrodinger_size)
      schrodinger_paddr = __pa(schrodinger_vaddr);
    if(schrodinger_vaddr && !schrodinger_size)
      schrodinger_paddr = DEFAULT_MAGIC_NUMBER; //magic number
    ret = SBI_PENGLAI_3(SBI_SM_RUN_ENCLAVE, enclave->eid, schrodinger_paddr, schrodinger_size);
    resume_id = enclave->eid;
  }
  //handler the ocall from enclave;
resume_for_rerun:
  while((ret == ENCLAVE_TIMER_IRQ) || (ret == ENCLAVE_OCALL) || (ret == ENCLAVE_YIELD) || (ret == ENCLAVE_RETURN_MONITOR_MODE))
  {
    if (ret == ENCLAVE_TIMER_IRQ)
    {
      //FIXME: no we call yield every time there is a time interrupt
      yield();
      ret = SBI_PENGLAI_2(SBI_SM_RESUME_ENCLAVE, resume_id, RESUME_FROM_TIMER_IRQ);
    }
    else if (ret == ENCLAVE_YIELD)
    {
      //FIXME: just sleep
      msleep(1000*120);
      ret = SBI_PENGLAI_2(SBI_SM_RESUME_ENCLAVE, resume_id, RESUME_FROM_TIMER_IRQ);
    }
    else if(ret == ENCLAVE_RETURN_MONITOR_MODE)
    {
      ret = penglai_enclave_resume_for_rerun(enclave_instance, enclave, resume_id, enclave_param->isShadow);  
    }
    else{
      ret = penglai_enclave_ocall(enclave_instance, enclave, resume_id, enclave_param->isShadow);     
    }
  }

  if(enclave->type == SHADOW_ENCLAVE)
    enclave_param->retval = enclave_instance->retval;
  else
    enclave_param->retval = enclave->retval;

  if(ret < 0)
  {
    penglai_eprintf("sbi call run enclave is failed \n");
    goto destroy_enclave;
  }
  else if (ret == ENCLAVE_RETURN_USER_MODE){
    return RETURN_USER_RELAY_PAGE;
  }

  free_enclave:
    if(enclave_param->isShadow == 1)
    {
      free_pages(enclave_instance->addr, enclave_instance->order);
      free_pages(enclave_instance->kbuffer, ENCLAVE_DEFAULT_KBUFFER_ORDER);
      kfree(enclave_instance);
      // penglai_dprintf("run: begin free addr4\n");
      return ret;
    }
    if(get_enclave_by_id(eid) && get_enclave_by_id(eid)->satp == satp)
    {
      destroy_enclave(enclave);
      enclave_idr_remove(eid);
      return ret;
    }
    return -EFAULT;

  destroy_enclave:
    if(get_enclave_by_id(eid) && get_enclave_by_id(eid)->satp == satp)
    {
      destroy_enclave(enclave);
      enclave_idr_remove(eid);
    }
    return -EFAULT;
}

int penglai_enclave_attest(struct file * filep, unsigned long args)
{
  struct penglai_enclave_attest_param *attest_param = (struct penglai_enclave_attest_param*) args;
  unsigned long eid = attest_param->eid;
  enclave_t *enclave;
  int ret =0;
  enclave = get_enclave_by_id(eid);
  if(!enclave)
  {
    penglai_eprintf("enclave is not exist %ld\n", eid);
    return -EINVAL;
  }

  if(enclave->type == SHADOW_ENCLAVE)
    ret = SBI_PENGLAI_3(SBI_SM_ATTEST_SHADOW_ENCLAVE, enclave->eid, __pa(&(attest_param->report)), attest_param->nonce);
  else
    ret = SBI_PENGLAI_3(SBI_SM_ATTEST_ENCLAVE, enclave->eid, __pa(&(attest_param->report)), attest_param->nonce);
  if(ret < 0)
  {
    penglai_eprintf("sbi call attest enclave is failed\n");
  }
  return ret;
}

long penglai_enclave_stop(struct file* filep, unsigned long args)
{
  struct penglai_enclave_user_param * enclave_param = (struct penglai_enclave_user_param*) args;
  unsigned long eid = enclave_param ->eid;
  enclave_t * enclave;
  unsigned long satp;
  int ret =0;

  enclave = get_enclave_by_id(eid);
  if (!enclave)
  {
    penglai_eprintf("enclave is not exist \n");
    return -EINVAL;
  } 

  satp = enclave->satp;
  ret = SBI_PENGLAI_1(SBI_SM_STOP_ENCLAVE, enclave->eid);
  if (ret < 0)
  {
    penglai_eprintf("sbi call stop enclave is failed \n");
  }

  return ret;
}

int penglai_enclave_resume(struct file * filep, unsigned long args)
{
  struct penglai_enclave_user_param * enclave_param = (struct penglai_enclave_user_param*) args;
  unsigned long eid = enclave_param ->eid;
  enclave_t * enclave;
  unsigned long satp;
  int ret =0;

  enclave = get_enclave_by_id(eid);
  if (!enclave)
  {
    penglai_eprintf("enclave is not exist \n");
    return -EINVAL;
  } 

  satp = enclave->satp;
  ret = SBI_PENGLAI_2(SBI_SM_RESUME_ENCLAVE, enclave->eid, RESUME_FROM_STOP);
  if (ret < 0)
  {
    penglai_eprintf("sbi call resume enclave is failed \n");
    goto destroy_enclave;
  }

  return ret;

  destroy_enclave:
    spin_lock(&enclave_create_lock);
    if(get_enclave_by_id(eid) && get_enclave_by_id(eid)->satp == satp)
    {
      destroy_enclave(enclave);
      enclave_idr_remove(eid);
    }
    spin_unlock(&enclave_create_lock);
    return -EFAULT;
}

long penglai_enclave_ioctl(struct file* filep, unsigned int cmd, unsigned long args)
{
  char ioctl_data[1024];
  int ioc_size, ret;
  ioc_size = _IOC_SIZE(cmd);
  if (ioc_size > sizeof(ioctl_data))
  {
    penglai_eprintf("ioc_data buff is not enough\n");
    return -EFAULT;
  }

  if(copy_from_user(ioctl_data, (void*)args, ioc_size))
  {
    penglai_eprintf("copy from the user is failed\n");
    return -EFAULT;
  }
  switch(cmd)
  {
    case PENGLAI_ENCLAVE_IOC_CREATE_ENCLAVE:
     ret = penglai_enclave_create(filep, (unsigned long)ioctl_data);
      break;
    case PENGLAI_ENCLAVE_IOC_RUN_ENCLAVE:
      ret = penglai_enclave_run(filep, (unsigned long)ioctl_data);
      break;
    case PENGLAI_ENCLAVE_IOC_ATTEST_ENCLAVE:
      ret = penglai_enclave_attest(filep, (unsigned long)ioctl_data);
      break;
    case PENGLAI_ENCLAVE_IOC_STOP_ENCLAVE:
      ret = penglai_enclave_stop(filep, (unsigned long)ioctl_data);
      break;
    case PENGLAI_ENCLAVE_IOC_RESUME_ENCLAVE:
      ret = penglai_enclave_resume(filep, (unsigned long)ioctl_data);
      break;
    case PENGLAI_ENCLAVE_IOC_DESTROY_ENCLAVE:
      ret = penglai_enclave_destroy(filep, (unsigned long)ioctl_data);
      break;
    case PENGLAI_SHMGET:
      ret = penglai_shmget(filep, (unsigned long)ioctl_data);
      break;
    case PENGLAI_SHMAT:
      ret = penglai_shmat(filep, (unsigned long)ioctl_data);
      break;
    case PENGLAI_SHMDT:
      ret = penglai_shmdt(filep, (unsigned long)ioctl_data);
      break;
    case PENGLAI_SHMCTL:
      ret = penglai_shmctl(filep, (unsigned long)ioctl_data);
      break;
    case PENGLAI_SCHRODINGER_GET:
      ret = penglai_schrodinger_get(filep, (unsigned long)ioctl_data);
      break;
    case PENGLAI_SCHRODINGER_AT:
      ret = penglai_schrodinger_at(filep, (unsigned long)ioctl_data);
      break;
    case PENGLAI_SCHRODINGER_DT:
      ret = penglai_schrodinger_dt(filep, (unsigned long)ioctl_data);
      break;
    case PENGLAI_SCHRODINGER_CTL:
      ret = penglai_schrodinger_ctl(filep, (unsigned long)ioctl_data);
      break;
    case PENGLAI_PERSISTENCY_INIT:
    {
      ret = penglai_fs_persistency_init(filep, (unsigned long)ioctl_data);
      break;
    }
     default:
     penglai_eprintf("ioctl is failed cmd:%lx create %lx\n", cmd, PENGLAI_ENCLAVE_IOC_CREATE_ENCLAVE);
      return -EFAULT;
  }
  if (copy_to_user((void*)args, ioctl_data, ioc_size))
  {
    penglai_eprintf("copy to user is failed \n");
    return -EFAULT;
  }
  return ret;
}
