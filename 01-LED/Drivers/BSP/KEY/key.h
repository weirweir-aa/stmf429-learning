#ifndef __KEY_H__
#define __KEY_H__

#include "stm32f4xx.h"
#include "core_cm4.h"
#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include "./SYSTEM/delay/delay.h"

#define KEY0_GPIO_PORT      GPIOH
#define KEY0_GPIO_PIN       GPIO_PIN_3

#define KEY1_GPIO_PORT      GPIOH
#define KEY1_GPIO_PIN       GPIO_PIN_2

#define KEY2_GPIO_PORT      GPIOC
#define KEY2_GPIO_PIN       GPIO_PIN_13

#define WKUP_GPIO_PORT      GPIOA
#define WKUP_GPIO_PIN       GPIO_PIN_0

typedef enum
{
    KEY0=0,
    KEY1,
    KEY2,
    WKUP,
    KEY_NUM,
}KEY_e;

extern bool KEY0_PRES;
extern bool KEY1_PRES;
extern bool KEY2_PRES;
extern bool KEY_UP_PRES;

void key_init(void);
KEY_e key_scan(void);
void key_test(void);

#endif 

