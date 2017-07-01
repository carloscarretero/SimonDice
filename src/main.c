/**************************************************************************//**
 *
 * @file     main.c
 * @brief    Funcion main para simular el juego Simon
 * @version  V1.00
 * @date     Febrero 2016
 *
 ******************************************************************************/

#include <LPC11xx.h>

#include "leds.h"
#include "botones.h"
#include "altavoz.h"
#include "juego.h"
#include "TMR16Bx.h"

int main(void)
{
		int juego=0, nivel=0, exito=0, sr=0, i,
		ultimo[MAX_TURNOS], mas_larga[MAX_TURNOS],
		dim_ultimo=0, dim_mas_larga=0;
		
		altavoz_inicializar();
		leds_inicializar();
		botones_inicializar();
		TMR16Bx_inicializar();
		
		inicio_juego();
		
		TMR16B0_iniciar_conteo_ms();
		while(1)
		{	
				
				nivel = botones_nivel_leer_pulsacion();
			
				if(nivel != 0)
				{
						sr = TMR16B0_leer_conteo_ms();
						juego = botones_juego_leer_pulsacion();
					
						if(juego == 1)
								juego_1(nivel,&exito,sr,ultimo,&dim_ultimo,mas_larga,&dim_mas_larga); 
						
						else if(juego == 2)
								juego_2(nivel,&exito,sr,ultimo,&dim_ultimo,mas_larga,&dim_mas_larga);
					
						else if(juego == 3)
								juego_3(nivel,&exito,sr,ultimo,&dim_ultimo,mas_larga,&dim_mas_larga);
						
							
						if(exito)
								exito_juego();
						else
								fracaso_juego();
						
						TMR16B0_iniciar_conteo_ms();
				}
				else
				{
						if(botones_mas_larga_leer_pulsacion() != 0)
								for(i=0; i<dim_mas_larga; ++i)
								{
									leds_encender_color(mas_larga[i]);
									altavoz_color_ms(mas_larga[i],400);
									leds_apagar_color(mas_larga[i]);
									TMR16B1_esperar_ms(400);
								}
	
						if(botones_ultimo_leer_pulsacion() != 0)
								for(i=0; i<dim_ultimo; ++i)
								{
									leds_encender_color(ultimo[i]);
									altavoz_color_ms(ultimo[i],400);
									leds_apagar_color(ultimo[i]);
									TMR16B1_esperar_ms(400);
								}
			
				}
				
		}
				
}

