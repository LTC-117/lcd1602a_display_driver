#ifndef __LCD1602A_DISPLAY_DRIVER_H__
#define __LCD1602A_DISPLAY_DRIVER_H__


#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_i2c.h"


void lcd_driver_init(I2C_TypeDef *i2c_module, uint32_t i2c_speed);


#endif
