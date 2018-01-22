#ifndef QQTWIDGET_H
#define QQTWIDGET_H

#include <qqt-local.h>
#include <qqtcore.h>

#include <QWidget>
#include <QTimer>
#include <QImage>

class QQTSHARED_EXPORT QQtWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QQtWidget ( QWidget* parent = 0 );
    virtual ~QQtWidget();

    enum ImageStyle
    {
        QQTCENTER,
        /*
         * 会产生label的效果，左右按照rect长，但是不缩放形状
         **/
        QQTTILEDWIDTH,
        QQTTILEDHEIGHT,
        QQTZOOMWIDTH,
        QQTZOOMHEIGHT,
    };
    void setType ( ImageStyle style = QQTCENTER ) { m_style = style; }

    void setPixmap ( const QString& pic = QString() );
    void setPixmap ( const QPixmap& pixmap );
    void setPixmap ( const QImage& image );

signals:
    void click();
    void doubleClick();
    void longClick();

    // QWidget interface
protected:
    void paintEvent ( QPaintEvent* ) override;

    // QWidget interface
protected:
    virtual void mousePressEvent ( QMouseEvent* event ) override;
    virtual void mouseReleaseEvent ( QMouseEvent* event ) override;
    virtual void mouseDoubleClickEvent ( QMouseEvent* event ) override;

protected slots:
    void slot_timeout();

private:
    quint32 m_style;
    QTimer* m_lcTimer;
    /*pixmap是必要的。绘图用pixmap。*/
    /*内部没有使用QPixmap存储，因为如果缩放widget，pixmap就没办法了，img有*/
    /*内部对QIcon的使用删除了，icon不是必要的。*/
    QImage mImg;
};

#endif // QPICWIDGET_H
