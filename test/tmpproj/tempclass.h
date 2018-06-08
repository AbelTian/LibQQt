#ifndef TEMPCLASS_H
#define TEMPCLASS_H

#include <QObject>
#include <qqtcore.h>
#include <qqt-local.h>

class QQTSHARED_EXPORT TemplateClass : public QObject
{
    Q_OBJECT
public:
    explicit TemplateClass ( QObject* parent = nullptr ) : QObject ( parent ) {

    }

signals:

public slots:
};

#endif // TEMPCLASS_H
