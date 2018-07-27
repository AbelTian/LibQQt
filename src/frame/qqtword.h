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

Q_DECLARE_FLAGS ( ESpanFlags, ESpanFlag )

/**
 * @brief The QQtWord class
 * 原理介绍
 * 内部使用GraphicScene实现,可以投影到GraphicView Printer Image等绘图设备.
 *
 * 功能支持
 * 添加文字, 可以跨页
 * 添加表格, 可以跨页, 支持经过合并单元格的表格.
 * 添加图片, 太大了会跳页
 * 添加Widget, 太大了会跳页
 *
 * 已经支持的屏幕的分辨率和DPI,帮助用户识别自己的目标画板的大小.
 * 公式 Rect1 : DPI1 = Rect2 : DPI2
 * 从Scene(内部)render()到外部画板的时候,需要计算这个rect.
 * 分类              Rect的像素                    DPI
 * Scene            2480*3508(A4)                300 300
 * DWin屏幕(View)    800*600                      136(x) 156(y) 理论值142 138
 * PC屏幕(View)      1920*1080                    96 96
 * Printer          9917*14033                   1200
 *
 * Scene可以设置纸张类型, 假如设置A3 DPI不变 SceneRect会变.而这个Rect像素大小,请参照PS.
 *
 * 关于排版的约束
 * 1. 开始设置好纸张,就不要更换,你肯定不想自己的数据被截断显示,内部不会放缩数据.
 *
 */
class QQTSHARED_EXPORT QQtWord : public QObject
{
    Q_OBJECT
public:
    explicit QQtWord ( QObject* parent = 0 );

    /**
     * @brief initWord 初始化纸张，第一张空白纸
     */
    void initWord();
    void addText ( const QString& text, QFont m_font = QFont(),
                   Qt::Alignment align = Qt::AlignHCenter, QPointF point = QPointF ( 0, 0 ) );
    void addTable ( const QTableView* table, QPointF pos = QPointF ( 0, 0 ) );
    void addSignoffText ( const QString& text, QFont m_font = QFont() );

    int pageNum();
    QQtGraphicsScene* getPage ( int num );

    QRectF clientRectF();
    QRectF paperRect();
    void setMargin ( qreal left = 0, qreal right = 0,
                     qreal top = 0, qreal botoom = 0 );
    void setLineSpacing ( qreal mainSpacing = 0 );
    void setHeaderSize ( qreal size = 0 );
    void setFooterSize ( qreal size = 0 );

    QFont font();
    void setFont ( QFont m_font = QFont() );
    void setHeaderFont ( QFont m_font = QFont() );
    QFont mainFont() { return m_mainFont; }
    QFont titleFont() { return m_titleFont; }
    QFont title2Font() { return m_title2Font; }
    QFont headerFont() { return m_headerFont; }
    void setHeaderLine ( bool show = false );
    void setFooterLine ( bool show = false );
    void setHeaderText ( const QString& text, QFont m_font = QFont(),
                         Qt::Alignment align = Qt::AlignHCenter );
    void setFooterText ( const QString& text, QFont m_font = QFont(),
                         Qt::Alignment align = Qt::AlignHCenter );

    void exportPdf ( const QString& pdf );
    void print();

protected:
    virtual void adjustdy ( qreal dy0 );
    virtual void createFrame();
    virtual void paintPageHeader();
    virtual void paintPageFooter();

signals:

public slots:

private:
    /*
     * 输出
     */
    QQtPrinter* pr;

    /*
     * 对页面元素高度不能迅速统计的场景
     */
    QVector<QQtGraphicsScene*> pageSceneVector;
    QQtGraphicsScene* pageScene;

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


    QHash<int, ESpanFlags> tableSpans ( const QTableView* table );
};

#endif // QQTWORD_H
