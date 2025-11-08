#include "lcd1602a.h"

#include "main.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_i2c.h"
#include "stm32f103xb.h"
#include <stdint.h>


/* 
 * I2C1_SCL -> PB6 | AF Open Drain
 * I2C1_SDA -> PB7 | AF Open Drain
 *
 * N = 1 -> 2-line display
 * F = 0 -> 5×8 dots font
 * D = 1 -> display on
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
}
