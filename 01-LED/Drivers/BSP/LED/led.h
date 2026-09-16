/*
* 这个代码的开发基于正点原子stm32f429的裸机开发，目的是构建电赛的基本体系
*/

#ifndef __LED_H__
#define __LED_H__

#include "stm32f4xx.h"
#include "core_cm4.h"
#include "stm32f4xx_hal.h"

#define LED0_GPIO_PORT 		GPIOB
#define LED0_GPIO_PIN  		GPIO_PIN_1

#define LED1_GPIO_PORT 		GPIOB
#define LED1_GPIO_PIN  		GPIO_PIN_0

typedef enum
{
	LED_0=0,
	LED_1,
	LED_NUM,
}LED_e;

void led_init(void);
void led_on(LED_e led);
void led_off(LED_e led);
void led_toggle(LED_e led);

#endif