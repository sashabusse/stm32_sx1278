#include <stdio.h>
#include "sx1278_hw_impl.h"

void SystemClock_Config(void);

#define SX_SPI_READ_BYTES 1

int main(void)
{
  HAL_Init();

  SystemClock_Config();

  sx1278_hw hw;

  hw.spi.td.Instance = SPI2;

  hw.nss.port = GPIOB;
  hw.nss.pin_msk = GPIO_PIN_12;

  hw.reset.port = GPIOA;
  hw.reset.pin_msk = GPIO_PIN_8;

  hw.dio0.port = GPIOA;
  hw.dio0.pin_msk = GPIO_PIN_9;

  sx_hw_init(&hw);

  //-------------------------------------------
  //uint8_t wr_data[1] = {0x08};
  //sx_hw_spi_write(&hw, 0x01, wr_data, 1);
  //-------------------------------------------
  //uint8_t wr_data[2] = {0x01 | (1 << 7), 0x08};
  //sx_hw_write_pin(&(hw.nss), 0);
  //
  //HAL_SPI_Transmit(&(hw.spi.td), wr_data, 2, 10000);
  //while (HAL_SPI_GetState(&(hw.spi.td)) != HAL_SPI_STATE_READY)
  //{
  //}
  //sx_hw_write_pin(&(hw.nss), 1);
  //-------------------------------------------

  //-------------------------------------------
  uint8_t re_data[SX_SPI_READ_BYTES];
  sx_hw_spi_read(&hw, 0x01, re_data, SX_SPI_READ_BYTES);

  printf("got values: \r\n");
  for (int i = 0; i < SX_SPI_READ_BYTES; i++)
  {
    printf("0x%X\r\n", re_data[i]);
  }
  printf("\r\n");
  //-------------------------------------------

  while (1)
  {
  }
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    printf("clock_init failed\r\n");
    while (1)
    {
    }
  }
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    printf("clock_init failed\r\n");
    while (1)
    {
    }
  }

  __HAL_RCC_SPI2_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
}
