#ifndef QQTWORD_H
#define QQTWORD_H

#include <QObject>
#include "qqt-qt.h"
#include "qqtprinter.h"
#include "qqtgraphicsscene.h"
#include "qqt-local.h"

enum ESpanFlag
{
    ESpanNone = 0,
    ESpanLeft = 1,
    ESpanTop = 2,
    ESpanRight = 4,
    ESpanBottom = 8,
    ESpanMiddle = 16,
};

Q_DECLARE_FLAGS(ESpanFlags, ESpanFlag)

class QQTSHARED_EXPORT QQTWord : public QObject
{
    Q_OBJECT
public:
    explicit QQTWord(QObject* parent = 0);

    void addText(const QString& text, QFont m_font = QFont(),
                 Qt::Alignment align = Qt::AlignHCenter, QPointF point = QPointF(0, 0));
    void addSignoffText(const QString& text, QFont m_font = QFont());
    void addTable(const QTableView* table, QPointF pos = QPointF(0, 0));

    int pageNum();
    QQTGraphicsScene* getPage(int num);
    void exportPdf(const QString& pdf);
    void print();

    QRectF clientRectF();
    QRectF paperRect();
    void setMargin(qreal left = 0, qreal right = 0,
                   qreal top = 0, qreal botoom = 0);
    void setLineSpacing(qreal mainSpacing = 0);
    void setHeaderSize(qreal size = 0);
    void setFooterSize(qreal size = 0);

    QFont font();
    void setFont(QFont m_font = QFont());
    void setHeaderFont(QFont m_font = QFont());
    QFont mainFont() { return m_mainFont; }
    QFont titleFont() { return m_titleFont; }
    QFont title2Font() { return m_title2Font; }
    QFont headerFont() { return m_headerFont; }
    void setHeaderLine(bool show = false);
    void setFooterLine(bool show = false);
    void setHeaderText(const QString& text, QFont m_font = QFont(),
                       Qt::Alignment align = Qt::AlignHCenter);
    void setFooterText(const QString& text, QFont m_font = QFont(),
                       Qt::Alignment align = Qt::AlignHCenter);
    /**
     * @brief initWordExpress 初始化纸张，第一张空白纸
     */
    void initWord();

protected:
    virtual void adjustdy(qreal dy0);
    virtual void createFrame();
    virtual void paintPageHeader();
    virtual void paintPageFooter();

signals:

public slots:

private:
    /*
     * 输出
     */
    QQTPrinter* pr;

    /*
     * 对页面元素高度不能迅速统计的场景
     */
    QVector<QQTGraphicsScene*> pageSceneVector;
    QQTGraphicsScene* pageScene;

    /*
     * 页面元素
     */
    int logicalDpiX;
    int logicalDpiY;
    QRectF sceneRect;

    qreal xpos, xpos2, ypos, ypos2;
    qreal dx, dy;

    qreal leftMargin;
    qreal rightMargin;
    qreal topMargin;
    qreal bottomMargin;

    qreal mainHeight;
    qreal titleHeight;
    qreal title2Height;
    qreal headerHeight;
    qreal mainSpacing;
    qreal titleSpacing;
    qreal title2Spacing;
    qreal headerSpacing;

    /*
     * 页眉
     */
    qreal headerSize;
    QFont m_headerFont;
    QFontMetrics* headerFmt;
    QString headerText;

    /*
     * 页脚
     */
    qreal footerSize;
    QString footerStdText;
    QString footerText;

    /*
     * 标题
     */
    QFont m_titleFont;
    QFontMetrics* titleFmt;

    /*
     * 二号标题
     */
    QFont m_title2Font;
    QFontMetrics* title2Fmt;

    /*
     * 正文
     */
    QFont m_mainFont;
    QFontMetrics* mainFmt;

    /*
     * 使用中
     */
    QFont m_font;
    QFontMetrics* fmt;


    QHash<int, ESpanFlags> tableSpans(const QTableView* table);
};

#endif // QQTWORD_H
