/**************************************************************************//**
 *
 * @file     juego.h
 * @brief    Cabecera de funciones para el juego de SIMON
 * @version  V1.00
 * @date     Febrero 2016
 *
 ******************************************************************************/
 


#ifndef JUEGO_H
#define JUEGO_H

#include <stdlib.h>
#include <stdint.h>

#include "leds.h"
#include "botones.h"
#include "altavoz.h"
#include "TMR16Bx.h"

#define MAX_TURNOS 16
#define ANTIRREBOTES_MS 300

/*
 *	Funcion que ejecuta una secuencia de colores y sonidos para indicar el inicio	del juego
 */
void inicio_juego(void);


/*
 *	Funcion que ejecuta una secuencia de colores y sonidos para indicar el exito del jugador
 *	en el juego
 */
void exito_juego(void);


/*
 *	Funcion que ejecuta una secuencia de colores y sonidos para indicar el fracaso del jugador
 *	en el juego
 */
void fracaso_juego(void);


/*
 *	Juego 1: Modo básico de Simon. Repetir secuencia hasta un numero determinado
 * 	de colores en dicha secuencia. Segun el nivel, varian:
 *		- Numero de turnos/colores en secuencia
 *		-	Tiempo de encendido de cada color en la muestra de la secuencia
 *		- Tiempo entre el encendido de cada color en la muestra de la secuencia
 *		- Tiempo entre que el usuario realiza la secuencia correctamente y comienza una nueva
 *	La funcion devuelve si el jugador ha tenido exito o no en *exito.
 *	La variable sr es la semilla para generar numeros pseudoaleatorios
 */
void juego_1(int nivel, int* exito, int sr, int* ultimo, int* dim_ultimo, int* mas_larga, int* dim_mas_larga);
		
														 
/*
 *	Juego 2: Modo Simon Inverso. El jugador debera repetir la secuencia de colores a la inversa.
 *	El jugador no tiene limite de tiempo para la repeticion de la secuencia. Segun el nivel, varian:
 *		- Numero de turnos/colores en secuencia
 *				- Nivel 1: 4 turnos
 *        -	Nivel 2: 8 turnos
 *				-	Nivel 3: 12 turnos
 *				- Nivel 4: 16 turnos
 * 	Cada 4 turnos, se reduce a la mitad el tiempo que se muestran los colores, el 
 * 	el tiempo entre la muestra de colores
 *	La funcion devuelve si el jugador ha tenido exito o no en *exito.
 *	La variable sr es la semilla para generar numeros pseudoaleatorios								 
 */
void juego_2(int nivel, int* exito, int sr, int* ultimo, int* dim_ultimo, int* mas_larga, int* dim_mas_larga);


/*
 *	Juego 3: Modo aleatorio de Simon. Repetir secuencia hasta un numero determinado
 * 	de colores en dicha secuencia. En cada turno, se determina de forma aleatoria si
 * 	el jugador ha de introducir la secuencia en orden normal o inverso. Se le indicara
 *	con un tono al final de la muestra de la secuencia:
 *		- Agudo: Introducir en orden normal
 *		- Grave: Introducir en orden inverso
 *	Segun el nivel, varia:
 *		- Numero de turnos/colores en secuencia
 *				- Nivel 1: 4 turnos
 *        -	Nivel 2: 8 turnos
 *				-	Nivel 3: 12 turnos
 *				- Nivel 4: 16 turnos
 * 	Cada 4 turnos, se reduce a la mitad el tiempo que se muestran los colores, el 
 * 	el tiempo entre la muestra de colores y el tiempo limite para pulsar colores
 *	La funcion devuelve si el jugador ha tenido exito o no en *exito.
 *	La variable sr es la semilla para generar numeros pseudoaleatorios
 */
void juego_3(int nivel, int* exito, int sr, int* ultimo, int* dim_ultimo, int* mas_larga, int* dim_mas_larga);

											 
#endif
														 
						
														 