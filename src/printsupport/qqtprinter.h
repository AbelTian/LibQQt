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

    //把QImage列表输出(投影)到上边的位置。
    //QQtWord会输出这个list。
    //如果sourceRect为空,那么按照打印机的PaperRect,这说明sourcePaper使用了打印机的分辨率1200.
    //只要纸张类型设置的正确,比如都是A4纸那样的长宽比,那么就不会失真.关键在长宽比和分辨率.
    //分辨率决定是否失真. 长宽比决定是否变形.
    void generateToPdfFile ( const QList<QImage>& sourcePapers, QRectF sourceRect = QRectF() );

    //嵌入式系统里打印到打印机
    void printPdf();

    //输出到打印机
    //内部实现

    //桌面打印到打印机
    //内部实现

private:
    QString m_outputname;
};

#endif // QQTPRINTER_H
