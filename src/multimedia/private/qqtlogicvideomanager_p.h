#ifndef QQTLOGICVIDEOMANAGER_P_H
#define QQTLOGICVIDEOMANAGER_P_H

#include <QObject>
#include <QTimer>
#include <QImage>

#include "qqt-qt.h"
#include "qqtcore.h"

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

#include <qqtimageconverter.h>

class QQtLogicVideoManager;
class QQtLogicVideoManagerPrivate : public QObject
{
    Q_OBJECT

public:
    explicit QQtLogicVideoManagerPrivate ( QQtLogicVideoManager* q, QObject* parent = 0 );
    virtual ~QQtLogicVideoManagerPrivate();

    bool open ( QString devName );
    bool close();

signals:
    //获取图像
    void readyRead ( const QImage& image );

protected slots:
    void slotSendImageToClient();

protected:
    //用户进程只需要调用一次
    virtual void init_dmmu();
    virtual void deinit_dmmu();

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

protected:

private:
    Q_DECLARE_PUBLIC ( QQtLogicVideoManager )
    QQtLogicVideoManager* q_ptr;

    static int sDmmuRefCount;
};

#endif // QQTLOGICVIDEOMANAGER_P_H

