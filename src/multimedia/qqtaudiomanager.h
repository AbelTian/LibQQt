#ifndef QQTAUDIOMANAGER_H
#define QQTAUDIOMANAGER_H

#include <QObject>

#include <QAudioInput>
#include <QAudioOutput>

#include <QAudioDeviceInfo>
#include <QAudioFormat>

#include <QAudioInputSelectorControl>
#include <QAudioOutputSelectorControl>

/**
 * @brief The QQtAudioManager class
 * 为用户提供连接声卡的通道，一个connection包括：输入选择，输出选择，输入信号，输出函数。
 *
 * 原理：
 * 声音三要素： 采样率， 量化精度， 声道
 * 通常我们用一位二进制表示两种状态， 如1表示高电平， 0表示低电平。在音频领域里，如只用一位二进制表示声音，那么只能表示发声和不发声两种状态（蜂鸣器）。
 * 如果使用过音频分析软件会发现，声音是由连续的不规则的波形来表示， 根本不可能用一位二进制数据表示一个人发出的声音。但可以用多位二进制的数据来表示(音频里通常是用8位或者16位). 如用8位数据表示 0 -- 20KHz:  0xff可表示20KHz,  0xfe表示19.92KHz, 0xfc表示19.84KHz ....
 * 把声音经过测量转换成多位的二进制数据就是在计算机系统里存储的原始声音数据(也叫pcm数据)， 数据的位数就是量化精度。通常是8位/16位
 *
 * 采样率就是声音转换成二进制数据的频率，常用的采样率有：  8000, 11025, 22050, 44100, 48000 从声音的还原角度来说采样率越高，质量就越好。
 *
 * 声音就是表示声音源的通道。嵌入式系统里通常是单声道/双声道. CD唱片通常是发烧友所用的，片中没有图像。而一张蝶片有650M左右，为什么只有十多首歌曲？
 * 算一算：
 * 高保真肯定是用最高的采样率48000, 量化精度16位(2字节)， 立体声2声道. 一首歌通常200秒
 * 48000 * 2 * 2 * 200 = 38400000字节,  大概38M一首歌曲
**/

#include <qqtcore.h>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtAudioManager : public QObject
{
    Q_OBJECT
public:
    explicit QQtAudioManager ( QObject* parent = nullptr );
    ~QQtAudioManager();

    /*输入、输出音频设备列表，用于显示*/
    static QList<QAudioDeviceInfo> availableInputDevices();
    static QList<QAudioDeviceInfo> availableOutputDevices();
    static QAudioDeviceInfo defaultInputDevice();
    static QAudioDeviceInfo defaultOutputDevice();

    /*一般建议设置一个AudioFormat，然后这个format和设置的相等。default为preffered格式*/
    QAudioFormat& inputAudioFormat ( void );
    QAudioFormat& outputAudioFormat ( void );

    /*读取和修改输入、输出设备。default为默认输入、输出设备*/
    QAudioDeviceInfo& inputDeviceInfo();
    QAudioDeviceInfo& outputDeviceInfo();

    /*对输入设备进行操作*/
    void startInput();
    void stopInput();
    QByteArray readStreamBytes();
    QAudioInput* inputManager();
    QIODevice* inputDevice();

    /*对输出设备进行操作*/
    void startOutput();
    void stopOutput();
    void writeStreamBytes ( QByteArray& bytes );
    QAudioOutput* outputManager();
    QIODevice* outputDevice();

signals:
    /*输入音频数据准备就绪，readAll即可读取。*/
    void readyRead();

public slots:

private:
    QAudioFormat mInputAudioFormat;
    QAudioFormat mOutputAudioFormat;

    /*保存输入、输出设备信息，采样率、声道、位宽*/
    QAudioDeviceInfo mInputDeviceInfo;
    QAudioDeviceInfo mOutputDeviceInfo;

    /*操作输入、输出设备的工具*/
    QAudioInput* mInputManager;
    QAudioOutput* mOutputManager;
    /*读写输入、输出设备的流控制器，QIODevice*/
    QIODevice* mInputDevice;
    QIODevice* mOutputDevice;

};

#endif // QQTAUDIOMANAGER_H
