/**
*  Robado de: https://gist.github.com/MatheusFaria/4cbb8b6dbe33fd5605cf8b8f7130ba6d
*  Textos creados con:
* 
* The ASCII arts were extracted from:
*  - http://www.fiikus.net/?pokedex
*  - http://www.world-of-nintendo.com/pictures/text/
* And also generated with:
*  - http://www.text-image.com
*/

#ifndef __ASCII_POKEMON_H__
#define __ASCII_POKEMON_H__

#include <stdio.h>
#include <string.h>

#define MAX_NOMBRE 100
#define RESET "\033[0m"
#define ROJO "\033[0m\033[31m"
#define ROJO_CLARO "\033[1m\033[31m"
#define FONDO_ROJO "\033[0m\033[41m"
#define VERDE "\033[0m\033[32m"
#define VERDE_OSCURO "\033[1m\033[32m"
#define FONDO_VERDE "\033[0m\033[42m"
#define NARANJA "\033[0m\033[33m"
#define AMARILLO "\033[1m\033[33m"
#define FONDO_AMARILLO "\033[0m\033[43m"
#define AZUL "\033[0m\033[34m"
#define AZUL_OSCURO "\033[1m\033[34m"
#define FONDO_AZUL "\033[0m\033[44m"
#define MAGENTA "\033[0m\033[35m"
#define FONDO_MAGENTA "\033[0m\033[45m"
#define CELESTE "\033[0m\033[36m"
#define CELESTE_OSCURO "\033[1m\033[36m"
#define PLATEADO "\033[0m\033[36m"
#define BLANCO "\033[1m\033[37m"

//Pre: Recibe el nombre de la especie
//Post: Imprime la mayoria de los pokemon de agua y un par facheros de los primero 151 
void mostrar_pokemon_ascii(char nombre_pokemon[MAX_NOMBRE]);

#endif /*ASCII_POKEMON_H*/