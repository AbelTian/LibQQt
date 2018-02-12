#include "qqtaudioeffect.h"

/*
 * 解析方法1 C语言
 */

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

__BEGIN_DECLS

typedef struct _wav_riff_t
{
    char id[5]; //ID:"RIFF"
    int size; //file_len - 8
    char type[5]; //type:"WAVE"
} wav_riff_t;


typedef struct _wav_format_t
{
    char id[5]; //ID:"fmt"
    int size;
    short compression_code;
    short channels;
    int samples_per_sec;
    int avg_bytes_per_sec;
    short block_align;
    short bits_per_sample;
} wav_format_t;


typedef struct _wav_fact_t
{
    char id[5];
    int size;
} wav_fact_t;


typedef struct _wav_data_t
{
    char id[5];
    int size;
} wav_data_t;


typedef struct _wav_t
{
    FILE* fp;
    wav_riff_t riff;
    wav_format_t format;
    wav_fact_t fact;
    wav_data_t data;
    int file_size;
    int data_offset;
    int data_size;
} wav_t;

wav_t* wav_open ( char* file_name );
void wav_close ( wav_t** wav );
void wav_rewind ( wav_t* wav );
int wav_over ( wav_t* wav );
int wav_read_data ( wav_t* wav, char* buffer, int buffer_size );
void wav_dump ( wav_t* wav );


__END_DECLS

/*
int strncasecmp ( char* s1, char* s2, register int n )
{
    while ( --n >= 0 && toupper ( ( unsigned char ) *s1 ) == toupper ( ( unsigned char ) *s2++ ) )
        if ( *s1++ == ' ' )
            return 0;

    return ( n < 0 ? 0 : toupper ( ( unsigned char ) * s1 ) - toupper ( ( unsigned char ) * --s2 ) );
}
*/

wav_t* wav_open ( char* file_name )
{
    wav_t* wav = NULL;
    char buffer[256];
    int read_len = 0;
    int offset = 0;


    if ( NULL == file_name )
    {
        printf ( "file_name is NULL\n" );
        return NULL;
    }

    wav = ( wav_t* ) malloc ( sizeof ( wav_t ) );

    if ( NULL == wav )
    {
        printf ( "malloc wav failedly\n" );
        return NULL;
    }

    memset ( wav, 0, sizeof ( wav_t ) );

    wav->fp = fopen ( file_name, "rb+" );

    if ( NULL == wav->fp )
    {
        printf ( "fopen %s failedly\n", file_name );
        free ( wav );
        return NULL;
    }

    //handle RIFF WAVE chunk
    read_len = fread ( buffer, 1, 12, wav->fp );

    if ( read_len < 12 )
    {
        printf ( "error wav file\n" );
        wav_close ( &wav );
        return NULL;
    }

    if ( strncasecmp ( "RIFF", buffer, 4 ) )
    {
        printf ( "error wav file\n" );
        wav_close ( &wav );
        return NULL;
    }

    memcpy ( wav->riff.id, buffer, 4 );
    wav->riff.size = * ( int* ) ( buffer + 4 );

    if ( strncasecmp ( "WAVE", buffer + 8, 4 ) )
    {
        printf ( "error wav file\n" );
        wav_close ( &wav );
        return NULL;
    }

    memcpy ( wav->riff.type, buffer + 8, 4 );

    wav->file_size = wav->riff.size + 8;
    offset += 12;

    while ( 1 )
    {
        char id_buffer[5] = {0};
        int tmp_size = 0;

        read_len = fread ( buffer, 1, 8, wav->fp );

        if ( read_len < 8 )
        {
            printf ( "error wav file\n" );
            wav_close ( &wav );
            return NULL;
        }

        memcpy ( id_buffer, buffer, 4 );
        tmp_size = * ( int* ) ( buffer + 4 );


        if ( 0 == strncasecmp ( "FMT", id_buffer, 3 ) )
        {
            memcpy ( wav->format.id, id_buffer, 3 );
            wav->format.size = tmp_size;
            read_len = fread ( buffer, 1, tmp_size, wav->fp );

            if ( read_len < tmp_size )
            {
                printf ( "error wav file\n" );
                wav_close ( &wav );
                return NULL;
            }

            wav->format.compression_code = * ( short* ) buffer;
            wav->format.channels = * ( short* ) ( buffer + 2 );
            wav->format.samples_per_sec = * ( int* ) ( buffer + 4 );
            wav->format.avg_bytes_per_sec = * ( int* ) ( buffer + 8 );
            wav->format.block_align = * ( short* ) ( buffer + 12 );
            wav->format.bits_per_sample = * ( short* ) ( buffer + 14 );
        }
        else if ( 0 == strncasecmp ( "DATA", id_buffer, 4 ) )
        {
            memcpy ( wav->data.id, id_buffer, 4 );
            wav->data.size = tmp_size;
            offset += 8;
            wav->data_offset = offset;
            wav->data_size = wav->data.size;
            break;
        }
        else
        {
            printf ( "unhandled chunk: %s, size: %d\n", id_buffer, tmp_size );
            fseek ( wav->fp, tmp_size, SEEK_CUR );
        }

        offset += 8 + tmp_size;
    }


    return wav;
}


void wav_close ( wav_t** wav )
{
    wav_t* tmp_wav;

    if ( NULL == wav )
    {
        return ;
    }


    tmp_wav = *wav;

    if ( NULL == tmp_wav )
    {
        return ;
    }


    if ( NULL != tmp_wav->fp )
    {
        fclose ( tmp_wav->fp );
    }

    free ( tmp_wav );


    *wav = NULL;
}


void wav_rewind ( wav_t* wav )
{
    if ( fseek ( wav->fp, wav->data_offset, SEEK_SET ) < 0 )
    {
        printf ( "wav rewind failedly\n" );
    }
}


int wav_over ( wav_t* wav )
{
    return feof ( wav->fp );
}


int wav_read_data ( wav_t* wav, char* buffer, int buffer_size )
{
    return fread ( buffer, 1, buffer_size, wav->fp );
}


void wav_dump ( wav_t* wav )
{
    printf ( "file length: %d\n", wav->file_size );


    printf ( "\nRIFF WAVE Chunk\n" );
    printf ( "id: %s\n", wav->riff.id );
    printf ( "size: %d\n", wav->riff.size );
    printf ( "type: %s\n", wav->riff.type );


    printf ( "\nFORMAT Chunk\n" );
    printf ( "id: %s\n", wav->format.id );
    printf ( "size: %d\n", wav->format.size );

    if ( wav->format.compression_code == 0 )
    {
        printf ( "compression: Unknown\n" );
    }
    else if ( wav->format.compression_code == 1 )
    {
        printf ( "compression: PCM/uncompressed\n" );
    }
    else if ( wav->format.compression_code == 2 )
    {
        printf ( "compression: Microsoft ADPCM\n" );
    }
    else if ( wav->format.compression_code == 6 )
    {
        printf ( "compression: ITU G.711 a-law\n" );
    }
    else if ( wav->format.compression_code == 7 )
    {
        printf ( "compression: ITU G.711 ?μ-law\n" );
    }
    else if ( wav->format.compression_code == 17 )
    {
        printf ( "compression: IMA ADPCM\n" );
    }
    else if ( wav->format.compression_code == 20 )
    {
        printf ( "compression: ITU G.723 ADPCM (Yamaha)\n" );
    }
    else if ( wav->format.compression_code == 49 )
    {
        printf ( "compression: GSM 6.10\n" );
    }
    else if ( wav->format.compression_code == 64 )
    {
        printf ( "compression: ITU G.721 ADPCM\n" );
    }
    else if ( wav->format.compression_code == 80 )
    {
        printf ( "compression: MPEG\n" );
    }
    else
    {
        printf ( "compression: Unknown\n" );
    }

    printf ( "channels: %d\n", wav->format.channels );
    printf ( "samples: %d\n", wav->format.samples_per_sec );
    printf ( "avg_bytes_per_sec: %d\n", wav->format.avg_bytes_per_sec );
    printf ( "block_align: %d\n", wav->format.block_align );
    printf ( "bits_per_sample: %d\n", wav->format.bits_per_sample );


    printf ( "\nDATA Chunk\n" );
    printf ( "id: %s\n", wav->data.id );
    printf ( "size: %d\n", wav->data.size );
    printf ( "data offset: %d\n", wav->data_offset );
}

/*
 * 解析方法2 使用QtFile接口，支持Qt资源文件
 */
// wav文件头信息结构
struct WAVFILEHEADER
{
    // RIFF 头;
    char RiffName[5];//RIFF
    unsigned int nRiffLength;//fileLen-8
    // 数据类型标识符;
    char WavName[5];//WAVE

    // 格式块中的块头;
    char FmtName[5];//fmt
    unsigned int nFmtLength;
    // 格式块中的块数据;
    unsigned short nAudioFormat;
    unsigned short nChannleNumber;
    unsigned int nSampleRate;
    unsigned int nBytesPerSecond;
    unsigned short nBlockAlign;
    unsigned short nBitsPerSample;

    // 附加信息(可选),根据 nFmtLength 来判断;
    // 扩展域大小;
    unsigned short nAppendMessage;

    //Fact块,可选字段，一般当wav文件由某些软件转化而成，则包含该Chunk;
    char FactName[5];
    unsigned int nFactLength;

    // DATA块，数据块中的块头;
    char    DATANAME[5];
    unsigned int   nDataLength;//fileDataSize

    // 以下是附加的一些计算信息;
    int fileDataSize;               // 文件音频数据大小;
    int fileHeaderSize;             // 文件头大小;
    int fileTailSize;               // 文件尾大小; 一般忽略。
    int fileTotalSize;              // 文件总大小;


    // 理论上应该将所有数据初始化，这里只初始化可选的数据;
    WAVFILEHEADER() {
        fileTailSize = 8;
        memset ( RiffName, 0, 5 );
        memset ( WavName, 0, 5 );
        memset ( FmtName, 0, 5 );
        memset ( FactName, 0, 5 );
    }

};

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
            pline() << "unhandled chunk" << tempName << tempSize;
            fileInfo.read ( tempSize );
            break;
        }
    }

    pline() << "filesize" << WavFileHeader.fileTotalSize;
    pline() << "fileheadersize" << WavFileHeader.fileHeaderSize;
    pline() << "filedatasize" << WavFileHeader.fileDataSize;
    pline() << "filetailsize" << WavFileHeader.fileTailSize;
    pline() << WavFileHeader.nChannleNumber << WavFileHeader.nSampleRate << WavFileHeader.nBitsPerSample;

    fileInfo.close();
}

QQtWavAudioEffect* QQtWavAudioEffect::msInstance = NULL;

QQtWavAudioEffect* QQtWavAudioEffect::Instance ( QObject* parent )
{
    if ( !msInstance )
        msInstance = new QQtWavAudioEffect ( parent );

    return msInstance;
}

QQtWavAudioEffect::QQtWavAudioEffect ( QObject* parent ) : QObject ( parent )
{
    mTimer = new QTimer ( this );
    connect ( mTimer, SIGNAL ( timeout() ), SLOT ( slotTimeout() ) );

    mVolume = 1;
}

void QQtWavAudioEffect::useDefaultOutputDevice()
{
    manager.outputDeviceInfo() = QQtAudioManager::defaultOutputDevice();
}

void QQtWavAudioEffect::useCustomOutputDevice ( const QAudioDeviceInfo& output )
{
    manager.outputDeviceInfo() = output;
}

void QQtWavAudioEffect::play ( QString localFile )
{
    //判断文件类型是否接受
    QMimeDatabase mimedb;
    QMimeType mimetype = mimedb.mimeTypeForFile ( localFile );
    pline() << "filename" << localFile << "mimetype" << mimetype.name()
            << QSoundEffect::supportedMimeTypes().contains ( mimetype.name(), Qt::CaseInsensitive ) ;

    if ( !QSoundEffect::supportedMimeTypes().contains ( mimetype.name(), Qt::CaseInsensitive ) )
    {
        pline() << "can't play file";
        return;
    }

    //判断音频具体格式
    //支持qrc文件
    bool ret = anlysisWavFileHeader ( localFile );
    //仅仅支持本地文件
    //bool ret = anlysisWavFileHeader_C ( localFile );

    if ( !ret )
    {
        pline() << "wav format parse fail";
        return;
    }

    //如果正在播放，先关闭写入音频数据流。
    mTimer->stop();
    manager.stopOutput();

    //读取到数据
    QFile f ( localFile );
    f.open ( QFile::ReadOnly );
    QByteArray b = f.read ( fileHeaderSize );
    pline() << b;
    mBytes = f.read ( fileDataSize );
    f.close();

    manager.outputAudioFormat() = mFormat;
    QAudioDeviceInfo& usingOutput = manager.outputDeviceInfo();

    //默认输出设备是否支持格式是否支持
    if ( !usingOutput.isFormatSupported ( mFormat ) )
    {
        //当前使用设备是否支持
        pline() << "output cant support" << mFormat;
        mFormat = usingOutput.nearestFormat ( mFormat ); //转换为最接近格式
    }

    pline() << "use format" << mFormat;

    manager.startOutput();
    //默认是静音的。
    manager.outputManager()->setVolume ( mVolume );

    //不响，音频输出设备接受顺序的间隔的输出，不接受一股脑输出。
    //manager.write ( bytes );
    //OK, 达到QSound效果。
    mTimer->start ( 10 );
}

void QQtWavAudioEffect::setVolume ( qreal volume )
{
    mVolume = volume;
    manager.outputManager()->setVolume ( mVolume );
}

void QQtWavAudioEffect::slotTimeout()
{
    //10ms 字节数
    //1s 字节数 = 采样率 * 采样深度（位宽）* 通道数 / 8
    int frameSize = mFormat.sampleRate() * mFormat.sampleSize() * mFormat.channelCount() / 8 / 100;
    QByteArray tempBytes;

    if ( mBytes.size() > frameSize )
    {
        tempBytes.resize ( frameSize );
    }
    else
    {
        tempBytes.resize ( mBytes.size() );
    }

    pline() << mBytes.size() << tempBytes.size() << frameSize;
    mBytes >> tempBytes;

    manager.write ( tempBytes );

    if ( mBytes.isEmpty() )
    {
        pline() << mBytes.size() << 0 << frameSize;
        mTimer->stop();
        manager.stopOutput();
    }

    return;

    QAudioOutput* audioOutput = manager.outputManager();
    QIODevice* streamOut = manager.outputDevice();

    if ( audioOutput && audioOutput->state() != QAudio::StoppedState &&
         audioOutput->state() != QAudio::SuspendedState )
    {
        int chunks = audioOutput->bytesFree() / audioOutput->periodSize();
        //1136 2048 无用的代码
        pline() << audioOutput->bytesFree() << audioOutput->periodSize();

        while ( chunks )
        {
            if ( tempBytes.length() >= audioOutput->periodSize() )
            {
                //写入到扬声器
                streamOut->write ( tempBytes.data(), audioOutput->periodSize() );
                tempBytes = tempBytes.mid ( audioOutput->periodSize() );
            }
            else
            {
                //写入到扬声器
                streamOut->write ( tempBytes );
                tempBytes.clear();
                break;
            }

            --chunks;
        }
    }


}

bool QQtWavAudioEffect::anlysisWavFileHeader_C ( QString localFile )
{
    wav_t* wav = NULL;
    wav = wav_open ( localFile.toLocal8Bit().data() );

    if ( !wav )
        return false;

    mFormat.setChannelCount ( wav->format.channels );
    mFormat.setSampleRate ( wav->format.samples_per_sec );
    mFormat.setSampleSize ( wav->format.bits_per_sample );
    mFormat.setByteOrder ( QAudioFormat::LittleEndian );
    mFormat.setCodec ( "audio/pcm" );
    mFormat.setSampleType ( QAudioFormat::SignedInt );

    fileTotalSize = wav->file_size;
    fileHeaderSize = wav->data_offset;
    fileDataSize = wav->data_size;
    fileTailSize = wav->file_size - wav->data_offset - wav->data_size;

    wav_dump ( wav );
    wav_close ( &wav );
    return true;

}

/*
 * 解析方法2 支援Qt 资源文件
 */
bool QQtWavAudioEffect::anlysisWavFileHeader ( QString fileName )
{
    WAVFILEHEADER WavFileHeader;
    bool ret = wavParse ( fileName, WavFileHeader );
    fileTotalSize = WavFileHeader.fileTotalSize;
    fileHeaderSize = WavFileHeader.fileHeaderSize;
    fileDataSize = WavFileHeader.fileDataSize;
    fileTailSize = WavFileHeader.fileTailSize;

    mFormat.setChannelCount ( WavFileHeader.nChannleNumber );
    mFormat.setSampleRate ( WavFileHeader.nSampleRate );
    mFormat.setSampleSize ( WavFileHeader.nBitsPerSample );
    mFormat.setByteOrder ( QAudioFormat::LittleEndian );
    mFormat.setCodec ( "audio/pcm" );
    mFormat.setSampleType ( QAudioFormat::SignedInt );
    return true;
}

void QQtWavAudio ( QString localFile )
{
    QQtWavAudioEffect::Instance ( )->play ( localFile );
}
