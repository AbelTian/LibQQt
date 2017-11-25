#include "qqtframe.h"
#include <QDir>

QSqlDatabase managerDB;
QString gUserName;
QString gPassword;

void QQtFrameMsgHandler ( QtMsgType type, const char* msg )
{
    if ( !QDir ( LOG_PATH ).exists() )
        QDir().mkpath ( LOG_PATH );

    static QMutex mutex;

    mutex.lock();

    QString level;

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
    }

    QString current_date_time = QDateTime::currentDateTime().toString ( "yyyy-MM-dd hh:mm:ss ddd" );
    QString message = QString ( "%1 %2 %3" ).arg ( current_date_time ).arg ( level ).arg ( msg );

    QString current_date = QDateTime::currentDateTime().toString ( "yyyy-MM-dd" );

    //check file num when start stay 30 days
    //check file size, overtop max size out to new, one day one file
    QString filename = QString ( "%1/log-%2.txt" ).arg ( LOG_PATH ).arg ( current_date );

#ifdef __EMBEDDED_LINUX__
    system ( QString ( "touch %1" ).arg ( filename ).toLatin1().data() );
#endif

    QFile logfile ( filename );
    logfile.open ( QIODevice::WriteOnly | QIODevice::Append );
    QTextStream text_stream ( &logfile );
    text_stream << message << "\r\n";
    logfile.flush();
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

