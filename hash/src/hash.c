#include <string.h>
#include <stdlib.h>
#include "internas.h"
#include "hash.h"

size_t funcion_hash(size_t tamanio, const char *cadena)
{
	size_t clave = 1;
	size_t len = strlen(cadena);
	for (size_t i = 0; i < len; i++) {
		clave += (size_t)cadena[i];
	}
	return (len * clave * (clave + 3)) % tamanio;
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

nodo_t *alocar_nodo(char *clave, void *elemento)
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
	if (!hash || !clave)
		return NULL;

	double factor_rehash = (double)(hash->cantidad_actual + 1) /
			       ((double)hash->cantidad_maxima);

	if (factor_rehash > factor_de_carga)
		rehash(hash);

	char *copia_clave = malloc((sizeof(char) * strlen(clave)) + 1);
	if (!copia_clave)
		return NULL;
	strcpy(copia_clave, clave);

	size_t posicion_tabla =
		funcion_hash(hash->cantidad_maxima, copia_clave);
	nodo_t *puntero_nodo = hash->tabla[posicion_tabla];

	if (!puntero_nodo) {
		nodo_t *nuevo_nodo = alocar_nodo(copia_clave, elemento);
		if (!nuevo_nodo) {
			free(copia_clave);
			return NULL;
		}
		if (anterior)
			*anterior = NULL;
		hash->tabla[posicion_tabla] = nuevo_nodo;
		hash->cantidad_actual++;
		return hash;
	}

	if (strcmp(puntero_nodo->clave, copia_clave) == 0) {
		if (anterior)
			*anterior = puntero_nodo->elemento;
		puntero_nodo->elemento = elemento;
		free(copia_clave);
		return hash;
	}

	while (puntero_nodo->siguiente) {
		puntero_nodo = puntero_nodo->siguiente;
		if (strcmp(puntero_nodo->clave, copia_clave) == 0) {
			if (anterior)
				*anterior = puntero_nodo->elemento;
			free(copia_clave);
			puntero_nodo->elemento = elemento;
			return hash;
		}
	}

	nodo_t *nuevo_nodo = alocar_nodo(copia_clave, elemento);
	if (!nuevo_nodo) {
		free(copia_clave);
		return NULL;
	}
	if (anterior)
		*anterior = NULL;
	hash->cantidad_actual++;
	puntero_nodo->siguiente = nuevo_nodo;
	return hash;
}

void rehash(hash_t *hash)
{
	if (!hash)
		return;

	nodo_t **nueva_tabla =
		calloc(hash->cantidad_maxima * 2, sizeof(nodo_t *));
	if (!nueva_tabla)
		return;

	nodo_t *nodo_act = NULL;
	nodo_t *nodo_nuevo = NULL;
	nodo_t *siguiente = NULL;

	for (size_t i = 0; i < hash->cantidad_maxima; i++) {
		nodo_act = hash->tabla[i];
		while (nodo_act) {
			siguiente = nodo_act->siguiente;
			nodo_act->siguiente = NULL;

			size_t nueva_pos = funcion_hash(
				hash->cantidad_maxima * 2, nodo_act->clave);
			nodo_nuevo = nueva_tabla[nueva_pos];

			if (!nodo_nuevo) {
				nueva_tabla[nueva_pos] = nodo_act;
				nodo_act = siguiente;
				continue;
			}
			while (nodo_nuevo->siguiente) {
				nodo_nuevo = nodo_nuevo->siguiente;
			}

			nodo_nuevo->siguiente = nodo_act;
			nodo_act = siguiente;
		}
	}
	free(hash->tabla);
	hash->tabla = nueva_tabla;
	hash->cantidad_maxima *= 2;
	return;
}

void *hash_quitar(hash_t *hash, const char *clave)
{
	if (!hash || !clave)
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
			free(nodo_posicion->clave);
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
	if (!hash || !clave)
		return NULL;
	size_t posicion = funcion_hash(hash->cantidad_maxima, clave);
	nodo_t *nodo_posicion = hash->tabla[posicion];
	if (!nodo_posicion)
		return NULL;
	while (nodo_posicion) {
		if (strcmp(nodo_posicion->clave, clave) == 0)
			return nodo_posicion->elemento;
		nodo_posicion = nodo_posicion->siguiente;
	}
	return NULL;
}

bool hash_contiene(hash_t *hash, const char *clave)
{
	if (!hash || !clave)
		return NULL;
	size_t posicion = funcion_hash(hash->cantidad_maxima, clave);
	nodo_t *nodo_posicion = hash->tabla[posicion];
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
	free(nodo->clave);
	free(nodo);
}

void hash_destruir(hash_t *hash)
{
	if (!hash)
		return;
	for (size_t i = 0; i < hash->cantidad_maxima; i++) {
		destruir_enlazados(hash->tabla[i], NULL);
	}
	free(hash->tabla);
	free(hash);
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
	if (!hash)
		return;
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
	if (!hash)
		return 0;
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
