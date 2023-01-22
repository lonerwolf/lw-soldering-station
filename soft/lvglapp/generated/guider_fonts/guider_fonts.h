/*
 * Copyright 2023 NXP
 * SPDX-License-Identifier: MIT
 */
#ifndef GUIDER_FONTS_H
#define GUIDER_FONTS_H
#ifdef __cplusplus
extern "C" {
#endif

#if LVGL_VERSION_MAJOR == 7
#include "lv_font/lv_font.h"
#else
#include "font/lv_font.h"
#endif

LV_FONT_DECLARE(lv_font_SimHei_40)
LV_FONT_DECLARE(lv_font_SimHei_24)
LV_FONT_DECLARE(lv_font_sa_digital_number_80)
LV_FONT_DECLARE(lv_font_sa_digital_number_165)
LV_FONT_DECLARE(lv_font_SimHei_20)
LV_FONT_DECLARE(lv_font_sa_digital_number_30)
LV_FONT_DECLARE(lv_font_sa_digital_number_60)


#ifdef __cplusplus
}
#endif
#endif
