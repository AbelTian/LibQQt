#ifndef QQTWORD_H
#define QQTWORD_H

#include <QObject>
#include "qqt-qt.h"
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
 *
 * 功能支持
 * 添加文字, 可以跨页
 * 添加表格, 可以跨页, 支持经过合并单元格的表格.
 * 添加图片, 太大了会跳页
 * 添加Widget, 太大了会跳页
 * 添加新页面,直接新页面编辑.
 * 设置纸张类型
 * 设置纸张方向
 *
 * 原理介绍
 * 内部使用GraphicScene实现, 使用函数添加内容,自动排版,
 * 可以投影到GraphicView Printer Image等绘图设备.
 *
 * 坐标原理
 * 根据所见即所得.
 * 图纸默认为A4, Rect在PS里能找到, DPI固定为300像素每英寸, 尺寸在WPS Word里能找到.
 * 在A4纸等纸上设计好排版,可以把尺寸直接拿过来用.
 * 接口单位全部为像素.
 *
 * 计算方法:
 * 在A4纸上用尺子量, 然后转换为英寸.
 * paperRect(0, 0, w, h) = dpi * 英寸(w, h).
 *
 * 已经知道的屏幕的分辨率和DPI,帮助用户识别自己的目标画板的大小.
 * 公式 Rect1 : DPI1 = Rect2 : DPI2
 * 从Scene(内部)render()到外部画板的时候,需要计算这个rect.
 * 分类              Rect的像素                    DPI
 * Scene            2480*3508(A4)                300 300
 * DWin屏幕(View)    800*600                      136(x) 156(y) 理论值142 138
 * PC屏幕(View)      1920*1080                    96 96
 * Printer          9917*14033                   1200
 * Image            1920*1080                    96 96
 * 可以设置纸张类型, 假如设置A3 DPI不变 SceneRect会变.而这个Rect像素大小,请参照PS.
 *
 * 关于排版的约束
 * 1. 开始设置好纸张,就不要更换,你肯定不想自己的数据被截断显示,内部不会放缩数据.
 * 2. 内部Scene使用默认的分辨率300, rect根据纸的类型而变化.
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
    /**
     * @brief addText 标准功能
     */
    void addText ( const QString& text, QFont m_font = QFont(),
                   Qt::Alignment align = Qt::AlignHCenter, QPointF point = QPointF ( 0, 0 ) );
    void addTable ( const QTableView* table, QPointF pos = QPointF ( 0, 0 ) );
    void addSignoffText ( const QString& text, QFont m_font = QFont() );

    int pageNum();
    QQtGraphicsScene* getPage ( int num );

    QRectF clientRectF();
    QRectF paperRect();

    //单位:像素. 可以结合Adobe PhotoShop和WPS Word进行计算.
    void setMargin ( qreal left = 375.5898, qreal right = 375.5898,
                     qreal top = 299.9994, qreal botoom = 299.9994 );
    void setLineSpacing ( qreal mainSpacing = 0 );
    void setHeaderHeight ( qreal size = 195.32 );
    void setFooterHeight ( qreal size = 195.32 );

    //正文,正在使用中
    QFont font();
    //default: QApplication::font()
    void setFont ( QFont m_font = QFont() );

    //header,使用中.
    void setHeaderFont ( QFont font = QFont() );
    void setHeaderLine ( bool show = false );
    void setHeaderText ( const QString& text, QFont m_font = QFont(),
                         Qt::Alignment align = Qt::AlignHCenter );

    //footer,使用中
    void setFooterFont ( QFont font = QFont() );
    void setFooterLine ( bool show = false );
    void setFooterText ( const QString& text, QFont m_font = QFont(),
                         Qt::Alignment align = Qt::AlignHCenter );

    /**
     * @brief mainFont 获取默认的固定格式
     */
    QFont mainFont() { return m_mainFont; }
    QFont titleFont() { return m_titleFont; }
    QFont title2Font() { return m_title2Font; }
    QFont headerFont() { return m_headerFont; }

    /**
     * @brief exportImages 将Word导出为多个图纸.
     */
    //内部有默认的大小和分辨率,根据这些获取目标Rect. 导出图片要用这个Rect.
    //sceneRect / sceneDPI = targetRect / targetDPI 注释:DPI为logicDPI.
    //可选输入: 桌面屏幕 96; DWIN屏 136,156; 打印机 1200; 其他 待测试;
    //DPI保证了(屏幕)所见即(A4纸)所得
    QRectF getTargetRectF ( qreal targetDPIX, qreal targetDPIY ) {
        QRectF targetRect;
        targetRect = QRectF ( 0.0, 0.0, targetDPIX * sceneRect.width() / logicalDpiX /*300*/,
                              targetDPIY * sceneRect.height() / logicalDpiY /*300*/ );
        return targetRect;
    }
    //如果targetRect为空,那么按照SceneRect的大小,分辨率300DPI(内部默认)导出.
    //虽然这里导出图片,但是通过图片可以导出PDF(QQtPrinter),可以显示(QQtWidget),
    //相当于把pageScene按照确定比例投影到确定大小的画纸(幕布)上,是个列表,很多页.
    //sceneRect dpi1 300
    //imageRect dpi2 96
    //printerPaperRect dpi3 1200
    //确定比值相同. dpi 像素每英寸 像素 / 像素每英寸 = 英寸 如果是A4纸,那么一定是固定值咯.
    void exportImage ( QList<QImage>& targetPapers, QRectF targetRect = QRectF() );

protected:
    virtual void adjustdy ( qreal dy0 );
    virtual void createFrame();
    virtual void paintPageHeader();
    virtual void paintPageFooter();

signals:

public slots:

private:
    /*
     * 对页面元素高度不能迅速统计的场景
     */
    QVector<QQtGraphicsScene*> pageSceneVector;
    QQtGraphicsScene* pageScene;

    /*
     * 页面元素
     */
    qreal logicalDpiX;
    qreal logicalDpiY;
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

    void initConstFont();
};

#endif // QQTWORD_H
