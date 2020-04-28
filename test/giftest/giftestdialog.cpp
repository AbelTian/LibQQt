#include "giftestdialog.h"
#include "ui_giftestdialog.h"
#include "qqtframe.h"

GifTestDialog::GifTestDialog ( QWidget* parent ) :
    QDialog ( parent ),
    ui ( new Ui::GifTestDialog )
{
    ui->setupUi ( this );

    //使用res函数以前，代码量如此巨大。
#if defined (__ANDROID__) || defined (__ANDROIDX86__)
#if 0
    //如果apk文件被删除了呢？
    ui->labelGif->setGifFile ( "assets:/waiting.gif" );
    ui->widgetGif->setGifFile ( "assets:/waiting.gif" );
    ui->widgetQQt->setPixmap ( "assets:/yun.png" );
#else
    ui->labelGif->setGifFile ( "://AppRoot/waiting.gif" );
    ui->widgetGif->setGifFile ( "://AppRoot/waiting.gif" );
    ui->widgetQQt->setPixmap ( "://AppRoot/yun.png" );
#endif
#else
    //不兼容android....
    ui->labelGif->setGifFile ( "./waiting.gif" );
    ui->widgetGif->setGifFile ( "./waiting.gif" );
    ui->widgetQQt->setPixmap ( "./yun.png" );
#endif

    //使用了res函数以后 代码得到了极大简化
    pline() << conf_res ( "waiting.gif" );
    pline() << conf_res ( "../waiting.gif" );
    pline() << QDir ( "." ).relativeFilePath ( "skin/yun.png" );
    pline() << QDir ( conf_res ( "../waiting.gif" ) ).absolutePath();

    ui->labelGif->setGifFile (  conf_skin ( "waiting.gif" ) );
    ui->widgetGif->setGifFile ( conf_skin ( "waiting.gif" ) );
    ui->widgetQQt->setPixmap ( conf_skin ( "yun.png" ) );

    ui->checkBox->iconTable() [BTN_NORMAL] = conf_skin ( "waiting.gif" );
    ui->checkBox->iconTable() [BTN_PRESS] = conf_skin ( "st.gif" );
    ui->checkBox->iconTable() [BTN_HOVER] = conf_skin ( "yun.png" );
    ui->checkBox->renderToVariable();

    ui->p1->iconTable() [BTN_NORMAL] = conf_skin ( "a.gif" );
    ui->p1->iconTable() [BTN_PRESS] = conf_skin ( "b.gif" );
    ui->p1->iconTable() [BTN_HOVER] = conf_skin ( "c.gif" );
    ui->p1->renderToVariable();

    ui->r1->iconTable() [BTN_NORMAL] = conf_skin ( "a.gif" );
    ui->r1->iconTable() [BTN_PRESS] = conf_skin ( "b.gif" );
    ui->r1->iconTable() [BTN_HOVER] = conf_skin ( "c.gif" );
    ui->r1->renderToVariable();

    ui->r2->iconTable() [BTN_NORMAL] = conf_skin ( "a.gif" );
    ui->r2->iconTable() [BTN_PRESS] = conf_skin ( "b.gif" );
    ui->r2->iconTable() [BTN_HOVER] = conf_skin ( "c.gif" );
    ui->r2->renderToVariable();

    ui->c1->iconTable() [BTN_NORMAL] = conf_skin ( "a.gif" );
    ui->c1->iconTable() [BTN_PRESS] = conf_skin ( "b.gif" );
    ui->c1->iconTable() [BTN_HOVER] = conf_skin ( "c.gif" );
    ui->c1->renderToVariable();

    ui->pb1->setGifFile ( conf_skin ( "a.gif" ), conf_skin ( "b.gif" ) );
    ui->pb1->setRange ( 0, 100 );
    ui->pb1->setValue ( 60 );

    QTimer* timer = new QTimer ( this );
    timer->setInterval ( 100 );
    timer->setSingleShot ( false );
    QObject::connect ( timer, SIGNAL ( timeout() ),
                       this, SLOT ( updateProgress() ) ) ;
    timer->start();

    pline() << QMovie::supportedFormats();
}

GifTestDialog::~GifTestDialog()
{
    delete ui;
}

void GifTestDialog::updateProgress()
{
    static int i = 0;
    ui->pb1->setValue ( i++ % 100 );
}
