#include "lista.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

nodo_t *nodo_en_posicion(lista_t *lista, size_t posicion)
{
	nodo_t *nodo = lista->nodo_inicio;
	if (!nodo) 
		return NULL;

	size_t i = 0;
	while (nodo->siguiente && i < posicion) {
		nodo = nodo->siguiente;
		i++;
	}

	return nodo;
}

lista_t *lista_crear()
{
	lista_t *lista = malloc(sizeof(lista_t));

	if(!lista)
		return NULL;

	lista->nodo_fin = NULL;
	lista->nodo_inicio = NULL;
	lista->cantidad = 0;

	return lista;
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	lista_insertar_en_posicion(lista, elemento, lista->cantidad);
	return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	if (!lista)
		return NULL;

	nodo_t *nuevo_nodo = calloc(1, sizeof(nodo_t));

	if (!nuevo_nodo)
		return NULL;

	nuevo_nodo->elemento = elemento;

	if (!lista->nodo_inicio) {
		lista->nodo_inicio = nuevo_nodo;
		lista->nodo_fin = nuevo_nodo;
		lista->cantidad++;
		return lista;
	}

	if (posicion == 0) {
		nuevo_nodo->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nuevo_nodo;
		lista->cantidad++;
		return lista;
	}

	if (posicion >= lista->cantidad) {
		lista->nodo_fin->siguiente = nuevo_nodo;
		lista->nodo_fin = nuevo_nodo;
		lista->cantidad++;
		return lista;
	}

	nodo_t *nodo_posicion = nodo_en_posicion(lista, posicion - 1);
	nodo_t *aux = nodo_posicion->siguiente;

	nodo_posicion->siguiente = nuevo_nodo;
	nuevo_nodo->siguiente = aux;
	lista->cantidad++;

	return lista;
}

void *lista_quitar(lista_t *lista)
{
	if (!lista || !lista->nodo_inicio)
		return NULL;

	nodo_t *anteultimo_nodo = nodo_en_posicion(lista, lista->cantidad - 2);

	void *elemento = anteultimo_nodo->siguiente->elemento;
	free(anteultimo_nodo->siguiente);

	anteultimo_nodo->siguiente = NULL;
	lista->cantidad--;

	return elemento;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	if (!lista || !lista->nodo_inicio)
		return NULL;

	nodo_t *nodo_posicion;
	lista->cantidad--;

	if (posicion == 0) {
		nodo_posicion = lista->nodo_inicio->siguiente;

		void *elemento = lista->nodo_inicio->elemento;
		free(lista->nodo_inicio);

		lista->nodo_inicio = nodo_posicion;

		if (!lista->nodo_inicio)
			lista->nodo_fin = lista->nodo_inicio;

		return elemento;
	}

	if (posicion >= lista->cantidad - 1) {
		nodo_posicion = nodo_en_posicion(lista, lista->cantidad - 1);

		void *elemento = lista->nodo_fin->elemento;
		free(lista->nodo_fin);

		lista->nodo_fin = nodo_posicion;
		return elemento;
	}

	nodo_posicion = nodo_en_posicion(lista, posicion - 1);
	nodo_t *a_eliminar = nodo_posicion->siguiente;
	void *elemento = a_eliminar->elemento;

	nodo_posicion->siguiente = a_eliminar->siguiente;

	free(a_eliminar);
	return elemento;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if (!lista)
		return NULL;

	nodo_t *nodo = nodo_en_posicion(lista, posicion);

	if (!nodo)
		return NULL;
	return nodo->elemento;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	if (!lista || !lista->nodo_inicio)
		return NULL;

	nodo_t *nodo = lista->nodo_inicio;
	while (nodo) {
		if (comparador(nodo->elemento, contexto))
			return nodo->elemento;
		nodo = nodo->siguiente;
	}
	return NULL;
}

void *lista_primero(lista_t *lista)
{
	if (!lista || !lista->nodo_inicio)
		return NULL;
	return lista->nodo_inicio->elemento;
}

void *lista_ultimo(lista_t *lista)
{
	if (!lista || !lista->nodo_inicio)
		return NULL;
	return lista->nodo_fin->elemento;
}

bool lista_vacia(lista_t *lista)
{
	return !!lista && !!lista->nodo_inicio;
}

size_t lista_tamanio(lista_t *lista)
{
	if (!lista)
		return 0;
	return lista->cantidad;
}

void lista_destruir(lista_t *lista)
{
	if (!lista)
		return;

	if (!lista->nodo_inicio) {
		return;
		free(lista);
	}

	nodo_t *nodo = lista->nodo_inicio;

	while (nodo) {
		nodo_t *aux = nodo->siguiente;
		free(nodo);
		nodo = aux;
	}

	free(lista);
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
	if (!lista)
		return;

	if (!lista->nodo_inicio) {
		return;
		free(lista);
	}

	nodo_t *nodo = lista->nodo_inicio;

	while (nodo) {
		nodo_t *aux = nodo->siguiente;
		funcion(nodo->elemento);
		free(nodo);
		nodo = aux;
	}

	free(lista);
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	return NULL;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	return false;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	return false;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	return NULL;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
	return;
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	return 0;
}
