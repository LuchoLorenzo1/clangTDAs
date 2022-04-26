#include "pila.h"
#include "lista.h"

pila_t *pila_crear()
{
	return (pila_t*) lista_crear();
}

pila_t *pila_apilar(pila_t *pila, void *elemento)
{
	return (pila_t*) lista_insertar((lista_t*)pila, elemento);
}

void *pila_desapilar(pila_t *pila)
{
	return lista_quitar((lista_t*)pila);
}

void *pila_tope(pila_t *pila)
{
	lista_t *lista = (lista_t*)pila;
	return lista->nodo_fin->elemento;
}

size_t pila_tamanio(pila_t *pila)
{
	lista_t *lista = (lista_t*)pila;
	return lista->cantidad;
}

bool pila_vacia(pila_t *pila)
{
	lista_t *lista = (lista_t*)pila;
	return !!lista->nodo_inicio;
}

void pila_destruir(pila_t *pila)
{
	lista_t *lista = (lista_t*)pila;
	lista_destruir(lista);
}
