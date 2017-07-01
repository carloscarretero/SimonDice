# SimonDice
<p align="center">
  <img src="https://github.com/carloscarretero/SimonDice/blob/master/img/portada.PNG">
</p>

## Creación
 - KEIL uVision 4 IDE
 - Lenguaje C
 
## Proyecto
Programación en lenguaje C del juego Simon Dice en un microcontrolador LPC1114.

El esquema del microcontrolador con las interconexiones de las botoneras del juego es el siguiente.
<p align="center">
  <img src="https://github.com/carloscarretero/SimonDice/blob/master/img/scheme.PNG">
</p>

## Juego
Esta version del juego Mi Amigo Simon tiene 3 modos de juego diferentes.

### Modo de juego 1: Modo estandar
Este es el modo de juego mas conocido por todos. Se basa en repetir una secuencia de colores dictaminada
por el programa. El programa muestra una secuencia, se reproduce dicha secuencia, si se hace correctamente,
se a~nade un nuevo color a dicha secuencia y vuelta a empezar, si no, se acaba el juego. El numero de colores
que el jugador debe introducir correctamente en una secuencia para ganar depende del nivel escogido:
- Nivel 1: 4 colores.
- Nivel 2: 8 colores.
- Nivel 3: 12 colores.
- Nivel 4: 16 colores.
En este modo de juego, el jugador tiene un tiempo maximo de pulsacion que no debe superar cada vez que
tenga que pulsar cada color en la repeticion de la secuencia, si lo sobrepasa, acaba el juego cuando pulse el
boton de algun color. Durante el transcurso del juego, en la ultima secuencia de cada nivel, se veran reducidos
a la mitad, el tiempo de muestra de cada color, el tiempo entre muestras de cada color y el tiempo maximo
de pulsacion. Por ejemplo: Si hemos elegido jugar el nivel 2, cuando lleguemos a la secuencia de 4 colores (la
ultima del nivel 1), se producira esta reduccion de los tiempos. Cuando lleguemos a la secuencia de 8 colores
(la ultima del nivel 2), se producira una nueva reduccion de los tiempos.

### Modo de juego 2: Modo inverso
Este modo de juego es semejante al anterior, solo que con alguna variacion. La primera es que, ahora, el
jugador no tiene un tiempo lmite para introducir cada color de una secuencia. La segunda, y mas importante,
es que, ahora, el jugador debe introducir la secuencia dictaminada por el programa en orden inverso. El numero
de colores por secuencia es el mismo. En este modo de juego tambien se producen las reducciones de tiempo al
nal de cada nivel.

### Modo de juego 3: Modo aleatorio
En este modo de juego, el jugador debe esperar al final de la muestra de una secuencia para que el programa
le diga si debe introducir dicha secuencia en orden normal o inverso. Esta decision se realiza de manera aleatoria,
y se comunica al final de cada secuencia con:
- Orden normal: Pitido agudo y iluminacion de los colores de la derecha (rojo y azul).
- Orden inverso: Pitido grave y iluminacion de los colores de la derecha (verde y amarillo).
El jugador no tiene un tiempo maximo para introducir cada color de una secuencia. El numero de colores por
secuencia es el mismo. En este modo de juego tambien se producen las reducciones de tiempo al final de cada
nivel.
