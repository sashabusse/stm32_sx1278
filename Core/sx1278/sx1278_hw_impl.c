#include "sx1278_hw_impl.h"
#include "stm32f1xx_hal.h"

#include <stdio.h>

void sx_hw_delay_ms(uint32_t ms)
{
    HAL_Delay(ms);
}

void sx_hw_write_pin(sx1278_hw_pin *p_pin, int val)
{
    HAL_GPIO_WritePin(p_pin->port, p_pin->pin_msk, val == 1 ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void sx_hw_pin_config(sx1278_hw *p_hw);
void sx_hw_spi_config(sx1278_hw_spi *p_spi);
#define SX_HW_AFTER_RESET_DELAY_MS 20

void sx_hw_init(sx1278_hw *p_hw)
{
    sx_hw_pin_config(p_hw);
    sx_hw_spi_config(&(p_hw->spi));

    //reset under nss high
    sx_hw_write_pin(&(p_hw->nss), 1);
    sx_hw_write_pin(&(p_hw->reset), 0);
    sx_hw_delay_ms(5);
    sx_hw_write_pin(&(p_hw->reset), 1);
    sx_hw_delay_ms(SX_HW_AFTER_RESET_DELAY_MS);
}

#define SX_SPI_WRITE_BIT (1 << 7)
#define SX_SPI_READ_BIT (0 << 7)

#define SX_SPI_IO_MAX_DELAY 10000
void sx_hw_spi_write(sx1278_hw *p_hw, uint8_t addr, uint8_t *p_data, uint16_t sz)
{
    sx_hw_write_pin(&(p_hw->nss), 0);

    addr |= SX_SPI_WRITE_BIT;
    HAL_SPI_Transmit(&(p_hw->spi.td), &addr, 1, SX_SPI_IO_MAX_DELAY);
    while (HAL_SPI_GetState(&(p_hw->spi.td)) != HAL_SPI_STATE_READY)
    {
    }

    HAL_SPI_Transmit(&(p_hw->spi.td), p_data, sz, SX_SPI_IO_MAX_DELAY);
    while (HAL_SPI_GetState(&(p_hw->spi.td)) != HAL_SPI_STATE_READY)
    {
    }

    sx_hw_write_pin(&(p_hw->nss), 1);
}

void sx_hw_spi_read(sx1278_hw *p_hw, uint8_t addr, uint8_t *p_data, uint16_t sz)
{
    sx_hw_write_pin(&(p_hw->nss), 0);

    addr |= SX_SPI_READ_BIT;
    HAL_SPI_Transmit(&(p_hw->spi.td), &addr, 1, SX_SPI_IO_MAX_DELAY);
    while (HAL_SPI_GetState(&(p_hw->spi.td)) != HAL_SPI_STATE_READY)
    {
    }

    HAL_SPI_Receive(&(p_hw->spi.td), p_data, sz, SX_SPI_IO_MAX_DELAY);

    sx_hw_write_pin(&(p_hw->nss), 1);
}

void sx_hw_spi_pin_config(sx1278_hw_spi *p_spi);
void sw_hw_reset_pin_config(sx1278_hw_pin *p_reset);
void sx_hw_nss_pin_config(sx1278_hw_pin *p_nss);
void sx_hw_dio0_pin_config(sx1278_hw_pin *p_dio0);

void sx_hw_pin_config(sx1278_hw *p_hw)
{
    sx_hw_spi_pin_config(&(p_hw->spi));
    sw_hw_reset_pin_config(&(p_hw->reset));
    sx_hw_nss_pin_config(&(p_hw->nss));
    sx_hw_dio0_pin_config(&(p_hw->dio0));
}

void sx_hw_spi_pin_config(sx1278_hw_spi *p_spi)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (p_spi->td.Instance == SPI2)
    {
        /**SPI2 GPIO Configuration
        PB13     ------> SPI2_SCK
        PB14     ------> SPI2_MISO
        PB15     ------> SPI2_MOSI
        */
        GPIO_InitStruct.Pin = GPIO_PIN_13 | GPIO_PIN_15;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_14;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    }
    else
    {
        printf("this spi instance is not supported\r\n");
        while (1)
        {
        }
    }
}

void sw_hw_reset_pin_config(sx1278_hw_pin *p_reset)
{
    HAL_GPIO_WritePin(p_reset->port, p_reset->pin_msk, GPIO_PIN_SET);

    GPIO_InitTypeDef gpio_init;
    gpio_init.Pin = p_reset->pin_msk;
    gpio_init.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init.Pull = GPIO_NOPULL;
    gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(p_reset->port, &gpio_init);
}

void sx_hw_nss_pin_config(sx1278_hw_pin *p_nss)
{
    HAL_GPIO_WritePin(p_nss->port, p_nss->pin_msk, GPIO_PIN_SET);

    GPIO_InitTypeDef gpio_init;
    gpio_init.Pin = p_nss->pin_msk;
    gpio_init.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init.Pull = GPIO_NOPULL;
    gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(p_nss->port, &gpio_init);
}

void sx_hw_dio0_pin_config(sx1278_hw_pin *p_dio0)
{
    GPIO_InitTypeDef gpio_init;
    gpio_init.Pin = p_dio0->pin_msk;
    gpio_init.Mode = GPIO_MODE_INPUT;
    gpio_init.Pull = GPIO_NOPULL;
    gpio_init.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(p_dio0->port, &gpio_init);
}

void sx_hw_spi_config(sx1278_hw_spi *p_spi)
{
    p_spi->td.Init.Mode = SPI_MODE_MASTER;
    p_spi->td.Init.Direction = SPI_DIRECTION_2LINES;
    p_spi->td.Init.DataSize = SPI_DATASIZE_8BIT;
    p_spi->td.Init.CLKPolarity = SPI_POLARITY_LOW;
    p_spi->td.Init.CLKPhase = SPI_PHASE_1EDGE;
    p_spi->td.Init.NSS = SPI_NSS_SOFT;
    p_spi->td.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
    p_spi->td.Init.FirstBit = SPI_FIRSTBIT_MSB;
    p_spi->td.Init.TIMode = SPI_TIMODE_DISABLE;
    p_spi->td.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    p_spi->td.Init.CRCPolynomial = 10;
    if (HAL_SPI_Init(&(p_spi->td)) != HAL_OK)
    {
        printf("spi init failed\r\n");
        while (1)
        {
        }
    }
}
