#ifndef QQTV4L2VIDEOMANAGER_H
#define QQTV4L2VIDEOMANAGER_H

//#include <qqt-local.h>
#define QQTSHARED_EXPORT

#include <QObject>
#include <QTimer>
#include <QSize>
#include <libv4l2capture.h>
#include <QImage>


/**
 * @brief The QQtV4L2VideoManager class
 * 单个视频设备采集器
 */
class QQTSHARED_EXPORT QQtV4L2VideoManager : public QObject
{
    Q_OBJECT
public:
    explicit QQtV4L2VideoManager ( QObject* parent = 0 );
    virtual ~QQtV4L2VideoManager();

    //基础设置
    void setDeviceName ( const QString& devName = "/dev/video0" );
    void setPixmapSize ( const QSize& size );
    void setPixmapFormat ( quint32 format );
    void setVideoRate ( int rate );

    void  check_support_fmt ( void );

public slots:
    void startCapture();
    void stopCapture();

signals:
    void readyRead ( const QImage& image );

protected:
    int convert_yuv_to_rgb_pixel ( int y, int u, int v );
    int convert_yuv_to_rgb_buffer ( unsigned char* yuv, unsigned char* rgb, unsigned int width,
                                    unsigned int height );

private slots:
    void slotGetCapture();

private:
    QString mDevName;
    QSize mSize;
    quint32 mFormat;
    int mRate;

    QTimer* timer;
    struct cap_handle* handler;

    uchar* pp;
    uchar* p;
    QImage* frame;
};

#endif // QQTV4L2VIDEOMANAGER_H
