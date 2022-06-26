#ifndef __INTERNAS_H_
#define __INTERNAS_H_

#include "hash.h"

typedef struct nodo nodo_t;

struct nodo {
	char *clave;
	void *elemento;
	nodo_t *siguiente;
};

struct hash {
	nodo_t **tabla;
	size_t cantidad_maxima;
	size_t cantidad_actual;
};

#define factor_de_carga 0.75

/*
 * Recibe un hash y se encarga de reallocar la memoria para el mismo, duplicando el tamanio que tiene.
 *
 * No vuelve a realocar cada uno de los nodos, los reconecta a todos en una nueva tabla.
 *
 * No devuelve nada. Si hay error, no hay rehash.
 * */
void rehash(hash_t *hash);

/*
 *  Recibe un tamanio y una cadena de caracteres (string)
 *
 * Devuelve una posicion necesariamente menor al tamanio
 * La cual siempre es igual para la misma cadena y el mismo tamanio
 * */
size_t funcion_hash(size_t tamanio, const char *cadena);

/*
 *
 * Recibe una clave cadena de chars y un elemento.
 *
 * Aloca memoria dinamica para el nodo y lo devuelve.
 * Devuelve NULL en caso de ERROR.
 *
 * */
nodo_t *alocar_nodo(char *clave, void *elemento);

/*
 * Recibe un nodo y libera la memoria para todos los nodos conectados al mismo.
 *
 * Recibe una funcion destructor para aplicar a cada elemento de los nodos.
 * Puede ser NULL y no es aplicada.
 *
 * */
void destruir_enlazados(nodo_t *nodo, void (*destructor)(void *));

#endif /* __INTERNAS_H___ */
