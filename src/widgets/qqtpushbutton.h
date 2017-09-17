#ifndef QQTPushButton_H
#define QQTPushButton_H

#include <QPushButton>
#include "qqtwidgets.h"
#include <qqt-local.h>

namespace Ui {
class QQTPushButton;
}

class QQTSHARED_EXPORT QQTPushButton : public QPushButton
{
    Q_OBJECT

public:
    explicit QQTPushButton(QWidget *parent = 0);
    ~QQTPushButton();

    /*
     * QQTPushButton [] = 不能正常运算 所以采用这种形式。
     */
    TBtnIconTable& iconTable() { return m_pixmap; }

private:
    Ui::QQTPushButton *ui;
    int state;
    TBtnIconTable m_pixmap;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void changeEvent(QEvent *e);

    // QWidget interface
protected:
    void enabledChange(bool);
};

#endif // QQTPushButton_H
