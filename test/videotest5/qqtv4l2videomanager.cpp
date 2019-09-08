#include <qqtv4l2videomanager.h>

#include <libv4l2capture.h>

#include <linux/videodev2.h>

QQtV4L2VideoManager::QQtV4L2VideoManager ( QObject* parent ) : QObject ( parent )
{
    handler = 0;
    pp = 0;
    frame = 0;

    mDevName = "/dev/video0";
    mSize = QSize ( 720, 480 );
    mFormat = V4L2_PIX_FMT_YUYV;//V4L2_PIX_FMT_NV21; //NV21? YUV? RGB?
    mRate = 10;

    timer = new QTimer ( this );
    timer->setSingleShot ( false );
    timer->setInterval ( 100 );
    connect ( timer, SIGNAL ( timeout() ), this, SLOT ( slotGetCapture() ) );
}

QQtV4L2VideoManager::~QQtV4L2VideoManager() {}

void QQtV4L2VideoManager::setDeviceName ( const QString& devName )
{
    mDevName = devName;
}

void QQtV4L2VideoManager::setPixmapSize ( const QSize& size )
{
    mSize = size;
}

void QQtV4L2VideoManager::setPixmapFormat ( quint32 format )
{
    mFormat = format;
}

void QQtV4L2VideoManager::setVideoRate ( int rate )
{
    mRate = rate;
}


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

#ifdef ANDROID
#include <android/log.h>
#define logstr(str)  __android_log_write(ANDROID_LOG_DEBUG, "QDebug", str);
#else
#define logstr(str)
#endif


void QQtV4L2VideoManager::check_support_fmt()
{
    //VIDIOC_ENUM_FMT // 查询,显⽰所有⽀持的格式
    printf ( "Checking Device Supported Format......\n" );
    struct v4l2_fmtdesc fmtdesc;
    fmtdesc.index = 0;
    fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    printf ( "Supported Formats:\n" );
    while ( ioctl ( handler->fd, VIDIOC_ENUM_FMT, &fmtdesc ) != -1 )
    {
        QString str = QString ( "%1 %2" ).arg ( fmtdesc.index + 1 ).arg ( ( char* ) fmtdesc.description );
        logstr ( str.toLocal8Bit().data() );
        printf ( "\t%d.%s\n", fmtdesc.index + 1, fmtdesc.description );
        fmtdesc.index++;
    }
    //检查是否支持格式V4L2_PIX_FMT_MJPEG
    struct v4l2_format fmt;
    memset ( &fmt, 0, sizeof ( fmt ) );
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
    if ( ioctl ( handler->fd, VIDIOC_TRY_FMT, &fmt ) == -1 && errno == EINVAL )
    {
        printf ( "not support format V4L2_PIX_FMT_MJPEG!\n" );
    }
    else
    {
        printf ( "Do support format V4L2_PIX_FMT_MJPEG!\n" );
    }

}


void QQtV4L2VideoManager::startCapture()
{
    if ( handler )
        capture_close ( handler );


    struct cap_param param;
    param.dev_name = mDevName.toLocal8Bit().data();
    param.width = mSize.width();
    param.height = mSize.height();
    param.rate = mRate;
    param.pixfmt = mFormat;
    handler = capture_open ( param );
    check_support_fmt();

    pp = ( unsigned char* ) malloc ( param.width * param.height * 3 * sizeof ( char ) );
    frame = new QImage ( pp, param.width, param.height, QImage::Format_RGB888 );
    timer->start();
}

void QQtV4L2VideoManager::stopCapture()
{
    timer->stop();

    if ( handler )
        capture_close ( handler );
    if ( pp )
        free ( pp );
    if ( frame )
        delete frame;
}

int QQtV4L2VideoManager::convert_yuv_to_rgb_pixel ( int y, int u, int v )
{
    unsigned int pixel32 = 0;
    unsigned char* pixel = ( unsigned char* ) &pixel32;
    int r, g, b;
    b = y + ( ( 443 * ( u - 128 ) ) >> 8 );
    b = ( b < 0 ) ? 0 : ( ( b > 255 ) ? 255 : b );
    g = y - ( ( 179 * ( v - 128 ) + 86 * ( u - 128 ) ) >> 8 );
    g = ( g < 0 ) ? 0 : ( ( g > 255 ) ? 255 : g );
    r = y + ( ( 351 * ( v - 128 ) ) >> 8 );
    r = ( r < 0 ) ? 0 : ( ( r > 255 ) ? 255 : r );
    pixel[0] = r;
    pixel[1] = g;
    pixel[2] = b;
    return pixel32;
}

int QQtV4L2VideoManager::convert_yuv_to_rgb_buffer ( unsigned char* yuv, unsigned char* rgb, unsigned int width, unsigned int height )
{
    unsigned int in, out = 0;
    unsigned int pixel_16;
    unsigned char pixel_24[3];
    unsigned int pixel32;
    int y0, u, y1, v;

    for ( in = 0; in < width * height * 2; in += 4 )
    {
        pixel_16 =
            yuv[in + 3] << 24 |
            yuv[in + 2] << 16 |
            yuv[in + 1] <<  8 |
            yuv[in + 0];
        y0 = ( pixel_16 & 0x000000ff );
        u  = ( pixel_16 & 0x0000ff00 ) >>  8;
        y1 = ( pixel_16 & 0x00ff0000 ) >> 16;
        v  = ( pixel_16 & 0xff000000 ) >> 24;
        pixel32 = convert_yuv_to_rgb_pixel ( y0, u, v );
        pixel_24[0] = ( pixel32 & 0x000000ff );
        pixel_24[1] = ( pixel32 & 0x0000ff00 ) >> 8;
        pixel_24[2] = ( pixel32 & 0x00ff0000 ) >> 16;
        rgb[out++] = pixel_24[0];
        rgb[out++] = pixel_24[1];
        rgb[out++] = pixel_24[2];
        pixel32 = convert_yuv_to_rgb_pixel ( y1, u, v );
        pixel_24[0] = ( pixel32 & 0x000000ff );
        pixel_24[1] = ( pixel32 & 0x0000ff00 ) >> 8;
        pixel_24[2] = ( pixel32 & 0x00ff0000 ) >> 16;
        rgb[out++] = pixel_24[0];
        rgb[out++] = pixel_24[1];
        rgb[out++] = pixel_24[2];
    }

    return 0;
}

void QQtV4L2VideoManager::slotGetCapture()
{
    int len = 0;
    capture_get_data ( handler, ( void** ) &p, &len );
    convert_yuv_to_rgb_buffer ( p, pp, mSize.width(), mSize.height() );
    emit readyRead ( *frame );
}
