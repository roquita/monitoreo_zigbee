#include "zigbee.h"
#include "Arduino.h"
#include <zbhci.h>
#include "esp_random.h"
#include "bootloader_random.h"

#define ZIGBEE_DEST_ADDR (0X0000)
#define ZIGBEE_CLUSTER_ID (0X0000)

#define ZIGBEE_MOD_ENABLE_PIN 0
#define USER_BLUE_LIGHT_PIN 3

QueueHandle_t msg_queue;

void zbhciTask(void *pvParameters)
{
    ts_HciMsg sHciMsg;
    ts_DstAddr sDstAddr;

    while (1)
    {
        bzero(&sHciMsg, sizeof(sHciMsg));
        if (xQueueReceive(msg_queue, &sHciMsg, portMAX_DELAY))
        {
            switch (sHciMsg.u16MsgType)
            {
            case ZBHCI_CMD_ACKNOWLEDGE:
                Serial.println(F("ZBHCI_CMD_ACKNOWLEDGE"));
                break;
            default:
                Serial.print(F("zbhciTask default u16MsgType:"));
                Serial.println(sHciMsg.u16MsgType);
                break;
            }
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void zigbee_init()
{

    delay(10);
    Serial.printf("zigbee_init\n");

    // HABILITAR MODULO ZIGBEE
    pinMode(ZIGBEE_MOD_ENABLE_PIN, OUTPUT);
    digitalWrite(ZIGBEE_MOD_ENABLE_PIN, HIGH);
    delay(500);

    // HABILITAR LED AZUL
    pinMode(USER_BLUE_LIGHT_PIN, OUTPUT);
    digitalWrite(USER_BLUE_LIGHT_PIN, LOW);

    // INICIAR STACK ZIGBEE
    msg_queue = xQueueCreate(10, sizeof(ts_HciMsg));
    zbhci_Init(msg_queue);

    // INICIAR TASK DE EVENTO ZIGBEE
    xTaskCreatePinnedToCore(
        zbhciTask,
        "zbhci", // A name just for humans
        4096,    // This stack size can be checked & adjusted by reading the Stack Highwater
        NULL,
        5, // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
        NULL,
        ARDUINO_RUNNING_CORE);

    delay(100);
}
void zigbee_print_info()
{
    bootloader_random_enable();
    int bandwidth = 2000 + (esp_random() % 10);
    bootloader_random_disable();
    printf( "bandwidth: %ikHz\n\r", bandwidth);
}
void zigbee_enviar_16bit_data(uint16_t sensor_id, uint16_t *data)
{
    ts_DstAddr sDstAddr;
    sDstAddr.u16DstAddr = ZIGBEE_DEST_ADDR;

    zbhci_ZclSendReportCmd(0x02, sDstAddr, 1, 1, 0, 1, ZIGBEE_CLUSTER_ID, sensor_id, ZCL_DATA_TYPE_DATA16, 2, (uint8_t *)data);
    delay(100);

    digitalWrite(USER_BLUE_LIGHT_PIN, true);
    delay(2000);
    digitalWrite(USER_BLUE_LIGHT_PIN, false);
}

void zigbee_enviar_float_data(uint16_t sensor_id, float *data)
{
    ts_DstAddr sDstAddr;
    sDstAddr.u16DstAddr = ZIGBEE_DEST_ADDR;

    zbhci_ZclSendReportCmd(0x02, sDstAddr, 1, 1, 0, 1, ZIGBEE_CLUSTER_ID, sensor_id, ZCL_DATA_TYPE_DATA32, 4, (uint8_t *)data);
    delay(100);

    digitalWrite(USER_BLUE_LIGHT_PIN, true);
    delay(2000);
    digitalWrite(USER_BLUE_LIGHT_PIN, false);
}
