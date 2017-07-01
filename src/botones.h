/**************************************************************************//**
 *
 * @file     botones.h
 * @brief    Cabecera de funciones para el uso de los botones conectados al LPC114
 * @version  V1.00
 * @date     Febrero 2016
 *
 ******************************************************************************/



#ifndef BOTONES_H
#define BOTONES_H

#include <LPC11xx.h>
#include "leds.h"
#include "altavoz.h"
#include "TMR16Bx.h"

#define T_PROPAGACION_MS 5

/*
 * Funcion que pone los registros GPIO2_3-6 como entrada
 * para su uso en las distintas funciones de botones
 */
void botones_inicializar(void);


/*
 * Funcion comprueba si se ha pulsado el boton de Marcha,
 * devolviendo el nivel elegido en el momento de la pulsacion o
 * 0 si no se ha pulsado el boton Marcha
 */
int botones_juego_leer_pulsacion(void);


/*
 * Funcion que lee el juego elegido en el switch de JUEGO 
 */
int botones_nivel_leer_pulsacion(void);

/*
 *	Funcion que comprueba si se ha pulsado el boton Ultimo
 */
int botones_ultimo_leer_pulsacion(void);

/*
 *	Funcion que comprueba si se ha pulsado el boton Mas Larga
 */
int botones_mas_larga_leer_pulsacion(void);


/*
 * Funcion que espera a que algun boton sea pulsado, y cuando esto ocurre, devuelve
 * el numero de color que ha sido pulsado:
 *	0 - Verde
 * 	1 - Amarrillo
 * 	2 - Rojo
 * 	3 - Azul
 * Mientras se este pulsando un boton, se encendera el led correspondiente y sonara
 * su nota asignada.
 */
int botones_colores_esperar_pulsacion(void);

#endif


