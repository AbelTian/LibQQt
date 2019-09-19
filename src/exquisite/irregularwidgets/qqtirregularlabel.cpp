#include <qqtirregularlabel.h>
#include <qqtwidget.h>

QQtIrregularLabel::QQtIrregularLabel ( QWidget* parent ) : QQtLabel ( parent )
{
    setAttribute ( Qt::WA_TranslucentBackground, true );
}

QQtIrregularLabel::~QQtIrregularLabel() {}

void QQtIrregularLabel::setAlignment ( Qt::Alignment alignment )
{
    QQtLabel::setAlignment ( alignment );
    makeMaskWidget();
}

void QQtIrregularLabel::makeMaskWidget ( void )
{
    if ( !pixmap() )
        return; //return QQtLabel::resizeEvent ( event );

    QImage normalImage = QImage ( pixmap()->toImage() );
    if ( normalImage.isNull() )
        return; //return QQtLabel::resizeEvent ( event );

    //label的特点，
    //图片无论如何不会缩放的 !!!
    //图片无论如何不会变形的
    //简而言之，图片是原型出现的。
    //label是永远不会小于图片的大小的，如果小于了，那肯定是widget。

    //绘图位置会有所变化。

    //准备好目标图板，等于当前窗口图板。
    //这个文件的主要目的是替代QIcon代码
    QImage resultImage ( size(), QImage::Format_ARGB32_Premultiplied );
    resultImage.fill ( Qt::transparent );

    QPainter painter ( &resultImage );
    //pline() << painter.renderHints();
    painter.setRenderHint ( QPainter::Antialiasing );
    painter.setRenderHint ( QPainter::TextAntialiasing );
    painter.setRenderHint ( QPainter::SmoothPixmapTransform );
    painter.setRenderHint ( QPainter::HighQualityAntialiasing );
    //pline() << painter.renderHints();

    //计算绘图位置，根据alignment，绘图位置不同。
    //pline() << alignment();
    int x0 = 0, y0 = 0;


    if ( alignment().testFlag ( Qt::AlignCenter ) )
    {
        x0 = ( resultImage.width() - normalImage.width() ) / 2;
        y0 = ( resultImage.height() - normalImage.height() ) / 2;
        //不会出现下边的代码
        x0 = x0 < 0 ? 0 : x0;
        y0 = y0 < 0 ? 0 : y0;
    }

    if ( alignment().testFlag ( Qt::AlignLeft ) )
    {
        x0 = 0;
    }

    if ( alignment().testFlag ( Qt::AlignRight ) )
    {
        x0 = resultImage.width() - normalImage.width();
    }

    if ( alignment().testFlag ( Qt::AlignHCenter ) )
    {
        x0 = ( resultImage.width() - normalImage.width() ) / 2;
    }

    if ( alignment().testFlag ( Qt::AlignJustify ) )
    {
        x0 = 0;
    }

    if ( alignment().testFlag ( Qt::AlignAbsolute ) )
    {
        x0 = 0;
    }

    if ( alignment().testFlag ( Qt::AlignHorizontal_Mask ) )
    {
        x0 = resultImage.width() - normalImage.width();
    }


    if ( alignment().testFlag ( Qt::AlignTop ) )
    {
        y0 = 0;
    }

    if ( alignment().testFlag ( Qt::AlignBottom ) )
    {
        y0 = resultImage.height() - normalImage.height();
    }

    if ( alignment().testFlag ( Qt::AlignVCenter ) )
    {
        y0 = ( resultImage.height() - normalImage.height() ) / 2;
    }

    if ( alignment().testFlag ( Qt::AlignBaseline ) )
    {
        y0 = 0;
    }

    if ( alignment().testFlag ( Qt::AlignVertical_Mask ) )
    {
        y0 = ( resultImage.height() - normalImage.height() ) / 2;
    }

    //绘制到目标图板
    painter.drawPixmap ( x0, y0, QPixmap::fromImage ( normalImage ) );
    painter.end();

    //将目标图板的mask设置为Mask
    setMask ( QPixmap::fromImage ( resultImage
                                 ).mask() );

#if 0
    static QQtWidget widget0;
    widget0.resize ( pixmap()->size() );
    widget0.setPixmap ( *pixmap() );
    widget0.show();

    static QQtWidget widget1;
    widget1.resize ( size() );
    widget1.setPixmap ( resultImage );
    widget1.show();
#endif
}


void QQtIrregularLabel::resizeEvent ( QResizeEvent* event )
{
    makeMaskWidget();
    return QQtLabel::resizeEvent ( event );
}
