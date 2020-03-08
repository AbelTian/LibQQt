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
    parseContentToDictionary();
}

QString QQtDataPersistence::dataFile() const { return mFileName; }

void QQtDataPersistence::prepareDataPersistence()
{
    parseContentToDictionary();
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
    packDictionaryToContent ( bytes );

    //如果在字典的值不同的时候才存储，其他人对文件的修改将无法体现在字典里。
    //非独占式，不读文件，减少了写次数。
    static QQtDictionary staticDict;
    if ( staticDict == mDict )
    {
        //qDebug() << "字典相同，不写。";
        //return;

        //如果在字典的值不同于文件里的值得时候存储，可以减少写文件次数。
        //独占式，每次读文件，减少了写次数。
        QByteArray bytes1;
        readFile ( bytes1 );
        if ( bytes1 == bytes )
        {
            //qDebug() << "相同，不写";
            return;
        }
        else
        {
            //qDebug() << "不相同，写";
        }
    }
    else
    {
        //qDebug() << "字典不同，写。";
        staticDict = mDict;
    }

#if 0
    //如果在字典的值不同于文件里的值得时候存储，可以减少写文件次数。
    //独占式，每次读文件，减少了写次数。
    {
        QByteArray bytes1;
        readFile ( bytes1 );

        if ( bytes1 == bytes )
        {
            qDebug() << "相同，不写";
            return;
        }
        else
        {
            qDebug() << "不相同，写";
        }
    }
#endif

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
