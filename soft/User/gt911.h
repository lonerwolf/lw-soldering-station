//
// Created by lonerwolf on 2023/1/8.
//

#ifndef _GT911_H
#define _GT911_H

#include <stdint.h>
#include <stdbool.h>

#define GT911_IIC_ERR_COUNT    1000
#define GT911_IIC_RADDR        0xBB      //IIC read address, should be 0x29
#define GT911_IIC_WADDR        0xBA      //IIC write address, should be 0x28

#define GT911_REG_PRODUCT_ID       0x8140    //ID of touch IC
#define GT911_REG_READ_XY          0x814E    //touch point information
#define GT911_REG_CONFIG           0x8047    /* 配置参数寄存器 */
#define GT911_REG_CONFIG_VERSION   0x8047    /* 配置文件版本号 */
#define GT911_REG_CONFIG_CHECKSUM  0x80FF    /* 配置文件校验码 */
#define GT911_REG_FIRMWARE_VERSION 0x8144    /* 固件版本号 */

#define GT911_TP_PRES_DOWN 0x80        //触摸屏被按下
#define GT911_TP_CATH_PRES 0x40        //有按键按下了

typedef struct {
    uint16_t x[5];
    uint16_t y[5];

    //状态 位7:按下1/松开0 位6:没有按键按下0 有按键按下1
    uint8_t sta;
} GT911_TP_Dev;

int gt911_init();

int gt911_get_xy(int16_t* x,int16_t* y);
int gt911_scan();

#endif //_GT911_H
