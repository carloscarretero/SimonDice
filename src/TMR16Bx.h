#ifndef TMR16BX_H
#define TMR16BX_H

#include <LPC11xx.h>
#define PeripheralClock 50000000

/*
 *	Funcion que habilita la entrada de reloj de los timers TMR16Bx
 */
void TMR16Bx_inicializar(void);

/*
 *	Funcion que usa lanza el timer TMR16B0 para que pida
 * 	interrupcion en un tiempo en ms predeterminado
 */
void TMR16B0_lanzar_ms(int tiempo_ms);

/*
 * 	Funcion que para el TMR16B0 cuando llega al tiempo que
 * 	se le ha indicado previamente
 */
int TMR16B0_final_ms(void);

/*
 *	Funcion que lanza el TMR16B0 para que funcione como un cronometro que cuenta ms
 */
void TMR16B0_iniciar_conteo_ms(void);

/*
 *	Funcion que devuelve el numero de ms transcurridos desde que se lanzo
 *	al TMR16B0 como cronometro
 */
int TMR16B0_leer_conteo_ms(void);

/*
 *	Funcion que usa el timer TMR16B0 para esperar un tiempo en ms
 */
void TMR16B1_esperar_ms(int tiempo_ms);

/*
 *	Funcion que usa el timer TMR16B0 para esperar un tiempo en us
 */
void TMR16B1_esperar_us(int tiempo_us);

#endif
