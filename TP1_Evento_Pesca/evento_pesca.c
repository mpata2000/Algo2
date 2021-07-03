#include "evento_pesca.h"
#include <stdlib.h>

#define FORMATO_LECTURA "%20[^;];%i;%i;%20[^\n]\n"
#define FORMATO_ESCRITURA "%s;%i;%i;%s\n"
#define ERROR -1
#define FUNCIONO 0


//Pre: Recive un puntero pokemon_t valido y un size_t a la cantidad que se quiere achicar pokemon_t.
//Post: Si se pudo agrandar pokemon_t* devuelve el nuevo puntero, sino se libera el puntero recivido y devuelve NULL.
pokemon_t* agrandar_pokemon(pokemon_t* pokemon,size_t cantidad_pokemon){
	pokemon_t* pokemon_aux = realloc(pokemon,sizeof(pokemon_t)*((size_t)(cantidad_pokemon+1)));
	if(pokemon_aux == NULL){
		free(pokemon);
		return NULL;
	}
	pokemon = pokemon_aux;
	return pokemon;
}

//Pre: Recive un puntero pokemon_t valido y un size_t a la cantidad que se quiere achicar pokemon_t.
//Post: Si se pudo achicar pokemon_t* devuelve el nuevo puntero, sino se libera o la cantidad es menor igal a 1 el puntero recivido y devuelve NULL.
pokemon_t* achicar_pokemon(pokemon_t* pokemon,size_t cantidad_pokemon){
	if(cantidad_pokemon <= 1){
		free(pokemon);
		return NULL;
	}

	pokemon_t* pokemon_aux = realloc(pokemon,sizeof(pokemon_t)*((cantidad_pokemon-1)));
	if(pokemon_aux == NULL){
		free(pokemon);
		return NULL;
	}
	pokemon = pokemon_aux;
	return pokemon;
}

//Pre: Recive un archivo valido y un poemon_t*.
//Post: Carga lo leido a pokemon_t y devuelve el numero de variables leidas.
int leer_arrecife(FILE* archivo_arrecife,pokemon_t* pokemon){
	return fscanf(archivo_arrecife,FORMATO_LECTURA,pokemon->especie,&(pokemon->velocidad),&(pokemon->peso),pokemon->color);
}


/*
 * Función que dado un archivo carga los pokémon que viven en el arrecife
 * reservando la memoria necesaria para el mismo. Se debe intentar leer la mayor
 * cantidad posible de registros del archivo. Al encontrar el primer registro
 * erróneo (o al llegar al final del archivo) se deben finalizar la lectura y
 * crear el arrecife con los pokémon leídos exitosamente. En caso de no
 * encontrar ningún registro con el formato correcto, se debe devolver error.
 * Devuelve un puntero a un arrecife válido o NULL en caso de error.
 */
arrecife_t* crear_arrecife(const char* ruta_archivo){
	pokemon_t pokemon_aux;

	arrecife_t* ptr_arrecife = malloc(sizeof(arrecife_t));
	if (ptr_arrecife == NULL){
		return NULL;
	}

	ptr_arrecife->pokemon = malloc(sizeof(pokemon_t));
	if(ptr_arrecife->pokemon == NULL){
		free(ptr_arrecife);
		return NULL;
 	}
	ptr_arrecife->cantidad_pokemon = 0;

	FILE* archivo_arrecife = fopen(ruta_archivo,"r");
	if(!archivo_arrecife){
		printf("NO se pudo abrir el archivo");
		free(ptr_arrecife->pokemon);
		free(ptr_arrecife);
		return NULL;
	}

	int leidos = leer_arrecife(archivo_arrecife, &pokemon_aux);

	while((leidos == 4)&&(ptr_arrecife->pokemon != NULL)){
		ptr_arrecife->pokemon = agrandar_pokemon(ptr_arrecife->pokemon,(size_t)ptr_arrecife->cantidad_pokemon);

		if(ptr_arrecife->pokemon != NULL){
			ptr_arrecife->pokemon[ptr_arrecife->cantidad_pokemon] = pokemon_aux;
			(ptr_arrecife->cantidad_pokemon)++;
			leidos = leer_arrecife(archivo_arrecife, &pokemon_aux);
		}
	}

	if((ptr_arrecife->cantidad_pokemon == 0)||(ptr_arrecife->pokemon == NULL)){
		free(ptr_arrecife->pokemon);
		free(ptr_arrecife);
		fclose(archivo_arrecife);
		printf("Uhhh... Parece que fallo.");
		return NULL;
	}

	fclose(archivo_arrecife);
	return ptr_arrecife;
}

/*
 * Función que crea un acuario vacío reservando la memoria necesaria para el mismo.
 * Devuelve el acuario o NULL en caso de error.
 */
acuario_t* crear_acuario(){
	acuario_t* ptr_acuario = malloc(sizeof(acuario_t));
	if(ptr_acuario == NULL){
		return NULL;
 	}

	ptr_acuario->pokemon = malloc(sizeof(pokemon_t));
	if(ptr_acuario->pokemon == NULL){
		free(ptr_acuario);
		return NULL;
 	}

	ptr_acuario->cantidad_pokemon = 0;
  
	return ptr_acuario;
}

// Pre: recibe un arrecife valido, la cantidad de Pokemon que se quire trasladar y una funcion boolena valida para seleccionar
// Post: Devuelve si hay suficientes pokemones que cumplen la condicion de seleccion
bool pokemones_suficientes(arrecife_t* arrecife,int cant_seleccion,bool (*seleccionar_pokemon) (pokemon_t*)){
	int i=0;
	int pokemon_arrecife = 0;

	while((i < arrecife->cantidad_pokemon) && (pokemon_arrecife < cant_seleccion)){
		if((*seleccionar_pokemon)(&(arrecife->pokemon[i]))){
			pokemon_arrecife++;
		}
		i++;
	}
	return (pokemon_arrecife >= cant_seleccion);
}


/*
 * Función que deberá sacar del arrecife a todos los pokémon que satisfagan la
 * condición dada por el puntero a función (que devuelvan true) y trasladarlos
 * hacia el acuario. El parámetro cant_seleccion especifica la cantidad máxima
 * de pokémon que serán trasladados. En caso de que haya menos pokémon trasladables en el
 * arrecife que los pedidos, no se deberá mover ninguno para conservar los pocos existentes.
 * El vector de pokemones del arrecife quedará solo con aquellos que no fueron
 * trasladados (su tamaño se ajustará luego de cada traslado).
 * El vector de pokemones del acuarió quedará con aquellos que fueron
 * trasladados esta vez más los que ya había en el
 * acuario (su tamaño se ajustará luego de cada traslado).
 * Devuelve -1 en caso de error o 0 en caso contrario.
 */
int trasladar_pokemon(arrecife_t* arrecife, acuario_t* acuario, bool (*seleccionar_pokemon) (pokemon_t*), int cant_seleccion){
	int i=0;
	int trasladados = 0;

	if(!pokemones_suficientes(arrecife,cant_seleccion,seleccionar_pokemon)){
		printf("No hay suficientes Pokemon.");
		return 	ERROR;
	}

	while((i<arrecife->cantidad_pokemon)&&(trasladados<cant_seleccion)&&(arrecife->pokemon != NULL)&&(acuario->pokemon != NULL)){
		if((*seleccionar_pokemon)(&(arrecife->pokemon[i]))){
			acuario->pokemon = agrandar_pokemon(acuario->pokemon,(size_t)acuario->cantidad_pokemon);
			acuario->pokemon[acuario->cantidad_pokemon] = arrecife->pokemon[i];
			(acuario->cantidad_pokemon)++;

			arrecife->pokemon[i] = arrecife->pokemon[(arrecife->cantidad_pokemon)-1];
			arrecife->pokemon = achicar_pokemon(arrecife->pokemon,(size_t)arrecife->cantidad_pokemon);
			(arrecife->cantidad_pokemon)--;

			trasladados++;
		}else{
			i++;
		}	
	}

	if(!(acuario->pokemon)){             // NO se chequea arrecife->pokemon porque se pude liberar si queda con 0 pokemon
		printf("Algo salio mal");
		return ERROR;
	}

	return FUNCIONO;
}



/*
 * Procedimiento que dado un arrecife deberá mostrar por pantalla a todos los pokemon que contiene.
 */
void censar_arrecife(arrecife_t* arrecife, void (*mostrar_pokemon)(pokemon_t*)){

	for(int i=0;i<arrecife->cantidad_pokemon;i++){	
		(*mostrar_pokemon)(&(arrecife->pokemon[i]));
	}
}

/*
 * Función que dado un acuario guarda en un archivo de texto a los pokemones que contiene.
 * Devuelve 0 si se realizo con éxito o -1 si hubo algun problema para guardar el archivo.
 */
int guardar_datos_acuario(acuario_t* acuario, const char* nombre_archivo){
	FILE* archivo_acuario = fopen(nombre_archivo,"w");
	if(!archivo_acuario){
		printf("No se pudo abrir el archivo");
		return ERROR;
	}

	for(int i=0; i < acuario->cantidad_pokemon;i++){
		fprintf(archivo_acuario,FORMATO_ESCRITURA,acuario->pokemon[i].especie,acuario->pokemon[i].velocidad,acuario->pokemon[i].peso,acuario->pokemon[i].color);
	}
	fclose(archivo_acuario);

	return FUNCIONO;
}

/*
 * Libera la memoria que fue reservada para el acuario.
 */
void liberar_acuario(acuario_t* acuario){
	if(acuario != NULL){
		if(acuario->pokemon != NULL){
			free(acuario->pokemon);
		}
		free(acuario);
	}
}


/*
 * Libera la memoria que fue reservada para el arrecife.
 */
void liberar_arrecife(arrecife_t* arrecife){
	if(arrecife != NULL){
		if(arrecife->pokemon != NULL){
			free(arrecife->pokemon);
		}
		free(arrecife);
	}
}