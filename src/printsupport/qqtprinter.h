#ifndef QQTPRINTER_H
#define QQTPRINTER_H

#include <QPrinter>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtPrinter : public QPrinter
{
public:
    explicit QQtPrinter ( PrinterMode mode = HighResolution );

    //输出到文件
    void setOutputFileName ( const QString& );

    //把QImage列表输出到上边的位置。QQtWord会输出这个list。
    void generateToFile ( const QList<QImage>& imgs );

    //嵌入式系统里打印到打印机
    void print();

    //输出到打印机
    //内部实现

    //桌面打印到打印机
    //内部实现

private:
    QString m_outputname;
};

#endif // QQTPRINTER_H
