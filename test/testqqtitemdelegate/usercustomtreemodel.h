#ifndef USERCUSTOMTREEMODEL_H
#define USERCUSTOMTREEMODEL_H

#include <qqtdicttreemodel.h>

enum ERfcSection
{
    RfcName,
    RfcUrl,
    RfcLocalUrl,
    RfcDownStatus,
    RfcDownTime,
    RfcDownProgress,

    RFCMax,
};

class UserCustomTreeModel : public QQtDictTreeModel
{
    Q_OBJECT

public:
    explicit UserCustomTreeModel ( QObject* parent = 0 )
        : QQtDictTreeModel ( parent ) {}
    virtual ~UserCustomTreeModel() {}
protected:

private:


    // QQtDictTreeModel interface
protected:
    virtual void packDictionaryToTreeModel ( const QQtDictionary& node, QStandardItem* pobject ) override;

    // QQtDictTreeModel interface
public:
    virtual void query ( QQtDictionary& dict ) override;

};

#endif // USERCUSTOMTREEMODEL_H

