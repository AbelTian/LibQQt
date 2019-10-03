#ifndef QQTAUDIOMANAGER_H
#define QQTAUDIOMANAGER_H

#include <QObject>

#include <QAudioInput>
#include <QAudioOutput>

#include <QAudioDeviceInfo>
#include <QAudioFormat>

#if QT_VERSION > QT_VERSION_CHECK(5,0,0)
#include <QAudioInputSelectorControl>
#include <QAudioOutputSelectorControl>
#endif

#include <qqtcore.h>
#include <qqt-local.h>

//设计思路：QQtAudioManager两端是内存和声卡（输入输出差分可选的）设备，为内存服务。

/**
 * @brief The QQtAudioManager class
 * 为用户提供连接声卡的通道，一个Manager包括：输入选择，输出选择，输入读信号，输出函数。
 * 关于回听：打开输入，不开输出=QAudioInput，开输出增加QAudioOutput=回听。
 * 关于输出：可以按照Timer时序write音频数据帧Bytes到输出设备。
 * 关于输入：可以在readyRead里面接收到来自选定输入设备的音频帧。
 * 这个音频设备管理器目标为用户提供声卡输入端（音频输入设备）（拾音器）的音频数据帧，附加回听功能。（地位：封装层次）
 *
 * 处理声音三要点
 * 声音的格式 ，也就是声音三要素，输入一个、输出一个，manager对其分开管理，但是建议用户合并为一个置等。通道数、采样位宽、采样率
 * 声音设备 ，输入一个、输出一个，manager管理start\stop等接口，manager内部的inputManager和outputManager负责其他接口。
 * 声音设备的读写出入口 ，manager管理，包括可读信号和写入函数。
 *
 * 先确定输入、输出设备，
 * Qt提供建议格式，一般建议用户选择使用输出设备的建议格式，或者使用两个公共的格式。
 * 然后，读写设备即可。
 * manager把读写声音设备当做读写一个设备处理。支持本地声卡，蓝牙连接的声卡，hdmi接口上的声卡，其他接口上的声卡。只要系统显示的，一般都支持。
 *
 * *******使用QQtAudioManager，用户关注输入、输出设备的切换，和输入、输出格式的改变即可，其他的不必关注。*******
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
 *
 * ****Qt5.9.1在安卓上在关闭时会崩溃****
**/
class QQTSHARED_EXPORT QQtAudioManager : public QObject
{
    Q_OBJECT
public:
    explicit QQtAudioManager ( QObject* parent = nullptr );
    virtual ~QQtAudioManager();


    /**
     * 选择输入、输出设备
     */

    /*输入、输出音频设备列表，用于显示*/
    static QList<QAudioDeviceInfo> availableInputDevices();
    static QList<QAudioDeviceInfo> availableOutputDevices();
    /*当前正在使用的默认输入、输出设备的信息*/
    static QAudioDeviceInfo defaultInputDevice();
    static QAudioDeviceInfo defaultOutputDevice();

    /*Manager的输入、输出设备的信息，用于切换Manager使用的输入、输出设备*/
    /*读取和修改输入、输出设备。default为默认输入、输出设备*/
    QAudioDeviceInfo& inputDeviceInfo();
    QAudioDeviceInfo& outputDeviceInfo();


    /**
     * 选择音频流的格式
     */

    /*一般建议设置一个AudioFormat，然后这个format和设置的相等。default为preffered格式*/
    //这里保证输入、输出使用格式相等 或者 不同
    //如果格式不同，在mac电脑上本地输入输出设备是可以使用的，但是对于连接的语音蓝牙话筒，却是不可以使用的，原因未知。
    //格式相同的时候，实在是太好用啦。
    //这个建议默认就相同，但是，在QQtAudioManager当中，并没有直接将其相等处理，如果用户在readyRead槽函数里，可以更改采样率进行某些特殊处理。一般不需要差异处理的，相等就行了。
    QAudioFormat& inputAudioFormat ( void );
    QAudioFormat& outputAudioFormat ( void );


    /**
     * 操作输入、输出设备
     */

    /*对输入设备进行操作*/
    /*带输入形参的接口，和这个接口功能相同，忽略那个。*/
    void startInput();
    void stopInput();
    QByteArray readAll();
    QByteArray read ( qint64 maxlen );
    QAudioInput* inputManager();
    //输入设备流句柄，用于对其读取数据。和上边的read函数一样的效果。
    QIODevice* inputDevice();

    /*对输出设备进行操作*/
    void startOutput();
    void stopOutput();
    void write ( const QByteArray& bytes );
    QAudioOutput* outputManager();
    //输出设备流句柄，用于对其写入数据。和上边的write函数一样的效果。
    QIODevice* outputDevice();

    //这是个方便，操作默认输入、输出设备的开关
    //用上边的stop等函数关闭。
    //如果使用这个函数，建议：设置公共的AudioFormat，比如输出的format，或者输入、输出都支持的Format。
    //这个Format不会跟随默认设备的改变而改变，有初始值，但是用户在使用过程中，有必要关注和更改。
    //prefer和nearest并不是default，所以还是需要用户设置。
    //分开在输入、输出format里进行设置
    //QAudioFormat& defaultAudioFormat();
    void startDefaultInput();
    void startDefaultOutput();

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
