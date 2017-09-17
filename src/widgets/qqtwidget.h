#ifndef QPICWIDGET_H
#define QPICWIDGET_H

#include <QWidget>
#include <qqt-local.h>

namespace Ui {
class QQTWidget;
}

class QQTSHARED_EXPORT QQTWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QQTWidget(QWidget *parent = 0);
    ~QQTWidget();

    enum {
        QQTCENTER,
        QQTTILEDWIDTH,
        QQTTILEDHEIGHT,
        QQTZOOMWIDTH,
        QQTZOOMHEIGHT,
    };
    void setPixmap(QString pic = QString());
    void setType(quint32 type = 0) { m_type = type; }
private:
    Ui::QQTWidget *ui;
    QString m_pic;
    quint32 m_type;
    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);
};

#endif // QPICWIDGET_H
