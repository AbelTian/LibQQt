#ifndef QQTIMAGECONVERTER_H
#define QQTIMAGECONVERTER_H
#include <QImage>
#include <QVideoFrame>

#include <qqt-local.h>
/**
 * @brief The QQtImageConverter class
 */
class QQTSHARED_EXPORT QQtImageConverter
{
public:
    explicit QQtImageConverter ();
    virtual ~QQtImageConverter ();

    QImage YUYVTORGB888 ( const QVideoFrame& frame );
    QImage UYVYTORGB888 ( const QVideoFrame& frame );

private:
    uchar* pp;
    QImage* mImage;
};

/**
 * @brief qqt_convert_uyvy_to_rgb888_buffer
 * @param src_buffer yuv422 [uyvy ...]
 * @param w
 * @param h
 * @param des_buffer rgb888
 * @return
 */
QQTSHARED_EXPORT int qqt_convert_uyvy_to_rgb888_buffer ( unsigned char* src_buffer,
                                                         int w, int h,
                                                         unsigned char* des_buffer );


QQTSHARED_EXPORT int qqt_convert_yuyv_to_rgb888_pixel ( int y, int u, int v );


/**
 * @brief qqt_convert_yuyv_to_rgb888_buffer
 * @param yuv yuv422 [yuyv ...]
 * @param rgb rgb888
 * @param width
 * @param height
 * @return
 */
QQTSHARED_EXPORT int qqt_convert_yuyv_to_rgb888_buffer ( unsigned char* yuv,
                                                         unsigned char* rgb,
                                                         unsigned int width, unsigned int height );

#endif // QQTIMAGECONVERTER_H
