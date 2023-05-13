Platformio core : 6.1.7
Platformio home : 3.4.3
Espressif 32 core : 6.1.0

* Modificar libreria de adxl345 (ver img)
* Esquemas en folder img. El gateway es la tarjeta TZigbee solamente.
* Repositorio base: https://github.com/Xinyuan-LilyGO/T-ZigBee
* Manual para programar esp32c3 y TLSR8258 de la tarjeta TZigbee: https://zbhci.readthedocs.io/en/latest/user-guide/burning.html
    Usar siempre el adaptador T-2UT

* PARA PROGRAMAR EL TRANSMISOR "PASTILLERO" (LO MISMO APLICA PARA TODOS LOS MODULOS)
    - Usar "TlsrComSwireWritter" para grabar el firmware "hciDevice..." en TLSR8258. Guia: https://zbhci.readthedocs.io/en/latest/user-guide/burning.html
    - En platformio, seleccionar "pastillero" acorde a "img/11.PNG". Compilar y flashear. Guia: https://zbhci.readthedocs.io/en/latest/user-guide/burning.html


