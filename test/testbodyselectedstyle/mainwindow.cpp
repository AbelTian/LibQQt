#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qqtchildbodymover.h>
#include <qqtbodyresizer.h>

#include <qqtframe.h>

#include <qqtbodyselectedstyle.h>

#include <qqtbodymousewheelscalingeffect.h>
QQtBodySelectedStyle* s0 ;

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

    centralWidget()->setFocusPolicy ( Qt::StrongFocus );

    ui->widget->setPixmap ( conf_root ( "logo.png" ) );
    ui->widget->setContentsMargins ( 4, 4, 4, 4 );
    ui->widget->setMouseTracking ( true );
    ui->widget->setFocusPolicy ( Qt::StrongFocus );
    ui->widget->installEventFilter ( new QQtChildBodyMover ( this ) );
    ui->widget->installEventFilter ( new QQtBodyResizer ( this ) );
    s0 = new QQtBodySelectedStyle ( this );
    ui->widget->installEventFilter ( s0 );
    //s0->setSelectedStyle ( QQtBodySelectedStyle::SelectedStyle_DottedLine );
    ui->radioButton_3->setChecked ( true );
    //ui->widget->setImageStyle ( QQtWidget::QQTZOOM_KEEPASPECTRATIO );
    ui->widget->installEventFilter ( new QQtBodyMouseWheelScalingEffect ( this ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_radioButton_toggled ( bool checked )
{
    s0->setSelectedStyle ( QQtBodySelectedStyle::SelectedStyle_QtDesigner );
}

void MainWindow::on_radioButton_2_toggled ( bool checked )
{
    s0->setSelectedStyle ( QQtBodySelectedStyle::SelectedStyle_QRCodeScaner );
}

void MainWindow::on_radioButton_3_toggled ( bool checked )
{
    s0->setSelectedStyle ( QQtBodySelectedStyle::SelectedStyle_DottedLine );
}
