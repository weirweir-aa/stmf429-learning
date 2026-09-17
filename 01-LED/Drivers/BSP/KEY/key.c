#include "key.h"
#include "./BSP/LED/led.h"

/*
*基础按键 按键还可以扩展
*   1.长按 短按
*   2.按下时间多长
    3.连续按
*/

bool KEY0_PRES=0;
bool KEY1_PRES=0;
bool KEY2_PRES=0;
bool KEY_UP_PRES=0;

void key_init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct={0};
    GPIO_InitStruct.Mode=GPIO_MODE_INPUT;
    GPIO_InitStruct.Speed=GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Pull=GPIO_PULLUP;

    GPIO_InitStruct.Pin =KEY0_GPIO_PIN | KEY1_GPIO_PIN;
    HAL_GPIO_Init(KEY0_GPIO_PORT,&GPIO_InitStruct);

    GPIO_InitStruct.Pin =KEY2_GPIO_PIN;
    HAL_GPIO_Init(KEY2_GPIO_PORT,&GPIO_InitStruct);

    GPIO_InitStruct.Mode=GPIO_MODE_INPUT;
    GPIO_InitStruct.Speed=GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Pull=GPIO_PULLDOWN;
    GPIO_InitStruct.Pin =WKUP_GPIO_PIN;
    HAL_GPIO_Init(WKUP_GPIO_PORT,&GPIO_InitStruct);
}
/*
*关于这个按键设计的解释：
*	1.判定按键按下 如果是第一次按下（检测到下降沿）就把key0_released设置为false表示按下
				如果key0_released已经是flase也就是表示按下还没松开
	2.判定按键没有按下 表示检测到上升沿（同时起到每一次循环都置位的作用）
*
	这个设计目前不支持连按和两个按键一起按下

*/
KEY_e key_scan(void)
{
    static bool key0_released = true;      /* 上次扫描时按键是否已松开 */
	static bool key1_released = true;
	static bool key2_released = true;
	static bool key_up_released = true;
	
    if(HAL_GPIO_ReadPin(KEY0_GPIO_PORT, KEY0_GPIO_PIN) == GPIO_PIN_RESET)
    {
        bool pressed = (HAL_GPIO_ReadPin(KEY0_GPIO_PORT, KEY0_GPIO_PIN) == GPIO_PIN_RESET);
        if (pressed && key0_released)          /* 下降沿 */
        {
            delay_ms(10);
            if (HAL_GPIO_ReadPin(KEY0_GPIO_PORT, KEY0_GPIO_PIN) == GPIO_PIN_RESET)
            {
                key0_released = false;
                return KEY0;                  /* 只在按下的那一次返回 */
            }
        }
		else if(!key0_released)
		{
			return KEY0;
		}
    }
	else
	{
		key0_released = true;	
	}

    if(HAL_GPIO_ReadPin(KEY1_GPIO_PORT, KEY1_GPIO_PIN) == GPIO_PIN_RESET)
    {
        bool pressed = (HAL_GPIO_ReadPin(KEY1_GPIO_PORT, KEY1_GPIO_PIN) == GPIO_PIN_RESET);
        if (pressed && key1_released)          /* 下降沿 */
        {
            delay_ms(10);
            if (HAL_GPIO_ReadPin(KEY1_GPIO_PORT, KEY1_GPIO_PIN) == GPIO_PIN_RESET)
            {
                key1_released = false;
                return KEY1;                  /* 只在按下的那一次返回 */
            }
        }
		else if(!key1_released)
		{
			return KEY1;
		}
    }
	else
	{
		key1_released = true;
	}

    if(HAL_GPIO_ReadPin(KEY2_GPIO_PORT, KEY2_GPIO_PIN) == GPIO_PIN_RESET)
    {
        bool pressed = (HAL_GPIO_ReadPin(KEY2_GPIO_PORT, KEY2_GPIO_PIN) == GPIO_PIN_RESET);
        if (pressed && key2_released)          /* 下降沿 */
        {
            delay_ms(10);
            if (HAL_GPIO_ReadPin(KEY2_GPIO_PORT, KEY2_GPIO_PIN) == GPIO_PIN_RESET)
            {
                key2_released = false;
                return KEY2;                  /* 只在按下的那一次返回 */
            }
        }
		else if(!key2_released)
		{
			return KEY2;
		}
    }
	else
	{
		key2_released = true; 
	}

    if(HAL_GPIO_ReadPin(WKUP_GPIO_PORT, WKUP_GPIO_PIN) == GPIO_PIN_SET)
    {
        bool pressed = (HAL_GPIO_ReadPin(WKUP_GPIO_PORT, WKUP_GPIO_PIN) == GPIO_PIN_SET);
        if (pressed && key_up_released)          /* 下降沿 */
        {
            delay_ms(10);
            if (HAL_GPIO_ReadPin(WKUP_GPIO_PORT, WKUP_GPIO_PIN) == GPIO_PIN_SET)
            {
                key_up_released = false;
                return WKUP;                  /* 只在按下的那一次返回 */
            }
        }
		else if(!key_up_released)
		{
			return WKUP;
		}
    }
	else
	{
		key_up_released = true;	
	}

    return KEY_NUM;
}

//测试
void key_test(void)
{
    KEY_e key = key_scan();
		
    if (key == KEY0)
    {
        led_toggle(LED_0);
        led_toggle(LED_1);
        delay_ms(500);
    }
    else if (key == KEY1)
    {
        led_on(LED_0);
        led_off(LED_1);
    }
    else if (key == KEY2)
    {
        led_off(LED_0);
        led_on(LED_1);
    }else
    {
        led_off(LED_0);                                 /* 翻转LED0 */
        led_off(LED_1);                                 /* 翻转LED1 */
    }
}