#define LOG_TAG "DMMU"
//#define LOG_NDEBUG 0

#ifdef __ANDROID__

#include <utils/Log.h>
#include <cutils/atomic.h>
#include <hardware/hardware.h>

#endif

#ifdef HAVE_ANDROID_OS
#include "fcntl.h"
#else
#include "sys/fcntl.h"
#endif	/* BUILD_WITH_ANDROID */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "sys/stat.h"
#include "sys/ioctl.h"
#include "sys/mman.h"
#include "fcntl.h"
#include <unistd.h>

#include "dmmu.h"

#define PAGE_SIZE	4096

#define PHYS_ADDR_TABLE_TEST 0


//#define DMMU_DBG 1


#if 0
#define LINE()								\
	do {								\
		printf("==>%s L%03d\n", __FUNCTION__, __LINE__);	\
	} while (0)
#define ENTER()								\
	do {								\
		printf("L%03d ENTER %s\n", __LINE__, __FUNCTION__);	\
	} while (0)
#define LEAVE()								\
	do {								\
		printf("L%03d LEAVE %s\n", __LINE__, __FUNCTION__);	\
	} while (0)
#define MY_DBG(sss, aaa...)								\
	do {										\
		printf("L%03d DEBUG %s, \n" sss, __LINE__, __FUNCTION__, ##aaa);	\
	} while (0)
#else

#define ENTER()									\
	do {									\
	} while (0)
#define LEAVE()									\
	do {									\
	} while (0)
#define MY_DBG(sss, aaa...)						\
	do {								\
	} while (0)
#endif


static int dmmu_fd = -1;
static int g_dmmu_open_count = 0;


int dmmu_init()
{
	ENTER();

	//	MY_DBG("DMMU_GET_BASE_PHYS=0x%x, DMMU_MAP_USER_MEM=0x%x, DMMU_UNMAP_USER_MEM=0x%x", 
	//		   DMMU_GET_BASE_PHYS, DMMU_MAP_USER_MEM, DMMU_UNMAP_USER_MEM);

	if (dmmu_fd < 0) {
		dmmu_fd = open(DMMU_DEV_NAME, O_RDWR);
		if (dmmu_fd < 0) {
			printf("DMMU: can't open device: %s\n", DMMU_DEV_NAME);
			return -1;
		}
	}
	//	android_atomic_inc(&g_dmmu_open_count);
	g_dmmu_open_count++;

	//MY_DBG("<------g_dmmu_open_count: %d\n", g_dmmu_open_count);
	printf("<------g_dmmu_open_count: %d\n", g_dmmu_open_count);

	return 0;
}

int dmmu_deinit()
{
	ENTER();

	if (dmmu_fd < 0) {
		printf("dmmu_fd < 0\n");
		return -1;
	}

	//	android_atomic_dec(&g_dmmu_open_count);
	g_dmmu_open_count--;

	if (g_dmmu_open_count == 0) {
		printf("g_dmmu_open_count is zero!\n");
		close(dmmu_fd); 		/* close fd */
		dmmu_fd = -1;
	}

	return 0;
}

int dmmu_set_table_flag(void)
{
	int ret = 0;
	int flag = VIDEO_TABLE_FLAGE;

	if (dmmu_fd < 0) {
		printf("dmmu_fd < 0\n");
		return -1;
	}

	ret = ioctl(dmmu_fd, DMMU_SET_TABLE_FLAG, &flag);
	if (ret < 0) {
		printf("DMMU_SET_TABLE_FLAG failed!!!\n");
		return -1;
	}
	return 0;
}

int dmmu_get_page_table_base_phys(unsigned int *phys_addr)
{
	int ret = 0;
	ENTER();
	if (phys_addr == NULL) {
		printf("phys_addr is NULL!\n");
		return -1;
	}

	if (dmmu_fd < 0) {
		printf("dmmu_fd < 0\n");
		return -1;
	}

	ret = ioctl(dmmu_fd, DMMU_GET_PAGE_TABLE_BASE_PHYS, phys_addr);
	if (ret < 0) {
		printf("dmmu_get_page_table_base_phys_addr ioctl(DMMU_GET_BASE_PHYS) failed, ret=%d\n", ret);
		return -1;
	}

	printf("==>%s L%d: tlb_table_base phys_addr = 0x%08x\n", __func__, __LINE__, *phys_addr);
	return 0;
}

/* NOTE: page_start and page_end maybe used both by two buffer. */
int dmmu_map_user_mem(void * vaddr, int size)
{
	ENTER();
	//int i;

	if (dmmu_fd < 0) {
		printf("dmmu_fd < 0\n");
		return -1;
	}

	//	printf("==>%s L%d: vaddr=%p, size=%d\n", __func__, __LINE__, vaddr, size);

	dmmu_match_user_mem_tlb(vaddr, size);

	struct dmmu_mem_info info;
	info.vaddr = vaddr;
	info.size = size;
	info.paddr = 0;
	info.pages_phys_addr_table = NULL;
	/* page count && offset */
	init_page_count(&info);

	int ret = 0;
	ret = ioctl(dmmu_fd, DMMU_MAP_USER_MEM, &info);
	if (ret < 0) {
		printf("dmmu_map_user_memory ioctl(DMMU_MAP_USER_MEM) failed, ret=%d\n", ret);
		return -1;
	}

	return 0;
}

int dmmu_unmap_user_mem(void * vaddr, int size)
{
	ENTER();

	if (dmmu_fd < 0) {
		printf("dmmu_fd < 0\n");
		return -1;
	}

	struct dmmu_mem_info info;
	info.vaddr = vaddr;
	info.size = size;

	int ret = 0;
	ret = ioctl(dmmu_fd, DMMU_UNMAP_USER_MEM, &info);
	if (ret < 0) {
		printf("dmmu_unmap_user_memory ioctl(DMMU_UNMAP_USER_MEM) failed, ret=%d\n", ret);
		return -1;
	}

	return 0;
}

/* NOTE: page_start and page_end maybe used both by two buffer. */
int dmmu_get_memory_physical_address(struct dmmu_mem_info * mem)
{
	ENTER();
	//int i;

	if (dmmu_fd < 0) {
		printf("dmmu_fd < 0\n");
		return -1;
	}

	if ( mem == NULL ) {
		printf("mem == NULL\n");
		return -1;
	}
	if ( mem->pages_phys_addr_table != NULL ) {
		printf("mem->pages_phys_addr_table != NULL\n");
		return -1;
	}

	mem->paddr = 0;
	/* page count && offset */
	init_page_count(mem);

	/* alloc page table space, pages_table filled by dmmu kernel driver. */
	if ( 1 ) {
		void *pages_phys_addr;
		int page_table_size = mem->page_count * sizeof(int);
		pages_phys_addr = (void *)malloc(page_table_size);
		memset((void*)pages_phys_addr, 0, page_table_size);
		MY_DBG("pages_phys_addr: %p\n", pages_phys_addr);
		mem->pages_phys_addr_table = pages_phys_addr;
	}

	if ( mem->pages_phys_addr_table ) {
		int ret = 0;
		ret = ioctl(dmmu_fd, DMMU_GET_TLB_PHYS, mem);
		if (ret < 0) {
			printf("get dmmu tlb phys addr failed!\n");
			return -1;
		}
		MY_DBG("Map mem phys_addr = 0x%08x\n", mem->paddr);
	}
	return 0;
}

int dmmu_release_memory_physical_address(struct dmmu_mem_info* mem)
{
	if ( mem->pages_phys_addr_table ) {
		free(mem->pages_phys_addr_table);
		mem->pages_phys_addr_table = NULL;
	}
	return 0;
}


/* NOTE: page_start and page_end maybe used both by two buffer. */
int dmmu_map_user_memory(struct dmmu_mem_info* mem)
{
	return dmmu_map_user_mem(mem->vaddr, mem->size);
}

/* NOTE: page_start and page_end maybe used both by two buffer. */
int dmmu_unmap_user_memory(struct dmmu_mem_info* mem)
{
	return dmmu_unmap_user_mem(mem->vaddr, mem->size);
}

int dmmu_match_user_mem_tlb(void * vaddr, int size)
{
	if (vaddr==NULL) 
		return 1;
	volatile unsigned char * pc;
	pc = (unsigned char *)vaddr;
	int pn = size/PAGE_SIZE;
	int pg;
	for(pg=0; pg<pn; pg++ ) {
		//volatile unsigned char c = *( volatile unsigned char*)pc;
		pc += PAGE_SIZE;
	}

	return 0;
}
