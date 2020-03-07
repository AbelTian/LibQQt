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
    handler.clear();
    handler.fromJson ( bytes );

    dp0.stop();


}
