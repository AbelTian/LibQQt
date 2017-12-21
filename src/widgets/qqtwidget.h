#ifndef QQTWIDGET_H
#define QQTWIDGET_H

#include <QWidget>
#include <QTimer>
#include <qqt-local.h>

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
    void setPixmap ( QString pic = QString() );
    void setType ( ImageStyle style = QQTCENTER ) { m_style = style; }

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
    QString m_pic;
    quint32 m_style;
    QTimer* m_lcTimer;
};

#endif // QPICWIDGET_H
