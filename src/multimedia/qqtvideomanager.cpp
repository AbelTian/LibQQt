#include <qqtvideomanager.h>
#include <qqtcore.h>

#include <qqtimageconverter.h>

//#define LOCAL_DEBUG
#ifdef LOCAL_DEBUG
#define p3line() p2line()
#else
#define p3line() QNoDebug()
#endif

QQtCameraVideoSurface::QQtCameraVideoSurface ( QObject* parent ) : QAbstractVideoSurface ( parent )
{
    mHorizontal = true;
    mVertical = false;
    mMirrorEnable = false;
}

QQtCameraVideoSurface::~QQtCameraVideoSurface()
{

}

void QQtCameraVideoSurface::setHorizontalMirror ( bool horizontal )
{
    mHorizontal = horizontal;
}

bool QQtCameraVideoSurface::horizontalMirror()
{
    return mHorizontal;
}

void QQtCameraVideoSurface::setVerticalMirror ( bool vertical )
{
    mVertical = vertical;
}

bool QQtCameraVideoSurface::verticalMirror()
{
    return mVertical;
}

void QQtCameraVideoSurface::setMirrorEnable ( bool enable )
{
    mMirrorEnable = enable;
}

bool QQtCameraVideoSurface::mirrorEnabled()
{
    return mMirrorEnable;
}

QList<QVideoFrame::PixelFormat> QQtCameraVideoSurface::supportedPixelFormats ( QAbstractVideoBuffer::HandleType
                                                                               handleType ) const
{
    //桌面
    return QList<QVideoFrame::PixelFormat>()
           << QVideoFrame::Format_YUYV
           << QVideoFrame::Format_UYVY
           //RGB系列都支持
           << QVideoFrame::Format_RGB24
           << QVideoFrame::Format_RGB32;
}

bool QQtCameraVideoSurface::present ( const QVideoFrame& frame )
{
    static int num = 0;

    p3line() << num++ << frame.isValid() << frame.isReadable() << frame.isWritable();
    p3line() << num++ << frame.bytesPerLine() << frame.size() << frame.startTime() << frame.endTime() << frame.mapMode();

    if ( !frame.isValid() )
        return false;

    QVideoFrame cloneFrame ( frame );

    p3line() << num++ << cloneFrame.isValid() << cloneFrame.isReadable() << cloneFrame.isWritable();
    p3line() << num++ << cloneFrame.bytesPerLine() << cloneFrame.size()
             << cloneFrame.startTime() << cloneFrame.endTime()
             << cloneFrame.mapMode() << ( int ) cloneFrame.pixelFormat()
             << QVideoFrame::imageFormatFromPixelFormat ( cloneFrame.pixelFormat() );

    /**
     * frame 可读
     */
    if ( !cloneFrame.map ( QAbstractVideoBuffer::ReadOnly ) )
        return false;

    /**
     * 处理frame
     */

    //Android下的视频格式是怎么回事？需要转换吗？
    //需要专门的转换函数。但凡QImage里面不支持的，都需要从pixelFormat手动转换过来。
    QImage _image;
    switch ( cloneFrame.pixelFormat() )
    {
        case QVideoFrame::Format_UYVY:
        {
            static QQtImageConverter icv;
            _image = icv.UYVYTORGB888 ( cloneFrame );
        }
        break;
        case QVideoFrame::Format_YUYV:
        {
            static QQtImageConverter icv;
            _image = icv.YUYVTORGB888 ( cloneFrame );
        }
        break;
        default:
        {
            _image = QImage ( cloneFrame.bits(),
                              cloneFrame.width(),
                              cloneFrame.height(),
                              QVideoFrame::imageFormatFromPixelFormat ( cloneFrame.pixelFormat() ) );
        }
        break;
    }

    /**
     * frame 不可读
     */
    cloneFrame.unmap();

    p3line() << num++ << _image.size() << _image.bytesPerLine() << _image.format();

    QImage image;
#if 1
    //需要对水平方向反转。
    //Windows，现在的图像保存能成功，直接显示，程序会异常退出。使用QImage的mirrored函数进行了水平翻转，可以正常显示。
    //水平翻转是为了不崩溃，正常显示图像。必选。
    //垂直翻转是为了上下显示正常。
    //这个的反转原因还需要调查一下，到底跟着谁反转。苹果下怎么设置都可以。
    switch ( cloneFrame.pixelFormat() )
    {
        case QVideoFrame::Format_YUYV:
        case QVideoFrame::Format_UYVY:
            image = _image.mirrored ( true, false );
            break;
        default:
            image = _image.mirrored ( true, true );
            break;
    }
#endif
    if ( mMirrorEnable )
        image = _image.mirrored ( mHorizontal, mVertical );

    p3line() << num++ << image.size() << image.bytesPerLine() << image.format();

    emit readyRead ( image );
    return true;
}

QQtVideoInput::QQtVideoInput ( QObject* parent ) : QObject ( parent )
{
    /**
     * 设置视频截图工具
     */
    mSurface  = new QQtCameraVideoSurface ( this );
    connect ( mSurface, SIGNAL ( readyRead ( QImage ) ), this, SIGNAL ( readyRead ( QImage ) ) );
    connect ( mSurface, SIGNAL ( readyRead ( QImage ) ), this, SLOT ( slotImageCaptured ( QImage ) ) );

    /**
     * 设置照相机
     */
    mCamera = new QQtCamera ( this );

    //QQtCamera 默认就是使用默认照相机，所以，这里不必设置了。
    mCamInfo = defaultCamera();
    mCamera->setCameraInfo ( mCamInfo );
    mCamera->setViewfinder ( mSurface );

    //
    mExposure = new QQtCameraExposure ( this );
    mFocus = new QQtCameraFocus ( this );
    mImageProcessing = new QQtCameraImageProcessing ( this );
    mExposure->setCameraExposure ( mCamera->exposure() );
    mFocus->setCameraFocus ( mCamera->focus() );
    mImageProcessing->setCameraImageProcessing ( mCamera->imageProcessing() );

    mAutoSearchMilliSeconds = 200;
    mAutoSearchTimer = new QTimer ( this );
    connect ( mAutoSearchTimer, SIGNAL ( timeout() ), this, SLOT ( slotTimeout() ) );
    mAutoSearchTimer->setInterval ( mAutoSearchMilliSeconds );
    mAutoSearchTimer->setSingleShot ( false );

    //默认开启自动对焦
    mAutoSearchFlag = true ;
    //默认不截图
    mCaptureFlag = false;
}

QQtVideoInput::~QQtVideoInput()
{

}

QCameraInfo QQtVideoInput::defaultCamera()
{
    return QCameraInfo::defaultCamera();
}

QList<QCameraInfo> QQtVideoInput::availableCameras ( QCamera::Position position )
{
    return QCameraInfo::availableCameras ( position );
}

QCameraInfo& QQtVideoInput::cameraInfo()
{
    return mCamInfo;
}

QCameraViewfinderSettings QQtVideoInput::viewFinderSettings()
{
    if ( !mCamera )
        return QCameraViewfinderSettings();
    return mCamera->viewfinderSettings();
}

void QQtVideoInput::setViewfinderSettings ( const QCameraViewfinderSettings& settings )
{
    if ( !mCamera )
        return;
    mCamera->setViewfinderSettings ( settings );
}

QList<QCameraViewfinderSettings> QQtVideoInput::supportedViewFinderSettings ( const QCameraInfo& camInfo )
{
    QCamera camera ( camInfo );
    return camera.supportedViewfinderSettings();
}

void QQtVideoInput::setViewMirror ( bool horizontal, bool vertical )
{
    mSurface->setHorizontalMirror ( horizontal );
    mSurface->setVerticalMirror ( vertical );
}

void QQtVideoInput::viewMirror ( bool& horizontal, bool& vertical )
{
    horizontal = mSurface->horizontalMirror();
    vertical = mSurface->verticalMirror();
}

void QQtVideoInput::setMirrorEnable ( bool enable )
{
    mSurface->setMirrorEnable ( enable );
}

bool QQtVideoInput::mirrorEnabled()
{
    return mSurface->mirrorEnabled();
}

QQtCamera* QQtVideoInput::camera() const
{
    return mCamera;
}

QQtCameraExposure* QQtVideoInput::expose() const
{
    return mExposure;
}

QQtCameraFocus* QQtVideoInput::focus() const
{
    return mFocus;
}

QQtCameraImageProcessing* QQtVideoInput::imageProcessing() const
{
    return mImageProcessing;
}

void QQtVideoInput::start()
{
    stop();

    //初始化截图Flag
    mCaptureFlag = false;

    //初始化照相机句柄
    mCamera->setCameraInfo ( mCamInfo );

    //初始化照相机图像控制句柄
    mExposure->setCameraExposure ( mCamera->exposure() );
    mFocus->setCameraFocus ( mCamera->focus() );
    mImageProcessing->setCameraImageProcessing ( mCamera->imageProcessing() );

    /**
     * 设置相机
     * 程序内部持续使用Capture Video。
     */
    //Windows 打印不支持，但是其实支持。
    if ( !mCamera->isCaptureModeSupported ( QCamera::CaptureVideo ) )
    {
        p3line() << mCamInfo.deviceName();
        //p3line() << mCamera << "Camera cannot capture video";
    }
    //播放图像 = QCamera::CaptureStillImage
    //播放图像 = QCamera::CaptureViewfinder
    mCamera->setCaptureMode ( QCamera::CaptureVideo );

    //设置输出
    mCamera->setViewfinder ( mSurface );

    //设置ViewfinderSettings
    //启动后设置...

    //启动
    mCamera->start();
    p3line() << mCamInfo.deviceName();
    p3line() << mCamera << "Camera start to capture video";

    //设置自动对焦
    if ( mAutoSearchFlag )
        mAutoSearchTimer->start();
}

void QQtVideoInput::stop()
{
    mAutoSearchTimer->stop();

    if ( mCamera )
    {
        mCamera->stop();
        //mCamera->deleteLater();
    }

    //mCamera = NULL;
}

void QQtVideoInput::load()
{
    mCamera->load();
}

void QQtVideoInput::unload()
{
    mCamera->unload();
}

void QQtVideoInput::startDefaultCamera()
{
    mCamInfo = defaultCamera();
    start();
}

void QQtVideoInput::setPrepareInterval ( int milliSeconds )
{
    mAutoSearchMilliSeconds = milliSeconds;
}

int QQtVideoInput::prepareInterval() const
{
    return mAutoSearchMilliSeconds;
}

void QQtVideoInput::capture()
{
    //现在使用截图Flag，将来可能要使用ImageCapture类，可以调整Shutter速度。
    //对外提供一个简化的截图功能。
    QMutexLocker locker ( &mMutexCaptureFlag );
    mCaptureFlag = true;
}

void QQtVideoInput::setAutoPrepare ( bool autosearch )
{
    mAutoSearchFlag = autosearch;

    if ( autosearch )
        mAutoSearchTimer->start();
    else
        mAutoSearchTimer->stop();
}

void QQtVideoInput::prepare ( QCamera::LockTypes locks )
{
    if ( !mCamera )
        return;
    mCamera->searchAndLock ( locks );
}

void QQtVideoInput::cancelPrepare ( QCamera::LockTypes locks )
{
    if ( !mCamera )
        return;
    mCamera->unlock();
}

void QQtVideoInput::slotTimeout()
{
    if ( !mCamera )
        return;
    mCamera->searchAndLock();
}

void QQtVideoInput::slotImageCaptured ( QImage image )
{
    QMutexLocker locker ( &mMutexCaptureFlag );

    if ( !mCaptureFlag )
        return;
    mCaptureFlag = false;

    emit readyReadCapture ( image );
}

QQtVideoOutput::QQtVideoOutput ( QObject* parent ) : QObject ( parent )
{
    mWidget = 0;
    mStartFlag = false;
}

QQtVideoOutput::~QQtVideoOutput() {}

QQtWidget*& QQtVideoOutput::viewFinder()
{
    return mWidget;
}

void QQtVideoOutput::start()
{
    QMutexLocker locker ( &mMutexStartFlag );
    mStartFlag = true;
}

void QQtVideoOutput::stop()
{
    QMutexLocker locker ( &mMutexStartFlag );
    mStartFlag = false;
}

void QQtVideoOutput::setPixmap ( QImage image )
{
    QMutexLocker locker ( &mMutexStartFlag );
    if ( !mStartFlag )
        return;
    if ( !mWidget )
        return;
    mWidget->setPixmap ( image );
}

QQtVideoManager::QQtVideoManager ( QObject* parent ) : QObject ( parent )
{
    mInput = new QQtVideoInput ( this );
    mOutput = new QQtVideoOutput ( this );

    connect ( mInput, SIGNAL ( readyRead ( QImage ) ), this, SIGNAL ( readyRead ( QImage ) ) );
    connect ( mInput, SIGNAL ( readyReadCapture ( QImage ) ), this, SIGNAL ( readyReadCapture ( QImage ) ) );
}

QQtVideoManager::~QQtVideoManager() {}

QCameraInfo QQtVideoManager::defaultCamera()
{
    return QQtVideoInput::defaultCamera();
}

QList<QCameraInfo> QQtVideoManager::availableCameras ( QCamera::Position position )
{
    return QQtVideoInput::availableCameras ( position );
}

QCameraInfo& QQtVideoManager::cameraInfo()
{
    return mInput->cameraInfo();
}

QQtWidget*& QQtVideoManager::viewFinder() const
{
    return mOutput->viewFinder();
}

QCameraViewfinderSettings QQtVideoManager::viewFinderSettings() const
{
    return mInput->viewFinderSettings();
}

void QQtVideoManager::setViewfinderSettings ( const QCameraViewfinderSettings& settings )
{
    return mInput->setViewfinderSettings ( settings );
}

QList<QCameraViewfinderSettings> QQtVideoManager::supportedViewFinderSettings()
{
    return mInput->supportedViewFinderSettings();
}

QQtCamera* QQtVideoManager::camera() const
{
    return mInput->camera();
}

QQtCameraExposure* QQtVideoManager::expose() const
{
    return mInput->expose();
}

QQtCameraFocus* QQtVideoManager::focus() const
{
    return mInput->focus();
}

QQtCameraImageProcessing* QQtVideoManager::imageProcessing() const
{
    return mInput->imageProcessing();
}

void QQtVideoManager::startInput()
{
    mInput->start();
}

void QQtVideoManager::stopInput()
{
    mInput->stop();
}

QQtVideoInput* QQtVideoManager::inputManager()
{
    return mInput;
}

void QQtVideoManager::startOutput()
{
    mOutput->start();
}

void QQtVideoManager::stopOutput()
{
    mOutput->stop();
}

QQtVideoOutput* QQtVideoManager::outputManager()
{
    return mOutput;
}

void QQtVideoManager::startDefaultInput()
{
    mInput->startDefaultCamera();
}

void QQtVideoManager::startDefaultOutput()
{
    mOutput->start();
}

void QQtVideoManager::capture()
{
    mInput->capture();
}

void QQtVideoManager::outputImage ( QImage image )
{
    mOutput->setPixmap ( image );
}
