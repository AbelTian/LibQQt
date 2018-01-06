#ifndef QQTAPPLICATION_H
#define QQTAPPLICATION_H

#include <QApplication>
#include <qqt-local.h>

/**
 * @brief The QQtApplication class
 * 建议多使用./skin 而不是://skin Qt qrc命令 在linux下 需要qrc文件有变动才会编译 local图片文件变化不会引发编译
 */
class QQTSHARED_EXPORT QQtApplication : public QApplication
{
    Q_OBJECT
public:
public:
    explicit QQtApplication ( int& argc, char** argv );
    virtual ~QQtApplication();

    void setLanguage ( QString qmfile = "./lang/zh_CN.qm" );
    //palette
    void setTextFont ( QString fontfile = "/usr/lib/fonts/heiti.ttf",
                       int fontsize = 11 );
    void setQSSStyle ( QString qssfile = "./skin/default.qss" );
    void setUPanAutorun ( bool run = false );

    virtual int initInstance() { return 0; }
    virtual int unInitInstance() { return 0; }

signals:

public slots:
    void slotUPanAutoRun ( int status );
private:
    bool bUPanAutoRun;

private:
    QTranslator* language;
};

#endif // QQTAPPLICATION_H
