#ifndef QQTNINEPATCHWIDGET_H
#define QQTNINEPATCHWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <qqtcore.h>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtNinePatchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QQtNinePatchWidget ( QWidget* parent = nullptr );

protected:

    /*
    **  功能                : 9格图处理
    **  picName          : 图片名字
    **  titleHeight      : 标题栏高度(单位:像素)
    **  BorderLineWidth  : 边框宽度(单位:像素)
    **  parent           : 带画背景的窗口句柄
    **  返回值              :处理完成的图片
    */
    QPixmap* NinePatch ( QString& picName, int titleHeight, int BorderLineWidth, QWidget* Wnd ) {
        QPixmap* pix = new QPixmap ( picName );

        int pixWidth = pix->width();
        int pixHeight = pix->height();

        QSize WndSize = Wnd->size();
        int DstWidth = WndSize.width();
        int DstHeight = WndSize.height();

        QPixmap pix_1 = pix->copy ( 0, 0, BorderLineWidth, titleHeight );
        QPixmap pix_2 = pix->copy ( BorderLineWidth, 0, pixWidth - BorderLineWidth * 2, titleHeight );
        QPixmap pix_3 = pix->copy ( pixWidth - BorderLineWidth, 0, BorderLineWidth, titleHeight );

        QPixmap pix_4 = pix->copy ( 0, titleHeight, BorderLineWidth, pixHeight - titleHeight - BorderLineWidth );
        QPixmap pix_5 = pix->copy ( BorderLineWidth, titleHeight, pixWidth - BorderLineWidth * 2,
                                    pixHeight - titleHeight - BorderLineWidth );
        QPixmap pix_6 = pix->copy ( pixWidth - BorderLineWidth, titleHeight, BorderLineWidth,
                                    pixHeight - titleHeight - BorderLineWidth );

        QPixmap pix_7 = pix->copy ( 0, pixHeight - BorderLineWidth, BorderLineWidth, BorderLineWidth );
        QPixmap pix_8 = pix->copy ( BorderLineWidth, pixHeight - BorderLineWidth, pixWidth - BorderLineWidth * 2,
                                    BorderLineWidth );
        QPixmap pix_9 = pix->copy ( pixWidth - BorderLineWidth, pixHeight - BorderLineWidth, BorderLineWidth, BorderLineWidth );

        pix_2 = pix_2.scaled ( DstWidth - BorderLineWidth * 2, titleHeight, Qt::IgnoreAspectRatio ); //保持高度拉宽
        pix_4 = pix_4.scaled ( BorderLineWidth, DstHeight - titleHeight - BorderLineWidth,
                               Qt::IgnoreAspectRatio ); //保持宽度拉高
        pix_5 = pix_5.scaled ( DstWidth - 3, DstHeight - titleHeight - BorderLineWidth );
        pix_6 = pix_6.scaled ( BorderLineWidth, DstHeight - titleHeight - BorderLineWidth,
                               Qt::IgnoreAspectRatio ); //保持宽度拉高
        pix_8 = pix_8.scaled ( DstWidth - BorderLineWidth * 2, BorderLineWidth ); //保持高度拉宽


        QPixmap* resultImg = new QPixmap ( WndSize );
        QPainter* painter = new QPainter ( resultImg );

        if ( !resultImg->isNull() ) {
            painter->drawPixmap ( 0, 0, pix_1 );
            painter->drawPixmap ( 3, 0, pix_2 );
            painter->drawPixmap ( DstWidth - 3, 0, pix_3 );
            painter->drawPixmap ( 0, titleHeight, pix_4 );
            painter->drawPixmap ( 3, titleHeight, pix_5 );
            painter->drawPixmap ( DstWidth - 3, titleHeight, pix_6 );
            painter->drawPixmap ( 0, DstHeight - 3, pix_7 );
            painter->drawPixmap ( 3, DstHeight - 3, pix_8 );
            painter->drawPixmap ( DstWidth - 3, DstHeight - 3, pix_9 );
            painter->end();
        }

        return resultImg;
    }



    /*
    **  功能             : 九宫格图处理
    **  picName          : 图片名字
    **  iHorzSplit       : 四个角上格子的宽度
    **  iVertSplit       : 四个角上格子的高度
    **  DstWidth         : 整个图片缩放的宽度
    **  DstWidth         : 整个图片缩放的高度
    **  返回值           : 处理完成的图片
    */
    QPixmap* NinePatch ( QString& picName, int iHorzSplit, int iVertSplit, int DstWidth, int DstHeight ) {
        QPixmap* pix = new QPixmap ( picName );

        int pixWidth = pix->width();
        int pixHeight = pix->height();

        QPixmap pix_1 = pix->copy ( 0, 0, iHorzSplit, iVertSplit );
        QPixmap pix_2 = pix->copy ( iHorzSplit, 0, pixWidth - iHorzSplit * 2, iVertSplit );
        QPixmap pix_3 = pix->copy ( pixWidth - iHorzSplit, 0, iHorzSplit, iVertSplit );

        QPixmap pix_4 = pix->copy ( 0, iVertSplit, iHorzSplit, pixHeight - iVertSplit * 2 );
        QPixmap pix_5 = pix->copy ( iHorzSplit, iVertSplit, pixWidth - iHorzSplit * 2, pixHeight - iVertSplit * 2 );
        QPixmap pix_6 = pix->copy ( pixWidth - iHorzSplit, iVertSplit, iHorzSplit, pixHeight - iVertSplit * 2 );

        QPixmap pix_7 = pix->copy ( 0, pixHeight - iVertSplit, iHorzSplit, iVertSplit );
        QPixmap pix_8 = pix->copy ( iHorzSplit, pixHeight - iVertSplit, pixWidth - iHorzSplit * 2, pixWidth - iHorzSplit * 2 );
        QPixmap pix_9 = pix->copy ( pixWidth - iHorzSplit, pixHeight - iVertSplit, iHorzSplit, iVertSplit );

        pix_2 = pix_2.scaled ( DstWidth - iHorzSplit * 2, iVertSplit, Qt::IgnoreAspectRatio ); //保持高度拉宽
        pix_4 = pix_4.scaled ( iHorzSplit, DstHeight - iVertSplit * 2, Qt::IgnoreAspectRatio ); //保持宽度拉高
        pix_5 = pix_5.scaled ( DstWidth - iHorzSplit * 2, DstHeight - iVertSplit * 2,
                               Qt::IgnoreAspectRatio ); //宽高都缩放
        pix_6 = pix_6.scaled ( iHorzSplit, DstHeight - iVertSplit * 2, Qt::IgnoreAspectRatio ); //保持宽度拉高
        pix_8 = pix_8.scaled ( DstWidth - iHorzSplit * 2, iVertSplit ); //保持高度拉宽


        QPixmap* resultImg = new QPixmap ( DstWidth, DstHeight );
        QPainter* painter = new QPainter ( resultImg );

        if ( !resultImg->isNull() ) {
            painter->drawPixmap ( 0, 0, pix_1 );
            painter->drawPixmap ( iHorzSplit, 0, pix_2 );
            painter->drawPixmap ( DstWidth - iHorzSplit, 0, pix_3 );

            painter->drawPixmap ( 0, iVertSplit, pix_4 );
            painter->drawPixmap ( iHorzSplit, iVertSplit, pix_5 );
            painter->drawPixmap ( DstWidth - iHorzSplit, iVertSplit, pix_6 );

            painter->drawPixmap ( 0, DstHeight - iVertSplit, pix_7 );
            painter->drawPixmap ( iHorzSplit, DstHeight - iVertSplit, pix_8 );
            painter->drawPixmap ( DstWidth - iHorzSplit, DstHeight - iVertSplit, pix_9 );
            painter->end();
        }

        return resultImg;
    }

    /*
     * 如果是个聊天气泡，四周的图片还能缩放吗？
     */
signals:

public slots:
};

#endif // QQTNINEPATCHWIDGET_H
