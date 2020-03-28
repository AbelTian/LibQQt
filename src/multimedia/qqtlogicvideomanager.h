#ifndef QQTLOGICVIDEOMANAGER_H
#define QQTLOGICVIDEOMANAGER_H

#include <QObject>
#include <QImage>

#include "qqt-local.h"
/**
 * @brief The QQtLogicVideoManager class
 * 模拟摄像头管理器
 */
class QQtLogicVideoManagerPrivate;
class QQTSHARED_EXPORT QQtLogicVideoManager : public QObject
{
    Q_OBJECT

public:
    explicit QQtLogicVideoManager ( QObject* parent = 0 );
    virtual ~QQtLogicVideoManager();

    //开启某个确定的模拟摄像头
    bool open ( QString devName = "/dev/cim" );
    bool close();

signals:
    //获取图像
    void readyRead ( const QImage& image );

protected:

private:
    Q_DECLARE_PRIVATE ( QQtLogicVideoManager )
    QQtLogicVideoManagerPrivate* d_ptr;
};

#endif // QQTLOGICVIDEOMANAGER_H
