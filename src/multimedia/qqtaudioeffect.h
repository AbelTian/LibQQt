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

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

/**
 * @brief The QQtAudioEffect class
 * QSound、QSoundEffect是不能指定输出设备的。
 * 用于播放音效文件，接受指定输出设备。
 * 请不要用来播放大文件
 * 尝试用QQt的，需要切掉wav文件的44头。
 * 尝试用QAudioDecoder，解码器不支持x-wav，defaultServiceProvider::requestService(): no service found for - "org.qt-project.qt.audiodecode"
 * 为什么QSoundEffect支持那么多wav格式？("audio/x-wav", "audio/wav", "audio/wave", "audio/x-pn-wav")
 * QAudioDecoder保存了一个提交，#5643241
 * QWavAudioEffect保存了一个提交，#5f43622
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

/*
 * Qt 中有一个 QBuffer 类，可以将 QByteArray 包装成一个 QIODevice。QMemBuffer
 * inputFile->isReadable() 一直都是 false 状态。原因是没在 open 函数中调用 QIODevice::open(mode)
 * 要解析wav，用自定义程序，还是用开源Library（libsndfile）？
 * 要播放wav，是用wav的音频格式来设定输出设备，还是用个输出设备支持的音频格式，wav里选取进行使用？
 * 如果来的是个QByteArray，那么，用QBuffer封装，
 */
class QQTSHARED_EXPORT QQtWavAudioEffect : public QObject
{
    Q_OBJECT

public:
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
        //bool ret = anlysisWavFileHeader_C ( localFile );

        if ( !ret ) {
            pline() << "wav format parse fail";
            return;
        }

        //默认输出设备是否支持格式是否支持
        if ( !manager.defaultOutputDevice().isFormatSupported ( mFormat ) ) {
            //当前使用设备是否支持
            pline() << "output cant support" << mFormat;
            mFormat = manager.defaultOutputDevice().nearestFormat ( mFormat ); //转换为最接近格式
        }

        pline() << "use format" << mFormat;

        //读取到数据
        QByteArray bytes;
        QFile f ( localFile );
        f.open ( QFile::ReadOnly );
        f.seek ( 52 );
        bytes = f.readAll();
        f.close();


        //使用默认设备
        manager.outputAudioFormat() = mFormat;
        manager.startDefaultOutput();

        /*
        QTimer* timer = new QTimer ( this );
        connect ( timer, &QTimer::timeout, [&]() {
            static int i = 52;
            int frameSize = mFormat.sampleRate() * mFormat.sampleSize() * mFormat.channelCount() / 8 / 100;
            QByteArray bytes;
            QFile f ( localFile );
            f.open ( QFile::ReadOnly );
            f.seek ( i );
            bytes = f.read ( frameSize );
            f.close();
            manager.write ( bytes );
            i += frameSize;
            pline() << i;
        } );
        timer->start();
        */
    }

    //需要用户设置输出设备
    void customPlay ( QString localFile );

signals:

public slots:

private slots:
private:
    QAudioFormat mFormat;
    QQtAudioManager manager;

public:

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

protected:
    /*
    int strncasecmp ( char* s1, char* s2, register int n )
    {
        while ( --n >= 0 && toupper ( ( unsigned char ) *s1 ) == toupper ( ( unsigned char ) *s2++ ) )
            if ( *s1++ == ' ' )
                return 0;

        return ( n < 0 ? 0 : toupper ( ( unsigned char ) * s1 ) - toupper ( ( unsigned char ) * --s2 ) );
    }
    */

    wav_t* wav_open ( char* file_name ) {
        wav_t* wav = NULL;
        char buffer[256];
        int read_len = 0;
        int offset = 0;


        if ( NULL == file_name ) {
            printf ( "file_name is NULL\n" );
            return NULL;
        }

        wav = ( wav_t* ) malloc ( sizeof ( wav_t ) );

        if ( NULL == wav ) {
            printf ( "malloc wav failedly\n" );
            return NULL;
        }

        memset ( wav, 0, sizeof ( wav_t ) );

        wav->fp = fopen ( file_name, "rb+" );

        if ( NULL == wav->fp ) {
            printf ( "fopen %s failedly\n", file_name );
            free ( wav );
            return NULL;
        }

        //handle RIFF WAVE chunk
        read_len = fread ( buffer, 1, 12, wav->fp );

        if ( read_len < 12 ) {
            printf ( "error wav file\n" );
            wav_close ( &wav );
            return NULL;
        }

        if ( strncasecmp ( "RIFF", buffer, 4 ) ) {
            printf ( "error wav file\n" );
            wav_close ( &wav );
            return NULL;
        }

        memcpy ( wav->riff.id, buffer, 4 );
        wav->riff.size = * ( int* ) ( buffer + 4 );

        if ( strncasecmp ( "WAVE", buffer + 8, 4 ) ) {
            printf ( "error wav file\n" );
            wav_close ( &wav );
            return NULL;
        }

        memcpy ( wav->riff.type, buffer + 8, 4 );
        wav->file_size = wav->riff.size + 8;
        offset += 12;

        while ( 1 ) {
            char id_buffer[5] = {0};
            int tmp_size = 0;

            read_len = fread ( buffer, 1, 8, wav->fp );

            if ( read_len < 8 ) {
                printf ( "error wav file\n" );
                wav_close ( &wav );
                return NULL;
            }

            memcpy ( id_buffer, buffer, 4 );
            tmp_size = * ( int* ) ( buffer + 4 );


            if ( 0 == strncasecmp ( "FMT", id_buffer, 3 ) ) {
                memcpy ( wav->format.id, id_buffer, 3 );
                wav->format.size = tmp_size;
                read_len = fread ( buffer, 1, tmp_size, wav->fp );

                if ( read_len < tmp_size ) {
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
            else if ( 0 == strncasecmp ( "DATA", id_buffer, 4 ) ) {
                memcpy ( wav->data.id, id_buffer, 4 );
                wav->data.size = tmp_size;
                offset += 8;
                wav->data_offset = offset;
                wav->data_size = wav->data.size;
                break;
            }
            else {
                printf ( "unhandled chunk: %s, size: %d\n", id_buffer, tmp_size );
                fseek ( wav->fp, tmp_size, SEEK_CUR );
            }

            offset += 8 + tmp_size;
        }


        return wav;
    }


    void wav_close ( wav_t** wav ) {
        wav_t* tmp_wav;

        if ( NULL == wav ) {
            return ;
        }


        tmp_wav = *wav;

        if ( NULL == tmp_wav ) {
            return ;
        }


        if ( NULL != tmp_wav->fp ) {
            fclose ( tmp_wav->fp );
        }

        free ( tmp_wav );


        *wav = NULL;
    }


    void wav_rewind ( wav_t* wav ) {
        if ( fseek ( wav->fp, wav->data_offset, SEEK_SET ) < 0 ) {
            printf ( "wav rewind failedly\n" );
        }
    }


    int wav_over ( wav_t* wav ) {
        return feof ( wav->fp );
    }


    int wav_read_data ( wav_t* wav, char* buffer, int buffer_size ) {
        return fread ( buffer, 1, buffer_size, wav->fp );
    }


    void wav_dump ( wav_t* wav ) {
        printf ( "file length: %d\n", wav->file_size );


        printf ( "\nRIFF WAVE Chunk\n" );
        printf ( "id: %s\n", wav->riff.id );
        printf ( "size: %d\n", wav->riff.size );
        printf ( "type: %s\n", wav->riff.type );


        printf ( "\nFORMAT Chunk\n" );
        printf ( "id: %s\n", wav->format.id );
        printf ( "size: %d\n", wav->format.size );

        if ( wav->format.compression_code == 0 ) {
            printf ( "compression: Unknown\n" );
        }
        else if ( wav->format.compression_code == 1 ) {
            printf ( "compression: PCM/uncompressed\n" );
        }
        else if ( wav->format.compression_code == 2 ) {
            printf ( "compression: Microsoft ADPCM\n" );
        }
        else if ( wav->format.compression_code == 6 ) {
            printf ( "compression: ITU G.711 a-law\n" );
        }
        else if ( wav->format.compression_code == 7 ) {
            printf ( "compression: ITU G.711 ?μ-law\n" );
        }
        else if ( wav->format.compression_code == 17 ) {
            printf ( "compression: IMA ADPCM\n" );
        }
        else if ( wav->format.compression_code == 20 ) {
            printf ( "compression: ITU G.723 ADPCM (Yamaha)\n" );
        }
        else if ( wav->format.compression_code == 49 ) {
            printf ( "compression: GSM 6.10\n" );
        }
        else if ( wav->format.compression_code == 64 ) {
            printf ( "compression: ITU G.721 ADPCM\n" );
        }
        else if ( wav->format.compression_code == 80 ) {
            printf ( "compression: MPEG\n" );
        }
        else {
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

    bool anlysisWavFileHeader_C ( QString localFile ) {
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

        wav_close ( &wav );
        return true;

    }

public:
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
        unsigned short nBytesPerSample;
        unsigned short nBitsPerSample;

        // 附加信息(可选),根据 nFmtLength 来判断;
        // 扩展域大小;
        unsigned short nAppendMessage;
        // 扩展域信息;
        char* AppendMessageData;

        //Fact块,可选字段，一般当wav文件由某些软件转化而成，则包含该Chunk;
        char FactName[5];
        unsigned int nFactLength;

        // DATA块，数据块中的块头;
        char    DATANAME[5];
        unsigned int   nDataLength;//fileDataSize
        // 以下是附加的一些计算信息;
        int fileDataSize;               // 文件音频数据大小;
        int fileHeaderSize;             // 文件头大小;
        int fileTotalSize;              // 文件总大小;


        // 理论上应该将所有数据初始化，这里只初始化可选的数据;
        WAVFILEHEADER() {
            nAppendMessage = 0;
            AppendMessageData = NULL;
            memset ( RiffName, 0, 5 );
            memset ( WavName, 0, 5 );
            memset ( FmtName, 0, 5 );
            memset ( FactName, 0, 5 );
            nFactLength = 0;
        }

    };

protected:

    // 解析wav文件的头信息;
    bool anlysisWavFileHeader ( QString fileName ) {
        QFile fileInfo ( fileName );

        if ( !fileInfo.open ( QIODevice::ReadOnly ) ) {
            return false;
        }

        WAVFILEHEADER WavFileHeader;

        // 读取 资源交换文件标志 "RIFF";
        fileInfo.read ( WavFileHeader.RiffName, sizeof ( WavFileHeader.RiffName ) - 1 );

        // 读取 RIFF 头后字节数;
        fileInfo.read ( ( char* ) &WavFileHeader.nRiffLength, sizeof ( WavFileHeader.nRiffLength ) );
        // 读取 波形文件标识符 "WAVE";
        fileInfo.read ( WavFileHeader.WavName, sizeof ( WavFileHeader.WavName )  - 1 );

        while ( 1 ) {
            char tempName[5] = {0};
            unsigned int tempSize = 0;

            fileInfo.read ( tempName, 4 );
            fileInfo.read ( ( char* ) &tempSize, 4 );

            QString strTempName ( tempName );

            if ( 0 == strTempName.compare ( "fmt ", Qt::CaseInsensitive ) ) {
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
                fileInfo.read ( ( char* ) &WavFileHeader.nBytesPerSample, sizeof ( WavFileHeader.nBytesPerSample ) );
                // 读取 每次采样得到的样本数据位数值;
                fileInfo.read ( ( char* ) &WavFileHeader.nBitsPerSample, sizeof ( WavFileHeader.nBitsPerSample ) );
            }
            else if ( 0 == strTempName.compare ( "fact", Qt::CaseInsensitive ) ) {
                // 存在fact块,读取数据;
                strcpy ( WavFileHeader.FactName, tempName );
                // fact块长度;
                WavFileHeader.nFactLength = tempSize;
                // 读取fact块数据;但是不处理
                fileInfo.read ( tempSize );
            }
            else if ( 0 == strTempName.compare ( "data", Qt::CaseInsensitive ) ) {
                strcpy ( WavFileHeader.DATANAME, tempName );
                WavFileHeader.nDataLength = tempSize;

                // 文件总大小;
                WavFileHeader.fileTotalSize = WavFileHeader.nRiffLength + 8;
                // 读取 音频数据大小;
                WavFileHeader.fileDataSize = tempSize;
                //文件头大小;
                WavFileHeader.fileHeaderSize = WavFileHeader.fileTotalSize - WavFileHeader.fileDataSize;

//                pline() << "filesize" << WavFileHeader.fileTotalSize;
//                pline() << "fileheadersize" << WavFileHeader.fileHeaderSize;
//                pline() << "filedatasize" << WavFileHeader.fileDataSize;

                break;
            }
            else {
                pline() << "unhandled chunk" << tempName << tempSize;
                fileInfo.read ( tempSize );
            }
        }

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

};

#endif // QQTAUDIOEFFECT_H
