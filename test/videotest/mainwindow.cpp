#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

    QVideoProbe* prob = new QVideoProbe ( this );
    QCamera* camera = new QCamera ( QCameraInfo::defaultCamera() );
    camera->setCaptureMode ( QCamera::CaptureVideo );
    prob->setSource ( camera );
    connect ( prob, SIGNAL ( videoFrameProbed ( const QVideoFrame& ) ),
              this, SLOT ( slotTestProbe ( const QVideoFrame& ) ) );
    connect ( ui->pushButton_3, SIGNAL ( released() ), camera, SLOT ( start() ) );

    return;

    input = new QQtVideoInput ( this );
    pline() << input->defaultCamera();
    pline() << input ->availableCameras();

    QCameraInfo inf = input->defaultCamera();
    ui->textBrowser->append ( QString ( "Camera:%1 [default]" ).arg ( inf.deviceName() ) );
    ui->textBrowser->append ( QString ( "  description:%1" ).arg ( inf.description() ) );
    ui->textBrowser->append ( QString ( "  position:%1" ).arg ( inf.position() ) );
    ui->textBrowser->append ( QString ( "  orientation:%1" ).arg ( inf.orientation() ) );
    ui->textBrowser->append ( QString ( "  isNull:%1" ).arg ( inf.isNull() ) );
    ui->textBrowser->append ( "" );

    QListIterator<QCameraInfo> itor ( input->availableCameras() );
    while ( itor.hasNext() )
    {
        const QCameraInfo& inf = itor.next();
        ui->textBrowser->append ( QString ( "Camera:%1 [index]" ).arg ( inf.deviceName() ) );
        ui->textBrowser->append ( QString ( "  description:%1" ).arg ( inf.description() ) );
        ui->textBrowser->append ( QString ( "  position:%1" ).arg ( inf.position() ) );
        ui->textBrowser->append ( QString ( "  orientation:%1" ).arg ( inf.orientation() ) );
        ui->textBrowser->append ( QString ( "  isNull:%1" ).arg ( inf.isNull() ) );
        ui->textBrowser->append ( "" );
    }

    pline() << input->viewFinderSettings().pixelFormat();
    pline() << input->camera()->supportedViewfinderPixelFormats();
    ui->textBrowser->append ( QString ( "Camera PixelFormat: [default]" ) );
    ui->textBrowser->append ( QString ( "  %1" ).arg ( input->viewFinderSettings().pixelFormat() ) );
    QListIterator<QVideoFrame::PixelFormat> itor1 ( input->camera()->supportedViewfinderPixelFormats() );
    while ( itor1.hasNext() )
    {
        const QVideoFrame::PixelFormat& fmt = itor1.next();
        ui->textBrowser->append ( QString ( "  %1 [index]" ).arg ( fmt ) );
    }
    ui->textBrowser->append ( "" );

    connect ( input, SIGNAL ( readyRead ( QImage ) ), this, SLOT ( slotImageComing ( QImage ) ) );
    connect ( input, SIGNAL ( readyReadCapture ( QImage ) ), this, SLOT ( slotCapture ( QImage ) ) );

    //input2 = new QQtVideoInput ( this );
    //connect ( input2, SIGNAL ( readyRead ( QImage ) ), this, SLOT ( slotImageComing2 ( QImage ) ) );

    //QThread* thread = new QThread();
    //input2->moveToThread ( thread );
    //thread->start();

    connect ( ui->pushButton_3, SIGNAL ( released() ), input, SLOT ( capture() ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotImageComing ( QImage img )
{
    ui->qqtwidget->setPixmap ( img );
}

void MainWindow::slotImageComing2 ( QImage img )
{
    ui->qqtwidget_2->setPixmap ( img );
    ui->qqtwidget_2->update();
}

void MainWindow::slotCapture ( QImage image )
{
    ui->qqtwidget_3->setPixmap ( image );
}

void MainWindow::slotTestProbe ( const QVideoFrame& frame )
{
    if ( !frame.isValid() )
        return;

    QVideoFrame cloneFrame ( frame );
    /**
     * frame 可读
     */
    if ( !cloneFrame.map ( QAbstractVideoBuffer::ReadOnly ) )
        return;

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

    //emit readyRead ( image );
    slotImageComing ( image );
    return ;
}

void MainWindow::on_pushButton_clicked()
{
    input->start();
    input2->start();
}

void MainWindow::on_pushButton_2_clicked()
{
    input->stop();
    input2->stop();
}
