#include <qqtv4l2videomanager.h>


QQtV4L2VideoManager::QQtV4L2VideoManager ( QObject* parent ) : QObject ( parent )
{
    handler = 0;

    mDevName = "/dev/video0";
    mSize = QSize ( 720, 480 );
    mFormat = 0; //NV21? YUV? RGB?
    mRate = 30;

    timer = new QTimer(this);
    timer->setSingleShot(false);
    timer->setInterval(200);
    connect(timer, SIGNAL(timeout()), this, SLOT(slotGetCapture()));
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

void QQtV4L2VideoManager::startCapture()
{
    if(handler)
        capture_close(handler);
    struct cap_param param;
    param.dev_name = mDevName.toLocal8Bit().data();
    param.width = mSize.width();
    param.height = mSize.height();
    param.rate = mRate;
    handler = capture_open(param);

    pp = ( unsigned char* ) malloc ( param.width * param.height * 3 * sizeof ( char ) );
    frame = new QImage ( pp, param.width, param.height, QImage::Format_RGB888 );
    timer->start();
}

void QQtV4L2VideoManager::stopCapture()
{
    if(handler)
        capture_close(handler);
}

int QQtV4L2VideoManager::convert_yuv_to_rgb_pixel(int y, int u, int v)
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

int QQtV4L2VideoManager::convert_yuv_to_rgb_buffer(unsigned char *yuv, unsigned char *rgb, unsigned int width, unsigned int height)
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
    capture_get_data(handler, (void**)&p, &len);
    convert_yuv_to_rgb_buffer(p, pp, mSize.width(), mSize.height());
    emit readyRead ( *frame );
}
