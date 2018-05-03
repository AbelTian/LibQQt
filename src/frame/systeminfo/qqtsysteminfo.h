#ifndef QQTSYSTEMINFO_H
#define QQTSYSTEMINFO_H

#include <QObject>

class QQtSystemInfoPrivate;

class QQtSystemInfo : public QObject
{
    Q_OBJECT
public:
    explicit QQtSystemInfo ( QObject* parent = nullptr );

signals:

public slots:

private:
    Q_DECLARE_PRIVATE ( QQtSystemInfo )
    Q_DISABLE_COPY ( QQtSystemInfo )
};

#endif // QQTSYSTEMINFO_H
