/**************************************************************************//**
 *
 * @file     leds.h
 * @brief    Cabecera de funciones para el uso de los leds conectados al LPC114
 * @version  V1.00
 * @date     Febrero 2016
 *
 ******************************************************************************/


#ifndef LEDS_H
#define LEDS_H

#include <LPC11xx.h>

/*
 *	Funcion que inicializa registros del LPC1114 para el uso de
 *	los leds de los botones
 */
void leds_inicializar(void);


/*
 *	Funcion que enciende el led verde
 */
void leds_encender_verde(void);


/*
 *	Funcion que apaga el led verde
 */
void leds_apagar_verde(void);


/*
 *	Funcion que enciende el led amarillo
 */
void leds_encender_amarillo(void);


/*
 *	Funcion que apaga el led amarillo
 */
void leds_apagar_amarillo(void);


/*
 *	Funcion que enciende el led rojo
 */
void leds_encender_rojo(void);


/*
 *	Funcion que apaga el led rojo
 */
void leds_apagar_rojo(void);


/*
 *	Funcion que enciende el led azul
 */
void leds_encender_azul(void);


/*
 *	Funcion que apaga el led azul
 */
void leds_apagar_azul(void);


/*
 *	Funcion que enciende leds segun los parametros de entrada ledV, ledA, ledR, ledAz
 *		ledV 	- Verde
 *		ledA 	- Amarillo
 *		ledR 	- Rojo
 *		ledAz - Azul
 */
void leds_encender(int ledV, int ledA, int ledR, int ledAz);


/*
 *	Funcion que apaga leds segun los parametros de entrada ledV, ledA, ledR, ledAz
 *		ledV 	- Verde
 *		ledA 	- Amarillo
 *		ledR 	- Rojo
 *		ledAz - Azul
 */
void leds_apagar(int ledV, int ledA, int ledR, int ledAz);


/*
 *	Funcion que enciende un led segun el parametro de entrada color
 *		0 	- Verde
 *		1 	- Amarillo
 *		2		- Rojo
 *		3 	- Azul
 */
void leds_encender_color(int color);


/*
 *	Funcion que enciende apaga un led segun el parametro de entrada color
 *		0 	- Verde
 *		1 	- Amarillo
 *		2		- Rojo
 *		3 	- Azul
 */
void leds_apagar_color(int color);


#endif

