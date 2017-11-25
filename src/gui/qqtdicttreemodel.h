#ifndef QQTDICTTREEMODEL_H
#define QQTDICTTREEMODEL_H

#include <qqttreemodel.h>
#include <qqt-local.h>
#include <qqtdictionary.h>

class QQTSHARED_EXPORT QQtDictTreeModel : public QQtTreeModel
{
    Q_OBJECT
public:
    explicit QQtDictTreeModel ( QObject* parent = 0 );


signals:

public slots:

    // QQtJsonTreeModel interface
public:
    bool query ( QString condition ) override;
    void setFilePath ( QString dictfile ) override;

protected:

};

#endif // QQTDICTTREEMODEL_H
