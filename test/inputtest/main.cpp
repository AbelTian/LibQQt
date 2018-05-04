#include "dialog.h"
#include <QQtApplication>
#include <QStyle>

int main ( int argc, char* argv[] )
{
    //QQtApplication::setStyle ( "Fusion" );
    //QQtApplication::setPalette ( QQtApplication::style()->standardPalette() );
    QQtApplication a ( argc, argv );

    Dialog w;
    w.show();

    return a.exec();
}
