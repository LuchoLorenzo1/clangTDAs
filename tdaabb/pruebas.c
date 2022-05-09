#include "src/abb.h"
#include <stdio.h>
#include "pa2mm.h"
#include "string.h"

int comparador_enteros(void *elemento1, void *elemento2)
{
	int n1 = *(int *)elemento1;
	int n2 = *(int *)elemento2;

	if (n1 == n2)
		return 0;
	if (n1 > n2)
		return 1;
	else
		return -1;
}

bool mostrar(void *elemento1, void *aux)
{
	int n1 = *(int *)elemento1;
	printf("%d\n", n1);
	return true;
}

void pruebas_creacion_e_insercion()
{
	pa2m_nuevo_grupo("Pruebas creacion e insercion");

	abb_t *arbol = abb_crear(comparador_enteros);
	pa2m_afirmar(!!arbol, "No hay errores al crear el arbol");
	pa2m_afirmar(abb_vacio(arbol), "Un arbol recien creado eta vacio");
	pa2m_afirmar(abb_tamanio(arbol) == 0,
		     "El tamanio de un arbol recien creado es 0");

	int a = 10;
	int b = 11;
	int c = 7;
	int d = 8;
	int e = 6;

	arbol = abb_insertar(arbol, &a);
	pa2m_afirmar(!abb_vacio(arbol),
		     "agregar un elemento hace que no este vacio el arbol");
	pa2m_afirmar(
		abb_tamanio(arbol) == 1,
		"agregar un elemento hace que el tamanio del arbol aumente correctamente");

	arbol = abb_insertar(arbol, &b);
	pa2m_afirmar(
		!!arbol,
		"agregar un elemento mayor al elemento raiz se agrega correctamente");
	pa2m_afirmar(
		abb_tamanio(arbol) == 2,
		"agregar un elemento hace que el tamanio del arbol aumente correctamente");

	arbol = abb_insertar(arbol, &c);
	pa2m_afirmar(
		!!arbol,
		"agregar un elemento menor al elemento raiz se agrega correctamente");
	pa2m_afirmar(
		abb_tamanio(arbol) == 3,
		"agregar un elemento hace que el tamanio del arbol aumente correctamente");

	arbol = abb_insertar(arbol, &d);
	arbol = abb_insertar(arbol, &e);

	pa2m_afirmar(
		abb_insertar(arbol, NULL) == NULL,
 		"agregar un elemento NULL devuelve NULL");
	pa2m_afirmar(
		abb_tamanio(arbol) == 5,
 		"agregar un elemento NULL no cambia el tamanio del arbol");
	pa2m_afirmar(
		abb_insertar(NULL, &d) == NULL,
 		"Agregar a un arbol NULL devuelve NULL");

	/* printf("%d\n", *(int*)arbol->nodo_raiz->izquierda->elemento); */
	/* printf("%d\n", *(int*)arbol->nodo_raiz->izquierda->izquierda->elemento); */
	/* printf("%d\n", *(int*)arbol->nodo_raiz->izquierda->derecha->elemento); */
	/* printf("%d\n", *(int*)arbol->nodo_raiz->derecha->elemento); */

	/* printf("INORDEN\n"); */
	/* abb_con_cada_elemento(arbol, INORDEN, mostrar, NULL); */
	/* printf("PREORDEN\n"); */
	/* abb_con_cada_elemento(arbol, PREORDEN, mostrar, NULL); */
	/* printf("POSTORDEN\n"); */
	/* abb_con_cada_elemento(arbol, POSTORDEN, mostrar, NULL); */

	abb_destruir(arbol);
}

void pruebas_quitar()
{
	pa2m_nuevo_grupo("Pruebas quitar");
	abb_t *arbol = abb_crear(comparador_enteros);

	int a = 10, b = 11, c = 7 , d = 8 , e = 8 , f = 8 , g = 8 , h = 8 , i = 6;

	abb_insertar(arbol, &a);
	abb_insertar(arbol, &b);
	abb_insertar(arbol, &c);
	abb_insertar(arbol, &d);
	abb_insertar(arbol, &e);
	abb_insertar(arbol, &e);
	abb_insertar(arbol, &e);

	int *quitado_hoja = (int*)abb_quitar(arbol, &e);
	pa2m_afirmar(quitado_hoja == &e, "Quitar una hoja devuelve el elemento de la hoja correctamente");
	pa2m_afirmar(abb_buscar(arbol, &e) == NULL, "Buscar el elemento de la hoja quitada devuelve NULL (no hay otro repetido)");
	pa2m_afirmar(abb_tamanio(arbol) == 4, "Quitar un elemento reduce el tamanio correctamente");

	int *quitado_normal = (int*)abb_quitar(arbol, &c);
	pa2m_afirmar(quitado_normal == &c, "Quitar una nodo devuelve el elemento del nodo correctamente");
	pa2m_afirmar(abb_buscar(arbol, &c) == NULL, "Buscar el elemento quitado devuelve NULL (no hay otro repetido)");
	pa2m_afirmar(abb_tamanio(arbol) == 4, "Quitar un elemento reduce el tamanio correctamente");

	int *quitado_raiz = (int*)abb_quitar(arbol, &a);
	pa2m_afirmar(quitado_raiz == &a, "Quitar la raiz devuelve el elemento del nodo correctamente");
	pa2m_afirmar(abb_buscar(arbol, &a) == NULL, "Buscar el elemento de la raiz quitada devuelve NULL (no hay otro repetido)");
	pa2m_afirmar(abb_tamanio(arbol) == 3, "Quitar un elemento reduce el tamanio correctamente");

	abb_destruir(arbol);
}


int main()
{
	pa2m_nuevo_grupo("Pruebas de ABB");

	pruebas_creacion_e_insercion();

	return pa2m_mostrar_reporte();
}
