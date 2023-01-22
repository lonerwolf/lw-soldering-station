/*
 * Copyright 2023 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */


#ifndef EVENTS_INIT_H_
#define EVENTS_INIT_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"

typedef void (*lv_my_ch_event_cb)(uint8_t);

void events_init(lv_ui *ui);
void events_init_screen_main(lv_ui *ui);

void lv_my_set_cb_iron_ch(lv_my_ch_event_cb cb);
void lv_my_set_cb_gun_ch(lv_my_ch_event_cb cb);

#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */