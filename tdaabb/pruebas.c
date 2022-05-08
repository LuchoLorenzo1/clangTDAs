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
	pa2m_afirmar(!!arbol, "Creo un arbol y no hay errores");
	pa2m_afirmar(abb_vacio(arbol), "Creo un arbol y esta vacio");
	pa2m_afirmar(abb_tamanio(arbol) == 0,
		     "Creo un arbol y su tamanio es 0");

	int a = 10;
	int b = 11;
	int c = 7;
	int d = 8;
	int e = 6;
	int f = 12;
	int g = 15;
	int h = 13;

	arbol = abb_insertar(arbol, &a);
	pa2m_afirmar(!abb_vacio(arbol),
		     "Agrego un elemento y ya no esta vacio el arbol");
	pa2m_afirmar(
		abb_tamanio(arbol) == 1,
		"Agrego un elemento y el tamanio del arbol aumenta correctamente");

	arbol = abb_insertar(arbol, &b);
	pa2m_afirmar(
		!!arbol,
		"Agrego un elemento mayor al elemento raiz y se agrega correctamente");
	pa2m_afirmar(
		abb_tamanio(arbol) == 2,
		"Agrego un elemento y el tamanio del arbol aumenta correctamente");

	arbol = abb_insertar(arbol, &c);
	pa2m_afirmar(
		!!arbol,
		"Agrego un elemento menor al elemento raiz y se agrega correctamente");
	pa2m_afirmar(
		abb_tamanio(arbol) == 3,
		"Agrego un elemento y el tamanio del arbol aumenta correctamente");

	arbol = abb_insertar(arbol, &d);
	arbol = abb_insertar(arbol, &e);
	arbol = abb_insertar(arbol, &f);
	arbol = abb_insertar(arbol, &g);
	arbol = abb_insertar(arbol, &h);

	/* printf("%d\n", *(int*)arbol->nodo_raiz->izquierda->elemento); */
	/* printf("%d\n", *(int*)arbol->nodo_raiz->izquierda->izquierda->elemento); */
	/* printf("%d\n", *(int*)arbol->nodo_raiz->izquierda->derecha->elemento); */
	/* printf("%d\n", *(int*)arbol->nodo_raiz->derecha->elemento); */

	printf("INORDEN\n");
	abb_con_cada_elemento(arbol, INORDEN, mostrar, NULL);
	printf("PREORDEN\n");
	abb_con_cada_elemento(arbol, PREORDEN, mostrar, NULL);
	printf("POSTORDEN\n");
	abb_con_cada_elemento(arbol, POSTORDEN, mostrar, NULL);

}
int main()
{
	pa2m_nuevo_grupo("Pruebas de ABB");

	pruebas_creacion_e_insercion();

	return pa2m_mostrar_reporte();
}
