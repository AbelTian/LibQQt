#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qqtdictionary.h>
#include <qqtdicthelper.h>
#include <QBuffer>

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

    QFile file ( "b.csv" );
    file.open ( QFile::ReadOnly );
    QByteArray bytes = file.readAll();
    ui->plainTextEdit->appendPlainText ( bytes );
    file.close();

    QQtDictionary dict;
    QList<QColor> bb;
    bb << QColor ( Qt::red );
    bb << QColor ( Qt::black );
    bb << QColor ( Qt::green );
    bb << QColor ( Qt::yellow );
    bb << QColor ( Qt::magenta );
    dict = bb;
    pline() << dict;

    QStringList cc;
    cc << "你好";
    cc << "您好";
    cc << "nin hao";
    cc << "Hello";
    dict = cc;
    pline() << dict;

    QQtDictionary dict1;
    dict1["StrKey"][0]["BBB"]["JJJ"][1]["GGG"] = "A Value.";
    QStringList keyList;
    keyList << "StrKey" << "0" << "BBB" << "JJJ";
    QQtDictionary& rd1 = QQtGetDictNode ( dict1, keyList );
    pline() << rd1;
    pline() << "-----";
    keyList << "1";
    rd1 = QQtGetDictNode ( dict1, keyList );
    pline() << rd1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked ( bool checked )
{
    if ( ui->plainTextEdit->toPlainText().isEmpty() )
        return;

    QQtDictionary dict;

    QByteArray bytes = ui->plainTextEdit->toPlainText().toLocal8Bit();

    QString seperate = ui->lineEdit->text();
    QString delimer = ui->lineEdit_2->text();
    QString encoding = ui->lineEdit_3->text();

    dict.fromCSV ( bytes, seperate, delimer, encoding );

    qDebug() << dict;
    for ( int i = 0; i < dict.getList().size(); i++ )
    {
        qDebug() << dict[i];
    }

    seperate = ui->lineEdit_11->text();
    delimer = ui->lineEdit_21->text();
    encoding = ui->lineEdit_31->text();

    ui->textBrowser_2->clear();
    ui->textBrowser_2->append ( dict.toCSV ( seperate, delimer, encoding ) );

    ui->textBrowser->clear();
    ui->textBrowser->append ( dict.toJson ( QJsonDocument::Indented ) );
}
