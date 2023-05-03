
#include "WiFi.h"
#include "esp_wifi.h"

// CABECERAS PARA MODULO ZIGBEE TLSR8258
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
QueueHandle_t msg_queue;

// CABECERAS  PARA LED 
#define CONFIG_BLUE_LIGHT_PIN 3

void setup()
{
    Serial.begin(115200);

    // Setup LED
    pinMode(CONFIG_BLUE_LIGHT_PIN, OUTPUT);
    digitalWrite(CONFIG_BLUE_LIGHT_PIN, LOW);

    // Setup MODULO ZIGBEE TLSR8258
    appPowerInit();
    msg_queue = xQueueCreate(10, sizeof(ts_HciMsg));
    // Power on the zigbee chip:
    //   appPowerOn(true);
    // Power off the zigbee chip:
    //   appPowerOn(false);
    //   zbhci_Deinit();
    appPowerOn(true);
    zbhci_Init(msg_queue);
    delay(100);
    xTaskCreatePinnedToCore(
        zbhciTask,
        "zbhciTask",
        4096,
        NULL,
        5,
        NULL,
        ARDUINO_RUNNING_CORE);
    delay(100);
    zbhci_NetworkStateReq();
    delay(100);
    zbhci_NodesJoinedGetReq(0);

    Serial.println(F("SETUP DONE!!!!"));
}

void loop()
{
}

void zbhciTask(void *pvParameters)
{
    ts_HciMsg sHciMsg;
     zbhci_MgmtPermitJoinReq(0xFFFC, 0xFF, 1); // CONECTION ENABLED

    while (1)
    {
        bzero(&sHciMsg, sizeof(sHciMsg));
        if (xQueueReceive(msg_queue, &sHciMsg, portMAX_DELAY))
        {
            switch (sHciMsg.u16MsgType)
            {
            case ZBHCI_CMD_BDB_COMMISSION_FORMATION_RSP:
                Serial.println(F("ZBHCI_CMD_BDB_COMMISSION_FORMATION_RSP"));
                zbhci_MgmtPermitJoinReq(0xFFFC, 0xFF, 1);
                break;

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

void appPowerInit()
{
    pinMode(0, OUTPUT);
}

void appPowerOn(bool active)
{
    if (active)
    {
        digitalWrite(0, HIGH);
    }
    else
    {
        digitalWrite(0, LOW);
    }
}

void appHandleZCLreportMsgRcv(ts_MsgZclReportMsgRcvPayload *payload)
{  
 
    printf("************* appHandleZCLreportMsgRcv ************\n");
    printf("u8SeqNum: %u\n", payload->u8SeqNum);
    printf("u16SrcAddr: %u\n", payload->u16SrcAddr);
    printf("u8SrcEp: %u\n", payload->u8SrcEp);
    printf("u16ClusterId: 0x%x\n", payload->u16ClusterId);
    printf("u8AttrNum: %u\n", payload->u8AttrNum);
    switch (payload->u16ClusterId)
    {
    case 0x0000: // Basic Cluster 
        for (size_t i = 0; i < payload->u8AttrNum; i++)
        {
            printf("---- u8AttrNum:%u ----\n", i);
            printf("u16AttrID: %u\n", payload->asAttrList[i].u16AttrID);   
            printf("u8DataType: %u\n", payload->asAttrList[i].u8DataType); 
            printf("u16DataLen: %u\n", payload->asAttrList[i].u16DataLen); 
            printf("uAttrData: %u\n", payload->asAttrList[i].uAttrData.u16AttrData);            
        }
        break;

    default:
        printf("appHandleZCLreportMsgRcv: default\n");
        break;
    }
}

