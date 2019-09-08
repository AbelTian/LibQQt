#include <libv4l2capture.h>


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

static int xioctl ( int fd, int request, void* arg )
{
    int r;
    do
        r = ioctl ( fd, request, arg );
    while ( -1 == r && EINTR == errno );
    return r;
}

static int init_mmap ( struct cap_handle* handle )
{
    struct v4l2_requestbuffers req;
    CLEAR ( req );

    req.count = 4;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;

    if ( xioctl ( handle->fd, VIDIOC_REQBUFS, &req ) == -1 )
    {
        if ( EINVAL == errno )
        {
            printf ( "--- %s does not support memory mapping\n",
                     handle->params.dev_name );
            return -1;
        }
        else
        {
            printf ( "--- %s VIDIOC_REQBUFS failed\n", handle->params.dev_name );
            return -1;
        }
    }

    if ( req.count < 2 )
    {
        printf ( "--- Insufficient buffer memory on %s\n",
                 handle->params.dev_name );
        return -1;
    }

    handle->buffers = (buffer_t*)calloc ( req.count, sizeof ( struct buffer_t ) );
    if ( !handle->buffers )
    {
        printf ( "--- Calloc memory failed\n" );
        return -1;
    }

    for ( handle->nbuffers = 0; handle->nbuffers < req.count; ++handle->nbuffers )
    {
        struct v4l2_buffer buf;
        CLEAR ( buf );
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = handle->nbuffers;
        if ( xioctl ( handle->fd, VIDIOC_QUERYBUF, &buf ) == -1 )
        {
            printf ( "--- Index: %d, VIDIOC_QUERYBUF failed\n", handle->nbuffers );
            goto err;
        }
        handle->buffers[handle->nbuffers].length = buf.length;
        handle->buffers[handle->nbuffers].start = mmap ( NULL, buf.length,
                                                         PROT_READ | PROT_WRITE, MAP_SHARED, handle->fd, buf.m.offset );
        if ( MAP_FAILED == handle->buffers[handle->nbuffers].start )
        {
            printf ( "--- Index: %d, memory map failed\n", handle->nbuffers );
            goto err;
        }
    }

    printf ( "+++ Device initialized\n" );
    return 0;

err:
    while ( handle->nbuffers > 0 )
    {
        handle->nbuffers--;
        munmap ( handle->buffers[handle->nbuffers].start,
                 handle->buffers[handle->nbuffers].length );
    }

    free ( handle->buffers );
    handle->buffers = NULL;
    return -1;
}

static int init_device ( struct cap_handle* handle )
{
    if ( handle->fd == -1 )
    {
        printf ( "--- Open the device firstly!\n" );
        return -1;
    }

    struct v4l2_capability cap;
    struct v4l2_cropcap cropcap;
    struct v4l2_crop crop;
    struct v4l2_format fmt;
    struct v4l2_streamparm sparam;

    if ( xioctl ( handle->fd, VIDIOC_QUERYCAP, &cap ) == -1 )
    {
        if ( EINVAL == errno )
        {
            printf ( "--- %s is no V4L2 device\n", handle->params.dev_name );
            return -1;
        }
        else
        {
            printf ( "--- device: %s VIDIOC_QUERYCAP failed\n",
                     handle->params.dev_name );
            return -1;
        }
    }

    if ( ! ( cap.capabilities & V4L2_CAP_VIDEO_CAPTURE ) )
    {
        printf ( "--- %s is no video capture device\n", handle->params.dev_name );
        return -1;
    }

    if ( ! ( cap.capabilities & V4L2_CAP_STREAMING ) )
    {
        printf ( "--- %s does not support streaming\n", handle->params.dev_name );
        return -1;
    }

    // set crop, not all capture support crop!
    CLEAR ( cropcap );
    cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if ( xioctl ( handle->fd, VIDIOC_CROPCAP, &cropcap ) == 0 ) // supported
    {
        crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        crop.c = cropcap.defrect;

        if ( xioctl ( handle->fd, VIDIOC_S_CROP, &crop ) == -1 )
        {
            switch ( errno )
            {
                case EINVAL:
                    break;
                default:
                    break;
            }

            printf (
                "!!! Set crop to (%d, %d, %d, %d) failed. Don't panic, not all capture device support crop!\n",
                crop.c.left, crop.c.top, crop.c.width, crop.c.height );
        }
        else
        {
            printf ( "+++ Set crop to (%d, %d, %d, %d) successfully!\n",
                     crop.c.left, crop.c.top, crop.c.width, crop.c.height );
        }
    }

    // set frame format
    CLEAR ( fmt );
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width = handle->params.width;
    fmt.fmt.pix.height = handle->params.height;
    fmt.fmt.pix.pixelformat = handle->params.pixfmt;
    fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;

    if ( xioctl ( handle->fd, VIDIOC_S_FMT, &fmt ) == -1 )
    {
        printf ( "--- Set pixal format %s VIDIOC_S_FMT failed!\n",
                 handle->params.dev_name );
        return -1;
    }
    handle->image_size = fmt.fmt.pix.sizeimage;

    // check setting result
    if ( fmt.fmt.pix.width != handle->params.width
         || fmt.fmt.pix.height != handle->params.height )
    {
        printf (
            "--- Set resolution to (%d, %d) failed, the size your camera supports are (%d, %d)\n",
            handle->params.width, handle->params.height, fmt.fmt.pix.width,
            fmt.fmt.pix.height );
        return -1;
    }

    unsigned int min;
    min = fmt.fmt.pix.width * 2;
    if ( fmt.fmt.pix.bytesperline < min )
        fmt.fmt.pix.bytesperline = min;
    min = fmt.fmt.pix.bytesperline * fmt.fmt.pix.height;
    if ( fmt.fmt.pix.sizeimage < min )
        fmt.fmt.pix.sizeimage = min;

    // set capture params
    CLEAR ( sparam );
    sparam.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    sparam.parm.capture.capturemode = V4L2_MODE_HIGHQUALITY;
    sparam.parm.capture.capability = V4L2_CAP_TIMEPERFRAME;
    sparam.parm.capture.timeperframe.denominator = handle->params.rate;
    sparam.parm.capture.timeperframe.numerator = 1;
    if ( xioctl ( handle->fd, VIDIOC_S_PARM, &sparam ) == -1 )
    {
        printf ( "--- Set capture params failed\n" );
        return -1;
    }

    // The new 720P camera on daogou must set this in order to work properly!
    int input = 1;
    if ( ioctl ( handle->fd, VIDIOC_S_INPUT, &input ) < 0 )
    {
        printf ( "!!! VIDIOC_S_INPUT failed\n" );
    }

    return init_mmap ( handle );
}

struct cap_handle* capture_open ( struct cap_param param )
{
    int ret;
    struct cap_handle* handle = (struct cap_handle*)malloc ( sizeof ( struct cap_handle ) );
    if ( !handle )
    {
        printf ( "--- malloc capture handle failed\n" );
        return NULL;
    }

    CLEAR ( *handle );
    handle->quit = 0;
    handle->image_counter = 0;
    handle->v4lbuf_put = 1;
    handle->params.dev_name = param.dev_name;
    handle->params.width = param.width;
    handle->params.height = param.height;
    handle->params.pixfmt = param.pixfmt;
    handle->params.rate = param.rate;

    struct stat st;
    if ( -1 == stat ( handle->params.dev_name, &st ) )
    {
        printf ( "--- Cannot identify video device %s: %d, %s\n",
                 handle->params.dev_name, errno, strerror ( errno ) );
        goto err;
    }

    if ( !S_ISCHR ( st.st_mode ) )
    {
        printf ( "--- %s is no char device\n", handle->params.dev_name );
        goto err;
    }

    handle->fd = open ( handle->params.dev_name, O_RDWR | O_NONBLOCK, 0 );
    if ( handle->fd == -1 )
    {
        printf ( "--- Cannot open device %s: %d, %s\n", handle->params.dev_name,
                 errno, strerror ( errno ) );
        goto err;
    }

    printf ( "+++ Capture opened\n" );
    ret = init_device ( handle );
    if ( ret < 0 )
    {
        printf ( "--- initialize capture device  failed\n" );
        goto err;
    }

    printf ( "+++ Capture Opened\n" );
    return handle;

err: free ( handle );
    return NULL;
}

static void uninit_device ( struct cap_handle* handle )
{
    unsigned int i;
    for ( i = 0; i < handle->nbuffers; ++i )
        munmap ( handle->buffers[i].start, handle->buffers[i].length );

    free ( handle->buffers );
    handle->buffers = NULL;
    printf ( "+++ Device uninitialized\n" );
}

void capture_close ( struct cap_handle* handle )
{
    uninit_device ( handle );

    if ( handle->fd == -1 )
        return;

    close ( handle->fd );
    handle->fd = -1;

    free ( handle );
    handle = NULL;
    printf ( "+++ Capture Closed\n" );
}

int capture_start ( struct cap_handle* handle )
{
    unsigned int i;
    enum v4l2_buf_type btype;

    for ( i = 0; i < handle->nbuffers; ++i )
    {
        struct v4l2_buffer buf;
        CLEAR ( buf );
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;
        if ( xioctl ( handle->fd, VIDIOC_QBUF, &buf ) == -1 )
        {
            printf ( "--- Index: %d, VIDIOC_QBUF failed\n", i );
            return -1;
        }
    }

    btype = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if ( xioctl ( handle->fd, VIDIOC_STREAMON, &btype ) == -1 )
    {
        printf ( "--- VIDIOC_STREAMON failed\n" );
        return -1;
    }

    printf ( "+++ Capture Started\n" );
    return 0;
}

void capture_stop ( struct cap_handle* handle )
{
    enum v4l2_buf_type btype;
    btype = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    xioctl ( handle->fd, VIDIOC_STREAMOFF, &btype );
    printf ( "+++ Capture Stopped\n" );
}

int capture_get_data ( struct cap_handle* handle, void** buf, int* len )
{
    fd_set fds;
    struct timeval tv;
    int ret = 0;

    FD_ZERO ( &fds );
    FD_SET ( handle->fd, &fds );
    tv.tv_sec = 2;    // must be reset
    tv.tv_usec = 0;

    ret = select ( handle->fd + 1, &fds, NULL, NULL, &tv );
    if ( ret == -1 )
    {
        printf ( "--- select failed, %d, %s\n", errno, strerror ( errno ) );
        return -1;
    }

    if ( ret == 0 )  // select timeout
    {
        printf ( "--- select timeout!\n" );
        return -1;
    }

    // put the v4l buffer to the queue if it's not
    if ( !handle->v4lbuf_put )
    {
        if ( xioctl ( handle->fd, VIDIOC_QBUF, &handle->v4lbuf ) == -1 )
        {
            printf ( "--- VIDIOC_QBUF failed\n" );
            return -1;
        }

        handle->v4lbuf_put = 1;
    }

    // fill the buffer from queue
    CLEAR ( handle->v4lbuf );
    handle->v4lbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    handle->v4lbuf.memory = V4L2_MEMORY_MMAP;

    if ( xioctl ( handle->fd, VIDIOC_DQBUF, &handle->v4lbuf ) == -1 )
    {
        switch ( errno )
        {
            case EAGAIN:
                return EAGAIN;      // > 0
            case EIO:
            default:
                printf ( "--- VIDIOC_DQBUF failed\n" );
                return -1;
        }
    }

    assert ( ( handle->v4lbuf.index < handle->nbuffers ) );
    *buf = handle->buffers[handle->v4lbuf.index].start;
    *len = handle->image_size;

    handle->v4lbuf_put = 0;    // the v4l buffer needs to put to the queue
    handle->image_counter++;
    return 0;
}

int capture_query_brightness ( struct cap_handle* handle, int* min, int* max,
                               int* step )
{
    struct v4l2_queryctrl qctrl;
    qctrl.id = V4L2_CID_BRIGHTNESS;
    int ret = ioctl ( handle->fd, VIDIOC_QUERYCTRL, &qctrl );
    if ( ret < 0 )
        return ret;

    *min = qctrl.minimum;
    *max = qctrl.maximum;
    *step = qctrl.step;
    return 0;
}

int capture_get_brightness ( struct cap_handle* handle, int* val )
{
    struct v4l2_control ctrl;
    ctrl.id = V4L2_CID_BRIGHTNESS;
    int ret = ioctl ( handle->fd, VIDIOC_G_CTRL, &ctrl );
    if ( ret < 0 )
        return ret;

    *val = ctrl.value;
    return 0;
}

int capture_set_brightness ( struct cap_handle* handle, int val )
{
    struct v4l2_control ctrl;
    ctrl.id = V4L2_CID_BRIGHTNESS;
    ctrl.value = val;
    int ret = ioctl ( handle->fd, VIDIOC_S_CTRL, &ctrl );
    if ( ret < 0 )
        return ret;
    return 0;
}

int capture_query_contrast ( struct cap_handle* handle, int* min, int* max,
                             int* step )
{
    struct v4l2_queryctrl qctrl;
    qctrl.id = V4L2_CID_CONTRAST;
    int ret = ioctl ( handle->fd, VIDIOC_QUERYCTRL, &qctrl );
    if ( ret < 0 )
        return ret;

    *min = qctrl.minimum;
    *max = qctrl.maximum;
    *step = qctrl.step;
    return 0;
}

int capture_get_contrast ( struct cap_handle* handle, int* val )
{
    struct v4l2_control ctrl;
    ctrl.id = V4L2_CID_CONTRAST;
    int ret = ioctl ( handle->fd, VIDIOC_G_CTRL, &ctrl );
    if ( ret < 0 )
        return ret;

    *val = ctrl.value;
    return 0;
}

int capture_set_contrast ( struct cap_handle* handle, int val )
{
    struct v4l2_control ctrl;
    ctrl.id = V4L2_CID_CONTRAST;
    ctrl.value = val;
    int ret = ioctl ( handle->fd, VIDIOC_S_CTRL, &ctrl );
    if ( ret < 0 )
        return ret;
    return 0;
}

int capture_query_saturation ( struct cap_handle* handle, int* min, int* max,
                               int* step )
{
    struct v4l2_queryctrl qctrl;
    qctrl.id = V4L2_CID_SATURATION;
    int ret = ioctl ( handle->fd, VIDIOC_QUERYCTRL, &qctrl );
    if ( ret < 0 )
        return ret;

    *min = qctrl.minimum;
    *max = qctrl.maximum;
    *step = qctrl.step;
    return 0;
}

int capture_get_saturation ( struct cap_handle* handle, int* val )
{
    struct v4l2_control ctrl;
    ctrl.id = V4L2_CID_SATURATION;
    int ret = ioctl ( handle->fd, VIDIOC_G_CTRL, &ctrl );
    if ( ret < 0 )
        return ret;

    *val = ctrl.value;
    return 0;
}

int capture_set_saturation ( struct cap_handle* handle, int val )
{
    struct v4l2_control ctrl;
    ctrl.id = V4L2_CID_SATURATION;
    ctrl.value = val;
    int ret = ioctl ( handle->fd, VIDIOC_S_CTRL, &ctrl );
    if ( ret < 0 )
        return ret;
    return 0;
}
