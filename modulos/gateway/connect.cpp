
#include "connect.h"
#include "WiFi.h"
#include "esp_wifi.h"
#include <HTTPClient.h>

#define USER_BLUE_LED_PIN 3
#define led_on() digitalWrite(USER_BLUE_LED_PIN, 1)
#define led_off() digitalWrite(USER_BLUE_LED_PIN, 0)
#define led_toogle() digitalWrite(USER_BLUE_LED_PIN, (digitalRead(USER_BLUE_LED_PIN) + 1) % 2)

const char *ssid = "SIETECOLORES";
const char *password = "QWE&ASD%ZXC#!!";
const char *serverName = "http://api.monitoreo.lat";

void connect_wifi()
{
    // SETUP LED AZUL
    pinMode(USER_BLUE_LED_PIN, OUTPUT);
    digitalWrite(USER_BLUE_LED_PIN, LOW);

    // SETUP WIFI
    WiFi.begin(ssid, password);
    Serial.println("Connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
        led_toogle();
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());

    // INICIAR PARPADEO DE LED AZUL
    for (int i = 0; i < 20; i++)
    {
        led_toogle();
        delay(100);
    }
    led_off();
}
void connect_server(char *json, const char *path)
{
    if (WiFi.status() == WL_CONNECTED)
    {
        WiFiClient client;
        HTTPClient http;

        char url[100] = {0};
        sprintf(url, "%s%s", serverName, path);

        // Your Domain name with URL path or IP address with path
        http.begin(client, url);

        // Specify content-type header
        http.addHeader("Content-Type", "application/json");

        // Send HTTP POST request
        int httpResponseCode = http.POST(json);

        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);

        // Free resources
        http.end();

        if (httpResponseCode == 200 || httpResponseCode == 201)
        {
            Serial.println(F("Good httpResponseCode"));
            for (int i = 0; i < 10; i++)
            {
                led_toogle();
                delay(100);
            }
            led_off();
        }
        else
        {
            Serial.println(F("Bad httpResponseCode"));
            led_on();
            delay(2000);
            led_off();
        }
    }
    else
    {
        Serial.println(F("WiFi Disconnected"));
        led_on();
        delay(2000);
        led_off();
    }
}