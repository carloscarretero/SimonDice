
#include "TMR16Bx.h"

#define PeripheralClock 50000000

/*
 *	Funcion que habilita la entrada de reloj de los timers TMR16Bx
 */
void TMR16Bx_inicializar(void)
{
		LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 7) | (1 << 8); // Habilita el reloj de los timers TMR16B0 y TMR16B1
}

/*
 *	Funcion que usa lanza el timer TMR16B0 para que pida
 * 	interrupcion en un tiempo en ms predeterminado
 */
void TMR16B0_lanzar_ms(int tiempo_ms)
{
		LPC_TMR16B0->TCR 	= 0;		// Paramos timer
		LPC_TMR16B0->PC		= 0;		// Contador de preescala a 0
		LPC_TMR16B0->TC 	= 0; 		// Contador principal a 0
		LPC_TMR16B0->PR 	= PeripheralClock/10000 - 1; // TC+1 cada 0.1 ms
		LPC_TMR16B0->MR0	= 10*tiempo_ms - 1;		// PR y MR0 coinciden cada ms
		LPC_TMR16B0->MCR 	= 1; 		// Activar la puesta a 1 del bit de petición  de interrupción cuando coincidan los
															// registros TC y MR0. 
		LPC_TMR16B0->IR 	= 1;  	// Asegurar que el bit de petición de interrupción está a 0 antes de poner en marcha el timer. 
		LPC_TMR16B0->TCR 	= 1; 		// Poner en marcha el timer.
}

/*
 * 	Funcion que para el TMR16B0 cuando llega al tiempo que
 * 	se le ha indicado previamente
 */
int TMR16B0_final_ms(void)
{
		if((LPC_TMR16B0->IR & 1) == 1)	// 	Preguntamos si hemos llegado al final del tiempo
		{
				LPC_TMR16B0->TCR = 0;		// Paramos el timer
				return 1;
		}
		else
				return 0;
}

/*
 *	Funcion que lanza el TMR16B0 para que funcione como un cronometro que cuenta ms
 */
void TMR16B0_iniciar_conteo_ms(void)
{
    LPC_TMR16B0->TCR 	= 0; 			// Parar timer
		LPC_TMR16B0->PC 	= 0;			// Contador de preescala a 0
		LPC_TMR16B0->TC 	= 0;			// Timer a 0
		LPC_TMR16B0->PR 	= PeripheralClock/1000 - 1; // TC se incrementa cada 1 ms
		LPC_TMR16B0->MCR 	= 0;			// No hay comportamiento ciclico
		LPC_TMR16B0->TCR 	= 1;			// Iniciar timer
}

/*
 *	Funcion que devuelve el numero de ms transcurridos desde que se lanzo
 *	al TMR16B0 como cronometro
 */
int TMR16B0_leer_conteo_ms(void)
{
    return LPC_TMR16B0->TC;		// Leer numero de ms transcurridos
}


/*
 *	Funcion que usa el timer TMR16B0 para esperar un tiempo en ms
 */
void TMR16B1_esperar_ms(int tiempo_ms)
{
		LPC_TMR16B1->TCR 	= 0;		// Paramos timer
		LPC_TMR16B1->PC		= 0;		// Contador de preescala a 0
		LPC_TMR16B1->TC 	= 0; 		// Contador principal a 0
		LPC_TMR16B1->PR 	= PeripheralClock/10000 - 1; // TC+1 cada 0.1 ms
		LPC_TMR16B1->MR0	= 10*tiempo_ms - 1;		// PR y MR0 coinciden cada ms
		LPC_TMR16B1->MCR 	= 1; 		// Activar la puesta a 1 del bit de petición  de interrupción cuando coincidan los
															// registros TC y MR0. 
		LPC_TMR16B1->IR 	= 1;  	// Asegurar que el bit de petición de interrupción está a 0 antes de poner en marcha el timer. 
		LPC_TMR16B1->TCR 	= 1; 		// Poner en marcha el timer.
		while((LPC_TMR16B1->IR & 1) == 0){} // Esperamos mientras no haya peticion de interrupcion
}

/*
 *	Funcion que usa el timer TMR16B0 para esperar un tiempo en us
 */
void TMR16B1_esperar_us(int tiempo_us)
{
		LPC_TMR16B1->TCR 	= 0;		// Paramos timer
		LPC_TMR16B1->PC		= 0;		// Contador de preescala a 0
		LPC_TMR16B1->TC 	= 0; 		// Contador principal a 0
		LPC_TMR16B1->PR 	= PeripheralClock/10000000 - 1; // TC+1 cada 0,1 us
		LPC_TMR16B1->MR0	= 10*tiempo_us - 1;		// PR y MR0 coinciden cada ms
		LPC_TMR16B1->MCR 	= 1; 		// Activar la puesta a 1 del bit de petición  de interrupción cuando coincidan los
															// registros TC y MR0. 
		LPC_TMR16B1->IR 	= 1;  	// Asegurar que el bit de petición de interrupción está a 0 antes de poner en marcha el timer. 
		LPC_TMR16B1->TCR 	= 1; 		// Poner en marcha el timer.
		while((LPC_TMR16B1->IR & 1) == 0){} // Esperamos mientras no haya peticion de interrupcion
}
