#include "qqtlogicvideomanager.h"

QQtLogicVideoManager::QQtLogicVideoManager ( QObject* parent ) :
    QObject ( parent )
{
    memset ( &sinfo, 0, sizeof ( struct sensor_info ) );
    pre_bpp = 16;
    rate = 15;        /* default to 15fps  */
    addr = 0;
    phys = 0;

    pre_size.w = 720;
    pre_size.h = 480;

    fd = 0;

    memset ( & pre_memory, 0, sizeof ( struct camera_memory ) );
    memset ( & pre_buf, 0, sizeof ( struct camera_buffer ) );
    memset ( & pre_size, 0, sizeof ( struct frm_size ) );

    tlb_base_phys = 0;
    format = HAL_PIXEL_FORMAT_YCbCr_422_I;

    pp = 0;
    frame = 0;

    timer = new QTimer ( this );
    timer->setSingleShot ( false );
    connect ( timer, SIGNAL ( timeout() ), this, SLOT ( slotSendImageToClient() ) );
}

QQtLogicVideoManager::~QQtLogicVideoManager()
{
    delete ui;
}

void QQtLogicVideoManager::init_dmmu()
{
    dmmu_init();
    dmmu_get_page_table_base_phys ( &tlb_base_phys );
}

void QQtLogicVideoManager::deinit_dmmu()
{
    dmmu_deinit();
}

bool QQtLogicVideoManager::open ( const QString& devName )
{
    //待测试
    close();

    fd = ::open ( devName.toLocal8Bit().constData(), O_RDWR ); //av

    if ( fd < 0 )
    {
        qDebug() << "Open device fail\n";
    }

    ioctl ( fd, CIMIO_SELECT_SENSOR, sinfo.sensor_id );

    ioctl ( fd, CIMIO_GET_SENSORINFO, &sinfo );

    ioctl ( fd, CIMIO_SET_TLB_BASE, tlb_base_phys ); //?????????

    int i = 0;

    if ( pre_buf.common && pre_buf.common->data )
    {
        dmmu_unmap_user_memory ( & ( pre_buf.dmmu_info ) );
        free ( pre_buf.common->data );
    }

    pre_buf.fd = fd;
    pre_buf.nr = 5;
    pre_buf.size = pre_size.w * pre_size.h * 3;
    pre_buf.common = &pre_memory;
    pre_buf.common->size = pre_buf.size * pre_buf.nr;
    pre_buf.common->data = memalign ( 4096, pre_buf.size * pre_buf.nr );
    memset ( pre_buf.common->data, 0xa5, ( pre_buf.size * pre_buf.nr ) );

    if ( pre_buf.common->data == NULL )
    {
        ::close ( fd );
        printf ( "==<%s L%d: null pointer!\n", __func__, __LINE__ );
        return false;
    }

    pre_buf.paddr = 0;
    pre_buf.dmmu_info.vaddr = pre_buf.common->data;
    pre_buf.dmmu_info.size = pre_buf.common->size;

    for ( i = 0; i < ( int ) ( pre_buf.common->size ); i += 0x1000 )
    {
        ( ( uint8_t* ) ( pre_buf.common->data ) ) [i] = 0xff;
    }

    ( ( uint8_t* ) ( pre_buf.common->data ) ) [pre_buf.common->size - 1] = 0xff;
    dmmu_map_user_memory ( & ( pre_buf.dmmu_info ) );

    for ( i = 0; i < pre_buf.nr; ++i )
    {
        pre_buf.yuvMeta[i].index = i;
        pre_buf.yuvMeta[i].width = pre_size.w;
        pre_buf.yuvMeta[i].height = pre_size.h;
        pre_buf.yuvMeta[i].format = format;
        pre_buf.yuvMeta[i].count = pre_buf.nr;
#ifdef __LINUX64__
        pre_buf.yuvMeta[i].yAddr = ( int64_t ) pre_buf.common->data + ( pre_buf.size ) * i;
#else
        pre_buf.yuvMeta[i].yAddr = ( int32_t ) pre_buf.common->data + ( pre_buf.size ) * i;
#endif
        pre_buf.yuvMeta[i].yPhy = pre_buf.paddr + i * ( pre_buf.size );

        if ( pre_buf.yuvMeta[i].format == HAL_PIXEL_FORMAT_YCbCr_422_I )    //yuv422 packed
        {
            pre_buf.yuvMeta[i].uAddr = pre_buf.yuvMeta[i].yAddr;
            pre_buf.yuvMeta[i].vAddr = pre_buf.yuvMeta[i].uAddr;
            pre_buf.yuvMeta[i].uPhy = pre_buf.yuvMeta[i].yPhy;
            pre_buf.yuvMeta[i].vPhy = pre_buf.yuvMeta[i].uPhy;
            pre_buf.yuvMeta[i].yStride = pre_buf.yuvMeta[i].width << 1;
            pre_buf.yuvMeta[i].uStride = pre_buf.yuvMeta[i].yStride;
            pre_buf.yuvMeta[i].vStride = pre_buf.yuvMeta[i].yStride;
        }
        else if ( pre_buf.yuvMeta[i].format == HAL_PIXEL_FORMAT_JZ_YUV_420_P )      //yuv420 planar
        {
            pre_buf.yuvMeta[i].uAddr = pre_buf.yuvMeta[i].yAddr + pre_size.w * pre_size.h;
            pre_buf.yuvMeta[i].vAddr = pre_buf.yuvMeta[i].uAddr + pre_size.w * pre_size.h / 4;
            pre_buf.yuvMeta[i].uPhy = pre_buf.yuvMeta[i].yPhy + pre_size.w * pre_size.h;
            pre_buf.yuvMeta[i].vPhy = pre_buf.yuvMeta[i].uPhy + pre_size.w * pre_size.h / 4;
            pre_buf.yuvMeta[i].yStride = pre_buf.yuvMeta[i].width << 1;
            pre_buf.yuvMeta[i].uStride = pre_buf.yuvMeta[i].width / 2;
            pre_buf.yuvMeta[i].vStride = pre_buf.yuvMeta[i].width / 2;
        }
        else if ( pre_buf.yuvMeta[i].format == HAL_PIXEL_FORMAT_RAW_SENSOR )    //raw bayer
        {
            pre_buf.yuvMeta[i].uAddr = pre_buf.yuvMeta[i].yAddr + pre_size.w * pre_size.h;
            pre_buf.yuvMeta[i].vAddr = pre_buf.yuvMeta[i].uAddr;
            pre_buf.yuvMeta[i].uPhy = pre_buf.yuvMeta[i].yPhy;
            pre_buf.yuvMeta[i].vPhy = pre_buf.yuvMeta[i].uPhy;
            pre_buf.yuvMeta[i].yStride = pre_buf.yuvMeta[i].width;
            pre_buf.yuvMeta[i].uStride = pre_buf.yuvMeta[i].yStride;
            pre_buf.yuvMeta[i].vStride = pre_buf.yuvMeta[i].yStride;
        }
    }

    ioctl ( fd, CIMIO_SET_PREVIEW_FMT, format );
    ioctl ( fd, CIMIO_SET_PREVIEW_SIZE, &pre_size );

    ioctl ( fd, CIMIO_SET_PREVIEW_MEM, ( unsigned long ) ( pre_buf.yuvMeta ) );

    ioctl ( fd, CIMIO_START_PREVIEW );

    pp = ( unsigned char* ) malloc ( pre_size.w * pre_size.h * 3 * sizeof ( char ) );
    frame = new QImage ( pp, pre_size.w, pre_size.h, QImage::Format_RGB888 );
    timer->start ( 100 );

    return true;
}

bool QQtLogicVideoManager::close()
{
    timer->stop();

    if ( fd <= 0 )
        printf ( "fd < 0\n" );

    ret = ioctl ( fd, CIMIO_SHUTDOWN );

    ::close ( fd );
    fd = 0;

    memset ( pre_buf.yuvMeta, 0, pre_buf.nr * sizeof ( CameraYUVMeta ) );
    pre_buf.size = 0;
    pre_buf.nr = 0;
    pre_buf.paddr = 0;
    pre_buf.fd = -1;

    if ( ( pre_buf.common != NULL ) && ( pre_buf.common->data != NULL ) )
    {
        dmmu_unmap_user_memory ( & ( pre_buf.dmmu_info ) );
        free ( pre_buf.common->data );
        pre_buf.common->data = NULL;
    }

    phys = 0;

    if ( pp )
        free ( pp );
    if ( frame )
        delete frame;

    return true;
}


int QQtLogicVideoManager::convert_yuv_to_rgb_pixel ( int y, int u, int v )
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

int QQtLogicVideoManager::convert_yuv_to_rgb_buffer ( unsigned char* yuv, unsigned char* rgb, unsigned int width,
                                                      unsigned int height )
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

void QQtLogicVideoManager::slotSendImageToClient()
{
    if ( fd <= 0 )
        return;
    /*
     * 此处采集视频为多线程采集 上边的log证明 数据已经被修改
     */
    addr = ioctl ( fd, CIMIO_GET_FRAME );
    p = ( uchar* ) addr;

    /*
     * 不具备优化能力，yuv缺少alpha。
     */
    convert_yuv_to_rgb_buffer ( p, pp, pre_size.w, pre_size.h );

    //no need. frame已经初始化好了，用的pp的地址
    //frame->loadFromData((uchar *)pp, w * h * 3 * sizeof(char));

    emit readyRead ( *frame );
}
