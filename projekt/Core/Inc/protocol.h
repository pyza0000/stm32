#pragma once
#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stddef.h>

#define FRAME_START   0x7E
#define FRAME_END     0x7F
#define FRAME_ESC     0x7D
#define FRAME_XOR     0x20

#define ADDR_PC       0x01
#define ADDR_STM32    0x02

// CMD
#define CMD_READ_NOW      0x10
#define CMD_CUR_VALUE     0x11
#define CMD_SET_PERIOD    0x12
#define CMD_GET_PERIOD    0x13
#define CMD_GET_HISTORY   0x14
#define CMD_HISTORY_DATA  0x15
#define CMD_ACK           0x16
#define CMD_NACK          0x17

// NACK ERR
#define ERR_CRC_ERROR     0x01
#define ERR_FORMAT_ERROR  0x02
#define ERR_PARAM_ERROR   0x03
#define ERR_DEVICE_ERROR  0x04
#define ERR_NO_DATA       0x05

typedef struct {
    UART_HandleTypeDef *huart;
    uint8_t self_addr;
} proto_ctx_t;

void proto_init(proto_ctx_t *ctx, UART_HandleTypeDef *huart, uint8_t self_addr);
void proto_rx_byte(proto_ctx_t *ctx, uint8_t b);

void proto_send_frame(proto_ctx_t *ctx, uint8_t dst, uint8_t cmd, const uint8_t *data, uint8_t len);
void proto_send_ack(proto_ctx_t *ctx, uint8_t dst);
void proto_send_nack(proto_ctx_t *ctx, uint8_t dst, uint8_t err);

// Musisz zaimplementować w main.c (albo osobnym module):
int16_t app_read_bme280_temp_centi(void);              // np. 2534 = 25.34°C
void    app_set_period_ms(uint32_t period_ms);
uint32_t app_get_period_ms(void);
uint8_t  app_get_history(uint8_t maxN, int16_t *out);  // zwraca ile wpisów zwrócił
