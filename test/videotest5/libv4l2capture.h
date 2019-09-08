#ifndef LIBV4L2CAPTURE_H
#define LIBV4L2CAPTURE_H


#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/videodev2.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

typedef unsigned int U32;

#define CLEAR(x) memset (&(x), 0, sizeof (x))
#define UNUSED(expr) do { (void)(expr); } while (0)

/**
 * capture parameters
 */
struct cap_param
{
    char* dev_name; /**< video device location, eg: /dev/video0 */
    int width; /**< video width */
    int height; /**< video height */
    U32 pixfmt; /**< video pixel format */
    int rate; /**< video rate */
};

/**< capture handle */

struct buffer_t
{
    void* start;
    size_t length;
};

struct cap_handle
{
    int fd;
    int image_size;
    struct buffer_t* buffers;
    unsigned int nbuffers;
    struct cap_param params;
    int quit;
    unsigned long image_counter;
    // v4l2 buffer get/put
    struct v4l2_buffer v4lbuf;
    int v4lbuf_put;     // 0/1
};

/**
 * @brief Open a capture device
 * @param param the capture parameters
 * @return the capture handle
 */
struct cap_handle* capture_open ( struct cap_param param );
/**
 * @brief Close a capture device
 * @param handle the capture handle to be closed
 */
void capture_close ( struct cap_handle* handle );

/**
 * @brief Start a capture stream
 * @param handle the capture handle
 */
int capture_start ( struct cap_handle* handle );

/**
 * @brief Stop a capture stream
 * @param handle the capture handle
 */
void capture_stop ( struct cap_handle* handle );

/**
 * @brief Fetch captured image on every step
 * Note: this is non-consistent with capture_loop()
 *
 * @param handle the capture handle
 * @param pbuf the point to the output image buffer
 * @param plen the point to the length buffer
 * @return -1 if timeout or error, 0 if ok, > 0 if non fatal error
 */
int capture_get_data ( struct cap_handle* handle, void** pbuf, int* plen );

int capture_query_brightness ( struct cap_handle* handle, int* min, int* max, int* step );
int capture_get_brightness ( struct cap_handle* handle, int* val );
int capture_set_brightness ( struct cap_handle* handle, int val );

int capture_query_contrast ( struct cap_handle* handle, int* min, int* max, int* step );
int capture_get_contrast ( struct cap_handle* handle, int* val );
int capture_set_contrast ( struct cap_handle* handle, int val );

int capture_query_saturation ( struct cap_handle* handle, int* min, int* max, int* step );
int capture_get_saturation ( struct cap_handle* handle, int* val );
int capture_set_saturation ( struct cap_handle* handle, int val );


#endif //LIBV4L2CAPTURE_H
