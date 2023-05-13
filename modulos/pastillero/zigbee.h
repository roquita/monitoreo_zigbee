#pragma once
#include "Arduino.h"

#define ZIGBEE_SENSOR_NIVEL_DE_PASTILLERO_ID (0x0020)

void zigbee_init();
void zigbee_enviar_16bit_data(uint16_t sensor_id, uint16_t *data);
void zigbee_enviar_float_data(uint16_t sensor_id, float *data);