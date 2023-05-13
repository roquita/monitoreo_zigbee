#pragma once
#include "Arduino.h"

#define ZIGBEE_SENSOR_HUMEDAD_DE_CAMA_ID (0x0010)
#define ZIGBEE_TEMPERATURA_AMBIENTAL_ID (0X0011)

void zigbee_init();
void zigbee_enviar_16bit_data(uint16_t sensor_id, uint16_t *data);
void zigbee_enviar_float_data(uint16_t sensor_id, float *data);