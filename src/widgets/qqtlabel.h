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
    virtual void mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

    // QWidget interface
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
};

#endif // QQTLABEL_H
