#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv.hpp>
#include <highgui.hpp>
#include <qqtgiflabel.h>

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

    // read an image
    cv::Mat image = cv::imread ( "./tt.png", 1 );
    // create image window named "My Image"
    cv::namedWindow ( "OpenCV Image" );
    // show the image on window
    cv::imshow ( "OpenCV Image", image );

    QQtGifLabel* label = new QQtGifLabel ( this );
}

MainWindow::~MainWindow()
{
    delete ui;
}
