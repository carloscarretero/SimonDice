/**************************************************************************//**
 *
 * @file     juego.c
 * @brief    Implementacion de funciones para el juego de SIMON
 * @version  V1.00
 * @date     Febrero 2016
 *
 ******************************************************************************/



#include "juego.h"

/*
 *	Funcion que ejecuta una secuencia de colores y sonidos para indicar el inicio	del juego
 */
void inicio_juego(void)
{
		int i;
		
		for(i=0; i<3; ++i)
		{
				leds_encender(1,0,0,0);
				altavoz_color_ms(0,100);
				leds_apagar(1,0,0,0);
			
				leds_encender(0,1,0,0);
				altavoz_color_ms(1,100);
				leds_apagar(0,1,0,0);
			
				leds_encender(0,0,0,1);
				altavoz_color_ms(3,100);
				leds_apagar(0,0,0,1);
			
				leds_encender(0,0,1,0);
				altavoz_color_ms(2,100);
				leds_apagar(0,0,1,0);
		}
		
		for(i=0; i<2; ++i)
		{
				leds_encender(1,0,0,1);
				TMR16B1_esperar_ms(500);
				leds_apagar(1,0,0,1);
			
				leds_encender(0,1,1,0);
				TMR16B1_esperar_ms(500);
				leds_apagar(0,1,1,0);
		}
		
		leds_encender(1,0,1,0);
		TMR16B1_esperar_ms(500);
		leds_apagar(1,0,1,0);
		
		leds_encender(0,1,0,1);
		TMR16B1_esperar_ms(500);
		leds_apagar(0,1,0,1);
		
		leds_encender(1,1,0,0);
		TMR16B1_esperar_ms(500);
		leds_apagar(1,1,0,0);
		
		leds_encender(0,0,1,1);
		TMR16B1_esperar_ms(500);
		leds_apagar(0,0,1,1);
		
		
		leds_encender(1,1,1,1);
		altavoz_suena_ms(440,1000);
		leds_apagar(1,1,1,1);
	
}

/*
 *	Funcion que ejecuta una secuencia de colores y sonidos para indicar el exito del jugador
 *	en el juego
 */
void exito_juego(void)
{
		int i;
		for(i=0; i<4; i++)
		{
				leds_encender(1,0,0,0);
				altavoz_color_ms(0,100);
				leds_apagar(1,0,0,0);
			
				leds_encender(0,1,0,0);
				altavoz_color_ms(1,100);
				leds_apagar(0,1,0,0);
			
				leds_encender(0,0,0,1);
				altavoz_color_ms(3,100);
				leds_apagar(0,0,0,1);
			
				leds_encender(0,0,1,0);
				altavoz_color_ms(2,100);
				leds_apagar(0,0,1,0);
		}
}

/*
 *	Funcion que ejecuta una secuencia de colores y sonidos para indicar el fracaso del jugador
 *	en el juego
 */
void fracaso_juego(void)
{
		leds_encender(1,1,1,1);
		altavoz_suena_ms(200,1000);
		leds_apagar(1,1,1,1);
}


/*
 *	Juego 1: Modo básico de Simon. Repetir secuencia hasta un numero determinado
 * 	de colores. El jugador tiene tiempo para introducir cada color de la secuencia. 
 * 	Segun el nivel, varian:
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
void juego_1(int nivel, int* exito, int sr, int* ultimo, int* dim_ultimo, int* mas_larga, int* dim_mas_larga) 
{
		int i, turno, fallo, turno_jugador, boton_pulsado, 
			numero_turnos, tiempo_entre_colores_ms, tiempo_color_encendido_ms, tiempo_entre_turnos_ms,
			tiempo_limite, tiempo_de_pulsacion,
			colores[MAX_TURNOS]; 		// Declaramos el vector de colores a acertar
		
		turno = 1;
		fallo = 0;
		tiempo_entre_colores_ms = tiempo_color_encendido_ms = tiempo_entre_turnos_ms = 500;
		tiempo_limite = 10000;
		*dim_ultimo = 0;
		
		srand(sr);
		
		numero_turnos = nivel*4;
		
		// Bucle que hace el juego hasta que se gana o se pierde
		while(turno <= numero_turnos && fallo == 0)
		{
				colores[turno-1] = rand()%4; // Nuevo color
				for(i=0; i<turno; i++)	// Imprimimos la secuencia de colores
				{	
						TMR16B1_esperar_ms(tiempo_entre_colores_ms);
						leds_encender_color(colores[i]);
						altavoz_color_ms(colores[i],tiempo_color_encendido_ms);
						leds_apagar_color(colores[i]);
				}
				
				turno_jugador = 1;
				while(turno_jugador <= turno && fallo == 0)
				{	
						TMR16B0_iniciar_conteo_ms();
						boton_pulsado = botones_colores_esperar_pulsacion();
						altavoz_color_ms(boton_pulsado,100);
						tiempo_de_pulsacion = TMR16B0_leer_conteo_ms();
					
						if(boton_pulsado == colores[turno_jugador-1] && tiempo_de_pulsacion <= tiempo_limite)
								turno_jugador++;
						else
								fallo = 1;
						
						TMR16B1_esperar_ms(ANTIRREBOTES_MS); // Tiempo antirrebotes
				}
				
				if(fallo == 0)
				{
						//Actualiza ultimo y mas larga
						*dim_ultimo = turno;
						for(i=0; i<turno; ++i)
							ultimo[i] = colores[i];
							
						if(turno == *dim_mas_larga+1)
						{
								for(i=0; i<turno; ++i)
										mas_larga[i] = colores[i];
								*dim_mas_larga = turno;	
						}
						
						turno++;
						TMR16B1_esperar_ms(tiempo_entre_turnos_ms);
				}
				
				if(turno%4 == 0)
				{
						tiempo_entre_colores_ms = tiempo_color_encendido_ms = tiempo_entre_turnos_ms /= 2;
						tiempo_limite /= 2;
				}
		} // while
		
		if(fallo == 0)
			*exito = 1;
		else
			*exito = 0;
}


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
void juego_2(int nivel, int* exito, int sr, int* ultimo, int* dim_ultimo, int* mas_larga, int* dim_mas_larga)
{
		int i, turno, fallo, turno_jugador, boton_pulsado, 
			numero_turnos, tiempo_entre_colores_ms, tiempo_color_encendido_ms, tiempo_entre_turnos_ms,
			colores[MAX_TURNOS]; 		// Declaramos el vector de colores a acertar
		
		turno = 1;
		fallo = 0;
		*dim_ultimo = 0;
		srand(sr);
		
		tiempo_entre_colores_ms = tiempo_color_encendido_ms = tiempo_entre_turnos_ms = 500;
		
		numero_turnos = nivel*4;
		
		// Bucle que hace el juego hasta que se gana o se pierde
		while(turno <= numero_turnos && fallo == 0)
		{
				colores[turno-1] = rand()%4; // Nuevo color
				for(i=0; i<turno; i++)	// Imprimimos la secuencia de colores
				{	
						TMR16B1_esperar_ms(tiempo_entre_colores_ms);
						leds_encender_color(colores[i]);
						altavoz_color_ms(colores[i],tiempo_color_encendido_ms);
						leds_apagar_color(colores[i]);
				}
				
				turno_jugador = turno-1;
				while(turno_jugador >= 0 && fallo == 0)
				{	
						boton_pulsado = botones_colores_esperar_pulsacion();
						altavoz_color_ms(boton_pulsado,100);
					
						if(boton_pulsado == colores[turno_jugador])
								turno_jugador--;
						else
								fallo = 1;
						
						TMR16B1_esperar_ms(ANTIRREBOTES_MS); // Tiempo antirrebotes
				}
				
				if(fallo == 0)
				{
						//Actualiza ultimo y mas larga
						*dim_ultimo = turno;
						for(i=0; i<turno; ++i)
							ultimo[i] = colores[i];
							
						if(turno == *dim_mas_larga+1)
						{
								for(i=0; i<turno; ++i)
										mas_larga[i] = colores[i];
								*dim_mas_larga = turno;	
						}
						
						turno++;
						TMR16B1_esperar_ms(tiempo_entre_turnos_ms);
				}
				
				if(turno%4 == 0)
						tiempo_entre_colores_ms = tiempo_color_encendido_ms = tiempo_entre_turnos_ms /= 2;
					
		}
		
		if(fallo == 0)
			*exito = 1;
		else
			*exito = 0;
}


/*
 *	Juego 3: Modo aleatorio de Simon. Repetir secuencia hasta un numero determinado
 * 	de colores en dicha secuencia. En cada turno, se determina de forma aleatoria si
 * 	el jugador ha de introducir la secuencia en orden normal o inverso. Se le indicara
 *	al final de la muestra de la secuencia con:
 *			Orden normal: Pitido agudo y iluminación de los colores de la derecha (rojo y azul).
 *      Orden inverso: Pitido grave y iluminación de los colores de la derecha (verde y amarillo).
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
void juego_3(int nivel, int* exito, int sr, int* ultimo, int* dim_ultimo, int* mas_larga, int* dim_mas_larga)
{
		int i, turno, fallo, turno_jugador, boton_pulsado, sentido,
			numero_turnos, tiempo_entre_colores_ms, tiempo_color_encendido_ms, tiempo_entre_turnos_ms,
			colores[MAX_TURNOS];  		// Declaramos el vector de colores a acertar
		
		turno = 1;
		fallo = 0;
		*dim_ultimo = 0;
		srand(sr);
		
		tiempo_entre_colores_ms = tiempo_color_encendido_ms = tiempo_entre_turnos_ms = 500;
		
		numero_turnos = nivel*4;
		
		// Bucle que hace el juego hasta que se gana o se pierde
		while(turno <= numero_turnos && fallo == 0)
		{
				colores[turno-1] = rand()%4; // Nuevo color
				for(i=0; i<turno; i++)	// Imprimimos la secuencia de colores
				{	
						TMR16B1_esperar_ms(tiempo_entre_colores_ms);
						leds_encender_color(colores[i]);
						altavoz_color_ms(colores[i],tiempo_color_encendido_ms);
						leds_apagar_color(colores[i]);
				}
				
				sentido = rand()%2;
				
				
				if(sentido == 0)
				{ 	// Sentido directo
						TMR16B1_esperar_ms(200);
						leds_encender(0,0,1,1);
						altavoz_suena_ms(440,200);
						leds_apagar(0,0,1,1);
						turno_jugador = 1;
						while(turno_jugador <= turno && fallo == 0)
						{	
								boton_pulsado = botones_colores_esperar_pulsacion();
								altavoz_color_ms(boton_pulsado,100);
							
								if(boton_pulsado == colores[turno_jugador-1])
										turno_jugador++;
								else
										fallo = 1;
							
								TMR16B1_esperar_ms(ANTIRREBOTES_MS); // Tiempo antirrebotes
						}
				}
				else
				{		// Sentido inverso
						TMR16B1_esperar_ms(200);
						leds_encender(1,1,0,0);
						altavoz_suena_ms(200,200);
						leds_apagar(1,1,0,0);
						turno_jugador = turno-1;
						while(turno_jugador >= 0 && fallo == 0)
						{	
								boton_pulsado = botones_colores_esperar_pulsacion();
								altavoz_color_ms(boton_pulsado,100);
							
								if(boton_pulsado == colores[turno_jugador])
										turno_jugador--;
								else
										fallo = 1;
								
								TMR16B1_esperar_ms(ANTIRREBOTES_MS); // Tiempo antirrebotes
						}
				}
				
				if(fallo == 0)
				{
						//Actualiza ultimo y mas larga
						*dim_ultimo = turno;
						for(i=0; i<turno; ++i)
							ultimo[i] = colores[i];
							
						if(turno == *dim_mas_larga+1)
						{
								for(i=0; i<turno; ++i)
										mas_larga[i] = colores[i];
								*dim_mas_larga = turno;	
						}
						
						turno++;
						TMR16B1_esperar_ms(tiempo_entre_turnos_ms);
				}
				
				if(turno%4 == 0)
						tiempo_entre_colores_ms = tiempo_color_encendido_ms = tiempo_entre_turnos_ms /= 2;
				
		} // while
		
		if(fallo == 0)
			*exito = 1;
		else
			*exito = 0;
}


