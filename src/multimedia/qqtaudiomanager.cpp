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
    connect ( mInputDevice, SIGNAL ( readyRead() ), this, SIGNAL ( readyRead() ) );
}

void QQtAudioManager::stopInput()
{
    //输入设备还开着，那么输入流设备一定开着。这是QQtAudioManager的功能设定。
    if ( mInputDevice )
    {
        //关闭QAudioInput，等于关闭了拾音器。
        mInputManager->stop();
        mInputManager->deleteLater();
        mInputManager = NULL;

        disconnect ( mInputDevice, SIGNAL ( readyRead() ), this, SIGNAL ( readyRead() ) );
        mInputDevice = NULL;
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
}

void QQtAudioManager::stopOutput()
{
    if ( mOutputDevice )
    {
        mOutputManager->stop();
        mOutputManager->deleteLater();
        mOutputManager = NULL;

        mOutputDevice = NULL;
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
    mOutputDeviceInfo = QQtAudioManager::defaultOutputDevice();

//    pline() << "out prefer" << mOutputDeviceInfo.preferredFormat().channelCount() <<
//            mOutputDeviceInfo.preferredFormat().sampleRate() <<
//            mOutputDeviceInfo.preferredFormat().sampleSize();

//    pline() << "out" << mOutputAudioFormat.channelCount() << mOutputAudioFormat.sampleRate() <<
//            mOutputAudioFormat.sampleSize();

    startOutput();
}
