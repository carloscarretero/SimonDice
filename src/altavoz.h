/**************************************************************************//**
 *
 * @file     altavoz.h
 * @brief    Cabecera de funciones para el uso del altavoz conectado al LPC114
 * @version  V1.00
 * @date     Febrero 2016
 *
 ******************************************************************************/

#ifndef ALTAVOZ_H
#define ALTAVOZ_H

#include <LPC11xx.h>

#include "TMR16Bx.h"

#define NOTA_AZUL 			415
#define NOTA_AMARILLO 	200
#define NOTA_ROJO 			252
#define NOTA_VERDE			209


/*
 * 	Funcion que inicializa los registros de memoria y timers para usar el altavoz
 * 	Vamos a utilizar la funcion CR32B0_MAT0 del pin PIO1_6 para que active al altavoz,
 *	Dejando la CPU libre para realizar otras tareas
 */
void altavoz_inicializar(void);


/*
 * 	Funcion que utiliza el TMR32B0 para lanzar un sonido de frecuencia frec_nota_HZ durante
 *	un tiempo indefinido
 */
void altavoz_lanzar_sonido(float frec_nota_Hz);


/*
 * 	Funcion que detiene el sonido lanzado por altavoz_lanzar_sonido(frec_nota_HZ)
 */
void altavoz_parar_sonido(void);


/*
 * 	Funcion que hace sonar una nota durante un tiempo en ms usando dos timers:
 *		- TMR16B1 para la duracion del sonido
 *		- TMR32B0 para el sonido
 */
void altavoz_suena_ms(float frec_nota_MHz, int tiempo_ms);


/*
 * 	Funcion que hace sonar una nota durante un tiempo en ms
 * 	Esa nota cambia dependiendo del valor del parametro color
 *		0 	- Nota asociada al Verde
 *		1 	- Nota asociada al Amarillo
 *		2		- Nota asociada al Rojo
 *		3 	- Nota asociada al Azul
 */
void altavoz_color_ms(int color, int tiempo_ms);


#endif

