#ifndef QQTSQLTREEMODEL_H
#define QQTSQLTREEMODEL_H

#include <qqttreemodel.h>
#include <qqttablemodel.h>
#include <QList>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQTSqlTreeModel : public QQTTreeModel
{
    Q_OBJECT
public:
    explicit QQTSqlTreeModel(QObject* parent = 0);

    //TODO:

    // QQTVirtualTreeModel interface
public:
    bool query(QString condition) Q_DECL_OVERRIDE;
    void setFilePath(QString dbname) Q_DECL_OVERRIDE;

protected:
    bool parseDatabase();
    bool parseTable(QString tableName);
private:
    QSqlDatabase m_db;
    QList<QQTTableModel*> tableModelList;
};

#endif // QQTSQLTREEMODEL_H
