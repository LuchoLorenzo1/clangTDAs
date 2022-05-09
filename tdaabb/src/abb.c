#include "abb.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

abb_t *abb_crear(abb_comparador comparador)
{
	if (!comparador)
		return NULL;

	abb_t *arbol = malloc(sizeof(abb_t));
	if (!arbol)
		return NULL;

	arbol->nodo_raiz = NULL;
	arbol->comparador = comparador;
	arbol->tamanio = 0;
	return arbol;
}

nodo_abb_t *insertar_recursivo(nodo_abb_t *nodo, void *elemento,
			       abb_comparador comparador)
{
	if (!nodo) {
		nodo_abb_t *nuevo_nodo = malloc(sizeof(nodo_abb_t));
		if (!nuevo_nodo)
			return NULL;
		nuevo_nodo->elemento = elemento;
		nuevo_nodo->derecha = NULL;
		nuevo_nodo->izquierda = NULL;
		return nuevo_nodo;
	}
	if (comparador(elemento, nodo->elemento) <= 0) {
		nodo_abb_t *nuevo_nodo = insertar_recursivo(
			nodo->izquierda, elemento, comparador);
		if (!nuevo_nodo)
			return NULL;
		nodo->izquierda = nuevo_nodo;
	} else {
		nodo_abb_t *nuevo_nodo =
			insertar_recursivo(nodo->derecha, elemento, comparador);
		if (!nuevo_nodo)
			return NULL;
		nodo->derecha = nuevo_nodo;
	}
	return nodo;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if (!arbol || !elemento)
		return NULL;

	nodo_abb_t *raiz = insertar_recursivo(arbol->nodo_raiz, elemento,
					      arbol->comparador);

	if (!raiz)
		return NULL;

	if (!arbol->nodo_raiz)
		arbol->nodo_raiz = raiz;

	arbol->tamanio++;
	return arbol;
}

nodo_abb_t *predecesor_inmediato(nodo_abb_t *nodo)
{
	nodo_abb_t *act = nodo;
	nodo_abb_t *ant = NULL;
	while (act->derecha) {
		ant = act;
		act = act->derecha;
	}
	if (ant)
		ant->derecha = NULL;
	return act;
}

void *quitar_recursivo(nodo_abb_t *nodo, void *elemento,
		       abb_comparador comparador, void **extraido)
{
	if (!nodo)
		return NULL;

	int comparacion = comparador(elemento, nodo->elemento);
	if (comparacion == 0) {
		nodo_abb_t *izq = nodo->izquierda;
		nodo_abb_t *der = nodo->derecha;
		*extraido = nodo->elemento;
		free(nodo);
		nodo = NULL;

		if (izq && der) {
			nodo_abb_t *reemplazo;
			if (izq->derecha) {
				reemplazo = predecesor_inmediato(izq);
				nodo_abb_t *todo_izquierda = reemplazo;
				while (todo_izquierda->izquierda)
					todo_izquierda =
						todo_izquierda->izquierda;
				todo_izquierda->izquierda = izq;
			} else {
				reemplazo = izq;
			}
			reemplazo->derecha = der;
			return reemplazo;
		}
		if (!izq && der)
			return der;
		if (izq && !der)
			return izq;
		if (!izq && !der)
			return NULL;

	} else if (comparacion < 0) {
		nodo->izquierda = quitar_recursivo(nodo->izquierda, elemento,
						   comparador, extraido);
	} else {
		nodo->derecha = quitar_recursivo(nodo->derecha, elemento,
						 comparador, extraido);
	}
	return nodo;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	if (!arbol || !elemento)
		return NULL;

	void *extraido = NULL;
	arbol->nodo_raiz = quitar_recursivo(arbol->nodo_raiz, elemento,
					    arbol->comparador, &extraido);
	if (!extraido)
		return NULL;
	arbol->tamanio--;
	return extraido;
}

void *buscar_recursivo(nodo_abb_t *nodo, void *elemento,
		       abb_comparador comparador)
{
	if (!nodo)
		return NULL;
	int comparacion = comparador(elemento, nodo->elemento);
	if (comparacion == 0)
		return nodo->elemento;
	else if (comparacion < 0)
		return buscar_recursivo(nodo->izquierda, elemento, comparador);
	else
		return buscar_recursivo(nodo->derecha, elemento, comparador);
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	if (!arbol || !elemento)
		return NULL;
	return buscar_recursivo(arbol->nodo_raiz, elemento, arbol->comparador);
}

bool abb_vacio(abb_t *arbol)
{
	if (!arbol || !arbol->nodo_raiz)
		return true;
	return false;
}

size_t abb_tamanio(abb_t *arbol)
{
	if (!arbol)
		return 0;
	return arbol->tamanio;
}

void destruir_recursivo(nodo_abb_t *nodo, void (*destructor)(void *))
{
	if (!nodo)
		return;
	destruir_recursivo(nodo->izquierda, destructor);
	destruir_recursivo(nodo->derecha, destructor);
	if (destructor)
		destructor(nodo->elemento);
	free(nodo);
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if (!arbol)
		return;
	destruir_recursivo(arbol->nodo_raiz, destructor);
	free(arbol);
}

void abb_destruir(abb_t *arbol)
{
	if (!arbol)
		return;
	destruir_recursivo(arbol->nodo_raiz, NULL);
	free(arbol);
}

size_t recorrer_inorden(nodo_abb_t *nodo, bool (*funcion)(void *, void *),
			void *aux, bool *continuar)
{
	if (!nodo)
		return 0;

	size_t izq = recorrer_inorden(nodo->izquierda, funcion, aux, continuar);
	if (!*continuar)
		return izq;

	*continuar = funcion(nodo->elemento, aux);
	if (!*continuar)
		return izq + 1;

	size_t der = recorrer_inorden(nodo->derecha, funcion, aux, continuar);
	return izq + der + 1;
}

size_t recorrer_preorden(nodo_abb_t *nodo, bool (*funcion)(void *, void *),
			 void *aux, bool *continuar)
{
	if (!nodo)
		return 0;

	*continuar = funcion(nodo->elemento, aux);
	if (!*continuar)
		return 1;

	size_t izq =
		recorrer_preorden(nodo->izquierda, funcion, aux, continuar);
	if (!*continuar)
		return izq + 1;

	size_t der = recorrer_preorden(nodo->derecha, funcion, aux, continuar);
	return izq + der + 1;
}

size_t recorrer_postorden(nodo_abb_t *nodo, bool (*funcion)(void *, void *),
			  void *aux, bool *continuar)
{
	if (!nodo)
		return 0;

	size_t izq =
		recorrer_postorden(nodo->izquierda, funcion, aux, continuar);
	if (!*continuar)
		return izq;

	size_t der = recorrer_postorden(nodo->derecha, funcion, aux, continuar);
	if (!*continuar)
		return izq + der;

	*continuar = funcion(nodo->elemento, aux);
	return izq + der + 1;
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	if (!arbol || !funcion)
		return 0;
	bool continuar = true;
	switch (recorrido) {
	case INORDEN:
		return recorrer_inorden(arbol->nodo_raiz, funcion, aux,
					&continuar);
	case PREORDEN:
		return recorrer_preorden(arbol->nodo_raiz, funcion, aux,
					 &continuar);
	case POSTORDEN:
		return recorrer_postorden(arbol->nodo_raiz, funcion, aux,
					  &continuar);
	default:
		return 0;
	}
}

typedef struct array_con_tamanio {
	void ***puntero_doble_array;
	size_t max;
	size_t *act;
} arr_t;

bool insertar_array(void *elemento, void *array_con_tamanio)
{
	arr_t aux = *(arr_t *)array_con_tamanio;

	void **array = *aux.puntero_doble_array;

	array[*aux.act] = elemento;
	(*aux.act)++;

	if (*aux.act == aux.max)
		return false;
	return true;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	if (!arbol || !array || tamanio_array <= 0)
		return 0;

	arr_t aux;
	aux.puntero_doble_array = &array;
	aux.max = tamanio_array;

	size_t tamanio_actual = 0;
	aux.act = &tamanio_actual;

	return abb_con_cada_elemento(arbol, recorrido, insertar_array, &aux);
}
