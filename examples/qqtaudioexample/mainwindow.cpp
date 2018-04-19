#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

    //wavManager设置待播放的文件，inputFormat起效
    wavManager.setInputSourceFile ( res ( "9763.wav" ) );
    //audManager设置输出设备，也就是设置输出喇叭，并且，这里的并且很重要，设置输出格式，等于wav里的音频的格式。
    audManager.outputDeviceInfo() = QQtAudioManager::defaultOutputDevice();
    audManager.outputAudioFormat() = wavManager.inputAudioFormat();

    //连接wavManager的音频帧接收槽，这里其实是个接收器，在接收器里播放。
    connect ( &wavManager, SIGNAL ( readyRead() ), this, SLOT ( on_play_frame() ) );
    ;

    //这个是专门为使用机械硬盘设置的，减慢读取timer，要不有滋滋的噪音。
    wavManager.inputManager()->setTimerInterval ( 100 );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    wavManager.stopInput();
    audManager.stopOutput();

    audManager.startDefaultOutput();
    wavManager.startInput();
}

void MainWindow::on_play_frame()
{
    //这里readAll就是读一帧，（wavManger内部对音频进行了切帧）。
    QByteArray bytes = wavManager.readAll();
    //播放
    audManager.write ( bytes );
}
