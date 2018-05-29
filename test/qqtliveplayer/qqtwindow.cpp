#include "qqtwindow.h"
#include "ui_qqtwindow.h"
#include "qqtobjectmanager.h"
#include "qqt-qt.h"
#include "qqtcore.h"
#include "qqtgui.h"
#include "animationmanager.h"

#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>
#include <VLCQtWidgets/WidgetVideo.h>

#include "qqtwidgets.h"
#include "qqttreewidget.h"
#include "qqtsqltreemodel.h"

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
    setAcceptDrops ( true );

    QQtSqlTreeModel* model = new QQtSqlTreeModel ( this );
    ui->treeView->setModel ( model );

    ( ( QQtSqlTreeModel* ) ui->treeView->model() )
    ->setAbsoluteFilePath ( "LiveStream.db" );
    ( ( QQtSqlTreeModel* ) ui->treeView->model() )
    ->query ( "" );
    for ( int i = 1; i < 11; i++ )
        ui->treeView->setColumnHidden ( i, true );
    ( ( QQtSqlTreeModel* ) ui->treeView->model() )
    ->setHeaderData ( 0, Qt::Horizontal, tr ( "pindao liebiao" ) );
    connect ( ui->treeView, SIGNAL ( doubleClicked ( const QModelIndex& ) ),
              this, SLOT ( doubleClicked ( const QModelIndex& ) ) );

#if 0
    QPixmap pixmap ( "./skin/default/splash.png" );
    QSplashScreen splash ( pixmap );
    splash.showMessage ( tr ( "Loading..." ), Qt::AlignBottom );
    splash.setFixedSize ( 600, 400 );
    splash.show();
    QQtSleep ( 400 );
    splash.finish ( this );
#elif 0
    /**
     * set movie in label0
     * label0 will dispear in this function
     */
    QMovie mov ( "./skin/default/splash.gif" );
    QLabel label;
    label.setMovie ( &mov );
    label.setFixedSize ( 400, 300 );
    moveCenter ( &label );
    mov.start();
    label.show();
    QQtSleep ( 3000 );
#endif

#if 1
    //QCoreApplication::setAttribute(Qt::AA_X11InitThreads);
    //VlcCommon::setPluginPath(QCoreApplication::applicationDirPath() + "/plugins");
    _instance = new VlcInstance ( VlcCommon::args(), this );
    _player = new VlcMediaPlayer ( _instance );
    _player->setVideoWidget ( ui->widget );
    ui->widget->setMediaPlayer ( _player );
    ui->widget->setWindowFlags ( ui->widget->windowFlags() | Qt::WindowTransparentForInput );
    ui->horizontalSlider->setMediaPlayer ( _player );
    ui->horizontalSlider->setVolume ( 100 );
    _media = NULL;

    //VlcMediaPlayer *_player2;
    //_player2 = new VlcMediaPlayer(_instance);
    //_player2->setVideoWidget(ui->widget_2);
    //QString url2 = "rtmp://live.hkstv.hk.lxdns.com/live/hks";
    //VlcMedia *_media2;
    //_media2 = new VlcMedia(url2, _instance);
    //ui->widget_2->setMediaPlayer(_player2);
    //_player2->open(_media2);

#endif

    /**
     * decorate all windows
     * nobody use animation to mainwindow
     * so this animation use to child window
     */
    AnimationManager::Instance ( this );
}

QQTWindow::~QQTWindow()
{
    delete ui;
}

void QQTWindow::doubleClicked ( const QModelIndex& index )
{
    if ( !index.parent().isValid() )
        return;

    QString uri = index.model()->index ( index.row(), 1, index.parent() ).data().toString();

    pline() << uri;

    if ( _player->hasVout() )
        _player->stop();
    if ( _media )
        delete _media;

    //QString url = "http://ivi.bupt.edu.cn/hls/cctv1.m3u8";
    _media = new VlcMedia ( uri, _instance );
    _player->open ( _media );
}

/**
 * @brief QQTWindow::dragEnterEvent
 * 当用户拖动文件到窗口部件上时候，就会触发dragEnterEvent事件
 */
void QQTWindow::dragEnterEvent ( QDragEnterEvent* event )
{
    //如果为文件，则支持拖放
    if ( event->mimeData()->hasFormat ( "text/uri-list" ) )
        event->acceptProposedAction();
}

/**
 * @brief QQTWindow::dropEvent
 * 当用户放下这个文件后，就会触发dropEvent事件
 */
void QQTWindow::dropEvent ( QDropEvent* event )
{
    /**
    * 注意：这里如果有多文件存在，意思是用户一下子拖动了多个文件，而不是拖动一个目录
    * 如果想读取整个目录，自己编写函数实现读取整个目录文件名
    */
    QList<QUrl> urls = event->mimeData()->urls();
    if ( urls.isEmpty() )
        return;

    /**
     * 往文本框中追加文件名
     */
    foreach ( QUrl url, urls )
    {
        QString file_name = url.toLocalFile();
        pline() << file_name;
        if ( _player->hasVout() )
            _player->stop();
        if ( _media )
            delete _media;
        _media = new VlcMedia ( file_name, true, _instance );
        _player->open ( _media );
        break;
    }
}
