#include "sensores.h"

/*
███████╗███████╗███╗   ██╗███████╗ ██████╗ ██████╗      ██████╗ █████╗ ██╗██████╗  █████╗ ███████╗
██╔════╝██╔════╝████╗  ██║██╔════╝██╔═══██╗██╔══██╗    ██╔════╝██╔══██╗██║██╔══██╗██╔══██╗██╔════╝
███████╗█████╗  ██╔██╗ ██║███████╗██║   ██║██████╔╝    ██║     ███████║██║██║  ██║███████║███████╗
╚════██║██╔══╝  ██║╚██╗██║╚════██║██║   ██║██╔══██╗    ██║     ██╔══██║██║██║  ██║██╔══██║╚════██║
███████║███████╗██║ ╚████║███████║╚██████╔╝██║  ██║    ╚██████╗██║  ██║██║██████╔╝██║  ██║███████║
╚══════╝╚══════╝╚═╝  ╚═══╝╚══════╝ ╚═════╝ ╚═╝  ╚═╝     ╚═════╝╚═╝  ╚═╝╚═╝╚═════╝ ╚═╝  ╚═╝╚══════╝
*/

// CABECERA PARA ADXL345 (CAIDAS)
#define ADXL345_IN1_PIN 5
#define I2C_SCL_PIN 7
#define I2C_SDA_PIN 6
#include <Arduino.h>
#include "Wire.h"
#include <SparkFun_ADXL345.h>
ADXL345 adxl = ADXL345();
bool adxl_event_flag = false;

// FUNCIONES PARA ADXL345(CAIDAS)
void IRAM_ATTR ADXL_ISR()
{
    adxl_event_flag = true;
}

void sensor_caidas_init()
{
    // SETUP PARA ADXL345 (CAIDAS)
    Wire.setPins(I2C_SDA_PIN, I2C_SCL_PIN);
    adxl.powerOn();           // Power on the ADXL345
    adxl.setRangeSetting(16); // Give the range settings
                              // Accepted values are 2g, 4g, 8g or 16g
                              // Higher Values = Wider Measurement Range
                              // Lower Values = Greater Sensitivity

    adxl.InactivityINT(0);
    adxl.ActivityINT(0);
    adxl.FreeFallINT(0);
    adxl.doubleTapINT(0);
    adxl.singleTapINT(0);

    adxl.setActivityXYZ(1, 1, 1);  // Set to activate movement detection in the axes "adxl.setActivityXYZ(X, Y, Z);" (1 == ON, 0 == OFF)
    adxl.setActivityThreshold(75); // 62.5mg per increment   // Set activity   // Inactivity thresholds (0-255)

    adxl.setInactivityXYZ(1, 1, 1);  // Set to detect inactivity in all the axes "adxl.setInactivityXYZ(X, Y, Z);" (1 == ON, 0 == OFF)
    adxl.setInactivityThreshold(75); // 62.5mg per increment   // Set inactivity // Inactivity thresholds (0-255)
    adxl.setTimeInactivity(10);      // How many seconds of no activity is inactive?

    adxl.setTapDetectionOnXYZ(1, 1, 1); // Detect taps in the directions turned ON "adxl.setTapDetectionOnX(X, Y, Z);" (1 == ON, 0 == OFF)

    // Set values for what is considered a TAP and what is a DOUBLE TAP (0-255)
    adxl.setTapThreshold(50);     // 62.5 mg per increment
    adxl.setTapDuration(15);      // 625 μs per increment
    adxl.setDoubleTapLatency(80); // 1.25 ms per increment
    adxl.setDoubleTapWindow(200); // 1.25 ms per increment
    // Set values for what is considered FREE FALL (0-255)
    adxl.setFreeFallThreshold(7);                     // (5 - 9) recommended - 62.5mg per increment
    adxl.setFreeFallDuration(30);                     // (20 - 70) recommended - 5ms per increment
    adxl.setImportantInterruptMapping(1, 2, 2, 2, 2); // Sets "adxl.setEveryInterruptMapping(single tap, double tap, free fall, activity, inactivity);"
                                                      // Accepts only 1 or 2 values for pins INT1 and INT2. This chooses the pin on the ADXL345 to use for Interrupts.
                                                      // This library may have a problem using INT2 pin. Default to INT1 pin.
    adxl.singleTapINT(1);                             // Turn on Interrupts for each mode (1 == ON, 0 == OFF)

    pinMode(ADXL345_IN1_PIN, INPUT);
    attachInterrupt(ADXL345_IN1_PIN, ADXL_ISR, RISING);
}
bool sensor_caidas_activado()
{
    volatile byte interrupts = adxl.getInterruptSource();
    return adxl_event_flag;
}
void sensor_caidas_reset()
{
    adxl_event_flag = false;
}

/*
██████╗  ██████╗ ████████╗ ██████╗ ███╗   ██╗    ██████╗ ███████╗    ██╗   ██╗███████╗██╗   ██╗ █████╗ ██████╗ ██╗ ██████╗
██╔══██╗██╔═══██╗╚══██╔══╝██╔═══██╗████╗  ██║    ██╔══██╗██╔════╝    ██║   ██║██╔════╝██║   ██║██╔══██╗██╔══██╗██║██╔═══██╗
██████╔╝██║   ██║   ██║   ██║   ██║██╔██╗ ██║    ██║  ██║█████╗      ██║   ██║███████╗██║   ██║███████║██████╔╝██║██║   ██║
██╔══██╗██║   ██║   ██║   ██║   ██║██║╚██╗██║    ██║  ██║██╔══╝      ██║   ██║╚════██║██║   ██║██╔══██║██╔══██╗██║██║   ██║
██████╔╝╚██████╔╝   ██║   ╚██████╔╝██║ ╚████║    ██████╔╝███████╗    ╚██████╔╝███████║╚██████╔╝██║  ██║██║  ██║██║╚██████╔╝
╚═════╝  ╚═════╝    ╚═╝    ╚═════╝ ╚═╝  ╚═══╝    ╚═════╝ ╚══════╝     ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝ ╚═════╝

*/

#include <Arduino.h>

#define USER_BUTTON_PIN 2
bool boton_event_flag = false;
void IRAM_ATTR BOTON_ISR()
{
    boton_event_flag = true;
}

void sensor_boton_de_usuario_init()
{
    pinMode(USER_BUTTON_PIN, INPUT);
    attachInterrupt(USER_BUTTON_PIN, BOTON_ISR, RISING);
}
bool sensor_boton_de_usuario_presionado()
{
    return boton_event_flag;
}
void sensor_boton_de_usuario_reset()
{
    boton_event_flag = false;
}

/*
████████╗██╗███████╗███╗   ███╗██████╗  ██████╗
╚══██╔══╝██║██╔════╝████╗ ████║██╔══██╗██╔═══██╗
   ██║   ██║█████╗  ██╔████╔██║██████╔╝██║   ██║
   ██║   ██║██╔══╝  ██║╚██╔╝██║██╔═══╝ ██║   ██║
   ██║   ██║███████╗██║ ╚═╝ ██║██║     ╚██████╔╝
   ╚═╝   ╚═╝╚══════╝╚═╝     ╚═╝╚═╝      ╚═════╝

*/

#define SEGUNDO_MS (1000)
#define MINUTO_MS (SEGUNDO_MS * 60)
#define PERIODO_MS (5 * MINUTO_MS)
int prev;

void periodo_init()
{
    prev = millis();
}
bool periodo_expirado()
{
    bool periodo_cumplido = ((millis() - prev) > PERIODO_MS) ? true : false;
    return periodo_cumplido;
}
void periodo_reset()
{
    prev = millis();
}

/*
████████╗███████╗███╗   ███╗██████╗ ███████╗██████╗  █████╗ ████████╗██╗   ██╗██████╗  █████╗      ██████╗ ██████╗ ██████╗ ██████╗  ██████╗ ██████╗  █████╗ ██╗
╚══██╔══╝██╔════╝████╗ ████║██╔══██╗██╔════╝██╔══██╗██╔══██╗╚══██╔══╝██║   ██║██╔══██╗██╔══██╗    ██╔════╝██╔═══██╗██╔══██╗██╔══██╗██╔═══██╗██╔══██╗██╔══██╗██║
   ██║   █████╗  ██╔████╔██║██████╔╝█████╗  ██████╔╝███████║   ██║   ██║   ██║██████╔╝███████║    ██║     ██║   ██║██████╔╝██████╔╝██║   ██║██████╔╝███████║██║
   ██║   ██╔══╝  ██║╚██╔╝██║██╔═══╝ ██╔══╝  ██╔══██╗██╔══██║   ██║   ██║   ██║██╔══██╗██╔══██║    ██║     ██║   ██║██╔══██╗██╔═══╝ ██║   ██║██╔══██╗██╔══██║██║
   ██║   ███████╗██║ ╚═╝ ██║██║     ███████╗██║  ██║██║  ██║   ██║   ╚██████╔╝██║  ██║██║  ██║    ╚██████╗╚██████╔╝██║  ██║██║     ╚██████╔╝██║  ██║██║  ██║███████╗
   ╚═╝   ╚══════╝╚═╝     ╚═╝╚═╝     ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝     ╚═════╝ ╚═════╝ ╚═╝  ╚═╝╚═╝      ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝

*/
// CABECERAS PARA LM35 (TEMPERATURA CORPORAL)
#include <driver/adc.h>
#include "esp_adc_cal.h"
#define LM35_PIN 4
#define ADC_VREF_mV 3300.0
#define ADC_RESOLUTION 4096.0
#define DEFAULT_VREF 1100

static esp_adc_cal_characteristics_t *adc_chars;

void sensor_temperatura_corporal_init()
{
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_11);

    adc_chars = (esp_adc_cal_characteristics_t *)calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, DEFAULT_VREF, adc_chars);
}
float sensor_temperatura_corporal_leer()
{
    adc_power_acquire();
    uint32_t raw = 0;
    for (int i = 0; i < 50; i++)
    {
        raw += (uint32_t)adc1_get_raw(ADC1_CHANNEL_4);
    }
    raw = raw / 50.0;

    uint32_t mv = esp_adc_cal_raw_to_voltage(raw, adc_chars);
    float temp_celsius = mv / 10.0;

    adc_power_release();
    return temp_celsius*23.0/35.1;
}

/*
██████╗ ██╗████████╗███╗   ███╗ ██████╗      ██████╗ █████╗ ██████╗ ██████╗ ██╗ █████╗  ██████╗ ██████╗
██╔══██╗██║╚══██╔══╝████╗ ████║██╔═══██╗    ██╔════╝██╔══██╗██╔══██╗██╔══██╗██║██╔══██╗██╔════╝██╔═══██╗
██████╔╝██║   ██║   ██╔████╔██║██║   ██║    ██║     ███████║██████╔╝██║  ██║██║███████║██║     ██║   ██║
██╔══██╗██║   ██║   ██║╚██╔╝██║██║   ██║    ██║     ██╔══██║██╔══██╗██║  ██║██║██╔══██║██║     ██║   ██║
██║  ██║██║   ██║   ██║ ╚═╝ ██║╚██████╔╝    ╚██████╗██║  ██║██║  ██║██████╔╝██║██║  ██║╚██████╗╚██████╔╝
╚═╝  ╚═╝╚═╝   ╚═╝   ╚═╝     ╚═╝ ╚═════╝      ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═════╝ ╚═╝╚═╝  ╚═╝ ╚═════╝ ╚═════╝

 ██████╗ ██████╗ ███╗   ██╗ ██████╗███████╗███╗   ██╗████████╗██████╗  █████╗  ██████╗██╗ ██████╗ ███╗   ██╗    ███████╗██████╗  ██████╗ ██████╗
██╔════╝██╔═══██╗████╗  ██║██╔════╝██╔════╝████╗  ██║╚══██╔══╝██╔══██╗██╔══██╗██╔════╝██║██╔═══██╗████╗  ██║    ██╔════╝██╔══██╗██╔═══██╗╚════██╗
██║     ██║   ██║██╔██╗ ██║██║     █████╗  ██╔██╗ ██║   ██║   ██████╔╝███████║██║     ██║██║   ██║██╔██╗ ██║    ███████╗██████╔╝██║   ██║ █████╔╝
██║     ██║   ██║██║╚██╗██║██║     ██╔══╝  ██║╚██╗██║   ██║   ██╔══██╗██╔══██║██║     ██║██║   ██║██║╚██╗██║    ╚════██║██╔═══╝ ██║   ██║██╔═══╝
╚██████╗╚██████╔╝██║ ╚████║╚██████╗███████╗██║ ╚████║   ██║   ██║  ██║██║  ██║╚██████╗██║╚██████╔╝██║ ╚████║    ███████║██║     ╚██████╔╝███████╗
 ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝╚══════╝╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝ ╚═════╝ ╚═╝  ╚═══╝    ╚══════╝╚═╝      ╚═════╝ ╚══════╝

*/
#include <Wire.h>
#include "MAX30105.h"
#include "spo2_algorithm.h"
MAX30105 particleSensor;
uint32_t irBuffer[100];  // infrared LED sensor data
uint32_t redBuffer[100]; // red LED sensor data
int32_t bufferLength;    // data length
int32_t spo2;            // SPO2 value
int8_t validSPO2;        // indicator to show if the SPO2 calculation is valid
int32_t heartRate;       // heart rate value
int8_t validHeartRate;   // indicator to show if the heart rate calculation is valid
TaskHandle_t led_task_handle = NULL;

void sensor_ritmo_cardiaco_y_concentracion_spo2_init()
{
    if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) // Use default I2C port, 400kHz speed
    {
        Serial.println(F("MAX30105 was not found. Please check wiring/power."));
        while (1)
            ;
    }

    byte ledBrightness = 60;                                                                       // Options: 0=Off to 255=50mA
    byte sampleAverage = 4;                                                                        // Options: 1, 2, 4, 8, 16, 32
    byte ledMode = 2;                                                                              // Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
    byte sampleRate = 100;                                                                         // Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
    int pulseWidth = 411;                                                                          // Options: 69, 118, 215, 411
    int adcRange = 16384;//4096;                                                                           // Options: 2048, 4096, 8192, 16384
    particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); // Configure sensor with these settings
}
static void _max30102_leer(bool *resultado, uint16_t *ritmo_cardiaco, uint16_t *concentracion_spo2)
{
    memset(irBuffer, 0, 100);
    memset(redBuffer, 0, 100);

    bufferLength = 100; // buffer length of 100 stores 4 seconds of samples running at 25sps

    // read the first 100 samples, and determine the signal range
    for (int i = 0; i < bufferLength; i++)
    {

        while (particleSensor.available() == false) // do we have new data?
            particleSensor.check();                 // Check the sensor for new data

        uint32_t redval = particleSensor.getRed();
        uint32_t irval = particleSensor.getIR();

        if (redval < 10000 || irval < 10000)
        {
            i--;
            continue;
        }

        redBuffer[i] = redval;
        irBuffer[i] = irval;
        particleSensor.nextSample(); // We're finished with this sample so move to next sample

/*
        Serial.print(F("red="));
        Serial.print(redBuffer[i], DEC);
        Serial.print(F(", ir="));
        Serial.println(irBuffer[i], DEC);
*/
    }

    // Continuously taking samples from MAX30102.  Heart rate and SpO2 are calculated every 1 second

    // dumping the first 25 sets of samples in the memory and shift the last 75 sets of samples to the top
    for (byte i = 25; i < 100; i++)
    {
        redBuffer[i - 25] = redBuffer[i];
        irBuffer[i - 25] = irBuffer[i];
    }

    // take 25 sets of samples before calculating the heart rate.
    for (byte i = 75; i < 100; i++)
    {
        while (particleSensor.available() == false) // do we have new data?
            particleSensor.check();                 // Check the sensor for new data

        uint32_t redval = particleSensor.getRed();
        uint32_t irval = particleSensor.getIR();

        if (redval < 10000 || irval < 10000)
        {
            i--;
            continue;
        }

        redBuffer[i] = redval;
        irBuffer[i] = irval;
        particleSensor.nextSample(); // We're finished with this sample so move to next sample
    }

    // After gathering 25 new samples recalculate HR and SP02
    maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);

    *ritmo_cardiaco = (uint16_t)heartRate*0.4;// ajuste
    *concentracion_spo2 = (uint16_t)spo2;

    if (validHeartRate != 1 || validSPO2 != 1)
    {
        Serial.println(F("Resultado invalido. Repetir proceso."));
        *resultado = false;
    }
    else
    {
        *resultado = true;
    }
}
void led_blink_fast(void *pvParameters)
{
    while (1)
    {
        digitalWrite(3, true);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        digitalWrite(3, false);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
void sensor_ritmo_cardiaco_y_concentracion_spo2_leer(uint16_t *ritmo_cardiaco, uint16_t *spo2)
{
    bool resultado_valido = false;

    while (1)
    {
        // INICIAR PARPADEO DE LED AZUL
        xTaskCreatePinnedToCore(led_blink_fast, "led_blink_fast", 4096, NULL, 5, &led_task_handle, ARDUINO_RUNNING_CORE);
        delay(5000);

        // LEER SENSOR MAX30102
        _max30102_leer(&resultado_valido, ritmo_cardiaco, spo2);

        // DETENER PARPADEO DE LED AZUL
        vTaskDelete(led_task_handle);
        digitalWrite(3, false);
        delay(1000);

        // VALIDAR RESULTADO
        if (resultado_valido)
            break;
    }
}
