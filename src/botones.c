/**************************************************************************//**
 *
 * @file     botones.c
 * @brief    Implementacion de funciones para el uso de los botones conectados al LPC114
 * @version  V1.00
 * @date     Febrero 2016
 *
 ******************************************************************************/

#include "botones.h"


/*
 * Funcion que pone los registros GPIO2_3-6 como entrada
 * para su uso en las distintas funciones de botones
 */
void botones_inicializar(void)
{
		LPC_GPIO2->DIR &= 0xF87;  		// GPIO2_3-6 	-> Entrada
}


/*
 * Funcion comprueba si se ha pulsado el boton de Marcha,
 * devolviendo el nivel elegido en el momento de la pulsacion o
 * 0 si no se ha pulsado el boton Marcha
 */
int botones_nivel_leer_pulsacion(void)
{
		int nivel = 0;
	
		LPC_GPIO2->DIR &= ~( (1 << 2)|(1 << 0) ); 	// GPIO2_2 y GPIO2_0 -> Entrada
		LPC_GPIO2->DIR |= (1 << 1); 	// GPIO2_1 		-> Salida
		LPC_GPIO2->DATA &= 0xFFD; 		// GPIO2_1 		= 0
	
		TMR16B1_esperar_ms(T_PROPAGACION_MS);
	
		// Cuando alguno se pulse, comprobamos cual es
		if( (LPC_GPIO2->DATA & (1 << 3)) == 0 )
				// Se ha pulsado con nivel = 1
				nivel = 1;
		else if((LPC_GPIO2->DATA & (1 << 4)) == 0)
				// Se ha pulsado con nivel = 2
				nivel = 2;
		else if((LPC_GPIO2->DATA & (1 << 5)) == 0)
				// Se ha pulsado con nivel = 3
				nivel = 3;
		else if((LPC_GPIO2->DATA & (1 << 6)) == 0)
				// Se ha pulsado con nivel = 4
				nivel = 4;
		
		return nivel;
}


/*
 * Funcion que lee el juego elegido en el switch de JUEGO 
 */
int botones_juego_leer_pulsacion(void)
{
		int juego;
	
		LPC_GPIO2->DIR &= ~( (1 << 1)|(1 << 0) ); 	// GPIO2_1 y GPIO2_0 -> Entrada
		LPC_GPIO2->DIR |= (1 << 2); 	// GPIO2_2 		-> Salida
		LPC_GPIO2->DATA &= 0xFFB; 		// GPIO2_2 		= 0
	
		TMR16B1_esperar_ms(T_PROPAGACION_MS);
			
		// Cuando alguno se pulse, comprobamos cual es
		if( (LPC_GPIO2->DATA & (1 << 3)) == 0 )
				// Se ha pulsado con nivel = 2
				juego = 2;
		else if((LPC_GPIO2->DATA & (1 << 5)) == 0)
				// Se ha pulsado con nivel = 3
				juego = 3;
		else 
				juego = 1;
		
		return juego;
}


/*
 *	Funcion que comprueba si se ha pulsado el boton Ultimo
 */
int botones_ultimo_leer_pulsacion(void)
{
		LPC_GPIO2->DIR &= ~( (1 << 1)|(1 << 0) ); 	// GPIO2_1 y GPIO2_0 -> Entrada
		LPC_GPIO2->DIR |= (1 << 2); 	// GPIO2_2 		-> Salida
		LPC_GPIO2->DATA &= 0xFFB; 		// GPIO2_2 		= 0
		
		TMR16B1_esperar_ms(T_PROPAGACION_MS);
	
		if( (LPC_GPIO2->DATA & (1 << 6)) == 0 )
				{
				// Se ha pulsado el boton
				TMR16B1_esperar_ms(100);
				if( (LPC_GPIO2->DATA & (1 << 6)) == 0 )
					return 1;
				else
					return 0;
		}
		else
				return 0;
		
}


/*
 *	Funcion que comprueba si se ha pulsado el boton Mas Larga
 */
int botones_mas_larga_leer_pulsacion(void)
{
		LPC_GPIO2->DIR &= ~( (1 << 1)|(1 << 0) ); 	// GPIO2_1 y GPIO2_0 -> Entrada
		LPC_GPIO2->DIR |= (1 << 2); 	// GPIO2_2 		-> Salida
		LPC_GPIO2->DATA &= 0xFFB; 		// GPIO2_2 		= 0
	
		TMR16B1_esperar_ms(T_PROPAGACION_MS);
	
		if( (LPC_GPIO2->DATA & (1 << 4)) == 0 )
		{
				// Se ha pulsado el boton
				TMR16B1_esperar_ms(100);
				if( (LPC_GPIO2->DATA & (1 << 4)) == 0 )
					return 1;
				else
					return 0;
		}
		else
				return 0;
}


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
int botones_colores_esperar_pulsacion(void)
{
	
		int boton_color;
		
		LPC_GPIO2->DIR &= ~( (1 << 2)|(1 << 1) ); 	// GPIO2_2 y GPIO2_1 -> Entrada
		LPC_GPIO2->DIR |= (1 << 0); 	// GPIO2_0 		-> Salida
		LPC_GPIO2->DATA &= 0xFFE; 		// GPIO2_0 		= 0
		
	
		TMR16B1_esperar_ms(T_PROPAGACION_MS);
			
		// Esperamos pulsacion de algun boton
		while( ((LPC_GPIO2->DATA & (1 << 3)) == 1 << 3) &&  // Mientras no se pulse verde
					 ((LPC_GPIO2->DATA & (1 << 4)) == 1 << 4) &&  // Ni se pulse amarillo
					 ((LPC_GPIO2->DATA & (1 << 5)) == 1 << 5) && 	// Ni se pulse rojo
					 ((LPC_GPIO2->DATA & (1 << 6)) == 1 << 6))		// Ni se pulse azul
		{}
			
		// Cuando alguno se pulse, comprobamos cual es
		if( (LPC_GPIO2->DATA & (1 << 3)) == 0 )
		{
				// Se ha pulsado el verde
				leds_encender_verde();
				altavoz_lanzar_sonido(NOTA_VERDE);
				while((LPC_GPIO2->DATA & (1 << 3)) == 0) {}
				altavoz_parar_sonido();
				leds_apagar_verde();
				boton_color = 0;
		}
		else if((LPC_GPIO2->DATA & (1 << 4)) == 0)
		{
				// Se ha pulsado el amarillo
				leds_encender_amarillo();
				altavoz_lanzar_sonido(NOTA_AMARILLO);
				while((LPC_GPIO2->DATA & (1 << 4)) == 0) {}
				altavoz_parar_sonido();
				leds_apagar_amarillo();
				boton_color = 1;
		}
		else if((LPC_GPIO2->DATA & (1 << 5)) == 0)
		{
				// Se ha pulsado el rojo
				leds_encender_rojo();
				altavoz_lanzar_sonido(NOTA_ROJO);
				while((LPC_GPIO2->DATA & (1 << 5)) == 0) {}
				altavoz_parar_sonido();
				leds_apagar_rojo();
				boton_color = 2;
		}
		else if((LPC_GPIO2->DATA & (1 << 6)) == 0)
		{
				// Se ha pulsado el azul
				leds_encender_azul();
				altavoz_lanzar_sonido(NOTA_AZUL);
				while((LPC_GPIO2->DATA & (1 << 6)) == 0) {}
				altavoz_parar_sonido();
				leds_apagar_azul();
				boton_color = 3;
		}
		
		return boton_color;
}

