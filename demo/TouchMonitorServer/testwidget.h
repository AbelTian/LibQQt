#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>

class TestWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TestWidget ( QWidget* parent = nullptr );

signals:

public slots:
    // QWidget interface
protected:
    virtual void paintEvent ( QPaintEvent* event ) override;

    // QWidget interface
protected:
    virtual void resizeEvent ( QResizeEvent* event ) override;
};

#endif // TESTWIDGET_H
