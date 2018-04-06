#include "qqtapplication.h"
#ifdef __PLUGINSUPPORT__
#include "qqtpluginwatcher.h"
#endif
#include <qqtmsgbox.h>
#include <qqtcore.h>
#include <qqtframe.h>
#include <qqtversion.h>
#include <QFile>
#include <QTextCodec>
#include <QSettings>
#include <QTranslator>
#include <QFontDatabase>
#ifdef __PROCESSMODULE__
#include <QProcess>
#endif
#ifdef __EMBEDDED_LINUX__
#include <qqtinput.h>
#endif

QQtApplication* qqtApp = NULL;

QQtApplication::QQtApplication ( int& argc, char** argv ) :
    QApplication ( argc, argv ),
    bUPanAutoRun ( false )
{
    /*设置Qt框架内部文本编码系统，基础编码。*/
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
    QTextCodec::setCodecForTr ( QTextCodec::codecForName ( "UTF-8" ) );
    QTextCodec::setCodecForCStrings ( QTextCodec::codecForName ( "UTF-8" ) );
#endif
    QTextCodec::setCodecForLocale ( QTextCodec::codecForName ( "UTF-8" ) );

    /*嵌入式，应用名称必须指定*/
    QCoreApplication::setOrganizationName ( "QQt" );
    /*专为Mac OS X 准备的，macOS下配置文件: CONF_PATH/organizationDomain/ApplicationName.ini ... */
    QCoreApplication::setOrganizationDomain ( "www.qqt.com" ); //
    QCoreApplication::setApplicationName ( "QQt" );

    /*设置配置文件所在路径*/
    QSettings::setDefaultFormat ( QSettings::IniFormat );
    QSettings::setPath ( QSettings::IniFormat, QSettings::UserScope, CONFIG_PATH );
    QSettings::setPath ( QSettings::IniFormat, QSettings::SystemScope, CONFIG_PATH );

    /*程序中，需要更改语言的位置，可以通过qqtApp->setLanguage实现。languageChanged信号连接到每个页面的更换语言的函数*/
    qqtApp = this;

#ifdef __DARWIN__
    QDir::setCurrent ( qApp->applicationDirPath() );
#endif

    pline() << "app root:" << qApp->applicationDirPath();
    pline() << "app work root:" << QDir::currentPath();
    pline() << "Qt version:" << QT_VERSION_STR;
    pline() << "LibQQt version:" << STR ( QQT_VERSION );

#ifdef __EMBEDDED_LINUX__
    pline() << "QTDIR:" << QProcessEnvironment::systemEnvironment().value ( "QTDIR" );
    pline() << "TSLIB_TSDEVICE:" << QProcessEnvironment::systemEnvironment().value ( "TSLIB_TSDEVICE" );
#endif

    /*解决，嵌入式板子上，串口关闭后有时无法打开的问题*/
#ifdef __EMBEDDED_LINUX__
    system ( "rm -f /tmp/LCK..ttyS*" );
#endif

    /*设置语言翻译器，用户需要自己设置语言，（默认为页面上的词汇，设置后为翻译的中文或者英文）*/
    language = new QTranslator ( this );

    /*设置随机数种子*/
    qsrand ( QTime ( 0, 0, 0 ).secsTo ( QTime::currentTime() ) );

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    /*
     * 打印失真与否与此处无关
     */
    QApplication::setGraphicsSystem ( "raster" );
#endif

    /*设置鼠标隐藏*/
#ifdef __EMBEDDED_LINUX__
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
    //QApplication::setOverrideCursor(Qt::ArrowCursor);
    QWSServer::setCursorVisible ( false );
#else
    //TODO:
#endif
#endif

    /*嵌入式板子上，初始化输入法*/
    /*要求：数据库在CONF_PATH/PinYin.db必须存在，否则会弹出out of memory Error opening database*/
#ifdef __EMBEDDED_LINUX__
    QQtInput::Instance()->Init ( "min", "control", "QQT", 14, 14 );
#endif

    /*设置USB热插拔检测，支持U盘，键盘，鼠标检测*/
#ifdef __PLUGINSUPPORT__
    QObject::connect ( QQtPluginWatcher::Instance(), SIGNAL ( storageChanged ( int ) ),
                       this, SLOT ( slotUPanAutoRun ( int ) ) );
#endif

}

QQtApplication::~QQtApplication()
{
    QFontDatabase::removeAllApplicationFonts();
}


void QQtApplication::setQSSStyle ( QString qssfile )
{
    /*
     * Could not parse application stylesheet 告警 可以忽略
     * 关于选中项的颜色，暂且按照默认，后来更改整体UI颜色和效果
     * 可以实现橙色一行选中
     * 肯定也能实现表头透明和QQT效果。
     */
    QFile styleFile ( qssfile );
    styleFile.open ( QIODevice::ReadOnly );
    QString styleString ( styleFile.readAll() );;
    styleFile.close();
    setStyleSheet ( styleString );
    /*
     * 设置所有默认颜色
     */
    //setPalette(QPalette(QColor("#F0F0F0")));
}


void QQtApplication::setUPanAutorun ( bool run )
{
    bUPanAutoRun = run;
}

void QQtApplication::setWriteLogSystem ( bool open )
{
    /*设置日志系统*/
#ifdef __QQTLOGSYSTEMSUPPORT__

    if ( open )
    {
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
        qInstallMsgHandler ( QQt4FrameMsgHandler );
#else
        qInstallMessageHandler ( QQt5FrameMsgHandler );
#endif
    }
    else
    {
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
        qInstallMsgHandler ( NULL );
#else
        qInstallMessageHandler ( NULL );
#endif
    }

#endif
}

void QQtApplication::slotUPanAutoRun ( int status )
{
    if ( !bUPanAutoRun )
        return;

#ifdef __PLUGINSUPPORT__

    if ( QQtPluginWatcher::E_ADD == status )
    {
        QString mP = QQtPluginWatcher::Instance()->upanMountPath();
        QString app = QString ( "%1/autorun.sh" ).arg ( mP );
        QFile file ( app );

        if ( file.exists() )
        {
            if ( QDialog::Rejected == QQtMsgBox::question ( 0, tr ( "Some app want to run in u disk!accepted?" ) ) )
            {
                return;
            }
        }
        else
        {
            return;
        }

#ifdef __PROCESSMODULE__
        QProcess* p = new QProcess ( this );
        p->setWorkingDirectory ( mP );
        p->start ( app );
#else
        //TODO:
#endif
    }

#else
    Q_UNUSED ( status )
#endif
}


void QQtApplication::setTextFont ( QString fontfile, int fontsize )
{
    /*这个函数没有任何问题，检测完毕。过去的报错是工作目录不对，无法加载其他数据库*/
    /*此处，改为使用QFontDatabase的经典静态方法调用方式*/
    //ignored
    QFontDatabase db;

    int fontID = QFontDatabase::addApplicationFont ( fontfile );
    pline() << "font file:" << fontfile;
    pline() << "font id:" << fontID;
    pline() << "font families:" << QFontDatabase::applicationFontFamilies ( fontID );
    //如果字体不对，这个地方会崩溃，那么我要加处理吗？
    QString ziti = QFontDatabase::applicationFontFamilies ( fontID ).at ( 0 );
    pline() << "font name:" << ziti;

    QFont font ( ziti, fontsize );
    QApplication::setFont ( font );
}


void QQtApplication::setLanguage ( QString qmfile )
{
    language->load ( qmfile );
    pline() << "currentLanguage" << qmfile;
    installTranslator ( language );
    emit languageChanged();
}
