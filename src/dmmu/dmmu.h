#ifndef _JZ_DMMU_H_
#define _JZ_DMMU_H_

#include <qqt-local.h>

__BEGIN_DECLS

#define DMMU_DEV_NAME "/dev/dmmu"
#define DMMU_PAGE_SIZE 4096

#define DMMU_IOCTL_MAGIC 'd'

#define DMMU_GET_PAGE_TABLE_BASE_PHYS		_IOW(DMMU_IOCTL_MAGIC, 0x01, unsigned int)
#define DMMU_GET_BASE_PHYS                  _IOR(DMMU_IOCTL_MAGIC, 0x02, unsigned int)
#define DMMU_MAP_USER_MEM		            _IOWR(DMMU_IOCTL_MAGIC, 0x11, struct dmmu_mem_info)
#define DMMU_UNMAP_USER_MEM		            _IOW(DMMU_IOCTL_MAGIC, 0x12, struct dmmu_mem_info)
#define DMMU_GET_TLB_PHYS                   _IOWR(DMMU_IOCTL_MAGIC, 0x13, struct dmmu_mem_info)
#define DMMU_SET_TABLE_FLAG 	            _IOW(DMMU_IOCTL_MAGIC, 0x34, int)

#define VIDEO_TABLE_FLAGE 1

struct dmmu_mem_info {
    int size;
    int page_count;

    unsigned int paddr;

    void *vaddr;
    void *pages_phys_addr_table;

    unsigned int start_offset;
    unsigned int end_offset;
};

static inline void init_page_count(struct dmmu_mem_info *info)
{
    int page_count;
#ifdef __EMBEDDED_LINUX__
    unsigned int start;			/* page start */
    unsigned int end;			/* page end */

    start = ((unsigned int)info->vaddr) & (~(DMMU_PAGE_SIZE-1));
    end = ((unsigned int)info->vaddr + (info->size-1)) & (~(DMMU_PAGE_SIZE-1));
    page_count = (end - start)/(DMMU_PAGE_SIZE) + 1;

    info->page_count = page_count;
    info->start_offset = (unsigned int)info->vaddr - start;
    info->end_offset = ((unsigned int)info->vaddr + info->size) - end;
//  printf("<----start_offset: %x, end_offset: %x, page_count: %d\n", info->start_offset, info->end_offset, page_count);
#else
    unsigned long start;			/* page start */
    unsigned long end;			/* page end */

    start = ((unsigned long)info->vaddr) & (~(DMMU_PAGE_SIZE-1));
    end = ((unsigned long)info->vaddr + (info->size-1)) & (~(DMMU_PAGE_SIZE-1));
    page_count = (end - start)/(DMMU_PAGE_SIZE) + 1;

    info->page_count = page_count;
    info->start_offset = (unsigned long)info->vaddr - start;
    info->end_offset = ((unsigned long)info->vaddr + info->size) - end;
//  printf("<----start_offset: %x, end_offset: %x, page_count: %d\n", info->start_offset, info->end_offset, page_count);
#endif

    return;
}

static inline int dump_mem_info(struct dmmu_mem_info *mem, char * description)
{
    if (mem == NULL) {
        printf("mem is NULL!\n");
        return -1;
    }
    printf("mem: %p, \t%s\n", mem, description?description:"");
    printf("\tvaddr= %p\n", mem->vaddr);
    printf("\tsize= %d (0x%x)\n", mem->size, mem->size);
    printf("\tpaddr= 0x%08x\n", mem->paddr);
    printf("\tpage_count= %d\n", mem->page_count);
    printf("\tpages_phys_addr_table=%p\n", mem->pages_phys_addr_table);
    printf("\tstart_offset= %d\n", mem->start_offset);
    printf("\tend_offset= %d\n", mem->end_offset);

    return 0;
}

enum REQUIRE_ALLOC_PAGE_TABLE {
    NO_REQUIRED = 0,
    REQUIRED = 1,
};

QQTSHARED_EXPORT extern int dmmu_init();
QQTSHARED_EXPORT extern int dmmu_set_table_flag(void);
QQTSHARED_EXPORT extern int dmmu_init_with_set_page_table(unsigned int * phys_addr, int size);
QQTSHARED_EXPORT extern int dmmu_deinit();
QQTSHARED_EXPORT extern int dmmu_get_page_table_base_phys(unsigned int * phys_addr);
QQTSHARED_EXPORT extern int dmmu_set_page_table(unsigned int * phys_addr, int size);
QQTSHARED_EXPORT extern int dmmu_map_user_memory(struct dmmu_mem_info* mem);
QQTSHARED_EXPORT extern int dmmu_unmap_user_memory(struct dmmu_mem_info* mem);

QQTSHARED_EXPORT extern int dmmu_map_user_mem(void * vaddr, int size);
QQTSHARED_EXPORT extern int dmmu_unmap_user_mem(void * vaddr, int size);

QQTSHARED_EXPORT extern int dmmu_match_user_mem_tlb(void * vaddr, int size);

QQTSHARED_EXPORT extern int dmmu_get_memory_physical_address(struct dmmu_mem_info* mem);
QQTSHARED_EXPORT extern int dmmu_release_memory_physical_address(struct dmmu_mem_info* mem);

__END_DECLS

#endif	/*  _JZ_DMMU_H_ */
