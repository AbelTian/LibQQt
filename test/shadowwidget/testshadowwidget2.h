#ifndef TESTSHADOWWIDGET2_H
#define TESTSHADOWWIDGET2_H

#include <QWidget>
#include <QLabel>

#include <QGraphicsEffect>

class TestShadowWidget2 : public QWidget
{
    Q_OBJECT
public:
    explicit TestShadowWidget2 ( QWidget* parent = 0 );
    virtual ~TestShadowWidget2();

    // QWidget interface
protected:
    virtual void paintEvent ( QPaintEvent* event ) override;
};

#endif //TESTSHADOWWIDGET2_H
