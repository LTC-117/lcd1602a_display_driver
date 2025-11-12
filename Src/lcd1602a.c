/** @file lcd1602a.c
 *
 * @brief Simple, non-portable STM32F103 driver for integration with the
 * LCD-1602A Display through an PCF8574T I2C Module.
 *
 * @par
 * Copyright (c) 2025 Lucas Tentoni Costa
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "lcd1602a.h"

#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_i2c.h"
#include "main.h"
//#include "stm32f103xb.h"
//#include <stdint.h>

/* 
 * @pinout
 *
 * I2C1_SCL -> PB6 | AF Open Drain
 * I2C1_SDA -> PB7 | AF Open Drain
 *
 * N = 1 -> 2-line display
 * F = 0 -> 5×8 dots font
 * D = 1 -> display on
 */


//static uint8_t lcd_buffer[LCD_BUFFER_SIZE];


/*!
 * @brief Initialize the STM32 board's I2C module
 * @param i2c_module  The address of the respective I2C Module selected.
 * @param i2c_speed   The clock speed operation for the selected module.
 * @retval None
 */
void lcd_driver_init(I2C_TypeDef *i2c_module, uint32_t i2c_speed)
{
    /* --------------- GPIO Initialization --------------- */

    uint32_t gpio_pin_scl = (i2c_module == I2C1)
        ? GPIO_PIN_6
        : GPIO_PIN_10;

    uint32_t gpio_pin_sda = (i2c_module == I2C1)
        ? GPIO_PIN_7
        : GPIO_PIN_11;

    GPIO_InitTypeDef i2c1_scl = {
        .Pin = gpio_pin_scl,
        .Mode = GPIO_MODE_AF_OD,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_FREQ_MEDIUM
    };

    GPIO_InitTypeDef i2c1_sda = {
        .Pin = gpio_pin_sda,
        .Mode = GPIO_MODE_AF_OD,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_FREQ_MEDIUM
    };

    HAL_GPIO_Init(GPIOB, &i2c1_scl);
    HAL_GPIO_Init(GPIOB, &i2c1_sda);

    /* --------------- I2C Initialization --------------- */

    I2C_InitTypeDef initialize = {
        .ClockSpeed = i2c_speed,
        .DutyCycle  = I2C_DUTYCYCLE_2,
        .OwnAddress1 = 0,
        .OwnAddress2 = 0,
        .AddressingMode = I2C_ADDRESSINGMODE_7BIT,
        .DualAddressMode = I2C_DUALADDRESS_DISABLE,
        .GeneralCallMode = I2C_GENERALCALL_DISABLE,
        .NoStretchMode = I2C_NOSTRETCH_DISABLE
    };

    I2C_HandleTypeDef hi2c = {
        .Instance = i2c_module,
        .Init     = initialize,
    };

    if (HAL_I2C_Init(&hi2c) != HAL_OK) {
        Error_Handler();
    }
} /* lcd_driver_init() */


void lcd_driver_write(void)
{
} /* lcd_driver_init() */
