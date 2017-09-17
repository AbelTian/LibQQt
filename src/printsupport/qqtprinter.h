#ifndef _QQTPRINTER_H
#define _QQTPRINTER_H

#include <QPrinter>
#include <qqt.h>

class QQTSHARED_EXPORT QQTPrinter : public QPrinter
{
public:
    QQTPrinter(PrinterMode mode = HighResolution);

    void setOutputFileName(const QString &);
    void print();

private:
    QString m_outputname;
};

#endif // QQTPRINTER_H
