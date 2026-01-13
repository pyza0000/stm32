#include "bme280_dma.h"

#define BME_REG_ID 0xD0

static inline uint16_t dev8(const bme280_dma_t *b){ return (uint16_t)(b->addr7 << 1); }

void bme_init(bme280_dma_t *b, I2C_HandleTypeDef *hi2c, uint8_t addr7)
{
    b->hi2c = hi2c;
    b->addr7 = addr7;
    b->done = 0;
    b->err = 0;
    b->rx = 0;
}

HAL_StatusTypeDef bme_read_id_dma(bme280_dma_t *b)
{
    b->done = 0;
    b->err = 0;
    return HAL_I2C_Mem_Read_DMA(b->hi2c, dev8(b), BME_REG_ID, I2C_MEMADD_SIZE_8BIT, &b->rx, 1);
}

uint8_t bme_is_done(bme280_dma_t *b){ return b->done; }
uint8_t bme_has_error(bme280_dma_t *b){ return b->err; }
uint8_t bme_get_id(bme280_dma_t *b){ return b->rx; }
