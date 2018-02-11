#ifndef TEMPCLASS_H
#define TEMPCLASS_H

#include <QObject>

class TempClass : public QObject
{
    Q_OBJECT
public:
    explicit TempClass ( QObject* parent = nullptr ) ;

signals:

public slots:
};

#endif // TEMPCLASS_H
