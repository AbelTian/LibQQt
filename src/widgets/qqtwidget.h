#ifndef QPICWIDGET_H
#define QPICWIDGET_H

#include <QWidget>
#include <qqt-local.h>

namespace Ui
{
class QQtWidget;
}

class QQTSHARED_EXPORT QQtWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QQtWidget(QWidget* parent = 0);
    ~QQtWidget();

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
    void setPixmap(QString pic = QString());
    void setType(ImageStyle style = QQTCENTER) { m_style = style; }
signals:
    void click();
    void doubleClick();

private:
    Ui::QQtWidget* ui;
    QString m_pic;
    quint32 m_style;
    // QWidget interface
protected:
    void paintEvent(QPaintEvent*) override;

    // QWidget interface
protected:
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent* event) override;
};

#endif // QPICWIDGET_H
