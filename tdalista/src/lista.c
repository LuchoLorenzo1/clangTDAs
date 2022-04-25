#include "lista.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

nodo_t *nodo_en_posicion(lista_t *lista, size_t posicion){
	nodo_t *nodo = lista->nodo_inicio;
	size_t i = 0;
	while (nodo && i<posicion) {
		nodo = nodo->siguiente;
		i++;
	}
	return nodo;
}

lista_t *lista_crear()
{
	return calloc(1,sizeof(lista_t));
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
    nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));

    if (!nuevo_nodo)
        return NULL;

    nuevo_nodo->elemento = elemento;

    if (!lista->nodo_inicio) {
        lista->nodo_inicio = nuevo_nodo;
    } else {
	lista->nodo_fin->siguiente = nuevo_nodo;
    }

    lista->cantidad++;
    lista->nodo_fin = nuevo_nodo;

    return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento, size_t posicion)
{
    if (!lista)
        return NULL;

    nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
    if (!nuevo_nodo)
	return NULL;

    nuevo_nodo->elemento = elemento;
    lista->cantidad++;

    if (!lista->nodo_inicio) {
        lista->nodo_inicio = nuevo_nodo;
        lista->nodo_fin = nuevo_nodo;
	return lista;
    } 




    /* nodo_t *nodo_posicion = iterador_interno(lista, posicion); */
    /* nodo_posicion->siguiente = nuevo_nodo; */

	/* return lista; */
    return NULL;
}

void *lista_quitar(lista_t *lista)
{
	return NULL;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	return NULL;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if(!lista)
		return NULL;

	size_t i = 0;
	nodo_t *nodo = lista->nodo_inicio;

	while (nodo && i < posicion) {
		nodo = nodo->siguiente;
		i++;
	}

	return nodo->elemento;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *), void *contexto)
{
	return NULL;
}

void *lista_primero(lista_t *lista)
{
	return NULL;
}

void *lista_ultimo(lista_t *lista)
{
	return NULL;
}

bool lista_vacia(lista_t *lista)
{
	return false;
}

size_t lista_tamanio(lista_t *lista)
{
	if (!lista) 
		return -1;
	return lista->cantidad;
}


void lista_destruir(lista_t *lista)
{
	if(!lista)
		return;

	nodo_t *nodo = lista->nodo_inicio;

	while(nodo){
		nodo_t *aux = nodo->siguiente;
		free(nodo);
		nodo = aux;
	}

	free(lista);
}


void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{

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
