/*
 * Copyright 2023 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "guider_fonts.h"

typedef struct
{
	lv_obj_t *screen_main;
	bool screen_main_del;
	lv_obj_t *screen_main_view_root;
	lv_obj_t *screen_main_view_top;
	lv_obj_t *screen_main_lb_title;
	lv_obj_t *screen_main_lb_time;
	lv_obj_t *screen_main_view_iron;
	lv_obj_t *screen_main_lb_iron;
	lv_obj_t *screen_main_lb_iron_set_temp;
	lv_obj_t *screen_main_lb_iron_set_temp_value;
    lv_anim_t screen_main_lb_iron_set_temp_value_anim;
	lv_obj_t *screen_main_lb_iron_temp_value;
	lv_obj_t *screen_main_lb_v;
	lv_obj_t *screen_main_lb_va;
	lv_obj_t *screen_main_lb_unit_v;
	lv_obj_t *screen_main_lb_a;
	lv_obj_t *screen_main_lb_aa;
	lv_obj_t *screen_main_lb_unit_a;
	lv_obj_t *screen_main_lb_w;
	lv_obj_t *screen_main_lb_wa;
	lv_obj_t *screen_main_lb_unit_w;
	lv_obj_t *screen_main_lb_iron_preset_temp;
	lv_obj_t *screen_main_btn_iron_CH1;
	lv_obj_t *screen_main_btn_iron_CH1_label;
	lv_obj_t *screen_main_btn_iron_CH2;
	lv_obj_t *screen_main_btn_iron_CH2_label;
	lv_obj_t *screen_main_btn_iron_CH3;
	lv_obj_t *screen_main_btn_iron_CH3_label;
	lv_obj_t *screen_main_led_iron;
	lv_obj_t *screen_main_view_gun;
	lv_obj_t *screen_main_lb_gun;
	lv_obj_t *screen_main_led_gun;
	lv_obj_t *screen_main_lb_gun_set_temp;
	lv_obj_t *screen_main_lb_gun_set_temp_value;
    lv_anim_t screen_main_lb_gun_set_temp_value_anim;
	lv_obj_t *screen_main_lb_gun_temp_value;
	lv_obj_t *screen_main_lb_gun_fan_value;
    lv_anim_t screen_main_lb_gun_fan_value_anim;
	lv_obj_t *screen_main_lb_unit_baifenbi;
	lv_obj_t *screen_main_lb_hot;
    lv_anim_t screen_main_lb_gun_hot_anim;
	lv_obj_t *screen_main_lb_gun_preset_temp;
	lv_obj_t *screen_main_btn_gun_CH1;
	lv_obj_t *screen_main_btn_gun_CH1_label;
	lv_obj_t *screen_main_btn_gun_CH2;
	lv_obj_t *screen_main_btn_gun_CH2_label;
	lv_obj_t *screen_main_btn_gun_CH3;
	lv_obj_t *screen_main_btn_gun_CH3_label;
}lv_ui;

void init_scr_del_flag(lv_ui *ui);
void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
void setup_scr_screen_main(lv_ui *ui);

#ifdef __cplusplus
}
#endif
#endif