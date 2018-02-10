#include "qqtaudiomanager.h"

QQtAudioManager::QQtAudioManager ( QObject* parent ) : QObject ( parent )
{
    mInputAudioFormat = QAudioDeviceInfo::defaultInputDevice().preferredFormat();
    mOutputAudioFormat = QAudioDeviceInfo::defaultOutputDevice().preferredFormat();

    mInputDeviceInfo = QAudioDeviceInfo::defaultInputDevice();
    mOutputDeviceInfo = QAudioDeviceInfo::defaultOutputDevice();

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
    if ( mInputDevice )
    {
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
