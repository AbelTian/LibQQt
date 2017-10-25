#ifndef QQTLABEL_H
#define QQTLABEL_H

#include <QLabel>
#include <qqtcore.h>

class QQtLabel : public QLabel
{
    Q_OBJECT
public:
    explicit QQtLabel(QWidget* parent = nullptr);

signals:
    void click();
    void doubleClick();
public slots:

    // QWidget interface
protected:
    virtual void mouseReleaseEvent(QMouseEvent* event) override;

    // QWidget interface
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent* event) override;
};

#endif // QQTLABEL_H
