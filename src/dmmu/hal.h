
#ifndef __HAL_H__
#define __HAL_H__

#include "jz_cim.h"

// android/hardware/libhardware/include/hardware/camera.h
struct camera_memory;
typedef void (*camera_release_memory)(struct camera_memory *mem);

typedef struct camera_memory {
    void *data;
    size_t size;
    void *handle;
    camera_release_memory release;
} camera_memory_t;

// android/hardware/xb4780/libcamera2/include/CameraDeviceCommon.h
struct camera_buffer {
	struct camera_memory* common;
	struct dmmu_mem_info dmmu_info;
	CameraYUVMeta yuvMeta[5];
	int index;
	int offset;
	int size;
	int nr;
	int fd;
	int paddr;
};


#endif //__HAL_H__
