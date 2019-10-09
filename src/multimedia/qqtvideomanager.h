#ifndef QQTVIDEOMANAGER_H
#define QQTVIDEOMANAGER_H

#include <QCamera>
#include <QCameraInfo>
#include <QCameraImageCapture>
#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>
#include <QCameraViewfinderSettings>
#include <QTimer>
#include <QMutex>
#include <QMutexLocker>

#include <qqt-local.h>

#include <qqtwidget.h>

#include <qqtcamera.h>

/**
 * ---------------------------------------------------------------------------------------------------------------------
 * | 使用方式           | Parent                   | Property Class        | Childen           | 备注
 * ---------------------------------------------------------------------------------------------------------------------
 * | setViewfinder     | QAbstractVideoSurface    | QQtCameraVideoSurface |                   | 视频，快，Buffer
 * ---------------------------------------------------------------------------------------------------------------------
 * | setViewfinder     | QMediaBindableInterface  | QGraphicsVideoItem    |                   | QGraphicsItem 系统专用
 * |                   |                          | QVideoWidget          | QCameraViewfinder | 视频，快，属于输出位置上的
 * ---------------------------------------------------------------------------------------------------------------------
 * | setMetaObject     | QMediaBindableInterface  | QCameraImageCapture   |                   | 截图，慢，默认保存文件
 * |                   |                          | QMediaRecorder        | QAudioRecorder    | 录像，快，保存文件，音视频
 * ---------------------------------------------------------------------------------------------------------------------
 */

/**
 * 功能：
 * 对视频设备进行管理。
 * 输入：摄像头
 * 输出：绘图设备（窗口）
 */

/**
 * @brief The QQtVideoSurface class
 * 从metaObject获取视频数据，帧。
 * Buffer，快速。
 */
class QQTSHARED_EXPORT QQtCameraVideoSurface : public QAbstractVideoSurface
{
    Q_OBJECT
public:
    QQtCameraVideoSurface ( QObject* parent = 0 );
    virtual ~QQtCameraVideoSurface();

    //默认：true，false。
    //经过测试
    //Windows下，webcam：true, true；不设置第一个为true，会崩溃。
    //macOS下，iSight：true, false; 第一个设置true，和Photo Booth一样。
    void setHorizontalMirror ( bool horizontal = true );
    bool horizontalMirror();
    void setVerticalMirror ( bool vertical = false );
    bool verticalMirror();

    //default: false
    void setMirrorEnable ( bool enable = true );
    bool mirrorEnabled();

signals:
    void readyRead ( QImage );

    // QAbstractVideoSurface interface
public:
    virtual QList<QVideoFrame::PixelFormat> supportedPixelFormats (
        QAbstractVideoBuffer::HandleType handleType ) const override;
    virtual bool present ( const QVideoFrame& frame ) override;

private:
    bool mHorizontal;
    bool mVertical;
    bool mMirrorEnable;
};

/**
 * @brief The QQtVideoInput class
 * 图像输入
 * 从照相机输入，输出QImage序。
 * 从照相机输入，支持截图，输出QImage。
 */
class QQTSHARED_EXPORT QQtVideoInput : public QObject
{
    Q_OBJECT
public:
    QQtVideoInput ( QObject* parent = 0 );
    virtual ~QQtVideoInput();

    /**
     * 选择输入设备
     */
    static QCameraInfo defaultCamera();
    static QList<QCameraInfo> availableCameras ( QCamera::Position position = QCamera::UnspecifiedPosition );
    //决定使用哪个Camera
    //QQtVideoInput不会立即生效，只有在开启后才会生效。
    QCameraInfo& cameraInfo ( void );

    /**
     * 选择输入格式，启动后设置。
     */
    QCameraViewfinderSettings viewFinderSettings();
    //设置采集的图像的PixFormat，帧率等信息。
    void setViewfinderSettings ( const QCameraViewfinderSettings& settings = QCameraViewfinderSettings() );
    //获取照相机支持的设置。默认查询defaultCamera的。
    static QList<QCameraViewfinderSettings> supportedViewFinderSettings ( const QCameraInfo& camInfo = defaultCamera() );

    //在不同的平台上有一定的使用限制。
    void setViewMirror ( bool horizontal = true, bool vertical = false );
    void viewMirror ( bool& horizontal, bool& vertical );
    //default:false
    void setMirrorEnable ( bool enable = true );
    bool mirrorEnabled();

    /**
     * 控制输入设备
     */
    QQtCamera* camera() const;
    QQtCameraExposure* expose() const;
    QQtCameraFocus* focus() const;
    QQtCameraImageProcessing* imageProcessing() const;

public slots:
    void start();
    void stop();
    void load();
    void unload();

    void startDefaultCamera();

    //自动对焦，手动对焦切换。默认，自动，200ms
    void setAutoPrepare ( bool autosearch = true );
    void setPrepareInterval ( int milliSeconds );
    int prepareInterval() const;

public slots:
    //用这个函数手动对焦。
    void prepare ( QCamera::LockTypes locks = QCamera::LockFocus );
    //放弃对焦、对焦停止、对焦完成
    void cancelPrepare ( QCamera::LockTypes locks = QCamera::LockFocus );

    //截图
    void capture();

    /**
     * 输出图像
     */
signals:
    //输出QImage序
    void readyRead ( QImage );
    //输出QImage
    void readyReadCapture ( QImage );

    /**
     * 以下与用户无关
     */
private slots:
    void slotTimeout();
    void slotImageCaptured ( QImage );
private:
    //经过调试，QCamera句柄，一个进程只能存在一个。
    QQtCamera* mCamera;
    QCameraInfo mCamInfo;
    QQtCameraVideoSurface* mSurface;
    QQtCameraExposure* mExposure;
    QQtCameraFocus* mFocus;
    QQtCameraImageProcessing* mImageProcessing;

    //自动对焦
    bool mAutoSearchFlag;
    QTimer* mAutoSearchTimer;
    int mAutoSearchMilliSeconds;

    //需要加锁吗？如果用户把这个类 moveToThread，并且不使用信号和槽模式调用 capture，那么需要加锁。
    QMutex mMutexCaptureFlag;
    bool mCaptureFlag;
};

/**
 * @brief The QQtVideoOutput class
 * 视频输出
 * 把QImage输出到取景器。
 * QWidget、QQtWidget都能完成。QVideoWidget QCameraViewfinder QGraphicsVideoItem这些需要QCamera。
 * QCamera可以有多个吗？各自设置不同的？不可以。
 */
class QQTSHARED_EXPORT QQtVideoOutput : public QObject
{
    Q_OBJECT
public:
    QQtVideoOutput ( QObject* parent = 0 );
    virtual ~QQtVideoOutput();

    /**
     * 设置输出设备
     */
    QQtWidget*& viewFinder();

    /**
     * 控制输出设备
     */
public slots:
    //开启后才能使用。
    void start();
    //关闭后停止显示。
    void stop();
    //对窗口输出图像。
    void setPixmap ( QImage image );

private:
    QQtWidget* mWidget;
    //需要加锁吗？如果用户把这个类 moveToThread，并且不使用信号和槽模式调用 start stop，那么需要加锁。
    QMutex mMutexStartFlag;
    bool mStartFlag;
};

/**
 * @brief The QQtVideoManager class
 * 视频设备管理器
 * 输入：照相机
 * 输出：取景器。
 *
 * 功能：
 * 获取录像机的每一帧，输出给用户处理，
 * 提供输出设备的管理，辅助用户输出到确定的窗口。
 */
class QQTSHARED_EXPORT QQtVideoManager : public QObject
{
    Q_OBJECT
public:
    QQtVideoManager ( QObject* parent = 0 );
    virtual ~QQtVideoManager();

    /**
     * 选择输入、输出设备
     */
    static QCameraInfo defaultCamera();
    static QList<QCameraInfo> availableCameras ( QCamera::Position position = QCamera::UnspecifiedPosition );
    //输入设备信息
    QCameraInfo& cameraInfo ( void );
    //输出设备信息
    QQtWidget*& viewFinder ( void ) const;

    /**
     * 设置输入、输出设备格式
     */
    //输入设备设置
    QCameraViewfinderSettings viewFinderSettings() const;
    void setViewfinderSettings ( const QCameraViewfinderSettings& settings );
    QList<QCameraViewfinderSettings> supportedViewFinderSettings();
    //输入设备的格式，决定输出设备的格式。

    /**
     * 控制输入、输出设备
     */
    QQtCamera* camera() const;
    QQtCameraExposure* expose() const;
    QQtCameraFocus* focus() const;
    QQtCameraImageProcessing* imageProcessing() const;

    QQtVideoInput* inputManager();
    QQtVideoOutput* outputManager();

public slots:
    void startInput();
    void stopInput();

    void startOutput();
    void stopOutput();

    void startDefaultInput();
    //等于start()。输出没有默认设备。
    void startDefaultOutput();

    void capture();

    /**
     * 输出图像
     */
signals:
    //从输入设备获得图像。用户处理这些图像。
    void readyRead ( QImage );
    void readyReadCapture ( QImage );

public slots:
    //把图像输出到输出设备。
    void outputImage ( QImage );

private:
    QQtVideoInput* mInput;
    QQtVideoOutput* mOutput;
};

#endif // QQTVIDEOMANAGER_H
