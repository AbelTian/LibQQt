#ifndef QQTAUDIOEFFECT_H
#define QQTAUDIOEFFECT_H

#include <qqtaudiomanager.h>
#include <qqtcore.h>
#include <qqt-local.h>

#include <QMimeType>
#include <QMimeData>
#include <QMimeDatabase>

#include <QSound>
#include <QSoundEffect>

/**
 * @brief The QQtAudioEffect class
 * QSound、QSoundEffect是不能指定输出设备的。
 * 用于播放音效文件，接受指定输出设备。
 * 请不要用来播放大文件
 * 尝试用QQt的，需要切掉wav文件的44头。
 * 尝试用QAudioDecoder，解码器不支持x-wav，defaultServiceProvider::requestService(): no service found for - "org.qt-project.qt.audiodecode"
 * 为什么QSoundEffect支持那么多wav格式？("audio/x-wav", "audio/wav", "audio/wave", "audio/x-pn-wav")
 * QAudioDecoder保存了一个提交，#100644
 * 现在更新为用QQt的，QQtAudioEffect目标支持多种格式的音效文件。
 */
class QQTSHARED_EXPORT QQtAudioEffect : public QQtAudioManager
{
    Q_OBJECT
public:
    explicit QQtAudioEffect ( QObject* parent = nullptr ) ;

    void play ( QString localFile );
    //需要用户设置输出设备
    void customPlay ( QString localFile );

signals:

public slots:

private slots:

private:
};

class QQTSHARED_EXPORT QQtWavAudioEffect : public QObject
{
    Q_OBJECT
public:
    // wav文件头信息结构
    struct WAVFILEHEADER
    {
        // RIFF 头;
        char RiffName[4];
        unsigned long nRiffLength;

        // 数据类型标识符;
        char WavName[4];

        // 格式块中的块头;
        char FmtName[4];
        unsigned long nFmtLength;

        // 格式块中的块数据;
        unsigned short nAudioFormat;
        unsigned short nChannleNumber;
        unsigned long nSampleRate;
        unsigned long nBytesPerSecond;
        unsigned short nBytesPerSample;
        unsigned short nBitsPerSample;

        // 附加信息(可选),根据 nFmtLength 来判断;
        // 扩展域大小;
        unsigned short nAppendMessage;
        // 扩展域信息;
        char* AppendMessageData;

        //Fact块,可选字段，一般当wav文件由某些软件转化而成，则包含该Chunk;
        char FactName[4];
        unsigned long nFactLength;
        char FactData[4];

        // 数据块中的块头;
        char    DATANAME[4];
        unsigned long   nDataLength;

        // 以下是附加的一些计算信息;
        int fileDataSize;               // 文件音频数据大小;
        int fileHeaderSize;             // 文件头大小;
        int fileTotalSize;              // 文件总大小;


        // 理论上应该将所有数据初始化，这里只初始化可选的数据;
        WAVFILEHEADER() {
            nAppendMessage = 0;
            AppendMessageData = NULL;
            strcpy ( FactName, "" );
            nFactLength = 0;
            strcpy ( FactData, "" );
        }

    };

    explicit QQtWavAudioEffect ( QObject* parent = nullptr ) : QObject ( parent ) {

    }

    void play ( QString localFile ) {
        //判断文件类型是否接受
        QMimeDatabase mimedb;
        QMimeType mimetype = mimedb.mimeTypeForFile ( localFile );
        pline() << "filename" << localFile << "mimetype" << mimetype.name()
                << QSoundEffect::supportedMimeTypes().contains ( mimetype.name(), Qt::CaseInsensitive ) ;

        if ( !QSoundEffect::supportedMimeTypes().contains ( mimetype.name(), Qt::CaseInsensitive ) ) {
            pline() << "can't play file";
            return;
        }

        //判断音频具体格式
        bool ret = anlysisWavFileHeader ( localFile );

        if ( !ret ) {
            pline() << "wav parse fail";
            return;
        }

        //默认输出设备是否支持格式是否支持
        pline() << mFormat;

        if ( !manager.defaultOutputDevice().isFormatSupported ( mFormat ) ) {
            //当前使用设备是否支持
            pline() << "output cant support" << mFormat;
            mFormat = manager.defaultOutputDevice().nearestFormat ( mFormat ); //转换为最接近格式
            pline() << "use format" << mFormat;
        }

        //读取到数据
        QByteArray bytes;
        QFile f ( localFile );
        f.open ( QFile::ReadOnly );
        bytes = f.readAll();
        f.close();

        //使用默认设备
        manager.outputAudioFormat() = mFormat;
        manager.startDefaultOutput();
        manager.writeBytes ( bytes );
    }

    //需要用户设置输出设备
    void customPlay ( QString localFile );

signals:

public slots:

private slots:
protected:
    // 解析wav文件的头信息;
    bool anlysisWavFileHeader ( QString fileName ) {
        QFile fileInfo ( fileName );

        if ( !fileInfo.open ( QIODevice::ReadOnly ) ) {
            return false;
        }

        // 读取 资源交换文件标志 "RIFF";
        fileInfo.read ( WavFileHeader.RiffName, sizeof ( WavFileHeader.RiffName ) );

        // 读取 RIFF 头后字节数;
        fileInfo.read ( ( char* ) &WavFileHeader.nRiffLength, sizeof ( WavFileHeader.nRiffLength ) );
        // 读取 波形文件标识符 "WAVE";
        fileInfo.read ( WavFileHeader.WavName, sizeof ( WavFileHeader.WavName ) );

        // 读取 波形格式标志 "fmt ";
        fileInfo.read ( WavFileHeader.FmtName, sizeof ( WavFileHeader.FmtName ) );

        // 读取 格式块中块数据大小;
        fileInfo.read ( ( char* ) &WavFileHeader.nFmtLength, sizeof ( WavFileHeader.nFmtLength ) );

        // 读取 格式种类;
        fileInfo.read ( ( char* ) &WavFileHeader.nAudioFormat, sizeof ( WavFileHeader.nAudioFormat ) );

        // 读取 音频通道数目;
        fileInfo.read ( ( char* ) &WavFileHeader.nChannleNumber, sizeof ( WavFileHeader.nChannleNumber ) );

        // 读取 采样频率;
        fileInfo.read ( ( char* ) &WavFileHeader.nSampleRate, sizeof ( WavFileHeader.nSampleRate ) );

        // 读取 波形数据传输速率;
        fileInfo.read ( ( char* ) &WavFileHeader.nBytesPerSecond, sizeof ( WavFileHeader.nBytesPerSecond ) );

        // 读取 数据块对齐单位;
        fileInfo.read ( ( char* ) &WavFileHeader.nBytesPerSample, sizeof ( WavFileHeader.nBytesPerSample ) );

        // 读取 每次采样得到的样本数据位数值;
        fileInfo.read ( ( char* ) &WavFileHeader.nBitsPerSample, sizeof ( WavFileHeader.nBitsPerSample ) );

        // 根据格式块中块数据大小，判断是否有附加信息;
        QString strAppendMessageData;           // 保存扩展域中的扩展信息;

        if ( WavFileHeader.nFmtLength >= 18 ) {
            // 读取附加信息占两个字节;
            fileInfo.read ( ( char* ) &WavFileHeader.nAppendMessage, sizeof ( WavFileHeader.nAppendMessage ) );
            // 这里 特别注意 nFmtLength 一般情况下是 16 或者18 ，但是有一个wav文件 nFmtLength 为50;
            // 说明我们读取完fmt格式块后面有附加信息，上面一行代码读取了两个字节数据
            // 这两个字节即为扩展域的大小，而剩余的 50 - 18 = 32字节即为扩展域中的扩展信息;
            // 对于扩展域中保存了什么格式的数据暂时无法得知，先用char型数组保存;
            // 这里 扩展域大小 可以通过 WavFileHeader.nAppendMessage （从文件中读取的扩展域大小） 也可以通过 nFmtLength（格式块长度） - 18 得到;
            int appendMessageLength = WavFileHeader.nFmtLength - 18;
            WavFileHeader.AppendMessageData = new char[appendMessageLength];
            fileInfo.read ( WavFileHeader.AppendMessageData, appendMessageLength );
            // 这里也可以在末尾加字符结束符查看数据,但是现在不确定扩展信息的具体格式;
            //WavFileHeader.AppendMessageData[appendMessageLength] = '\0';
            // 转成QString 查看扩展信息数据;
            strAppendMessageData = QString ( WavFileHeader.AppendMessageData );
        }

        // 由于Fact块为可选，可能存在，所以需要判断;
        char chunkName[5];
        fileInfo.read ( chunkName, sizeof ( chunkName ) - 1 );
        // 需要加上字符结束符 '\0'，否则转成QString会出错，通过strlen来计算chunkName的字符长度也会出错。
        chunkName[4] = '\0';
        QString strChunkName ( chunkName );

        if ( strChunkName.compare ( "fact" ) == 0 ) {
            // 存在fact块,读取数据;
            strcpy ( WavFileHeader.FactName, chunkName );
            // 读取fact块长度;
            fileInfo.read ( ( char* ) &WavFileHeader.nFactLength, sizeof ( WavFileHeader.nFactLength ) );
            // 读取fact块数据;
            fileInfo.read ( WavFileHeader.FactData, sizeof ( WavFileHeader.FactData ) );

            // 存在Fact块 , 读取 数据块标识符;
            fileInfo.read ( WavFileHeader.DATANAME, sizeof ( WavFileHeader.DATANAME ) );
        }
        else {
            // 不存在Fact块，直接赋值;
            strcpy ( WavFileHeader.DATANAME, chunkName );
        }


        // 读取 数据块大小;
        fileInfo.read ( ( char* ) &WavFileHeader.nDataLength, sizeof ( WavFileHeader.nDataLength ) );

        // 读取 音频数据大小;
        WavFileHeader.fileDataSize = fileInfo.readAll().size();

        // 文件总大小;
        WavFileHeader.fileTotalSize = WavFileHeader.nRiffLength + 8;

        //文件头大小;
        WavFileHeader.fileHeaderSize = WavFileHeader.fileTotalSize - WavFileHeader.fileDataSize;

        fileInfo.close();

        pline() << WavFileHeader.nChannleNumber << WavFileHeader.nSampleRate << WavFileHeader.nBitsPerSample;
        mFormat.setChannelCount ( WavFileHeader.nChannleNumber );
        mFormat.setSampleRate ( WavFileHeader.nSampleRate );
        mFormat.setSampleSize ( WavFileHeader.nBitsPerSample );
        mFormat.setByteOrder ( QAudioFormat::LittleEndian );
        mFormat.setCodec ( "audio/pcm" );
        mFormat.setSampleType ( QAudioFormat::SignedInt );
        return true;
    }
private:
    WAVFILEHEADER WavFileHeader;
    QAudioFormat mFormat;
    QQtAudioManager manager;
};

#if 0

/*
 * Qt 中有一个 QBuffer 类，可以将 QByteArray 包装成一个 QIODevice。
 * inputFile->isReadable() 一直都是 false 状态。原因是刚开始我们没在 open 函数中调用 QIODevice::open(mode)
 * 要解析wav，用自定义程序，还是用开源Library（libsndfile）？
 * 要播放wav，是用wav的音频格式来设定输出设备，还是用个输出设备支持的音频格式，wav里选取进行使用？
 * 如果来的是个QByteArray，那么，用QBuffer封装，
 */
class QQTSHARED_EXPORT QQtWavFile : public QFile
{
    //依赖 Q_OBJECT
    Q_OBJECT
public:

public:
    explicit QQtWavFile ( QObject* parent = nullptr ) {

    }

    QAudioFormat format();
    void setUserFormat ( const QAudioFormat& userFormat );

protected:
    qint64 readData ( QByteArray& bytes ) ;
    qint64 writeData ( const QByteArray& bytes );
private:
    QString mFileName;
signals:

public slots:

private slots:

private:
    //默认情况下，UserForamt=DefaultFormat，但是，输出格式改变，将更改UserFormat，DefaultFormat还是文件的音频格式。
    //UserFormat将影响读取数据的内容格式。
    QAudioFormat mUserFormat;
};

class QQTSHARED_EXPORT QQtPCMDevice : public QIODevice
{
    Q_OBJECT
public:
    explicit QQtPCMDevice ( QObject* parent = nullptr ) {

    }

signals:

public slots:

private slots:

};
#endif

#endif // QQTAUDIOEFFECT_H
