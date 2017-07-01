/**************************************************************************//**
 *
 * @file     altavoz.c
 * @brief    Implementación de funciones para el uso del altavoz conectado al LPC114
 * @version  V1.00
 * @date     Febrero 2016
 *
 ******************************************************************************/


#include "altavoz.h"

/*
 * 	Funcion que inicializa los registros de memoria y timers para usar el altavoz
 * 	Vamos a utilizar la funcion CR32B0_MAT0 del pin PIO1_6 para que active al altavoz,
 *	Dejando la CPU libre para realizar otras tareas
 */
void altavoz_inicializar(void)
{
		LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 16);		// Habilita reloj para configuracion IOCON
		LPC_IOCON->PIO1_6 |= 0x02;								// PIO1_6 -> CT32B_MAT0
		LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 9); 		// Habilita el reloj de los timers TMR32B0.
		LPC_TMR32B0->EMR |= (3 << 4);							// Acción 3: Cada vez que TMR32B0->TC = TM32B0->MR0, 
																							// CR32B0_MAT0 cambia su valor (0->1, 1->0)
}

/*
 * 	Funcion que utiliza el TMR32B0 para lanzar un sonido con periodo en us "periodo_us"
 * 	Se hace uso de CR32B0_MAT0 del pin PI01_6 para dejar libre a la cpu mientras se actua sobre
 *	el altavoz. Mientras no se pare, el timer se reinicia cada vez que TC Y MR0 coinciden, para
 *	conseguir un sonido continuado hasta que se le de la orden al timer de parar con otra funcion
 */
void TMR32B0_lanzar_sonido(int periodo_us)
{
		LPC_TMR32B0->TCR 	= 0;		// Paramos timer
		LPC_TMR32B0->PC		= 0;		// Contador de preescala a 0
		LPC_TMR32B0->TC 	= 0; 		// Contador principal a 0
		LPC_TMR32B0->PR 	= PeripheralClock/10000000 - 1; // TC+1 cada 0,1 us
		LPC_TMR32B0->MR0	= 10*periodo_us - 1;						// PR y MR0 coinciden cada 1 us
		LPC_TMR32B0->MCR 	= (1 << 1); // TC = MR0 -> TC = 0
		LPC_TMR32B0->TCR 	= 1; 				// Poner en marcha el timer.
}

/*
 * 	Funcion que detiene el TMR32B0 para detener el sonido que este sonando en ese momento.
 *	Si no hay ningun sonido, no tiene ningun efecto
 */
void TMR32B0_parar_sonido(void)
{
		LPC_TMR32B0->TCR = 0; // Paramos el timer
}

/*
 * 	Funcion que utiliza el TMR32B0 para lanzar un sonido de frecuencia frec_nota_HZ durante
 *	un tiempo indefinido
 */
void altavoz_lanzar_sonido(float frec_nota_Hz)
{
		int T;
		T = 1000.0f/frec_nota_Hz;
		TMR32B0_lanzar_sonido((int)(1000.0f*T)/2.0f);
}

/*
 * 	Funcion que detiene el sonido lanzado por altavoz_lanzar_sonido(frec_nota_HZ)
 */
void altavoz_parar_sonido(void)
{
		TMR32B0_parar_sonido();
}

/*
 * 	Funcion que hace sonar una nota durante un tiempo en ms usando dos timers:
 *		- TMR16B1 para la duracion del sonido
 *		- TMR32B0 para el sonido
 */
void altavoz_suena_ms(float frec_nota_Hz, int tiempo_ms)
{
		altavoz_lanzar_sonido(frec_nota_Hz);
	
		TMR16B1_esperar_ms(tiempo_ms);
	
		altavoz_parar_sonido();
}

/*
 * 	Funcion que hace sonar una nota durante un tiempo en ms
 * 	Esa nota cambia dependiendo del valor del parametro color
 *		0 	- Nota asociada al Verde
 *		1 	- Nota asociada al Amarillo
 *		2		- Nota asociada al Rojo
 *		3 	- Nota asociada al Azul
 */
void altavoz_color_ms(int color, int tiempo_ms)
{
		if(color == 0)
			altavoz_suena_ms(NOTA_VERDE,tiempo_ms);
		else if(color == 1)
			altavoz_suena_ms(NOTA_AMARILLO,tiempo_ms);
		else if(color == 2)
			altavoz_suena_ms(NOTA_ROJO,tiempo_ms);
		else if(color == 3)
			altavoz_suena_ms(NOTA_AZUL,tiempo_ms);
}

