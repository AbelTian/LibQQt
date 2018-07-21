#ifndef QQTTIMEEDIT_H
#define QQTTIMEEDIT_H

#include <QTimeEdit>
#include <qqtcore.h>
#include <qqtcore.h>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtTimeEdit : public QTimeEdit
{
    Q_OBJECT
public:
    explicit QQtTimeEdit ( QWidget* parent = nullptr );
    virtual ~QQtTimeEdit() {}

    /*QQtInput不支持Qt默认的QDateEdit，QDateTimeEdit，QTimeEdit，QSpinBox，QDoubleSpinBox，必须使用这些个QQt继承下来的类*/
    /*Qt默认Protected，这个函数，在QQtInput要使用这个函数，所以在这里公开出来*/
    QLineEdit* lineEdit() const { return QTimeEdit::lineEdit(); }
    void setLineEdit ( QLineEdit* edit ) { return QTimeEdit::setLineEdit ( edit ); }

signals:

public slots:
};

#endif // QQTTIMEEDIT_H
