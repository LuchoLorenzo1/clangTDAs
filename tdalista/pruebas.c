#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa2m.h"

void pruebas_creacion_insercion()
{
	pa2m_nuevo_grupo("Pruebas de creacion e insercion");

	lista_t *lista = lista_crear();

	pa2m_afirmar(!!lista, "Lista creada con exito");

	pa2m_afirmar(lista_tamanio(lista) == 0,
		     "La lista esta vacia por defecto");

	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == NULL,
		     "El primer elemento es nulo");

	int a = 1, b = 2, c = 3, d = 4, e = 5;

	lista_insertar(lista, &a);
	lista_insertar(lista, &b);

	pa2m_afirmar(
		(int *)lista_elemento_en_posicion(lista, 0) == &a,
		"El primer elemento que inserte, es el primero en la lista");

	pa2m_afirmar(
		(int *)lista_elemento_en_posicion(lista, 1) == &b,
		"El segundo elemento que inserte, es el segundo en la lista");

	lista_insertar_en_posicion(lista, &c, 0);
	pa2m_afirmar(
		(int *)lista_elemento_en_posicion(lista, 0) == &c,
		"Inserto un elemento en el inicio de la lista y es el primero");

	lista_insertar_en_posicion(lista, &d, 2);
	pa2m_afirmar(
		(int *)lista_elemento_en_posicion(lista, 2) == &d,
		"Inserto elemento en la posicion 2 y esta en la posicion 2");

	lista_insertar_en_posicion(lista, &e, 100);
	pa2m_afirmar(
		(int *)lista_elemento_en_posicion(lista, 5) == &e,
		"Inserto un elemento en una posicion muy grande, y es el ultimo elemento");

	/* printf("%d\n",*(int*)lista->nodo_inicio->elemento); */
	/* printf("%d\n",*(int*)lista->nodo_inicio->siguiente->elemento); */
	/* printf("%d\n",*(int*)lista->nodo_inicio->siguiente->siguiente->elemento); */
	/* printf("%d\n",*(int*)lista->nodo_inicio->siguiente->siguiente->siguiente->elemento); */
	/* printf("%d\n",*(int*)lista->nodo_inicio->siguiente->siguiente->siguiente->siguiente->elemento); */

	pa2m_afirmar(lista_tamanio(lista) == 5,
		     "El tamanio de la lista es 5 elementos");

	lista_destruir(lista);
}

void pruebas_quitar()
{
	pa2m_nuevo_grupo("Pruebas de quitar");
	lista_t *lista = lista_crear();

	int a = 1, b = 2, c = 3, d = 4, e = 5;
	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	lista_insertar(lista, &c);
	lista_insertar(lista, &d);
	lista_insertar(lista, &e);

	int *entero = lista_quitar(lista);
	pa2m_afirmar(
		entero == &e,
		"Quito el ultimo elemento y es el que devuelve la funcion");
	pa2m_afirmar(
		lista_elemento_en_posicion(lista, lista_tamanio(lista) - 1) ==
			&d,
		"Quito el ultimo elemento y ahora el ultimo elemento de la lista es el anteultimo");
	pa2m_afirmar(
		lista_tamanio(lista) == 4,
		"Quito el ultimo elemento y el tamanio de la lista es 1 menos");

	entero = (int *)lista_quitar_de_posicion(lista, 0);
	pa2m_afirmar(entero == &a,
		     "Quito el primer elemento y es el que devuelve la funcion");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == &b,
		     "Quito el primero y el ahora primero es el segundo");

	int f = 28;
	lista_insertar_en_posicion(lista, &f, 1);
	entero = (int*)lista_quitar_de_posicion(lista, 1);
	pa2m_afirmar(
		entero == &f,
		"Agrego un elemento, lo quito y devuelve el mismo elemento");

	lista_destruir(lista);
}

void pruebas_listas()
{
	pruebas_creacion_insercion();
	pruebas_quitar();
}

int main()
{
	pruebas_listas();
	return pa2m_mostrar_reporte();
}
