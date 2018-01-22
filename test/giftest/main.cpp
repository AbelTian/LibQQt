#include "giftestdialog.h"
#include <qqtapplication.h>
#include "qqtcore.h"
#include "qqtwidgets.h"

int main ( int argc, char* argv[] )
{
    /*务必使用QQtApplication，否则，初始化设置不正确，App无法正确的确认目录位置。*/
    QQtApplication a ( argc, argv );

    GifTestDialog w;
    w.show();
    moveFull ( &w );

    return a.exec();
}
