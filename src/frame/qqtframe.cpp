#include "qqtframe.h"

QSqlDatabase managerDB;
QString gUserName;
QString gPassword;

void qqtFrameMsgHandler(QtMsgType type, const char * msg)
{
    static QMutex mutex;
    mutex.lock();

    QString text;
    switch(type)
    {
    case QtDebugMsg:
        text = QString("Debug");
        break;

    case QtWarningMsg:
        text = QString("Warning");
        break;

    case QtCriticalMsg:
        text = QString("Critical");
        break;

    case QtFatalMsg:
        text = QString("Fatal");
    }

    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString message = QString("%1 %2 %3").arg(current_date_time).arg(text).arg(msg);
    QString current_date = QDateTime::currentDateTime().toString("yyyy-MM-dd");

    //check file num when start stay 30 days
    //check file size, overtop max size out to new, one day one file
    QString filename = QString("./log/log-%1.txt").arg(current_date);

#ifdef __EMBEDDED_LINUX__
    system(QString("touch %1").arg(filename).toLatin1().data());
#endif

    QFile file(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    text_stream << message << "\r\n";
    file.flush();
    file.close();

    mutex.unlock();

    fprintf(stderr, "%s\n", msg);
}
