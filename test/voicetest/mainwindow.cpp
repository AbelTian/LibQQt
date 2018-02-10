#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qqtaudiomanager.h>
#include <qqtcore.h>

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

    connect ( &manager, SIGNAL ( readyRead() ), this, SLOT ( readyRead() ) );



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

void MainWindow::on_pushButton_clicked()
{
    /*这里是自定义输入、输出设备*/
    QString name = ui->inputListWidget->currentIndex().data().toString();
    QAudioDeviceInfo dev = findInputAudioDeviceInfoByName ( name );

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
    manager.inputAudioFormat() = manager.outputDeviceInfo().preferredFormat();
    manager.outputAudioFormat() = manager.outputDeviceInfo().preferredFormat();

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
    QByteArray bytes = manager.readStreamBytes();
    manager.writeStreamBytes ( bytes );
}

void MainWindow::on_pushButton_3_clicked()
{
    manager.stopOutput();
    manager.stopInput();
}
