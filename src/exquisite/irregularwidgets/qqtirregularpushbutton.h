#ifndef QQTIRREGULARPUSHBUTTON_H
#define QQTIRREGULARPUSHBUTTON_H

#include <qqtpushbutton.h>
#include <qqt-local.h>

/**
 * @brief The QQtIrregularPushbutton class
 * 不规则按钮
 *
 * 功能约束：其他5个状态的图片姿态必须和NORMAL图片姿态一致。
 */
class QQTSHARED_EXPORT QQtIrregularPushbutton : public QQtPushButton
{
    Q_OBJECT
public:
    QQtIrregularPushbutton ( QWidget* parent = 0 );
    virtual ~QQtIrregularPushbutton();

    // QWidget interface
protected:
    virtual void resizeEvent ( QResizeEvent* event ) override;
};

#endif //QQTIRREGULARPUSHBUTTON_H
