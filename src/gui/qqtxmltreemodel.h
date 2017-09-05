#ifndef QQTXMLTREEMODEL_H
#define QQTXMLTREEMODEL_H

#include <qqttreemodel.h>
#include <QDomDocument>

class QQTXmlTreeModel : public QQTTreeModel
{
    Q_OBJECT
public:
    explicit QQTXmlTreeModel(QObject *parent = 0);


signals:

public slots:

    // QQTTreeModel interface
public:
    bool query(QString condition) override;
    void setFilePath(QString xmlfile) override;

protected:
       /**
     * @brief parseChildElement
     * @param element
     */
    void parseChildElement(const QDomElement &element, QStandardItem* itemParent = 0);

private:
    QDomDocument doc;
};

#endif // QQTXMLTREEMODEL_H
