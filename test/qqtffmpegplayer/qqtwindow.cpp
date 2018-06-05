#include "qqtwindow.h"
#include "ui_qqtwindow.h"
#include "qqtobjectmanager.h"
#include "qqtwidgets.h"

//#include "FFmpegPlayer.h"

QQTWindow::QQTWindow ( QWidget* parent ) :
    QStackedWidget ( parent ),
    ui ( new Ui::QQTWindow )
{
    ui->setupUi ( this );

    QQtObjectManager::registerObject ( this );

#ifdef __EMBEDDED_LINUX__
    /*
     * 这里只要frameless足够
     */
    setWindowFlags ( Qt::FramelessWindowHint );
    /*
     * 控件背景透明，显示设置的图片背景或者下一级背景。
     */
    setAttribute ( Qt::WA_TranslucentBackground, true );
#endif
    setFixedSize ( 1024, 600 );
    moveCenter ( this );

    //FFmpegPlayer* player = new FFmpegPlayer ( this );
    //player->setMedia ( "/Users/abel/Downloads/cccc.mp3" );
    //player->play();
}

QQTWindow::~QQTWindow()
{
    delete ui;
}
