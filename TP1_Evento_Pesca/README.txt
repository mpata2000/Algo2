TP1 - ¡Gran pesca Pokemon!
      Trabajo parctico Nro 1 de Algoritmos II-Curso Mendez de  Faculta de ingenieria de la Universidad de Buenos Aires

Introduccion:
    Este programa tiene como objetivo principal capturar a los Pokemon(con un criterio)que hay en un arrecife y pasarlos al acurio del usuario.

    El programa al ejecutarse deberia inciar un acuario_t* y un arrecife_t* con sus respectivas funciones del evento_pesca.h, se debe aclarar que el formato de 
    archivo que recive crear_arecife es: "especie;velocidad;peso;color\n". Ambas funciones crear_arrecife y crear_acuario si fallan van a devolver NULL y se deberia
    terminar la ejecucion del programa. 

    Si se a logrado con exito la inicializacion de arrecife_t* y acuario_t* ahora se puede a traspasar los Pokemon, para ello se utiliza trasladar_pokemon.
    Es importante mandar un puntero a funcion bool que devuelva true cuando se cumplan los criterios devuelva true, si no el traslado no va funcionar bien.
    Si se llega a mandar  un acuario_t* o un arrecife_t* sin inicializar de forma correcta, o ocurre un error en la ejecuccion de la funcion,esta va a devolver -1.
    Si arrecife_t* se queda sin Pokemon va ser liberado y igualado a NULL

    Tras hacer el traslado se puede llamar a censar_arrecife la cual recive un puntero de una funcion que muestra cada pokemon individualmente a como lo desee el
    usuario. Esta funcion va a mostrar los pokemones restantes de arrecife_t*.

    Por ultimo se deberia guardar acuario_t* con guardar_datos_acuario. Esta funcion guarda los datos de acuario_t* en el archivo de lectura con el mismo formato
    que el de lectura: "especie;velocidad;peso;color\n" . Si o si cuando se desee finalizar la ejecucion se debera utilizar liberar_acuario y liberar_arrecife
    para que el programa no pierda memoria.
    

Compilacion y Ejecucion:
    Para compilar y correr este programa se utiliza un archivo makefile.

    Sus comandos son:

        -> make o make evento_pesca :
            Este comando compila el programa si y solo si el archivo de ejecucion evento_pesca esta desactulizado.

            CFLAGS = -g -Wall -Werror -Wconversion -std=c99

            evento_pesca: simulacion.c evento_pesca.c ascii_pokemon.c ascii_pokemon.h
	            gcc *.c $(CFLAGS) -o evento_pesca

        -> make debug :
            Este comando primero chequea que evento_pesca este compilado y actualizado(si no lo esta lo actualiza) y corre gdb en evento_pesca.

            debug: evento_pesca
	            gdb evento_pesca
        
        -> make test : 
            Este comando primero chequea que evento evento_pesca este compilado y actualizado; y corre valgrind para testear perdidas de memoria.
            
            test: evento_pesca
	            valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./evento_pesca

        -> make run:
            Se usa para ejecutar el programa. El comando primero chequea que evento_pesca este compilado y actualizado(si no lo esta lo actualiza).

Punteros
    Un puntero es una variable  que guarda direcciones de memoria

    Se declara:

        tipo_de_variable* bombre_puntero;

    

Arimetica de Punteros
 ->Operador Direccion(&): Este permite acceder a la direccion de memoria de una variable.

 -> Operador Indireccion(*): Ademas de que permite declarar un tipo de dato puntero, tambien permite ver el valor que esta en la direccion de memoria asignada.

 -> Incrementos(++) y Decrementos(--): Se puede usar un puntero como si de un array se tratase y mover por posiciones en la memoria(que es secuencial).

    Equivalencia punteros-arreglo:

        array[0] == *array 
        array[1] == *(array+1) 
        array[2] == *(array+1) 
        array[n] == *(array+n) 

    Multiples Indirecciones

        int a = 3;
        int *b = &a;
        int **c = &b;
        int ***d = &c;

        *d == c
        **d == *c == b
        ***d == **c == *b == a == 3

Punteros a Funciones:
    Los punteros a funciones apuntan a codigo, no a datos. Apunta a la primer instruccion ejecutable de la funcion(normalmente). El nombre de la funcion tambien
    puede ser utilizado para obtener la direccion de esta.

    Los punteros a funciones en C pueden ser:
        ->Elementos de un vector
        ->Pasados como parametro a una funcion
        ->Ser devuelto por una funcion

    Como se declara:

        tipo_de_retorno (*nombre_puntero_funcion)(tipo_var_1,tipo_var_2,...,tipo_var_n) = nombre_puntero_funcion;

        ej:

            void hello_world(char nombre[]){
                printf("Hello World!\n");
                printf("Have a nice day %s\n",nombre);
            }

            int main(){
                char nombre[] = "Martin";

                void (*puntero_hello_world)(char*) = hello_world; //Declaro el puntero a la funcion y la apunto a hello_world

                (*puntero_hello_world)(nombre); //Llamo al puntero a la funcion que es igual a llamar a hello_world
            }

Malloc y Realloc:
    -> void* malloc(size_t size):
            Utilizado para pedirle al SIstema operativo que se desea utilizar memoria del heap(memoria dinamica).El sistema operativo reserva size bytes y 
            devuelve la direccion del primer byte de memoria(La memoria no esta inicializada). Si el valor de size es 0, esta puede devolver NULL o un valor a un
            puntero unico. Si no se puede ocupar memoria(ej. esta todo ocupado el heap) devuelve NULL.
    
    -> void* realloc(void*ptr, size_t size) :
            Realloc modifica el tamaño del bloque de memoria apuntado por ptr en size bytes (puede aumentar o disminuir el tamaño del bloque). Si el nuevo bloque
            es mayor que el tamaño anterior, lo inicializa con basura si falla devuelve NULL


Por ultimo agradezco a Santiago Fernandez(mi corrector) sin el este trabajo no habria sido posible. Por ello le dededico este video:
    https://www.youtube.com/watch?v=dQw4w9WgXcQ
