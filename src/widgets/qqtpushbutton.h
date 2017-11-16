#ifndef QQTPUSHBUTTON_H
#define QQTPUSHBUTTON_H

#include <QPushButton>
#include "qqtwidgets.h"
#include <qqt-local.h>
#include "qqtwidgets.h"

class QQTSHARED_EXPORT QQtPushButton : public QPushButton
{
    Q_OBJECT

public:
    explicit QQtPushButton(QWidget* parent = 0);
    ~QQtPushButton();

    /*
     * QQtPushButton [] = 不能正常运算 所以采用这种形式。
     */
    inline TBtnIconTable& iconTable() { return m_pixmap; }
    inline EBtnStatus btnStatus() const { return state; }
    inline void setRing(bool op = false) { ring = op; }
private:
    EBtnStatus state;
    TBtnIconTable m_pixmap;
    bool ring;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent*);

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);
    void changeEvent(QEvent* e);

    // QWidget interface
protected:
    void enabledChange(bool);
};

#endif // QQTPUSHBUTTON_H
