CFLAGS = -g -Wall -Werror -Wconversion -std=c99

evento_pesca: simulacion.c evento_pesca.c ascii_pokemon.c ascii_pokemon.h
	gcc *.c $(CFLAGS) -o evento_pesca

debug: evento_pesca
	gdb evento_pesca 

test: evento_pesca
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./evento_pesca

run: evento_pesca
	./evento_pesca