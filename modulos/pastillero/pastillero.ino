#include <Arduino.h>
#include "sensores.h"
#include "zigbee.h"

void setup()
{
    Serial.begin(115200);

    sensor_nivel_de_pastillero_init();
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

        // ENVIAR INFORMACION DE SENSOR PASTILLERO POR ZIGBEE
        uint16_t nivel_de_pastillero = sensor_nivel_de_pastillero_leer();
        Serial.print(F("nivel_de_pastillero(cm):"));
        Serial.println(nivel_de_pastillero);
        zigbee_enviar_16bit_data(ZIGBEE_SENSOR_NIVEL_DE_PASTILLERO_ID, &nivel_de_pastillero);

        // RESET SENSOR BOTON
        sensor_boton_de_usuario_reset();
    }
    if (periodo_expirado())
    {

        Serial.println(F("periodo_expirado"));

        // ENVIAR INFORMACION DE SENSOR PASTILLERO  POR ZIGBEE
        uint16_t nivel_de_pastillero = sensor_nivel_de_pastillero_leer();
        Serial.print(F("nivel_de_pastillero(cm):"));
        Serial.println(nivel_de_pastillero);
        zigbee_enviar_16bit_data(ZIGBEE_SENSOR_NIVEL_DE_PASTILLERO_ID, &nivel_de_pastillero);

        periodo_reset();
    }
    delay(1);
}