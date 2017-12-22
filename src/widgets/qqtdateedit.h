#ifndef QQTDATEEDIT_H
#define QQTDATEEDIT_H

#include <QDateEdit>

class QQtDateEdit : public QDateEdit
{
    Q_OBJECT
public:
    explicit QQtDateEdit ( QWidget* parent = nullptr );
    virtual ~QQtDateEdit() {}

    /*Qt默认Protected，这个函数，在QQtInput要使用这个函数，所以在这里公开出来*/
    /*QQtInput不支持Qt默认的QDateEdit，QDateTimeEdit，QTimeEdit，QSpinBox，QDoubleSpinBox，必须使用这些个QQt继承下来的类*/
    QLineEdit* lineEdit() const { return QDateEdit::lineEdit(); }
    void setLineEdit ( QLineEdit* edit ) { return QDateEdit::setLineEdit ( edit ); }

signals:

public slots:
};

#endif // QQTDATEEDIT_H
