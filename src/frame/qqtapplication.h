#ifndef QQTAPPLICATION_H
#define QQTAPPLICATION_H

#include <QApplication>
#include <qqt-local.h>

/**
 * @brief The QQtApplication class
 * 建议多使用./skin 而不是://skin Qt qrc命令 在linux下 需要qrc文件有变动才会编译 local图片文件变化不会引发编译
 * qqtframe里提供skin和res函数，去适配资源位置系统变动的情况。
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
    //这是设置全部控件的，基本的QSS，通用的QSS，全在这个里，特殊不变的也在这里。
    void setQSSStyle ( QString qssfile = "./skin/default.qss" );
    void setUPanAutorun ( bool run = false );
    void setWriteLogSystem ( bool open = true );

    /**
     * 这个是设置应用程序框架窗口风格的，
     * "windows", "motif", "cde", "plastique", "windowsxp", or "macintosh"
     */
    void setFrameworkStyle ( QString style = "macintosh" );

    //这两个函数和MFC架构里的那两个函数一样的功能，但是Qt提供了main函数里的更好的窗口方法，所以，这里无效。
    virtual int initInstance() { return 0; }
    virtual int unInitInstance() { return 0; }

    /**
     * 用户从这里接收语言更改信号，更改所有窗口的语言。
     */
signals:
    void languageChanged();

    //这个是给PluginWatcher用的，和用户无关。允许重写
public slots:
    virtual void slotUPanAutoRun ( int status );
private:
    bool bUPanAutoRun;

private:
    QTranslator* language;
};

extern QQtApplication* qqtApp;

#endif // QQTAPPLICATION_H
