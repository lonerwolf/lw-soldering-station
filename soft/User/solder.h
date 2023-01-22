//
// Created by lonerwolf on 2023/1/14.
//

#ifndef _SOLDER_H
#define _SOLDER_H

#include <stdint.h>
#include <stdbool.h>
#include "debug.h"
#include "FreeRTOS.h"
#include "task.h"

#define SOLDER_DELAY_MS(ms) (vTaskDelay(pdMS_TO_TICKS(ms)))

#define SOLDER_PID_MIN_OUTPUT 0
#define SOLDER_PID_MAX_OUTPUT 250

#define SOLDER_IRON_TEMP_SLEEP 100 //烙铁睡眠温度
#define SOLDER_IRON_TEMP_MAX 400 //烙铁最大可选温度
#define SOLDER_IRON_TEMP_MIN 200 //烙铁最小可选温度

#define SOLDER_GUN_TEMP_SLEEP 150 //风枪睡眠后风枪最高温度
#define SOLDER_GUN_TEMP_MAX 400 //风枪最大可选温度
#define SOLDER_GUN_TEMP_MIN 200 //风枪最小可选温度

#define SOLDER_GUN_FAN_MAX 100 //风枪最大风力
#define SOLDER_GUN_FAN_MIN 0 //风枪最小风力

typedef struct _solder_pid_t{
    //激进PID参数
    float aggKp;
    float aggKi;
    float aggKd;
    //保守PID参数
    float consKp;
    float consKi;
    float consKd;
    int32_t e0;//上次的差值
    int32_t e1;//上上次的差值
}SolderPid,*PtSolderPid;

typedef enum _solder_iron_type_e{
    SolderIronType_T12,
    SolderIronType_JBC210,
    SolderIronType_JBC245
}SolderIronType;

typedef enum _solder_iron_mode_e{
    SolderIronMode_OFF = 0,
    SolderIronMode_Sleep = 1,
    SolderIronMode_Heat,
}SolderIronMode;

typedef enum _solder_gun_mode_e{
    SolderGunMode_OFF = 0,
    SolderGunMode_Sleep = 1,
    SolderGunMode_Heat,
}SolderGunMode;

//typedef uint16_t (*SolderGetAdcFun)(void);
typedef uint16_t (*SolderGetPwmFun)(void);
typedef void (*SolderSetPwmFun)(uint16_t);
typedef int (*SolderGetTwoAdcFun)(uint16_t*,uint16_t*);
typedef void (*SolderSetGpio)(bool);

typedef struct _solder_t{
    SolderIronType iron_type;
    SolderPid iron_pid;
    volatile SolderIronMode iron_mode;
    uint16_t iron_dest_temp;
    uint16_t iron_current_temp;
    bool iron_reed_key;
    //T12 JBC210在测温时需要关闭PWM输出
    bool iron_stop_in_adc;
#define SOLDER_IRON_MEAN_FILTERING_ARRAY_LEN 5
    uint16_t iron_temp_mean_filtering_array[SOLDER_IRON_MEAN_FILTERING_ARRAY_LEN];

    SolderPid gun_pid;
    volatile SolderGunMode gun_mode;
    uint16_t gun_dest_temp;
    uint16_t gun_current_temp;
    bool gun_fan_is_cool;
    uint8_t gun_fan_pwm;
    bool gun_reed_key;
#define SOLDER_GUN_MEAN_FILTERING_ARRAY_LEN 5
    uint16_t gun_temp_mean_filtering_array[SOLDER_GUN_MEAN_FILTERING_ARRAY_LEN];

    //SolderGetAdcFun iron_get_adc_fun;
    SolderSetPwmFun iron_set_pwm_fun;
    SolderGetPwmFun iron_get_pwm_fun;
    //SolderGetAdcFun gun_get_adc_fun;
    SolderSetPwmFun gun_set_pwm_fun;
    SolderGetPwmFun gun_get_pwm_fun;
    SolderGetTwoAdcFun iron_and_gun_get_adc_fun;
    SolderSetGpio gun_220_ctl_fun;
    SolderSetPwmFun gun_fan_set_pwm_fun;
}Solder,*PtSolder;

int solder_init(PtSolder handle, SolderIronType ironType,
                SolderGetTwoAdcFun ironAndGunGetAdcFun,
                SolderSetPwmFun ironSetPwmFun,
                SolderGetPwmFun ironGetPwmFun,
                SolderSetPwmFun gunSetPwmFun,
                SolderGetPwmFun gunGetPwmFun,
                SolderSetGpio gun220SetGpioFun,
                SolderSetPwmFun gunFanSetPwmFun);
void solder_iron_start(PtSolder handle);
void solder_iron_stop(PtSolder handle);
void solder_set_iron_dest_temp(PtSolder handle, uint16_t destTemp);
void solder_set_iron_reed_key(PtSolder handle, bool key);
uint16_t solder_get_iron_current_temp(PtSolder handle);
uint16_t solder_get_gun_current_temp(PtSolder handle);
void solder_gun_start(PtSolder handle);
void solder_gun_stop(PtSolder handle);
void solder_set_gun_dest_temp(PtSolder handle, uint16_t destTemp);
void solder_set_gun_fan_is_cool(PtSolder handle, bool isCool);
void solder_set_gun_fan_value(PtSolder handle, uint8_t v);
void solder_set_gun_reed_key(PtSolder handle, bool key);
void solder_loop(PtSolder handle);
bool solder_iron_is_start(PtSolder handle);
bool solder_gun_is_start(PtSolder handle);

#endif //_SOLDER_H
