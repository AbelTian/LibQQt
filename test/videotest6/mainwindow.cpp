#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qqtmsgbox.h>
#include <QMessageBox>

#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/videodev2.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

static int xioctl ( int fd, int request, void* arg )
{
    int r;
    do
        r = ioctl ( fd, request, arg );
    while ( -1 == r && EINTR == errno );
    return r;
}


MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );
}

MainWindow::~MainWindow()
{
    delete ui;
}

int fd = 0;

void MainWindow::on_pushButton_clicked()
{
    fd = ::open ( "/dev/video2", O_RDONLY );
    if ( fd < 0 )
    {
        QMessageBox::warning ( this, "Open Error", "打开设备失败" );
        return;
    }

    printf ( "Checking Device Supported Format......\n" );
    struct v4l2_fmtdesc fmtdesc;
    fmtdesc.index = 0;
    fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    printf ( "Supported Formats:\n" );
    while ( ioctl ( fd, VIDIOC_ENUM_FMT, &fmtdesc ) != -1 )
    {
        QMessageBox::warning ( this, "Supported Format", QString ( "Fmt: %1: %2" ).arg ( fmtdesc.index ).arg ( ( char* ) fmtdesc.description ) );
        printf ( "\t%d.%s\n", fmtdesc.index + 1, fmtdesc.description );
        fmtdesc.index++;
    }
    //检查是否支持格式V4L2_PIX_FMT_MJPEG
    struct v4l2_format fmt;
    memset ( &fmt, 0, sizeof ( fmt ) );
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
    if ( ioctl ( fd, VIDIOC_TRY_FMT, &fmt ) == -1 && errno == EINVAL )
    {
        QMessageBox::warning ( this, "Try Format", QString ( "不支持MJPEG" ) );
        printf ( "not support format V4L2_PIX_FMT_MJPEG!\n" );
    }
    else
    {
        QMessageBox::warning ( this, "Try Format", QString ( "支持MJPEG" ) );
        printf ( "Do support format V4L2_PIX_FMT_MJPEG!\n" );
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    ::close ( fd );
}
