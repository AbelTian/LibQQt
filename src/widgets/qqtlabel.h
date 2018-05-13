#ifndef QQTLABEL_H
#define QQTLABEL_H

#include <QLabel>
#include <QTimer>
#include <qqtcore.h>

class QQtLabel : public QLabel
{
    Q_OBJECT
public:
    explicit QQtLabel ( QWidget* parent = nullptr );
    virtual ~QQtLabel() {}
signals:
    void click();
    void doubleClick();
    void longClick();

public slots:

    // QWidget interface
protected:
    virtual void mouseReleaseEvent ( QMouseEvent* event ) override;

    // QWidget interface
protected:
    virtual void mouseDoubleClickEvent ( QMouseEvent* event ) override;

protected slots:
    void slot_timeout();

    // QWidget interface
protected:
    virtual void mousePressEvent ( QMouseEvent* event ) override;

private:
    QTimer* m_lcTimer;
};

#endif // QQTLABEL_H
