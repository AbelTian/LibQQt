#ifndef QQTREPORT_H
#define QQTREPORT_H

#include "qqtword.h"

class QQTReport : public QQTWord
{
    Q_OBJECT
public:
    explicit QQTReport(QObject *parent = 0);

    void createSampleReport(const QString& head, const QString& foot, const QString& title,
                              const QTableView* table);

    void CreateComplexReport(const QString &head, const QString &foot,
                               const QString &title, const QList<QTableView *> &table);

signals:

public slots:


    // QQTWord interface
protected:

private:
};

QQTReport* QQTReportInstance(QObject* parent);

#endif // QQTREPORT_H
