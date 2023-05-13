#include "Arduino.h"
#include "zigbee.h"
#include <stdio.h>
#include <stdbool.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include <string.h>
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "esp_system.h"
#include "zbhci.h"

#define ZIGBEE_MOD_ENABLE_PIN 0

/* AMBIENTE*/
#define ZIGBEE_SENSOR_HUMEDAD_DE_CAMA_ID (0x0010)
#define ZIGBEE_TEMPERATURA_AMBIENTAL_ID (0X0011)

/* PASTILLERO*/
#define ZIGBEE_SENSOR_NIVEL_DE_PASTILLERO_ID (0x0020)

/* PERSONA*/
#define ZIGBEE_SENSOR_CAIDA_ID (0x0030)
#define ZIGBEE_SENSOR_TEMPERATURA_CORPORAL_ID (0X0032)
#define ZIGBEE_SENSOR_RITMO_CARDIACO_ID (0X0033)
#define ZIGBEE_SENSOR_CONCENTRACION_SPO2_ID (0X0034)

/* BOTON EMERGENCIA*/
#define ZIGBEE_SENSOR_BOTON_ID (0X0031)

QueueHandle_t msg_queue;

/* AMBIENTE*/
float sensor_temperatura_ambiental_val = 0.0;
uint16_t sensor_humedad_de_cama_val = 0;
volatile bool datos_ambiente_recibido = false;

/* PASTILLERO*/
uint16_t sensor_nivel_de_pastillero_val = 0;
volatile bool datos_pastillero_recibido = false;

/* PERSONA*/
uint16_t sensor_caida_val = 0;
float sensor_temperatura_corporal_val = 0.0;
uint16_t sensor_ritmo_cardiaco_val = 0;
uint16_t sensor_concentracion_spo2_val = 0;
volatile bool datos_persona_recibido = false;

/* BOTON EMERGENCIA*/
uint16_t sensor_boton_de_usuario_val = 0;
volatile bool boton_emergencia_activado = false;

void appHandleZCLreportMsgRcv(ts_MsgZclReportMsgRcvPayload *payload)
{

    printf("appHandleZCLreportMsgRcv ==> ");

    switch (payload->u16ClusterId)
    {
    case 0x0000: // Basic Cluster
        for (size_t i = 0; i < payload->u8AttrNum; i++)
        {
            printf(" u8AttrNum:%u || ", i);
            printf(" u16AttrID: %u || ", payload->asAttrList[i].u16AttrID);
            printf(" u8DataType: %u || ", payload->asAttrList[i].u8DataType);
            printf(" u16DataLen: %u || ", payload->asAttrList[i].u16DataLen);

            uint16_t attrID = payload->asAttrList[i].u16AttrID;

            bool data_is_16bit = (payload->asAttrList[i].u8DataType == ZCL_DATA_TYPE_DATA16);
            if (data_is_16bit)
            {
                uint16_t data = payload->asAttrList[i].uAttrData.u16AttrData;
                printf(" data: %u\n\r", data);

                if (attrID == ZIGBEE_SENSOR_HUMEDAD_DE_CAMA_ID)
                {
                    sensor_humedad_de_cama_val = data;
                    datos_ambiente_recibido = true;
                }

                if (attrID == ZIGBEE_SENSOR_NIVEL_DE_PASTILLERO_ID)
                {
                    sensor_nivel_de_pastillero_val = data;
                    datos_pastillero_recibido = true;
                }

                if (attrID == ZIGBEE_SENSOR_BOTON_ID)
                {
                    sensor_boton_de_usuario_val = data;
                    boton_emergencia_activado = true;
                }
                if (attrID == ZIGBEE_SENSOR_CAIDA_ID)
                {
                    sensor_caida_val = data;
                }
                if (attrID == ZIGBEE_SENSOR_RITMO_CARDIACO_ID)
                {
                    sensor_ritmo_cardiaco_val = data;
                }
                if (attrID == ZIGBEE_SENSOR_CONCENTRACION_SPO2_ID)
                {
                    sensor_concentracion_spo2_val = data;
                    datos_persona_recibido = true;
                }
            }

            bool data_is_32bit = (payload->asAttrList[i].u8DataType == ZCL_DATA_TYPE_DATA32);
            if (data_is_32bit)
            {
                float data = *((float *)(&(payload->asAttrList[i].uAttrData.u32AttrData)));
                printf(" data: %.2f\n\r", data);

                if (attrID == ZIGBEE_TEMPERATURA_AMBIENTAL_ID)
                {
                    sensor_temperatura_ambiental_val = data;
                }
                if (attrID == ZIGBEE_SENSOR_TEMPERATURA_CORPORAL_ID)
                {
                    sensor_temperatura_corporal_val = data;
                }
            }

            if (!data_is_16bit && !data_is_32bit)
            {
                printf(" nodata\n\r");
            }
        }
        break;

    default:
        printf("appHandleZCLreportMsgRcv: default\n");
        break;
    }
}

void zbhciTask(void *pvParameters)
{
    ts_HciMsg sHciMsg;

    // HABILITAR CONEXIONES HACIA EL COORDINADOR
    zbhci_MgmtPermitJoinReq(0xFFFC, 0xFF, 1);

    // RECEPCIONAR MENSAJES DE TRANSMISORES
    while (1)
    {
        bzero(&sHciMsg, sizeof(sHciMsg));
        if (xQueueReceive(msg_queue, &sHciMsg, portMAX_DELAY))
        {
            switch (sHciMsg.u16MsgType)
            {
            case ZBHCI_CMD_ZCL_REPORT_MSG_RCV:
                Serial.println(F("ZBHCI_CMD_ZCL_REPORT_MSG_RCV"));
                appHandleZCLreportMsgRcv(&sHciMsg.uPayload.sZclReportMsgRcvPayload);

                break;
            default:
                Serial.print(F("zbhciTask default: 0x"));
                Serial.println(sHciMsg.u16MsgType, HEX);
                break;
            }
        }
        delay(100);
    }
    vTaskDelete(NULL);
}

void zigbee_init()
{
    // HABILITAR MODULO ZIGBEE
    pinMode(ZIGBEE_MOD_ENABLE_PIN, OUTPUT);
    digitalWrite(ZIGBEE_MOD_ENABLE_PIN, HIGH);

    // HABILITAR ZIGBEE STACK
    msg_queue = xQueueCreate(10, sizeof(ts_HciMsg));
    zbhci_Init(msg_queue);
    delay(100);
    xTaskCreatePinnedToCore(zbhciTask, "zbhciTask", 4096, NULL, 5, NULL, ARDUINO_RUNNING_CORE);
    delay(100);
}