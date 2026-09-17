#include "led.h"

void led_init(void)
{
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = LED0_GPIO_PIN | LED1_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(LED0_GPIO_PORT, &GPIO_InitStruct);
    HAL_GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStruct);

    led_off(LED_0);
    led_off(LED_1);
}

void led_on(LED_e led)
{
    switch (led)
    {
        case LED_0:
            HAL_GPIO_WritePin(LED0_GPIO_PORT, LED0_GPIO_PIN, GPIO_PIN_RESET);
            break;
        case LED_1:
            HAL_GPIO_WritePin(LED1_GPIO_PORT, LED1_GPIO_PIN, GPIO_PIN_RESET);
            break;
        default:
            break;
    }
}

void led_off(LED_e led)
{
    switch (led)
    {
        case LED_0:
            HAL_GPIO_WritePin(LED0_GPIO_PORT, LED0_GPIO_PIN, GPIO_PIN_SET);
            break;
        case LED_1:
            HAL_GPIO_WritePin(LED1_GPIO_PORT, LED1_GPIO_PIN, GPIO_PIN_SET);
            break;
        default:
            break;
    }
}


void led_toggle(LED_e led)
{
    switch (led)
    {
        case LED_0:
            HAL_GPIO_TogglePin(LED0_GPIO_PORT, LED0_GPIO_PIN);
            break;
        case LED_1:
            HAL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_GPIO_PIN);
            break;
        default:
            break;
    }
}

