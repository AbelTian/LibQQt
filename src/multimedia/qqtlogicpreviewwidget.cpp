#include "qqtlogicpreviewwidget.h"
#include "ui_qqtlogicpreviewwidget.h"

QQtLogicPreviewWidget::QQtLogicPreviewWidget ( QWidget* parent ) :
    QWidget ( parent ),
    ui ( new Ui::QQtLogicPreviewWidget )
{
    ui->setupUi ( this );
    manager = new QQtLogicVideoManager ( this );
    connect ( manager, SIGNAL ( readyRead ( const QImage& ) ),
              this, SLOT ( slotReadyRead ( const QImage& ) ) );
}

QQtLogicPreviewWidget::~QQtLogicPreviewWidget()
{
    delete ui;
}

void QQtLogicPreviewWidget::slotReadyRead ( const QImage& image )
{
    mImage = image;
}


void QQtLogicPreviewWidget::paintEvent ( QPaintEvent* )
{
    QStylePainter painter ( this );

    /*
     * 采集的图像左边上边有黑边 更换摄像头或许回有所改善 待调试
     */
    QRect srcRect ( 2, 6, 720, 480 );
    QRect dstRect = rect();
    painter.scale ( 1.01, 1.02 );

    /*
     * 缩放OK
     */
    painter.drawImage ( dstRect, mImage, srcRect );
    //painter.drawPixmap(dstRect,QPixmap::fromImage(*frame,Qt::AutoColor),srcRect);;
    /*
     * 裁切OK
     */
    //painter.drawItemPixmap(srcRect, Qt::AlignCenter, QPixmap::fromImage(*frame,Qt::AutoColor));
    /*
     * 30ms 屏幕有闪烁
     */
    //update();
}


void QQtLogicPreviewWidget::mousePressEvent ( QMouseEvent* e )
{
    static bool bGInit = false;

    if ( !bGInit && !bFullScreen )
    {
        flags = windowFlags();
        flags |= Qt::FramelessWindowHint;
        geome = geometry();
        bGInit = true;
    }

#ifdef __EMBEDDED_LINUX__

    //pline() << e->pos() << e->globalPos();
    if ( e->pos().x() < 0 || e->pos().y() < 0 ||
         e->pos().x() > geome.width() || e->pos().y() > geome.height() )
    {
        //在mips板上，全屏返回的时候，点击其他位置，会多响应一次，在此处过滤。
        pline() << "warning!";
        Q_UNUSED ( e );
        return;
    }

#endif

    setAttribute ( Qt::WA_TranslucentBackground, true );
    setAttribute ( Qt::WA_NoMousePropagation, true );
    setAttribute ( Qt::WA_OpaquePaintEvent, true );

    if ( bFullScreen )
    {
        flags ^= Qt::Window;
        flags |= Qt::Widget;
        setParent ( m_parent, flags );
        setGeometry ( geome );
        show();
        bFullScreen = false;
    }
    else
    {
        int QQT_SCRN_WIDTH = QApplication::desktop()->availableGeometry().width();
        int QQT_SCRN_HEIGHT = QApplication::desktop()->availableGeometry().height();
        flags ^= Qt::Widget;
        flags |= Qt::Window;
        setParent ( 0, flags );
        setGeometry ( 0, 0, QQT_SCRN_WIDTH, QQT_SCRN_HEIGHT );
        show();
        bFullScreen = true;
    }

    pline() << flags;
    QWidget::mousePressEvent ( e );
}
