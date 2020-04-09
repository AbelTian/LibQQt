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

    //更换语言，激发languageChanged()信号。
    void setLanguage ( QString qmfile = "./lang/zh_CN.qm" );

    //palette
    //更改全部窗口的字体，字体大小。
    bool setTextFont ( QString fontfile = "/usr/lib/fonts/heiti.ttf", int fontsize = 11 );

    //更改全部控件的QSS，基本的QSS，通用的QSS，全在这个里，特殊不变的也允许放在这里。
    void setQSSStyle ( QString qssfile = "./skin/default.qss" );

    //设置U盘自动运行，自动运行U盘autorun脚本。默认关闭，用户手动开启。
    void setUPanAutorun ( bool run = true );

    //写到log目录下每日日志文件。默认关闭，用户手动开启。
    void setWriteLogSystem ( bool open = true );

    //高DPI窗口控件缩放，自动适配不同的显示屏幕。默认关闭，用户手动开启。
    //需要在QQtApplication创建之前调用。
    //>=5.6.0，建议5.7.1以后开始使用。
    static void setHighDpiScaling ( bool open = true );

    //设置工作目录
    void setWorkRoot ( const QString& workroot );

    //获取工作目录 总是跟随用户设置改变 $(pwd)或者%CD%
    QString getWorkRoot();

    //QQtApplication把启动目录强制切换到了应用程序所在目录，如果用户需要更改回去，那么自己切换到这个目录即可。
    //获取启动时目录
    //这个值是固定不变的。
    const QString& getStartingWorkRoot() const;

    //这两个函数和MFC架构里的那两个函数一样的功能，但是Qt提供了main函数里的更好的窗口启动方法，所以，这里不实现。
    virtual int initInstance() { return 0; }
    virtual int unInitInstance() { return 0; }

    /**
     * 用户接收这个语言更改信号，更改所有窗口的语言。
     */
signals:
    void languageChanged();

    //这个是给PluginWatcher用的，和用户无关。允许重写
protected slots:
    virtual void slotUPanAutoRun ( int status );
private:
    bool bUPanAutoRun;

private:
    QTranslator* language;

private:
    QString startWorkRoot;
};

extern QQtApplication* qqtApp;

#endif // QQTAPPLICATION_H
