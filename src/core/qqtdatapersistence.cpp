#include <qqtdatapersistence.h>

#include <QFile>

QQtDataPersistence::QQtDataPersistence ( QObject* parent )
    : QObject ( parent )
{
    mDataFormat = JsonData;

    mTimerInterval = 1000;
    mTimer = new QTimer ( this );
    mTimer->setSingleShot ( false );
    mTimer->setInterval ( mTimerInterval );
    connect ( mTimer, SIGNAL ( timeout() ),
              this, SLOT ( slotTimeOut() ) );
}

QQtDataPersistence::~QQtDataPersistence() {}

void QQtDataPersistence::setDataFormat ( QQtDataPersistence::DataFormat format ) { mDataFormat = format; }

QQtDataPersistence::DataFormat QQtDataPersistence::dataFormat() const { return mDataFormat; }

void QQtDataPersistence::setDataFile ( const QString& fileName )
{
    mFileName = fileName;

    QByteArray bytes;
    QFile file ( mFileName );
    if ( file.exists() )
        file.open ( QFile::ReadOnly );
    else
        file.open ( QFile::Truncate | QFile::ReadOnly );
    bytes = file.readAll();
    file.close();

    mLock.lockForWrite();
    mDict.clear();
    switch ( mDataFormat )
    {
        case JsonData:
            mDict.fromJson ( bytes );
            break;
        case XmlData:
            mDict.fromXML ( bytes );
            break;
        case YamlData:
            mDict.fromYAML ( bytes );
            break;
        case IniData:
            mDict.fromINI ( bytes );
            break;
        case PropertiesData:
            mDict.fromProperties ( bytes );
            break;
        case MaxFormat:
        default:
            break;
    }
    mLock.unlock();;
}

QString QQtDataPersistence::dataFile() const { return mFileName; }

void QQtDataPersistence::prepareDataPersistence()
{
    mTimer->start();
}

void QQtDataPersistence::exitDataPersistence()
{
    mTimer->stop();
}

void QQtDataPersistence::start()
{
    mLock.lockForWrite();
}

QQtDictionary& QQtDataPersistence::dictionary() { return mDict; }

void QQtDataPersistence::stop()
{
    mLock.unlock();
}

int QQtDataPersistence::timerInterval() const { return mTimerInterval; }

void QQtDataPersistence::setTimerInterval ( int millSecond ) { mTimerInterval = millSecond; }

void QQtDataPersistence::slotTimeOut()
{
    QByteArray bytes;
    mLock.lockForRead();
    switch ( mDataFormat )
    {
        case JsonData:
            bytes = mDict.toJson ( QJsonDocument::Indented );
            break;
        case XmlData:
            bytes = mDict.toXML ( 4 );
            break;
        case YamlData:
            bytes = mDict.toYAML ( );
            break;
        case IniData:
            bytes = mDict.toINI ( );
            break;
        case PropertiesData:
            bytes = mDict.toProperties ( );
            break;
        case MaxFormat:
        default:
            break;
    }
    mLock.unlock();;

    QFile file ( mFileName );
    if ( file.exists() )
        file.open ( QFile::WriteOnly );
    else
        file.open ( QFile::Truncate | QFile::WriteOnly );
    file.write ( bytes );
    file.close();
}
