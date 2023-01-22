#ifndef LV_CONF_H
#define LV_CONF_H

#include <stdint.h>

/* Color Settings */

#define LV_HOR_RES_MAX (800)
#define LV_VER_RES_MAX (480)
#define LV_COLOR_DEPTH 16
#define LV_COLOR_16_SWAP 0
#define LV_COLOR_SCREEN_TRANSP 0
#define LV_COLOR_MIX_ROUND_OFS (LV_COLOR_DEPTH == 32 ? 0: 128)
#define LV_COLOR_CHROMA_KEY lv_color_hex(0x00ff00)


/* Memory Settings */

#define LV_MEM_CUSTOM 0
#if LV_MEM_CUSTOM == 0
/* Size of the memory available for `lv_mem_alloc` in bytes (>= 2kB)*/
#define LV_MEM_SIZE (320U * 1024U)
#else     /* LV_MEM_CUSTOM */
#define LV_MEM_CUSTOM_INCLUDE <stdlib.h>
#define LV_MEM_CUSTOM_ALLOC malloc
#define LV_MEM_CUSTOM_FREE free
#define LV_MEM_CUSTOM_REALLOC realloc
#endif    /* LV_MEM_CUSTOM */
#define LV_MEM_BUF_MAX_NUM 16
#define LV_MEMCPY_MEMSET_STD 0


/* HAL Settings */

#define LV_DISP_DEF_REFR_PERIOD 30
#define LV_INDEV_DEF_READ_PERIOD 30
#define LV_TICK_CUSTOM 0
#if LV_TICK_CUSTOM
#define LV_TICK_CUSTOM_INCLUDE "Arduino.h"
#define LV_TICK_CUSTOM_SYS_TIME_EXPR (millis())
#endif    /* LV_TICK_CUSTOM */
#define LV_DPI_DEF 130


/* Drawing Configuration */

#define LV_DRAW_COMPLEX 1
#if LV_DRAW_COMPLEX
#define LV_SHADOW_CACHE_SIZE 0
#define LV_CIRCLE_CACHE_SIZE 4
#endif    /* LV_DRAW_COMPLEX */
#define LV_IMG_CACHE_DEF_SIZE 0
#define LV_GRADIENT_MAX_STOPS 2
#define LV_GRAD_CACHE_DEF_SIZE 0
#define LV_DITHER_GRADIENT 0
#if LV_DITHER_GRADIENT
#define LV_DITHER_ERROR_DIFFUSION 0
#endif    /* LV_DITHER_GRADIENT */
#define LV_DISP_ROT_MAX_BUF (10U * 1024U)


/* GPU Configuration */

#if LV_USE_GPU_NXP_PXP
#endif    /* LV_USE_GPU_NXP_PXP */
#define LV_USE_GPU_SDL 0
#if LV_USE_GPU_SDL
#define LV_GPU_SDL_INCLUDE_PATH <SDL2/SDL.h>
#define LV_GPU_SDL_LRU_SIZE (1024 * 1024 * 8)
#define LV_GPU_SDL_CUSTOM_BLEND_MODE (SDL_VERSION_ATLEAST(2, 0, 6))
#endif    /* LV_USE_GPU_SDL */


/* Logging Configuration */

#define LV_USE_LOG 0
#if LV_USE_LOG
#define LV_LOG_LEVEL LV_LOG_LEVEL_WARN
#define LV_LOG_PRINTF 0
#define LV_LOG_TRACE_MEM 1
#define LV_LOG_TRACE_TIMER 1
#define LV_LOG_TRACE_INDEV 1
#define LV_LOG_TRACE_DISP_REFR 1
#define LV_LOG_TRACE_EVENT 1
#define LV_LOG_TRACE_OBJ_CREATE 1
#define LV_LOG_TRACE_LAYOUT 1
#define LV_LOG_TRACE_ANIM 1
#endif    /* LV_USE_LOG */


/* Asserts Configuration */

#define LV_USE_ASSERT_NULL 1
#define LV_USE_ASSERT_MALLOC 1
#define LV_USE_ASSERT_STYLE 0
#define LV_USE_ASSERT_MEM_INTEGRITY 0
#define LV_USE_ASSERT_OBJ 0
#define LV_ASSERT_HANDLER_INCLUDE <stdint.h>
#define LV_ASSERT_HANDLER while(1);


/* Other Features Configuration */

#define LV_USE_PERF_MONITOR 0
#if LV_USE_PERF_MONITOR
#define LV_USE_PERF_MONITOR_POS LV_ALIGN_BOTTOM_RIGHT
#endif    /* LV_USE_PERF_MONITOR */
#define LV_USE_MEM_MONITOR 0
#if LV_USE_MEM_MONITOR
#define LV_USE_MEM_MONITOR_POS LV_ALIGN_BOTTOM_LEFT
#endif    /* LV_USE_MEM_MONITOR */
#define LV_USE_REFR_DEBUG 0
#define LV_SPRINTF_CUSTOM 0
#if LV_SPRINTF_CUSTOM
#define LV_SPRINTF_INCLUDE <stdio.h>
#define lv_snprintf snprintf
#define lv_vsnprintf vsnprintf
#else     /* LV_SPRINTF_CUSTOM */
#define LV_SPRINTF_USE_FLOAT 0
#endif    /* LV_SPRINTF_CUSTOM */
#define LV_USE_USER_DATA 1
#define LV_ENABLE_GC 0
#if LV_ENABLE_GC
#define LV_GC_INCLUDE "gc.h"
#endif    /* LV_ENABLE_GC */


/* Compiler Settings */

#define LV_BIG_ENDIAN_SYSTEM 0
#define LV_ATTRIBUTE_TICK_INC
#define LV_ATTRIBUTE_TIMER_HANDLER
#define LV_ATTRIBUTE_FLUSH_READY
#ifndef LV_ATTRIBUTE_LARGE_CONST
#define LV_ATTRIBUTE_LARGE_CONST
#endif    /* LV_ATTRIBUTE_LARGE_CONST */
#define LV_ATTRIBUTE_LARGE_RAM_ARRAY
#define LV_ATTRIBUTE_FAST_MEM
#define LV_ATTRIBUTE_DMA
#define LV_EXPORT_CONST_INT(int_value) struct _silence_gcc_warning
#define LV_USE_LARGE_COORD 0


/* Font Usage */

#define LV_FONT_MONTSERRAT_8 0
#define LV_FONT_MONTSERRAT_10 0
#define LV_FONT_MONTSERRAT_12 1
#define LV_FONT_MONTSERRAT_14 1
#define LV_FONT_MONTSERRAT_16 0
#define LV_FONT_MONTSERRAT_18 0
#define LV_FONT_MONTSERRAT_20 0
#define LV_FONT_MONTSERRAT_22 0
#define LV_FONT_MONTSERRAT_24 0
#define LV_FONT_MONTSERRAT_26 0
#define LV_FONT_MONTSERRAT_28 0
#define LV_FONT_MONTSERRAT_30 0
#define LV_FONT_MONTSERRAT_32 0
#define LV_FONT_MONTSERRAT_34 0
#define LV_FONT_MONTSERRAT_36 0
#define LV_FONT_MONTSERRAT_38 0
#define LV_FONT_MONTSERRAT_40 0
#define LV_FONT_MONTSERRAT_42 0
#define LV_FONT_MONTSERRAT_44 0
#define LV_FONT_MONTSERRAT_46 0
#define LV_FONT_MONTSERRAT_48 0
#define LV_FONT_MONTSERRAT_12_SUBPX 0
#define LV_FONT_MONTSERRAT_28_COMPRESSED 0
#define LV_FONT_DEJAVU_16_PERSIAN_HEBREW 0
#define LV_FONT_SIMSUN_16_CJK 0
#define LV_FONT_UNSCII_8 0
#define LV_FONT_UNSCII_16 0
#define LV_FONT_CUSTOM_DECLARE
#define LV_FONT_DEFAULT &lv_font_montserrat_14
#define LV_FONT_FMT_TXT_LARGE 0
#define LV_USE_FONT_COMPRESSED 0
#define LV_USE_FONT_SUBPX 0
#if LV_USE_FONT_SUBPX
#define LV_FONT_SUBPX_BGR 0
#endif    /* LV_USE_FONT_SUBPX */


/* Text Settings */

#define LV_TXT_ENC LV_TXT_ENC_UTF8
#define LV_TXT_BREAK_CHARS " ,.;:-_"
#define LV_TXT_LINE_BREAK_LONG_LEN 0
#define LV_TXT_LINE_BREAK_LONG_PRE_MIN_LEN 3
#define LV_TXT_LINE_BREAK_LONG_POST_MIN_LEN 3
#define LV_TXT_COLOR_CMD "#"
#define LV_USE_BIDI 0
#if LV_USE_BIDI
#define LV_BIDI_BASE_DIR_DEF LV_BIDI_DIR_AUTO
#endif    /* LV_USE_BIDI */
#define LV_USE_ARABIC_PERSIAN_CHARS 0


/* Widget Usage */

#define LV_USE_ARC 0
#define LV_USE_ANIMIMG 0
#define LV_USE_BAR 0
#define LV_USE_BTN 1
#define LV_USE_BTNMATRIX 0
#define LV_USE_CANVAS 0
#define LV_USE_CHECKBOX 0
#define LV_USE_DROPDOWN 0
#define LV_USE_IMG 0
#define LV_USE_LABEL 1
#if LV_USE_LABEL
#define LV_LABEL_TEXT_SELECTION 1
#define LV_LABEL_LONG_TXT_HINT 1
#endif    /* LV_USE_LABEL */
#define LV_USE_LINE 0
#define LV_USE_ROLLER 0
#if LV_USE_ROLLER
#define LV_ROLLER_INF_PAGES 7
#endif    /* LV_USE_ROLLER */
#define LV_USE_SLIDER 0
#define LV_USE_SWITCH 0
#define LV_USE_TEXTAREA 0
#if LV_USE_TEXTAREA
#define LV_TEXTAREA_DEF_PWD_SHOW_TIME 1500
#endif    /* LV_USE_TEXTAREA */
#define LV_USE_TABLE 0
#define LV_USE_ANALOGCLOCK 0
#define LV_USE_CALENDAR 0
#if LV_USE_CALENDAR
#define LV_CALENDAR_WEEK_STARTS_MONDAY 0
#if LV_CALENDAR_WEEK_STARTS_MONDAY == 0
#define LV_CALENDAR_DEFAULT_DAY_NAMES {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"}
#endif    /* LV_CALENDAR_WEEK_STARTS_MONDAY */
#define LV_CALENDAR_DEFAULT_MONTH_NAMES {"January", "February", "March",  "April", "May",  "June", "July", "August", "September", "October", "November", "December"}
#define LV_USE_CALENDAR_HEADER_ARROW 1
#define LV_USE_CALENDAR_HEADER_DROPDOWN 1
#endif    /* LV_USE_CALENDAR */
#define LV_USE_CAROUSEL 0
#define LV_USE_CHART 0
#define LV_USE_COLORWHEEL 0
#define LV_USE_DCLOCK 0
#define LV_USE_IMGBTN 0
#define LV_USE_KEYBOARD 0
#define LV_USE_LED 1
#define LV_USE_LIST 0
#define LV_USE_MENU 0
#define LV_USE_METER 0
#define LV_USE_MSGBOX 0
#define LV_USE_RADIOBTN 0
#define LV_USE_SPAN 0
#if LV_USE_SPAN
#define LV_SPAN_SNIPPET_STACK_SIZE 64
#endif    /* LV_USE_SPAN */
#define LV_USE_SPINBOX 0
#define LV_USE_SPINNER 0
#define LV_USE_TABVIEW 0
#define LV_USE_TILEVIEW 0
#define LV_USE_WIN 0
#define LV_USE_ZH_KEYBOARD 0
#if LV_USE_ZH_KEYBOARD
#define LV_ZH_KEYBOARD_MINI 0
#endif    /* LV_USE_ZH_KEYBOARD */


/* Themes */

#define LV_USE_THEME_DEFAULT 1
#if LV_USE_THEME_DEFAULT
#define LV_THEME_DEFAULT_DARK 0
#define LV_THEME_DEFAULT_GROW 1
#define LV_THEME_DEFAULT_TRANSITION_TIME 80
#endif    /* LV_USE_THEME_DEFAULT */
#define LV_USE_THEME_BASIC 1
#define LV_USE_THEME_MONO 1


/* Layouts */

#define LV_USE_FLEX 1
#define LV_USE_GRID 1


/* 3rd party libraries */

#define LV_USE_FS_STDIO 0
#if LV_USE_FS_STDIO
#define LV_FS_STDIO_LETTER 'E'
#define LV_FS_STDIO_PATH ""
#define LV_FS_STDIO_CACHE_SIZE 0
#endif    /* LV_USE_FS_STDIO */
#define LV_USE_FS_POSIX 0
#if LV_USE_FS_POSIX
#define LV_FS_POSIX_LETTER '\0'
#define LV_FS_POSIX_PATH ""
#define LV_FS_POSIX_CACHE_SIZE 0
#endif    /* LV_USE_FS_POSIX */
#define LV_USE_FS_WIN32 0
#if LV_USE_FS_WIN32
#define LV_FS_WIN32_LETTER '\0'
#define LV_FS_WIN32_PATH ""
#define LV_FS_WIN32_CACHE_SIZE 0
#endif    /* LV_USE_FS_WIN32 */
#define LV_USE_FS_FATFS 0
#if LV_USE_FS_FATFS
#define LV_FS_FATFS_LETTER '\0'
#define LV_FS_FATFS_CACHE_SIZE 0
#endif    /* LV_USE_FS_FATFS */
#define LV_USE_PNG 0
#define LV_USE_BMP 0
#define LV_USE_SJPG 0
#define LV_USE_GIF 0
#define LV_USE_QRCODE 0
#define LV_USE_FREETYPE 0
#if LV_USE_FREETYPE
#define LV_FREETYPE_CACHE_SIZE (16U * 1024U)
#if LV_FREETYPE_CACHE_SIZE >= 0
#define LV_FREETYPE_SBIT_CACHE 0
#define LV_FREETYPE_CACHE_FT_FACES 0
#define LV_FREETYPE_CACHE_FT_SIZES 0
#endif    /* LV_FREETYPE_CACHE_SIZE */
#endif    /* LV_USE_FREETYPE */
#define LV_USE_RLOTTIE 0
#define LV_USE_FFMPEG 0
#if LV_USE_FFMPEG
#define LV_FFMPEG_AV_DUMP_FORMAT 0
#endif    /* LV_USE_FFMPEG */


/* Other Components */

#define LV_USE_SNAPSHOT 0
#define LV_USE_MONKEY 0
#define LV_USE_GRIDNAV 0
#define LV_USE_GUIDER_SIMULATOR 1

#endif