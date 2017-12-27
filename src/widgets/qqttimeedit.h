#ifndef QQTTIMEEDIT_H
#define QQTTIMEEDIT_H

#include <QTimeEdit>
#include <qqtcore.h>

class QQtTimeEdit : public QTimeEdit
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
