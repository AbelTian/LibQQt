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

QQtDictionary& QQtDataPersistence::dictionary() { return mDict; }

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

void QQtDataPersistence::stop()
{
    mLock.unlock();
}

int QQtDataPersistence::timerInterval() const { return mTimerInterval; }

void QQtDataPersistence::setTimerInterval ( int millSecond ) { mTimerInterval = millSecond; }

void QQtDataPersistence::slotTimeOut()
{
    /*减少写文件；fix：文件相同时，使用marker强制写*/
    static QQtDictionary staticDict;
    if ( staticDict == mDict )
    {
        //字典相同
        if ( getMarker() == false )
        {
            return;
        }
        //用户设置了marker标记true，强制写
        setMarker ( false );
    }
    else
    {
        //字典不同
        staticDict = mDict;
    }

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
