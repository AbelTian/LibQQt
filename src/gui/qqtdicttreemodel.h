#ifndef QQTDICTTREEMODEL_H
#define QQTDICTTREEMODEL_H

#include <qqttreemodel.h>
#include <qqtdictionary.h>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtDictTreeModel : public QQtTreeModel
{
    Q_OBJECT
public:
    explicit QQtDictTreeModel ( QObject* parent = 0 );


signals:

public slots:

    // QQtDictTreeModel interface
public:
    bool query ( QString condition ) override;
    void setFilePath ( QString dictfile ) override;

protected:

};

#endif // QQTDICTTREEMODEL_H
