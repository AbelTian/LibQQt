#ifndef __JZ_CIM_H__
#define __JZ_CIM_H__

#define CIMIO_SHUTDOWN                 0x01   // stop preview
#define CIMIO_START_PREVIEW            0x02
#define CIMIO_START_CAPTURE            0x03
#define CIMIO_GET_FRAME                0x04
#define CIMIO_GET_SENSORINFO           0x05
#define CIMIO_GET_VAR                  0x06
#define CIMIO_GET_CAPTURE_PARAM        0x07
#define CIMIO_GET_PREVIEW_PARAM        0x08 // get preview size and format
#define CIMIO_GET_SUPPORT_PSIZE        0x09
#define CIMIO_SET_PARAM                0x0a
#define CIMIO_SET_PREVIEW_MEM          0x0b // alloc mem for buffers by app
#define CIMIO_SET_CAPTURE_MEM          0x0c // alloc mem for buffers by app
#define CIMIO_SELECT_SENSOR            0x0d
#define CIMIO_DO_FOCUS                 0x0e
#define CIMIO_AF_INIT                  0x0f
#define CIMIO_SET_PREVIEW_SIZE         0x10
#define CIMIO_SET_CAPTURE_SIZE         0x11
#define CIMIO_GET_SUPPORT_CSIZE        0x12
#define CIMIO_SET_VIDEO_MODE           0x13
#define CIMIO_STOP_PREVIEW             0x14
#define CIMIO_SET_TLB_BASE             0x15
#define CIMIO_GET_SENSOR_COUNT         0x16
#define CIMIO_SET_PREVIEW_FMT          0x17
#define CIMIO_SET_CAPTURE_FMT          0x18
#define CIMIO_GET_SHAPNESS_PARAM       0x19
#define CIMIO_GET_CONTAAST_PARAM       0x1a

#ifdef __KERNEL__
//cim output format, set according system/core/include/system/graphics.h
#define HAL_PIXEL_FORMAT_YV12          0x32315659
#define HAL_PIXEL_FORMAT_JZ_YUV_420_P  0x47700001
#define HAL_PIXEL_FORMAT_JZ_YUV_420_B  0x47700002
#define HAL_PIXEL_FORMAT_YCbCr_422_I   0x14
#endif

#define CIM_CSC_YUV420B                0x1
#define CIM_CSC_YUV420P                0x2
#define CIM_BYPASS_YUV422I             0X3

//cim config for sensor YUYV output order
#define SENSOR_OUTPUT_FORMAT_Y0UY1V    0 //11 22 33 44
#define SENSOR_OUTPUT_FORMAT_UY1VY0    1 //22 33 44 11
#define SENSOR_OUTPUT_FORMAT_Y1VY0U    2 //33 44 11 22
#define SENSOR_OUTPUT_FORMAT_VY0UY1    3 //44 11 22 33
#define SENSOR_OUTPUT_FORMAT_VY1UY0    4 //44 33 22 11
#define SENSOR_OUTPUT_FORMAT_Y1UY0V    5 //33 22 11 44
#define SENSOR_OUTPUT_FORMAT_UY0VY1    6 //22 11 44 33
#define SENSOR_OUTPUT_FORMAT_Y0VY1U    7 //11 44 33 22

//camera param cmd
#define CPCMD_SET_BALANCE              (0x1 << (16 + 3))
#define CPCMD_SET_EFFECT               (0x1 << (16 + 4))
#define CPCMD_SET_ANTIBANDING          (0x1 << (16 + 5))
#define CPCMD_SET_FLASH_MODE           (0x1 << (16 + 6))
#define CPCMD_SET_SCENE_MODE           (0x1 << (16 + 7))
#define CPCMD_SET_FOCUS_MODE           (0x1 << (16 + 9))
#define CPCMD_SET_FPS                  (0x1 << (16 + 10))
#define CPCMD_SET_NIGHTSHOT_MODE       (0x1 << (16 + 11))
#define CPCMD_SET_LUMA_ADAPTATION      (0x1 << (16 + 12))
#define CPCMD_SET_BRIGHTNESS           (0x1 << (16 + 13)) //add for VT app
#define CPCMD_SET_CONTRAST             (0x1 << (16 + 14)) //add for VT app
#define CPCMD_SET_SHARPNESS            (0x1 << (16 + 15))
#define CPCMD_SET_SATURATION		(0x1 << (16 + 8))

// Values for white balance settings.
#define WHITE_BALANCEVALUES_NUM        9
enum {
    WHITE_BALANCE_AUTO                 = 0x1 << 0,
    WHITE_BALANCE_INCANDESCENT         = 0x1 << 1,
    WHITE_BALANCE_FLUORESCENT          = 0x1 << 2,
    WHITE_BALANCE_WARM_FLUORESCENT     = 0x1 << 3,
    WHITE_BALANCE_DAYLIGHT             = 0x1 << 4,
    WHITE_BALANCE_CLOUDY_DAYLIGHT      = 0x1 << 5,
    WHITE_BALANCE_TWILIGHT             = 0x1 << 6,
    WHITE_BALANCE_SHADE                = 0x1 << 7,
    WHITE_BALANCE_TUNGSTEN             = 0x1 << 8,
};
// Values for effect settings.
#define EFFECTVALUES_NUM               12
enum {
    EFFECT_NONE                        = 0x1 << 0,
    EFFECT_MONO                        = 0x1 << 1,
    EFFECT_NEGATIVE                    = 0x1 << 2,
    EFFECT_SOLARIZE                    = 0x1 << 3,
    EFFECT_SEPIA                       = 0x1 << 4,
    EFFECT_POSTERIZE                   = 0x1 << 5,
    EFFECT_WHITEBOARD                  = 0x1 << 6,
    EFFECT_BLACKBOARD                  = 0x1 << 7,
    EFFECT_AQUA                        = 0x1 << 8,
    EFFECT_PASTEL                      = 0x1 << 9,
    EFFECT_MOSAIC                      = 0x1 << 10,
    EFFECT_RESIZE                      = 0x1 << 11,
};
// Values for antibanding settings.
#define ANTIBANVALUES_NUM              4
enum {
    ANTIBANDING_AUTO                   = 0x1 << 0,
    ANTIBANDING_50HZ                   = 0x1 << 1,
    ANTIBANDING_60HZ                   = 0x1 << 2,
    ANTIBANDING_OFF                    = 0x1 << 3,
};
// Values for flash mode settings.
#define FLASHMODE_NUM                  6
enum {
    FLASH_MODE_OFF                     = 0x1 << 0,
    FLASH_MODE_AUTO                    = 0x1 << 1,
    FLASH_MODE_ON                      = 0x1 << 2,
    FLASH_MODE_RED_EYE                 = 0x1 << 3,
    FLASH_MODE_TORCH                   = 0x1 << 4,
    FLASH_MODE_ALWAYS                  = 0x1 << 5,
};
// Values for scene mode settings.
#define SCENEVALUES_NUM               16
enum {
    SCENE_MODE_AUTO                    = 0x1 << 0,
    SCENE_MODE_ACTION                  = 0x1 << 1,
    SCENE_MODE_PORTRAIT                = 0x1 << 2,
    SCENE_MODE_LANDSCAPE               = 0x1 << 3,
    SCENE_MODE_NIGHT                   = 0x1 << 4,
    SCENE_MODE_NIGHT_PORTRAIT          = 0x1 << 5,
    SCENE_MODE_THEATRE                 = 0x1 << 6,
    SCENE_MODE_BEACH                   = 0x1 << 7,
    SCENE_MODE_SNOW                    = 0x1 << 8,
    SCENE_MODE_SUNSET                  = 0x1 << 9,
    SCENE_MODE_STEADYPHOTO             = 0x1 << 10,
    SCENE_MODE_FIREWORKS               = 0x1 << 11,
    SCENE_MODE_SPORTS                  = 0x1 << 12,
    SCENE_MODE_PARTY                   = 0x1 << 13,
    SCENE_MODE_CANDLELIGHT             = 0x1 << 14,
    SCENE_MODE_BARCODE                 = 0x1 << 15,
};
// Values for focus mode settings.
#define FOCUSMODE_NUM                  7
enum {
    FOCUS_MODE_FIXED                   = 0x1 << 0,
    FOCUS_MODE_AUTO                    = 0x1 << 1,
    FOCUS_MODE_INFINITY                = 0x1 << 2,
    FOCUS_MODE_MACRO                   = 0x1 << 3,
    FOCUS_MODE_CONTINUOUS_VIDEO        = 0x1<<4,
    FOCUS_MODE_CONTINUOUS_PICTURE      = 0x1<<5,
    FOCUS_MODE_EDOF                    = 0x1<<6,
};
#define PREVIEWFORMAT_NUM 10
enum PreviewFormat {
    PIXEL_FORMAT_YUV422SP              = 0x1<<0,
    PIXEL_FORMAT_YUV420SP              = 0x1<<1,
    PIXEL_FORMAT_YUV422I               = 0x1<<2,
    PIXEL_FORMAT_RGB565                = 0x1<<3,
    PIXEL_FORMAT_JPEG                  = 0x1<<4,
    PIXEL_FORMAT_YUV420P               = 0x1<<5,
    PIXEL_FORMAT_JZ_YUV420T            = 0x1<<6,
    PIXEL_FORMAT_JZ_YUV420P            = 0x1<<7,
    PIXEL_FORMAT_RGBA8888              = 0x1<<8,
    PIXEL_FORMAT_BAYER_RGGB            = 0x1<<9
};

// Values for fps mode settings.
#define FPS_MODE_10                    0x1<<0
#define FPS_MODE_15                    0x1<<1
#define FPS_MODE_20                    0x1<<2
#define FPS_MODE_25                    0x1<<3
#define FPS_MODE_30                    0x1<<4

// Values for contrast settings.
#define CONTRAST_P5		0x1<<0
#define CONTRAST_P4		0x1<<1
#define CONTRAST_P3		0x1<<2
#define CONTRAST_P2		0x1<<3
#define CONTRAST_P1		0x1<<4
#define CONTRAST_P0		0x1<<5
#define CONTRAST_M1		0x1<<6
#define CONTRAST_M2		0x1<<7
#define CONTRAST_M3		0x1<<8
#define CONTRAST_M4		0x1<<9
#define CONTRAST_M5		0x1<<10

// Values for sharpness settings.
#define SHARP_P4		0x1<<0
#define SHARP_P3		0x1<<1
#define SHARP_P2		0x1<<2
#define SHARP_P1		0x1<<3
#define SHARP_P0		0x1<<4
#define SHARP_M1		0x1<<5
#define SHARP_M2		0x1<<6
#define SHARP_M3		0x1<<7
#define SHARP_M4		0x1<<8

// Values for saturation settings.
#define SATURATION_P4		0x1<<0
#define SATURATION_P3		0x1<<1
#define SATURATION_P2		0x1<<2
#define SATURATION_P1		0x1<<3
#define SATURATION_P0		0x1<<4
#define SATURATION_M1		0x1<<5
#define SATURATION_M2		0x1<<6
#define SATURATION_M3		0x1<<7
#define SATURATION_M4		0x1<<8

struct frm_size {
    unsigned int w;
    unsigned int h;
};

struct mode_bit_map {
    unsigned short balance;
    unsigned short effect;
    unsigned short antibanding;
    unsigned short flash_mode;
    unsigned short scene_mode;
    unsigned short focus_mode;
    unsigned short fps;
    unsigned short contrast;
    unsigned short sharpness;
};

//add by wwzhao for ov5640
typedef struct integer_menu
{
    char name[32];
    int default_value;
    int minimum;
    int maximum;
    int step;
    char reserved[2];
}integer_menu;

struct sensor_info
{
    unsigned int sensor_id;
    char name[32];
    int vendor;
    int facing;
    int orientation;

    unsigned int prev_resolution_nr;
    unsigned int cap_resolution_nr;

    //add by wwzhao for ov5640
    unsigned int sharpness_supported;
    unsigned int contrast_supported;

    struct mode_bit_map modes;
};

#ifdef __KERNEL__
typedef struct cim_sensor {
    int vendor;
    u16 chipid;
    int    id;
    char  name[16];
    struct list_head   list;

    int facing;
    int orientation;
    int cim_cfg;
    struct mode_bit_map modes;   //indicate sensor can support modes
    struct mode_bit_map para;   //indicate currnet parameter value

    bool first_used;

    //add by wwzhao for ov5640
    bool sharpness_supported;
    struct integer_menu *sharpness;
    bool contrast_supported;
    struct integer_menu *contrast;

    struct frm_size   *preview_size;
    struct frm_size   *capture_size;
    int prev_resolution_nr;
    int cap_resolution_nr;
    int cap_wait_frame;

    int (*probe)(struct cim_sensor *data);
    int (*init)(struct cim_sensor *data);
    int (*power_on)(struct cim_sensor *data);
    int (*shutdown)(struct cim_sensor *data);
    int (*reset)(struct cim_sensor *data);

    int (*before_power_on)(struct cim_sensor *data);
    int (*after_power_on)(struct cim_sensor *data);

    int (*af_init)(struct cim_sensor *data);
    int (*start_af)(struct cim_sensor *data);
    int (*stop_af)(struct cim_sensor *data);
    void (*read_all_regs)(struct cim_sensor *data);

    int (*set_preivew_mode)(struct cim_sensor *data);
    int (*set_capture_mode)(struct cim_sensor *data);
    int (*set_video_mode)(struct cim_sensor *data);

    int (*set_resolution)(struct cim_sensor *data,int width,int height);
    int (*set_balance)(struct cim_sensor *data,unsigned short arg);
    int (*set_effect)(struct cim_sensor *data,unsigned short arg);
    int (*set_antibanding)(struct cim_sensor *data,unsigned short arg);
    int (*set_flash_mode)(struct cim_sensor *data,unsigned short arg);
    int (*set_scene_mode)(struct cim_sensor *data,unsigned short arg);
    int (*set_focus_mode)(struct cim_sensor *data,unsigned short arg);
    int (*set_fps)(struct cim_sensor *data,unsigned short arg);
    int (*set_nightshot)(struct cim_sensor *data,unsigned short arg);
    int (*set_luma_adaption)(struct cim_sensor *data,unsigned short arg);
    int (*set_brightness)(struct cim_sensor *data,unsigned short arg);
    int (*set_contrast)(struct cim_sensor *data, unsigned short arg);
    int (*set_sharpness)(struct cim_sensor *data, unsigned short arg);
    int (*set_saturation)(struct cim_sensor *data, unsigned short arg);

//    int (*fill_buffer)(struct cim_sensor *data,char *buf);

    void *private;
}cim_sensor;

struct jz_cim_platform_data {
    void (*power_on)(void);
    void (*power_off)(void);
};

#define CAMERA_FACING_FRONT  1
#define CAMERA_FACING_BACK  0

extern int camera_sensor_register(struct cim_sensor *desc);
#endif //end kernel

typedef struct CameraYUVMeta {
    int32_t index;
    int32_t width;
    int32_t height;
    int32_t yPhy;
    int32_t uPhy;
    int32_t vPhy;
    int32_t yAddr;
    int32_t uAddr;
    int32_t vAddr;
    int32_t yStride;
    int32_t uStride;
    int32_t vStride;
    int32_t count;
    int32_t format;
}CameraYUVMeta;

#endif
