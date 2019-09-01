#ifndef TESTSHADOWWIDGET_H
#define TESTSHADOWWIDGET_H

#include <QWidget>
#include <QLabel>

#include <QGraphicsEffect>

class TestShadowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TestShadowWidget ( QWidget* parent = 0 );
    virtual ~TestShadowWidget();

    // QWidget interface
protected:
    virtual void paintEvent ( QPaintEvent* event ) override;
};

#endif //TESTSHADOWWIDGET_H
