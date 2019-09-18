#ifndef QQTWIDGET_H
#define QQTWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QImage>

#include <qqt-local.h>
#include <qqtcore.h>

/*
 * QSS美化，和QQtWidget图片背景不能共存
 * QSS部分影响QQtWidget，比如Size等
*/
class QQTSHARED_EXPORT QQtWidget : public QWidget
{
    Q_OBJECT

public:
    enum ImageStyle
    {
        /**
         * 整个居中,全面缩放显示
         */
        QQTCENTER,
        /**
         * 切
         * 从左上
         * 会产生label的效果，左右按照rect长，但是不缩放形状
         **/
        QQTTILEDWIDTH,
        QQTTILEDHEIGHT,
        QQTTILED,

        /**
         * 缩放
         * 忽略长宽比
         */
        QQTZOOMWIDTH,
        QQTZOOMHEIGHT,
        QQTZOOM,

        /**
         * 缩放
         * 保持长宽比
         */
        QQTZOOMWIDTH_KEEPASPECTRATIO,
        QQTZOOMHEIGHT_KEEPASPECTRATIO,
        QQTZOOM_KEEPASPECTRATIO,

        QQTIMAGESTYLEMAX
    };

public:
    explicit QQtWidget ( QWidget* parent = 0 );
    virtual ~QQtWidget();

    ImageStyle imageStyle();
    void setImageStyle ( ImageStyle style = QQTCENTER );

    void setPixmap ( const QImage& image );
    void setPixmap ( const QString& pic );
    void setPixmap ( const QPixmap& pixmap );

    QImage image();
    void setImage ( const QImage& image );

    // QWidget interface
protected:
    void paintEvent ( QPaintEvent* ) override;

private:
    ImageStyle m_style;
    /*pixmap是必要的。绘图用pixmap。*/
    /*内部没有使用QPixmap存储，因为如果缩放widget，pixmap就没办法了，img有*/
    /*内部对QIcon的使用删除了，icon不是必要的。*/
    QImage mImage;
};

#endif // QWIDGET_H
