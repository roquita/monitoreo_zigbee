#include <Arduino.h>
#include "sensores.h"
#include "zigbee.h"

void setup()
{
    Serial.begin(115200);

    sensor_humedad_de_cama_init();
    sensor_temperatura_ambiental_init();
    sensor_boton_de_usuario_init();

    periodo_init();

    zigbee_init();
    zigbee_print_info();
}

void loop()
{

    if (sensor_boton_de_usuario_presionado())
    {
        Serial.println(F("boton_de_usuario_presionado"));

        // ENVIAR INFORMACION DE SENSOR TEMPERATURA AMBIENTAL POR ZIGBEE
        float temperatura_ambiental = sensor_temperatura_ambiental_leer();
        Serial.print(F("temperatura_ambiental:"));
        Serial.println(temperatura_ambiental, 2);
        zigbee_enviar_float_data(ZIGBEE_TEMPERATURA_AMBIENTAL_ID, &temperatura_ambiental);

        // ENVIAR INFORMACION DE SENSOR HUMEDAD DE CAMA POR ZIGBEE
        uint16_t humedad_de_cama = sensor_humedad_de_cama_leer();
        Serial.print(F("humedad_de_cama:"));
        Serial.println(humedad_de_cama);
        zigbee_enviar_16bit_data(ZIGBEE_SENSOR_HUMEDAD_DE_CAMA_ID, &humedad_de_cama);

        // RESET SENSOR BOTON
        sensor_boton_de_usuario_reset();
    }
    if (periodo_expirado())
    {

        Serial.println(F("periodo_expirado"));

        // ENVIAR INFORMACION DE SENSOR TEMPERATURA AMBIENTAL POR ZIGBEE
        float temperatura_ambiental = sensor_temperatura_ambiental_leer();
        Serial.print(F("temperatura_ambiental:"));
        Serial.println(temperatura_ambiental, 2);
        zigbee_enviar_float_data(ZIGBEE_TEMPERATURA_AMBIENTAL_ID, &temperatura_ambiental);

        // ENVIAR INFORMACION DE SENSOR HUMEDAD DE CAMA POR ZIGBEE
        uint16_t humedad_de_cama = sensor_humedad_de_cama_leer();
        Serial.print(F("humedad_de_cama:"));
        Serial.println(humedad_de_cama);
        zigbee_enviar_16bit_data(ZIGBEE_SENSOR_HUMEDAD_DE_CAMA_ID, &humedad_de_cama);

        periodo_reset();
    }
    delay(1);
}