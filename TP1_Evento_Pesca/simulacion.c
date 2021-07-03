#include "evento_pesca.h"
#include "ascii_pokemon.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define ARCHIVO_ACUARIO "acuario.txt"
#define ARCHIVO_ARRECIFE "arrecife.txt"
#define MAGIKARP_PESO_GORDO 15
#define VELOCIDAD_PROMEDIO_CAMINATA 5
#define POKEMON_PESADO 100
#define POKEMON_VELOCIDAD_ALTA 50
#define MAX_FUNCIONES_SELECCION 7
#define MAX_FUNCIONES_MOSTRAR 5
#define MAX_POKEDOLARES 10000000
#define ANIO_MINIMO 1950
#define VARIACION_ANIO 70
#define MAX_DIAS_MES 31
#define MAX_MESES 12
#define MIN_POKE_ID 300000000
#define VAR_POKE_ID 200000000

// Devuelve true si el makigarp pesa mas de 15kg
bool magikarp_gordo(pokemon_t* pokemon){
    return ((strcmp(pokemon->color,"magikarp")||strcmp(pokemon->color,"Magikarp"))&& (pokemon->peso > MAGIKARP_PESO_GORDO));
}

//Devuelve true si es un magikarp dorado
bool magikarp_shiny(pokemon_t* pokemon){
    return ((strcmp(pokemon->color,"magikarp")||strcmp(pokemon->color,"Magikarp"))&& (strcmp(pokemon->color,"dorado")));
}

//Devuelve siempre TRUE
bool psicopata(pokemon_t* pokemon){
    return true;
}

//Devuelve true si el pokemon pesa mas que POKEMON_PESADO(100kg)
bool tene_cuidado_en_un_puente(pokemon_t* pokemon){
    return (pokemon->peso > POKEMON_PESADO);
}

//Devuelve true si el pokemon es mas lento o igual la velocidad promedio de na persona caminando(5KM/h)
bool lo_pasas_caminando(pokemon_t* pokemon){
    return (pokemon->velocidad <= VELOCIDAD_PROMEDIO_CAMINATA);
}

//Devuelve true si el pokemon es mas rapido que POKEMON_VELOCIDAD_ALTA(60KM/h)
bool tene_cuidado_con_la_bici(pokemon_t* pokemon){
    return (pokemon->velocidad > POKEMON_VELOCIDAD_ALTA);
}

//Devuelve true si el nombre del poquemon empieza con p o P
bool empieza_con_p(pokemon_t* pokemon){
    return ((pokemon->especie[0] == 'P')||(pokemon->especie[0] == 'p'));
}


void mostrar_pokemon_lista(pokemon_t* pokemon){
    printf("\t# Nombre: %16s # Peso %7i kg # Velocidad: %7i km/h # Color: %12s #\n",pokemon->especie,pokemon->peso,pokemon->velocidad,pokemon->color);
}

void mostrar_tarjeta(pokemon_t* pokemon){
    printf("╔════════════════════════╗\n");
    printf("║%*s%*s║\n",(int)(12+strlen(pokemon->especie)/2),pokemon->especie,(int)(12-strlen(pokemon->especie)/2)," ");
    printf("╠═══════════╦════════════╣\n");
    printf("║ Peso      ║ %8i kg║\n",pokemon->peso);
    printf("║ Velocidad ║ %6i km/h║\n",pokemon->velocidad);
    printf("║ Color     ║ %11s║\n",pokemon->color);
    printf("╚═══════════╩════════════╝\n\n");
}

void dibujar_pokemon_favoritos(pokemon_t* pokemon){
    mostrar_pokemon_ascii(pokemon->especie);
}

void poke_documento(pokemon_t* pokemon){
    int anio = (rand()%VARIACION_ANIO)+ANIO_MINIMO;
    int mes = (rand()%MAX_MESES)+1;
    int dia = (rand()%MAX_DIAS_MES)+1;

    printf("┌────────────────────────────────────────┐\n");
    printf("│ ┌──────────┐                           │\n");
    printf("│ │##########│ Especie:                  │\n");
    printf("│ │"ROJO_CLARO"CLASSIFIED"RESET"│    %-22s │\n",pokemon->especie);
    printf("│ │##########│ Color:          Peso:     │\n");
    printf("│ │"ROJO_CLARO"CLASSIFIED"RESET"│   %-12s    %-7i │\n",pokemon->color,pokemon->peso);
    printf("│ │##########│ Fecha de nacimiento:      │\n");
    printf("│ └──────────┘     %2i/%2i/%4i            │\n",dia,mes,anio);
    printf("│   Poke-ID: %-27i │\n", (rand()%VAR_POKE_ID)+MIN_POKE_ID);
    printf("└────────────────────────────────────────┘\n\n");
}

void poke_date(pokemon_t* pokemon){
    printf(FONDO_ROJO"Hola soy: %s"RESET"\n"RESET,pokemon->especie);
    printf("Peso %ikg y puedo correr a %ikm/h\n",pokemon->peso,pokemon->velocidad);
    printf("Mi hermoso color es %s\n",pokemon->color);
    printf("Gano %i pokedolares al mes\n",rand()%MAX_POKEDOLARES);
    printf(RESET"\n");
}

int main(){
    int i=0;
    srand((unsigned int)time(NULL));
    arrecife_t* arrecife = crear_arrecife(ARCHIVO_ARRECIFE);
    acuario_t* acuario = crear_acuario();

    bool (*seleccionar_pokemon[MAX_FUNCIONES_SELECCION])(pokemon_t*) = {magikarp_gordo,magikarp_shiny,psicopata,tene_cuidado_en_un_puente,lo_pasas_caminando,tene_cuidado_con_la_bici,empieza_con_p};
    void (*mostrar_pokemon[MAX_FUNCIONES_MOSTRAR])(pokemon_t*) = {poke_date,poke_documento,dibujar_pokemon_favoritos,mostrar_tarjeta,mostrar_pokemon_lista};


    while((i<MAX_FUNCIONES_SELECCION)&&(acuario != NULL)&&(arrecife != NULL)){
        int cantidad_selec = (rand()%5)+1;
        trasladar_pokemon(arrecife,acuario,seleccionar_pokemon[i], cantidad_selec);
        censar_arrecife(arrecife,mostrar_pokemon[rand()%MAX_FUNCIONES_MOSTRAR]);
        printf(FONDO_AZUL"\n\tPresione ENTER para continuar"RESET);
        printf("\n");
        getchar();
        system("clear");
        i++;
    }

    guardar_datos_acuario(acuario,ARCHIVO_ACUARIO);

    liberar_acuario(acuario);
    liberar_arrecife(arrecife);

    return 0;
}