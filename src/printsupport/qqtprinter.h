#ifndef _QQTPRINTER_H
#define _QQTPRINTER_H

#include <QPrinter>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtPrinter : public QPrinter
{
public:
    QQtPrinter ( PrinterMode mode = HighResolution );

    void setOutputFileName ( const QString& );
    void print();

private:
    QString m_outputname;
};

#endif // QQTPRINTER_H
