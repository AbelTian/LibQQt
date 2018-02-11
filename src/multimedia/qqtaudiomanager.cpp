#include "qqtaudiomanager.h"

QQtAudioManager::QQtAudioManager ( QObject* parent ) : QObject ( parent )
{
    mInputAudioFormat = defaultInputDevice().preferredFormat();
    mOutputAudioFormat = defaultOutputDevice().preferredFormat();

    mInputDeviceInfo = defaultInputDevice();
    mOutputDeviceInfo = defaultOutputDevice();

    mInputDevice = NULL;
    mOutputDevice = NULL;

    mInputManager = NULL;
    mOutputManager = NULL;
}

QQtAudioManager::~QQtAudioManager()
{
    stopInput();
    stopOutput();
}

QList<QAudioDeviceInfo> QQtAudioManager::availableInputDevices() { return QAudioDeviceInfo::availableDevices ( QAudio::AudioInput ); }

QList<QAudioDeviceInfo> QQtAudioManager::availableOutputDevices() { return QAudioDeviceInfo::availableDevices ( QAudio::AudioOutput ); }

QAudioDeviceInfo QQtAudioManager::defaultInputDevice() { return QAudioDeviceInfo::defaultInputDevice(); }

QAudioDeviceInfo QQtAudioManager::defaultOutputDevice() { return QAudioDeviceInfo::defaultOutputDevice(); }

QAudioFormat& QQtAudioManager::inputAudioFormat() { return mInputAudioFormat; }

QAudioFormat& QQtAudioManager::outputAudioFormat() { return mOutputAudioFormat; }

QAudioDeviceInfo& QQtAudioManager::inputDeviceInfo() { return mInputDeviceInfo; }

QAudioDeviceInfo& QQtAudioManager::outputDeviceInfo() { return mOutputDeviceInfo; }

void QQtAudioManager::startInput()
{
    stopInput();
    mInputManager = new QAudioInput ( mInputDeviceInfo, mInputAudioFormat, this );
    mInputDevice = mInputManager->start();
    if ( !mInputDevice || QAudio::NoError != mInputManager->error() )
    {
        pline() << mInputDeviceInfo.deviceName() << mInputAudioFormat.sampleSize() << mInputAudioFormat.sampleRate() <<
                mInputAudioFormat.channelCount() << "open failed, errcode:" << mInputManager->error();
        delete mInputManager;
        return;
    }
    //对IODevice读写，总是主动读写，但是在音频操作场合，读取音频输入，是被动的读，乐哉快哉。
    //在网络读写IODevice当中，也是变成了被动的读，快哉乐哉。
    connect ( mInputDevice, SIGNAL ( readyRead() ), this, SIGNAL ( readyRead() ) );
}

void QQtAudioManager::stopInput()
{
    //输入设备还开着，那么输入流设备一定开着。这是QQtAudioManager的功能设定。
    if ( mInputDevice )
    {
        disconnect ( mInputDevice, SIGNAL ( readyRead() ), this, SIGNAL ( readyRead() ) );
        mInputDevice = NULL;

        //关闭QAudioInput，等于关闭了拾音器。
        //这两个函数有一个（应该是deleteLater，迅速执行了）会释放mInputDevice，导致野指针，在android设备上会崩溃。此处注意。把disconnect函数提前。
        //注释：mInputDevice是mInputManager的读写口，由mInputManager内部产生和释放。
        mInputManager->stop();
        mInputManager->deleteLater();
        mInputManager = NULL;
    }
}

QByteArray QQtAudioManager::readBytes()
{
    if ( mInputDevice )
        return mInputDevice->readAll();
}

QAudioInput* QQtAudioManager::inputManager() { return mInputManager; }

QIODevice* QQtAudioManager::inputDevice() { return mInputDevice; }

void QQtAudioManager::startOutput()
{
    stopOutput();
    mOutputManager = new QAudioOutput ( mOutputDeviceInfo, mOutputAudioFormat, this );
    mOutputDevice = mOutputManager->start();
    if ( !mOutputDevice || QAudio::NoError != mOutputManager->error() )
    {
        pline() << mOutputDeviceInfo.deviceName() << mOutputAudioFormat.sampleSize() << mOutputAudioFormat.sampleRate() <<
                mOutputAudioFormat.channelCount() << "open failed, errcode:" << mOutputManager->error();
        delete mOutputManager;
        return;
    }
}

void QQtAudioManager::stopOutput()
{
    if ( mOutputDevice )
    {
        mOutputDevice = NULL;

        mOutputManager->stop();
        mOutputManager->deleteLater();
        mOutputManager = NULL;

    }
}

void QQtAudioManager::writeBytes ( QByteArray& bytes )
{
    if ( mOutputDevice )
        mOutputDevice->write ( bytes );
}

QAudioOutput* QQtAudioManager::outputManager() { return mOutputManager; }

QIODevice* QQtAudioManager::outputDevice() { return mOutputDevice; }

/*用户只需要处理音频输入、输出设备和每个的格式，QAudioInput、QAudioOutput、QIODevice(in + out)，都被QQtAudioManager处理了。*/
void QQtAudioManager::startDefaultInput()
{
    /*使用默认输入设备*/
    mInputDeviceInfo = QQtAudioManager::defaultInputDevice();

    //注意：用户一定要设置输入、输出Format，否则，如果默认输入输出设备格式不同，悲剧就要发生了。
    //这里的设置仅仅是个意见
    if ( !mInputAudioFormat.isValid() )
        mInputAudioFormat = defaultInputDevice().preferredFormat();

//    pline() << "in prefer" << mInputDeviceInfo.preferredFormat().channelCount() <<
//            mInputDeviceInfo.preferredFormat().sampleRate() <<
//            mInputDeviceInfo.preferredFormat().sampleSize();

//    pline() << "in" << mInputAudioFormat.channelCount() << mInputAudioFormat.sampleRate() <<
//            mInputAudioFormat.sampleSize();

    startInput();
}

void QQtAudioManager::startDefaultOutput()
{
    /*使用默认输出设备*/
    mOutputDeviceInfo = defaultOutputDevice();

    //注意：用户一定要设置输入、输出Format，否则，如果默认输入输出设备格式不同，悲剧就要发生了。
    //这里的设置仅仅是个意见
    if ( !mOutputAudioFormat.isValid() )
        mOutputAudioFormat = defaultOutputDevice().preferredFormat();

//    pline() << "out prefer" << mOutputDeviceInfo.preferredFormat().channelCount() <<
//            mOutputDeviceInfo.preferredFormat().sampleRate() <<
//            mOutputDeviceInfo.preferredFormat().sampleSize();

//    pline() << "out" << mOutputAudioFormat.channelCount() << mOutputAudioFormat.sampleRate() <<
//            mOutputAudioFormat.sampleSize();

    startOutput();
}
