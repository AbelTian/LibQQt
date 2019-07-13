#include "qqtwavaudiomanager.h"
#include "libqwav.h"

QQtWavAudioInput::QQtWavAudioInput ( QObject* parent ) : QObject ( parent )
{
    mTimer = new QTimer ( this );
    connect ( mTimer, SIGNAL ( timeout() ), SLOT ( slotTimeout() ) );

    mFileBytes.clear();
    mBytes.clear();
    mBytesBuffer.setBuffer ( &mBytes );

    mTimerInterval = 20;
}

QIODevice* QQtWavAudioInput::setSourceFile ( const QString& localFile )
{
    //如果开着，不管。
    mSourceFile = localFile;

#if QT_VERSION > QT_VERSION_CHECK(5,0,0)

    //判断文件类型是否接受
    QMimeDatabase mimedb;
    QMimeType mimetype = mimedb.mimeTypeForFile ( mSourceFile );

    if ( !QSoundEffect::supportedMimeTypes().contains ( mimetype.name(), Qt::CaseInsensitive ) )
    {
        pline() << "filename" << localFile << "mimetype" << mimetype.name()
                << QSoundEffect::supportedMimeTypes().contains ( mimetype.name(), Qt::CaseInsensitive ) ;
        pline() << "can't play file";
        return NULL;
    }
#endif

    //判断音频具体格式
    //支持qrc文件
    TWavFileInfo info;
    bool ret = anlysisWavFileHeader ( mSourceFile, mFormat, info );
    //仅仅支持本地文件
    //bool ret = anlysisWavFileHeader_C ( localFile );

    if ( !ret )
    {
        pline() << "wav format parse fail";
        return NULL;
    }

    mFileTotalSize = info.fileTotalSize;
    mFileHeaderSize = info.fileHeaderSize;
    mFileDataSize = info.fileDataSize;
    mFileTailSize = info.fileTailSize;

    return &mBytesBuffer;
}

void QQtWavAudioInput::setTimerInterval ( int millSecond ) { mTimerInterval = millSecond; }


void QQtWavAudioInput::start()
{
    stop();

    mChannelCount = mFormat.channelCount();
    mSampleSize = mFormat.sampleSize();
    mSampleRate = mFormat.sampleRate();

    //读取到数据
    QFile f ( mSourceFile );
    f.open ( QFile::ReadOnly );
    QByteArray b = f.read ( mFileHeaderSize );
    //这个地方测试完成：内部解析wav头，两个都很成功。C Qt 都OK.
    //pline() << b;
    mFileBytes = f.read ( mFileDataSize );
    f.close();

    mBytesBuffer.open ( QIODevice::ReadWrite );
    mTimer->start ( mTimerInterval );
    return;
}

void QQtWavAudioInput::stop()
{
    //如果正在播放，先关闭写入音频数据流。
    mTimer->stop();
    //如果存在，则清空。
    //这两个变量Buffer是什么操作关系？QBuffer是QByteArray的QIODevice套。
    //改变QByteArray，会直接影响QBuffer的读写。QBuffer也会影响QByteArray的内容。
    mFileBytes.clear();
    mBytes.clear();

    if ( mBytesBuffer.isOpen() )
        mBytesBuffer.close();
}

int QQtWavAudioInput::fileTotalSize() {return mFileTotalSize;}

int QQtWavAudioInput::fileHeaderSize() { return mFileHeaderSize; }

int QQtWavAudioInput::fileDataSize() {return mFileDataSize;}

int QQtWavAudioInput::fileTailSize() {return mFileTailSize;}


void QQtWavAudioInput::slotTimeout()
{
    //1s 字节数 = 采样率 * 采样深度（位宽）* 通道数 / 8
    //mTimerInterval ms 字节数 = 1s 字节数 / (1000/mTimerInterval)
    //每个音符 字节数 = 采样深度（位宽）* 通道数 / 8;
    int frameSize = mSampleRate * mSampleSize * mChannelCount / 8 / ( 1000 / mTimerInterval );
    QByteArray tempBytes;

    if ( mFileBytes.size() > frameSize )
    {
        tempBytes.resize ( frameSize );
    }
    else
    {
        tempBytes.resize ( mFileBytes.size() );
    }

    //pline() << mFileBytes.size() << tempBytes.size() << frameSize;
    //mFileBytes 逐渐减少
    mFileBytes >> tempBytes;
    //这是给用户的。
    mBytes = tempBytes;
    //回到初始位置
    mBytesBuffer.seek ( 0 );
    //激发readyRead信号
    mBytesBuffer.write ( 0 );

    if ( mFileBytes.isEmpty() )
    {
        //pline() << mFileBytes.size() << 0 << frameSize;
        //这里不要关闭Buffer，客户一般还没用完。
        mTimer->stop();
    }

    return;
}

QQtWavAudioOutput::QQtWavAudioOutput ( QObject* parent ) : QObject ( parent )
{
    mFileBytes.clear();
    mBytesBuffer.setBuffer ( &mFileBytes );

    mFormat.setByteOrder ( QAudioFormat::LittleEndian );
    mFormat.setChannelCount ( 2 );
    mFormat.setCodec ( "audio/pcm" );
    mFormat.setSampleRate ( 44100 );
    mFormat.setSampleSize ( 16 );
    mFormat.setSampleType ( QAudioFormat::SignedInt );
}

QIODevice* QQtWavAudioOutput::setSourceFile ( const QString& localFile )
{
    mSourceFile = localFile;
    return &mBytesBuffer;
}

QAudioFormat& QQtWavAudioOutput::format() { return mFormat; }

void QQtWavAudioOutput::start()
{
    if ( mSourceFile.isEmpty() )
        return;

    //这里清空文件，不会发生保存？不会，这里清空Buffer。
    mFileBytes.clear();

    if ( mBytesBuffer.isOpen() )
        mBytesBuffer.close();

    mBytesBuffer.open ( QIODevice::WriteOnly );
}

void QQtWavAudioOutput::stop()
{
    //在stop的时候，才会把数据全部存储到wav文件
    if ( mSourceFile.isEmpty() )
        return;

    //防止多次关闭导致音频文件被破坏。
    if ( mFileBytes.isEmpty() )
        return;

    QFile file ( mSourceFile );
    file.open ( QFile::Truncate | QFile::WriteOnly );

    addWavHeader ( file, mFormat );
    file.write ( mFileBytes );
    addWavTail ( file );
    //这个时候，Header里面RiffLength是错误的。改写
    file.seek ( 0 );
    addWavHeader ( file, mFormat );
    //现在纠正好了。
    file.close();

    mFileBytes.clear();

    if ( mBytesBuffer.isOpen() )
        mBytesBuffer.close();
}



QQtWavAudioManager::QQtWavAudioManager ( QObject* parent ) : QObject ( parent )
{
    mInputManager = new QQtWavAudioInput ( this );
    mOutputManager = new QQtWavAudioOutput ( this );

    mInputDevice = mInputManager->device();
    mOutputDevice = mOutputManager->device();

    connect ( mInputDevice, SIGNAL ( readyRead() ),
              this, SIGNAL ( readyRead() ) );

}

QQtWavAudioManager::~QQtWavAudioManager()
{
    stopInput();
    stopOutput();
}

void QQtWavAudioManager::setInputSourceFile ( const QString& localFile )
{
    QIODevice* ioDev = mInputManager->setSourceFile ( localFile );

    if ( !ioDev )
    {
        pline() << mInputManager->sourceFile()
                << inputAudioFormat().sampleSize()
                << inputAudioFormat().sampleRate()
                << inputAudioFormat().channelCount()
                << "open failed, errcode:"
                << "-1";
        return;
    }
}

QString QQtWavAudioManager::inputSourceFile() { return mInputManager->sourceFile(); }

void QQtWavAudioManager::setOutputSourceFile ( const QString& localFile )
{
    QIODevice* ioDev = mOutputManager->setSourceFile ( localFile );

    if ( !ioDev )
    {
        pline() << mOutputManager->sourceFile()
                << outputAudioFormat().sampleSize()
                << outputAudioFormat().sampleRate()
                << outputAudioFormat().channelCount()
                << "open failed, errcode:"
                << "-1";
        return;
    }
}

QString QQtWavAudioManager::outputSourceFile() { return mOutputManager->sourceFile(); }

const QAudioFormat& QQtWavAudioManager::inputAudioFormat() { return mInputManager->format(); }

QAudioFormat& QQtWavAudioManager::outputAudioFormat() { return mOutputManager->format(); }

int QQtWavAudioManager::inputFileTotalSize() { return mInputManager->fileTotalSize(); }

int QQtWavAudioManager::inputFileHeaderSize() { return mInputManager->fileHeaderSize(); }

int QQtWavAudioManager::inputFileDataSize() { return mInputManager->fileDataSize(); }

int QQtWavAudioManager::inputFileTailSize() { return mInputManager->fileTailSize(); }

QQtWavAudioInput* QQtWavAudioManager::inputManager() { return mInputManager; }

QIODevice* QQtWavAudioManager::inputDevice() { return mInputDevice; }

QQtWavAudioOutput* QQtWavAudioManager::outputManager() { return mOutputManager; }

QIODevice* QQtWavAudioManager::outputDevice() { return mOutputDevice; }

void QQtWavAudioManager::startInput()
{
    stopInput();
    mInputManager->start();
}

void QQtWavAudioManager::stopInput()
{
    mInputManager->stop();
}

void QQtWavAudioManager::startOutput()
{
    stopOutput();
    mOutputManager->start();
}

void QQtWavAudioManager::stopOutput()
{
    mOutputManager->stop();
}

QByteArray QQtWavAudioManager::readAll()
{
    return mInputDevice->readAll();
}

QByteArray QQtWavAudioManager::read ( qint64 maxlen )
{
    return mInputDevice->read ( maxlen );
}

void QQtWavAudioManager::write ( const QByteArray& bytes )
{
    mOutputDevice->write ( bytes );
}
