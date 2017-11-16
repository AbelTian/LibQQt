#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qqtsvgwidget.h"
#include "qqtsvgpushbutton.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString svg = QString("/Users/abel/Pictures/jia.svg");
    ui->w->setSvgFile(svg);

    ui->b0->iconTable()[BTN_NORMAL] = "/Users/abel/Develop/d1-product/App/skin/default/bt_stir.svg";
    ui->b0->iconTable()[BTN_HOVER] = "/Users/abel/Develop/d1-product/App/skin/default/bt_stir.svg";
    ui->b0->iconTable()[BTN_PRESS] = "/Users/abel/Develop/d1-product/App/skin/default/bt_stir_press.svg";
    ui->b0->renderToVariable();
}

MainWindow::~MainWindow()
{
    delete ui;
}
