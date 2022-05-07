#include "abb.h"
#include <stddef.h>
#include <stdlib.h>

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
	int n = comparador(elemento, nodo->elemento);
	if (n <= 0) {
		nodo_abb_t *nuevo_nodo = insertar_recursivo(
			nodo->izquierda, elemento, comparador);
		if (!nuevo_nodo)
			return NULL;
		nodo->izquierda = nuevo_nodo;
	} else {
		nodo_abb_t *nuevo_nodo = insertar_recursivo(
			nodo->izquierda, elemento, comparador);
		if (!nuevo_nodo)
			return NULL;
		nodo->derecha = nuevo_nodo;
	}
	return nodo;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if (!arbol)
		return NULL;

	if (!arbol->nodo_raiz) {
		nodo_abb_t *raiz = malloc(sizeof(nodo_abb_t));
		if (!raiz)
			return NULL;
		raiz->derecha = NULL;
		raiz->izquierda = NULL;
		raiz->elemento = elemento;
		arbol->nodo_raiz = raiz;
		arbol->tamanio++;
		return arbol;
	}

	nodo_abb_t *raiz = insertar_recursivo(arbol->nodo_raiz, elemento,
					      arbol->comparador);
	if (!raiz)
		return NULL;
	arbol->tamanio++;
	return arbol;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	return NULL;
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	return NULL;
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

void abb_destruir(abb_t *arbol)
{
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
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

	size_t izq = recorrer_inorden(nodo->izquierda, funcion, aux, continuar);
	if (!*continuar)
		return izq + 1;

	size_t der = recorrer_inorden(nodo->derecha, funcion, aux, continuar);
	return izq + der + 1;
}

size_t recorrer_postorden(nodo_abb_t *nodo, bool (*funcion)(void *, void *),
			  void *aux, bool *continuar)
{
	if (!nodo)
		return 0;

	size_t izq = recorrer_inorden(nodo->izquierda, funcion, aux, continuar);
	if (!*continuar)
		return izq;

	size_t der = recorrer_inorden(nodo->derecha, funcion, aux, continuar);
	if (!*continuar)
		return izq + der;

	*continuar = funcion(nodo->elemento, aux);
	return izq + der + 1;
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	bool t = true;
	switch (recorrido) {
	case INORDEN:
		return recorrer_inorden(arbol->nodo_raiz, funcion, aux, &t);
	case PREORDEN:
		return recorrer_preorden(arbol->nodo_raiz, funcion, aux, &t);
	case POSTORDEN:
		return recorrer_postorden(arbol->nodo_raiz, funcion, aux, &t);
	default:
		return 0;
	}
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	switch (recorrido) {
	case INORDEN:
		break;
	case PREORDEN:
		break;
	case POSTORDEN:
		break;
	default:
		break;
	}

	return 0;
}
