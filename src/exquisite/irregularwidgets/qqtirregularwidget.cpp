#include <qqtirregularwidget.h>

#include <QStylePainter>

QQtIrregularWidget::QQtIrregularWidget ( QWidget* parent ) : QQtWidget ( parent )
{
    setAttribute ( Qt::WA_TranslucentBackground, true );
}

QQtIrregularWidget::~QQtIrregularWidget() {}


void QQtIrregularWidget::resizeEvent ( QResizeEvent* event )
{
    if ( image().isNull() )
        return QQtWidget::resizeEvent ( event );

    switch ( imageStyle() )
    {
        case QQTCENTER:
        {
#if 0
            //无效
            QWidget widget;
            widget.resize ( size() );
            QStylePainter painter ( &widget );
            painter.drawItemPixmap ( widget.rect(), Qt::AlignCenter,
                                     QIcon ( QPixmap::fromImage ( image() ) ).pixmap ( widget.size(),
                                                                                       QIcon::Normal, QIcon::On ) );
            setMask ( widget.mask() );
#endif
#if 1
            //这个变量的跨平台特征，我很关心。
            QImage resultImage ( size(), QImage::Format_ARGB32_Premultiplied );
            resultImage.fill ( Qt::transparent );

            QPainter painter ( &resultImage );
            //pline() << painter.renderHints();
            painter.setRenderHint ( QPainter::Antialiasing );
            painter.setRenderHint ( QPainter::TextAntialiasing );
            painter.setRenderHint ( QPainter::SmoothPixmapTransform );
            //painter.setRenderHint ( QPainter::HighQualityAntialiasing );
            //pline() << painter.renderHints();

            //获取合理大小的pixmap 很可能会缩小一下
            QPixmap pixmap;
#if 0
            int w0, h0;
            w0 = resultImage.width() - pixmap.width();
            h0 = resultImage.height() - pixmap.height();

            //这里的步骤，其实就是QQtWidget里面CENTER效果，QIcon干的事情。
            //copy一点变化都没有
            //scale就是裁切，不知道为什么缩放全是裁切。

            //为什么会有画面撕裂？
            //QPixmap初始化后，有进行赋值，新的图片位置不一样，然后，撕裂了。所以，pixmap只能赋值一次！

            //图片过大 缩小 无论如何都不行
            if ( w0 < 0 || h0 < 0 )
                pixmap = QPixmap::fromImage ( image()
                                              .scaled ( resultImage.size(), Qt::KeepAspectRatio )
                                            );
            else if ( w0 < 0 && h0 < 0 )
                pixmap = QPixmap::fromImage ( image()
                                              .scaled ( resultImage.size(), Qt::KeepAspectRatio )
                                            );
            else if ( w0 < 0 )
                pixmap = QPixmap::fromImage ( image()
                                              .scaled ( resultImage.width(), image().height(), Qt::KeepAspectRatio )
                                            );
            else if ( h0 < 0 )
                pixmap = QPixmap::fromImage ( image()
                                              .scaled ( image().width(), resultImage.height(), Qt::KeepAspectRatio )
                                            );
            else
                pixmap = QPixmap::fromImage ( image() );
#endif

#if 1
            //偶尔会有重影，所以resize的频率不要太高，尤其在缩小的时候。
            pixmap = QIcon ( QPixmap::fromImage ( image() ) ).pixmap ( resultImage.size(),
                                                                       QIcon::Normal, QIcon::On );
#endif

            //QQtWidget里面，StylePainter自动居中绘制，这里，手动居中绘制。
            //从合理位置开始绘制 很可能从中间开始绘制
            int x0, y0;
            x0 = ( resultImage.width() - pixmap.width() ) / 2;
            y0 = ( resultImage.height() - pixmap.height() ) / 2;
            x0 = x0 < 0 ? 0 : x0;
            y0 = y0 < 0 ? 0 : y0;

            painter.drawPixmap ( x0, y0, pixmap );
            painter.end();

            setMask ( QPixmap::fromImage ( resultImage ).mask() );
#if 0
            static QQtWidget widget0;
            widget0.resize ( size() );
            widget0.setPixmap ( resultImage );
            widget0.show();
            static QQtWidget widget1;
            widget1.resize ( pixmap.size() );
            widget1.setPixmap ( pixmap );
            widget1.show();
#endif
#endif
#if 0
            //不居中
            setMask ( QIcon ( QPixmap::fromImage ( image() ) ).pixmap ( rect().size(),
                                                                        QIcon::Normal, QIcon::On ).mask() );
#endif
        }
        break;

        case QQTTILEDWIDTH:
        {
            setMask ( QPixmap::fromImage ( image().copy ( rect() )
                                           .scaledToWidth ( rect().width() )
                                         ).mask() );
        }
        break;

        case QQTTILEDHEIGHT:
        {
            setMask ( QPixmap::fromImage ( image().copy ( rect() )
                                           .scaledToHeight ( rect().height() )
                                         ).mask() );
        }
        break;

        case QQTTILED:
        {
            setMask ( QPixmap::fromImage ( image().copy ( rect() )
                                           .scaled ( rect().width(), rect().height(), Qt::KeepAspectRatio )
                                         ).mask() );
        }
        break;

        case QQTZOOMWIDTH:
        {
            setMask ( QPixmap::fromImage ( image()
                                           .scaled ( rect().width(), image().height(), Qt::IgnoreAspectRatio )
                                         ).mask() );
        }
        break;

        case QQTZOOMHEIGHT:
        {
            setMask ( QPixmap::fromImage ( image()
                                           .scaled ( image().width(), rect().height(), Qt::IgnoreAspectRatio )
                                         ).mask() );
        }
        break;

        case QQTZOOM:
        {
            setMask ( QPixmap::fromImage ( image()
                                           .scaled ( rect().width(), rect().height(), Qt::IgnoreAspectRatio )
                                         ).mask() );
        }
        break;

        case QQTZOOMWIDTH_KEEPASPECTRATIO:
        {
            setMask ( QPixmap::fromImage ( image()
                                           .scaled ( rect().width(), image().height(), Qt::KeepAspectRatio )
                                         ).mask() );
        }
        break;

        case QQTZOOMHEIGHT_KEEPASPECTRATIO:
        {
            setMask ( QPixmap::fromImage ( image()
                                           .scaled ( image().width(), rect().height(), Qt::KeepAspectRatio )
                                         ).mask() );
        }
        break;

        case QQTZOOM_KEEPASPECTRATIO:
        {
            setMask ( QPixmap::fromImage ( image()
                                           .scaled ( rect().width(), rect().height(), Qt::KeepAspectRatio )
                                         ).mask() );
        }
        break;

        default:
        {

        }
        break;
    }

    return QQtWidget::resizeEvent ( event );
}
