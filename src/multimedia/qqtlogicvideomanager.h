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
 * @brief The QQtLogicVideoManager class
 * 模拟摄像头管理器
 */
class QQTSHARED_EXPORT QQtLogicVideoManager : public QObject
{
    Q_OBJECT

public:
    explicit QQtLogicVideoManager ( QObject* parent = 0 );
    virtual ~QQtLogicVideoManager();

    //用户进程只需要调用一次
    static void init_dmmu();
    static void deinit_dmmu();

    //开启某个确定的模拟摄像头
    bool open ( const QString& devName = "/dev/cim" );
    bool close();

signals:
    //获取图像
    void readyRead ( const QImage& image );

protected:
    //yuv转rgb
    virtual int convert_yuv_to_rgb_pixel ( int y, int u, int v );
    virtual int convert_yuv_to_rgb_buffer ( unsigned char* yuv, unsigned char* rgb, unsigned int width,
                                            unsigned int height );

protected slots:
    void slotSendImageToClient();

private:
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
};

#endif // QQTLOGICVIDEOMANAGER_H
