#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qqtobjectmanager.h"
#include "qqt-qt.h"
#include "qqtcore.h"
#include "qqtwidgets.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
#ifdef __EMBEDDED_LINUX__
    /*
     * 这里只要frameless足够
     */
    setWindowFlags(Qt::FramelessWindowHint);
    /*
     * 控件背景透明，显示设置的图片背景或者下一级背景。
     */
    setAttribute(Qt::WA_TranslucentBackground, true);
#endif
    //setFixedSize(1024, 600);
    //moveCenter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
