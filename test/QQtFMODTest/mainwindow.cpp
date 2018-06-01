#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fmod.hpp"
#include <qqtcore.h>

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );
    int busy = 0;
    FMOD::File_GetDiskBusy ( &busy );
    pline() << busy;
}

MainWindow::~MainWindow()
{
    delete ui;
}
