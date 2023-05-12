#pragma once
#include "Arduino.h"

#define ZIGBEE_SENSOR_CAIDA_ID (0x0030)
#define ZIGBEE_SENSOR_BOTON_ID (0X0031)
#define ZIGBEE_SENSOR_TEMPERATURA_CORPORAL_ID (0X0032)
#define ZIGBEE_SENSOR_RITMO_CARDIACO_ID (0X0033)
#define ZIGBEE_SENSOR_CONCENTRACION_SPO2_ID (0X0034)

void zigbee_init();
void zigbee_enviar_16bit_data(uint16_t sensor_id, uint16_t *data);
void zigbee_enviar_float_data(uint16_t sensor_id, float *data);