#pragma once

#include <Arduino.h>

/*
███████╗███████╗███╗   ██╗███████╗ ██████╗ ██████╗      ██████╗ █████╗ ██╗██████╗  █████╗ ███████╗
██╔════╝██╔════╝████╗  ██║██╔════╝██╔═══██╗██╔══██╗    ██╔════╝██╔══██╗██║██╔══██╗██╔══██╗██╔════╝
███████╗█████╗  ██╔██╗ ██║███████╗██║   ██║██████╔╝    ██║     ███████║██║██║  ██║███████║███████╗
╚════██║██╔══╝  ██║╚██╗██║╚════██║██║   ██║██╔══██╗    ██║     ██╔══██║██║██║  ██║██╔══██║╚════██║
███████║███████╗██║ ╚████║███████║╚██████╔╝██║  ██║    ╚██████╗██║  ██║██║██████╔╝██║  ██║███████║
╚══════╝╚══════╝╚═╝  ╚═══╝╚══════╝ ╚═════╝ ╚═╝  ╚═╝     ╚═════╝╚═╝  ╚═╝╚═╝╚═════╝ ╚═╝  ╚═╝╚══════╝
*/

void sensor_caidas_init();
bool sensor_caidas_activado();
void sensor_caidas_reset();

/*
██████╗  ██████╗ ████████╗ ██████╗ ███╗   ██╗    ██████╗ ███████╗    ██╗   ██╗███████╗██╗   ██╗ █████╗ ██████╗ ██╗ ██████╗
██╔══██╗██╔═══██╗╚══██╔══╝██╔═══██╗████╗  ██║    ██╔══██╗██╔════╝    ██║   ██║██╔════╝██║   ██║██╔══██╗██╔══██╗██║██╔═══██╗
██████╔╝██║   ██║   ██║   ██║   ██║██╔██╗ ██║    ██║  ██║█████╗      ██║   ██║███████╗██║   ██║███████║██████╔╝██║██║   ██║
██╔══██╗██║   ██║   ██║   ██║   ██║██║╚██╗██║    ██║  ██║██╔══╝      ██║   ██║╚════██║██║   ██║██╔══██║██╔══██╗██║██║   ██║
██████╔╝╚██████╔╝   ██║   ╚██████╔╝██║ ╚████║    ██████╔╝███████╗    ╚██████╔╝███████║╚██████╔╝██║  ██║██║  ██║██║╚██████╔╝
╚═════╝  ╚═════╝    ╚═╝    ╚═════╝ ╚═╝  ╚═══╝    ╚═════╝ ╚══════╝     ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝ ╚═════╝

*/
void sensor_boton_de_usuario_init();
bool sensor_boton_de_usuario_presionado();
void sensor_boton_de_usuario_reset();

/*
████████╗██╗███████╗███╗   ███╗██████╗  ██████╗
╚══██╔══╝██║██╔════╝████╗ ████║██╔══██╗██╔═══██╗
   ██║   ██║█████╗  ██╔████╔██║██████╔╝██║   ██║
   ██║   ██║██╔══╝  ██║╚██╔╝██║██╔═══╝ ██║   ██║
   ██║   ██║███████╗██║ ╚═╝ ██║██║     ╚██████╔╝
   ╚═╝   ╚═╝╚══════╝╚═╝     ╚═╝╚═╝      ╚═════╝

*/
void periodo_init();
bool periodo_expirado();
void periodo_reset();

/*
████████╗███████╗███╗   ███╗██████╗ ███████╗██████╗  █████╗ ████████╗██╗   ██╗██████╗  █████╗      ██████╗ ██████╗ ██████╗ ██████╗  ██████╗ ██████╗  █████╗ ██╗
╚══██╔══╝██╔════╝████╗ ████║██╔══██╗██╔════╝██╔══██╗██╔══██╗╚══██╔══╝██║   ██║██╔══██╗██╔══██╗    ██╔════╝██╔═══██╗██╔══██╗██╔══██╗██╔═══██╗██╔══██╗██╔══██╗██║
   ██║   █████╗  ██╔████╔██║██████╔╝█████╗  ██████╔╝███████║   ██║   ██║   ██║██████╔╝███████║    ██║     ██║   ██║██████╔╝██████╔╝██║   ██║██████╔╝███████║██║
   ██║   ██╔══╝  ██║╚██╔╝██║██╔═══╝ ██╔══╝  ██╔══██╗██╔══██║   ██║   ██║   ██║██╔══██╗██╔══██║    ██║     ██║   ██║██╔══██╗██╔═══╝ ██║   ██║██╔══██╗██╔══██║██║
   ██║   ███████╗██║ ╚═╝ ██║██║     ███████╗██║  ██║██║  ██║   ██║   ╚██████╔╝██║  ██║██║  ██║    ╚██████╗╚██████╔╝██║  ██║██║     ╚██████╔╝██║  ██║██║  ██║███████╗
   ╚═╝   ╚══════╝╚═╝     ╚═╝╚═╝     ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝     ╚═════╝ ╚═════╝ ╚═╝  ╚═╝╚═╝      ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝

*/

void sensor_temperatura_corporal_init();
float sensor_temperatura_corporal_leer();

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

void sensor_ritmo_cardiaco_y_concentracion_spo2_init();
void sensor_ritmo_cardiaco_y_concentracion_spo2_leer(uint16_t *ritmo_cardiaco, uint16_t *spo2);