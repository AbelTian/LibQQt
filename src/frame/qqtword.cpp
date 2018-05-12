#include "qqt-qt.h"
#include "qqtcore.h"
#include "qqtprinter.h"
#include "qqtgraphicsscene.h"
#include "qqtgraphicsitem.h"
#include "qqtword.h"

QQtWord::QQtWord(QObject* parent) :
    QObject(parent),
    fmt(0), headerFmt(0), titleFmt(0), title2Fmt(0), mainFmt(0)
{
    //setup printer
    /**
      MIPS bug: you must use QQtPrinter(QPrinter::HighResolution)
      Other constructer won't work well
      */
    pr = new QQtPrinter(QPrinter::HighResolution);
    pr->setFullPage(true);
    pr->setColorMode(QPrinter::Color);
    pr->setPaperSize(QPrinter::A4);
    pr->setOrientation(QPrinter::Portrait);
    pr->setOutputFormat(QPrinter::PdfFormat);

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

    QRect rect = pr->paperRect();
    sceneRect = QRectF(0.0, 0.0, logicalDpiX * rect.width() / pr->logicalDpiX(),
                       logicalDpiY * rect.height() / pr->logicalDpiY());

#if 0
    //1200 9917,14033 printerRect 固定
    //116  958,1356 sceneRect
    //142  1113,1660 sceneRect
    pline() << pr->logicalDpiX() << pr->logicalDpiY();
    pline()  << logicalDpiX << logicalDpiY << pr->pageRect() << sceneRect;
    pline() << pr->paperRect(QPrinter::DevicePixel);
    pline() << pr->paperRect(QPrinter::Millimeter);
    pline() << pr->paperRect(QPrinter::Point);
    pline() << pr->paperRect(QPrinter::Inch);
    pline() << pr->paperRect(QPrinter::Pica);
    pline() << pr->paperRect(QPrinter::Didot);
    pline() << pr->paperRect(QPrinter::Cicero);
#endif

    m_mainFont = QApplication::font();

    if (mainFmt)
        delete mainFmt;

    mainFmt = new QFontMetrics(m_mainFont);
    m_titleFont = QApplication::font();
    m_titleFont.setPointSize(22);

    if (titleFmt)
        delete titleFmt;

    titleFmt = new QFontMetrics(m_titleFont);
    m_title2Font = QApplication::font();;
    m_title2Font.setPointSize(16);

    if (title2Fmt)
        delete title2Fmt;

    title2Fmt = new QFontMetrics(m_title2Font);

    setMargin();
    setHeaderSize();
    setFooterSize();

    setFont();
    setHeaderFont();
    setLineSpacing();

    setHeaderLine();
    setFooterLine();

    initWord();
}

void QQtWord::setMargin(qreal left, qreal right, qreal top, qreal botoom)
{
    leftMargin = 134.6;
    rightMargin = 134.6;
    topMargin = 177.7;
    bottomMargin = 177.7;
}

QRectF QQtWord::clientRectF()
{
    return QRectF(leftMargin, topMargin,
                  sceneRect.width() - leftMargin - rightMargin,
                  sceneRect.height() - topMargin - bottomMargin);
}

QRectF QQtWord::paperRect()
{
    return QRectF(0, 0,
                  sceneRect.width(),
                  sceneRect.height());
}

void QQtWord::setFont(QFont font)
{
    //normal font 11
    m_font = QApplication::font();

    if (fmt)
        delete fmt;

    fmt = new QFontMetrics(m_font);
}

void QQtWord::setLineSpacing(qreal spacing)
{
    /*
     * 单倍行距
     */
    mainHeight = mainFmt->height();
    titleHeight = titleFmt->height();
    title2Height = title2Fmt->height();
    headerHeight = headerFmt->height();

    mainSpacing = mainFmt->height() * 2;
    titleSpacing = titleFmt->height() * 2;
    title2Spacing = title2Fmt->height() * 2;
    headerSpacing = headerFmt->height() * 1;
}

void QQtWord::addText(const QString& text, QFont font, Qt::Alignment align, QPointF point)
{
    QFontMetrics fmt = QFontMetrics(font);
    int spacing = fmt.height() * 2;
    int height = fmt.height();
    int width = fmt.width(text);

    //pline() << font.pointSize() << fmt.height();

    adjustdy(height + spacing);

    QQtGraphicsTextItem* item = pageScene->addText(text, font);

    if (align & Qt::AlignLeft)
        item->moveBy(dx, dy + height);
    else if (align & Qt::AlignRight)
        item->moveBy(xpos2 - width, dy + height);
    else if (align & Qt::AlignHCenter)
        item->moveBy((pageScene->width() / 2) - (width / 2), dy + height);

    dy += height + spacing;
}

void QQtWord::addSignoffText(const QString& text, QFont font)
{
    adjustdy(mainHeight + mainSpacing);

    int ddy = dy;

    dy = ypos2 - ((mainHeight + mainSpacing) * 2);

    addText(text, m_mainFont, Qt::AlignRight);

    dy = ddy;
}

void QQtWord::addTable(const QTableView* table, QPointF pos)
{
    Q_ASSERT(table);

    QAbstractItemModel* model = table->model();
    QFont tableFont = table->font();
    QFontMetrics tableFmt = QFontMetrics(tableFont);

    int tableRowHeight = 0;

    if (!table->horizontalHeader()->isHidden())
    {
        tableRowHeight = table->horizontalHeader()->height();
        adjustdy(tableRowHeight);

        for (int col = 0; col < model->columnCount(); col++)
        {
            int logicalIndex = table->horizontalHeader()->logicalIndex(col);
            int actColSize = table->columnWidth(logicalIndex);

            if (table->horizontalHeader()->isSectionHidden(col))
                continue;

            QPen pen(Qt::gray, 0.1);
            QBrush brush(QColor(255, 250, 250));
            //QBrush brush(tableView->horizontalHeader()->palette().background());
            pageScene->addRect(dx, dy, actColSize, tableRowHeight, pen, brush);

            QString txt = model->headerData(logicalIndex, Qt::Horizontal, Qt::DisplayRole).toString();
            txt = tableFmt.elidedText(txt, Qt::ElideRight, actColSize - 2);
            QQtGraphicsTextItem* item = pageScene->addText(txt, tableFont);
            item->moveBy(dx, dy);
            dx += actColSize;
        }

        dy += tableRowHeight;
    }

    QHash<int, ESpanFlags> spans = tableSpans(table);
    QHashIterator<int, ESpanFlags> it(spans);

    while (0 && it.hasNext())
    {
        it.next();
        pline() << it.key() << it.value();
        pline() << it.value().testFlag(ESpanLeft) <<
                it.value().testFlag(ESpanTop)  <<
                it.value().testFlag(ESpanRight) <<
                it.value().testFlag(ESpanBottom) <<
                it.value().testFlag(ESpanMiddle) ;
    }

    //Table rows
    QPen pen(Qt::gray, 0.1);
    QBrush brush(Qt::gray, Qt::SolidPattern);
    int row = 0;

    for (;;)
    {
        if (row >= model->rowCount())
        {
            break;
        }

        if (table->isRowHidden(row))
            continue;

        tableRowHeight = table->rowHeight(row);
        adjustdy(tableRowHeight);

        for (int col = 0; col < model->columnCount(); col++)
        {
            int logicalIndex = table->horizontalHeader()->logicalIndex(col);
            int actColSize = table->columnWidth(logicalIndex);

            if (table->isColumnHidden(col))
                continue;

            int point = row * model->columnCount() + col;
            ESpanFlags flags = spans.value(point);

            QPen pen(Qt::gray, 0.1);
            QBrush brush(table->palette().window());
            bool balt = table->alternatingRowColors();

            if (ESpanNone == flags)
            {
                if (balt)
                {
                    int modulo = row % 2;

                    if (modulo != 0)
                    {
                        //rectangle grey
                        pageScene->addRect(dx, dy, actColSize, tableRowHeight, pen, brush);
                    }
                    else
                    {
                        pageScene->addRect(dx, dy, actColSize, tableRowHeight, pen);
                    }
                }
                else
                {
                    pageScene->addRect(dx, dy, actColSize, tableRowHeight, pen);
                }
            }

            if (flags.testFlag(ESpanLeft))
                pageScene->addLine(dx, dy, dx, dy + tableRowHeight, pen);

            if (flags.testFlag(ESpanTop))
                pageScene->addLine(dx, dy, dx + actColSize, dy, pen);

            if (flags.testFlag(ESpanRight))
                pageScene->addLine(dx + actColSize, dy, dx + actColSize, dy + tableRowHeight, pen);

            if (flags.testFlag(ESpanBottom))
                pageScene->addLine(dx, dy + tableRowHeight, dx + actColSize, dy + tableRowHeight, pen);

            if (ESpanNone == flags ||
                (flags.testFlag(ESpanLeft) && flags.testFlag(ESpanTop)))
            {
                QString txt = model->data(model->index(row, logicalIndex)).toString();
                txt = tableFmt.elidedText(txt, Qt::ElideRight, actColSize - 2);
                QQtGraphicsTextItem* item = pageScene->addText(txt, tableFont);
                item->moveBy(dx, dy);
            }

            dx += actColSize;
        }

        row++;
        dy += tableRowHeight;
        dx = xpos;
    }
}

int QQtWord::pageNum() { return pageSceneVector.size(); }

void QQtWord::exportPdf(const QString& pdf)
{
    // setup printer
    pr->setOutputFileName(pdf);

    // print pdf
    QPainter p(pr);

    QQtGraphicsScene* pageScene = 0;

    foreach (pageScene, pageSceneVector)
    {

        pageScene->render(&p, pr->paperRect(), sceneRect);

        if (pageScene != pageSceneVector.last())
            pr->newPage();
    }
}

QQtGraphicsScene* QQtWord::getPage(int num)
{
    if (num < 1 || num > pageSceneVector.size())
        return NULL;

    return pageSceneVector.at(num - 1);
}

void QQtWord::print()
{
    pr->print();
}

void QQtWord::setHeaderFont(QFont font)
{
    //header font
    m_headerFont = QApplication::font();;
    m_headerFont.setPointSize(9);

    if (headerFmt)
        delete headerFmt;

    headerFmt = new QFontMetrics(m_headerFont);
}

void QQtWord::setHeaderSize(qreal size)
{
    headerSize = 70;
}

void QQtWord::setHeaderLine(bool show)
{

}

void QQtWord::setHeaderText(const QString& text, QFont font, Qt::Alignment align)
{
    headerText = text;
    paintPageHeader();
}

void QQtWord::setFooterSize(qreal size)
{
    footerSize = 70;
}

QFont QQtWord::font() { return m_font; }

void QQtWord::setFooterLine(bool show)
{
    Q_UNUSED(show)
}

void QQtWord::setFooterText(const QString& text, QFont font, Qt::Alignment align)
{
    Q_UNUSED(font)
    Q_UNUSED(align)
    footerText = text;
    paintPageFooter();
}

void QQtWord::initWord()
{
    while (! pageSceneVector.isEmpty())
    {
        QQtGraphicsScene* pageScene = pageSceneVector.first();
        pageScene->clear();
        delete pageScene;
        pageSceneVector.remove(0);
    }

    headerText = "";
    footerText = "";
    createFrame();
}

void QQtWord::adjustdy(qreal dy0)
{
    dx = xpos;

    if (dy + dy0 < ypos2)
        return;

    createFrame();
}


void QQtWord::createFrame()
{
    xpos = leftMargin;
    xpos2 = sceneRect.width() - rightMargin;
    ypos = topMargin;
    ypos2 = sceneRect.height() - bottomMargin;
    dx = xpos;
    dy = ypos;

    pageScene = new QQtGraphicsScene(sceneRect);
    pageSceneVector.append(pageScene);
    paintPageHeader();
    paintPageFooter();
}

void QQtWord::paintPageHeader()
{
    // Page header
    if (headerText.isEmpty())
        return;

    int sx = xpos;
    int sy = ypos - headerSize;
    /*
     * 页眉
     */
    QQtGraphicsTextItem* headerItem = pageScene->addText(headerText, m_headerFont);
    headerItem->moveBy(sx, sy);

    //std text
    QString date = QDate::currentDate().toString(QLocale().dateFormat());
    QString time = QTime::currentTime().toString(QLocale().timeFormat(QLocale::ShortFormat));
    QString headerStdText;
    headerStdText = date + "  " + time;
    QQtGraphicsTextItem* item = pageScene->addText(headerStdText, m_headerFont);
    item->moveBy(xpos2 - headerFmt->width(headerStdText), sy);

    sy += headerItem->boundingRect().height();

    //line
    pageScene->addLine(xpos, sy, xpos2, sy, QPen(Qt::black, 1.0));
}

void QQtWord::paintPageFooter()
{
    if (footerText.isEmpty())
        return;

    /*
     * footer
     */
    int sx = xpos;

    QString footerStdText = tr("Page") + QString::number(pageSceneVector.size()) + tr(" ");
    QQtGraphicsTextItem* item = pageScene->addText(footerStdText, m_headerFont);
    int height = item->boundingRect().height();
    int sy = ypos2 + footerSize - height;
    item->moveBy(xpos2 - headerFmt->width(footerStdText), sy);

    pageScene->addLine(xpos, sy, xpos2, sy, QPen(Qt::black, 1.0));

    QQtGraphicsTextItem* footerItem = pageScene->addText(footerText, m_headerFont);
    footerItem->moveBy(xpos, sy);
}

QHash<int, ESpanFlags> QQtWord::tableSpans(const QTableView* table)
{
    Q_ASSERT(table);

    QAbstractItemModel* model = table->model();
    int colCount = model->columnCount();
    int rowCount = model->rowCount();

    QHash<int, ESpanFlags> spans;

    for (int row = 0; row < rowCount; row++)
    {

        for (int col = 0; col < colCount; col++)
        {
            int rowSpan = table->rowSpan(row, col);
            int colSpan = table->columnSpan(row, col);

            int point = (row) * colCount + (col);
            ESpanFlags flags = ESpanNone;

            /*
             * 没有合并
             */
            if (rowSpan == 1 && colSpan == 1)
            {
                spans.insert(point, flags);
                continue;
            }

            for (int i = 0; i < rowSpan; i++)
            {

                point = (row + i) * colCount + col + 0;

                /*
                 * 如果此处有Span，但是Spans已经赋值，那么break
                 */
                if (ESpanNone != spans.value(point, ESpanNone))
                    break;

                for (int j = 0; j < colSpan; j++)
                {
                    point = (row + i) * colCount + col + j;

                    /*
                     * 如果此处有Span，但是Spans已经赋值，那么break
                     */
                    if (ESpanNone != spans.value(point, ESpanNone))
                        break;

                    ESpanFlags flags = ESpanNone;

                    if (i == 0)
                        flags |= ESpanFlags(ESpanTop);

                    if (i == rowSpan - 1)
                        flags |= ESpanFlags(ESpanBottom);

                    if (j == 0)
                        flags |= ESpanFlags(ESpanLeft);

                    if (j == colSpan - 1)
                        flags |= ESpanFlags(ESpanRight);

                    if (i != 0 && j != 0 && i != rowSpan - 1 && j != colSpan - 1)
                        flags |= ESpanMiddle;

                    spans.insert(point, flags);
                }
            }
        }
    }

    return spans;
}
