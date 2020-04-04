#include <qqtdatapersistence.h>

#include <QFile>

QQtDataPersistence::QQtDataPersistence ( QObject* parent )
    : QObject ( parent )
{
    reset_marker();
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
    if ( mFileName.isEmpty() )
        return;
    parseContentToDictionary();
}

QString QQtDataPersistence::dataFile() const { return mFileName; }

void QQtDataPersistence::prepareDataPersistence()
{
    if ( mFileName.isEmpty() )
        return;
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

QQtDictionary& QQtDataPersistence::dictionary()
{
    return mDict;
}

const QQtDictionary& QQtDataPersistence::dictionary() const
{
    return mDict;
}

void QQtDataPersistence::stop()
{
    marker();
    mLock.unlock();
}

int QQtDataPersistence::timerInterval() const { return mTimerInterval; }

void QQtDataPersistence::setTimerInterval ( int millSecond ) { mTimerInterval = millSecond; }

void QQtDataPersistence::slotTimeOut()
{
    /*减少写文件；marker强制写*/
    if ( getMarker() == false )
    {
        return;
    }
    //用户设置了marker标记true，强制写
    setMarker ( false );

    QByteArray bytes;
    packDictionaryToContent ( bytes );
    writeFile ( bytes );
}

void QQtDataPersistence::parseContentToDictionary()
{
    QByteArray bytes;
    readFile ( bytes );

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
#ifdef __YAMLSUPPORT__
        case YamlData:
            mDict.fromYAML ( bytes );
            break;
#endif
#ifdef __INICONTENTSUPPORT__
        case IniData:
            mDict.fromINI ( bytes );
            break;
        case PropertiesData:
            mDict.fromProperties ( bytes );
            break;
#endif
        case MaxFormat:
        default:
            break;
    }
    mLock.unlock();;
}

void QQtDataPersistence::packDictionaryToContent ( QByteArray& bytes )
{
    mLock.lockForRead();
    switch ( mDataFormat )
    {
        case JsonData:
            bytes = mDict.toJson ( QJsonDocument::Indented );
            break;
        case XmlData:
            bytes = mDict.toXML ( 4 );
            break;
#ifdef __YAMLSUPPORT__
        case YamlData:
            bytes = mDict.toYAML ( );
            break;
#endif
#ifdef __INICONTENTSUPPORT__
        case IniData:
            bytes = mDict.toINI ( );
            break;
        case PropertiesData:
            bytes = mDict.toProperties ( );
            break;
#endif
        case MaxFormat:
        default:
            break;
    }
    mLock.unlock();;
}

void QQtDataPersistence::readFile ( QByteArray& bytes )
{
    if ( mFileName.isEmpty() )
        return;

    QFile file ( mFileName );
    if ( file.exists() )
        file.open ( QFile::ReadOnly );
    else
        file.open ( QFile::Truncate | QFile::ReadOnly );
    bytes = file.readAll();
    file.close();
}

void QQtDataPersistence::writeFile ( const QByteArray& bytes )
{
    if ( mFileName.isEmpty() )
        return;

    QFile file ( mFileName );
    if ( file.exists() )
        file.open ( QFile::WriteOnly );
    else
        file.open ( QFile::Truncate | QFile::WriteOnly );
    file.write ( bytes );
    file.close();
}

void QQtDataPersistence::marker ()
{
    bMarker = true;
}

void QQtDataPersistence::reset_marker()
{
    bMarker = false;
}

bool QQtDataPersistence::setMarker ( bool mark )
{
    bMarker = mark;
}

bool QQtDataPersistence::getMarker() const
{
    return bMarker;
}
