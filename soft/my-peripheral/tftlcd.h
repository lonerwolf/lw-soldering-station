//
// Created by lonerwolf on 2023/1/1.
//

#ifndef _TFTLCD_H
#define _TFTLCD_H

//修改宏变量 修改FSMC地址

#include <stdint.h>
#include "ch32v30x_conf.h"
#include "debug.h"

#define tftlcd_delay_ms(ms)          Delay_Ms(ms)//vTaskDelay(pdMS_TO_TICKS(ms))
#define TFTLCD_RST_ACTIVE()          GPIO_ResetBits(GPIOC,GPIO_Pin_5)
#define TFTLCD_RST_INACTIVE()        GPIO_SetBits(GPIOC,GPIO_Pin_5)
#define TFTLCD_BACKLIGHT_ACTIVE()    GPIO_SetBits(GPIOC,GPIO_Pin_8)
#define TFTLCD_BACKLIGHT_INACTIVE()  GPIO_ResetBits(GPIOC,GPIO_Pin_8)

//扫描方向定义
#define TFTLCD_SCAN_DIR_L2R_U2D 0 //从左到右,从上到下
#define TFTLCD_SCAN_DIR_L2R_D2U 1 //从左到右,从下到上
#define TFTLCD_SCAN_DIR_R2L_U2D 2 //从右到左,从上到下
#define TFTLCD_SCAN_DIR_R2L_D2U 3 //从右到左,从下到上

#define TFTLCD_SCAN_DIR_U2D_L2R 4 //从上到下,从左到右
#define TFTLCD_SCAN_DIR_U2D_R2L 5 //从上到下,从右到左
#define TFTLCD_SCAN_DIR_D2U_L2R 6 //从下到上,从左到右
#define TFTLCD_SCAN_DIR_D2U_R2L 7 //从下到上,从右到左

//画笔颜色
#define TFTLCD_COLOR_WHITE 0xFFFF
#define TFTLCD_COLOR_BLACK 0x0000
#define TFTLCD_COLOR_BLUE 0x001F
#define TFTLCD_COLOR_BRED 0XF81F
#define TFTLCD_COLOR_GRED 0XFFE0
#define TFTLCD_COLOR_GBLUE 0X07FF
#define TFTLCD_COLOR_RED 0xF800
#define TFTLCD_COLOR_MAGENTA 0xF81F
#define TFTLCD_COLOR_GREEN 0x07E0
#define TFTLCD_COLOR_CYAN 0x7FFF
#define TFTLCD_COLOR_YELLOW 0xFFE0
#define TFTLCD_COLOR_BROWN 0XBC40 //棕色
#define TFTLCD_COLOR_BRRED 0XFC07 //棕红色
#define TFTLCD_COLOR_GRAY 0X8430	 //灰色

typedef enum _tftlcd_dir{
    TFTLCD_DIR_VDIR=0,
    TFTLCD_DIR_HDIR,
}TFTLCD_Dir;

//TFTLCD
typedef struct _tftlcd {
    volatile uint16_t REG;
    volatile uint16_t RAM;
}TFTLCD_TypeDef;

//https://blog.csdn.net/qq_45578181/article/details/126512960
#define TFTLCD_BASE        ((uint32_t)(0x60000000 | 0x0001FFFE))
#define TFTLCD             ((TFTLCD_TypeDef *) TFTLCD_BASE)

typedef struct _tftlcd_dev{
    uint16_t width;
    uint16_t height;
    uint16_t id;
    enum _tftlcd_dir  dir;
    uint16_t wram_cmd;
    uint16_t setx_cmd;
    uint16_t sety_cmd;
}TFTLCD_DEV,*PT_TFTLCD_DEV;

int tftlcd_init(PT_TFTLCD_DEV handle);
void tftlcd_clear(PT_TFTLCD_DEV handle,uint16_t color);
void tftlcd_write_ram_prepare(PT_TFTLCD_DEV handle);
void tftlcd_set_cursor(PT_TFTLCD_DEV handle,uint16_t Xpos, uint16_t Ypos);
void tftlcd_set_window(PT_TFTLCD_DEV handle,uint16_t sx, uint16_t sy, uint16_t width, uint16_t height);
void tftlcd_set_rect(PT_TFTLCD_DEV handle,uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

#endif //_TFTLCD_H
