#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qqtcore.h"

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

    int busy = 0;
    FMOD::File_GetDiskBusy ( &busy );
    pline() << busy;

    //wavManager设置待播放的文件，inputFormat起效
    wavManager.setInputSourceFile ( res ( "9763.wav" ) );
    //audManager设置输出设备，也就是设置输出喇叭，并且，这里的并且很重要，设置输出格式，等于wav里的音频的格式。
    audManager.outputDeviceInfo() = QQtAudioManager::defaultOutputDevice();
    audManager.outputAudioFormat() = wavManager.inputAudioFormat();

    //连接wavManager的音频帧接收槽，这里其实是个接收器，在接收器里播放。
    connect ( &wavManager, SIGNAL ( readyRead() ), this, SLOT ( on_play_frame() ) );
    ;

#if 0
    result = FMOD::System_Create ( &system );
    pline() << result;
    result = system->getVersion ( &version );
    pline() << result;
    result = system->init ( 32, FMOD_INIT_NORMAL, 0 );
    pline() << result;
    result = system->createStream ( res ( "9763.wav" ).toLocal8Bit().constData(), FMOD_LOOP_NORMAL | FMOD_2D, 0,
                                    &sound );
    pline() << result;
    result = sound->getNumSubSounds ( &numsubsounds );
    pline() << result;
    if ( numsubsounds )
    {
        sound->getSubSound ( 0, &sound_to_play );
    }
    else
    {
        sound_to_play = sound;
    }
#endif
}

MainWindow::~MainWindow()
{
    delete ui;

#if 0
    result = sound->release();  /* Release the parent, not the sound that was retrieved with getSubSound. */
    pline() << result;
    result = system->close();
    pline() << result;
    result = system->release();
    pline() << result;
#endif
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

void MainWindow::on_pushButton_2_clicked()
{
#if 0
    result = system->playSound ( sound_to_play, 0, false, &channel );
    pline() << result;
#endif
}
