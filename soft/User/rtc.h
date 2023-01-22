//
// Created by lonerwolf on 2023/1/15.
//

#ifndef _RTC_H
#define _RTC_H

#include <stdint.h>

typedef struct _rtc_calendar_obj
{
    volatile uint8_t hour;
    volatile uint8_t min;
    volatile uint8_t sec;

    volatile uint16_t w_year;
    volatile uint8_t  w_month;
    volatile uint8_t  w_date;
    volatile uint8_t  week;
} Rtc_Calendar;

int rtc_init(void);
void rtc_get(Rtc_Calendar* calendar);
int rtc_set(uint16_t syear, uint8_t smon, uint8_t sday, uint8_t hour, uint8_t min, uint8_t sec);

#endif //_RTC_H
