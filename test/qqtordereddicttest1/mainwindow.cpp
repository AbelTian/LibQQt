#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qqtorderedmap.h>
#include <qqtordereddictionary.h>


#include <QDebug>
#include <QFile>

template<typename T>
QString qDebugStr ( T& t )
{
    QString str1;
    QDebug ( &str1 ) << t;
    return  str1;
}

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

    QMap<QString, QString> m0;
    m0.insert ( "String0", "String0" );
    m0.insert ( "AA0", "AA0" );
    m0.insert ( "EE0", "EE0" );

    QMapIterator<QString, QString> i0 ( m0 );
    while ( i0.hasNext() )
    {
        i0.next();
        qDebug() << i0.key() << i0.value();
    }

    for ( QMap<QString, QString>::Iterator i1 = m0.begin();
          i1 != m0.end(); i1++ )
    {
        qDebug() << i1.key() << i1.value();
    }


    QOrderedMap<QString, QString> map;

    map.insert ( "AA0", "AA0" );
    map.insert ( "EE0", "EE0" );
    map.insert ( "NN0", "NN0" );
    map.insert ( "KK0", "KK0" );
    map.insert ( "CC0", "CC0" );
    map.insert ( "String0", "String0" );

    //谨慎 模板里i++操作符异常。唉，我错了。前缀++，后缀++不一样。
    QOrderedMapIterator<QString, QString> itor ( map );
    //qDebug()  << itor.hasNext();
    while ( itor.hasNext() )
    {
        itor.next();
        qDebug() << itor.hasNext();;
        qDebug() << itor.key() << itor.value() << itor.hasNext();;

        //ui->textBrowser_2->append ( ds0.dictionary().toJson ( QJsonDocument::Indented ) );
        //ui->textBrowser_2->append ( ds0.buffer().toHex() );
    }

    itor.toBack();
    while ( itor.hasPrevious() )
    {
        itor.previous();
        qDebug() << itor.hasPrevious();;
        qDebug() << itor.key() << itor.value() << itor.hasPrevious();;
    }

    //error
    qDebug() << map["AA0"];
    qDebug() << map.value ( "AA0" );
    qDebug() << ".......";
#ifdef Q_MAP_DEBUG
    map.dump();
#endif

    QFile file ( "weather.json" );
    file.open ( QFile::ReadOnly );
    QByteArray bytes = file.readAll();
    file.close();
    QOrderedDictionary m2;
    m2.fromJson ( bytes ); //Json接口排序了
    qDebug() << m2;

    bytes = m2.toJson ( 4 );
    ui->textBrowser->append ( QString ( bytes ) );

    bytes = m2.toJson ( 0 );
    ui->textBrowser_2->append ( QString ( bytes ) );

    bytes = m2.toJson ( -1 );
    ui->textBrowser_5->append ( QString ( bytes ) );

    QOrderedDictionary m3;
    m3["GGG"] = "GGG";
    m3["ZZZ"] = "ZZZ";
    m3["BBBG"] = "BBBG";
    m3["JJJ"][0] = "CJJJ0";
    m3["JJJ"][1] = "AJJJ1";
    m3["JJJ"][2] = "BJJJ2";
    qDebug() << "Test:" << m3;

    qDebug() << qPrintable ( m3.toJson ( 4 ) ); //Json接口排序了。
    qDebug() << qPrintable ( m3.toXML ( 4 ) ); //

    QOrderedDictionaryMapIterator itor2 ( m3.getMap() );
    while ( itor2.hasNext() )
    {
        itor2.next();
        const QString& key = itor2.key();
        const QOrderedDictionary& value = itor2.value();
        pline() << key << value;
    }
    itor2.toBack();
    while ( itor2.hasPrevious() )
    {
        itor2.previous();
        qDebug() << itor2.hasPrevious();;
        qDebug() << itor2.key() << itor2.value() << itor2.hasPrevious();;
    }

    QOrderedDictionary m4;
    file.setFileName ( "mainwindow.ui" );
    file.open ( QFile::ReadOnly );
    bytes = file.readAll();
    file.close();
    m4.fromXML ( bytes );
    //qDebug() << m4["ui"];
    ui->textBrowser_4->append ( qPrintable ( m4.toXML ( 4 ) ) );


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::testMapFunc()
{

}
