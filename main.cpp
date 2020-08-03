/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "time.h"

#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"

DigitalOut led1(LED1); //PI_1

void delay(int milliseconds)
{
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}

int main()
{   
    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
    BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
    
    BSP_LCD_Clear(LCD_COLOR_GREEN);
    BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *) "HELLO WORLD MBED+RENODE", CENTER_MODE);
    

    while (true)
    {
        printf("HELLO WORLD MBED+RENODE \n");          
        //thread_sleep_for(WAIT_TIME_MS);//does not work with Renode
        led1=!led1;
        delay(10000);
    }
}
