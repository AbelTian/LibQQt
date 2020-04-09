#ifndef QQTPUSHBUTTON_H
#define QQTPUSHBUTTON_H

#include <QPushButton>
#include <QTimer>

#include "qqtcore.h"
#include <qqt-local.h>

#include "qqtwidgets.h"

/**
 * @brief The QQtPushButton class
 * 原装Button在嵌入式板子上无法处理掉Hover问题。
 * QSS里设置也可以，把HOVER设置为和NORMAL一样，只是QSS代码量过大。
 * 原装Pushbutton需要设置setFlat以防止出现default button框。
 */
class QQTSHARED_EXPORT QQtPushButton : public QPushButton
{
    Q_OBJECT

public:
    explicit QQtPushButton ( QWidget* parent = 0 );
    virtual ~QQtPushButton();

    QImage stateImage ( int index );
    void setStateImage ( int index, const QImage& image );

    //normal, press; uncheck, check; [0,1];
    void setNormalImage ( const QImage& normal, const QImage& press );
    //hover; [2];
    void setHoverImage ( const QImage& hover );
    //disable; [4];
    void setDisableImage ( const QImage& disable );

    void setEnabled ( bool );
    void setDisabled ( bool );

    const TBtnImageTable& imageTable() const;
    TBtnImageTable& imageTable();

protected:
    void setWorkState ( int index );
    int workState() const;
    virtual void translateImage();
    virtual void setImage ( const QImage& image );
protected:

private:
    EBtnStatus mWorkState;
    TBtnImageTable mImageTable;
    QImage mImage;

    // QWidget interface
protected:
    virtual void mousePressEvent ( QMouseEvent* event ) override;
    virtual void mouseReleaseEvent ( QMouseEvent* event ) override;
    virtual void enterEvent ( QEvent* event ) override;
    virtual void leaveEvent ( QEvent* event ) override;

    // QWidget interface
protected:
    virtual void paintEvent ( QPaintEvent* event ) override;

};

#endif // QQTPUSHBUTTON_H
