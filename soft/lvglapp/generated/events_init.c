/*
 * Copyright 2023 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

static lv_my_ch_event_cb l_iron_ch_cb = 0;
static lv_my_ch_event_cb l_gun_ch_cb = 0;
void lv_my_set_cb_iron_ch(lv_my_ch_event_cb cb){
    l_iron_ch_cb = cb;
}
void lv_my_set_cb_gun_ch(lv_my_ch_event_cb cb){
    l_gun_ch_cb = cb;
}

void events_init(lv_ui *ui)
{
}

static void screen_main_btn_iron_CH1_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		if(l_iron_ch_cb)
            l_iron_ch_cb(1);
	}
		break;
	default:
		break;
	}
}

static void screen_main_btn_iron_CH2_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
        if(l_iron_ch_cb)
            l_iron_ch_cb(2);
	}
		break;
	default:
		break;
	}
}

static void screen_main_btn_iron_CH3_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
        if(l_iron_ch_cb)
            l_iron_ch_cb(3);
	}
		break;
	default:
		break;
	}
}

static void screen_main_btn_gun_CH1_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
        if(l_gun_ch_cb)
            l_gun_ch_cb(1);
	}
		break;
	default:
		break;
	}
}

static void screen_main_btn_gun_CH2_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
        if(l_gun_ch_cb)
            l_gun_ch_cb(2);
	}
		break;
	default:
		break;
	}
}

static void screen_main_btn_gun_CH3_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
        if(l_gun_ch_cb)
            l_gun_ch_cb(3);
	}
		break;
	default:
		break;
	}
}

void events_init_screen_main(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_main_btn_iron_CH1, screen_main_btn_iron_CH1_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_main_btn_iron_CH2, screen_main_btn_iron_CH2_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_main_btn_iron_CH3, screen_main_btn_iron_CH3_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_main_btn_gun_CH1, screen_main_btn_gun_CH1_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_main_btn_gun_CH2, screen_main_btn_gun_CH2_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_main_btn_gun_CH3, screen_main_btn_gun_CH3_event_handler, LV_EVENT_ALL, NULL);
}
