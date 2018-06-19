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

    QLineEdit* lineEdit() const { return QTimeEdit::lineEdit(); }
    void setLineEdit ( QLineEdit* edit ) { return QTimeEdit::setLineEdit ( edit ); }

signals:

public slots:
};

#endif // QQTTIMEEDIT_H
