#include <stdlib.h>
#include "internas.h"
#include "hash.h"
#include <string.h>

size_t funcion_hash(size_t tamanio, const char *cadena)
{
	double n = constante * (double)strlen(cadena) *
		   ((double)cadena[0] * (double)cadena[strlen(cadena) - 1]);
	return (size_t)((double)tamanio * (n - (size_t)n));
}

/* size_t funcion_hash(hash_t *hash, const char *cadena)
{
	return strlen(cadena) % hash->cantidad_maxima;
} */

void rehash(hash_t *hash)
{
	if (!hash)
		return;

	nodo_t **nueva_tabla =
		calloc(hash->cantidad_maxima * 2, sizeof(nodo_t *));
	if (!nueva_tabla)
		return;

	nodo_t *nodo_posicion = NULL;
	nodo_t *nodo_nueva_pos = NULL;
	nodo_t *siguiente = NULL;
	for (size_t i = 0; i < hash->cantidad_maxima; i++) {
		nodo_posicion = hash->tabla[i];
		while (nodo_posicion) {
			siguiente = nodo_posicion->siguiente;
			nodo_posicion->siguiente = NULL;

			size_t posicion_nueva =
				funcion_hash(hash->cantidad_maxima * 2,
					     nodo_posicion->clave);
			nodo_nueva_pos = nueva_tabla[posicion_nueva];

			if (!nodo_nueva_pos) {
				nueva_tabla[posicion_nueva] = nodo_posicion;
				nodo_posicion = siguiente;
				continue;
			}
			while (nodo_nueva_pos->siguiente) {
				nodo_nueva_pos = nodo_nueva_pos->siguiente;
			}
			nodo_nueva_pos->siguiente = nodo_posicion;
			nodo_posicion = siguiente;
		}
	}
	free(hash->tabla);
	hash->tabla = nueva_tabla;
	hash->cantidad_maxima *= 2;
	return;
}

hash_t *hash_crear(size_t capacidad)
{
	if (capacidad < 3)
		capacidad = 3;

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
	if (!hash)
		return NULL;

	double factor = (double)(hash->cantidad_actual + 1) /
			((double)hash->cantidad_maxima);

	if (factor > 0.75)
		rehash(hash);

	size_t posicion_tabla = funcion_hash(hash->cantidad_maxima, clave);
	nodo_t *puntero_nodo = hash->tabla[posicion_tabla];

	if (!puntero_nodo) {
		nodo_t *nuevo_nodo = alocar_nodo(clave, elemento);
		if (!nuevo_nodo)
			return NULL;
		hash->tabla[posicion_tabla] = nuevo_nodo;
		hash->cantidad_actual++;
		return hash;
	}

	if (strcmp(puntero_nodo->clave, clave) == 0) {
		*anterior = puntero_nodo->elemento;
		puntero_nodo->elemento = elemento;
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
	if (!hash)
		return NULL;
	size_t posicion = funcion_hash(hash->cantidad_maxima, clave);
	nodo_t *nodo_posicion = hash->tabla[posicion];
	if (!nodo_posicion)
		return NULL;

	nodo_t *anterior = NULL;
	while (nodo_posicion) {
		if (strcmp(nodo_posicion->clave, clave) == 0) {
			if (!anterior) {
				hash->tabla[posicion] =
					nodo_posicion->siguiente;
			} else {
				anterior->siguiente = nodo_posicion->siguiente;
			}
			void *elemento = nodo_posicion->elemento;
			free(nodo_posicion);
			hash->cantidad_actual--;
			return elemento;
		}
		anterior = nodo_posicion;
		nodo_posicion = nodo_posicion->siguiente;
	}
	return NULL;
}

void *hash_obtener(hash_t *hash, const char *clave)
{
	if (!hash)
		return NULL;
	size_t posicion = funcion_hash(hash->cantidad_maxima, clave);
	nodo_t *nodo_posicion = hash->tabla[posicion];
	if (!nodo_posicion)
		return NULL;
	while (nodo_posicion->siguiente) {
		if (strcmp(nodo_posicion->clave, clave) == 0)
			return nodo_posicion->elemento;
		nodo_posicion = nodo_posicion->siguiente;
	}
	if (strcmp(nodo_posicion->clave, clave) == 0)
		return nodo_posicion->elemento;
	return NULL;
}

bool hash_contiene(hash_t *hash, const char *clave)
{
	if (!hash)
		return NULL;
	nodo_t *nodo_posicion =
		hash->tabla[funcion_hash(hash->cantidad_maxima, clave)];
	while (nodo_posicion) {
		if (strcmp(nodo_posicion->clave, clave) == 0)
			return true;
		nodo_posicion = nodo_posicion->siguiente;
	}
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
	free(hash->tabla);
	free(hash);
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
	for (size_t i = 0; i < hash->cantidad_maxima; i++) {
		destruir_enlazados(hash->tabla[i], destructor);
	}
	free(hash->tabla);
	free(hash);
}

size_t hash_con_cada_clave(hash_t *hash,
			   bool (*f)(const char *clave, void *valor, void *aux),
			   void *aux)
{
	nodo_t *nodo_posicion;
	size_t recorridos = 0;
	for (size_t i = 0; i < hash->cantidad_maxima; i++) {
		nodo_posicion = hash->tabla[i];
		while (nodo_posicion) {
			recorridos++;
			if (!f(nodo_posicion->clave, nodo_posicion->elemento,
			       aux))
				return recorridos;
			nodo_posicion = nodo_posicion->siguiente;
		}
	}
	return recorridos;
}
