#include "abb.h"

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
