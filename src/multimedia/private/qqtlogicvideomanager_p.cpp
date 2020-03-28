#include <qqtlogicvideomanager_p.h>
#include <qqtlogicvideomanager.h>

int QQtLogicVideoManagerPrivate::sDmmuRefCount = 0;

QQtLogicVideoManagerPrivate::QQtLogicVideoManagerPrivate ( QQtLogicVideoManager* q, QObject* parent )
    : q_ptr ( q ), QObject ( parent )
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
    connect ( timer, SIGNAL ( timeout() ),
              this, SLOT ( slotSendImageToClient() ) );

    connect ( this, SIGNAL ( readyRead ( const QImage& ) ),
              q, SIGNAL ( readyRead ( const QImage& ) ) );

    if ( sDmmuRefCount <= 0 )
    {
        init_dmmu();
    }
    sDmmuRefCount++;
}

QQtLogicVideoManagerPrivate::~QQtLogicVideoManagerPrivate()
{
    sDmmuRefCount--;
    if ( sDmmuRefCount <= 0 )
    {
        deinit_dmmu();
    }
}

void QQtLogicVideoManagerPrivate::init_dmmu()
{
    dmmu_init();
    dmmu_get_page_table_base_phys ( &tlb_base_phys );
}

void QQtLogicVideoManagerPrivate::deinit_dmmu()
{
    dmmu_deinit();
}

bool QQtLogicVideoManagerPrivate::open ( QString devName )
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

bool QQtLogicVideoManagerPrivate::close()
{
    timer->stop();

    if ( fd <= 0 )
        printf ( "fd < 0\n" );

    int ret = ioctl ( fd, CIMIO_SHUTDOWN );

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

void QQtLogicVideoManagerPrivate::slotSendImageToClient()
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
    qqt_convert_yuyv_to_rgb888_buffer ( p, pp, pre_size.w, pre_size.h );

    //no need. frame已经初始化好了，用的pp的地址
    //frame->loadFromData((uchar *)pp, w * h * 3 * sizeof(char));

    emit readyRead ( *frame );
}
