#include "sensores.h"

/*
██████╗  █████╗ ███████╗████████╗██╗██╗     ██╗     ███████╗██████╗  ██████╗
██╔══██╗██╔══██╗██╔════╝╚══██╔══╝██║██║     ██║     ██╔════╝██╔══██╗██╔═══██╗
██████╔╝███████║███████╗   ██║   ██║██║     ██║     █████╗  ██████╔╝██║   ██║
██╔═══╝ ██╔══██║╚════██║   ██║   ██║██║     ██║     ██╔══╝  ██╔══██╗██║   ██║
██║     ██║  ██║███████║   ██║   ██║███████╗███████╗███████╗██║  ██║╚██████╔╝
╚═╝     ╚═╝  ╚═╝╚══════╝   ╚═╝   ╚═╝╚══════╝╚══════╝╚══════╝╚═╝  ╚═╝ ╚═════╝

*/
#include <Arduino.h>
#include <Ultrasonic.h>
#define HCSR04_ECHO_PIN 5
#define HCSR04_TRIGGER_PIN 4
Ultrasonic ultrasonic(HCSR04_TRIGGER_PIN, HCSR04_ECHO_PIN);

void sensor_nivel_de_pastillero_init()
{
}
uint16_t sensor_nivel_de_pastillero_leer()
{
    return (uint16_t)ultrasonic.read();
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