#ifndef QQTDOUBLESPINBOX_H
#define QQTDOUBLESPINBOX_H

#include <QDoubleSpinBox>
#include <qqtcore.h>
#include <qqtcore.h>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    explicit QQtDoubleSpinBox ( QWidget* parent = nullptr );
    virtual ~QQtDoubleSpinBox() {}

    /*QQtInput不支持Qt默认的QDateEdit，QDateTimeEdit，QTimeEdit，QSpinBox，QDoubleSpinBox，必须使用这些个QQt继承下来的类*/
    /*Qt默认Protected，这个函数，在QQtInput要使用这个函数，所以在这里公开出来*/
    QLineEdit* lineEdit() const { return QDoubleSpinBox::lineEdit(); }
    void setLineEdit ( QLineEdit* edit ) { return QDoubleSpinBox::setLineEdit ( edit ); }

signals:

public slots:
};

#endif // QQTDOUBLESPINBOX_H
