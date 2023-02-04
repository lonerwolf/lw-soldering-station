//
// Created by lonerwolf on 2023/1/5.
//

#ifndef _SYSTEM_H
#define _SYSTEM_H

#include <stdint.h>
#include <stdbool.h>

typedef void (*system_irq_cb)(void);

void system_all_gpio_in(void);
void system_init(void);
void system_hardfault_deal(void);

float system_get_voltage_system();
float system_get_temp1();
float system_get_temp2();
float system_get_iron_current();
int system_get_adc_iron_and_gun_sensor(uint16_t *ironAdcValue, uint16_t *gunAdcValue);

void system_lcd_dma(uint32_t dstAddr,uint32_t buffAddr,uint16_t buffSizeHalfWord);
void system_lcd_dma_it(uint32_t dstAddr,uint32_t buffAddr,uint16_t buffSizeHalfWord,system_irq_cb cb);

void system_set_led_iron_pwm(uint16_t pwm);
uint16_t system_get_led_max_pwm();
void system_set_led_gun_pwm(uint16_t pwm);
uint16_t system_get_fan_max_pwm();
void system_set_fan_system_pwm(uint16_t pwm);
uint16_t system_get_iron_pwm();
void system_set_iron_pwm(uint16_t pwm);
uint16_t system_get_fan_gun_max_pwm();
uint16_t system_get_fan_gun_min_pwm();
void system_set_fan_gun_pwm(uint16_t pwm);
uint16_t system_get_gun_pwm();
void system_set_gun_pwm(uint16_t pwm);

void system_set_switch_220_ctl(bool set);
bool system_get_switch_rotate1_state();
bool system_get_switch_rotate2_state();
bool system_get_switch_iron_state();
bool system_get_switch_iron_reed_key_state();
bool system_get_switch_iron_shake_key_state();
bool system_get_switch_gun_state();
bool system_get_switch_gun_reed_key_state();

int16_t system_get_encoder1_count();
void system_clear_encoder1_count();
int16_t system_get_encoder2_count();
void system_clear_encoder2_count();

void system_pid_timer_start(system_irq_cb cb);
void system_pid_timer_stop();

void system_buzzer_start(void);
void system_buzzer_stop(void);

#endif //_SYSTEM_H
