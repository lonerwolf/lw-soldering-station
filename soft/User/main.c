/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/06/06
* Description        : Main program body.
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/


#include <stdlib.h>
#include "debug.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "system.h"
#include "tftlcd.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "gui_guider.h"
#include "solder.h"
#include "rtc.h"

typedef enum _cmd_e {
    CMD_PID_SEMAPHORE = 1,
    CMD_SWITCH_IRON_CHANGE,
    CMD_SWITCH_GUN_CHANGE,
    CMD_IRON_DEST_TEMP_CHANGE,
    CMD_GUN_DEST_TEMP_CHANGE,
    CMD_GUN_DEST_FAN_CHANGE,
    CMD_SWITCH_IRON_REED_CHANGE,
    CMD_SWITCH_GUN_REED_CHANGE,
    CMD_IRON_MODE_CHANGE,
    CMD_GUN_MODE_CHANGE,
    CMD_GUN_FAN_TYPE_CHANGE,
} CmdType;

static TaskHandle_t l_task_check_handler;
#define TASK_CHECK_PRIO     (configMAX_PRIORITIES-1)
#define TASK_CHECK_STK_SIZE      256
static StackType_t l_task_check_stack[TASK_CHECK_STK_SIZE];
static StaticTask_t l_task_check_task_buffer;

static TaskHandle_t l_task_pid_handler;
#define TASK_PID_PRIO     (configMAX_PRIORITIES-2)
#define TASK_PID_STK_SIZE      256
static StackType_t l_task_pid_stack[TASK_PID_STK_SIZE];
static StaticTask_t l_task_pid_task_buffer;

static TaskHandle_t l_task_ui_handler;
#define TASK_UI_PRIO     5
#define TASK_UI_STK_SIZE    4096
static StackType_t l_task_ui_stack[TASK_UI_STK_SIZE];
static StaticTask_t l_task_ui_task_buffer;

static QueueHandle_t l_task_pid_queue;
static StaticQueue_t l_task_pid_queue_static;
#define l_task_pid_queue_size 32
#define l_task_pid_queue_item_size 1
static uint8_t l_task_pid_queue_buff[l_task_pid_queue_size * l_task_pid_queue_item_size];

static QueueHandle_t l_task_ui_queue;
static StaticQueue_t l_task_ui_queue_static;
#define l_task_ui_queue_size 32
#define l_task_ui_queue_item_size 1
static uint8_t l_task_ui_queue_buff[l_task_ui_queue_size * l_task_ui_queue_item_size];

//定时器服务任务控制块
static StaticTask_t FreertosTimerTaskTCB;
//定时器服务任务堆栈
static StackType_t FreertosTimerTaskStack[configTIMER_TASK_STACK_DEPTH];

void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer,
                                    StackType_t **ppxTimerTaskStackBuffer,
                                    uint32_t *pulTimerTaskStackSize) {
    *ppxTimerTaskTCBBuffer = &FreertosTimerTaskTCB;
    *ppxTimerTaskStackBuffer = FreertosTimerTaskStack;
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

//空闲任务控制块
static StaticTask_t FreertosIdleTaskTCB;
//空闲任务任务堆栈
static StackType_t FreertosIdleTaskStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
                                   StackType_t **ppxIdleTaskStackBuffer,
                                   uint32_t *pulIdleTaskStackSize) {
    *ppxIdleTaskTCBBuffer = &FreertosIdleTaskTCB;
    *ppxIdleTaskStackBuffer = FreertosIdleTaskStack;
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

void vApplicationTickHook(void) {
    lv_tick_inc(1000/configTICK_RATE_HZ);
}

TFTLCD_DEV g_tftlcd_dev;
lv_ui guider_ui;

static Solder l_solder_handle;

static volatile bool l_iron_switch_state = false;
static volatile bool l_iron_switch_pre_state = false;
static volatile bool l_iron_reed_key_switch_state = false;
static volatile bool l_iron_reed_key_switch_pre_state = false;
static volatile bool l_iron_shake_key_switch_state = false;
static volatile bool l_iron_shake_key_switch_pre_state = false;
static volatile bool l_gun_switch_state = false;
static volatile bool l_gun_switch_pre_state = false;
static volatile bool l_gun_reed_key_switch_state = false;
static volatile bool l_gun_reed_key_switch_pre_state = false;

static volatile bool l_rotate1_switch_state = false;
static volatile bool l_rotate1_switch_pre_state = false;
static volatile bool l_rotate2_switch_state = false;
static volatile bool l_rotate2_switch_pre_state = false;

#define IRON_CH1_TEMP 300
#define IRON_CH2_TEMP 320
#define IRON_CH3_TEMP 350
#define GUN_CH1_TEMP 320
#define GUN_CH2_TEMP 350
#define GUN_CH3_TEMP 380
static volatile uint16_t l_iron_dest_temp = 320;
static volatile uint16_t l_gun_dest_temp = 350;
static volatile uint16_t l_gun_dest_fan = 30;
static volatile bool l_gun_fan_is_cool = false;

typedef enum _iron_mode_e {
    IronMode_NO,
    IronMode_SET_TEMP
} IronMode;

typedef enum _gun_mode_e {
    GunMode_NO,
    GunMode_SET_TEMP,
    GunMode_SET_FAN_IS_COOL,
    GunMode_SET_FAN,
} GunMode;

static IronMode l_iron_mode = IronMode_NO;
static uint32_t l_iron_mode_tick = 0;
static GunMode l_gun_mode = GunMode_NO;
static uint32_t l_gun_mode_tick = 0;

//界面设置超时
#define UI_MODE_SET_TIMEOUT_MS 8000

void task_check(void *pvParameters) {
    uint8_t timer_count = 0;
    uint8_t led_pwm_flag = 0;
    uint16_t led_pwm_count = 0;
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(20));
        timer_count++;
        if (timer_count > 1000) {
            timer_count = 0;
        }
        //状态检测
        {
            uint32_t nowTick = xTaskGetTickCount();
            if (l_iron_mode == IronMode_SET_TEMP) {
                if ((nowTick - l_iron_mode_tick) * 1000 / configTICK_RATE_HZ >= UI_MODE_SET_TIMEOUT_MS) {
                    l_iron_mode = IronMode_NO;
                    uint8_t message = CMD_IRON_DEST_TEMP_CHANGE;
                    xQueueSend(l_task_pid_queue, (void *) &message, pdMS_TO_TICKS(20));
                    xQueueSend(l_task_ui_queue, (void *) &message, 0);
                    message = CMD_IRON_MODE_CHANGE;
                    xQueueSend(l_task_ui_queue, (void *) &message, 0);
                }
            }
            if (l_gun_mode == GunMode_SET_TEMP) {
                if ((nowTick - l_gun_mode_tick) * 1000 / configTICK_RATE_HZ >= UI_MODE_SET_TIMEOUT_MS) {
                    l_gun_mode = GunMode_NO;
                    uint8_t message = CMD_GUN_DEST_TEMP_CHANGE;
                    xQueueSend(l_task_pid_queue, (void *) &message, pdMS_TO_TICKS(20));
                    xQueueSend(l_task_ui_queue, (void *) &message, 0);
                    message = CMD_GUN_MODE_CHANGE;
                    xQueueSend(l_task_ui_queue, (void *) &message, 0);
                }
            }
            if (l_gun_mode == GunMode_SET_FAN_IS_COOL) {
                if ((nowTick - l_gun_mode_tick) * 1000 / configTICK_RATE_HZ >= UI_MODE_SET_TIMEOUT_MS) {
                    l_gun_mode = GunMode_NO;
                    uint8_t message = CMD_GUN_FAN_TYPE_CHANGE;
                    xQueueSend(l_task_pid_queue, (void *) &message, pdMS_TO_TICKS(20));
                    xQueueSend(l_task_ui_queue, (void *) &message, 0);
                    message = CMD_GUN_MODE_CHANGE;
                    xQueueSend(l_task_ui_queue, (void *) &message, 0);
                }
            }
            if (l_gun_mode == GunMode_SET_FAN) {
                if ((nowTick - l_gun_mode_tick) * 1000 / configTICK_RATE_HZ >= UI_MODE_SET_TIMEOUT_MS) {
                    l_gun_mode = GunMode_NO;
                    uint8_t message = CMD_GUN_DEST_FAN_CHANGE;
                    xQueueSend(l_task_pid_queue, (void *) &message, pdMS_TO_TICKS(20));
                    xQueueSend(l_task_ui_queue, (void *) &message, 0);
                    message = CMD_GUN_MODE_CHANGE;
                    xQueueSend(l_task_ui_queue, (void *) &message, 0);
                }
            }
        }
        //按键检测,消抖
        {
            //if (timer_count % 2 == 0) {
            bool state;
            state = system_get_switch_rotate1_state();
            if (l_rotate1_switch_pre_state != l_rotate1_switch_state) {
                if (l_rotate1_switch_pre_state == state) {
                    l_rotate1_switch_state = state;

                    if(l_rotate1_switch_state){
                        if (l_iron_mode == IronMode_NO) {
                            //进入调温
                            l_iron_mode = IronMode_SET_TEMP;
                            l_iron_mode_tick = xTaskGetTickCount();
                            uint8_t message = CMD_IRON_MODE_CHANGE;
                            xQueueSend(l_task_ui_queue, (void *) &message, 0);
                        } else {
                            //设置温度有效
                            l_iron_mode = IronMode_NO;
                            uint8_t message = CMD_IRON_DEST_TEMP_CHANGE;
                            xQueueSend(l_task_pid_queue, (void *) &message, pdMS_TO_TICKS(20));
                            xQueueSend(l_task_ui_queue, (void *) &message, 0);
                            message = CMD_IRON_MODE_CHANGE;
                            xQueueSend(l_task_ui_queue, (void *) &message, 0);
                        }
                    }
                }
            } else {
                if (l_rotate1_switch_pre_state != state) {
                    l_rotate1_switch_pre_state = state;
                }
            }

            state = system_get_switch_rotate2_state();
            if (l_rotate2_switch_pre_state != l_rotate2_switch_state) {
                if (l_rotate2_switch_pre_state == state) {
                    l_rotate2_switch_state = state;

                    if(l_rotate2_switch_state){
                        if (l_gun_mode == GunMode_NO) {
                            //进入调温
                            l_gun_mode = GunMode_SET_TEMP;
                            l_gun_mode_tick = xTaskGetTickCount();
                            uint8_t message = CMD_GUN_MODE_CHANGE;
                            xQueueSend(l_task_ui_queue, (void *) &message, 0);
                        } else if (l_gun_mode == GunMode_SET_TEMP) {
                            l_gun_mode = GunMode_SET_FAN_IS_COOL;
                            l_gun_mode_tick = xTaskGetTickCount();

                            uint8_t message = CMD_GUN_DEST_TEMP_CHANGE;
                            xQueueSend(l_task_pid_queue, (void *) &message, pdMS_TO_TICKS(20));
                            xQueueSend(l_task_ui_queue, (void *) &message, 0);
                            message = CMD_GUN_MODE_CHANGE;
                            xQueueSend(l_task_ui_queue, (void *) &message, 0);
                        } else if (l_gun_mode == GunMode_SET_FAN_IS_COOL) {
                            l_gun_mode = GunMode_SET_FAN;
                            l_gun_mode_tick = xTaskGetTickCount();

                            uint8_t message = CMD_GUN_FAN_TYPE_CHANGE;
                            xQueueSend(l_task_pid_queue, (void *) &message, pdMS_TO_TICKS(20));
                            xQueueSend(l_task_ui_queue, (void *) &message, 0);
                            message = CMD_GUN_MODE_CHANGE;
                            xQueueSend(l_task_ui_queue, (void *) &message, 0);
                        } else {
                            l_gun_mode = GunMode_NO;

                            uint8_t message = CMD_GUN_DEST_FAN_CHANGE;
                            xQueueSend(l_task_pid_queue, (void *) &message, pdMS_TO_TICKS(20));
                            xQueueSend(l_task_ui_queue, (void *) &message, 0);
                            message = CMD_GUN_MODE_CHANGE;
                            xQueueSend(l_task_ui_queue, (void *) &message, 0);
                        }
                    }
                }
            } else {
                if (l_rotate2_switch_pre_state != state) {
                    l_rotate2_switch_pre_state = state;
                }
            }

            state = system_get_switch_iron_state();
            if (l_iron_switch_pre_state != l_iron_switch_state) {
                if (l_iron_switch_pre_state == state) {
                    l_iron_switch_state = state;
                    uint8_t message = CMD_SWITCH_IRON_CHANGE;
                    xQueueSend(l_task_pid_queue, (void *) &message, portMAX_DELAY);
                    xQueueSend(l_task_ui_queue, (void *) &message, 0);
                }
            } else {
                if (l_iron_switch_pre_state != state) {
                    l_iron_switch_pre_state = state;
                }
            }

            state = system_get_switch_iron_reed_key_state();
            if (l_iron_reed_key_switch_pre_state != l_iron_reed_key_switch_state) {
                if (l_iron_reed_key_switch_pre_state == state) {
                    l_iron_reed_key_switch_state = state;
                    uint8_t message = CMD_SWITCH_IRON_REED_CHANGE;
                    xQueueSend(l_task_pid_queue, (void *) &message, portMAX_DELAY);
                }
            } else {
                if (l_iron_reed_key_switch_pre_state != state) {
                    l_iron_reed_key_switch_pre_state = state;
                }
            }

            state = system_get_switch_iron_shake_key_state();
            if (l_iron_shake_key_switch_pre_state != l_iron_shake_key_switch_state) {
                if (l_iron_shake_key_switch_pre_state == state) {
                    l_iron_shake_key_switch_state = state;
                }
            } else {
                if (l_iron_shake_key_switch_pre_state != state) {
                    l_iron_shake_key_switch_pre_state = state;
                }
            }

            state = system_get_switch_gun_state();
            if (l_gun_switch_pre_state != l_gun_switch_state) {
                if (l_gun_switch_pre_state == state) {
                    l_gun_switch_state = state;
                    uint8_t message = CMD_SWITCH_GUN_CHANGE;
                    xQueueSend(l_task_pid_queue, (void *) &message, portMAX_DELAY);
                    xQueueSend(l_task_ui_queue, (void *) &message, 0);
                }
            } else {
                if (l_gun_switch_pre_state != state) {
                    l_gun_switch_pre_state = state;
                }
            }

            state = system_get_switch_gun_reed_key_state();
            if (l_gun_reed_key_switch_pre_state != l_gun_reed_key_switch_state) {
                if (l_gun_reed_key_switch_pre_state == state) {
                    l_gun_reed_key_switch_state = state;
                    uint8_t message = CMD_SWITCH_GUN_REED_CHANGE;
                    xQueueSend(l_task_pid_queue, (void *) &message, portMAX_DELAY);
                }
            } else {
                if (l_gun_reed_key_switch_pre_state != state) {
                    l_gun_reed_key_switch_pre_state = state;
                }
            }
            //}
        }

        //呼吸灯
        {
            //if (timer_count % 2 == 0) {
            if (led_pwm_flag == 0) {
                led_pwm_count++;
                if (led_pwm_count == system_get_led_max_pwm() / 4) {
                    led_pwm_flag = 1;
                }
            } else {
                led_pwm_count--;
                if (led_pwm_count == 0) {
                    led_pwm_flag = 0;
                }
            }
            if (l_iron_switch_state) {
                system_set_led_iron_pwm(system_get_led_max_pwm());
            } else {
                system_set_led_iron_pwm(led_pwm_count);
            }
            if (l_gun_switch_state) {
                system_set_led_gun_pwm(system_get_led_max_pwm());
            } else {
                system_set_led_gun_pwm(led_pwm_count);
            }
            //}
        }

        //编码器
        {
            int16_t enc = system_get_encoder1_count();
            system_clear_encoder1_count();
            if (enc != 0 && l_iron_mode == IronMode_SET_TEMP) {
                if (l_iron_dest_temp + enc <= SOLDER_IRON_TEMP_MAX && l_iron_dest_temp + enc >= SOLDER_IRON_TEMP_MIN) {
                    l_iron_dest_temp = l_iron_dest_temp + enc;
                }
                if (l_iron_dest_temp + enc > SOLDER_IRON_TEMP_MAX) {
                    l_iron_dest_temp = SOLDER_IRON_TEMP_MAX;
                }
                if (l_iron_dest_temp + enc < SOLDER_IRON_TEMP_MIN) {
                    l_iron_dest_temp = SOLDER_IRON_TEMP_MIN;
                }
                l_iron_mode_tick = xTaskGetTickCount();
                uint8_t message = CMD_IRON_DEST_TEMP_CHANGE;
                xQueueSend(l_task_ui_queue, (void *) &message, 0);
            }

            enc = system_get_encoder2_count();
            system_clear_encoder2_count();
            if (enc != 0) {
                if (l_gun_mode == GunMode_SET_TEMP) {
                    if (l_gun_dest_temp + enc <= SOLDER_GUN_TEMP_MAX && l_gun_dest_temp + enc >= SOLDER_GUN_TEMP_MIN) {
                        l_gun_dest_temp = l_gun_dest_temp + enc;
                    }
                    if (l_gun_dest_temp + enc > SOLDER_GUN_TEMP_MAX) {
                        l_gun_dest_temp = SOLDER_GUN_TEMP_MAX;
                    }
                    if (l_gun_dest_temp + enc < SOLDER_GUN_TEMP_MIN) {
                        l_gun_dest_temp = SOLDER_GUN_TEMP_MIN;
                    }
                    l_gun_mode_tick = xTaskGetTickCount();

                    uint8_t message = CMD_GUN_DEST_TEMP_CHANGE;
                    xQueueSend(l_task_ui_queue, (void *) &message, 0);
                }
                if (l_gun_mode == GunMode_SET_FAN_IS_COOL) {
                    //if(enc%2 != 0){
                        l_gun_fan_is_cool = !l_gun_fan_is_cool;
                    //}
                    l_gun_mode_tick = xTaskGetTickCount();

                    uint8_t message = CMD_GUN_FAN_TYPE_CHANGE;
                    xQueueSend(l_task_ui_queue, (void *) &message, 0);
                }
                if (l_gun_mode == GunMode_SET_FAN) {
                    if (l_gun_dest_fan + enc <= SOLDER_GUN_FAN_MAX && l_gun_dest_fan + enc >= SOLDER_GUN_FAN_MIN) {
                        l_gun_dest_fan = l_gun_dest_fan + enc;
                    }
                    if (l_gun_dest_fan + enc > SOLDER_GUN_FAN_MAX) {
                        l_gun_dest_fan = SOLDER_GUN_FAN_MAX;
                    }
                    if (l_gun_dest_fan + enc < SOLDER_GUN_FAN_MIN) {
                        l_gun_dest_fan = SOLDER_GUN_FAN_MIN;
                    }
                    l_gun_mode_tick = xTaskGetTickCount();

                    uint8_t message = CMD_GUN_DEST_FAN_CHANGE;
                    xQueueSend(l_task_ui_queue, (void *) &message, 0);
                }
            }
        }

        //温度检测 散热风扇
        {
            if(timer_count % 500 == 0){
                float temp1 = system_get_temp1();
                float temp2 = system_get_temp2();
                uint16_t dest_temp = 0;
                if(temp1 >= temp2){
                    dest_temp = temp1;
                }else{
                    dest_temp = temp2;
                }
                if(dest_temp < 20){
                    system_set_fan_system_pwm(0);
                }else if(dest_temp < 25){
                    system_set_fan_system_pwm(system_get_fan_max_pwm()*1/5);
                }else if(dest_temp < 30){
                    system_set_fan_system_pwm(system_get_fan_max_pwm()*2/5);
                }else if(dest_temp < 35){
                    system_set_fan_system_pwm(system_get_fan_max_pwm()*3/5);
                }else{
                    system_set_fan_system_pwm(system_get_fan_max_pwm()*4/5);
                }
            }
        }
    }
}

void pid_timer_cb_irq() {
    portBASE_TYPE xHigherPriorityTaskWoken;
    uint8_t message;
    message = CMD_PID_SEMAPHORE;
    xQueueSendFromISR(l_task_pid_queue, (void *) &message, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void task_pid(void *pvParameters) {
    bool pid_timer_is_start = false;
    while (1) {
        uint8_t message;
        if (xQueueReceive(l_task_pid_queue, &message, portMAX_DELAY) == pdFALSE) {
            continue;
        }
        //printf("task_pid CmdType:%d\n", cmd);

        //不能有延时函数，PID计算会队列超出

        switch ((CmdType) (message)) {
            case CMD_SWITCH_IRON_CHANGE:
                if (l_iron_switch_state) {
                    solder_iron_start(&l_solder_handle);
                    if (pid_timer_is_start == false) {
                        pid_timer_is_start = true;
                        system_pid_timer_start(pid_timer_cb_irq);
                    }
                } else {
                    solder_iron_stop(&l_solder_handle);
                }
                break;
            case CMD_SWITCH_GUN_CHANGE:
                if (l_gun_switch_state) {
                    solder_gun_start(&l_solder_handle);
                    if (pid_timer_is_start == false) {
                        pid_timer_is_start = true;
                        system_pid_timer_start(pid_timer_cb_irq);
                    }
                } else {
                    solder_gun_stop(&l_solder_handle);
                }
                break;
            case CMD_PID_SEMAPHORE:
                solder_loop(&l_solder_handle);
                if (solder_iron_is_start(&l_solder_handle) || solder_gun_is_start(&l_solder_handle)) {
                    system_pid_timer_start(pid_timer_cb_irq);
                } else {
                    pid_timer_is_start = false;
                }
                break;
            case CMD_IRON_DEST_TEMP_CHANGE:
                solder_set_iron_dest_temp(&l_solder_handle, l_iron_dest_temp);
                break;
            case CMD_GUN_DEST_TEMP_CHANGE:
                solder_set_gun_dest_temp(&l_solder_handle, l_gun_dest_temp);
                break;
            case CMD_SWITCH_IRON_REED_CHANGE:
                break;
            case CMD_SWITCH_GUN_REED_CHANGE:
                solder_set_gun_reed_key(&l_solder_handle,l_gun_reed_key_switch_state);
                break;
            case CMD_GUN_FAN_TYPE_CHANGE:
                solder_set_gun_fan_is_cool(&l_solder_handle, l_gun_fan_is_cool);
                break;
            case CMD_GUN_DEST_FAN_CHANGE:
                solder_set_gun_fan_value(&l_solder_handle, l_gun_dest_fan);
                break;
        }
    }
}

static void anim_progress_load(void* obj, int32_t v) {
    lv_obj_set_style_text_opa(obj,v,LV_STATE_DEFAULT);
}

static void anim_text_start(lv_obj_t * obj,lv_anim_t* anim){
    lv_anim_init(anim);
    lv_anim_set_var(anim, obj);
    lv_anim_set_exec_cb(anim, (lv_anim_exec_xcb_t) anim_progress_load);
    lv_anim_set_values(anim, 80, 255);
    lv_anim_set_time(anim, 1000);
    //lv_anim_set_repeat_delay(anim, 200);
    lv_anim_set_path_cb(anim, lv_anim_path_linear);
    lv_anim_set_repeat_count(anim,1000);
    lv_anim_set_playback_time(anim, 1000);
    lv_anim_start(anim);
}

static void anim_text_stop(lv_obj_t * obj,lv_anim_t* anim){
    lv_anim_del(anim->var,NULL);
    lv_obj_set_style_text_opa(obj,255,LV_STATE_DEFAULT);
}

#include "events_init.h"
static void iron_ch_cb(uint8_t ch){
    if(ch == 1)
        l_iron_dest_temp = IRON_CH1_TEMP;
    else if(ch == 2)
        l_iron_dest_temp = IRON_CH2_TEMP;
    else
        l_iron_dest_temp = IRON_CH3_TEMP;
    uint8_t message = CMD_IRON_DEST_TEMP_CHANGE;
    xQueueSend(l_task_pid_queue, (void *) &message, pdMS_TO_TICKS(100));
    xQueueSend(l_task_ui_queue, (void *) &message, 0);
}

static void gun_ch_cb(uint8_t ch){
    if(ch == 1)
        l_gun_dest_temp = GUN_CH1_TEMP;
    else if(ch == 2)
        l_gun_dest_temp = GUN_CH2_TEMP;
    else
        l_gun_dest_temp = GUN_CH3_TEMP;
    uint8_t message = CMD_GUN_DEST_TEMP_CHANGE;
    xQueueSend(l_task_pid_queue, (void *) &message, pdMS_TO_TICKS(100));
    xQueueSend(l_task_ui_queue, (void *) &message, 0);
}

void task_ui(void *pvParameters) {
    Rtc_Calendar calendar;
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();

    setup_ui(&guider_ui);
    lv_my_set_cb_iron_ch(iron_ch_cb);
    lv_my_set_cb_gun_ch(gun_ch_cb);

    lv_label_set_text_fmt(guider_ui.screen_main_lb_iron_temp_value, "%d", 0);
    lv_label_set_text_fmt(guider_ui.screen_main_lb_gun_temp_value, "%d", 0);
    lv_label_set_text_fmt(guider_ui.screen_main_lb_iron_set_temp_value, "%d", l_iron_dest_temp);
    lv_label_set_text_fmt(guider_ui.screen_main_lb_gun_set_temp_value, "%d", l_gun_dest_temp);
    lv_label_set_text_fmt(guider_ui.screen_main_lb_gun_fan_value, "%d", l_gun_dest_fan);
    lv_led_off(guider_ui.screen_main_led_iron);
    lv_led_off(guider_ui.screen_main_led_gun);

    while (1) {
        uint8_t message;
        while(xQueueReceive(l_task_ui_queue, &message, 0) == pdTRUE){
            CmdType cmd = (CmdType) (message);
            printf("task_ui CmdType:%d\n", cmd);

            switch (cmd) {
                case CMD_SWITCH_IRON_CHANGE:
                    if(l_iron_switch_state){
                        lv_led_on(guider_ui.screen_main_led_iron);
                    }else{
                        lv_led_off(guider_ui.screen_main_led_iron);
                    }
                    break;
                case CMD_SWITCH_GUN_CHANGE:
                    if(l_gun_switch_state){
                        lv_led_on(guider_ui.screen_main_led_gun);
                    }else{
                        lv_led_off(guider_ui.screen_main_led_gun);
                    }
                    break;
                case CMD_IRON_DEST_TEMP_CHANGE:
                    lv_label_set_text_fmt(guider_ui.screen_main_lb_iron_set_temp_value, "%d", l_iron_dest_temp);
                    break;
                case CMD_GUN_DEST_TEMP_CHANGE:
                    lv_label_set_text_fmt(guider_ui.screen_main_lb_gun_set_temp_value, "%d", l_gun_dest_temp);
                    break;
                case CMD_GUN_DEST_FAN_CHANGE:
                    lv_label_set_text_fmt(guider_ui.screen_main_lb_gun_fan_value, "%d", l_gun_dest_fan);
                    break;
                case CMD_IRON_MODE_CHANGE:
                    if(l_iron_mode == IronMode_SET_TEMP){
                        anim_text_start(guider_ui.screen_main_lb_iron_set_temp_value,&(guider_ui.screen_main_lb_iron_set_temp_value_anim));
                    }else{
                        anim_text_stop(guider_ui.screen_main_lb_iron_set_temp_value,&(guider_ui.screen_main_lb_iron_set_temp_value_anim));
                    }
                    break;
                case CMD_GUN_MODE_CHANGE:
                    if(l_gun_mode == GunMode_SET_TEMP){
                        anim_text_stop(guider_ui.screen_main_lb_hot,&(guider_ui.screen_main_lb_gun_hot_anim));
                        anim_text_stop(guider_ui.screen_main_lb_gun_fan_value,&(guider_ui.screen_main_lb_gun_fan_value_anim));
                        anim_text_start(guider_ui.screen_main_lb_gun_set_temp_value,&(guider_ui.screen_main_lb_gun_set_temp_value_anim));
                    }else if(l_gun_mode == GunMode_SET_FAN_IS_COOL){
                        anim_text_stop(guider_ui.screen_main_lb_gun_set_temp_value,&(guider_ui.screen_main_lb_gun_set_temp_value_anim));
                        anim_text_stop(guider_ui.screen_main_lb_gun_fan_value,&(guider_ui.screen_main_lb_gun_fan_value_anim));
                        anim_text_start(guider_ui.screen_main_lb_hot,&(guider_ui.screen_main_lb_gun_hot_anim));
                    }else if(l_gun_mode == GunMode_SET_FAN){
                        anim_text_stop(guider_ui.screen_main_lb_gun_set_temp_value,&(guider_ui.screen_main_lb_gun_set_temp_value_anim));
                        anim_text_stop(guider_ui.screen_main_lb_hot,&(guider_ui.screen_main_lb_gun_hot_anim));
                        anim_text_start(guider_ui.screen_main_lb_gun_fan_value,&(guider_ui.screen_main_lb_gun_fan_value_anim));
                    }else{
                        anim_text_stop(guider_ui.screen_main_lb_gun_set_temp_value,&(guider_ui.screen_main_lb_gun_set_temp_value_anim));
                        anim_text_stop(guider_ui.screen_main_lb_hot,&(guider_ui.screen_main_lb_gun_hot_anim));
                        anim_text_stop(guider_ui.screen_main_lb_gun_fan_value,&(guider_ui.screen_main_lb_gun_fan_value_anim));
                    }
                    break;
                case CMD_GUN_FAN_TYPE_CHANGE:
                    if(l_gun_fan_is_cool == false){
                        lv_label_set_text(guider_ui.screen_main_lb_hot, "热风");
                        lv_obj_set_style_text_color(guider_ui.screen_main_lb_hot,lv_color_make(0xff, 0x00, 0x00),LV_STATE_DEFAULT);
                    }else{
                        lv_label_set_text(guider_ui.screen_main_lb_hot, "冷风");
                        lv_obj_set_style_text_color(guider_ui.screen_main_lb_hot,lv_color_make(0x00, 0x00, 0xff),LV_STATE_DEFAULT);
                    }
                    break;
            }
        }
        if(l_iron_switch_state){
            lv_label_set_text_fmt(guider_ui.screen_main_lb_iron_temp_value, "%d", solder_get_iron_current_temp(&l_solder_handle));
            float voltage = system_get_voltage_system();
            float current = system_get_iron_current();
            lv_label_set_text_fmt(guider_ui.screen_main_lb_va, "%.2f", voltage);
            lv_label_set_text_fmt(guider_ui.screen_main_lb_aa, "%.2f", current);
            lv_label_set_text_fmt(guider_ui.screen_main_lb_wa, "%.2f", voltage*current);
        }else{
            lv_label_set_text_fmt(guider_ui.screen_main_lb_va, "%.2f", 0);
            lv_label_set_text_fmt(guider_ui.screen_main_lb_aa, "%.2f", 0);
            lv_label_set_text_fmt(guider_ui.screen_main_lb_wa, "%.2f", 0);
            lv_label_set_text_fmt(guider_ui.screen_main_lb_iron_temp_value, "%d", 0);
        }
        if(l_gun_switch_state){
            lv_label_set_text_fmt(guider_ui.screen_main_lb_gun_temp_value, "%d", solder_get_gun_current_temp(&l_solder_handle));
        }
        {
            rtc_get(&calendar);
            lv_label_set_text_fmt(guider_ui.screen_main_lb_time,
                                  "%d-%02d-%02d %02d:%02d:%02d",
                                  calendar.w_year, calendar.w_month, calendar.w_date,
                                  calendar.hour, calendar.min, calendar.sec);
        }
        lv_timer_handler();
    }
}

//数字范围映射
static float my_map(float value, float fromLow, float fromHigh, float toLow, float toHigh) {
    return ((value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow);
}

static void gun_fan_fun(uint16_t v){
    system_set_fan_gun_pwm(my_map(v,SOLDER_GUN_FAN_MIN,SOLDER_GUN_FAN_MAX,system_get_fan_gun_min_pwm(),system_get_fan_gun_max_pwm()));
}

int main(void) {
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    //144MHZ APB2 2分频 ADC最大APB2时钟8分频 ADC最大不能超过14MHZ
    RCC_PCLK2Config(RCC_HCLK_Div2);

    Delay_Init();
    USART_Printf_Init(115200);
    printf("FreeRTOS Kernel Version:%s\r\n", tskKERNEL_VERSION_NUMBER);

    system_init();

/*    {
        RCC_ClocksTypeDef asd;
        RCC_GetClocksFreq(&asd);
        printf("SYSCLK_Frequency:%d\r\n", asd.SYSCLK_Frequency);
        printf("HCLK_Frequency:%d\r\n", asd.HCLK_Frequency);
        printf("PCLK1_Frequency:%d\r\n", asd.PCLK1_Frequency);
        printf("PCLK2_Frequency:%d\r\n", asd.PCLK2_Frequency);
        printf("ADCCLK_Frequency:%d\r\n", asd.ADCCLK_Frequency);
    }*/

    if (tftlcd_init(&g_tftlcd_dev)) {
        printf("tftlcd_init failed\n");
    }

    l_task_check_handler = xTaskCreateStatic((TaskFunction_t) task_check,
                                             (const char *) "task_check",
                                             (uint32_t) TASK_CHECK_STK_SIZE,
                                             (void *) NULL,
                                             (UBaseType_t) TASK_CHECK_PRIO,
                                             l_task_check_stack,
                                             &l_task_check_task_buffer);

    l_task_pid_handler = xTaskCreateStatic((TaskFunction_t) task_pid,
                                           (const char *) "task_pid",
                                           (uint32_t) TASK_PID_STK_SIZE,
                                           (void *) NULL,
                                           (UBaseType_t) TASK_PID_PRIO,
                                           l_task_pid_stack,
                                           &l_task_pid_task_buffer);

    l_task_ui_handler = xTaskCreateStatic((TaskFunction_t) task_ui,
                                           (const char *) "task_ui",
                                           (uint32_t) TASK_UI_STK_SIZE,
                                           (void *) NULL,
                                           (UBaseType_t) TASK_UI_PRIO,
                                           l_task_ui_stack,
                                           &l_task_ui_task_buffer);

    l_task_pid_queue = xQueueCreateStatic(l_task_pid_queue_size, l_task_pid_queue_item_size, l_task_pid_queue_buff,
                                          &l_task_pid_queue_static);
    l_task_ui_queue = xQueueCreateStatic(l_task_ui_queue_size, l_task_ui_queue_item_size, l_task_ui_queue_buff,
                                         &l_task_ui_queue_static);

    solder_init(&l_solder_handle, SolderIronType_JBC245, system_get_adc_iron_and_gun_sensor, system_set_iron_pwm,
                system_get_iron_pwm, system_set_gun_pwm, system_get_gun_pwm, system_set_switch_220_ctl,gun_fan_fun);
    solder_set_iron_dest_temp(&l_solder_handle, l_iron_dest_temp);
    solder_set_iron_reed_key(&l_solder_handle, l_iron_reed_key_switch_state);
    solder_set_gun_dest_temp(&l_solder_handle, l_gun_dest_temp);
    solder_set_gun_reed_key(&l_solder_handle, l_gun_reed_key_switch_state);
    solder_set_gun_fan_is_cool(&l_solder_handle, l_gun_fan_is_cool);

    //printf("vTaskStartScheduler\n");
    vTaskStartScheduler();

    while (1) {
        printf("shouldn't run at here!!\n");
    }
}
