#ifndef __KEY_EXIT_H__
#define __KEY_EXIT_H__

#include "stm32f4xx.h"
#include "core_cm4.h"
#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include "./SYSTEM/delay/delay.h"

/* 引脚 和 中断编号 & 中断服务函数 定义 */
#define KEY0_INT_GPIO_PORT GPIOH
#define KEY0_INT_GPIO_PIN GPIO_PIN_3
#define KEY0_INT_IRQn EXTI3_IRQn
#define KEY0_INT_IRQHandler EXTI3_IRQHandler

#define KEY1_INT_GPIO_PORT GPIOH
#define KEY1_INT_GPIO_PIN GPIO_PIN_2
#define KEY1_INT_IRQn EXTI2_IRQn
#define KEY1_INT_IRQHandler EXTI2_IRQHandler

#define KEY2_INT_GPIO_PORT GPIOC
#define KEY2_INT_GPIO_PIN GPIO_PIN_13
#define KEY2_INT_IRQn EXTI15_10_IRQn
#define KEY2_INT_IRQHandler EXTI15_10_IRQHandler

#define WKUP_INT_GPIO_PORT GPIOA
#define WKUP_INT_GPIO_PIN GPIO_PIN_0
#define WKUP_INT_IRQn EXTI0_IRQn
#define WKUP_INT_IRQHandler EXTI0_IRQHandler

void key_exit_init(void);

#endif
