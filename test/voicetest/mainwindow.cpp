#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qqtaudiomanager.h>
#include <qqtcore.h>
#include <qsound.h>
#include <qsoundeffect.h>
#include <qqtsoundeffect.h>
#include <qqtframe.h>

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

    connect ( &manager, SIGNAL ( readyRead() ), this, SLOT ( readyRead() ) );

    connect ( &wavRecManager, SIGNAL ( readyRead() ), this, SLOT ( wavRecReadyRead() ) );
    connect ( &wavFileManager, SIGNAL ( readyRead() ), this, SLOT ( wavFileReadyRead() ) );

    QList<QAudioDeviceInfo> ladInfo;
    ladInfo = QAudioDeviceInfo::availableDevices ( QAudio::AudioInput );
    QListIterator<QAudioDeviceInfo> itor ( ladInfo );
    pline() << "本机音频输入设备列表";

    while ( itor.hasNext() )
        pline() << itor.next().deviceName();

    pline() << "默认输入设备" << QAudioDeviceInfo::defaultInputDevice().deviceName();
    pline() << "输入设备详细信息";
    itor.toFront();

    while ( itor.hasNext() )
    {
        QAudioDeviceInfo adInfo = itor.next();
        pline() << adInfo.deviceName();
        pline() << adInfo.supportedByteOrders();
        pline() << adInfo.supportedChannelCounts();
        pline() << adInfo.supportedCodecs();
        pline() << adInfo.supportedSampleRates();
        pline() << adInfo.supportedSampleSizes();
        pline() << adInfo.supportedSampleTypes();
    }


    QList<QAudioDeviceInfo> ladOutputInfo;
    ladOutputInfo = QAudioDeviceInfo::availableDevices ( QAudio::AudioOutput );
    QListIterator<QAudioDeviceInfo> itor2 ( ladOutputInfo );
    pline() << "本机音频输出设备列表";

    while ( itor2.hasNext() )
        pline() << itor2.next().deviceName();

    pline() << "默认输出设备" << QAudioDeviceInfo::defaultOutputDevice().deviceName();
    pline() << "输出设备详细信息";
    itor2.toFront();

    while ( itor2.hasNext() )
    {
        QAudioDeviceInfo adInfo = itor2.next();
        pline() << adInfo.deviceName();
        pline() << adInfo.supportedByteOrders();
        pline() << adInfo.supportedChannelCounts();
        pline() << adInfo.supportedCodecs();
        pline() << adInfo.supportedSampleRates();
        pline() << adInfo.supportedSampleSizes();
        pline() << adInfo.supportedSampleTypes();
    }


    pline() << "..........................";

    connect ( ui->inputListWidget->selectionModel(), SIGNAL ( currentRowChanged ( QModelIndex, QModelIndex ) ),
              this, SLOT ( currentInputRowChanged ( QModelIndex, QModelIndex ) ) );
    connect ( ui->outputListWidget->selectionModel(), SIGNAL ( currentRowChanged ( QModelIndex, QModelIndex ) ),
              this, SLOT ( currentOutputRowChanged ( QModelIndex, QModelIndex ) ) );

//    on_pushButton_2_clicked();
//    ui->inputListWidget->setCurrentRow ( 0 );
//    ui->outputListWidget->setCurrentRow ( 0 );
//    ui->inputListWidget->setFocus();

    ui->inHS->setRange ( 0, 100 );
    ui->inHS->setValue ( 100 );

    ui->outHS->setRange ( 0, 100 );
    ui->outHS->setValue ( 100 );

    //pline() << QSoundEffect::supportedMimeTypes();

    QSoundEffect e;
    e.setLoopCount ( 1 );
    e.setVolume ( 0.9f );
    e.setMuted ( false );

    //不响
    QUrl u;
    u.setUrl ( "http://xmdx.sc.chinaz.com/Files/DownLoad/sound1/201802/9733.wav" );
    e.setSource ( u );
    //e.play();

    //响
    e.setSource ( QUrl::fromLocalFile ( res ( "9733.wav" ) ) );
    //e.play();

    //响
    //QSound::play ( res ( "9733.wav" ) );

    //响
    QQtWavSoundEffect e1;
    //e1.play ( res ( "9733.wav" ) );

    //响
    //QApplication::beep();

    //建议初始化
    QQtWavSoundEffect::Instance ( this );

    //可以多次循环调用。
    QQtWavSound ( res ( "9733.wav" ) );

    //QQtSleep ( 3000 );

}

MainWindow::~MainWindow()
{
    delete ui;
}

QAudioDeviceInfo MainWindow::findInputAudioDeviceInfoByName ( QString devName )
{
    QList<QAudioDeviceInfo> ladInfo;
    ladInfo = QQtAudioManager::availableInputDevices();
    QListIterator<QAudioDeviceInfo> itor ( ladInfo );

    while ( itor.hasNext() )
    {
        QAudioDeviceInfo adInfo = itor.next();

        if ( devName == adInfo.deviceName() )
            return adInfo;
    }
}

QAudioDeviceInfo MainWindow::findOutputAudioDeviceInfoByName ( QString devName )
{
    QList<QAudioDeviceInfo> ladInfo;
    ladInfo = QQtAudioManager::availableOutputDevices();
    QListIterator<QAudioDeviceInfo> itor ( ladInfo );

    while ( itor.hasNext() )
    {
        QAudioDeviceInfo adInfo = itor.next();

        if ( devName == adInfo.deviceName() )
            return adInfo;
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->inputListWidget->clear();

    QList<QAudioDeviceInfo> ladInfo;
    ladInfo = QQtAudioManager::availableInputDevices();
    QListIterator<QAudioDeviceInfo> itor ( ladInfo );
    pline() << "本机音频输入设备列表";

    while ( itor.hasNext() )
    {
        QAudioDeviceInfo adInfo = itor.next();
        pline() << adInfo.deviceName();
        ui->inputListWidget->addItem ( adInfo.deviceName() );
    }


    ui->outputListWidget->clear();

    QList<QAudioDeviceInfo> ladOutputInfo;
    ladOutputInfo = QQtAudioManager::availableOutputDevices();
    QListIterator<QAudioDeviceInfo> itor2 ( ladOutputInfo );
    pline() << "本机音频输出设备列表";

    while ( itor2.hasNext() )
    {
        QAudioDeviceInfo adInfo = itor2.next();
        pline() << adInfo.deviceName();
        ui->outputListWidget->addItem ( adInfo.deviceName() );
    }

}

void MainWindow::currentInputRowChanged ( QModelIndex cur, QModelIndex )
{
    /*在清空设备列表时，clear函数，会调用多次这个函数。在这里用cur valid加以过滤，否则，程序会崩溃退出。*/
    if ( !cur.isValid() )
        return;

    ui->inBit->clear();
    ui->inChn->clear();
    ui->intRate->clear();


    QString name = cur.data().toString();
    QAudioDeviceInfo dev = findInputAudioDeviceInfoByName ( name );

    if ( dev.isNull() )
        return;

    QList<int> size = dev.supportedSampleSizes();
    QListIterator<int> itor ( size );

    while ( itor.hasNext() )
    {
        QString s0 = QString::number ( itor.next() );
        ui->inBit->addItem ( s0 );
    }

    itor = dev.supportedChannelCounts();

    while ( itor.hasNext() )
    {
        QString s0 = QString::number ( itor.next() );
        ui->inChn->addItem ( s0 );
    }

    itor = dev.supportedSampleRates();

    while ( itor.hasNext() )
    {
        QString s0 = QString::number ( itor.next() );
        ui->intRate->addItem ( s0 );
    }

}

void MainWindow::currentOutputRowChanged ( QModelIndex cur, QModelIndex )
{
    if ( !cur.isValid() )
        return;

    ui->outBit->clear();
    ui->outChn->clear();
    ui->outRate->clear();


    QString name = cur.data().toString();
    QAudioDeviceInfo dev = findOutputAudioDeviceInfoByName ( name );

    if ( dev.isNull() )
        return;

    QList<int> size = dev.supportedSampleSizes();
    QListIterator<int> itor ( size );

    while ( itor.hasNext() )
    {
        QString s0 = QString::number ( itor.next() );
        ui->outBit->addItem ( s0 );
    }

    itor = dev.supportedChannelCounts();

    while ( itor.hasNext() )
    {
        QString s0 = QString::number ( itor.next() );
        ui->outChn->addItem ( s0 );
    }

    itor = dev.supportedSampleRates();

    while ( itor.hasNext() )
    {
        QString s0 = QString::number ( itor.next() );
        ui->outRate->addItem ( s0 );
    }
}

/*
 * 处理声音三要点
 * 声音的格式 ，也就是声音三要素，输入一个、输出一个，manager对其分开管理，但是建议用户合并为一个置等。通道数、采样位宽、采样率
 * 声音设备 ，输入一个、输出一个，manager管理start\stop等接口，manager内部的inputManager和outputManager负责其他接口。
 * 声音设备的读写出入口 ，manager管理，包括可读信号和写入函数。
*/
void MainWindow::on_pushButton_clicked()
{
    /*这里是自定义输入、输出设备*/
    QString name = QQtAudioManager::defaultInputDevice().deviceName();

    if ( ui->inputListWidget->currentIndex().isValid() )
        name = ui->inputListWidget->currentIndex().data().toString();

    QAudioDeviceInfo dev = findInputAudioDeviceInfoByName ( name );

    name = QQtAudioManager::defaultOutputDevice().deviceName();

    if ( ui->outputListWidget->currentIndex().isValid() )
        name = ui->outputListWidget->currentIndex().data().toString();

    QAudioDeviceInfo devOut = findOutputAudioDeviceInfoByName ( name );

    /*使用默认输入、输出设备*/
    //如果开启这段代码，页面上的输入、输出设备选择，就仅仅是个显示了，不具备操作能力。
    /*
    dev = QQtAudioManager::defaultInputDevice();
    devOut = QQtAudioManager::defaultOutputDevice();
    */

    //把设备设进manager去
    manager.inputDeviceInfo() = dev;
    manager.outputDeviceInfo() = devOut;

    //这里保证输入、输出使用格式相等 或者 不同
    //如果格式不同，在mac电脑上本地输入输出设备是可以使用的，但是对于连接的语音蓝牙话筒，却是不可以使用的，原因未知。
    //格式相同的时候，实在是太好用啦。
    //这个建议默认就相同，但是，在QQtAudioManager当中，并没有直接将其相等处理，如果用户在readyRead槽函数里，可以更改采样率进行某些特殊处理。一般不需要差异处理的，相等就行了。
//    int inBit = ui->inBit->currentIndex().data().toInt();
//    int inChn = ui->inChn->currentIndex().data().toInt();
//    int inRate = ui->intRate->currentIndex().data().toInt();
//    QAudioFormat inFmt;
//    inFmt.setChannelCount ( inChn );
//    inFmt.setSampleSize ( inBit );
//    inFmt.setSampleRate ( inRate );
//    inFmt.setCodec ( "audio/pcm" );
//    manager.inputAudioFormat() = inFmt;

    QAudioFormat outFmt = manager.outputDeviceInfo().preferredFormat();

    int outBit = outFmt.sampleSize(), outChn = outFmt.channelCount(), outRate = outFmt.sampleRate();

    if ( ui->outBit->currentIndex().isValid() )
        outBit = ui->outBit->currentIndex().data().toInt();

    if ( ui->outChn->currentIndex().isValid() )
        outChn = ui->outChn->currentIndex().data().toInt();

    if ( ui->outRate->currentIndex().isValid() )
        outRate = ui->outRate->currentIndex().data().toInt();

    outFmt.setChannelCount ( outChn );
    outFmt.setSampleSize ( outBit );
    outFmt.setSampleRate ( outRate );
    outFmt.setCodec ( "audio/pcm" );

    manager.inputAudioFormat() = outFmt;
    manager.outputAudioFormat() = outFmt;

    pline() << "in prefer" << dev.preferredFormat().channelCount() << dev.preferredFormat().sampleRate() <<
            dev.preferredFormat().sampleSize();

    pline() << "out prefer" << devOut.preferredFormat().channelCount() << devOut.preferredFormat().sampleRate() <<
            devOut.preferredFormat().sampleSize();

    pline() << "in" << manager.inputAudioFormat().channelCount() << manager.inputAudioFormat().sampleRate() <<
            manager.inputAudioFormat().sampleSize();

    pline() << "out" << manager.outputAudioFormat().channelCount() << manager.outputAudioFormat().sampleRate() <<
            manager.outputAudioFormat().sampleSize();

    manager.startInput();
    manager.startOutput();
}

void MainWindow::readyRead()
{
    //这里是用户实现，任何用户希望做的事情，都在这里做完。
    //可以 录音、保存文件
    //可以 直接播放
    //可以 混音 +保存 +播放...
    //可以 消音
    //可以 将pcm转换为其他格式音频
    //可以 降噪
    //可以 ...
    //ptime();//11-12ms 是个10ms timer
    QByteArray bytes = manager.readAll();
    manager.write ( bytes );
}

void MainWindow::wavRecReadyRead()
{
    QByteArray bytes = wavRecManager.readAll();
    //pline() << "recording:" << bytes.size();
    wavFileManager.write ( bytes );
}

void MainWindow::wavFileReadyRead()
{
    QByteArray bytes = wavFileManager.readAll();
    //pline() << "playing:" << bytes.size();
    wavRecManager.write ( bytes );
}

void MainWindow::on_pushButton_3_clicked()
{
    manager.stopInput();
    manager.stopOutput();
}

/*bug:Qt 设置音量会报错退出*/
void MainWindow::on_inHS_valueChanged ( int value )
{
    return;

    if ( !manager.inputDevice() )
        return;

    qreal linearVolume;
//    qreal linearVolume = QAudio::convertVolume ( value / qreal ( 100.0 ),
//                                                 QAudio::LogarithmicVolumeScale,
//                                                 QAudio::LinearVolumeScale );

//    pline() << "输入音量" << value << linearVolume << qRound ( linearVolume * 100 ) ;
    manager.inputManager()->setVolume ( qRound ( linearVolume * 100 ) );
}

/*bug:Qt 设置音量会报错退出*/
void MainWindow::on_outHS_valueChanged ( int value )
{
    return;

    if ( !manager.outputDevice() )
        return;

    qreal vol = qreal ( value ) / 100;
    pline() << "输出音量" << vol ;
    manager.outputManager()->setVolume ( vol );
}

void MainWindow::on_pushButton_4_clicked()
{
    manager.inputAudioFormat() = QQtAudioManager::defaultOutputDevice().preferredFormat();
    manager.outputAudioFormat() = QQtAudioManager::defaultOutputDevice().preferredFormat();

    pline() << "in prefer" << QQtAudioManager::defaultInputDevice().preferredFormat().channelCount() <<
            QQtAudioManager::defaultInputDevice().preferredFormat().sampleRate() <<
            QQtAudioManager::defaultInputDevice().preferredFormat().sampleSize();

    pline() << "out prefer" << QQtAudioManager::defaultOutputDevice().preferredFormat().channelCount() <<
            QQtAudioManager::defaultOutputDevice().preferredFormat().sampleRate() <<
            QQtAudioManager::defaultOutputDevice().preferredFormat().sampleSize();

    pline() << "in" << manager.inputAudioFormat().channelCount() << manager.inputAudioFormat().sampleRate() <<
            manager.inputAudioFormat().sampleSize();

    pline() << "out" << manager.outputAudioFormat().channelCount() << manager.outputAudioFormat().sampleRate() <<
            manager.outputAudioFormat().sampleSize();

    manager.startDefaultInput();
    manager.startDefaultOutput();
}

void MainWindow::on_pushButton_5_clicked()
{
    QString name = QQtAudioManager::defaultOutputDevice().deviceName();

    if ( ui->outputListWidget->currentIndex().isValid() )
        name = ui->outputListWidget->currentIndex().data().toString();

    QAudioDeviceInfo devOut = findOutputAudioDeviceInfoByName ( name );

    QQtWavSoundEffect::Instance()->useCustomOutputDevice ( devOut );
    QQtWavSound()->setLoops ( 3 );
    QQtWavSound ( res ( "9733.wav" ) );
}

void MainWindow::on_pushButton_6_clicked()
{
    QString name = QQtAudioManager::defaultOutputDevice().deviceName();

    if ( ui->outputListWidget->currentIndex().isValid() )
        name = ui->outputListWidget->currentIndex().data().toString();

    QAudioDeviceInfo devOut = findOutputAudioDeviceInfoByName ( name );

    QQtWavSoundEffect::Instance()->useCustomOutputDevice ( devOut );
    QQtWavSound ( res ( "9763.wav" ) );
    //QSound::play ( res("9763.wav"));
}

void MainWindow::on_pushButton_7_clicked()
{
    QString name = QQtAudioManager::defaultOutputDevice().deviceName();

    if ( ui->outputListWidget->currentIndex().isValid() )
        name = ui->outputListWidget->currentIndex().data().toString();

    QAudioDeviceInfo devOut = findOutputAudioDeviceInfoByName ( name );

    QQtWavSoundEffect::Instance()->useCustomOutputDevice ( devOut );
    QQtWavSound()->setLoops ( 1 );
    QQtWavSound ( res ( "9612.wav" ) );
}

#define TMPFILE "./temp.wav"

void MainWindow::on_pushButton_8_clicked()
{
    //不需要停止录音？需要
    //android 不支持./temp.wav....

    //record
    QAudioDeviceInfo input = QQtAudioManager::defaultInputDevice();
    wavRecManager.inputDeviceInfo() = input;
    wavRecManager.inputAudioFormat() = input.preferredFormat();

    //save wav file
    wavFileManager.outputAudioFormat() = wavRecManager.inputAudioFormat();
    wavFileManager.setOutputSourceFile ( TMPFILE );

    pline() << "record:" << wavRecManager.inputDeviceInfo().deviceName() << wavRecManager.inputAudioFormat();
    pline() << "save:" << wavFileManager.outputSourceFile() << wavFileManager.outputAudioFormat();

    //内部存在自动关停。对wav写自动关停，会导致文件被重写。这个函数是录音重新开始，所以可以自动关停。
    wavFileManager.startOutput();
    wavRecManager.startInput();
}

void MainWindow::on_pushButton_9_clicked()
{
    //不需要停止放音？需要

    //read wav file
    wavFileManager.setInputSourceFile ( TMPFILE );

    //play record
    wavRecManager.outputAudioFormat() = wavFileManager.inputAudioFormat();
    wavRecManager.outputDeviceInfo() = QQtAudioManager::defaultOutputDevice();

    pline() << "file:" << wavFileManager.inputSourceFile() << wavFileManager.inputAudioFormat();
    pline() << "play:" << wavRecManager.outputDeviceInfo().deviceName() << wavRecManager.outputAudioFormat();

    //内部存在自动关停。
    wavRecManager.startOutput();
    wavFileManager.startInput();
}

void MainWindow::on_pushButton_10_clicked()
{
    wavRecManager.stopInput();
    wavFileManager.stopOutput();
}

void MainWindow::on_pushButton_11_clicked()
{
    wavFileManager.stopInput();
    wavRecManager.stopOutput();
}

void MainWindow::on_pushButton_12_clicked()
{
    //android support 16bit but 24bit
    QQtWavSoundEffect* e0 = QQtWavSound();
    e0->setTimerInterval ( 100 );
    QQtWavSound ( res ( "9767.wav" ) );
}
