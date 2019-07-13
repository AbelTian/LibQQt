#include "libqwav.h"

#include <QFile>
#include <QDebug>

//header data tail
bool addWavHeader ( QIODevice& outputDevice, const QAudioFormat& format )
{
    // 开始设置WAV的文件头
    // 这里具体的数据代表什么含义请看上一篇文章（Qt之WAV文件解析）中对wav文件头的介绍
    WAVFILEHEADER WavFileHeader;
    qstrcpy ( WavFileHeader.RiffName, "RIFF" );
    qstrcpy ( WavFileHeader.WavName, "WAVE" );
    qstrcpy ( WavFileHeader.FmtName, "fmt " );
    qstrcpy ( WavFileHeader.DATANAME, "data" );

    // 表示 FMT块 的长度
    WavFileHeader.nFmtLength = 16;

    // 表示 按照PCM 编码;
    WavFileHeader.nAudioFormat = 1;
    // 声道数目;
    WavFileHeader.nChannleNumber = format.channelCount();
    // 采样频率;
    WavFileHeader.nSampleRate = format.sampleRate();
    //这个地方，int到unsinged int数据没有丢失。
    //pline() << WavFileHeader.nSampleRate << mFormat.sampleRate();
    // 每次采样得到的样本数据位数;
    WavFileHeader.nBitsPerSample = format.sampleSize();

    // nBytesPerSample 和 nBytesPerSecond这两个值通过设置的参数计算得到;
    // 数据块对齐单位(每个采样需要的字节数 = 通道数 × 每次采样得到的样本数据位数 / 8 )
    WavFileHeader.nBlockAlign = WavFileHeader.nChannleNumber * WavFileHeader.nBitsPerSample / 8;
    // 波形数据传输速率
    // (每秒平均字节数 = 采样频率 × 通道数 × 每次采样得到的样本数据位数 / 8  = 采样频率 × 每个采样需要的字节数 )
    WavFileHeader.nBytesPerSecond = WavFileHeader.nSampleRate * WavFileHeader.nChannleNumber *
                                    WavFileHeader.nBitsPerSample / 8;

    outputDevice.seek ( 0 );
    //riff 8 + 4
    WavFileHeader.nRiffLength = outputDevice.size() - 8;
    outputDevice.write ( WavFileHeader.RiffName, sizeof ( WavFileHeader.RiffName ) - 1 );
    outputDevice.write ( ( char* ) &WavFileHeader.nRiffLength, sizeof ( WavFileHeader.nRiffLength ) );
    outputDevice.write ( WavFileHeader.WavName, sizeof ( WavFileHeader.WavName )  - 1 );

    //fmt 8 + 16
    outputDevice.write ( WavFileHeader.FmtName, 4 );
    outputDevice.write ( ( char* ) &WavFileHeader.nFmtLength, 4 );

    outputDevice.write ( ( char* ) &WavFileHeader.nAudioFormat, sizeof ( WavFileHeader.nAudioFormat ) );
    outputDevice.write ( ( char* ) &WavFileHeader.nChannleNumber, sizeof ( WavFileHeader.nChannleNumber ) );
    outputDevice.write ( ( char* ) &WavFileHeader.nSampleRate, sizeof ( WavFileHeader.nSampleRate ) );
    outputDevice.write ( ( char* ) &WavFileHeader.nBytesPerSecond, sizeof ( WavFileHeader.nBytesPerSecond ) );
    outputDevice.write ( ( char* ) &WavFileHeader.nBlockAlign, sizeof ( WavFileHeader.nBlockAlign ) );
    outputDevice.write ( ( char* ) &WavFileHeader.nBitsPerSample, sizeof ( WavFileHeader.nBitsPerSample ) );

    //data 8
    outputDevice.write ( WavFileHeader.DATANAME, 4 );
    outputDevice.write ( ( char* ) &WavFileHeader.nDataLength, 4 );

    WavFileHeader.fileHeaderSize = outputDevice.pos();

    //44
    //int headerSize = WavFileHeader.fileHeaderSize;
    //qDebug() << headerSize;
    return true;
}

bool addWavTail ( QIODevice& outputDevice )
{
    QByteArray tailBytes;
    tailBytes += "q\xFCq\xFC";
    tailBytes += "a\xFB";
    tailBytes += "a\xFB";
    //8
    //pline() << tailBytes << tailBytes.size();
    outputDevice.write ( tailBytes );
    return true;
}


bool addWavDataBytes ( QIODevice& outputDevice, const QByteArray& bytes )
{
    outputDevice.write ( bytes );
    return true;
}

bool wavParse ( QString fileName, WAVFILEHEADER& WavFileHeader )
{
    QFile fileInfo ( fileName );

    if ( !fileInfo.open ( QIODevice::ReadOnly ) )
    {
        return false;
    }

    // 警告：每一次读，都不seek的！用户调用了seek不会引发pos变化，read会。

    // 读取 资源交换文件标志 "RIFF";
    fileInfo.read ( WavFileHeader.RiffName, sizeof ( WavFileHeader.RiffName ) - 1 );

    // 读取 RIFF 头后字节数;
    fileInfo.read ( ( char* ) &WavFileHeader.nRiffLength, sizeof ( WavFileHeader.nRiffLength ) );
    // 读取 波形文件标识符 "WAVE";
    fileInfo.read ( WavFileHeader.WavName, sizeof ( WavFileHeader.WavName )  - 1 );

    // 警告：每一次读，都不seek的！用户调用了seek不会引发pos变化，read会。
    while ( 1 )
    {
        char tempName[5] = {0};
        unsigned int tempSize = 0;

        fileInfo.read ( tempName, 4 );
        fileInfo.read ( ( char* ) &tempSize, 4 );

        QString strTempName ( tempName );

        if ( 0 == strTempName.compare ( "fmt ", Qt::CaseInsensitive ) )
        {
            strcpy ( WavFileHeader.FmtName, tempName );
            WavFileHeader.nFmtLength = tempSize;
            // 读取 格式种类;
            fileInfo.read ( ( char* ) &WavFileHeader.nAudioFormat, sizeof ( WavFileHeader.nAudioFormat ) );
            // 读取 音频通道数目;
            fileInfo.read ( ( char* ) &WavFileHeader.nChannleNumber, sizeof ( WavFileHeader.nChannleNumber ) );
            // 读取 采样频率;
            fileInfo.read ( ( char* ) &WavFileHeader.nSampleRate, sizeof ( WavFileHeader.nSampleRate ) );
            // 读取 波形数据传输速率;
            fileInfo.read ( ( char* ) &WavFileHeader.nBytesPerSecond, sizeof ( WavFileHeader.nBytesPerSecond ) );
            // 读取 数据块对齐单位;
            fileInfo.read ( ( char* ) &WavFileHeader.nBlockAlign, sizeof ( WavFileHeader.nBlockAlign ) );
            // 读取 每次采样得到的样本数据位数值;
            fileInfo.read ( ( char* ) &WavFileHeader.nBitsPerSample, sizeof ( WavFileHeader.nBitsPerSample ) );
            // 如果有扩展字节
            fileInfo.read ( tempSize - 16 );
        }
        else if ( 0 == strTempName.compare ( "fact", Qt::CaseInsensitive ) )
        {
            // 存在fact块,读取数据;
            strcpy ( WavFileHeader.FactName, tempName );
            // fact块长度;
            WavFileHeader.nFactLength = tempSize;
            // 读取fact块数据;但是不处理
            fileInfo.read ( tempSize );
            qDebug() << "fact data" << tempName << tempSize;
        }
        else if ( 0 == strTempName.compare ( "data", Qt::CaseInsensitive ) )
        {
            strcpy ( WavFileHeader.DATANAME, tempName );
            WavFileHeader.nDataLength = tempSize;

            // 读取 音频数据大小;
            WavFileHeader.fileDataSize = tempSize;
            //文件头大小;
            WavFileHeader.fileHeaderSize = fileInfo.pos();

            // 注意：这里的总大小，包括结尾8个字节，wav文件有8个结尾字节。"q\xFCq\xFC""a\xFB""a\xFB"
            // 文件总大小;
            WavFileHeader.fileTotalSize = WavFileHeader.nRiffLength + 8;

            break;
        }
        else
        {
            qDebug() << "unhandled chunk" << tempName << tempSize;
            fileInfo.read ( tempSize );
            break;
        }
    }

    //测试OK
    //    pline() << "filesize" << WavFileHeader.fileTotalSize;
    //    pline() << "fileheadersize" << WavFileHeader.fileHeaderSize;
    //    pline() << "filedatasize" << WavFileHeader.fileDataSize;
    //    pline() << "filetailsize" << WavFileHeader.fileTailSize;
    //    pline() << WavFileHeader.nChannleNumber << WavFileHeader.nSampleRate << WavFileHeader.nBitsPerSample;

    fileInfo.close();
}


/*
 * 解析方法2 支援Qt 资源文件
 */
bool anlysisWavFileHeader ( QString fileName, QAudioFormat& format, TWavFileInfo& fileinfo )
{
    WAVFILEHEADER WavFileHeader;
    bool ret = wavParse ( fileName, WavFileHeader );

    format.setChannelCount ( WavFileHeader.nChannleNumber );
    format.setSampleRate ( WavFileHeader.nSampleRate );
    format.setSampleSize ( WavFileHeader.nBitsPerSample );
    format.setByteOrder ( QAudioFormat::LittleEndian );
    format.setCodec ( "audio/pcm" );
    format.setSampleType ( QAudioFormat::SignedInt );

    fileinfo.fileTotalSize = WavFileHeader.fileTotalSize;
    fileinfo.fileHeaderSize = WavFileHeader.fileHeaderSize;
    fileinfo.fileDataSize = WavFileHeader.fileDataSize;
    fileinfo.fileTailSize = WavFileHeader.fileTailSize;
    return true;
}
