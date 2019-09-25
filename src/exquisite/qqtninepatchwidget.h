#ifndef QQTNINEPATCHWIDGET_H
#define QQTNINEPATCHWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QImage>
#include <qqtcore.h>
#include <qqt-local.h>

/**
 * @brief The QQtNinePatchWidget class
 * 九宫格图片
 *
 * 输入图片，
 * 设置边上的高度和宽度，就可以自动缩放到画布上显示。
 * 默认是不缩放的，ImageStyle_Zoom。
 */
class QQTSHARED_EXPORT QQtNinePatchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QQtNinePatchWidget ( QWidget* parent = nullptr );
    virtual ~QQtNinePatchWidget();

    void setImage ( const QImage& image );
    void setImage ( const QString& filename );
    void setImage ( const QPixmap& pixmap );
    QImage& image();

    void setCornerSize ( QSize size );
    void setCornerHeight ( int height );
    void setCornerWidth ( int width );
protected:

signals:

public slots:

    // QWidget interface
protected:
    virtual void paintEvent ( QPaintEvent* event ) override;

private:
    QImage mImg;
    QSize mCorner;
};

#endif // QQTNINEPATCHWIDGET_H
