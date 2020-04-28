#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qqtframe.h>

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

#if 0
    ui->widget->setNormalImage ( QImage ( conf_skin ( "bt_bt_normal.png" ) ), QImage ( conf_skin ( "bt_bt_press.png" ) ) );
    ui->widget->setHoverImage ( QImage ( conf_skin ( "bt_bt_hover.png" ) ) );
    ui->widget->setDisableImage ( QImage ( conf_skin ( "bt_bt_disable.png" ) ) );
#else
    ui->widget->setImage ( QImage ( conf_skin ( "bt_bt_normal.png" ) ) );
#endif

    ui->pushButton_2->setNormalImage ( QImage ( conf_skin ( "bt_bt_normal.png" ) ),
                                       QImage ( conf_skin ( "bt_bt_press.png" ) ) );
    ui->pushButton_2->setHoverImage ( QImage ( conf_skin ( "bt_bt_hover.png" ) ) );
    ui->pushButton_2->setDisableImage ( QImage ( conf_skin ( "bt_bt_disable.png" ) ) );

#if 1
    ui->pushButton_3->imageTable() [BTN_NORMAL] = QImage ( conf_skin ( "bt_bt_normal.png" ) );
    ui->pushButton_3->imageTable() [BTN_PRESS] = QImage ( conf_skin ( "bt_bt_press.png" ) );
    ui->pushButton_3->imageTable() [BTN_HOVER] = QImage ( conf_skin ( "bt_bt_hover.png" ) );
    ui->pushButton_3->imageTable() [BTN_DISABLE] = QImage ( conf_skin ( "bt_bt_disable.png" ) );
#endif

    ui->pushButton->setCheckable ( true );
    ui->pushButton->setChecked ( false );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked ( bool checked )
{
    if ( checked )
    {
        ui->widget->setEnabled ( false );
        ui->pushButton_2->setEnabled ( false );
        ui->pushButton_3->setEnabled ( false );
        ui->pushButton_4->setEnabled ( false );
    }
    else
    {
        ui->widget->setEnabled ( true );
        ui->pushButton_2->setEnabled ( true );
        ui->pushButton_3->setEnabled ( true );
        ui->pushButton_4->setEnabled ( true );
    }

}
