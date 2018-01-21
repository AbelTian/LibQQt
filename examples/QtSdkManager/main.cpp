#include "mainwindow.h"
#include <QApplication>

#include "qqtobjectfactory.h"
#include "qqtcore.h"
#include "qqthttpdownloadmanager.h"
#include "qqtapplication.h"
#include "qqtqtiowebpageparser.h"
#include "qqtdictionary.h"

int main ( int argc, char* argv[] )
{
    QQtApplication a ( argc, argv );

    QQtQtIOWebPageParser webparser;
    webparser.startNewParse ( );

    MainWindow w;
    w.show();

    return a.exec();
}
