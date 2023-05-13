#pragma once

/* AMBIENTE*/
extern float sensor_temperatura_ambiental_val;
extern uint16_t sensor_humedad_de_cama_val;
extern volatile bool datos_ambiente_recibido;

/* PASTILLERO*/
extern uint16_t sensor_nivel_de_pastillero_val;
extern volatile bool datos_pastillero_recibido;

/* PERSONA*/
extern uint16_t sensor_caida_val;
extern float sensor_temperatura_corporal_val;
extern uint16_t sensor_ritmo_cardiaco_val;
extern uint16_t sensor_concentracion_spo2_val;
extern volatile bool datos_persona_recibido;

/* BOTON EMERGENCIA*/
extern uint16_t sensor_boton_de_usuario_val;
extern volatile bool boton_emergencia_activado;

void zigbee_init();