#include <qqtimageconverter.h>

int qqt_convert_uyvy_to_rgb888_buffer ( unsigned char* src_buffer, int w, int h,
                                        unsigned char* des_buffer )
{
    unsigned char* yuv, *rgb;
    unsigned char u, v, y1, y2;

    yuv = src_buffer;
    rgb = des_buffer;

    if ( yuv == NULL || rgb == NULL )
    {
        printf ( "error: input data null!\n" );
        return -1;
    }

    int size = w * h;

    for ( int i = 0; i < size; i += 2 )
    {
        y1 = yuv[2 * i + 1];
        y2 = yuv[2 * i + 3];
        u = yuv[2 * i];
        v = yuv[2 * i + 2];

#if 0
        rgb[3 * i]     = ( unsigned char ) ( y1 + 1.402 * ( u - 128 ) );
        rgb[3 * i + 1] = ( unsigned char ) ( y1 - 0.344 * ( u - 128 ) - 0.714 * ( v - 128 ) );
        rgb[3 * i + 2] = ( unsigned char ) ( y1 + 1.772 * ( v - 128 ) );

        rgb[3 * i + 3] = ( unsigned char ) ( y2 + 1.375 * ( u - 128 ) );
        rgb[3 * i + 4] = ( unsigned char ) ( y2 - 0.344 * ( u - 128 ) - 0.714 * ( v - 128 ) );
        rgb[3 * i + 5] = ( unsigned char ) ( y2 + 1.772 * ( v - 128 ) );
#endif

        //为提高性能此处用移位运算；
        rgb[3 * i]     = ( unsigned char ) ( y1 + ( u - 128 ) + ( ( 104 * ( u - 128 ) ) >> 8 ) );
        rgb[3 * i + 1] = ( unsigned char ) ( y1 - ( 89 * ( v - 128 ) >> 8 ) - ( ( 183 * ( u - 128 ) ) >> 8 ) );
        rgb[3 * i + 2] = ( unsigned char ) ( y1 + ( v - 128 ) + ( ( 199 * ( v - 128 ) ) >> 8 ) );

        rgb[3 * i + 3] = ( unsigned char ) ( y2 + ( u - 128 ) + ( ( 104 * ( u - 128 ) ) >> 8 ) );
        rgb[3 * i + 4] = ( unsigned char ) ( y2 - ( 89 * ( v - 128 ) >> 8 ) - ( ( 183 * ( u - 128 ) ) >> 8 ) );
        rgb[3 * i + 5] = ( unsigned char ) ( y2 + ( v - 128 ) + ( ( 199 * ( v - 128 ) ) >> 8 ) );
    }

    return 0;
}

int qqt_convert_yuyv_to_rgb888_pixel ( int y, int u, int v )
{
    //pixel32 是个4字节中转量
    unsigned int pixel32 = 0;
    unsigned char* pixel = ( unsigned char* ) &pixel32;
    int r, g, b;
    b = y + ( ( 443 * ( u - 128 ) ) >> 8 );
    b = ( b < 0 ) ? 0 : ( ( b > 255 ) ? 255 : b );
    g = y - ( ( 179 * ( v - 128 ) + 86 * ( u - 128 ) ) >> 8 );
    g = ( g < 0 ) ? 0 : ( ( g > 255 ) ? 255 : g );
    r = y + ( ( 351 * ( v - 128 ) ) >> 8 );
    r = ( r < 0 ) ? 0 : ( ( r > 255 ) ? 255 : r );
    pixel[0] = r;
    pixel[1] = g;
    pixel[2] = b;
    return pixel32;
}

int qqt_convert_yuyv_to_rgb888_buffer ( unsigned char* yuv, unsigned char* rgb, unsigned int width,
                                        unsigned int height )
{
    unsigned int in, out = 0;
    unsigned int pixel_16;
    unsigned char pixel_24[3];
    unsigned int pixel32;
    int y0, u, y1, v;

    for ( in = 0; in < width * height * 2; in += 4 )
    {
        pixel_16 =
            yuv[in + 3] << 24 |
            yuv[in + 2] << 16 |
            yuv[in + 1] <<  8 |
            yuv[in + 0];
        y0 = ( pixel_16 & 0x000000ff );
        u  = ( pixel_16 & 0x0000ff00 ) >>  8;
        y1 = ( pixel_16 & 0x00ff0000 ) >> 16;
        v  = ( pixel_16 & 0xff000000 ) >> 24;
        pixel32 = qqt_convert_yuyv_to_rgb888_pixel ( y0, u, v );
        pixel_24[0] = ( pixel32 & 0x000000ff );
        pixel_24[1] = ( pixel32 & 0x0000ff00 ) >> 8;
        pixel_24[2] = ( pixel32 & 0x00ff0000 ) >> 16;
        rgb[out++] = pixel_24[0];
        rgb[out++] = pixel_24[1];
        rgb[out++] = pixel_24[2];
        pixel32 = qqt_convert_yuyv_to_rgb888_pixel ( y1, u, v );
        pixel_24[0] = ( pixel32 & 0x000000ff );
        pixel_24[1] = ( pixel32 & 0x0000ff00 ) >> 8;
        pixel_24[2] = ( pixel32 & 0x00ff0000 ) >> 16;
        rgb[out++] = pixel_24[0];
        rgb[out++] = pixel_24[1];
        rgb[out++] = pixel_24[2];
    }

    return 0;
}
