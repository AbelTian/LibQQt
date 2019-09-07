#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qqtcore.h>

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );
    camera = 0;
    probe = new QVideoProbe ( this );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    on_pushButton_2_clicked();

    //start
    camera = new QCamera ( QCamera::FrontFace );
    camera->setCaptureMode ( QCamera::CaptureVideo );
    bool ret = probe->setSource ( camera );
    pline() << ret;
    connect ( probe, SIGNAL ( videoFrameProbed ( QVideoFrame ) ), this, SLOT ( present ( QVideoFrame ) ) );
    camera->start();

}

void MainWindow::on_pushButton_2_clicked()
{
    //stop
    if ( camera )
    {
        camera->stop();
        camera->deleteLater();
        camera = 0;
    }
}

void MainWindow::slotSetPicture ( QImage img )
{
    ui->widget->setPixmap ( img );
}

void MainWindow::present ( const QVideoFrame& frame )
{
    pline() << "ggg";

    if ( !frame.isValid() )
        return;

    QVideoFrame cloneFrame ( frame );
    /**
     * frame 可读
     */
    if ( !cloneFrame.map ( QAbstractVideoBuffer::ReadOnly ) )
        return;

    /**
     * 处理frame
     */

    //Android下的视频格式是怎么回事？需要转换吗？

    const QImage _image ( cloneFrame.bits(),
                          cloneFrame.width(),
                          cloneFrame.height(),
                          QVideoFrame::imageFormatFromPixelFormat ( cloneFrame.pixelFormat() ) );

    //需要对水平方向反转。
    //Windows，现在的图像保存能成功，直接显示，程序会异常退出。使用QImage的mirrored函数进行了水平翻转，可以正常显示。
    //水平翻转是为了不崩溃，正常显示图像。必选。
    //垂直翻转是为了上下显示正常。
    const QImage image = _image.mirrored ( true, true );

    /**
     * frame 不可读
     */
    cloneFrame.unmap();

    slotSetPicture ( image );
    return;
}
