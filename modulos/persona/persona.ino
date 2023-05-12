#include <Arduino.h>
#include "sensores.h"
#include "zigbee.h"

void setup()
{
    Serial.begin(115200);

    sensor_caidas_init();
    sensor_boton_de_usuario_init();
    sensor_temperatura_corporal_init();
    sensor_ritmo_cardiaco_y_concentracion_spo2_init();

    periodo_init();

    zigbee_init();
}

void loop()
{

    if (sensor_caidas_activado())
    {
        Serial.println(F("sensor_caidas_activado"));

        // ENVIAR INFORMACION DE SENSOR DE CAIDA POR ZIGBEE
        uint16_t caida_detectada = 1;
        zigbee_enviar_16bit_data(ZIGBEE_SENSOR_CAIDA_ID, &caida_detectada);
        caida_detectada = 0;
        zigbee_enviar_16bit_data(ZIGBEE_SENSOR_CAIDA_ID, &caida_detectada);

        // RESET SENSOR DE CAIDAS
        sensor_caidas_reset();
    }

    if (sensor_boton_de_usuario_presionado())
    {
        Serial.println(F("boton_de_usuario_presionado"));

        // ENVIAR INFORMACION DE SENSOR BOTON POR ZIGBEE
        uint16_t boton_presionado = 1;
        zigbee_enviar_16bit_data(ZIGBEE_SENSOR_BOTON_ID, &boton_presionado);
        boton_presionado = 0;
        zigbee_enviar_16bit_data(ZIGBEE_SENSOR_BOTON_ID, &boton_presionado);

        // ENVIAR INFORMACION DE SENSOR TEMPERATURA CORPORAL POR ZIGBEE
        float temperatura_corporal = sensor_temperatura_corporal_leer();
        Serial.print(F("temperatura_corporal:"));
        Serial.println(temperatura_corporal, 2);
        zigbee_enviar_float_data(ZIGBEE_SENSOR_TEMPERATURA_CORPORAL_ID, &temperatura_corporal);

        // ENVIAR INFORMACION DE SENSORES RITMO CARDIACO Y CONCENTRACION DE SPO2
        uint16_t ritmo_cardiaco = 0;
        uint16_t concentracion_spo2 = 0;
        sensor_ritmo_cardiaco_y_concentracion_spo2_leer(&ritmo_cardiaco, &concentracion_spo2);
        Serial.print(F("ritmo_cardiaco:"));
        Serial.println(ritmo_cardiaco);
        Serial.print(F("concentracion_spo2:"));
        Serial.println(concentracion_spo2);
        zigbee_enviar_16bit_data(ZIGBEE_SENSOR_RITMO_CARDIACO_ID, &ritmo_cardiaco);
        zigbee_enviar_16bit_data(ZIGBEE_SENSOR_CONCENTRACION_SPO2_ID, &concentracion_spo2);

        // RESET SENSOR BOTON
        sensor_boton_de_usuario_reset();
    }
    if (periodo_expirado())
    {

        Serial.println(F("periodo_expirado"));

        // ENVIAR INFORMACION DE SENSOR TEMPERATURA CORPORAL POR ZIGBEE
        float temperatura_corporal = sensor_temperatura_corporal_leer();
        Serial.print(F("temperatura_corporal:"));
        Serial.println(temperatura_corporal, 2);
        zigbee_enviar_float_data(ZIGBEE_SENSOR_TEMPERATURA_CORPORAL_ID, &temperatura_corporal);

        // ENVIAR INFORMACION DE SENSORES RITMO CARDIACO Y CONCENTRACION DE SPO2
        uint16_t ritmo_cardiaco = 0;
        uint16_t concentracion_spo2 = 0;
        sensor_ritmo_cardiaco_y_concentracion_spo2_leer(&ritmo_cardiaco, &concentracion_spo2);
        Serial.print(F("ritmo_cardiaco:"));
        Serial.println(ritmo_cardiaco);
        Serial.print(F("concentracion_spo2:"));
        Serial.println(concentracion_spo2);
        zigbee_enviar_16bit_data(ZIGBEE_SENSOR_RITMO_CARDIACO_ID, &ritmo_cardiaco);
        zigbee_enviar_16bit_data(ZIGBEE_SENSOR_CONCENTRACION_SPO2_ID, &concentracion_spo2);

        periodo_reset();
    }
    delay(1);
}