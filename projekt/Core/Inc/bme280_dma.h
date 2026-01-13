#pragma once
#include "stm32f4xx_hal.h"
#include <stdint.h>

typedef struct {
    I2C_HandleTypeDef *hi2c;
    uint8_t addr7;              // 0x76 lub 0x77
    volatile uint8_t done;
    volatile uint8_t err;
    uint8_t rx;
} bme280_dma_t;

void bme_init(bme280_dma_t *b, I2C_HandleTypeDef *hi2c, uint8_t addr7);
HAL_StatusTypeDef bme_read_id_dma(bme280_dma_t *b);
uint8_t bme_is_done(bme280_dma_t *b);
uint8_t bme_has_error(bme280_dma_t *b);
uint8_t bme_get_id(bme280_dma_t *b);
