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
#ifdef __PROCESSSUPPORT__
#include <QProcess>
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

    /*配置文件名称设定*/
    //App继承QQtApplication以后，必须设置这三个Value，改变为自己的Value。
    /*嵌入式，应用名称必须指定 配置文件路径$CONF_PATH/organizationName/applicationName.conf[.ini]*/
    QCoreApplication::setOrganizationName ( "QQt" );
    /*专为Mac OS X 准备的，macOS下配置文件: $CONF_PATH/organizationDomain/ApplicationName.ini ... */
    QCoreApplication::setOrganizationDomain ( "www.qqt.com" ); //
    QCoreApplication::setApplicationName ( "QQt" );

    /*设置配置文件路径*/
    QSettings::setDefaultFormat ( QSettings::IniFormat );
    QSettings::setPath ( QSettings::IniFormat, QSettings::UserScope, CONFIG_PATH );
    QSettings::setPath ( QSettings::IniFormat, QSettings::SystemScope, CONFIG_PATH );

    /*程序中，需要更改语言，可以通过qqtApp->setLanguage实现。languageChanged信号连接到每个页面的刷新语言的槽函数，一般会在槽函数里调用ui->retranslateUi(this)*/
    qqtApp = this;

    /*这里是个方便,因为配置文件默认在运行目录.*/
    /*如果用户的运行程序，希望运行目录在当前执行的目录下，在自己的程序中改变下即可。*/
    /*在继承类里做这个工作,工作量实在是太大了,所以,我在这里做的.*/
//#if defined (__DARWIN__) || defined (__EMBEDDED_LINUX__)
    startWorkRoot = QDir::currentPath();
    QDir::setCurrent ( qApp->applicationDirPath() );
//#endif

    qDebug() << qPrintable ( tr ( "QQt Application Framework Software" ) );
    qDebug() << qPrintable ( tr ( "Copyright (C) 2017-2020 Tianduanrui. All rights reserved." ) );
    //qDebug() << tr ( "Assigned by Dezhou." );

    pline() << "Qt version:" << QT_VERSION_STR;
    pline() << "LibQQt version:" << STR ( QQT_VERSION );
    pline() << "App root:" << qApp->applicationDirPath();
    pline() << "App work root:" << QDir::currentPath();

#ifdef __EMBEDDED_LINUX__
    pline() << "QTDIR:" << QProcessEnvironment::systemEnvironment().value ( "QTDIR" );
    pline() << "TSLIB_TSDEVICE:" << QProcessEnvironment::systemEnvironment().value ( "TSLIB_TSDEVICE" );
#endif

    /*解决：嵌入式板子上串口关闭后有时无法打开的问题*/
#ifdef __EMBEDDED_LINUX__
    system ( "rm -f /tmp/LCK..ttyS*" );
#endif

    /*设置语言翻译器。用户需要自己设置语言，（默认为页面上的词汇，设置后为翻译的中文或者英文或者俄文或者其他语言。）*/
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

    /*设置USB热插拔检测，支持U盘，键盘，鼠标检测*/
#ifdef __PLUGINSUPPORT__
    QObject::connect ( QQtPluginWatcher::Instance(), SIGNAL ( storageChanged ( int ) ),
                       this, SLOT ( slotUPanAutoRun ( int ) ) );
#endif

    /*输入法*/
    /*LibQQt 3.0以后，移除QQtInput模块。*/
    /*LibQQt 3.0以后，如果用户需要使用输入法，请使用Multi-link Technology依赖QQtInput工程。*/
    /*在App工程pro里添加add_dependent_manager(QQtInput)即可。*/
    /*我把QQtInput类单独制作成了一个Library，QQtInput library。请参看QQtInput工程。*/
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

void QQtApplication::setHighDpiScaling ( bool open )
{
#if QT_VERSION >= QT_VERSION_CHECK(5,6,0)
    setAttribute ( Qt::AA_EnableHighDpiScaling, open );
    //这个设置好像没什么用，如果打开了，图片会被窗口吃掉一部分才开始缩小。如果不开就正常了。奇怪的图形坐标系。好像是个Qt BUG，所以关闭。应该识别为放大了的，可是没识别，上边那个好像就把图片放大了。
    //setAttribute ( Qt::AA_UseHighDpiPixmaps, open );
#endif
}

void QQtApplication::setWorkRoot ( const QString& workroot )
{
    QDir::setCurrent ( workroot );
}

QString QQtApplication::getWorkRoot()
{
    return QDir::currentPath();
}

const QString& QQtApplication::getStartingWorkRoot() const
{
    return startWorkRoot;
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

#ifdef __PROCESSSUPPORT__
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


bool QQtApplication::setTextFont ( QString fontfile, int fontsize )
{
    /*这个函数没有任何问题，检测完毕。过去的报错是工作目录不对，无法加载其他数据库*/
    /*此处，改为使用QFontDatabase的经典静态方法调用方式*/
    //ignored
    QFontDatabase fontdb0;

    int fontID = QFontDatabase::addApplicationFont ( fontfile );
    pline() << "font file:" << fontfile;
    pline() << "font id:" << fontID;
    pline() << "font families:" << QFontDatabase::applicationFontFamilies ( fontID );
    //如果字体不对，这个地方会崩溃，那么我要加处理吗？加。
    if ( fontID < 0 )
    {
        pline() << QString ( "%1 is setted failed, unexisted, but ignored." ).arg ( fontfile );
        return false;
    }
    QString ziti = QFontDatabase::applicationFontFamilies ( fontID ).at ( 0 );
    pline() << "font name:" << ziti;

    QFont font1 ( ziti, fontsize );
    QApplication::setFont ( font1 );

    return true;
}


void QQtApplication::setLanguage ( QString qmfile )
{
    language->load ( qmfile );
    pline() << "currentLanguage" << qmfile;
    installTranslator ( language );
    emit languageChanged();
}
