#include "pila.h"
#include "lista.h"

pila_t *pila_crear()
{
	return (pila_t *)lista_crear();
}

pila_t *pila_apilar(pila_t *pila, void *elemento)
{
	return (pila_t *)lista_insertar_en_posicion((lista_t *)pila, elemento,
						    0);
}

void *pila_desapilar(pila_t *pila)
{
	return lista_quitar_de_posicion((lista_t *)pila, 0);
}

void *pila_tope(pila_t *pila)
{
	if (!pila)
		return NULL;
	lista_t *lista = (lista_t *)pila;
	if (!lista->nodo_inicio)
		return NULL;
	return lista->nodo_inicio->elemento;
}

size_t pila_tamanio(pila_t *pila)
{
	if (!pila)
		return 0;
	lista_t *lista = (lista_t *)pila;
	return lista->cantidad;
}

bool pila_vacia(pila_t *pila)
{
	lista_t *lista = (lista_t *)pila;
	if (!lista)
		return 0;
	return !lista->nodo_inicio;
}

void pila_destruir(pila_t *pila)
{
	lista_destruir((lista_t *)pila);
}
