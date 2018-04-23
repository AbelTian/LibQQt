#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qqtobjectmanager.h"
#include "qqt-qt.h"
#include "qqtcore.h"
#include "qqtwidgets.h"

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
