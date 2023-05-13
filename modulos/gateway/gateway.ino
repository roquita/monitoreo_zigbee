
#include "Arduino.h"
#include "zigbee.h"
#include "connect.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

void setup()
{
    Serial.begin(115200);
    zigbee_init();
    connect_wifi();
    Serial.println(F("GATEWAY SETUP DONE!!!!"));
}

void loop()
{
    if (datos_ambiente_recibido)
    {
        datos_ambiente_recibido = false;
        char json[100] = {0};
        snprintf(json, sizeof(json), "{\"tempAmbient\":%.2f,\"humCama\":\"%s\"}",
                 sensor_temperatura_ambiental_val, sensor_humedad_de_cama_val == 0 ? "Seco" : "Humedo");
        printf("json: \"%s\"\n\r", json);

        // enviar a servidor
        connect_server(json, "/api/v1/habitacion");
    }

    if (datos_pastillero_recibido)
    {
        datos_pastillero_recibido = false;
        char json[100] = {0};
        snprintf(json, sizeof(json), "{\"nivelPasti\":%u}", sensor_nivel_de_pastillero_val);
        printf("json: \"%s\"\n\r", json);

        // enviar a servidor
        connect_server(json, "/api/v1/pastillero");
    }
    if (datos_persona_recibido)
    {
        datos_persona_recibido = false;
        char json[100] = {0};
        snprintf(json, sizeof(json), "{\"caidaDetect\":%s,\"tempCorpor\":%.2f,\"satOxig\":%u,\"ritmoCardiac\":%u}",
                 (sensor_caida_val == 1) ? "true" : "false", sensor_temperatura_corporal_val + 0.01,
                 sensor_concentracion_spo2_val, sensor_ritmo_cardiaco_val);
        printf("json: \"%s\"\n\r", json);

        // enviar a servidor
        connect_server(json, "/api/v1/persona");
    }
    if (boton_emergencia_activado)
    {
        boton_emergencia_activado = false;
        char json[100] = {0};
        snprintf(json, sizeof(json), "{\"isActive\":true}");
        printf("json: \"%s\"\n\r", json);

        // enviar a servidor
        connect_server(json, "/api/v1/boton");
    }

    delay(1);
}
