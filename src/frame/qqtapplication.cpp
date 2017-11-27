#include "qqtapplication.h"
#ifdef __PLUGINWATCHER__
#include "qqtpluginwatcher.h"
#endif
#include <qqtwidgets.h>
#include <qqtmsgbox.h>
#include <qqtversion.h>
#include <qqtframe.h>
#include <qqtcore.h>
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

QQtApplication::QQtApplication ( int& argc, char** argv ) :
    QApplication ( argc, argv ),
    bUPanAutoRun ( false )
{
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
    QTextCodec::setCodecForTr ( QTextCodec::codecForName ( "UTF-8" ) );
    QTextCodec::setCodecForCStrings ( QTextCodec::codecForName ( "UTF-8" ) );
#endif
    QTextCodec::setCodecForLocale ( QTextCodec::codecForName ( "UTF-8" ) );

    QCoreApplication::setOrganizationName ( COMPANY_NAME );
    QCoreApplication::setOrganizationDomain ( COMPANY_DOMAIN ); // 专为Mac OS X 准备的
    QCoreApplication::setApplicationName ( PRODUCT_NAME );
    QSettings::setPath ( QSettings::NativeFormat, QSettings::UserScope, CONFIG_PATH );
    QSettings::setPath ( QSettings::NativeFormat, QSettings::SystemScope, CONFIG_PATH );

#ifdef __QQTLOGFILESUPPORT__
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    qInstallMsgHandler ( QQt4FrameMsgHandler );
#else
    qInstallMessageHandler ( QQt5FrameMsgHandler );
#endif
#endif

#ifdef __EMBEDDED_LINUX__
    system ( "rm -f /tmp/LCK..ttyS*" );
#endif

    pline() << qApp->applicationDirPath();

    language = new QTranslator ( this );
    setLanguage();

    qsrand ( QTime ( 0, 0, 0 ).secsTo ( QTime::currentTime() ) );

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
    QQtInput::Instance()->Init ( "min", "control", "QQT", 14, 14 );
#endif

#ifdef __PLUGINWATCHER__
    QObject::connect ( QQtPluginWatcher::Instance(), SIGNAL ( storageChanged ( int ) ),
                       this, SLOT ( slotUPanAutoRun ( int ) ) );
#endif

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

void QQtApplication::slotUPanAutoRun ( int status )
{
    if ( !bUPanAutoRun )
        return;

#ifdef __PLUGINWATCHER__

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
    QFontDatabase db;

    int fontID = db.addApplicationFont ( fontfile );
    QString ziti = db.applicationFontFamilies ( fontID ).at ( 0 );
    pline() << ziti;

    QFont font ( ziti, fontsize );
    QApplication::setFont ( font );
}


void QQtApplication::setLanguage ( QString qmfile )
{
    language->load ( qmfile );
    pline() << "currentLanguage" << qmfile;
    installTranslator ( language );
}
