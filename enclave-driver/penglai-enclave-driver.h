#ifndef _PENGLAI_ENCLAVE_DRIVER
#define _PENGLAI_ENCLAVE_DRIVER

#define DEFAULT_SECURE_PAGES_ORDER 9
#define DEFAULT_SHADOW_ENCLAVE_ORDER 6
#define DEFAULT_MEMORY_EXTEND_NUM 3

struct dev_private_data_t
{
  unsigned long mmap_vaddr;
  unsigned long mmap_size;
};

struct pt_entry_t
{
  unsigned long pte_addr;
  unsigned long pte;
};
unsigned long penglai_get_free_pages(gfp_t gfp_mask, unsigned int order);

#define penglai_printf(fmt, ...) printk("PENGLAI MODULE: "fmt, ##__VA_ARGS__)
#define penglai_eprintf(fmt, ...) printk("[ERROR] PENGLAI MODULE: "fmt, ##__VA_ARGS__)
#define penglai_dprintf(fmt, ...) printk("[DEBUG] PENGLAI MODULE: "fmt, ##__VA_ARGS__)
#endif
