#ifndef __SX1278_HW_IMPL_H
#define __SX1278_HW_IMPL_H

#include "stm32f1xx.h"

typedef struct __sx1278_hw_pin
{
    GPIO_TypeDef *port;
    uint32_t pin_msk;
} sx1278_hw_pin;

typedef struct __sx1278_hw_spi
{
    SPI_HandleTypeDef td;
} sx1278_hw_spi;

typedef struct __sx1278_hw
{
    sx1278_hw_spi spi;
    sx1278_hw_pin nss;
    sx1278_hw_pin reset;
    sx1278_hw_pin dio0;
    //not used yet
    //sx1278_hw_pin dio1;
    //sx1278_hw_pin dio2;
} sx1278_hw;

void sx_hw_init(sx1278_hw *p_hw);
void sx_hw_delay_ms(uint32_t ms);
void sx_hw_write_pin(sx1278_hw_pin *p_pin, int val);
void sx_hw_spi_write(sx1278_hw *p_hw, uint8_t addr, uint8_t *p_data, uint16_t sz);
void sx_hw_spi_read(sx1278_hw *p_hw, uint8_t addr, uint8_t *p_data, uint16_t sz);

#endif