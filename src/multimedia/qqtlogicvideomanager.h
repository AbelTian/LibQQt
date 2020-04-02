#ifndef QQTLOGICVIDEOMANAGER_H
#define QQTLOGICVIDEOMANAGER_H

#include <QObject>
#include <QImage>

#include "qqt-local.h"
/**
 * @brief The QQtLogicVideoInput class
 * 模拟摄像头管理器
 */
class QQtLogicVideoInputPrivate;
class QQTSHARED_EXPORT QQtLogicVideoInput : public QObject
{
    Q_OBJECT

public:
    explicit QQtLogicVideoInput ( QObject* parent = 0 );
    virtual ~QQtLogicVideoInput();

    //开启某个确定的模拟摄像头
    bool open ( QString devName = "/dev/cim" );
    bool close();

signals:
    //获取图像
    void readyRead ( const QImage& image );

protected:

private:
    Q_DECLARE_PRIVATE ( QQtLogicVideoInput )
    QQtLogicVideoInputPrivate* d_ptr;
};

/**
 * @brief The QQtLogicVideoManager class
 */
class QQTSHARED_EXPORT QQtLogicVideoManager : public QObject
{
    Q_OBJECT
public:
    explicit QQtLogicVideoManager ( QObject* parent = 0 );
    virtual ~QQtLogicVideoManager();


public:
    //开启某个确定的模拟摄像头
    bool openInput ( QString devName = "/dev/cim" );
    bool closeInput();

signals:
    //获取图像
    void readyRead ( const QImage& image );

private:
    QQtLogicVideoInput* mInputManager;
};

#endif // QQTLOGICVIDEOMANAGER_H
