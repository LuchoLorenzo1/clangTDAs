#include "cola.h"
#include "lista.h"

cola_t *cola_crear()
{
	return (cola_t *)lista_crear();
}

cola_t *cola_encolar(cola_t *cola, void *elemento)
{
	return (cola_t *)lista_insertar((lista_t *)cola, elemento);
}

void *cola_desencolar(cola_t *cola)
{
	return lista_quitar_de_posicion((lista_t *)cola, 0);
}

void *cola_frente(cola_t *cola)
{
	if (!cola)
		return NULL;
	lista_t *lista = (lista_t *)cola;
	if (!lista->nodo_inicio)
		return NULL;
	return lista->nodo_inicio->elemento;
}

size_t cola_tamanio(cola_t *cola)
{
	if (!cola)
		return 0;
	lista_t *lista = (lista_t *)cola;
	return lista->cantidad;
}

bool cola_vacia(cola_t *cola)
{
	if (!cola)
		return true;
	lista_t *lista = (lista_t *)cola;
	return !lista->nodo_inicio;
}

void cola_destruir(cola_t *cola)
{
	free((lista_t *)cola);
}
