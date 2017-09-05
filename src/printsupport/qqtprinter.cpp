#include "qqtprinter.h"
#include "stdlib.h"

QQTPrinter::QQTPrinter(QPrinter::PrinterMode mode) :
    QPrinter(mode)
{

}

void QQTPrinter::setOutputFileName(const QString &name)
{
    m_outputname = name;
    QPrinter::setOutputFileName(m_outputname);
}

void QQTPrinter::print()
{
    /*
     * 此处不会影响打印质量，不必再调试
     */
    QString cmd;
    QString pbm="./output.pbm";

    cmd = cmd.sprintf("gs -q -dBATCH -dSAFER -dQUIET -dNOPAUSE -sPAPERSIZE=a4 -r600*600 -sDEVICE=pbmraw -sOutputFile=%s %s", pbm.toLatin1().data(), m_outputname.toLatin1().data());
    system(cmd.toLatin1().data());

    cmd = cmd.sprintf("foo2zjs -z3 -p9 -r600*600 %s > /dev/usb/lp0", pbm.toLatin1().data());
    system(cmd.toLatin1().data());
}
