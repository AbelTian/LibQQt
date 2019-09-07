#ifndef QQTV4L2VIDEOMANAGER_H
#define QQTV4L2VIDEOMANAGER_H

//#include <qqt-local.h>
#define QQTSHARED_EXPORT

#include <QObject>

class QQTSHARED_EXPORT QQtV4L2VideoManager : public QObject
{
    Q_OBJECT
public:
    explicit QQtV4L2VideoManager ( QObject* parent = 0 );
    virtual ~QQtV4L2VideoManager();

    void setDeviceName ( const QString& devName = "/dev/video0" );

    void setPixmapSize ( const QSize& size );

    void setPixmapFormat ( quint32 format );

    void setVideoRate ( int rate );

signals:
    void readyRead ( const QImage& image );

private:
    QString mDevName;
    QSize mSize;
    quint32 mFormat;
    int mRate;
};

#endif // QQTV4L2VIDEOMANAGER_H
