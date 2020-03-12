#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qfile.h>
#include <qqtdictionary.h>

#include <QDebug>
#define p3line() qDebug()

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

    QFile file ( "mainwindow.ui" );
    file.open ( QFile::ReadOnly );
    QByteArray bytes = file.readAll();
    file.close();;

    QQtDictionary dict;
    dict.fromXML ( bytes );
    p3line() << "root:" << dict;
    p3line() << "__processinginstruction__:" << dict["__processinginstruction__"];
    p3line() << "person:" << dict["person"];

    p3line() << "address:" << dict["person"]["address"];
    p3line() << "username:" << dict["person"]["username"];


    p3line() << "phone-number:" << dict["person"]["phone-number"];
    p3line() << "phone-number1:" << dict["person"]["phone-number"][0];
    p3line() << "phone-number1.__attributes__:" << dict["person"]["phone-number"][0]["__attributes__"];
    p3line() << "phone-number1.#text:" << dict["person"]["phone-number"][0]["#text"];

    QByteArray bytes0 = dict.toXML ( 4 );
    p3line() << qPrintable ( QString ( bytes0 ) );
    ui->textBrowser->append ( bytes0 );

    bytes0 = dict.toJson ( QJsonDocument::Indented ) ;
    p3line() << qPrintable ( QString ( bytes0 ) );
    ui->textBrowser_2->append ( bytes0 );

    bytes0 = dict.toYAML() ;
    p3line() << qPrintable ( QString ( bytes0 ) );
    ui->textBrowser_3->append ( bytes0 );

    bytes0 = dict["ui"]["widget"].toINI() ;
    p3line() << qPrintable ( QString ( bytes0 ) );
    ui->textBrowser_4->append ( bytes0 );

    bytes0 = dict["ui"]["layoutdefault"]["__attributes__"].toProperties() ;
    p3line() << qPrintable ( QString ( bytes0 ) );
    ui->textBrowser_5->append ( bytes0 );


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked ( bool checked )
{
    if ( ui->lineEdit->text().isEmpty() )
        return;

    QFile file ( ui->lineEdit->text() );
    file.open ( QFile::ReadOnly );
    QByteArray bytes = file.readAll();
    file.close();;

    QQtDictionary dict;
    if ( ui->comboBox->currentText().contains ( ".xml" ) )
    {
        dict.fromXML ( bytes );
    }
    else if ( ui->comboBox->currentText().contains ( ".json" ) )
    {
        dict.fromJson ( bytes );
    }
    else if ( ui->comboBox->currentText().contains ( ".ini" ) )
    {
        dict.fromINI ( bytes );
    }
    else if ( ui->comboBox->currentText().contains ( ".yaml" ) )
    {
        dict.fromYAML ( bytes );
    }
    else if ( ui->comboBox->currentText().contains ( ".properties" ) )
    {
        dict.fromProperties ( bytes );
    }
    else
    {
        return;
    }

    if ( ui->checkBox->isChecked() )
    {
        ui->textBrowser->clear();
        ui->textBrowser->append ( dict.toXML ( 4 ) );



        if ( !ui->lineEdit_2->text().isEmpty() )
        {

            QFile file ( ui->lineEdit_2->text() + ".xml" );
            file.open ( QFile::Truncate | QFile::WriteOnly );
            file.write ( dict.toXML ( 4 ) );
            file.close();;
        }

    }

    if ( ui->checkBox_2->isChecked() )
    {
        ui->textBrowser_2->clear();
        ui->textBrowser_2->append ( dict.toJson ( QJsonDocument::Indented ) );



        if ( !ui->lineEdit_2->text().isEmpty() )
        {

            QFile file ( ui->lineEdit_2->text() + ".json" );
            file.open ( QFile::Truncate | QFile::WriteOnly );
            file.write ( dict.toJson ( QJsonDocument::Indented ) );
            file.close();;
        }

    }

    if ( ui->checkBox_3->isChecked() )
    {
        ui->textBrowser_3->clear();
        ui->textBrowser_3->append ( dict.toYAML() );




        if ( !ui->lineEdit_2->text().isEmpty() )
        {

            QFile file ( ui->lineEdit_2->text() + ".yaml" );
            file.open ( QFile::Truncate | QFile::WriteOnly );
            file.write ( dict.toYAML() );
            file.close();;
        }

    }

    if ( ui->checkBox_4->isChecked() )
    {
        ui->textBrowser_4->clear();
        ui->textBrowser_4->append ( dict.toINI() );



        if ( !ui->lineEdit_2->text().isEmpty() )
        {

            QFile file ( ui->lineEdit_2->text() + ".ini" );
            file.open ( QFile::Truncate | QFile::WriteOnly );
            file.write ( dict.toINI() );
            file.close();;
        }

    }

    if ( ui->checkBox_5->isChecked() )
    {
        ui->textBrowser_5->clear();
        ui->textBrowser_5->append ( dict.toProperties() );


        if ( !ui->lineEdit_2->text().isEmpty() )
        {
            QFile file ( ui->lineEdit_2->text() + ".properties" );
            file.open ( QFile::Truncate | QFile::WriteOnly );
            file.write ( dict.toProperties() );
            file.close();;
        }


    }

}
