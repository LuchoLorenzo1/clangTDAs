VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2
CFLAGS =-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0
CC = gcc
ARG = ejemplo/objetos.txt ejemplo/interacciones.txt

all: clean valgrind

escape: escape_pokemon.c src/*
	$(CC) $(CFLAGS) src/*.c  escape_pokemon.c -o escape 2>&1

run: escape
	./escape ejemplo/objetos.txt ejemplo/interacciones.txt

valgrind: escape
	valgrind $(VALGRIND_FLAGS) ./escape $(ARG) 2>&1

valgrind-pruebas: pruebas
	valgrind $(VALGRIND_FLAGS) ./pruebas 2>&1

pruebas: src/*.c pruebas.c
	$(CC) $(CFLAGS) src/*.c  pruebas.c -o pruebas 2>&1

clean:
	rm -f escape *.o pruebas 2>&1
