/**************************************************************************//**
 *
 * @file     leds.c
 * @brief    Implementacion de funciones para el uso de los leds conectados al LPC114
 * @version  V1.00
 * @date     Febrero 2016
 *
 ******************************************************************************/

#include "leds.h"

/*
 *	Funcion que inicializa registros del LPC1114 para el uso de
 *	los leds de los botones
 */
void leds_inicializar(void)
{
		LPC_GPIO3->DIR |=  (1 << 3) | (1 << 2) | (1 << 1) | (1 << 0);
}

/*
 *	Funcion que enciende el led verde
 */
void leds_encender_verde(void)
{
		LPC_GPIO3->DATA &= 0xFFE;
}

/*
 *	Funcion que apaga el led verde
 */
void leds_apagar_verde(void)
{
		LPC_GPIO3->DATA |= (1 << 0); 
}

/*
 *	Funcion que enciende el led amarillo
 */
void leds_encender_amarillo(void)
{
		LPC_GPIO3->DATA &= 0xFFD;
}

/*
 *	Funcion que apaga el led amarillo
 */
void leds_apagar_amarillo(void)
{
		LPC_GPIO3->DATA |= (1 << 1);
}

/*
 *	Funcion que enciende el led rojo
 */
void leds_encender_rojo(void)
{
		LPC_GPIO3->DATA &= 0xFFB;
}

/*
 *	Funcion que apaga el led rojo
 */
void leds_apagar_rojo(void)
{
		LPC_GPIO3->DATA |= (1 << 2);
}

/*
 *	Funcion que enciende el led azul
 */
void leds_encender_azul(void)
{
		LPC_GPIO3->DATA &= 0xFF7; 
}

/*
 *	Funcion que apaga el led azul
 */
void leds_apagar_azul(void)
{
		LPC_GPIO3->DATA |= (1 << 3);
}

/*
 *	Funcion que enciende leds segun los parametros de entrada ledV, ledA, ledR, ledAz
 *		ledV 	- Verde
 *		ledA 	- Amarillo
 *		ledR 	- Rojo
 *		ledAz - Azul
 */
void leds_encender(int ledV, int ledA, int ledR, int ledAz)
{
		if(ledV == 1)
				leds_encender_verde();
		if(ledA == 1)
				leds_encender_amarillo();
		if(ledR == 1)
				leds_encender_rojo();
		if(ledAz == 1)
				leds_encender_azul();
}

/*
 *	Funcion que apaga leds segun los parametros de entrada ledV, ledA, ledR, ledAz
 *		ledV 	- Verde
 *		ledA 	- Amarillo
 *		ledR 	- Rojo
 *		ledAz - Azul
 */
void leds_apagar(int ledV, int ledA, int ledR, int ledAz)
{
		if(ledV == 1)
				leds_apagar_verde();
		if(ledA == 1)
				leds_apagar_amarillo();
		if(ledR == 1)
				leds_apagar_rojo();
		if(ledAz == 1)
				leds_apagar_azul();
}

/*
 *	Funcion que enciende un led segun el parametro de entrada color
 *		0 	- Verde
 *		1 	- Amarillo
 *		2		- Rojo
 *		3 	- Azul
 */
void leds_encender_color(int color)
{
		if(color == 0)
				leds_encender_verde();
		if(color == 1)
				leds_encender_amarillo();
		if(color == 2)
				leds_encender_rojo();
		if(color == 3)
				leds_encender_azul();
}

/*
 *	Funcion que enciende apaga un led segun el parametro de entrada color
 *		0 	- Verde
 *		1 	- Amarillo
 *		2		- Rojo
 *		3 	- Azul
 */
void leds_apagar_color(int color)
{
		if(color == 0)
				leds_apagar_verde();
		if(color == 1)
				leds_apagar_amarillo();
		if(color == 2)
				leds_apagar_rojo();
		if(color == 3)
				leds_apagar_azul();
}
