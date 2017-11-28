#include "qqtframe.h"
#include <QDir>

QSqlDatabase managerDB;
QString gUserName;
QString gPassword;

void QQtFrameMsgHandler ( QtMsgType type, const char* msg )
{
    /*只有这样才能保证，在app目录下，判定和创建目录*/
    if ( !QDir ( QDir ( qApp->applicationDirPath() ).filePath ( LOG_PATH ) ).exists() )
        QDir ( qApp->applicationDirPath() ).mkpath ( LOG_PATH );

    static QMutex mutex;

    mutex.lock();

    QString level = "Debug";

    switch ( type )
    {
    case QtDebugMsg:
        level = QString ( "Debug" );
        break;

    case QtWarningMsg:
        level = QString ( "Warning" );
        break;

    case QtCriticalMsg:
        level = QString ( "Critical" );
        break;

    case QtFatalMsg:
        level = QString ( "Fatal" );
        break;

    default:
        break;
    }

    QString current_date_time = QDateTime::currentDateTime().toString ( "yyyy-MM-dd hh:mm:ss ddd" );
    QString message = QString ( "%1 %2 %3" ).arg ( current_date_time ).arg ( level ).arg ( msg );
    QString current_date = QDateTime::currentDateTime().toString ( "yyyy-MM-dd" );

    //check file num when start stay 30 days
    //check file size, overtop max size out to new, one day one file

    /*经过排查，写文件出现段错误，原因出在设文件路径的地方*/
    /*其实，通过MacOS下，log目录随便乱出现，这其实是对QDir错误使用的结果，就应该看出，这个地方肯定也有错误*/
    /*已经纠正*/
    QString filename = QString ( "%1/%2/log-%3.txt" ).arg ( qApp->applicationDirPath() ).arg ( LOG_PATH )
                       .arg ( current_date );

#ifdef __EMBEDDED_LINUX__
    system ( QString ( "touch %1" ).arg ( filename ).toLocal8Bit().constData() );
#endif

    QFile logfile ( filename );

    if ( !logfile.exists() )
        logfile.open ( QFile::Truncate | QFile::WriteOnly );
    else
        logfile.open ( QFile::Append | QFile::WriteOnly );

    logfile.write ( message.toLocal8Bit() );
    logfile.close();

    mutex.unlock();

    fprintf ( stderr, "%s\n", msg );
}

void QQt4FrameMsgHandler ( QtMsgType type, const char* msg )
{
    QQtFrameMsgHandler ( type, msg );
}

#if QT_VERSION > QT_VERSION_CHECK(5, 0, 0)
void QQt5FrameMsgHandler ( QtMsgType type, const QMessageLogContext& context, const QString& content )
{

//    fprintf ( stderr, "%d %s %s %d %s %s\n", type,
//              context.category,
//              context.file,
//              context.line,
//              context.function,
//              content.toLocal8Bit().constData() );
    QQtFrameMsgHandler ( type, content.toLocal8Bit().constData() );
}
#endif

