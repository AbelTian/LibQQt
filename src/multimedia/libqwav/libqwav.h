#ifndef LIBQWAV_H
#define LIBQWAV_H

#include "libqwav_global.h"

#include "string.h"
#include <QAudioFormat>
#include <QIODevice>

//dll __imp_ lib no __imp_
//跟这个extern没关系。
//动态导出、导入时就是有__imp_
//静态导出、导入时就是没有__imp_，导出的是函数原型。

//这个extern的作用是在导出库源文件是.c文件时，使用者必须使用extern "C"包含对应的头文件。
//就这么一个作用。

//#ifdef __cplusplus
//extern "C" {
//#endif

/*
 * 解析方法2 使用QtFile接口，支持Qt资源文件
 */
// wav文件头信息结构
struct WAVFILEHEADER
{
    // RIFF 头;
    char RiffName[5];//RIFF
    int nRiffLength;//fileLen-8
    // 数据类型标识符;
    char WavName[5];//WAVE

    // 格式块中的块头;
    char FmtName[5];//fmt
    int nFmtLength;
    // 格式块中的块数据;
    short nAudioFormat;
    short nChannleNumber;
    int nSampleRate;
    int nBytesPerSecond;
    short nBlockAlign;
    short nBitsPerSample;

    // 附加信息(可选),根据 nFmtLength 来判断;
    // 扩展域大小;
    short nAppendMessage;

    //Fact块,可选字段，一般当wav文件由某些软件转化而成，则包含该Chunk;
    char FactName[5];
    int nFactLength;

    // DATA块，数据块中的块头;
    char    DATANAME[5];
    int   nDataLength;//fileDataSize

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

//44 固定的
LIBQWAVSHARED_EXPORT bool addWavHeader ( QIODevice& outputDevice, const QAudioFormat& format );
//8 固定的
LIBQWAVSHARED_EXPORT bool addWavTail ( QIODevice& outputDevice );
LIBQWAVSHARED_EXPORT bool addWavDataBytes ( QIODevice& outputDevice, const QByteArray& bytes );


typedef struct _TWavFileInfo
{
    int fileDataSize;               // 文件音频数据大小;
    int fileHeaderSize;             // 文件头大小;
    int fileTailSize;               // 文件尾大小; 一般忽略。
    int fileTotalSize;              // 文件总大小;
} TWavFileInfo;


LIBQWAVSHARED_EXPORT bool wavParse ( QString fileName, WAVFILEHEADER& WavFileHeader );
LIBQWAVSHARED_EXPORT bool anlysisWavFileHeader ( QString fileName, QAudioFormat& format, TWavFileInfo& fileinfo );

//#ifdef __cplusplus
//}
//#endif

#endif // LIBQWAV_H
