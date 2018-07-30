#include "qqtprinter.h"
#include <QImage>
#include <QPainter>

QQtPrinter::QQtPrinter ( QPrinter::PrinterMode mode ) :
    QPrinter ( mode )
{
    //setup printer
    /**
      MIPS bug: you must use QQtPrinter(QPrinter::HighResolution)
      Other constructer won't work well
     */
    //QPrinter(QPrinter::HighResolution);
    setFullPage ( true );
    setColorMode ( QPrinter::Color );
    setPaperSize ( QPrinter::A4 );
    setOrientation ( QPrinter::Portrait );
    setOutputFormat ( QPrinter::PdfFormat );

#if 0
    //setup printer
    /**
      MIPS bug: you must use QQtPrinter(QPrinter::HighResolution)
      Other constructer won't work well
      */
    pr = new QQtPrinter ( QPrinter::HighResolution );
    pr->setFullPage ( true );
    pr->setColorMode ( QPrinter::Color );
    pr->setPaperSize ( QPrinter::A4 );
    pr->setOrientation ( QPrinter::Portrait );
    pr->setOutputFormat ( QPrinter::PdfFormat );
    /*
     * Font目标是打印纸上，所见即所得。
     * Pos目标不是纸上的，是屏幕上的，所以更换屏幕，必须更换DPI；
     * 这个数值是迪文屏上的标准分辨率，打印机使用会失真；
     * 迪文View 142,138 //PCView 96 //打印机View 1200
     * 打印机分辨率1200不会失真，绘图必须进行坐标变换。
     * 数值增大，DrawText可用空间减小甚至切掉一部分
     */
#ifdef __EMBEDDED_LINUX__
    /*
     * 这是实验结果，和理论结果不符合。
     */
    logicalDpiX = 136;
    logicalDpiY = 156;
#else
    /*
     * 这个值是理论值，绘图格子比较大
     */
    logicalDpiX = 96;
    logicalDpiY = 96;
#endif
    //1200 9917,14033 printerRect 固定
    //116  958,1356 sceneRect
    //142  1113,1660 sceneRect
    pline() << pr->logicalDpiX() << pr->logicalDpiY();
    pline()  << logicalDpiX << logicalDpiY << pr->pageRect() << sceneRect;
    pline() << pr->paperRect ( QPrinter::DevicePixel );
    pline() << pr->paperRect ( QPrinter::Millimeter );
    pline() << pr->paperRect ( QPrinter::Point );
    pline() << pr->paperRect ( QPrinter::Inch );
    pline() << pr->paperRect ( QPrinter::Pica );
    pline() << pr->paperRect ( QPrinter::Didot );
    pline() << pr->paperRect ( QPrinter::Cicero );
    QRect rect = pr->paperRect();
    sceneRect = QRectF ( 0.0, 0.0, logicalDpiX * rect.width() / pr->logicalDpiX(),
                         logicalDpiY * rect.height() / pr->logicalDpiY() );
#endif
}

void QQtPrinter::setOutputFileName ( const QString& name )
{
    m_outputname = name;
    QPrinter::setOutputFileName ( m_outputname );
}

void QQtPrinter::generateToPdfFile ( const QList<QImage>& sourcePapers , QRectF sourceRect )
{
    if ( sourceRect == QRectF() )
        sourceRect = paperRect();

    // print pdf
    QPainter p ( this );

    QListIterator<QImage> itor ( sourcePapers );
    while ( itor.hasNext() )
    {
        const QImage& page = itor.next();
        p.drawImage ( paperRect(), page, sourceRect );
        if ( itor.hasNext() )
            newPage();
    }
}

void QQtPrinter::printPdf()
{
    /*
     * 此处不会影响打印质量，不必再调试
     */
    QString cmd;
    QString pbm = "./output.pbm";

    cmd = cmd.sprintf ( "gs -q -dBATCH -dSAFER -dQUIET -dNOPAUSE -sPAPERSIZE=a4 -r600*600 -sDEVICE=pbmraw -sOutputFile=%s %s",
                        pbm.toLatin1().data(), m_outputname.toLatin1().data() );
    system ( cmd.toLatin1().data() );

    cmd = cmd.sprintf ( "foo2zjs -z3 -p9 -r600*600 %s > /dev/usb/lp0", pbm.toLatin1().data() );
    system ( cmd.toLatin1().data() );
}
