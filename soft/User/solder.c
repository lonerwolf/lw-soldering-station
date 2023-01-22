//
// Created by lonerwolf on 2023/1/14.
//

#include <string.h>
#include "solder.h"
#include "ch32v30x_conf.h"
#include "tools.h"

#define SOLDER_PID_JBC245_AGG_KP 0.5
#define SOLDER_PID_JBC245_AGG_KI 1
#define SOLDER_PID_JBC245_AGG_KD 0
#define SOLDER_PID_JBC245_CONS_KP 0.5
#define SOLDER_PID_JBC245_CONS_KI 1
#define SOLDER_PID_JBC245_CONS_KD 0

#define SOLDER_PID_JBC210_AGG_KP 0.5
#define SOLDER_PID_JBC210_AGG_KI 1
#define SOLDER_PID_JBC210_AGG_KD 0
#define SOLDER_PID_JBC210_CONS_KP 0.5
#define SOLDER_PID_JBC210_CONS_KI 1
#define SOLDER_PID_JBC210_CONS_KD 0

#define SOLDER_PID_T12_AGG_KP 11
#define SOLDER_PID_T12_AGG_KI 1
#define SOLDER_PID_T12_AGG_KD 0
#define SOLDER_PID_T12_CONS_KP 0.5
#define SOLDER_PID_T12_CONS_KI 0.6
#define SOLDER_PID_T12_CONS_KD 0

#define SOLDER_PID_GUN_AGG_KP 11
#define SOLDER_PID_GUN_AGG_KI 0.5
#define SOLDER_PID_GUN_AGG_KD 1
#define SOLDER_PID_GUN_CONS_KP 0.5
#define SOLDER_PID_GUN_CONS_KI 0.6
#define SOLDER_PID_GUN_CONS_KD 6

#define SOLDER_T12_IRON_TEMP_100_ADC_VALUE 20
#define SOLDER_T12_IRON_TEMP_150_ADC_VALUE 210
#define SOLDER_T12_IRON_TEMP_200_ADC_VALUE 750
#define SOLDER_T12_IRON_TEMP_250_ADC_VALUE 1200
#define SOLDER_T12_IRON_TEMP_300_ADC_VALUE 2000
#define SOLDER_T12_IRON_TEMP_350_ADC_VALUE 2640
#define SOLDER_T12_IRON_TEMP_400_ADC_VALUE 2900
#define SOLDER_T12_IRON_TEMP_450_ADC_VALUE 3120

#define SOLDER_JBC210_IRON_TEMP_100_ADC_VALUE 20
#define SOLDER_JBC210_IRON_TEMP_150_ADC_VALUE 210
#define SOLDER_JBC210_IRON_TEMP_200_ADC_VALUE 750
#define SOLDER_JBC210_IRON_TEMP_250_ADC_VALUE 1200
#define SOLDER_JBC210_IRON_TEMP_300_ADC_VALUE 2000
#define SOLDER_JBC210_IRON_TEMP_350_ADC_VALUE 2640
#define SOLDER_JBC210_IRON_TEMP_400_ADC_VALUE 2900
#define SOLDER_JBC210_IRON_TEMP_450_ADC_VALUE 3120

#define SOLDER_JBC245_IRON_TEMP_100_ADC_VALUE 20
#define SOLDER_JBC245_IRON_TEMP_150_ADC_VALUE 210
#define SOLDER_JBC245_IRON_TEMP_200_ADC_VALUE 750
#define SOLDER_JBC245_IRON_TEMP_250_ADC_VALUE 1200
#define SOLDER_JBC245_IRON_TEMP_300_ADC_VALUE 2000
#define SOLDER_JBC245_IRON_TEMP_350_ADC_VALUE 2640
#define SOLDER_JBC245_IRON_TEMP_400_ADC_VALUE 2900
#define SOLDER_JBC245_IRON_TEMP_450_ADC_VALUE 3120

#define SOLDER_GUN_TEMP_200_ADC_VALUE 750
#define SOLDER_GUN_TEMP_250_ADC_VALUE 900
#define SOLDER_GUN_TEMP_300_ADC_VALUE 1000
#define SOLDER_GUN_TEMP_350_ADC_VALUE 1200
#define SOLDER_GUN_TEMP_400_ADC_VALUE 1400
#define SOLDER_GUN_TEMP_450_ADC_VALUE 1600

static uint16_t solder_conv_iron_adc_to_temp(PtSolder handle, uint16_t adc) {
    switch (handle->iron_type) {
        case SolderIronType_JBC245:
            if (adc < SOLDER_JBC245_IRON_TEMP_100_ADC_VALUE)
                return tools_map(adc, 0, SOLDER_JBC245_IRON_TEMP_100_ADC_VALUE, 0, 100);
            else if (adc < SOLDER_JBC245_IRON_TEMP_150_ADC_VALUE)
                return tools_map(adc, SOLDER_JBC245_IRON_TEMP_100_ADC_VALUE, SOLDER_JBC245_IRON_TEMP_150_ADC_VALUE, 100, 150);
            else if (adc < SOLDER_JBC245_IRON_TEMP_200_ADC_VALUE)
                return tools_map(adc, SOLDER_JBC245_IRON_TEMP_150_ADC_VALUE, SOLDER_JBC245_IRON_TEMP_200_ADC_VALUE, 150, 200);
            else if (adc < SOLDER_JBC245_IRON_TEMP_250_ADC_VALUE)
                return tools_map(adc, SOLDER_JBC245_IRON_TEMP_200_ADC_VALUE, SOLDER_JBC245_IRON_TEMP_250_ADC_VALUE, 200, 250);
            else if (adc < SOLDER_JBC245_IRON_TEMP_300_ADC_VALUE)
                return tools_map(adc, SOLDER_JBC245_IRON_TEMP_250_ADC_VALUE, SOLDER_JBC245_IRON_TEMP_300_ADC_VALUE, 250, 300);
            else if (adc < SOLDER_JBC245_IRON_TEMP_350_ADC_VALUE)
                return tools_map(adc, SOLDER_JBC245_IRON_TEMP_300_ADC_VALUE, SOLDER_JBC245_IRON_TEMP_350_ADC_VALUE, 300, 350);
            else if (adc < SOLDER_JBC245_IRON_TEMP_400_ADC_VALUE)
                return tools_map(adc, SOLDER_JBC245_IRON_TEMP_350_ADC_VALUE, SOLDER_JBC245_IRON_TEMP_400_ADC_VALUE, 350, 400);
            else if (adc < SOLDER_JBC245_IRON_TEMP_450_ADC_VALUE)
                return tools_map(adc, SOLDER_JBC245_IRON_TEMP_400_ADC_VALUE, SOLDER_JBC245_IRON_TEMP_450_ADC_VALUE, 400, 450);
            else
                return 600;
            break;
        case SolderIronType_JBC210:
            if (adc < SOLDER_JBC210_IRON_TEMP_100_ADC_VALUE)
                return tools_map(adc, 0, SOLDER_JBC210_IRON_TEMP_100_ADC_VALUE, 0, 100);
            else if (adc < SOLDER_JBC210_IRON_TEMP_150_ADC_VALUE)
                return tools_map(adc, SOLDER_JBC210_IRON_TEMP_100_ADC_VALUE, SOLDER_JBC210_IRON_TEMP_150_ADC_VALUE, 100, 150);
            else if (adc < SOLDER_JBC210_IRON_TEMP_200_ADC_VALUE)
                return tools_map(adc, SOLDER_JBC210_IRON_TEMP_150_ADC_VALUE, SOLDER_JBC210_IRON_TEMP_200_ADC_VALUE, 150, 200);
            else if (adc < SOLDER_JBC210_IRON_TEMP_250_ADC_VALUE)
                return tools_map(adc, SOLDER_JBC210_IRON_TEMP_200_ADC_VALUE, SOLDER_JBC210_IRON_TEMP_250_ADC_VALUE, 200, 250);
            else if (adc < SOLDER_JBC210_IRON_TEMP_300_ADC_VALUE)
                return tools_map(adc, SOLDER_JBC210_IRON_TEMP_250_ADC_VALUE, SOLDER_JBC210_IRON_TEMP_300_ADC_VALUE, 250, 300);
            else if (adc < SOLDER_JBC210_IRON_TEMP_350_ADC_VALUE)
                return tools_map(adc, SOLDER_JBC210_IRON_TEMP_300_ADC_VALUE, SOLDER_JBC210_IRON_TEMP_350_ADC_VALUE, 300, 350);
            else if (adc < SOLDER_JBC210_IRON_TEMP_400_ADC_VALUE)
                return tools_map(adc, SOLDER_JBC210_IRON_TEMP_350_ADC_VALUE, SOLDER_JBC210_IRON_TEMP_400_ADC_VALUE, 350, 400);
            else if (adc < SOLDER_JBC210_IRON_TEMP_450_ADC_VALUE)
                return tools_map(adc, SOLDER_JBC210_IRON_TEMP_400_ADC_VALUE, SOLDER_JBC210_IRON_TEMP_450_ADC_VALUE, 400, 450);
            else
                return 600;
            break;
        case SolderIronType_T12:
            if (adc < SOLDER_T12_IRON_TEMP_100_ADC_VALUE)
                return tools_map(adc, 0, SOLDER_T12_IRON_TEMP_100_ADC_VALUE, 0, 100);
            else if (adc < SOLDER_T12_IRON_TEMP_150_ADC_VALUE)
                return tools_map(adc, SOLDER_T12_IRON_TEMP_100_ADC_VALUE, SOLDER_T12_IRON_TEMP_150_ADC_VALUE, 100, 150);
            else if (adc < SOLDER_T12_IRON_TEMP_200_ADC_VALUE)
                return tools_map(adc, SOLDER_T12_IRON_TEMP_150_ADC_VALUE, SOLDER_T12_IRON_TEMP_200_ADC_VALUE, 150, 200);
            else if (adc < SOLDER_T12_IRON_TEMP_250_ADC_VALUE)
                return tools_map(adc, SOLDER_T12_IRON_TEMP_200_ADC_VALUE, SOLDER_T12_IRON_TEMP_250_ADC_VALUE, 200, 250);
            else if (adc < SOLDER_T12_IRON_TEMP_300_ADC_VALUE)
                return tools_map(adc, SOLDER_T12_IRON_TEMP_250_ADC_VALUE, SOLDER_T12_IRON_TEMP_300_ADC_VALUE, 250, 300);
            else if (adc < SOLDER_T12_IRON_TEMP_350_ADC_VALUE)
                return tools_map(adc, SOLDER_T12_IRON_TEMP_300_ADC_VALUE, SOLDER_T12_IRON_TEMP_350_ADC_VALUE, 300, 350);
            else if (adc < SOLDER_T12_IRON_TEMP_400_ADC_VALUE)
                return tools_map(adc, SOLDER_T12_IRON_TEMP_350_ADC_VALUE, SOLDER_T12_IRON_TEMP_400_ADC_VALUE, 350, 400);
            else if (adc < SOLDER_T12_IRON_TEMP_450_ADC_VALUE)
                return tools_map(adc, SOLDER_T12_IRON_TEMP_400_ADC_VALUE, SOLDER_T12_IRON_TEMP_450_ADC_VALUE, 400, 450);
            else
                return 600;
            break;
    }

    return 1000;
}

static uint16_t solder_conv_gun_adc_to_temp(PtSolder handle, uint16_t adc) {
    if (adc < SOLDER_GUN_TEMP_200_ADC_VALUE)
        return tools_map(adc, 0, SOLDER_GUN_TEMP_200_ADC_VALUE, 0, 200);
    else if (adc < SOLDER_GUN_TEMP_250_ADC_VALUE)
        return tools_map(adc, SOLDER_GUN_TEMP_200_ADC_VALUE, SOLDER_GUN_TEMP_250_ADC_VALUE, 200, 250);
    else if (adc < SOLDER_GUN_TEMP_300_ADC_VALUE)
        return tools_map(adc, SOLDER_GUN_TEMP_250_ADC_VALUE, SOLDER_GUN_TEMP_300_ADC_VALUE, 250, 300);
    else if (adc < SOLDER_GUN_TEMP_350_ADC_VALUE)
        return tools_map(adc, SOLDER_GUN_TEMP_300_ADC_VALUE, SOLDER_GUN_TEMP_350_ADC_VALUE, 300, 350);
    else if (adc < SOLDER_GUN_TEMP_400_ADC_VALUE)
        return tools_map(adc, SOLDER_GUN_TEMP_350_ADC_VALUE, SOLDER_GUN_TEMP_400_ADC_VALUE, 350, 400);
    else if (adc < SOLDER_GUN_TEMP_450_ADC_VALUE)
        return tools_map(adc, SOLDER_GUN_TEMP_400_ADC_VALUE, SOLDER_GUN_TEMP_450_ADC_VALUE, 400, 450);
    else
        return 600;
}

static inline void solder_reset_pid_param(PtSolderPid handle) {
    handle->e0 = 0;
    handle->e1 = 0;
}

static inline void solder_reset_iron_temp_mean(PtSolder handle) {
    memset(handle->iron_temp_mean_filtering_array, 0, SOLDER_IRON_MEAN_FILTERING_ARRAY_LEN * sizeof(uint16_t));
}

static inline void solder_reset_gun_temp_mean(PtSolder handle) {
    memset(handle->gun_temp_mean_filtering_array, 0, SOLDER_GUN_MEAN_FILTERING_ARRAY_LEN * sizeof(uint16_t));
}

//温度均值滤波
static uint16_t solder_iron_temp_mean_filtering(PtSolder handle, uint16_t currentTemp) {
    uint32_t sum = 0;
    for (int i = 1; i < SOLDER_IRON_MEAN_FILTERING_ARRAY_LEN; i++) {
        sum += handle->iron_temp_mean_filtering_array[i];
    }
    sum += currentTemp;
    memmove(handle->iron_temp_mean_filtering_array, handle->iron_temp_mean_filtering_array + 1,
            (SOLDER_IRON_MEAN_FILTERING_ARRAY_LEN - 1) * sizeof(uint16_t));
    handle->iron_temp_mean_filtering_array[SOLDER_IRON_MEAN_FILTERING_ARRAY_LEN - 1] = currentTemp;

    return sum / SOLDER_IRON_MEAN_FILTERING_ARRAY_LEN;
}

static uint16_t solder_gun_temp_mean_filtering(PtSolder handle, uint16_t currentTemp) {
    uint32_t sum = 0;
    for (int i = 1; i < SOLDER_GUN_MEAN_FILTERING_ARRAY_LEN; i++) {
        sum += handle->gun_temp_mean_filtering_array[i];
    }
    sum += currentTemp;
    memmove(handle->gun_temp_mean_filtering_array, handle->gun_temp_mean_filtering_array + 1,
            (SOLDER_GUN_MEAN_FILTERING_ARRAY_LEN - 1) * sizeof(uint16_t));
    handle->gun_temp_mean_filtering_array[SOLDER_GUN_MEAN_FILTERING_ARRAY_LEN - 1] = currentTemp;

    return sum / SOLDER_GUN_MEAN_FILTERING_ARRAY_LEN;
}

int solder_init(PtSolder handle, SolderIronType ironType,
                SolderGetTwoAdcFun ironAndGunGetAdcFun,
                SolderSetPwmFun ironSetPwmFun,
                SolderGetPwmFun ironGetPwmFun,
                SolderSetPwmFun gunSetPwmFun,
                SolderGetPwmFun gunGetPwmFun,
                SolderSetGpio gun220SetGpioFun,
                SolderSetPwmFun gunFanSetPwmFun) {
    if (ironAndGunGetAdcFun == NULL
        || ironSetPwmFun == NULL
        || ironGetPwmFun == NULL
        || gunSetPwmFun == NULL
        || gunGetPwmFun == NULL
        || gun220SetGpioFun == NULL
        || gunFanSetPwmFun == NULL) {
        return -1;
    }

    memset(handle, 0, sizeof(Solder));

    handle->iron_and_gun_get_adc_fun = ironAndGunGetAdcFun;
    handle->iron_get_pwm_fun = ironGetPwmFun;
    handle->iron_set_pwm_fun = ironSetPwmFun;
    handle->gun_get_pwm_fun = gunGetPwmFun;
    handle->gun_set_pwm_fun = gunSetPwmFun;
    handle->gun_220_ctl_fun = gun220SetGpioFun;
    handle->gun_fan_set_pwm_fun = gunFanSetPwmFun;

    handle->iron_type = ironType;
    switch (ironType) {
        case SolderIronType_T12:
            handle->iron_stop_in_adc = true;

            handle->iron_pid.aggKp = SOLDER_PID_T12_AGG_KP;
            handle->iron_pid.aggKi = SOLDER_PID_T12_AGG_KI;
            handle->iron_pid.aggKd = SOLDER_PID_T12_AGG_KD;
            handle->iron_pid.consKp = SOLDER_PID_T12_CONS_KP;
            handle->iron_pid.consKi = SOLDER_PID_T12_CONS_KI;
            handle->iron_pid.consKd = SOLDER_PID_T12_CONS_KD;
            break;
        case SolderIronType_JBC210:
            handle->iron_stop_in_adc = true;

            handle->iron_pid.aggKp = SOLDER_PID_JBC210_AGG_KP;
            handle->iron_pid.aggKi = SOLDER_PID_JBC210_AGG_KI;
            handle->iron_pid.aggKd = SOLDER_PID_JBC210_AGG_KD;
            handle->iron_pid.consKp = SOLDER_PID_JBC210_CONS_KP;
            handle->iron_pid.consKi = SOLDER_PID_JBC210_CONS_KI;
            handle->iron_pid.consKd = SOLDER_PID_JBC210_CONS_KD;
            break;
        case SolderIronType_JBC245:
            handle->iron_stop_in_adc = false;

            handle->iron_pid.aggKp = SOLDER_PID_JBC245_AGG_KP;
            handle->iron_pid.aggKi = SOLDER_PID_JBC245_AGG_KI;
            handle->iron_pid.aggKd = SOLDER_PID_JBC245_AGG_KD;
            handle->iron_pid.consKp = SOLDER_PID_JBC245_CONS_KP;
            handle->iron_pid.consKi = SOLDER_PID_JBC245_CONS_KI;
            handle->iron_pid.consKd = SOLDER_PID_JBC245_CONS_KD;
            break;
        default:
            handle->iron_stop_in_adc = false;
            break;
    }

    handle->gun_pid.aggKp = SOLDER_PID_GUN_AGG_KP;
    handle->gun_pid.aggKi = SOLDER_PID_GUN_AGG_KI;
    handle->gun_pid.aggKd = SOLDER_PID_GUN_AGG_KD;
    handle->gun_pid.consKp = SOLDER_PID_GUN_CONS_KP;
    handle->gun_pid.consKi = SOLDER_PID_GUN_CONS_KI;
    handle->gun_pid.consKd = SOLDER_PID_GUN_CONS_KD;

    return 0;
}

void solder_set_iron_dest_temp(PtSolder handle, uint16_t destTemp) {
    if (destTemp > SOLDER_IRON_TEMP_MAX) {
        destTemp = SOLDER_IRON_TEMP_MAX;
    }
    if (destTemp < SOLDER_IRON_TEMP_MIN) {
        destTemp = SOLDER_IRON_TEMP_MIN;
    }
    handle->iron_dest_temp = destTemp;
}

void solder_set_iron_reed_key(PtSolder handle, bool key) {
    handle->iron_reed_key = key;
    if (handle->iron_reed_key) {
        if (handle->iron_mode != SolderIronMode_OFF) {
            handle->iron_mode = SolderIronMode_Sleep;
        }
    } else {
        if (handle->iron_mode == SolderIronMode_Sleep) {
            handle->iron_mode = SolderIronMode_Heat;
            solder_reset_iron_temp_mean(handle);
            solder_reset_pid_param((PtSolderPid) &(handle->iron_pid));
        }
    }
}

uint16_t solder_get_iron_current_temp(PtSolder handle) {
    return handle->iron_current_temp;
}

uint16_t solder_get_gun_current_temp(PtSolder handle) {
    return handle->gun_current_temp;
}

void solder_set_gun_dest_temp(PtSolder handle, uint16_t destTemp) {
    if (destTemp > SOLDER_GUN_TEMP_MAX) {
        destTemp = SOLDER_GUN_TEMP_MAX;
    }
    if (destTemp < SOLDER_GUN_TEMP_MIN) {
        destTemp = SOLDER_GUN_TEMP_MIN;
    }
    handle->gun_dest_temp = destTemp;
}

void solder_set_gun_fan_is_cool(PtSolder handle, bool isCool) {
    handle->gun_fan_is_cool = isCool;
}

void solder_set_gun_fan_value(PtSolder handle, uint8_t v) {
    if (v > SOLDER_GUN_FAN_MAX) {
        v = SOLDER_GUN_FAN_MAX;
    }
    if (v < SOLDER_GUN_FAN_MIN) {
        v = SOLDER_GUN_FAN_MIN;
    }
    handle->gun_fan_pwm = v;
}

void solder_set_gun_reed_key(PtSolder handle, bool key) {
    handle->gun_reed_key = key;
    if (handle->gun_reed_key) {
        if (handle->gun_mode != SolderGunMode_OFF) {
            handle->gun_mode = SolderGunMode_Sleep;
        }
    } else {
        if (handle->gun_mode == SolderGunMode_Sleep) {
            handle->gun_mode = SolderGunMode_Heat;
            solder_reset_gun_temp_mean(handle);
            solder_reset_pid_param((PtSolderPid) &(handle->gun_pid));
            handle->gun_fan_set_pwm_fun(handle->gun_fan_pwm);
        }
    }
}

static uint8_t solder_iron_pid_op(PtSolder handle, uint16_t destValue, uint16_t nowValue, uint8_t currentOutput) {
    int32_t e = destValue - nowValue;
    int32_t res = 0;
    switch (handle->iron_type) {
        case SolderIronType_T12:
        case SolderIronType_JBC210:
            if (e > 50) {//温差大于50全速
                res = SOLDER_PID_MAX_OUTPUT;
            } else if (e > 30) {//温差大于30激进
                //增量PID公式 PID=Uk+KP*【E(k)-E(k-1)】+KI*E(k)+KD*【E(k)-2E(k-1)+E(k-2)】
                int32_t duk = handle->iron_pid.aggKp * (e - handle->iron_pid.e0) + handle->iron_pid.aggKi * e +
                              handle->iron_pid.aggKd * (e - 2 * handle->iron_pid.e0 + handle->iron_pid.e1);
                res = currentOutput + duk;
            } else {
                int32_t duk = handle->iron_pid.consKp * (e - handle->iron_pid.e0) + handle->iron_pid.consKi * e +
                              handle->iron_pid.consKd * (e - 2 * handle->iron_pid.e0 + handle->iron_pid.e1);
                res = currentOutput + duk;
            }
            break;
        case SolderIronType_JBC245:
            if (e > 100) {//温差大于100全速
                res = SOLDER_PID_MAX_OUTPUT;
            } else if (e > 50) {//温差大于50激进
                //增量PID公式 PID=Uk+KP*【E(k)-E(k-1)】+KI*E(k)+KD*【E(k)-2E(k-1)+E(k-2)】
                int32_t duk = handle->iron_pid.aggKp * (e - handle->iron_pid.e0) + handle->iron_pid.aggKi * e +
                              handle->iron_pid.aggKd * (e - 2 * handle->iron_pid.e0 + handle->iron_pid.e1);
                res = currentOutput + duk;
            } else {
                int32_t duk = handle->iron_pid.consKp * (e - handle->iron_pid.e0) + handle->iron_pid.consKi * e +
                              handle->iron_pid.consKd * (e - 2 * handle->iron_pid.e0 + handle->iron_pid.e1);
                res = currentOutput + duk;
            }
            break;
    }

    if (res > SOLDER_PID_MAX_OUTPUT)
        res = SOLDER_PID_MAX_OUTPUT;
    if (res < SOLDER_PID_MIN_OUTPUT)
        res = SOLDER_PID_MIN_OUTPUT;

    handle->iron_pid.e1 = handle->iron_pid.e0;
    handle->iron_pid.e0 = e;
    return (uint8_t) res;
}

static uint8_t solder_gun_pid_op(PtSolder handle, uint16_t destValue, uint16_t nowValue, uint8_t currentOutput) {
    int32_t e = destValue - nowValue;
    int32_t res = 0;
    if (e > 100) {//温差大于100全速
        res = SOLDER_PID_MAX_OUTPUT;
    } else if (e > 50) {//温差大于50激进
        //增量PID公式 PID=Uk+KP*【E(k)-E(k-1)】+KI*E(k)+KD*【E(k)-2E(k-1)+E(k-2)】
        int32_t duk = handle->gun_pid.aggKp * (e - handle->gun_pid.e0) + handle->gun_pid.aggKi * e +
                      handle->gun_pid.aggKd * (e - 2 * handle->gun_pid.e0 + handle->gun_pid.e1);
        res = currentOutput + duk;
    } else {
        int32_t duk = handle->gun_pid.consKp * (e - handle->gun_pid.e0) + handle->gun_pid.consKi * e +
                      handle->gun_pid.consKd * (e - 2 * handle->gun_pid.e0 + handle->gun_pid.e1);
        res = currentOutput + duk;
    }

    if (res > SOLDER_PID_MAX_OUTPUT)
        res = SOLDER_PID_MAX_OUTPUT;
    if (res < SOLDER_PID_MIN_OUTPUT)
        res = SOLDER_PID_MIN_OUTPUT;

    handle->gun_pid.e1 = handle->gun_pid.e0;
    handle->gun_pid.e0 = e;
    return (uint8_t) res;
}

bool solder_iron_is_start(PtSolder handle) {
    if (handle->iron_mode == SolderIronMode_OFF)
        return false;
    return true;
}

bool solder_gun_is_start(PtSolder handle) {
    if (handle->gun_mode == SolderGunMode_OFF)
        return false;
    return true;
}

void solder_iron_start(PtSolder handle) {
    if (handle->iron_mode == SolderIronMode_OFF) {
        solder_reset_iron_temp_mean(handle);
        solder_reset_pid_param((PtSolderPid) &(handle->iron_pid));
        if (handle->iron_reed_key) {
            handle->iron_mode = SolderIronMode_Sleep;
        } else {
            handle->iron_mode = SolderIronMode_Heat;
        }
        handle->iron_set_pwm_fun(0);
    }
}

void solder_iron_stop(PtSolder handle) {
    handle->iron_mode = SolderIronMode_OFF;
    handle->iron_set_pwm_fun(0);
    handle->iron_current_temp = 0;
}

void solder_gun_start(PtSolder handle) {
    if (handle->gun_mode == SolderGunMode_OFF) {
        if (handle->gun_reed_key) {
            handle->gun_mode = SolderGunMode_Sleep;
        } else {
            handle->gun_mode = SolderGunMode_Heat;
        }
        solder_reset_gun_temp_mean(handle);
        solder_reset_pid_param((PtSolderPid) &(handle->gun_pid));
        handle->gun_set_pwm_fun(0);
        handle->gun_220_ctl_fun(true);
        SOLDER_DELAY_MS(20);
        handle->gun_fan_set_pwm_fun(handle->gun_fan_pwm);
    }
}

void solder_gun_stop(PtSolder handle) {
    handle->gun_mode = SolderGunMode_OFF;
    handle->gun_set_pwm_fun(0);
    //光耦零点才真正关闭可控硅,此时再断开继电器
    SOLDER_DELAY_MS(12);
    handle->gun_220_ctl_fun(false);
    handle->gun_fan_set_pwm_fun(SOLDER_GUN_FAN_MIN);
}

void solder_loop(PtSolder handle) {
    bool needAdc = false;
    if (handle->iron_mode != SolderIronMode_OFF) {
        needAdc = true;
    }

    if (handle->gun_mode != SolderGunMode_OFF) {
        needAdc = true;
    }

    uint16_t ironAdcV, gunAdcV;
    if (needAdc) {
        {
            uint8_t currentPwm;
            if (handle->iron_stop_in_adc) {
                currentPwm = handle->iron_get_pwm_fun();
                handle->iron_set_pwm_fun(SOLDER_PID_MIN_OUTPUT);
                SOLDER_DELAY_MS(1);
            }
            if (handle->iron_and_gun_get_adc_fun(&ironAdcV, &gunAdcV)) {
                printf("solder_loop get adc failed\n");
            }
            if (handle->iron_stop_in_adc) {
                handle->iron_set_pwm_fun(currentPwm);
            }
        }
        uint16_t current_iron_temp;
        if (handle->iron_mode != SolderIronMode_OFF) {
            uint16_t destTemp = 0;
            if (handle->iron_mode == SolderIronMode_Sleep) {
                destTemp = SOLDER_IRON_TEMP_SLEEP;
            } else {
                destTemp = handle->iron_dest_temp;
            }
            uint8_t currentPwm = handle->iron_get_pwm_fun();
            uint16_t current_temp = solder_conv_iron_adc_to_temp(handle, ironAdcV);
            current_temp = solder_iron_temp_mean_filtering(handle, current_temp);
            handle->iron_current_temp = current_temp;
            uint8_t newPwm = solder_iron_pid_op(handle, destTemp, current_temp, currentPwm);
            handle->iron_set_pwm_fun(newPwm);
            current_iron_temp = current_temp;
        }

        uint16_t current_gun_temp;
        if (handle->gun_mode != SolderGunMode_OFF) {
            if (handle->gun_mode == SolderGunMode_Sleep) {
                handle->gun_set_pwm_fun(SOLDER_PID_MIN_OUTPUT);
                uint16_t current_temp = solder_conv_gun_adc_to_temp(handle, gunAdcV);
                current_temp = solder_gun_temp_mean_filtering(handle, current_temp);
                if (current_temp < SOLDER_GUN_TEMP_SLEEP) {
                    handle->gun_fan_set_pwm_fun(SOLDER_GUN_FAN_MIN);
                } else {
                    handle->gun_fan_set_pwm_fun(handle->gun_fan_pwm);
                }
            } else {
                handle->gun_fan_set_pwm_fun(handle->gun_fan_pwm);
                if (handle->gun_fan_is_cool) {
                    handle->gun_set_pwm_fun(SOLDER_PID_MIN_OUTPUT);
                } else {
                    uint16_t destTemp = handle->gun_dest_temp;
                    uint8_t currentPwm = handle->gun_get_pwm_fun();
                    uint16_t current_temp = solder_conv_gun_adc_to_temp(handle, gunAdcV);
                    current_temp = solder_gun_temp_mean_filtering(handle, current_temp);
                    handle->gun_current_temp = current_temp;
                    uint8_t newPwm = solder_gun_pid_op(handle, destTemp, current_temp, currentPwm);
                    handle->gun_set_pwm_fun(newPwm);
                    current_gun_temp = current_temp;
                }
            }
        }

/*        static uint32_t debug_count = 0;
        debug_count++;
        if (debug_count >= 500) {
            debug_count = 0;
            printf("ironAdcV:%d\n", ironAdcV);
            printf("iron_pwm:%d\n", handle->iron_get_pwm_fun());
            printf("iron_current_temp:%d\n", current_iron_temp);
            printf("iron_dest_temp:%d\n", handle->iron_dest_temp);
            //printf("solder_conv_iron_adc_to_temp:%d\n", solder_conv_iron_adc_to_temp(ironAdcV));

            //printf("SOLDER_JBC245_IRON_TEMP_400_ADC_VALUE:%d\n", SOLDER_JBC245_IRON_TEMP_400_ADC_VALUE);
            //printf("gun_dest_temp:%d\n",handle->gun_dest_temp);
            //printf("SOLDER_GUN_TEMP_400_ADC_VALUE:%d\n", SOLDER_GUN_TEMP_400_ADC_VALUE);

            //printf("gunAdcV:%d\n",gunAdcV);
            //printf("gun_pwm:%d\n",handle->gun_get_pwm_fun());
            //printf("gun_current_temp:%d\n",current_gun_temp);
            //printf("gun_dest_temp:%d\n",handle->gun_dest_temp);
        }*/
    }
}

