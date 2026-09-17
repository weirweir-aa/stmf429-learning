#include "key_exit.h"
#include "./BSP/LED/led.h"

/*
*	外部中断按键初始化
*	KEY0 -> PH3  -> EXTI3
*	KEY1 -> PH2  -> EXTI2
*	KEY2 -> PC13 -> EXTI15_10
*	WKUP -> PA0  -> EXTI0
*
*	KEY0~KEY2 按下时接地(低电平), 所以用上拉输入 + 下降沿触发;
*	WKUP 按下时接VCC(高电平), 所以用下拉输入 + 上升沿触发
*/
void key_exit_init(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();

    /* KEY0~KEY2: 上拉输入, 下降沿触发 */
    gpio_init_struct.Mode  = GPIO_MODE_IT_FALLING;
    gpio_init_struct.Pull  = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;

    gpio_init_struct.Pin = KEY0_INT_GPIO_PIN;
    HAL_GPIO_Init(KEY0_INT_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.Pin = KEY1_INT_GPIO_PIN;
    HAL_GPIO_Init(KEY1_INT_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.Pin = KEY2_INT_GPIO_PIN;
    HAL_GPIO_Init(KEY2_INT_GPIO_PORT, &gpio_init_struct);

    /* WKUP: 下拉输入, 上升沿触发 */
    gpio_init_struct.Mode = GPIO_MODE_IT_RISING;
    gpio_init_struct.Pull = GPIO_PULLDOWN;

    gpio_init_struct.Pin = WKUP_INT_GPIO_PIN;
    HAL_GPIO_Init(WKUP_INT_GPIO_PORT, &gpio_init_struct);

    /* 使能中断, 抢占优先级 2, 子优先级 0 */
    HAL_NVIC_SetPriority(KEY0_INT_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(KEY0_INT_IRQn);

    HAL_NVIC_SetPriority(KEY1_INT_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(KEY1_INT_IRQn);

    HAL_NVIC_SetPriority(KEY2_INT_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(KEY2_INT_IRQn);

    HAL_NVIC_SetPriority(WKUP_INT_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(WKUP_INT_IRQn);
}

void KEY0_INT_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY0_INT_GPIO_PIN);
    __HAL_GPIO_EXTI_CLEAR_IT(KEY0_INT_GPIO_PIN);
}

void KEY1_INT_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY1_INT_GPIO_PIN);
    __HAL_GPIO_EXTI_CLEAR_IT(KEY1_INT_GPIO_PIN);
}

void KEY2_INT_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY2_INT_GPIO_PIN);
    __HAL_GPIO_EXTI_CLEAR_IT(KEY2_INT_GPIO_PIN);
}

void WKUP_INT_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(WKUP_INT_GPIO_PIN);
    __HAL_GPIO_EXTI_CLEAR_IT(WKUP_INT_GPIO_PIN);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    delay_ms(10);
    switch (GPIO_Pin)
    {
    case KEY0_INT_GPIO_PIN:
        if(!HAL_GPIO_ReadPin(KEY0_INT_GPIO_PORT,KEY0_INT_GPIO_PIN))
        {
            led_toggle(LED_0);
            led_toggle(LED_1);
        }
        break;
    
    case KEY1_INT_GPIO_PIN:
        if(!HAL_GPIO_ReadPin(KEY1_INT_GPIO_PORT,KEY1_INT_GPIO_PIN))
        {
            led_toggle(LED_0);
            // led_toggle(LED_1);
        }
        break;

    case KEY2_INT_GPIO_PIN:
        if(!HAL_GPIO_ReadPin(KEY2_INT_GPIO_PORT,KEY2_INT_GPIO_PIN))
        {
            // led_toggle(LED_0);
            led_toggle(LED_1);
        }
        break;
        
    default:
        break;
    }
}
