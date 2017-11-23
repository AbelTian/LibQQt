#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qqtqtiowebpageparser.h"

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );
    m_webpageparser = new QQtQtIOWebPageParser ( this );
    connect ( m_webpageparser, SIGNAL ( replyFinished ( QQtWebAccessSession* ) ),
              this, SLOT ( replyFinished ( QQtWebAccessSession* ) ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}
