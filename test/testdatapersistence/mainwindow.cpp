#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qqt-qt.h>
#include <qqtdictionary.h>
#include <qqtdatapersistence.h>

QQtDataPersistence dp0;

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

    QFile file ( "a.txt" );
    file.open ( QFile::ReadOnly );
    QByteArray bytes = file.readAll();
    file.close();

    QQtDictionary dict;
    dict.fromJson ( bytes );
    QByteArray bytes0 = dict.toJson ( QJsonDocument::Indented );
    qDebug() << qPrintable ( bytes0 );
    ui->plainTextEdit->appendPlainText ( bytes0 );

    QTimer* timer = new QTimer ( this );
    timer->setInterval ( 2500 );
    connect ( timer, SIGNAL ( timeout() ),
              this, SLOT ( slotTimeout() ) );
    timer->start();

    dp0.setDataFile ( "a.txt" );
    dp0.prepareDataPersistence();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotTimeout()
{
    QFile file ( "a.txt" );
    file.open ( QFile::ReadOnly );
    QByteArray bytes = file.readAll();
    file.close();

    QQtDictionary dict;
    dict.fromJson ( bytes );
    QByteArray bytes0 = dict.toJson ( QJsonDocument::Indented );
    qDebug() << qPrintable ( bytes0 );

    ui->textBrowser->clear();
    ui->textBrowser->append ( bytes );
}

void MainWindow::on_pushButton_clicked ( bool checked )
{
    QByteArray bytes = ui->plainTextEdit->toPlainText().toLocal8Bit();

    dp0.start();

    QQtDictionary& handler = dp0.dictionary();
    //不清空就是和原字典合并，
    handler.clear();
    handler.fromJson ( bytes );

    //旁边的按钮更改了内部数据，又给改回去了，只好force write，marker()。
    dp0.marker();
    dp0.stop();


}

void MainWindow::on_pushButton_2_clicked ( bool checked )
{
    QByteArray bytes = ui->plainTextEdit->toPlainText().toLocal8Bit();


    QFile file ( "a.txt" );
    if ( file.exists() )
        file.open ( QFile::WriteOnly );
    else
        file.open ( QFile::Truncate | QFile::WriteOnly );
    file.write ( bytes );
    file.close();
}
