#include "qqtapp.h"
#include "qqt-qt.h"
#include "qqtgui.h"
#include "qqtcore.h"
#include "qqtinput.h"
#include "qqtmsgbox.h"
#include "qqtframe.h"
#include "qqttcpclient.h"
#include "qqttcpserver.h"
#include "qqtserialport.h"
#include "qqtpluginwatcher.h"
#include "qqtversion.h"

/*
 * 转移到Lan协议当中去。
 */
void QQTLanServer ( QObject* parent = 0 )
{
    static QQtTcpServer* s = new QQtTcpServer ( parent );
    s->listen ( QHostAddress::Any, 8000 );

    //s->installedProtocol();
}

QQTApp::QQTApp ( int& argc, char** argv ) : QApplication ( argc, argv )
{
#ifndef __QT5__
    QTextCodec::setCodecForTr ( QTextCodec::codecForName ( "UTF-8" ) );
    QTextCodec::setCodecForCStrings ( QTextCodec::codecForName ( "UTF-8" ) );
#endif
    QTextCodec::setCodecForLocale ( QTextCodec::codecForName ( "UTF-8" ) );

    QApplication::setOrganizationName ( "QQt" );
    QApplication::setOrganizationDomain ( "qqtffmpeg.com" ); // 专为Mac OS X 准备的
    QApplication::setApplicationName ( "qqtffmpeg" );
    QSettings::setPath ( QSettings::NativeFormat, QSettings::UserScope, CONFIG_PATH );
    QSettings::setPath ( QSettings::NativeFormat, QSettings::SystemScope, CONFIG_PATH );

    system ( "rm -f /tmp/LCK..ttyS*" );

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    /*
     * 打印失真与否与此处无关
     */
    QApplication::setGraphicsSystem ( "raster" );
#endif

#ifdef __EMBEDDED_LINUX__
    //QApplication::setOverrideCursor(Qt::ArrowCursor);
    QWSServer::setCursorVisible ( false );
#endif

#ifdef __EMBEDDED_LINUX__
    QFontDatabase db;

#if 0
    int heitiFontID = db.addApplicationFont ( "/usr/lib/fonts/heiti.ttf" );
    QString heiti = db.applicationFontFamilies ( heitiFontID ).at ( 0 );
    pline() << heiti;
#else
    int wenquanyiFontID = db.addApplicationFont ( "/usr/lib/fonts/wenquanyi.ttf" );
    QString wenquanyi = db.applicationFontFamilies ( wenquanyiFontID ).at ( 0 );
    pline() << wenquanyi;
#endif

    QFont font ( wenquanyi, 11 );
    QApplication::setFont ( font );
#endif

    pline() << qApp->applicationDirPath();

    language = new QTranslator ( this );
    setLanguage();

#if 0
    /*
     * 打开方法数据库
     */
    managerDB = newDatabaseConn();
    setDatabaseName ( managerDB, DB_MANAGER );
#endif

#if 1
    /*
     * Could not parse application stylesheet 告警 可以忽略
     * 关于选中项的颜色，暂且按照默认，后来更改整体UI颜色和效果
     * 可以实现橙色一行选中
     * 肯定也能实现表头透明和QQT效果。
     */
    QFile styleFile ( "./skin/default.qss" );
    styleFile.open ( QIODevice::ReadOnly );
    QString styleString ( styleFile.readAll() );;
    styleFile.close();
    setStyleSheet ( styleString );
    /*
     * 设置所有默认颜色
     */
    //setPalette(QPalette(QColor("#F0F0F0")));
#endif

#ifdef __EMBEDDED_LINUX__
    QQtInput::Instance()->Init ( "min", "control", "QQT", 14, 14 );
#endif

    qsrand ( QTime ( 0, 0, 0 ).secsTo ( QTime::currentTime() ) );

#if 0
    QObject::connect ( QQtPluginWatcher::Instance(), SIGNAL ( storageChanged ( int ) ),
                       this, SLOT ( slotUPanAutoRun ( int ) ) );
#endif
    //QQtTcpClient
    //QQTCloudClientInstance(this);
#ifdef __EMBEDDED_LINUX__
    //QQTEthManager
    QQtEthenetManager::Instance ( this );
#endif
    //QQtTcpServer
    //QQTPeerPort

    //QQTPeerPortInstance(this);
    //QQtSerialPort
    //QQTUserSerialPortInstance(this);
}

QQTApp::~QQTApp() {}

void QQTApp::setLanguage()
{
    /*
     * 公司或组织名
     * 应用程序名
     */
    QSettings setting;
    QString qm;
    qm = setting.value ( "Language" ).toInt() ? "./lang/en_US.qm" : "./lang/zh_CN.qm";

    language->load ( qm );
    pline() << "currentLanguage" << qm;
    installTranslator ( language );
}

void QQTApp::slotUPanAutoRun ( int status )
{
#if 0
    if ( QQtPluginWatcher::E_ADD == status )
    {
        QString mP = QQtPluginWatcher::Instance()->upanMountPath();
        QString app = QString ( "%1/autorun.sh" ).arg ( mP );
        QFile file ( app );
        if ( file.exists() )
            if ( QDialog::Rejected == QQtMsgBox::question ( 0, tr ( "Some app want to run in u disk!accepted?" ) ) )
                return;
        QProcess* p = new QProcess ( this );
        p->setWorkingDirectory ( mP );
        p->start ( app );
    }
#endif
}
