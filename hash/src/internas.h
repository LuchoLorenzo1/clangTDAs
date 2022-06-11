#ifndef __INTERNAS_H_
#define __INTERNAS_H_

#include "hash.h"

typedef struct nodo nodo_t;

struct nodo {
	const char *clave;
	void *elemento;
	nodo_t *siguiente;
};

struct hash {
	nodo_t **tabla;
	size_t cantidad_maxima;
	size_t cantidad_actual;
};
#define constante 0.618033988

/*
 *
 * Se ocupa del rehash
 *
 *
 * */
void rehash(hash_t *hash);

/*
 *
 * Se ocupa del rehash
 *
 *
 * */
size_t funcion_hash(size_t tamanio, const char *cadena);

/*
 *
 * Se ocupa del rehash
 *
 *
 * */
nodo_t *alocar_nodo(const char *clave, void *elemento);

/*
 *
 * Se ocupa del rehash
 *
 *
 * */
void destruir_enlazados(nodo_t *nodo, void (*destructor)(void *));

#endif /* __INTERNAS_H___ */
