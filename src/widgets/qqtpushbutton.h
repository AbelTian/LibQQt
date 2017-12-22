#ifndef QQTPUSHBUTTON_H
#define QQTPUSHBUTTON_H

#include <QPushButton>
#include "qqtwidgets.h"
#include <qqt-local.h>
#include "qqtwidgets.h"
#include <QTimer>

class QQTSHARED_EXPORT QQtPushButton : public QPushButton
{
    Q_OBJECT

public:
    explicit QQtPushButton ( QWidget* parent = 0 );
    virtual ~QQtPushButton();

    /*
     * QQtPushButton [] = 不能正常运算 所以采用这种形式。
     */
    inline TBtnIconTable& iconTable() { return m_pixmap; }
    inline EBtnStatus btnStatus() const { return state; }
    inline void setRing ( bool op = false ) { ring = op; }

signals:
    void longClick();

private:
    EBtnStatus state;
    TBtnIconTable m_pixmap;
    bool ring;
    QTimer* m_lcTimer;

    // QWidget interface
protected:
    virtual void paintEvent ( QPaintEvent* ) override;

    // QWidget interface
protected:
    virtual void mousePressEvent ( QMouseEvent* ) override;
    virtual void mouseReleaseEvent ( QMouseEvent* ) override;
    virtual void enterEvent ( QEvent* ) override;
    virtual void leaveEvent ( QEvent* ) override;
    virtual void changeEvent ( QEvent* e ) override;

    // QWidget interface
protected:
    void enabledChange ( bool );
protected slots:
    void slot_timeout();
};

#endif // QQTPUSHBUTTON_H
