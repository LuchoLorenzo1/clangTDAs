#include <math.h>
#include "hash.h"
#include <stdlib.h>
#include <string.h>

#define constante 0.618033988

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

/* int funcion_hash(hash_t hash, char *cadena) */
/* { */
/* 	if (!cadena) */
/* 		return 0; */
/* 	int clave = strlen(cadena) * (cadena[0] * cadena[strlen(cadena) - 1]); */
/* 	double n = clave * constante; */
/* 	int parte_entera_n = (int)n; */
/* 	return (int)(hash.cantidad_maxima * (n - parte_entera_n)); */
/* } */

int funcion_hash(hash_t *hash, const char *cadena)
{
	return (cadena[0] * strlen(cadena)) % hash->cantidad_maxima;
}

hash_t *hash_crear(size_t capacidad)
{
	hash_t *hash = malloc(sizeof(hash_t));
	if (!hash)
		return NULL;

	nodo_t **tabla = calloc(capacidad, sizeof(nodo_t *));
	if (!tabla) {
		free(hash);
		return NULL;
	}

	hash->tabla = tabla;
	hash->cantidad_maxima = capacidad;
	hash->cantidad_actual = 0;

	return hash;
}

nodo_t *alocar_nodo(const char *clave, void *elemento)
{
	nodo_t *nodo = malloc(sizeof(nodo_t));
	if (!nodo)
		return NULL;
	nodo->clave = clave;
	nodo->elemento = elemento;
	nodo->siguiente = NULL;
	return nodo;
}

hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento,
		      void **anterior)
{
	if (!hash || !elemento)
		return NULL;

	int posicion_tabla = funcion_hash(hash, clave);
	nodo_t *puntero_nodo = hash->tabla[posicion_tabla];

	if (!puntero_nodo) {
		nodo_t *nuevo_nodo = alocar_nodo(clave, elemento);
		if (!nuevo_nodo)
			return NULL;
		hash->cantidad_actual++;
		return hash;
	}

	while (puntero_nodo->siguiente) {
		puntero_nodo = puntero_nodo->siguiente;
		if (strcmp(puntero_nodo->clave, clave) == 0) {
			puntero_nodo->elemento = elemento;
			return hash;
		}
	}

	nodo_t *nuevo_nodo = alocar_nodo(clave, elemento);
	if (!nuevo_nodo)
		return NULL;
	hash->cantidad_actual++;
	puntero_nodo->siguiente = nuevo_nodo;
	return hash;
}

void *hash_quitar(hash_t *hash, const char *clave)
{
	return NULL;
}

void *hash_obtener(hash_t *hash, const char *clave)
{
	return NULL;
}

bool hash_contiene(hash_t *hash, const char *clave)
{
	return false;
}

size_t hash_cantidad(hash_t *hash)
{
	if (!hash)
		return 0;
	return hash->cantidad_actual;
}

void destruir_enlazados(nodo_t *nodo, void (*destructor)(void *))
{
	if (!nodo)
		return;
	destruir_enlazados(nodo->siguiente, destructor);
	if (destructor)
		destructor(nodo->elemento);
	free(nodo);
}

void hash_destruir(hash_t *hash)
{
	for (size_t i = 0; i < hash->cantidad_maxima; i++) {
		destruir_enlazados(hash->tabla[i], NULL);
	}
	free(hash);
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
	for (size_t i = 0; i < hash->cantidad_maxima; i++) {
		destruir_enlazados(hash->tabla[i], destructor);
	}
	free(hash);
}

size_t hash_con_cada_clave(hash_t *hash,
			   bool (*f)(const char *clave, void *valor, void *aux),
			   void *aux)
{
	return 0;
}
