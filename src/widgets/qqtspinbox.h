#ifndef QQTSPINBOX_H
#define QQTSPINBOX_H

#include <QSpinBox>
#include <qqtcore.h>
#include <qqtcore.h>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtSpinBox : public QSpinBox
{
    Q_OBJECT
public:
    explicit QQtSpinBox ( QWidget* parent = nullptr );
    virtual ~QQtSpinBox() {}

    /*QQtInput不支持Qt默认的QDateEdit，QDateTimeEdit，QTimeEdit，QSpinBox，QDoubleSpinBox，必须使用这些个QQt继承下来的类*/
    /*Qt默认Protected，这个函数，在QQtInput要使用这个函数，所以在这里公开出来*/
    QLineEdit* lineEdit() const { return QSpinBox::lineEdit(); }
    void setLineEdit ( QLineEdit* edit ) { return QSpinBox::setLineEdit ( edit ); }

signals:

public slots:
};

#endif // QQTSPINBOX_H
