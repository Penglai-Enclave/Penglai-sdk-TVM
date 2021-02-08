#include <linux/mm.h>
#include <linux/file.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/miscdevice.h>
#include <linux/pt_area.h>
#include <asm/sbi.h>
#include "penglai-enclave-driver.h"
#include "penglai-enclave-ioctl.h"
#include "penglai-schrodinger.h"
#include "riscv64.h"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("enclave_ioctl");
MODULE_AUTHOR("LuXu");
MODULE_VERSION("enclave_ioctl");

extern unsigned long va_pa_offset;
unsigned long penglai_get_free_pages(gfp_t gfp_mask, unsigned int order)
{
  unsigned long va;
  int ret;
  va = __get_free_pages(gfp_mask, order);
  if (order < 9 )
  {
    struct pt_entry_t split_pte;
    split_pte.pte = 0;
    split_pte.pte_addr = 0;
    ret = SBI_PENGLAI_3(SBI_SM_SPLIT_HUGE_PAGE, __pa(va), (1<<order)*4096, __pa(&split_pte));
    if (split_pte.pte_addr != 0)
    {
      char * new_pt_pte_page = alloc_pt_pte_page();
      ret = SBI_PENGLAI_2(SBI_SM_MAP_PTE, split_pte.pte_addr, __pa(new_pt_pte_page));
    }
  }
  return va;
}
static int dev_open(struct inode *inodep, struct file *filep)
{
  filep->private_data = kzalloc(sizeof(struct dev_private_data_t), GFP_KERNEL);

  if(!filep->private_data)
  {
    penglai_eprintf("dev_open: failed to allocate private_data\n");
    return -1;
  }

  return 0;
}

static int dev_release(struct inode *inodep, struct file *filep)
{
  if(filep->private_data)
  {
    kfree(filep->private_data);
  }

  return 0;
}

static int dev_mmap(struct file* filep, struct vm_area_struct *vma)
{
  struct dev_private_data_t* dev_data = filep->private_data;
  if(!(dev_data->mmap_vaddr) || dev_data->mmap_size < (vma->vm_end - vma->vm_start))
  {
    penglai_eprintf("mmap: no enough data to mmap\n");
    return -1;
  }

  unsigned long addr = dev_data->mmap_vaddr;
  unsigned long size = vma->vm_end - vma->vm_start;
  unsigned long size0 = 0;
  for(size0 = 0; size0 < size; size0 += RISCV_PGSIZE)
  {
    struct page* page = virt_to_page(addr + size0);
    // get_page(page);
  }
  if(remap_pfn_range(vma, vma->vm_start, virt_to_pfn(addr), vma->vm_end - vma->vm_start, vma->vm_page_prot))
  {
    penglai_eprintf("mmap: failed to mmap\n");
    for(size0 = 0; size0 < size; size0 += RISCV_PGSIZE)
    {
      struct page* page = virt_to_page(addr + size0);
      // put_page(page);
    }
    return -1;
  }

  return 0;
}

static const struct file_operations enclave_ops = {
  .open = dev_open,
  .owner = THIS_MODULE,
  .mmap = dev_mmap,
  .unlocked_ioctl = penglai_enclave_ioctl,
  .release = dev_release,
};

struct miscdevice enclave_dev = {
  .minor = MISC_DYNAMIC_MINOR,
  .name = "penglai_enclave_dev",
  .fops = &enclave_ops,
  .mode = 0666,
};

struct pt_page_list{
  //struct pt_page_list *prev_page;
  struct pt_page_list *next_page;
};

extern char *pt_area_vaddr;
extern unsigned long pt_area_pages;

extern int PGD_PAGE_ORDER;
extern int PMD_PAGE_ORDER;
static int enclave_ioctl_init(void)
{
  int ret;
  unsigned long addr;
  penglai_printf("enclave_ioctl_init...\n");

  //register enclave_dev
  ret=misc_register(&enclave_dev);
  penglai_printf("enclave_dev minor %d\n", enclave_dev.minor);
  if(ret < 0)
  {
    penglai_eprintf("register enclave_dev failed!\n");
    goto deregister_device;
  }

  //allocate bitmap
  struct sysinfo s_info;
  si_meminfo(&s_info);
  unsigned long bitmap_bytes = s_info.totalram * sizeof(int);
  unsigned long bitmap_pages = (bitmap_bytes % PAGE_SIZE) == 0 ? bitmap_bytes >> PAGE_SHIFT : (bitmap_bytes >> PAGE_SHIFT) + 1;
  unsigned long order = ilog2(bitmap_pages -1) + 1;
  if (order < 9)
    order = 9;
  uintptr_t bitmap = penglai_get_free_pages(GFP_KERNEL, order);
  if(!bitmap)
  {
    penglai_eprintf("failed to allocate %lu page(s)\n", ((unsigned long) 0x1)<<order);
    ret = -ENOMEM;
    goto deregister_device;
  }
  bitmap_pages = 1 << order;
  memset(bitmap, 0, (bitmap_pages << PAGE_SHIFT));
  penglai_printf("total %lupages, bitmap_pages need %lu, allocate %lu page(s)\n", s_info.totalram, bitmap_pages, (unsigned long)1<<order);
  //broadcast to other harts
  ret = SBI_PENGLAI_4(SBI_SM_INIT, __pa(pt_area_vaddr), pt_area_pages << PAGE_SHIFT,
      __pa(bitmap), bitmap_pages << PAGE_SHIFT);
  // asm volatile ("li a6, 0x100100\n\t" "li a7, 84\n\t" "ecall\n\t");
  penglai_printf("sm init is finish\n");
  if(ret)
  {
    penglai_eprintf("failed to create mbitmap\n");
    goto free_bitmap;
  }
  ret = SBI_PENGLAI_2(SBI_SM_PT_AREA_SEPARATION, PGD_PAGE_ORDER, PMD_PAGE_ORDER);

  unsigned long schrodinger_addr = penglai_get_free_pages(GFP_KERNEL, DEFAULT_SCHRODINGER_ORDER);
  if(schrodinger_addr)
  {
    ret = schrodinger_init(schrodinger_addr, RISCV_PGSIZE * (1 << DEFAULT_SCHRODINGER_ORDER));
    if(ret != 0)
    {
      free_pages(schrodinger_addr, DEFAULT_SCHRODINGER_ORDER);
      penglai_eprintf("failed to alloc schrodinger mem\n");
      goto free_bitmap;
    }
  }
  else
  {
    penglai_eprintf("failed to alloc schrodinger mem\n");
    goto free_bitmap;
  }
  unsigned long sptbr = csr_read(sptbr);
  penglai_printf("register_chrdev succeeded!\n");
  return 0;
  
free_bitmap:
  if(bitmap)
  {
    free_pages(bitmap, order);
  }

deregister_device:
  misc_deregister(&enclave_dev);
  return ret;
}

static void enclave_ioctl_exit(void)
{
  //unsigned long size, addr, order, count;
  penglai_printf("enclave_ioctl_exit...\n");
  misc_deregister(&enclave_dev);
  return;
}

module_init(enclave_ioctl_init);
module_exit(enclave_ioctl_exit);
