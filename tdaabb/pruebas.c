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

bool triplicar_elementos(void *elemento1, void *aux)
{
	int *n1 = (int *)elemento1;
	*n1 = *n1 * 3;
	return true;
}

void pruebas_creacion_e_insercion()
{
	pa2m_nuevo_grupo("Pruebas creacion e insercion");

	abb_t *arbol = abb_crear(comparador_enteros);
	pa2m_afirmar(!!arbol, "No hay errores al crear el arbol");
	pa2m_afirmar(abb_vacio(arbol), "Un arbol recien creado eta vacio");
	pa2m_afirmar(abb_tamanio(arbol) == 0,
		     "El tamaño de un arbol recien creado es 0");

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
		"agregar un elemento hace que el tamaño del arbol aumente correctamente");

	arbol = abb_insertar(arbol, &b);
	pa2m_afirmar(
		!!arbol,
		"agregar un elemento mayor al elemento raiz se agrega correctamente");
	pa2m_afirmar(
		abb_tamanio(arbol) == 2,
		"agregar un elemento hace que el tamaño del arbol aumente correctamente");

	arbol = abb_insertar(arbol, &c);
	pa2m_afirmar(
		!!arbol,
		"agregar un elemento menor al elemento raiz se agrega correctamente");
	pa2m_afirmar(
		abb_tamanio(arbol) == 3,
		"agregar un elemento hace que el tamaño del arbol aumente correctamente");

	arbol = abb_insertar(arbol, &d);
	arbol = abb_insertar(arbol, &e);

	pa2m_afirmar(abb_insertar(arbol, NULL) == NULL,
		     "agregar un elemento NULL devuelve NULL");
	pa2m_afirmar(abb_tamanio(arbol) == 5,
		     "agregar un elemento NULL no cambia el tamaño del arbol");
	pa2m_afirmar(abb_insertar(NULL, &d) == NULL,
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

	int a = 50, b = 60, c = 70, d = 55, e = 54, f = 52, g = 53, h = 51,
	    i = 56;

	abb_insertar(arbol, &a);
	abb_insertar(arbol, &b);
	abb_insertar(arbol, &c);
	abb_insertar(arbol, &d);
	abb_insertar(arbol, &e);
	abb_insertar(arbol, &f);
	abb_insertar(arbol, &g);
	abb_insertar(arbol, &h);
	abb_insertar(arbol, &i);

	int *quitado_hoja = (int *)abb_quitar(arbol, &i);
	pa2m_afirmar(
		quitado_hoja == &i,
		"Quitar una hoja devuelve el elemento de la hoja correctamente");
	pa2m_afirmar(
		abb_buscar(arbol, &i) == NULL,
		"Buscar el elemento de la hoja quitada devuelve NULL (si no hay otro repetido)");
	pa2m_afirmar(abb_tamanio(arbol) == 8,
		     "Quitar un elemento reduce el tamaño correctamente");

	abb_insertar(arbol, &i);

	int *quitado_complicado = (int *)abb_quitar(arbol, &b);
	pa2m_afirmar(
		quitado_complicado == &b,
		"Quitar una nodo devuelve el elemento del nodo correctamente");
	pa2m_afirmar(
		abb_buscar(arbol, &b) == NULL,
		"Buscar el elemento quitado devuelve NULL (si no hay otro repetido)");
	pa2m_afirmar(abb_tamanio(arbol) == 8,
		     "Quitar un elemento reduce el tamaño correctamente");

	int *quitado_raiz = (int *)abb_quitar(arbol, &a);
	pa2m_afirmar(
		quitado_raiz == &a,
		"Quitar la raiz devuelve el elemento del nodo correctamente");
	pa2m_afirmar(
		abb_buscar(arbol, &a) == NULL,
		"Buscar el elemento de la raiz quitada devuelve NULL (no hay otro repetido)");
	pa2m_afirmar(abb_tamanio(arbol) == 7,
		     "Quitar un elemento reduce el tamaño correctamente");

	int *quitado = abb_quitar(arbol, &b);
	pa2m_afirmar(
		quitado == NULL,
		"Intentar quitar un elemento que no esta en el arbol devuelve NULL");
	pa2m_afirmar(
		abb_tamanio(arbol) == 7,
		"Intentar quitar un elemento que no esta en el arbol NO reduce el tamaño");

	abb_destruir(arbol);
}

void pruebas_recorrer()
{
	pa2m_nuevo_grupo("Pruebas recorrer");
	abb_t *arbol = abb_crear(comparador_enteros);

	int a = 50, b = 60, c = 70, d = 55, e = 40, f = 52, g = 45, h = 51,
	    i = 56;
	abb_insertar(arbol, &a);
	abb_insertar(arbol, &b);
	abb_insertar(arbol, &c);
	abb_insertar(arbol, &d);
	abb_insertar(arbol, &e);
	abb_insertar(arbol, &f);
	abb_insertar(arbol, &g);
	abb_insertar(arbol, &h);
	abb_insertar(arbol, &i);

	int inorden[9] = { 40, 45, 50, 51, 52, 55, 56, 60, 70 };
	int postorden[9] = { 45, 40, 51, 52, 56, 55, 70, 60, 50 };
	int preorden[9] = { 50, 40, 45, 60, 55, 52, 51, 56, 70 };

	pa2m_afirmar(abb_tamanio(arbol) == 9,
		     "El tamaño del arbol es correcto");
	int *elementos[10];
	size_t cantidad = abb_recorrer(arbol, INORDEN, (void **)elementos, 9);
	pa2m_afirmar(
		cantidad == 9,
		"Recorrer el arbol con inorden devuelve el tamaño correcto");
	bool recorrido = true;
	for (size_t i = 0; i < cantidad; i++)
		if (*(int *)elementos[i] != inorden[i]) {
			recorrido = false;
			break;
		}
	pa2m_afirmar(
		recorrido,
		"El recorrido inorden llamando a la función abb_recorrer es el correcto");

	int *elementos2[10];
	cantidad = abb_recorrer(arbol, PREORDEN, (void **)elementos2, 9);
	pa2m_afirmar(
		cantidad == 9,
		"Recorrer el arbol con preorden devuelve el tamaño correcto");
	recorrido = true;
	for (size_t i = 0; i < cantidad; i++)
		if (*(int *)elementos2[i] != preorden[i]) {
			recorrido = false;
			break;
		}
	pa2m_afirmar(
		recorrido,
		"El recorrido preorden llamando a la función abb_recorrer es el correcto");

	int *elementos3[10];
	cantidad = abb_recorrer(arbol, POSTORDEN, (void **)elementos3, 9);
	pa2m_afirmar(
		cantidad == 9,
		"Recorrer el arbol con postorden devuelve el tamaño correcto");
	recorrido = true;
	for (size_t i = 0; i < cantidad; i++)
		if (*(int *)elementos3[i] != postorden[i]) {
			recorrido = false;
			break;
		}
	pa2m_afirmar(
		recorrido,
		"El recorrido postorden llamando a la función abb_recorrer es el correcto");

	cantidad =abb_con_cada_elemento(arbol, PREORDEN, triplicar_elementos, NULL);
	pa2m_afirmar(
		cantidad == 9,
		"Recorrer el arbol con la funcion abb_con_cada_elemento devuelve el tamaño correcto");

	int *elementos4[10];
	cantidad = abb_recorrer(arbol, PREORDEN, (void **)elementos4, 9);
	recorrido = true;
	for (size_t i = 0; i < cantidad; i++)
		if (*(int *)elementos4[i] != preorden[i]*3) {
			recorrido = false;
			break;
		}
	pa2m_afirmar(
		recorrido,
		"Utilizo la funcion abb_con_cada_elemento para triplicar todos los elementos y funciona perfectamente");

	cantidad = abb_recorrer(arbol, PREORDEN, (void **)elementos4, 9);
	pa2m_afirmar(
		recorrido,
		"Utilizo la funcion abb_con_cada_elemento para triplicar todos los elementos y funciona perfectamente");

	abb_destruir(arbol);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de ABB");

	pruebas_creacion_e_insercion();
	pruebas_quitar();
	pruebas_recorrer();

	return pa2m_mostrar_reporte();
}
