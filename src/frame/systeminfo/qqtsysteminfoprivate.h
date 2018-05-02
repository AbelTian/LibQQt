#ifndef QQTSYSTEMINFOPRIVATE_H
#define QQTSYSTEMINFOPRIVATE_H

#include <QObject>

class QQtSystemInfoPrivate : public QObject
{
    Q_OBJECT
public:
    explicit QQtSystemInfoPrivate(QObject *parent = nullptr);

signals:

public slots:
};

#endif // QQTSYSTEMINFOPRIVATE_H