
#ifndef QQTLOGICVIDEOMANAGER_H
#define QQTLOGICVIDEOMANAGER_H

#include "qqt-qt.h"
#include "qqtlinux.h"
#include "qqtcore.h"
#include "qqt-local.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "graphics.h"
#include "dmmu.h"
#include "hal.h"
#include "jz_cim.h"

#ifdef __cplusplus
}
#endif  /* __cplusplus */


/**
 * @brief The QQtLogicPreviewWidget class
 * QQt模拟摄像头预览控件
 * 省略dmmu的Qt Wrapper类
 */
class QQTSHARED_EXPORT QQtLogicPreviewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QQtLogicPreviewWidget ( QWidget* parent = 0 );
    ~QQtLogicPreviewWidget();
    int play();
    int close();

private:
    Ui::QQtLogicPreviewWidget* ui;

    struct sensor_info sinfo;
    int pre_bpp;
    int rate;         /* default to 15fps  */
    unsigned int addr;
    unsigned int phys;

    int fd;
    int format;

    struct camera_memory pre_memory;
    struct camera_buffer pre_buf;
    struct frm_size pre_size;
    unsigned int tlb_base_phys;

    uchar* pp;
    uchar* p;
    QImage* frame;
    QTimer* timer;

    bool bFullScreen;
    QWidget* m_parent;
    QRect geome;
    Qt::WindowFlags flags;

    int convert_yuv_to_rgb_pixel ( int y, int u, int v );
    int convert_yuv_to_rgb_buffer ( unsigned char* yuv, unsigned char* rgb, unsigned int width, unsigned int height );

    // QWidget interface
protected:
    void paintEvent ( QPaintEvent* );
    void mousePressEvent ( QMouseEvent* e );
};

#endif // QQTLOGICVIDEOMANAGER_H
