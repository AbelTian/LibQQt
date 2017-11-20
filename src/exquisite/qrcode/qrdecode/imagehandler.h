#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include <QObject>
#include <QImage>
#include <QSharedPointer>
#include <QQuickItemGrabResult>
#include <QQuickItem>

class ImageHandler : public QObject
{
    Q_OBJECT
private:
    QSharedPointer<QQuickItemGrabResult> result;

public:
    explicit ImageHandler ( QObject* parent = 0 );

    void extractQImage ( QObject* imageObj,
                         const double offsetX = 0, const double offsetY = 0,
                         const double width = 0, const double height = 0 );

public slots:
    QImage makeScreen ( QQuickItem* videoOutput );
    void emitConversionResult();

signals:
    void conversionDone ( QImage result );

};

#endif // IMAGEHANDLER_H
