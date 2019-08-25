#include <qqtcamera.h>

QQtCameraExposure::QQtCameraExposure ( QObject* parent ) : QObject ( parent )
{
    mExposure = 0;
}

QQtCameraExposure::~QQtCameraExposure() {}

void QQtCameraExposure::setCameraExposure ( QCameraExposure* object )
{
    Q_ASSERT ( object );

    if ( mExposure )
    {
        disconnect ( mExposure, SIGNAL ( flashReady ( bool ) ), this, SIGNAL ( flashReady ( bool ) ) );
        disconnect ( mExposure, SIGNAL ( apertureChanged ( qreal ) ), this, SIGNAL ( apertureChanged ( qreal ) ) );
        disconnect ( mExposure, SIGNAL ( apertureRangeChanged() ), this, SIGNAL ( apertureRangeChanged() ) );
        disconnect ( mExposure, SIGNAL ( shutterSpeedChanged ( qreal ) ), this, SIGNAL ( shutterSpeedChanged ( qreal ) ) );
        disconnect ( mExposure, SIGNAL ( shutterSpeedRangeChanged() ), this, SIGNAL ( shutterSpeedRangeChanged() ) );
        disconnect ( mExposure, SIGNAL ( isoSensitivityChanged ( int ) ), this, SIGNAL ( isoSensitivityChanged ( int ) ) );
        disconnect ( mExposure, SIGNAL ( exposureCompensationChanged ( qreal ) ), this, SIGNAL ( exposureCompensationChanged ( qreal ) ) );

        mExposure->deleteLater();
    }

    mExposure = object;

    connect ( mExposure, SIGNAL ( flashReady ( bool ) ), this, SIGNAL ( flashReady ( bool ) ) );
    connect ( mExposure, SIGNAL ( apertureChanged ( qreal ) ), this, SIGNAL ( apertureChanged ( qreal ) ) );
    connect ( mExposure, SIGNAL ( apertureRangeChanged() ), this, SIGNAL ( apertureRangeChanged() ) );
    connect ( mExposure, SIGNAL ( shutterSpeedChanged ( qreal ) ), this, SIGNAL ( shutterSpeedChanged ( qreal ) ) );
    connect ( mExposure, SIGNAL ( shutterSpeedRangeChanged() ), this, SIGNAL ( shutterSpeedRangeChanged() ) );
    connect ( mExposure, SIGNAL ( isoSensitivityChanged ( int ) ), this, SIGNAL ( isoSensitivityChanged ( int ) ) );
    connect ( mExposure, SIGNAL ( exposureCompensationChanged ( qreal ) ), this, SIGNAL ( exposureCompensationChanged ( qreal ) ) );

}

QCameraExposure* QQtCameraExposure::exposure()
{
    return mExposure;
}

bool QQtCameraExposure::isAvailable() const
{
    return mExposure->isAvailable();
}

QCameraExposure::FlashModes QQtCameraExposure::flashMode() const
{
    return mExposure->flashMode();
}

bool QQtCameraExposure::isFlashModeSupported ( QCameraExposure::FlashModes mode ) const
{
    return mExposure->isFlashModeSupported ( mode );
}

bool QQtCameraExposure::isFlashReady() const
{
    return mExposure->isFlashReady();
}

QCameraExposure::ExposureMode QQtCameraExposure::exposureMode() const
{
    return mExposure->exposureMode();
}

bool QQtCameraExposure::isExposureModeSupported ( QCameraExposure::ExposureMode mode ) const
{
    return mExposure->isExposureModeSupported ( mode );
}

qreal QQtCameraExposure::exposureCompensation() const
{
    return mExposure->exposureCompensation();
}

QCameraExposure::MeteringMode QQtCameraExposure::meteringMode() const
{
    return mExposure->meteringMode();
}

bool QQtCameraExposure::isMeteringModeSupported ( QCameraExposure::MeteringMode mode ) const
{
    return mExposure->isMeteringModeSupported ( mode );
}

QPointF QQtCameraExposure::spotMeteringPoint() const
{
    return mExposure->spotMeteringPoint();
}

void QQtCameraExposure::setSpotMeteringPoint ( const QPointF& point )
{
    return mExposure->setSpotMeteringPoint ( point );
}

int QQtCameraExposure::isoSensitivity() const
{
    return mExposure->isoSensitivity();
}

qreal QQtCameraExposure::aperture() const
{
    return mExposure->aperture();
}

qreal QQtCameraExposure::shutterSpeed() const
{
    return mExposure->shutterSpeed();
}

int QQtCameraExposure::requestedIsoSensitivity() const
{
    return mExposure->requestedIsoSensitivity();
}

qreal QQtCameraExposure::requestedAperture() const
{
    return mExposure->requestedAperture();
}

qreal QQtCameraExposure::requestedShutterSpeed() const
{
    return mExposure->requestedShutterSpeed();
}

QList<int> QQtCameraExposure::supportedIsoSensitivities ( bool* continuous ) const
{
    return mExposure->supportedIsoSensitivities ( continuous );
}

QList<qreal> QQtCameraExposure::supportedApertures ( bool* continuous ) const
{
    return mExposure->supportedApertures ( continuous );
}

QList<qreal> QQtCameraExposure::supportedShutterSpeeds ( bool* continuous ) const
{
    return mExposure->supportedShutterSpeeds ( continuous );
}

void QQtCameraExposure::setFlashMode ( QCameraExposure::FlashModes mode )
{
    return mExposure->setFlashMode ( mode );
}

void QQtCameraExposure::setExposureMode ( QCameraExposure::ExposureMode mode )
{
    return mExposure->setExposureMode ( mode );
}

void QQtCameraExposure::setMeteringMode ( QCameraExposure::MeteringMode mode )
{
    return mExposure->setMeteringMode ( mode );
}

void QQtCameraExposure::setExposureCompensation ( qreal ev )
{
    return mExposure->setExposureCompensation ( ev );
}

void QQtCameraExposure::setManualIsoSensitivity ( int iso )
{
    return mExposure->setManualIsoSensitivity ( iso );
}

void QQtCameraExposure::setAutoIsoSensitivity()
{
    return mExposure->setAutoIsoSensitivity ( );
}

void QQtCameraExposure::setManualAperture ( qreal aperture )
{
    return mExposure->setManualAperture ( aperture );
}

void QQtCameraExposure::setAutoAperture()
{
    return mExposure->setAutoAperture ( );
}

void QQtCameraExposure::setManualShutterSpeed ( qreal seconds )
{
    return mExposure->setManualShutterSpeed ( seconds );
}

void QQtCameraExposure::setAutoShutterSpeed()
{
    return mExposure->setAutoShutterSpeed ( );
}


QQtCameraFocus::QQtCameraFocus ( QObject* parent ) : QObject ( parent )
{
    mFocus = 0;
}

QQtCameraFocus::~QQtCameraFocus() {}

void QQtCameraFocus::setCameraFocus ( QCameraFocus* object )
{
    Q_ASSERT ( object );

    if ( mFocus )
    {
        disconnect ( mFocus, SIGNAL ( opticalZoomChanged ( qreal ) ), this, SIGNAL ( opticalZoomChanged ( qreal ) ) );
        disconnect ( mFocus, SIGNAL ( digitalZoomChanged ( qreal ) ), this, SIGNAL ( digitalZoomChanged ( qreal ) ) );
        disconnect ( mFocus, SIGNAL ( focusZonesChanged (  ) ), this, SIGNAL ( focusZonesChanged (  ) ) );
        disconnect ( mFocus, SIGNAL ( maximumOpticalZoomChanged ( qreal ) ), this, SIGNAL ( maximumOpticalZoomChanged ( qreal ) ) );
        disconnect ( mFocus, SIGNAL ( maximumDigitalZoomChanged ( qreal ) ), this, SIGNAL ( maximumDigitalZoomChanged ( qreal ) ) );
        mFocus->deleteLater();
    }

    mFocus = object;

    connect ( mFocus, SIGNAL ( opticalZoomChanged ( qreal ) ), this, SIGNAL ( opticalZoomChanged ( qreal ) ) );
    connect ( mFocus, SIGNAL ( digitalZoomChanged ( qreal ) ), this, SIGNAL ( digitalZoomChanged ( qreal ) ) );
    connect ( mFocus, SIGNAL ( focusZonesChanged (  ) ), this, SIGNAL ( focusZonesChanged (  ) ) );
    connect ( mFocus, SIGNAL ( maximumOpticalZoomChanged ( qreal ) ), this, SIGNAL ( maximumOpticalZoomChanged ( qreal ) ) );
    connect ( mFocus, SIGNAL ( maximumDigitalZoomChanged ( qreal ) ), this, SIGNAL ( maximumDigitalZoomChanged ( qreal ) ) );

}

QCameraFocus* QQtCameraFocus::focus()
{
    return mFocus;
}

bool QQtCameraFocus::isAvailable() const
{
    return mFocus->isAvailable();
}

QCameraFocus::FocusModes QQtCameraFocus::focusMode() const
{
    return mFocus->focusMode();
}

void QQtCameraFocus::setFocusMode ( QCameraFocus::FocusModes mode )
{
    return mFocus->setFocusMode ( mode );
}

bool QQtCameraFocus::isFocusModeSupported ( QCameraFocus::FocusModes mode ) const
{
    return mFocus->isFocusModeSupported ( mode );
}

QCameraFocus::FocusPointMode QQtCameraFocus::focusPointMode() const
{
    return mFocus->focusPointMode (  );
}

void QQtCameraFocus::setFocusPointMode ( QCameraFocus::FocusPointMode mode )
{
    return mFocus->setFocusPointMode ( mode );
}

bool QQtCameraFocus::isFocusPointModeSupported ( QCameraFocus::FocusPointMode mode ) const
{
    return mFocus->isFocusPointModeSupported ( mode );
}

QPointF QQtCameraFocus::customFocusPoint() const
{
    return mFocus->customFocusPoint (  );
}

void QQtCameraFocus::setCustomFocusPoint ( const QPointF& point )
{
    return mFocus->setCustomFocusPoint ( point );
}

QCameraFocusZoneList QQtCameraFocus::focusZones() const
{
    return mFocus->focusZones (  );
}

qreal QQtCameraFocus::maximumOpticalZoom() const
{
    return mFocus->maximumOpticalZoom (  );
}

qreal QQtCameraFocus::maximumDigitalZoom() const
{
    return mFocus->maximumDigitalZoom (  );
}

qreal QQtCameraFocus::opticalZoom() const
{
    return mFocus->opticalZoom (  );
}

qreal QQtCameraFocus::digitalZoom() const
{
    return mFocus->digitalZoom (  );
}

void QQtCameraFocus::zoomTo ( qreal opticalZoom, qreal digitalZoom )
{
    return mFocus->zoomTo ( opticalZoom, digitalZoom );
}


QQtCameraImageProcessing::QQtCameraImageProcessing ( QObject* parent ) : QObject ( parent )
{
    mImageProcessing = 0;
}

QQtCameraImageProcessing::~QQtCameraImageProcessing() {}

void QQtCameraImageProcessing::setCameraImageProcessing ( QCameraImageProcessing* object )
{
    Q_ASSERT ( object );

    if ( mImageProcessing )
    {
        mImageProcessing->deleteLater();
    }

    mImageProcessing = object;
}

bool QQtCameraImageProcessing::isAvailable() const
{
    return mImageProcessing->isAvailable();
}

QCameraImageProcessing::WhiteBalanceMode QQtCameraImageProcessing::whiteBalanceMode() const
{
    return mImageProcessing->whiteBalanceMode();
}

void QQtCameraImageProcessing::setWhiteBalanceMode ( QCameraImageProcessing::WhiteBalanceMode mode )
{
    return mImageProcessing->setWhiteBalanceMode ( mode );
}

bool QQtCameraImageProcessing::isWhiteBalanceModeSupported ( QCameraImageProcessing::WhiteBalanceMode mode ) const
{
    return mImageProcessing->isWhiteBalanceModeSupported ( mode );
}

qreal QQtCameraImageProcessing::manualWhiteBalance() const
{
    return mImageProcessing->manualWhiteBalance();
}

void QQtCameraImageProcessing::setManualWhiteBalance ( qreal colorTemperature )
{
    return mImageProcessing->setManualWhiteBalance ( colorTemperature );
}

qreal QQtCameraImageProcessing::brightness() const
{
#if !defined ( __ARM_LINUX__ ) && !defined ( __MIPS__LINUX__ )
    return mImageProcessing->brightness();
#endif
}

void QQtCameraImageProcessing::setBrightness ( qreal value )
{
    return mImageProcessing->setManualWhiteBalance ( value );
}

qreal QQtCameraImageProcessing::contrast() const
{
    return mImageProcessing->contrast();
}

void QQtCameraImageProcessing::setContrast ( qreal value )
{
    return mImageProcessing->setContrast ( value );
}

qreal QQtCameraImageProcessing::saturation() const
{
    return mImageProcessing->saturation();
}

void QQtCameraImageProcessing::setSaturation ( qreal value )
{
    return mImageProcessing->setSaturation ( value );
}

qreal QQtCameraImageProcessing::sharpeningLevel() const
{
    return mImageProcessing->sharpeningLevel();
}

void QQtCameraImageProcessing::setSharpeningLevel ( qreal value )
{
    return mImageProcessing->setSharpeningLevel ( value );
}

qreal QQtCameraImageProcessing::denoisingLevel() const
{
    return mImageProcessing->denoisingLevel();
}

void QQtCameraImageProcessing::setDenoisingLevel ( qreal value )
{
    return mImageProcessing->setDenoisingLevel ( value );
}

QCameraImageProcessing::ColorFilter QQtCameraImageProcessing::colorFilter() const
{
    return mImageProcessing->colorFilter();
}

void QQtCameraImageProcessing::setColorFilter ( QCameraImageProcessing::ColorFilter filter )
{
    return mImageProcessing->setColorFilter ( filter );
}

bool QQtCameraImageProcessing::isColorFilterSupported ( QCameraImageProcessing::ColorFilter filter ) const
{
    return mImageProcessing->isColorFilterSupported ( filter );
}

QQtCamera::QQtCamera ( QObject* parent ) : QObject ( parent )
{
    //初始化Camera。
    mCamera = 0;
    //初始化CameraInfo。
    mCameraInfo = QCameraInfo::defaultCamera();

    //mCamera 句柄持续为真。
    setCameraInfo ( QCameraInfo::defaultCamera() );
}

QQtCamera::~QQtCamera() {}

void QQtCamera::setCameraInfo ( const QCameraInfo& camInfo )
{
    //更新mCamera
    if ( mCamera )
    {
        disconnect ( mCamera, SIGNAL ( stateChanged ( QCamera::State ) ), this, SIGNAL ( stateChanged ( QCamera::State ) ) );
        disconnect ( mCamera, SIGNAL ( captureModeChanged ( QCamera::CaptureModes ) ), this, SIGNAL ( captureModeChanged ( QCamera::CaptureModes ) ) );
        disconnect ( mCamera, SIGNAL ( statusChanged ( QCamera::Status ) ), this, SIGNAL ( statusChanged ( QCamera::Status ) ) );
        disconnect ( mCamera, SIGNAL ( locked() ), this, SIGNAL ( locked() ) );
        disconnect ( mCamera, SIGNAL ( lockFailed() ), this, SIGNAL ( lockFailed() ) );
        disconnect ( mCamera, SIGNAL ( lockStatusChanged ( QCamera::LockStatus, QCamera::LockChangeReason ) ), this, SIGNAL ( lockStatusChanged ( QCamera::LockStatus, QCamera::LockChangeReason ) ) );
        disconnect ( mCamera, SIGNAL ( lockStatusChanged ( QCamera::LockType, QCamera::LockStatus, QCamera::LockChangeReason ) ), this, SIGNAL ( lockStatusChanged ( QCamera::LockType, QCamera::LockStatus,
                     QCamera::LockChangeReason ) ) );
        disconnect ( mCamera, SIGNAL ( error ( QCamera::Error ) ), this, SIGNAL ( error ( QCamera::Error ) ) );
        mCamera->stop();
        mCamera->deleteLater();
    }

    mCameraInfo = camInfo;
    mCamera = new QCamera ( mCameraInfo, this );

#if 0
    //更新 Viewfinder
    setViewfinder ( m_vw_viewfinder );
    setViewfinder ( m_gv_viewfinder );
    setViewfinder ( m_avs_viewfinder );

    //更新 ViewfinderSettings
    setViewfinderSettings ( mVfSettings );
#endif

    //更新信号、槽的连接
    connect ( mCamera, SIGNAL ( stateChanged ( QCamera::State ) ), this, SIGNAL ( stateChanged ( QCamera::State ) ) );
    connect ( mCamera, SIGNAL ( captureModeChanged ( QCamera::CaptureModes ) ), this, SIGNAL ( captureModeChanged ( QCamera::CaptureModes ) ) );
    connect ( mCamera, SIGNAL ( statusChanged ( QCamera::Status ) ), this, SIGNAL ( statusChanged ( QCamera::Status ) ) );
    connect ( mCamera, SIGNAL ( locked() ), this, SIGNAL ( locked() ) );
    connect ( mCamera, SIGNAL ( lockFailed() ), this, SIGNAL ( lockFailed() ) );
    connect ( mCamera, SIGNAL ( lockStatusChanged ( QCamera::LockStatus, QCamera::LockChangeReason ) ), this, SIGNAL ( lockStatusChanged ( QCamera::LockStatus, QCamera::LockChangeReason ) ) );
    connect ( mCamera, SIGNAL ( lockStatusChanged ( QCamera::LockType, QCamera::LockStatus, QCamera::LockChangeReason ) ), this, SIGNAL ( lockStatusChanged ( QCamera::LockType, QCamera::LockStatus,
              QCamera::LockChangeReason ) ) );
    connect ( mCamera, SIGNAL ( error ( QCamera::Error ) ), this, SIGNAL ( error ( QCamera::Error ) ) );

}

QCameraInfo QQtCamera::cameraInfo() const
{
    return mCameraInfo;
}

QCamera* QQtCamera::camera() const
{
    return mCamera;
}

QMultimedia::AvailabilityStatus QQtCamera::availability() const
{
    return mCamera->availability();
}

QCamera::State QQtCamera::state() const
{
    return mCamera->state();
}

QCamera::Status QQtCamera::status() const
{
    return mCamera->status();
}

QCamera::CaptureModes QQtCamera::captureMode() const
{
    return mCamera->captureMode();
}

bool QQtCamera::isCaptureModeSupported ( QCamera::CaptureModes mode ) const
{
    return mCamera->isCaptureModeSupported ( mode );
}

QCameraExposure* QQtCamera::exposure() const
{
    return mCamera->exposure();
}

QCameraFocus* QQtCamera::focus() const
{
    return mCamera->focus();
}

QCameraImageProcessing* QQtCamera::imageProcessing() const
{
    return mCamera->imageProcessing();
}

void QQtCamera::setViewfinder ( QVideoWidget* viewfinder )
{
    mCamera->setViewfinder ( viewfinder );
}

void QQtCamera::setViewfinder ( QGraphicsVideoItem* viewfinder )
{
    mCamera->setViewfinder ( viewfinder );
}

void QQtCamera::setViewfinder ( QAbstractVideoSurface* surface )
{
    mCamera->setViewfinder ( surface );
}

QCameraViewfinderSettings QQtCamera::viewfinderSettings() const
{
    return mCamera->viewfinderSettings();
}

void QQtCamera::setViewfinderSettings ( const QCameraViewfinderSettings& settings )
{
    return mCamera->setViewfinderSettings ( settings );
}

QList<QCameraViewfinderSettings> QQtCamera::supportedViewfinderSettings ( const QCameraViewfinderSettings& settings ) const
{
    return mCamera->supportedViewfinderSettings ( settings );
}

QList<QSize> QQtCamera::supportedViewfinderResolutions ( const QCameraViewfinderSettings& settings ) const
{
    return mCamera->supportedViewfinderResolutions ( settings );
}

QList<QCamera::FrameRateRange> QQtCamera::supportedViewfinderFrameRateRanges ( const QCameraViewfinderSettings& settings ) const
{
    return mCamera->supportedViewfinderFrameRateRanges ( settings );
}

QList<QVideoFrame::PixelFormat> QQtCamera::supportedViewfinderPixelFormats ( const QCameraViewfinderSettings& settings ) const
{
    return mCamera->supportedViewfinderPixelFormats ( settings );
}

QCamera::Error QQtCamera::error() const
{
    return mCamera->error (  );
}

QString QQtCamera::errorString() const
{
    return mCamera->errorString (  );
}

QCamera::LockTypes QQtCamera::supportedLocks() const
{
    return mCamera->supportedLocks (  );
}

QCamera::LockTypes QQtCamera::requestedLocks() const
{
    return mCamera->requestedLocks (  );
}

QCamera::LockStatus QQtCamera::lockStatus() const
{
    return mCamera->lockStatus (  );
}

QCamera::LockStatus QQtCamera::lockStatus ( QCamera::LockType lock ) const
{
    return mCamera->lockStatus ( lock );
}

void QQtCamera::setCaptureMode ( QCamera::CaptureModes mode )
{
    return mCamera->setCaptureMode ( mode );
}

void QQtCamera::load()
{
    return mCamera->load();
}

void QQtCamera::unload()
{
    return mCamera->unload();
}

void QQtCamera::start()
{
    return mCamera->start();
}

void QQtCamera::stop()
{
    return mCamera->stop();
}

void QQtCamera::searchAndLock()
{
    return mCamera->searchAndLock();
}

void QQtCamera::unlock()
{
    return mCamera->unlock();
}

void QQtCamera::searchAndLock ( QCamera::LockTypes locks )
{
    return mCamera->searchAndLock ( locks );
}

void QQtCamera::unlock ( QCamera::LockTypes locks )
{
    return mCamera->unlock ( locks );
}
