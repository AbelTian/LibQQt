#ifndef QQTCAMERA_H
#define QQTCAMERA_H

/**
 * 包装类
 * 为QQtVideoManager提供包装类，促使句柄、信号、槽，外部在使用时，不变。
 * 用户感兴趣可以使用。
 */

#include <QCamera>
#include <QCameraInfo>

#include <qqt-local.h>

/**
 * @brief The QQtCameraExposure class
 * 为QCameraExposure提供能够保持的句柄。
 * 不应该管理句柄的删除。
 */
class QQTSHARED_EXPORT QQtCameraExposure : public QObject
{
    Q_OBJECT
public:
    QQtCameraExposure ( QObject* parent = 0 );
    virtual ~QQtCameraExposure();

    //决定exposure句柄
    void setCameraExposure ( QCameraExposure* object );
    QCameraExposure* exposure();

    bool isAvailable() const;

    QCameraExposure::FlashModes flashMode() const;
    bool isFlashModeSupported ( QCameraExposure::FlashModes mode ) const;
    bool isFlashReady() const;

    QCameraExposure::ExposureMode exposureMode() const;
    bool isExposureModeSupported ( QCameraExposure::ExposureMode mode ) const;

    qreal exposureCompensation() const;

    QCameraExposure::MeteringMode meteringMode() const;
    bool isMeteringModeSupported ( QCameraExposure::MeteringMode mode ) const;

    QPointF spotMeteringPoint() const;
    void setSpotMeteringPoint ( const QPointF& point );

    int isoSensitivity() const;
    qreal aperture() const;
    qreal shutterSpeed() const;

    int requestedIsoSensitivity() const;
    qreal requestedAperture() const;
    qreal requestedShutterSpeed() const;

    QList<int> supportedIsoSensitivities ( bool* continuous = Q_NULLPTR ) const;
    QList<qreal> supportedApertures ( bool* continuous = Q_NULLPTR ) const;
    QList<qreal> supportedShutterSpeeds ( bool* continuous = Q_NULLPTR ) const;

public slots:
    void setFlashMode ( QCameraExposure::FlashModes mode );
    void setExposureMode ( QCameraExposure::ExposureMode mode );
    void setMeteringMode ( QCameraExposure::MeteringMode mode );

    void setExposureCompensation ( qreal ev );

    void setManualIsoSensitivity ( int iso );
    void setAutoIsoSensitivity();

    void setManualAperture ( qreal aperture );
    void setAutoAperture();

    void setManualShutterSpeed ( qreal seconds );
    void setAutoShutterSpeed();

signals:
    void flashReady ( bool );

    void apertureChanged ( qreal );
    void apertureRangeChanged();
    void shutterSpeedChanged ( qreal );
    void shutterSpeedRangeChanged();
    void isoSensitivityChanged ( int );
    void exposureCompensationChanged ( qreal );

private:
    QCameraExposure* mExposure;
};

/**
 * @brief The QQtCameraFocus class
 * QCameraFocus的包装，保持句柄。
 */
class QQTSHARED_EXPORT QQtCameraFocus : public QObject
{
    Q_OBJECT
public:
    QQtCameraFocus ( QObject* parent = 0 );
    virtual ~QQtCameraFocus();

    void setCameraFocus ( QCameraFocus* object );
    QCameraFocus* focus();

    bool isAvailable() const;

    QCameraFocus::FocusModes focusMode() const;
    void setFocusMode ( QCameraFocus::FocusModes mode );
    bool isFocusModeSupported ( QCameraFocus::FocusModes mode ) const;

    QCameraFocus::FocusPointMode focusPointMode() const;
    void setFocusPointMode ( QCameraFocus::FocusPointMode mode );
    bool isFocusPointModeSupported ( QCameraFocus::FocusPointMode mode ) const;
    QPointF customFocusPoint() const;
    void setCustomFocusPoint ( const QPointF& point );

    QCameraFocusZoneList focusZones() const;

    qreal maximumOpticalZoom() const;
    qreal maximumDigitalZoom() const;
    qreal opticalZoom() const;
    qreal digitalZoom() const;

    void zoomTo ( qreal opticalZoom, qreal digitalZoom );

signals:
    void opticalZoomChanged ( qreal );
    void digitalZoomChanged ( qreal );

    void focusZonesChanged();

    void maximumOpticalZoomChanged ( qreal );
    void maximumDigitalZoomChanged ( qreal );

private:
    QCameraFocus* mFocus;
};

/**
 * @brief The QQtCameraImageProcessing class
 * QCameraImageProcessing的包装类，保持句柄。
 */
class QQTSHARED_EXPORT QQtCameraImageProcessing : public QObject
{
    Q_OBJECT
public:
    QQtCameraImageProcessing ( QObject* parent = 0 );
    virtual ~QQtCameraImageProcessing();

    void setCameraImageProcessing ( QCameraImageProcessing* object );

    bool isAvailable() const;

    QCameraImageProcessing::WhiteBalanceMode whiteBalanceMode() const;
    void setWhiteBalanceMode ( QCameraImageProcessing::WhiteBalanceMode mode );
    bool isWhiteBalanceModeSupported ( QCameraImageProcessing::WhiteBalanceMode mode ) const;

    qreal manualWhiteBalance() const;
    void setManualWhiteBalance ( qreal colorTemperature );

    qreal brightness() const;
    void setBrightness ( qreal value );

    qreal contrast() const;
    void setContrast ( qreal value );

    qreal saturation() const;
    void setSaturation ( qreal value );

    qreal sharpeningLevel() const;
    void setSharpeningLevel ( qreal value );

    qreal denoisingLevel() const;
    void setDenoisingLevel ( qreal value );

    QCameraImageProcessing::ColorFilter colorFilter() const;
    void setColorFilter ( QCameraImageProcessing::ColorFilter filter );
    bool isColorFilterSupported ( QCameraImageProcessing::ColorFilter filter ) const;

private:
    QCameraImageProcessing* mImageProcessing;
};

/**
 * @brief The QQtCamera class
 * 封装QCamera
 * 已预置defaultCamera，
 * 句柄保持不变。
 *      包装类的句柄不变，信号和槽就可以持续使用了。
 *      内部句柄在变化，但是从外部看，无所谓，外部使用的句柄、信号、槽都是稳定的。
 * 功能丰富、齐全。
 * 多线程不安全。
 */
class QQTSHARED_EXPORT QQtCamera : public QObject
{
    Q_OBJECT
public:
    QQtCamera ( QObject* parent = 0 );
    virtual ~QQtCamera();

    //QQt setCameraInfo 决定以下所有关系照相机的操作。
    //更改 CameraInfo，QQtCamera 会切换到新Camera的默认输出设置，用户需要重新设置 ViewfinderSettings 达到输出设置目的。
    //更改 CameraInfo，QQtCamera 会舍弃过去的Viewfinder，用户需要重新设置 Viewfinder。
    void setCameraInfo ( const QCameraInfo& camInfo );
    QCameraInfo cameraInfo() const;

    //optional
    //以下函数可选使用，句柄处于持续变动之中。
    QCamera* camera() const;

    QMultimedia::AvailabilityStatus availability() const;

    QCamera::State state() const;
    QCamera::Status status() const;

    QCamera::CaptureModes captureMode() const;
    bool isCaptureModeSupported ( QCamera::CaptureModes mode ) const;

    QCameraExposure* exposure() const;
    QCameraFocus* focus() const;
    QCameraImageProcessing* imageProcessing() const;

    void setViewfinder ( QVideoWidget* viewfinder );
    void setViewfinder ( QGraphicsVideoItem* viewfinder );
    void setViewfinder ( QAbstractVideoSurface* surface );

    QCameraViewfinderSettings viewfinderSettings() const;
    void setViewfinderSettings ( const QCameraViewfinderSettings& settings );

    QList<QCameraViewfinderSettings> supportedViewfinderSettings (
        const QCameraViewfinderSettings& settings = QCameraViewfinderSettings() ) const;

    QList<QSize> supportedViewfinderResolutions (
        const QCameraViewfinderSettings& settings = QCameraViewfinderSettings() ) const;

    QList<QCamera::FrameRateRange> supportedViewfinderFrameRateRanges (
        const QCameraViewfinderSettings& settings = QCameraViewfinderSettings() ) const;

    QList<QVideoFrame::PixelFormat> supportedViewfinderPixelFormats (
        const QCameraViewfinderSettings& settings = QCameraViewfinderSettings() ) const;

    QCamera::Error error() const;
    QString errorString() const;

    QCamera::LockTypes supportedLocks() const;
    QCamera::LockTypes requestedLocks() const;

    QCamera::LockStatus lockStatus() const;
    QCamera::LockStatus lockStatus ( QCamera::LockType lock ) const;

public slots:
    void setCaptureMode ( QCamera::CaptureModes mode );

    void load();
    void unload();

    void start();
    void stop();

    void searchAndLock();
    void unlock();

    void searchAndLock ( QCamera::LockTypes locks );
    void unlock ( QCamera::LockTypes locks );

signals:
    void stateChanged ( QCamera::State );
    void captureModeChanged ( QCamera::CaptureModes );
    void statusChanged ( QCamera::Status );

    void locked();
    void lockFailed();

    void lockStatusChanged ( QCamera::LockStatus, QCamera::LockChangeReason );
    void lockStatusChanged ( QCamera::LockType, QCamera::LockStatus, QCamera::LockChangeReason );

    void error ( QCamera::Error );

private:
    QCamera* mCamera;
    QCameraInfo mCameraInfo;
};

#endif // QQTCAMERA_H
