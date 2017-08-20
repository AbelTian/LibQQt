#include "qqtdefine.h"


QByteArray &operator<<(QByteArray &l, const quint8 r)
{
    return l.append(r);
}


QByteArray &operator<<(QByteArray &l, const quint16 r)
{
    return l<<quint8(r>>8)<<quint8(r);
}


QByteArray &operator<<(QByteArray &l, const quint32 r)
{
    return l<<quint16(r>>16)<<quint16(r);
}


QByteArray &operator<<(QByteArray &l, const QByteArray &r)
{
    return l.append(r);
}


QByteArray &operator>>(QByteArray &l, quint8 &r)
{
    r = l.left(sizeof(quint8))[0];
    return l.remove(0, sizeof(quint8));
}


QByteArray &operator>>(QByteArray &l, quint16 &r)
{
    quint8 r0 = 0, r1 = 0;
    l >> r0 >> r1;
    r = ( r0 << 8 ) | r1;
    return l;
}


QByteArray &operator>>(QByteArray &l, quint32 &r)
{
    quint8 r0 = 0, r1 = 0, r2 = 0, r3 = 0;
    l >> r0 >> r1 >> r2 >> r3;
    r = ( r0 << 24 ) | ( r1 << 16 ) | ( r2 << 8 ) | r3;
    return l;
}


QByteArray &operator>>(QByteArray &l, QByteArray &r)
{
    r = l.left(r.size());
    return l.remove(0, r.size());
}

QByteArray &operator<<(QByteArray &l, const qint8 r)
{
    quint8 ubyte = quint8(r);
    l << ubyte;
    return l;
}

QByteArray &operator<<(QByteArray &l, const qint16 r)
{
    quint16 ubyte = quint16(r);
    l << ubyte;
    return l;
}

QByteArray &operator<<(QByteArray &l, const qint32 r)
{
    quint32 ubyte = quint32(r);
    l << ubyte;
    return l;
}

QByteArray &operator>>(QByteArray &l, qint8 r)
{
    quint8 ubyte = 0;
    l >> ubyte;
    r = qint8(ubyte);
    return l;
}

QByteArray &operator>>(QByteArray &l, qint16 r)
{
    quint16 ubyte = 0;
    l >> ubyte;
    r = qint16(ubyte);
    return l;
}

QByteArray &operator>>(QByteArray &l, qint32 r)
{
    quint32 ubyte = 0;
    l >> ubyte;
    r = qint32(ubyte);
    return l;
}


tagBtnIconTable::tagBtnIconTable()
{
    pixmap[BTN_NORMAL] = "./skin/default/bt_bt_normal.png";
    pixmap[BTN_UNCHECK] = "./skin/default/bt_bt_normal.png";
#ifdef __MIPS_LINUX__
    pixmap[BTN_HOVER] = "./skin/default/bt_bt_hover.png";
    pixmap[BTN_CHECK] = "./skin/default/bt_bt_hover.png";
    pixmap[BTN_PRESS] = "./skin/default/bt_bt_hover.png";
#else
    pixmap[BTN_HOVER] = "./skin/default/bt_bt_hover.png";
    pixmap[BTN_CHECK] = "./skin/default/bt_bt_check.png";
    pixmap[BTN_PRESS] = "./skin/default/bt_bt_press.png";
#endif
    pixmap[BTN_DISABLE] = "./skin/default/bt_bt_disable.png";
}

QString tagBtnIconTable::pixMap(int index)
{
    if(index < 0 || index + 1 > BTN_MAX)
        return pixmap[BTN_NORMAL];
    return pixmap[index];
}

void tagBtnIconTable::setPixMap(int index, QString pix)
{
    if(index < 0 || index + 1 > BTN_MAX)
        return;
    pixmap[index] = pix;
}

void tagBtnIconTable::initNormal(QString normal, QString press)
{
    if(!normal.isEmpty())
        pixmap[BTN_NORMAL] = normal;
    if(!press.isEmpty())
        pixmap[BTN_PRESS] = press;
}

void tagBtnIconTable::initCheck(QString uncheck, QString check)
{
    if(!uncheck.isEmpty())
        pixmap[BTN_UNCHECK] = uncheck;
    if(!check.isEmpty())
        pixmap[BTN_CHECK] = check;
}

void tagBtnIconTable::initOther(QString hover, QString disable)
{
    if(!hover.isEmpty())
        pixmap[BTN_HOVER] = hover;
    if(!disable.isEmpty())
        pixmap[BTN_DISABLE] = disable;
}

QString &tagBtnIconTable::operator [](int index)
{
    if(index < 0 || index >= BTN_MAX)
        return pixmap[0];

    return pixmap[index];
}

const QString &tagBtnIconTable::operator[](int index) const
{
    return operator [](index);
}


bool tagWifi::isValid()
{
    return wifi[ESSID_BSSID].isEmpty() ? false : true;
}

#ifdef __MIPS_LINUX__
tagWifi& tagWifi::operator= (tagWifi& w)
#else
tagWifi &tagWifi::operator=(const tagWifi &w)
#endif
{
    for(int i = ESSID_STATUS; i < ESSID_MAX; i++)
        wifi[i] = w[i];
    return *this;
}

QString &tagWifi::operator[](int index)
{
    if(index < ESSID_STATUS || index >= ESSID_MAX)
        return wifi[0];

    return wifi[index];
}

const QString &tagWifi::operator[](int index) const
{
    return operator [](index);
}

QSqlDatabase managerDB;
QString gUserName;
QString gPassword;


QSqlDatabase newDatabaseConn()
{
    QUuid uuid = QUuid::createUuid();
    //qDebug() << uuid.toString();
    return QSqlDatabase::addDatabase(DB_TYPE, uuid.toString());
}

void moveCenter(QWidget *w)
{
    int x1 = 0, y1 = 0;

    x1 = ( QApplication::desktop()->availableGeometry().width()
           - w->width() ) / 2;
    y1 = ( QApplication::desktop()->availableGeometry().height()
           - w->height() ) / 2;


    w->move(x1, y1);

    return;
}

//opened
void setDatabaseName(QSqlDatabase &db, QString dbName)
{
    if(db.isOpen())
        db.close();

    db.setDatabaseName(QString("%1/%2").arg(DB_PATH).arg(dbName));

    if (!db.open()) {
        QMessageBox::warning(0, QObject::tr("QSQLITE %1 Error").arg(db.databaseName()),
                             db.lastError().text());
        return;
    }
}


void openDatabase(QSqlDatabase &db)
{
    if(db.isOpen())
        return;

    if (!db.open()) {
        QMessageBox::warning(0, QObject::tr("QSQLITE %1 Error").arg(db.databaseName()),
                             db.lastError().text());
        return;
    }
}


void closeDatabase(QSqlDatabase &db)
{
    db.close();
}


void moveRight(QWidget *w)
{
    w->move((QApplication::desktop()->width() - w->width()), 0);
}


void msgHandler(QtMsgType type, const char * msg)
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

#ifdef __MIPS_LINUX__
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


void QQTSleep(int millsecond)
{
    QElapsedTimer timer;
    timer.start();
    while(timer.elapsed() < millsecond)
    {
         QApplication::processEvents();
    }
}
