/*
 * Copyright 2023 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_screen_main(lv_ui *ui){

	//Write codes screen_main
	ui->screen_main = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui->screen_main, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_main_main_default
	static lv_style_t style_screen_main_main_main_default;
	if (style_screen_main_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_main_main_default);
	else
		lv_style_init(&style_screen_main_main_main_default);
	lv_style_set_bg_color(&style_screen_main_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_screen_main_main_main_default, 0);
	lv_obj_add_style(ui->screen_main, &style_screen_main_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_view_root
	ui->screen_main_view_root = lv_obj_create(ui->screen_main);
	lv_obj_set_pos(ui->screen_main_view_root, 0, 0);
	lv_obj_set_size(ui->screen_main_view_root, 800, 480);
	lv_obj_set_scrollbar_mode(ui->screen_main_view_root, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_view_root_main_main_default
	static lv_style_t style_screen_main_view_root_main_main_default;
	if (style_screen_main_view_root_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_view_root_main_main_default);
	else
		lv_style_init(&style_screen_main_view_root_main_main_default);
	lv_style_set_radius(&style_screen_main_view_root_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_view_root_main_main_default, lv_color_make(0x2b, 0x2d, 0x39));
	lv_style_set_bg_grad_color(&style_screen_main_view_root_main_main_default, lv_color_make(0x1a, 0x1a, 0x22));
	lv_style_set_bg_grad_dir(&style_screen_main_view_root_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_main_view_root_main_main_default, 255);
	lv_style_set_border_color(&style_screen_main_view_root_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_main_view_root_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_main_view_root_main_main_default, 255);
	lv_style_set_pad_left(&style_screen_main_view_root_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_view_root_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_view_root_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_view_root_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_view_root, &style_screen_main_view_root_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_view_top
	ui->screen_main_view_top = lv_obj_create(ui->screen_main);
	lv_obj_set_pos(ui->screen_main_view_top, 0, 0);
	lv_obj_set_size(ui->screen_main_view_top, 800, 52);
	lv_obj_set_scrollbar_mode(ui->screen_main_view_top, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_view_top_main_main_default
	static lv_style_t style_screen_main_view_top_main_main_default;
	if (style_screen_main_view_top_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_view_top_main_main_default);
	else
		lv_style_init(&style_screen_main_view_top_main_main_default);
	lv_style_set_radius(&style_screen_main_view_top_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_view_top_main_main_default, lv_color_make(0x38, 0x3b, 0x45));
	lv_style_set_bg_grad_color(&style_screen_main_view_top_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_main_view_top_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_view_top_main_main_default, 255);
	lv_style_set_border_color(&style_screen_main_view_top_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_main_view_top_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_main_view_top_main_main_default, 255);
	lv_style_set_pad_left(&style_screen_main_view_top_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_view_top_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_view_top_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_view_top_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_view_top, &style_screen_main_view_top_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_lb_title
	ui->screen_main_lb_title = lv_label_create(ui->screen_main_view_top);
	lv_obj_set_pos(ui->screen_main_lb_title, 22, 7);
	lv_obj_set_size(ui->screen_main_lb_title, 130, 40);
	lv_obj_set_scrollbar_mode(ui->screen_main_lb_title, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_main_lb_title, "lw焊台");
	lv_label_set_long_mode(ui->screen_main_lb_title, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_lb_title_main_main_default
	static lv_style_t style_screen_main_lb_title_main_main_default;
	if (style_screen_main_lb_title_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_lb_title_main_main_default);
	else
		lv_style_init(&style_screen_main_lb_title_main_main_default);
	lv_style_set_radius(&style_screen_main_lb_title_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_lb_title_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_main_lb_title_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_main_lb_title_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_lb_title_main_main_default, 0);
	lv_style_set_text_color(&style_screen_main_lb_title_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_main_lb_title_main_main_default, &lv_font_SimHei_40);
	lv_style_set_text_letter_space(&style_screen_main_lb_title_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_main_lb_title_main_main_default, 0);
	lv_style_set_text_align(&style_screen_main_lb_title_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_main_lb_title_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_lb_title_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_lb_title_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_lb_title_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_lb_title, &style_screen_main_lb_title_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_lb_time
	ui->screen_main_lb_time = lv_label_create(ui->screen_main_view_top);
	lv_obj_set_pos(ui->screen_main_lb_time, 490, 14);
	lv_obj_set_size(ui->screen_main_lb_time, 300, 24);
	lv_obj_set_scrollbar_mode(ui->screen_main_lb_time, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_main_lb_time, "2020-10-10 10:10:10");
	lv_label_set_long_mode(ui->screen_main_lb_time, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_lb_time_main_main_default
	static lv_style_t style_screen_main_lb_time_main_main_default;
	if (style_screen_main_lb_time_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_lb_time_main_main_default);
	else
		lv_style_init(&style_screen_main_lb_time_main_main_default);
	lv_style_set_radius(&style_screen_main_lb_time_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_lb_time_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_main_lb_time_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_main_lb_time_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_lb_time_main_main_default, 0);
	lv_style_set_text_color(&style_screen_main_lb_time_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_main_lb_time_main_main_default, &lv_font_SimHei_24);
	lv_style_set_text_letter_space(&style_screen_main_lb_time_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_main_lb_time_main_main_default, 0);
	lv_style_set_text_align(&style_screen_main_lb_time_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_main_lb_time_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_lb_time_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_lb_time_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_lb_time_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_lb_time, &style_screen_main_lb_time_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_view_iron
	ui->screen_main_view_iron = lv_obj_create(ui->screen_main);
	lv_obj_set_pos(ui->screen_main_view_iron, 0, 52);
	lv_obj_set_size(ui->screen_main_view_iron, 400, 428);
	lv_obj_set_scrollbar_mode(ui->screen_main_view_iron, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_view_iron_main_main_default
	static lv_style_t style_screen_main_view_iron_main_main_default;
	if (style_screen_main_view_iron_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_view_iron_main_main_default);
	else
		lv_style_init(&style_screen_main_view_iron_main_main_default);
	lv_style_set_radius(&style_screen_main_view_iron_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_view_iron_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_main_view_iron_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_main_view_iron_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_view_iron_main_main_default, 0);
	lv_style_set_border_color(&style_screen_main_view_iron_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_main_view_iron_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_main_view_iron_main_main_default, 255);
	lv_style_set_pad_left(&style_screen_main_view_iron_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_view_iron_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_view_iron_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_view_iron_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_view_iron, &style_screen_main_view_iron_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_lb_iron
	ui->screen_main_lb_iron = lv_label_create(ui->screen_main_view_iron);
	lv_obj_set_pos(ui->screen_main_lb_iron, 5, 7);
	lv_obj_set_size(ui->screen_main_lb_iron, 100, 40);
	lv_obj_set_scrollbar_mode(ui->screen_main_lb_iron, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_main_lb_iron, "烙铁");
	lv_label_set_long_mode(ui->screen_main_lb_iron, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_lb_iron_main_main_default
	static lv_style_t style_screen_main_lb_iron_main_main_default;
	if (style_screen_main_lb_iron_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_lb_iron_main_main_default);
	else
		lv_style_init(&style_screen_main_lb_iron_main_main_default);
	lv_style_set_radius(&style_screen_main_lb_iron_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_lb_iron_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_main_lb_iron_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_main_lb_iron_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_lb_iron_main_main_default, 0);
	lv_style_set_text_color(&style_screen_main_lb_iron_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_main_lb_iron_main_main_default, &lv_font_SimHei_40);
	lv_style_set_text_letter_space(&style_screen_main_lb_iron_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_main_lb_iron_main_main_default, 0);
	lv_style_set_text_align(&style_screen_main_lb_iron_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_main_lb_iron_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_lb_iron_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_lb_iron_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_lb_iron_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_lb_iron, &style_screen_main_lb_iron_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_lb_iron_set_temp
	ui->screen_main_lb_iron_set_temp = lv_label_create(ui->screen_main_view_iron);
	lv_obj_set_pos(ui->screen_main_lb_iron_set_temp, 10, 59);
	lv_obj_set_size(ui->screen_main_lb_iron_set_temp, 170, 40);
	lv_obj_set_scrollbar_mode(ui->screen_main_lb_iron_set_temp, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_main_lb_iron_set_temp, "设置温度");
	lv_label_set_long_mode(ui->screen_main_lb_iron_set_temp, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_lb_iron_set_temp_main_main_default
	static lv_style_t style_screen_main_lb_iron_set_temp_main_main_default;
	if (style_screen_main_lb_iron_set_temp_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_lb_iron_set_temp_main_main_default);
	else
		lv_style_init(&style_screen_main_lb_iron_set_temp_main_main_default);
	lv_style_set_radius(&style_screen_main_lb_iron_set_temp_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_lb_iron_set_temp_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_main_lb_iron_set_temp_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_main_lb_iron_set_temp_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_lb_iron_set_temp_main_main_default, 0);
	lv_style_set_text_color(&style_screen_main_lb_iron_set_temp_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_main_lb_iron_set_temp_main_main_default, &lv_font_SimHei_40);
	lv_style_set_text_letter_space(&style_screen_main_lb_iron_set_temp_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_main_lb_iron_set_temp_main_main_default, 0);
	lv_style_set_text_align(&style_screen_main_lb_iron_set_temp_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_main_lb_iron_set_temp_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_lb_iron_set_temp_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_lb_iron_set_temp_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_lb_iron_set_temp_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_lb_iron_set_temp, &style_screen_main_lb_iron_set_temp_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_lb_iron_set_temp_value
	ui->screen_main_lb_iron_set_temp_value = lv_label_create(ui->screen_main_view_iron);
	lv_obj_set_pos(ui->screen_main_lb_iron_set_temp_value, 181, 11);
	lv_obj_set_size(ui->screen_main_lb_iron_set_temp_value, 200, 81);
	lv_obj_set_scrollbar_mode(ui->screen_main_lb_iron_set_temp_value, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_main_lb_iron_set_temp_value, "450");
	lv_label_set_long_mode(ui->screen_main_lb_iron_set_temp_value, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_lb_iron_set_temp_value_main_main_default
	static lv_style_t style_screen_main_lb_iron_set_temp_value_main_main_default;
	if (style_screen_main_lb_iron_set_temp_value_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_lb_iron_set_temp_value_main_main_default);
	else
		lv_style_init(&style_screen_main_lb_iron_set_temp_value_main_main_default);
	lv_style_set_radius(&style_screen_main_lb_iron_set_temp_value_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_lb_iron_set_temp_value_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_main_lb_iron_set_temp_value_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_main_lb_iron_set_temp_value_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_lb_iron_set_temp_value_main_main_default, 0);
	lv_style_set_text_color(&style_screen_main_lb_iron_set_temp_value_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_main_lb_iron_set_temp_value_main_main_default, &lv_font_sa_digital_number_80);
	lv_style_set_text_letter_space(&style_screen_main_lb_iron_set_temp_value_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_main_lb_iron_set_temp_value_main_main_default, 0);
	lv_style_set_text_align(&style_screen_main_lb_iron_set_temp_value_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_main_lb_iron_set_temp_value_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_lb_iron_set_temp_value_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_lb_iron_set_temp_value_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_lb_iron_set_temp_value_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_lb_iron_set_temp_value, &style_screen_main_lb_iron_set_temp_value_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_lb_iron_temp_value
	ui->screen_main_lb_iron_temp_value = lv_label_create(ui->screen_main_view_iron);
	lv_obj_set_pos(ui->screen_main_lb_iron_temp_value, 0, 104);
	lv_obj_set_size(ui->screen_main_lb_iron_temp_value, 400, 180);
	lv_obj_set_scrollbar_mode(ui->screen_main_lb_iron_temp_value, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_main_lb_iron_temp_value, "360");
	lv_label_set_long_mode(ui->screen_main_lb_iron_temp_value, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_lb_iron_temp_value_main_main_default
	static lv_style_t style_screen_main_lb_iron_temp_value_main_main_default;
	if (style_screen_main_lb_iron_temp_value_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_lb_iron_temp_value_main_main_default);
	else
		lv_style_init(&style_screen_main_lb_iron_temp_value_main_main_default);
	lv_style_set_radius(&style_screen_main_lb_iron_temp_value_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_lb_iron_temp_value_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_main_lb_iron_temp_value_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_main_lb_iron_temp_value_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_lb_iron_temp_value_main_main_default, 0);
	lv_style_set_text_color(&style_screen_main_lb_iron_temp_value_main_main_default, lv_color_make(0xff, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_main_lb_iron_temp_value_main_main_default, &lv_font_sa_digital_number_165);
	lv_style_set_text_letter_space(&style_screen_main_lb_iron_temp_value_main_main_default, 0);
	lv_style_set_text_line_space(&style_screen_main_lb_iron_temp_value_main_main_default, 0);
	lv_style_set_text_align(&style_screen_main_lb_iron_temp_value_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_main_lb_iron_temp_value_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_lb_iron_temp_value_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_lb_iron_temp_value_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_lb_iron_temp_value_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_lb_iron_temp_value, &style_screen_main_lb_iron_temp_value_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_lb_v
	ui->screen_main_lb_v = lv_label_create(ui->screen_main_view_iron);
	lv_obj_set_pos(ui->screen_main_lb_v, 10, 293);
	lv_obj_set_size(ui->screen_main_lb_v, 60, 20);
	lv_obj_set_scrollbar_mode(ui->screen_main_lb_v, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_main_lb_v, "电压:");
	lv_label_set_long_mode(ui->screen_main_lb_v, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_lb_v_main_main_default
	static lv_style_t style_screen_main_lb_v_main_main_default;
	if (style_screen_main_lb_v_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_lb_v_main_main_default);
	else
		lv_style_init(&style_screen_main_lb_v_main_main_default);
	lv_style_set_radius(&style_screen_main_lb_v_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_lb_v_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_main_lb_v_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_main_lb_v_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_lb_v_main_main_default, 0);
	lv_style_set_text_color(&style_screen_main_lb_v_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_main_lb_v_main_main_default, &lv_font_SimHei_20);
	lv_style_set_text_letter_space(&style_screen_main_lb_v_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_main_lb_v_main_main_default, 0);
	lv_style_set_text_align(&style_screen_main_lb_v_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_main_lb_v_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_lb_v_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_lb_v_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_lb_v_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_lb_v, &style_screen_main_lb_v_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_lb_va
	ui->screen_main_lb_va = lv_label_create(ui->screen_main_view_iron);
	lv_obj_set_pos(ui->screen_main_lb_va, 71, 286);
	lv_obj_set_size(ui->screen_main_lb_va, 110, 30);
	lv_obj_set_scrollbar_mode(ui->screen_main_lb_va, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_main_lb_va, "24.00\n");
	lv_label_set_long_mode(ui->screen_main_lb_va, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_lb_va_main_main_default
	static lv_style_t style_screen_main_lb_va_main_main_default;
	if (style_screen_main_lb_va_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_lb_va_main_main_default);
	else
		lv_style_init(&style_screen_main_lb_va_main_main_default);
	lv_style_set_radius(&style_screen_main_lb_va_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_lb_va_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_main_lb_va_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_main_lb_va_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_lb_va_main_main_default, 0);
	lv_style_set_text_color(&style_screen_main_lb_va_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_main_lb_va_main_main_default, &lv_font_sa_digital_number_30);
	lv_style_set_text_letter_space(&style_screen_main_lb_va_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_main_lb_va_main_main_default, 0);
	lv_style_set_text_align(&style_screen_main_lb_va_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_main_lb_va_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_lb_va_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_lb_va_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_lb_va_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_lb_va, &style_screen_main_lb_va_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_lb_unit_v
	ui->screen_main_lb_unit_v = lv_label_create(ui->screen_main_view_iron);
	lv_obj_set_pos(ui->screen_main_lb_unit_v, 182, 298);
	lv_obj_set_size(ui->screen_main_lb_unit_v, 15, 15);
	lv_obj_set_scrollbar_mode(ui->screen_main_lb_unit_v, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_main_lb_unit_v, "V");
	lv_label_set_long_mode(ui->screen_main_lb_unit_v, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_lb_unit_v_main_main_default
	static lv_style_t style_screen_main_lb_unit_v_main_main_default;
	if (style_screen_main_lb_unit_v_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_lb_unit_v_main_main_default);
	else
		lv_style_init(&style_screen_main_lb_unit_v_main_main_default);
	lv_style_set_radius(&style_screen_main_lb_unit_v_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_lb_unit_v_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_main_lb_unit_v_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_main_lb_unit_v_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_lb_unit_v_main_main_default, 0);
	lv_style_set_text_color(&style_screen_main_lb_unit_v_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_main_lb_unit_v_main_main_default, &lv_font_SimHei_20);
	lv_style_set_text_letter_space(&style_screen_main_lb_unit_v_main_main_default, 0);
	lv_style_set_text_line_space(&style_screen_main_lb_unit_v_main_main_default, 0);
	lv_style_set_text_align(&style_screen_main_lb_unit_v_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_main_lb_unit_v_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_lb_unit_v_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_lb_unit_v_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_lb_unit_v_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_lb_unit_v, &style_screen_main_lb_unit_v_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_lb_a
	ui->screen_main_lb_a = lv_label_create(ui->screen_main_view_iron);
	lv_obj_set_pos(ui->screen_main_lb_a, 203, 293);
	lv_obj_set_size(ui->screen_main_lb_a, 60, 20);
	lv_obj_set_scrollbar_mode(ui->screen_main_lb_a, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_main_lb_a, "电流:");
	lv_label_set_long_mode(ui->screen_main_lb_a, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_lb_a_main_main_default
	static lv_style_t style_screen_main_lb_a_main_main_default;
	if (style_screen_main_lb_a_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_lb_a_main_main_default);
	else
		lv_style_init(&style_screen_main_lb_a_main_main_default);
	lv_style_set_radius(&style_screen_main_lb_a_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_lb_a_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_main_lb_a_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_main_lb_a_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_lb_a_main_main_default, 0);
	lv_style_set_text_color(&style_screen_main_lb_a_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_main_lb_a_main_main_default, &lv_font_SimHei_20);
	lv_style_set_text_letter_space(&style_screen_main_lb_a_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_main_lb_a_main_main_default, 0);
	lv_style_set_text_align(&style_screen_main_lb_a_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_main_lb_a_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_lb_a_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_lb_a_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_lb_a_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_lb_a, &style_screen_main_lb_a_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_lb_aa
	ui->screen_main_lb_aa = lv_label_create(ui->screen_main_view_iron);
	lv_obj_set_pos(ui->screen_main_lb_aa, 264, 286);
	lv_obj_set_size(ui->screen_main_lb_aa, 110, 30);
	lv_obj_set_scrollbar_mode(ui->screen_main_lb_aa, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_main_lb_aa, "10.00");
	lv_label_set_long_mode(ui->screen_main_lb_aa, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_lb_aa_main_main_default
	static lv_style_t style_screen_main_lb_aa_main_main_default;
	if (style_screen_main_lb_aa_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_lb_aa_main_main_default);
	else
		lv_style_init(&style_screen_main_lb_aa_main_main_default);
	lv_style_set_radius(&style_screen_main_lb_aa_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_lb_aa_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_main_lb_aa_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_main_lb_aa_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_lb_aa_main_main_default, 0);
	lv_style_set_text_color(&style_screen_main_lb_aa_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_main_lb_aa_main_main_default, &lv_font_sa_digital_number_30);
	lv_style_set_text_letter_space(&style_screen_main_lb_aa_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_main_lb_aa_main_main_default, 0);
	lv_style_set_text_align(&style_screen_main_lb_aa_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_main_lb_aa_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_lb_aa_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_lb_aa_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_lb_aa_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_lb_aa, &style_screen_main_lb_aa_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_lb_unit_a
	ui->screen_main_lb_unit_a = lv_label_create(ui->screen_main_view_iron);
	lv_obj_set_pos(ui->screen_main_lb_unit_a, 375, 298);
	lv_obj_set_size(ui->screen_main_lb_unit_a, 15, 15);
	lv_obj_set_scrollbar_mode(ui->screen_main_lb_unit_a, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_main_lb_unit_a, "A");
	lv_label_set_long_mode(ui->screen_main_lb_unit_a, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_lb_unit_a_main_main_default
	static lv_style_t style_screen_main_lb_unit_a_main_main_default;
	if (style_screen_main_lb_unit_a_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_lb_unit_a_main_main_default);
	else
		lv_style_init(&style_screen_main_lb_unit_a_main_main_default);
	lv_style_set_radius(&style_screen_main_lb_unit_a_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_lb_unit_a_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_main_lb_unit_a_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_main_lb_unit_a_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_lb_unit_a_main_main_default, 0);
	lv_style_set_text_color(&style_screen_main_lb_unit_a_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_main_lb_unit_a_main_main_default, &lv_font_SimHei_20);
	lv_style_set_text_letter_space(&style_screen_main_lb_unit_a_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_main_lb_unit_a_main_main_default, 0);
	lv_style_set_text_align(&style_screen_main_lb_unit_a_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_main_lb_unit_a_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_lb_unit_a_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_lb_unit_a_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_lb_unit_a_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_lb_unit_a, &style_screen_main_lb_unit_a_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_lb_w
	ui->screen_main_lb_w = lv_label_create(ui->screen_main_view_iron);
	lv_obj_set_pos(ui->screen_main_lb_w, 85, 335);
	lv_obj_set_size(ui->screen_main_lb_w, 56, 20);
	lv_obj_set_scrollbar_mode(ui->screen_main_lb_w, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_main_lb_w, "功率:");
	lv_label_set_long_mode(ui->screen_main_lb_w, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_lb_w_main_main_default
	static lv_style_t style_screen_main_lb_w_main_main_default;
	if (style_screen_main_lb_w_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_lb_w_main_main_default);
	else
		lv_style_init(&style_screen_main_lb_w_main_main_default);
	lv_style_set_radius(&style_screen_main_lb_w_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_lb_w_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_main_lb_w_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_main_lb_w_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_lb_w_main_main_default, 0);
	lv_style_set_text_color(&style_screen_main_lb_w_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_main_lb_w_main_main_default, &lv_font_SimHei_20);
	lv_style_set_text_letter_space(&style_screen_main_lb_w_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_main_lb_w_main_main_default, 0);
	lv_style_set_text_align(&style_screen_main_lb_w_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_main_lb_w_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_lb_w_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_lb_w_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_lb_w_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_lb_w, &style_screen_main_lb_w_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_lb_wa
	ui->screen_main_lb_wa = lv_label_create(ui->screen_main_view_iron);
	lv_obj_set_pos(ui->screen_main_lb_wa, 142, 328);
	lv_obj_set_size(ui->screen_main_lb_wa, 140, 35);
	lv_obj_set_scrollbar_mode(ui->screen_main_lb_wa, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_main_lb_wa, "240.00");
	lv_label_set_long_mode(ui->screen_main_lb_wa, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_lb_wa_main_main_default
	static lv_style_t style_screen_main_lb_wa_main_main_default;
	if (style_screen_main_lb_wa_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_lb_wa_main_main_default);
	else
		lv_style_init(&style_screen_main_lb_wa_main_main_default);
	lv_style_set_radius(&style_screen_main_lb_wa_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_lb_wa_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_main_lb_wa_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_main_lb_wa_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_lb_wa_main_main_default, 0);
	lv_style_set_text_color(&style_screen_main_lb_wa_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_main_lb_wa_main_main_default, &lv_font_sa_digital_number_30);
	lv_style_set_text_letter_space(&style_screen_main_lb_wa_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_main_lb_wa_main_main_default, 0);
	lv_style_set_text_align(&style_screen_main_lb_wa_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_main_lb_wa_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_lb_wa_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_lb_wa_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_lb_wa_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_lb_wa, &style_screen_main_lb_wa_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_lb_unit_w
	ui->screen_main_lb_unit_w = lv_label_create(ui->screen_main_view_iron);
	lv_obj_set_pos(ui->screen_main_lb_unit_w, 283, 340);
	lv_obj_set_size(ui->screen_main_lb_unit_w, 15, 15);
	lv_obj_set_scrollbar_mode(ui->screen_main_lb_unit_w, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_main_lb_unit_w, "W");
	lv_label_set_long_mode(ui->screen_main_lb_unit_w, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_lb_unit_w_main_main_default
	static lv_style_t style_screen_main_lb_unit_w_main_main_default;
	if (style_screen_main_lb_unit_w_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_lb_unit_w_main_main_default);
	else
		lv_style_init(&style_screen_main_lb_unit_w_main_main_default);
	lv_style_set_radius(&style_screen_main_lb_unit_w_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_lb_unit_w_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_main_lb_unit_w_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_main_lb_unit_w_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_lb_unit_w_main_main_default, 0);
	lv_style_set_text_color(&style_screen_main_lb_unit_w_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_main_lb_unit_w_main_main_default, &lv_font_SimHei_20);
	lv_style_set_text_letter_space(&style_screen_main_lb_unit_w_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_main_lb_unit_w_main_main_default, 0);
	lv_style_set_text_align(&style_screen_main_lb_unit_w_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_main_lb_unit_w_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_lb_unit_w_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_lb_unit_w_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_lb_unit_w_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_lb_unit_w, &style_screen_main_lb_unit_w_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_lb_iron_preset_temp
	ui->screen_main_lb_iron_preset_temp = lv_label_create(ui->screen_main_view_iron);
	lv_obj_set_pos(ui->screen_main_lb_iron_preset_temp, 5, 385);
	lv_obj_set_size(ui->screen_main_lb_iron_preset_temp, 110, 24);
	lv_obj_set_scrollbar_mode(ui->screen_main_lb_iron_preset_temp, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_main_lb_iron_preset_temp, "预设温度");
	lv_label_set_long_mode(ui->screen_main_lb_iron_preset_temp, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_lb_iron_preset_temp_main_main_default
	static lv_style_t style_screen_main_lb_iron_preset_temp_main_main_default;
	if (style_screen_main_lb_iron_preset_temp_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_lb_iron_preset_temp_main_main_default);
	else
		lv_style_init(&style_screen_main_lb_iron_preset_temp_main_main_default);
	lv_style_set_radius(&style_screen_main_lb_iron_preset_temp_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_lb_iron_preset_temp_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_main_lb_iron_preset_temp_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_main_lb_iron_preset_temp_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_lb_iron_preset_temp_main_main_default, 0);
	lv_style_set_text_color(&style_screen_main_lb_iron_preset_temp_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_main_lb_iron_preset_temp_main_main_default, &lv_font_SimHei_24);
	lv_style_set_text_letter_space(&style_screen_main_lb_iron_preset_temp_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_main_lb_iron_preset_temp_main_main_default, 0);
	lv_style_set_text_align(&style_screen_main_lb_iron_preset_temp_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_main_lb_iron_preset_temp_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_lb_iron_preset_temp_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_lb_iron_preset_temp_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_lb_iron_preset_temp_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_lb_iron_preset_temp, &style_screen_main_lb_iron_preset_temp_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_btn_iron_CH1
	ui->screen_main_btn_iron_CH1 = lv_btn_create(ui->screen_main_view_iron);
	lv_obj_set_pos(ui->screen_main_btn_iron_CH1, 120, 370);
	lv_obj_set_size(ui->screen_main_btn_iron_CH1, 80, 50);
	lv_obj_set_scrollbar_mode(ui->screen_main_btn_iron_CH1, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_btn_iron_ch1_main_main_default
	static lv_style_t style_screen_main_btn_iron_ch1_main_main_default;
	if (style_screen_main_btn_iron_ch1_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_btn_iron_ch1_main_main_default);
	else
		lv_style_init(&style_screen_main_btn_iron_ch1_main_main_default);
	lv_style_set_radius(&style_screen_main_btn_iron_ch1_main_main_default, 5);
	lv_style_set_bg_color(&style_screen_main_btn_iron_ch1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_main_btn_iron_ch1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_main_btn_iron_ch1_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_btn_iron_ch1_main_main_default, 255);
	lv_style_set_border_color(&style_screen_main_btn_iron_ch1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_main_btn_iron_ch1_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_main_btn_iron_ch1_main_main_default, 255);
	lv_style_set_text_color(&style_screen_main_btn_iron_ch1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_main_btn_iron_ch1_main_main_default, &lv_font_SimHei_24);
	lv_style_set_text_align(&style_screen_main_btn_iron_ch1_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_obj_add_style(ui->screen_main_btn_iron_CH1, &style_screen_main_btn_iron_ch1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	//lv_obj_add_flag(ui->screen_main_btn_iron_CH1, LV_OBJ_FLAG_CHECKABLE);
	ui->screen_main_btn_iron_CH1_label = lv_label_create(ui->screen_main_btn_iron_CH1);
	lv_label_set_text(ui->screen_main_btn_iron_CH1_label, "CH1");
	lv_obj_set_style_pad_all(ui->screen_main_btn_iron_CH1, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->screen_main_btn_iron_CH1_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes screen_main_btn_iron_CH2
	ui->screen_main_btn_iron_CH2 = lv_btn_create(ui->screen_main_view_iron);
	lv_obj_set_pos(ui->screen_main_btn_iron_CH2, 215, 370);
	lv_obj_set_size(ui->screen_main_btn_iron_CH2, 80, 50);
	lv_obj_set_scrollbar_mode(ui->screen_main_btn_iron_CH2, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_btn_iron_ch2_main_main_default
	static lv_style_t style_screen_main_btn_iron_ch2_main_main_default;
	if (style_screen_main_btn_iron_ch2_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_btn_iron_ch2_main_main_default);
	else
		lv_style_init(&style_screen_main_btn_iron_ch2_main_main_default);
	lv_style_set_radius(&style_screen_main_btn_iron_ch2_main_main_default, 5);
	lv_style_set_bg_color(&style_screen_main_btn_iron_ch2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_main_btn_iron_ch2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_main_btn_iron_ch2_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_btn_iron_ch2_main_main_default, 255);
	lv_style_set_border_color(&style_screen_main_btn_iron_ch2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_main_btn_iron_ch2_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_main_btn_iron_ch2_main_main_default, 255);
	lv_style_set_text_color(&style_screen_main_btn_iron_ch2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_main_btn_iron_ch2_main_main_default, &lv_font_SimHei_24);
	lv_style_set_text_align(&style_screen_main_btn_iron_ch2_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_obj_add_style(ui->screen_main_btn_iron_CH2, &style_screen_main_btn_iron_ch2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	//lv_obj_add_flag(ui->screen_main_btn_iron_CH2, LV_OBJ_FLAG_CHECKABLE);
	ui->screen_main_btn_iron_CH2_label = lv_label_create(ui->screen_main_btn_iron_CH2);
	lv_label_set_text(ui->screen_main_btn_iron_CH2_label, "CH2");
	lv_obj_set_style_pad_all(ui->screen_main_btn_iron_CH2, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->screen_main_btn_iron_CH2_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes screen_main_btn_iron_CH3
	ui->screen_main_btn_iron_CH3 = lv_btn_create(ui->screen_main_view_iron);
	lv_obj_set_pos(ui->screen_main_btn_iron_CH3, 310, 370);
	lv_obj_set_size(ui->screen_main_btn_iron_CH3, 80, 50);
	lv_obj_set_scrollbar_mode(ui->screen_main_btn_iron_CH3, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_btn_iron_ch3_main_main_default
	static lv_style_t style_screen_main_btn_iron_ch3_main_main_default;
	if (style_screen_main_btn_iron_ch3_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_btn_iron_ch3_main_main_default);
	else
		lv_style_init(&style_screen_main_btn_iron_ch3_main_main_default);
	lv_style_set_radius(&style_screen_main_btn_iron_ch3_main_main_default, 5);
	lv_style_set_bg_color(&style_screen_main_btn_iron_ch3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_main_btn_iron_ch3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_main_btn_iron_ch3_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_btn_iron_ch3_main_main_default, 255);
	lv_style_set_border_color(&style_screen_main_btn_iron_ch3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_main_btn_iron_ch3_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_main_btn_iron_ch3_main_main_default, 255);
	lv_style_set_text_color(&style_screen_main_btn_iron_ch3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_main_btn_iron_ch3_main_main_default, &lv_font_SimHei_24);
	lv_style_set_text_align(&style_screen_main_btn_iron_ch3_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_obj_add_style(ui->screen_main_btn_iron_CH3, &style_screen_main_btn_iron_ch3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	//lv_obj_add_flag(ui->screen_main_btn_iron_CH3, LV_OBJ_FLAG_CHECKABLE);
	ui->screen_main_btn_iron_CH3_label = lv_label_create(ui->screen_main_btn_iron_CH3);
	lv_label_set_text(ui->screen_main_btn_iron_CH3_label, "CH3");
	lv_obj_set_style_pad_all(ui->screen_main_btn_iron_CH3, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->screen_main_btn_iron_CH3_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes screen_main_led_iron
	ui->screen_main_led_iron = lv_led_create(ui->screen_main_view_iron);
	lv_obj_set_pos(ui->screen_main_led_iron, 125, 8);
	lv_obj_set_size(ui->screen_main_led_iron, 40, 40);
	lv_obj_set_scrollbar_mode(ui->screen_main_led_iron, LV_SCROLLBAR_MODE_OFF);
	lv_led_set_brightness(ui->screen_main_led_iron, 255);
	lv_led_set_color(ui->screen_main_led_iron, lv_color_make(0xff, 0x33, 0x33));

	//Write codes screen_main_view_gun
	ui->screen_main_view_gun = lv_obj_create(ui->screen_main);
	lv_obj_set_pos(ui->screen_main_view_gun, 400, 52);
	lv_obj_set_size(ui->screen_main_view_gun, 400, 428);
	lv_obj_set_scrollbar_mode(ui->screen_main_view_gun, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_view_gun_main_main_default
	static lv_style_t style_screen_main_view_gun_main_main_default;
	if (style_screen_main_view_gun_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_view_gun_main_main_default);
	else
		lv_style_init(&style_screen_main_view_gun_main_main_default);
	lv_style_set_radius(&style_screen_main_view_gun_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_view_gun_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_main_view_gun_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_main_view_gun_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_view_gun_main_main_default, 0);
	lv_style_set_border_color(&style_screen_main_view_gun_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_main_view_gun_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_main_view_gun_main_main_default, 255);
	lv_style_set_pad_left(&style_screen_main_view_gun_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_view_gun_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_view_gun_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_view_gun_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_view_gun, &style_screen_main_view_gun_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_lb_gun
	ui->screen_main_lb_gun = lv_label_create(ui->screen_main_view_gun);
	lv_obj_set_pos(ui->screen_main_lb_gun, 5, 7);
	lv_obj_set_size(ui->screen_main_lb_gun, 100, 40);
	lv_obj_set_scrollbar_mode(ui->screen_main_lb_gun, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_main_lb_gun, "风枪");
	lv_label_set_long_mode(ui->screen_main_lb_gun, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_lb_gun_main_main_default
	static lv_style_t style_screen_main_lb_gun_main_main_default;
	if (style_screen_main_lb_gun_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_lb_gun_main_main_default);
	else
		lv_style_init(&style_screen_main_lb_gun_main_main_default);
	lv_style_set_radius(&style_screen_main_lb_gun_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_lb_gun_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_main_lb_gun_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_main_lb_gun_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_lb_gun_main_main_default, 0);
	lv_style_set_text_color(&style_screen_main_lb_gun_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_main_lb_gun_main_main_default, &lv_font_SimHei_40);
	lv_style_set_text_letter_space(&style_screen_main_lb_gun_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_main_lb_gun_main_main_default, 0);
	lv_style_set_text_align(&style_screen_main_lb_gun_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_main_lb_gun_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_lb_gun_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_lb_gun_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_lb_gun_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_lb_gun, &style_screen_main_lb_gun_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_led_gun
	ui->screen_main_led_gun = lv_led_create(ui->screen_main_view_gun);
	lv_obj_set_pos(ui->screen_main_led_gun, 125, 8);
	lv_obj_set_size(ui->screen_main_led_gun, 40, 40);
	lv_obj_set_scrollbar_mode(ui->screen_main_led_gun, LV_SCROLLBAR_MODE_OFF);
	lv_led_set_brightness(ui->screen_main_led_gun, 255);
	lv_led_set_color(ui->screen_main_led_gun, lv_color_make(0xff, 0x33, 0x33));

	//Write codes screen_main_lb_gun_set_temp
	ui->screen_main_lb_gun_set_temp = lv_label_create(ui->screen_main_view_gun);
	lv_obj_set_pos(ui->screen_main_lb_gun_set_temp, 10, 59);
	lv_obj_set_size(ui->screen_main_lb_gun_set_temp, 170, 40);
	lv_obj_set_scrollbar_mode(ui->screen_main_lb_gun_set_temp, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_main_lb_gun_set_temp, "设置温度");
	lv_label_set_long_mode(ui->screen_main_lb_gun_set_temp, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_lb_gun_set_temp_main_main_default
	static lv_style_t style_screen_main_lb_gun_set_temp_main_main_default;
	if (style_screen_main_lb_gun_set_temp_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_lb_gun_set_temp_main_main_default);
	else
		lv_style_init(&style_screen_main_lb_gun_set_temp_main_main_default);
	lv_style_set_radius(&style_screen_main_lb_gun_set_temp_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_lb_gun_set_temp_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_main_lb_gun_set_temp_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_main_lb_gun_set_temp_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_lb_gun_set_temp_main_main_default, 0);
	lv_style_set_text_color(&style_screen_main_lb_gun_set_temp_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_main_lb_gun_set_temp_main_main_default, &lv_font_SimHei_40);
	lv_style_set_text_letter_space(&style_screen_main_lb_gun_set_temp_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_main_lb_gun_set_temp_main_main_default, 0);
	lv_style_set_text_align(&style_screen_main_lb_gun_set_temp_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_main_lb_gun_set_temp_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_lb_gun_set_temp_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_lb_gun_set_temp_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_lb_gun_set_temp_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_lb_gun_set_temp, &style_screen_main_lb_gun_set_temp_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_lb_gun_set_temp_value
	ui->screen_main_lb_gun_set_temp_value = lv_label_create(ui->screen_main_view_gun);
	lv_obj_set_pos(ui->screen_main_lb_gun_set_temp_value, 181, 11);
	lv_obj_set_size(ui->screen_main_lb_gun_set_temp_value, 200, 81);
	lv_obj_set_scrollbar_mode(ui->screen_main_lb_gun_set_temp_value, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_main_lb_gun_set_temp_value, "450");
	lv_label_set_long_mode(ui->screen_main_lb_gun_set_temp_value, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_lb_gun_set_temp_value_main_main_default
	static lv_style_t style_screen_main_lb_gun_set_temp_value_main_main_default;
	if (style_screen_main_lb_gun_set_temp_value_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_lb_gun_set_temp_value_main_main_default);
	else
		lv_style_init(&style_screen_main_lb_gun_set_temp_value_main_main_default);
	lv_style_set_radius(&style_screen_main_lb_gun_set_temp_value_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_lb_gun_set_temp_value_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_main_lb_gun_set_temp_value_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_main_lb_gun_set_temp_value_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_lb_gun_set_temp_value_main_main_default, 0);
	lv_style_set_text_color(&style_screen_main_lb_gun_set_temp_value_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_main_lb_gun_set_temp_value_main_main_default, &lv_font_sa_digital_number_80);
	lv_style_set_text_letter_space(&style_screen_main_lb_gun_set_temp_value_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_main_lb_gun_set_temp_value_main_main_default, 0);
	lv_style_set_text_align(&style_screen_main_lb_gun_set_temp_value_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_main_lb_gun_set_temp_value_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_lb_gun_set_temp_value_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_lb_gun_set_temp_value_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_lb_gun_set_temp_value_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_lb_gun_set_temp_value, &style_screen_main_lb_gun_set_temp_value_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_lb_gun_temp_value
	ui->screen_main_lb_gun_temp_value = lv_label_create(ui->screen_main_view_gun);
	lv_obj_set_pos(ui->screen_main_lb_gun_temp_value, 0, 104);
	lv_obj_set_size(ui->screen_main_lb_gun_temp_value, 400, 180);
	lv_obj_set_scrollbar_mode(ui->screen_main_lb_gun_temp_value, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_main_lb_gun_temp_value, "360");
	lv_label_set_long_mode(ui->screen_main_lb_gun_temp_value, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_lb_gun_temp_value_main_main_default
	static lv_style_t style_screen_main_lb_gun_temp_value_main_main_default;
	if (style_screen_main_lb_gun_temp_value_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_lb_gun_temp_value_main_main_default);
	else
		lv_style_init(&style_screen_main_lb_gun_temp_value_main_main_default);
	lv_style_set_radius(&style_screen_main_lb_gun_temp_value_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_lb_gun_temp_value_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_main_lb_gun_temp_value_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_main_lb_gun_temp_value_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_lb_gun_temp_value_main_main_default, 0);
	lv_style_set_text_color(&style_screen_main_lb_gun_temp_value_main_main_default, lv_color_make(0xff, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_main_lb_gun_temp_value_main_main_default, &lv_font_sa_digital_number_165);
	lv_style_set_text_letter_space(&style_screen_main_lb_gun_temp_value_main_main_default, 0);
	lv_style_set_text_line_space(&style_screen_main_lb_gun_temp_value_main_main_default, 0);
	lv_style_set_text_align(&style_screen_main_lb_gun_temp_value_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_main_lb_gun_temp_value_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_lb_gun_temp_value_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_lb_gun_temp_value_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_lb_gun_temp_value_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_lb_gun_temp_value, &style_screen_main_lb_gun_temp_value_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_lb_gun_fan_value
	ui->screen_main_lb_gun_fan_value = lv_label_create(ui->screen_main_view_gun);
	lv_obj_set_pos(ui->screen_main_lb_gun_fan_value, 150, 293);
	lv_obj_set_size(ui->screen_main_lb_gun_fan_value, 150, 65);
	lv_obj_set_scrollbar_mode(ui->screen_main_lb_gun_fan_value, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_main_lb_gun_fan_value, "100");
	lv_label_set_long_mode(ui->screen_main_lb_gun_fan_value, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_lb_gun_fan_value_main_main_default
	static lv_style_t style_screen_main_lb_gun_fan_value_main_main_default;
	if (style_screen_main_lb_gun_fan_value_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_lb_gun_fan_value_main_main_default);
	else
		lv_style_init(&style_screen_main_lb_gun_fan_value_main_main_default);
	lv_style_set_radius(&style_screen_main_lb_gun_fan_value_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_lb_gun_fan_value_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_main_lb_gun_fan_value_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_main_lb_gun_fan_value_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_lb_gun_fan_value_main_main_default, 0);
	lv_style_set_text_color(&style_screen_main_lb_gun_fan_value_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_main_lb_gun_fan_value_main_main_default, &lv_font_sa_digital_number_60);
	lv_style_set_text_letter_space(&style_screen_main_lb_gun_fan_value_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_main_lb_gun_fan_value_main_main_default, 0);
	lv_style_set_text_align(&style_screen_main_lb_gun_fan_value_main_main_default, LV_TEXT_ALIGN_RIGHT);
	lv_style_set_pad_left(&style_screen_main_lb_gun_fan_value_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_lb_gun_fan_value_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_lb_gun_fan_value_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_lb_gun_fan_value_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_lb_gun_fan_value, &style_screen_main_lb_gun_fan_value_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_lb_unit_baifenbi
	ui->screen_main_lb_unit_baifenbi = lv_label_create(ui->screen_main_view_gun);
	lv_obj_set_pos(ui->screen_main_lb_unit_baifenbi, 301, 320);
	lv_obj_set_size(ui->screen_main_lb_unit_baifenbi, 35, 40);
	lv_obj_set_scrollbar_mode(ui->screen_main_lb_unit_baifenbi, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_main_lb_unit_baifenbi, "%");
	lv_label_set_long_mode(ui->screen_main_lb_unit_baifenbi, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_lb_unit_baifenbi_main_main_default
	static lv_style_t style_screen_main_lb_unit_baifenbi_main_main_default;
	if (style_screen_main_lb_unit_baifenbi_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_lb_unit_baifenbi_main_main_default);
	else
		lv_style_init(&style_screen_main_lb_unit_baifenbi_main_main_default);
	lv_style_set_radius(&style_screen_main_lb_unit_baifenbi_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_lb_unit_baifenbi_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_main_lb_unit_baifenbi_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_main_lb_unit_baifenbi_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_lb_unit_baifenbi_main_main_default, 0);
	lv_style_set_text_color(&style_screen_main_lb_unit_baifenbi_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_main_lb_unit_baifenbi_main_main_default, &lv_font_SimHei_40);
	lv_style_set_text_letter_space(&style_screen_main_lb_unit_baifenbi_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_main_lb_unit_baifenbi_main_main_default, 0);
	lv_style_set_text_align(&style_screen_main_lb_unit_baifenbi_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_main_lb_unit_baifenbi_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_lb_unit_baifenbi_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_lb_unit_baifenbi_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_lb_unit_baifenbi_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_lb_unit_baifenbi, &style_screen_main_lb_unit_baifenbi_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_lb_hot
	ui->screen_main_lb_hot = lv_label_create(ui->screen_main_view_gun);
	lv_obj_set_pos(ui->screen_main_lb_hot, 59, 306);
	lv_obj_set_size(ui->screen_main_lb_hot, 90, 40);
	lv_obj_set_scrollbar_mode(ui->screen_main_lb_hot, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_main_lb_hot, "热风");
	lv_label_set_long_mode(ui->screen_main_lb_hot, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_lb_hot_main_main_default
	static lv_style_t style_screen_main_lb_hot_main_main_default;
	if (style_screen_main_lb_hot_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_lb_hot_main_main_default);
	else
		lv_style_init(&style_screen_main_lb_hot_main_main_default);
	lv_style_set_radius(&style_screen_main_lb_hot_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_lb_hot_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_main_lb_hot_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_main_lb_hot_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_lb_hot_main_main_default, 0);
	lv_style_set_text_color(&style_screen_main_lb_hot_main_main_default, lv_color_make(0xff, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_main_lb_hot_main_main_default, &lv_font_SimHei_40);
	lv_style_set_text_letter_space(&style_screen_main_lb_hot_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_main_lb_hot_main_main_default, 0);
	lv_style_set_text_align(&style_screen_main_lb_hot_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_main_lb_hot_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_lb_hot_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_lb_hot_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_lb_hot_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_lb_hot, &style_screen_main_lb_hot_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_lb_gun_preset_temp
	ui->screen_main_lb_gun_preset_temp = lv_label_create(ui->screen_main_view_gun);
	lv_obj_set_pos(ui->screen_main_lb_gun_preset_temp, 5, 385);
	lv_obj_set_size(ui->screen_main_lb_gun_preset_temp, 110, 24);
	lv_obj_set_scrollbar_mode(ui->screen_main_lb_gun_preset_temp, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_main_lb_gun_preset_temp, "预设温度");
	lv_label_set_long_mode(ui->screen_main_lb_gun_preset_temp, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_lb_gun_preset_temp_main_main_default
	static lv_style_t style_screen_main_lb_gun_preset_temp_main_main_default;
	if (style_screen_main_lb_gun_preset_temp_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_lb_gun_preset_temp_main_main_default);
	else
		lv_style_init(&style_screen_main_lb_gun_preset_temp_main_main_default);
	lv_style_set_radius(&style_screen_main_lb_gun_preset_temp_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_lb_gun_preset_temp_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_main_lb_gun_preset_temp_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_main_lb_gun_preset_temp_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_lb_gun_preset_temp_main_main_default, 0);
	lv_style_set_text_color(&style_screen_main_lb_gun_preset_temp_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_main_lb_gun_preset_temp_main_main_default, &lv_font_SimHei_24);
	lv_style_set_text_letter_space(&style_screen_main_lb_gun_preset_temp_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_main_lb_gun_preset_temp_main_main_default, 0);
	lv_style_set_text_align(&style_screen_main_lb_gun_preset_temp_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_main_lb_gun_preset_temp_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_lb_gun_preset_temp_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_lb_gun_preset_temp_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_lb_gun_preset_temp_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_lb_gun_preset_temp, &style_screen_main_lb_gun_preset_temp_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_btn_gun_CH1
	ui->screen_main_btn_gun_CH1 = lv_btn_create(ui->screen_main_view_gun);
	lv_obj_set_pos(ui->screen_main_btn_gun_CH1, 120, 370);
	lv_obj_set_size(ui->screen_main_btn_gun_CH1, 80, 50);
	lv_obj_set_scrollbar_mode(ui->screen_main_btn_gun_CH1, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_btn_gun_ch1_main_main_default
	static lv_style_t style_screen_main_btn_gun_ch1_main_main_default;
	if (style_screen_main_btn_gun_ch1_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_btn_gun_ch1_main_main_default);
	else
		lv_style_init(&style_screen_main_btn_gun_ch1_main_main_default);
	lv_style_set_radius(&style_screen_main_btn_gun_ch1_main_main_default, 5);
	lv_style_set_bg_color(&style_screen_main_btn_gun_ch1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_main_btn_gun_ch1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_main_btn_gun_ch1_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_btn_gun_ch1_main_main_default, 255);
	lv_style_set_border_color(&style_screen_main_btn_gun_ch1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_main_btn_gun_ch1_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_main_btn_gun_ch1_main_main_default, 255);
	lv_style_set_text_color(&style_screen_main_btn_gun_ch1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_main_btn_gun_ch1_main_main_default, &lv_font_SimHei_24);
	lv_style_set_text_align(&style_screen_main_btn_gun_ch1_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_obj_add_style(ui->screen_main_btn_gun_CH1, &style_screen_main_btn_gun_ch1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	//lv_obj_add_flag(ui->screen_main_btn_gun_CH1, LV_OBJ_FLAG_CHECKABLE);
	ui->screen_main_btn_gun_CH1_label = lv_label_create(ui->screen_main_btn_gun_CH1);
	lv_label_set_text(ui->screen_main_btn_gun_CH1_label, "CH1");
	lv_obj_set_style_pad_all(ui->screen_main_btn_gun_CH1, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->screen_main_btn_gun_CH1_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes screen_main_btn_gun_CH2
	ui->screen_main_btn_gun_CH2 = lv_btn_create(ui->screen_main_view_gun);
	lv_obj_set_pos(ui->screen_main_btn_gun_CH2, 215, 370);
	lv_obj_set_size(ui->screen_main_btn_gun_CH2, 80, 50);
	lv_obj_set_scrollbar_mode(ui->screen_main_btn_gun_CH2, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_btn_gun_ch2_main_main_default
	static lv_style_t style_screen_main_btn_gun_ch2_main_main_default;
	if (style_screen_main_btn_gun_ch2_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_btn_gun_ch2_main_main_default);
	else
		lv_style_init(&style_screen_main_btn_gun_ch2_main_main_default);
	lv_style_set_radius(&style_screen_main_btn_gun_ch2_main_main_default, 5);
	lv_style_set_bg_color(&style_screen_main_btn_gun_ch2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_main_btn_gun_ch2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_main_btn_gun_ch2_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_btn_gun_ch2_main_main_default, 255);
	lv_style_set_border_color(&style_screen_main_btn_gun_ch2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_main_btn_gun_ch2_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_main_btn_gun_ch2_main_main_default, 255);
	lv_style_set_text_color(&style_screen_main_btn_gun_ch2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_main_btn_gun_ch2_main_main_default, &lv_font_SimHei_24);
	lv_style_set_text_align(&style_screen_main_btn_gun_ch2_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_obj_add_style(ui->screen_main_btn_gun_CH2, &style_screen_main_btn_gun_ch2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	//lv_obj_add_flag(ui->screen_main_btn_gun_CH2, LV_OBJ_FLAG_CHECKABLE);
	ui->screen_main_btn_gun_CH2_label = lv_label_create(ui->screen_main_btn_gun_CH2);
	lv_label_set_text(ui->screen_main_btn_gun_CH2_label, "CH2");
	lv_obj_set_style_pad_all(ui->screen_main_btn_gun_CH2, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->screen_main_btn_gun_CH2_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes screen_main_btn_gun_CH3
	ui->screen_main_btn_gun_CH3 = lv_btn_create(ui->screen_main_view_gun);
	lv_obj_set_pos(ui->screen_main_btn_gun_CH3, 310, 370);
	lv_obj_set_size(ui->screen_main_btn_gun_CH3, 80, 50);
	lv_obj_set_scrollbar_mode(ui->screen_main_btn_gun_CH3, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_btn_gun_ch3_main_main_default
	static lv_style_t style_screen_main_btn_gun_ch3_main_main_default;
	if (style_screen_main_btn_gun_ch3_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_btn_gun_ch3_main_main_default);
	else
		lv_style_init(&style_screen_main_btn_gun_ch3_main_main_default);
	lv_style_set_radius(&style_screen_main_btn_gun_ch3_main_main_default, 5);
	lv_style_set_bg_color(&style_screen_main_btn_gun_ch3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_main_btn_gun_ch3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_main_btn_gun_ch3_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_btn_gun_ch3_main_main_default, 255);
	lv_style_set_border_color(&style_screen_main_btn_gun_ch3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_main_btn_gun_ch3_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_main_btn_gun_ch3_main_main_default, 255);
	lv_style_set_text_color(&style_screen_main_btn_gun_ch3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_main_btn_gun_ch3_main_main_default, &lv_font_SimHei_24);
	lv_style_set_text_align(&style_screen_main_btn_gun_ch3_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_obj_add_style(ui->screen_main_btn_gun_CH3, &style_screen_main_btn_gun_ch3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	//lv_obj_add_flag(ui->screen_main_btn_gun_CH3, LV_OBJ_FLAG_CHECKABLE);
	ui->screen_main_btn_gun_CH3_label = lv_label_create(ui->screen_main_btn_gun_CH3);
	lv_label_set_text(ui->screen_main_btn_gun_CH3_label, "CH3");
	lv_obj_set_style_pad_all(ui->screen_main_btn_gun_CH3, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->screen_main_btn_gun_CH3_label, LV_ALIGN_CENTER, 0, 0);

    lv_anim_init(&ui->screen_main_lb_iron_set_temp_value_anim);
    lv_anim_init(&ui->screen_main_lb_gun_set_temp_value_anim);
    lv_anim_init(&ui->screen_main_lb_gun_hot_anim);
    lv_anim_init(&ui->screen_main_lb_gun_fan_value_anim);
	//Init events for screen
	events_init_screen_main(ui);
}