#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa2m.h"

bool sumar(void *elemento, void *contexto)
{
	int *suma = (int *)contexto;
	*suma += *(int *)elemento;
	return true;
}

bool sumar_hasta_encontrar_un_5(void *elemento, void *contexto)
{
	if(*(int*)elemento == 5) 
		return false;
	int *suma = (int *)contexto;
	*suma += *(int *)elemento;
	return true;
}
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
		(int *)lista_elemento_en_posicion(lista, lista_tamanio(lista) -
								 1) == &e,
		"Inserto un elemento en una posicion muy grande, y es el ultimo elemento");

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
	pa2m_afirmar(
		entero == &a,
		"Quito el primer elemento y es el que devuelve la funcion");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == &b,
		     "Quito el primero y el ahora primero es el segundo");

	int f = 28;
	lista_insertar_en_posicion(lista, &f, 1);
	entero = (int *)lista_quitar_de_posicion(lista, 1);
	pa2m_afirmar(
		entero == &f,
		"Agrego un elemento, lo quito y devuelve el mismo elemento");

	lista_quitar(lista);
	lista_quitar(lista);
	lista_quitar(lista);

	pa2m_afirmar(lista_vacia(lista),
		     "Quito todos los elementos y la lista esta vacia");

	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	lista_quitar(lista);
	entero = (int *)lista_quitar(lista);
	pa2m_afirmar(
		entero == &a,
		"Vuelvo a agregar dos elementos, los quito y el ultimo que quito es el primero que agregue");
	pa2m_afirmar(lista_vacia(lista),
		     "Vuelvo a vaciar la lista y esta vacia");
	pa2m_afirmar(lista_tamanio(lista) == 0, "El tamaño de la lista es 0");
	lista_destruir(lista);
}

void pruebas_iterador()
{
	pa2m_nuevo_grupo("Pruebas iterador lista");

	lista_t *lista = lista_crear();
	int a = 1, b = 2, c = 3, d = 4, e = 5;
	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	lista_insertar(lista, &c);
	lista_insertar(lista, &d);
	lista_insertar(lista, &e);

	lista_iterador_t *it;
	int suma = 0;

	for (it = lista_iterador_crear(lista);
	     lista_iterador_tiene_siguiente(it); lista_iterador_avanzar(it)) {
		suma += *(int *)lista_iterador_elemento_actual(it);
	}

	pa2m_afirmar(
		suma == 15,
		"Sumo todos los elementos de la lista con un iterador externo y el resultado es correcto");

	bool t = lista_iterador_tiene_siguiente(it);
	pa2m_afirmar(
		!t,
		"Fijarse si el iterador tiene siguiente cuando itere toda la lista tiene que ser false");

	t = lista_iterador_avanzar(it);
	pa2m_afirmar(
		!t,
		"Intento avanzar el iterador cuando itere toda la lista y me la funcion me devuelve false");

	t = lista_iterador_avanzar(it);
	pa2m_afirmar(
		!t,
		"Intento avanzar el iterador cuando itere toda la lista y me la funcion me devuelve false");

	lista_iterador_destruir(it);

	suma = 0;
	int *psuma = &suma;
	lista_con_cada_elemento(lista, sumar, (void *)psuma);
	
	pa2m_afirmar(
		*psuma == 15,
		"Sumo todos los elementos de la lista con un iterador interno y el resultado es correcto");

	*psuma = 0;
	lista_con_cada_elemento(lista, sumar_hasta_encontrar_un_5, (void *)psuma);

	pa2m_afirmar(
		*psuma == 10,
		"Sumo todos los elementos de la lista con un iterador interno y una funcion que para antes del final y el resultado es correcto");

	lista_destruir(lista);
}

void pruebas_pilas()
{
	pa2m_nuevo_grupo("Pruebas con pilas");

	pila_t *pila = pila_crear();
	
	pa2m_afirmar(!!pila, "la pila se crea sin ningun error");
	pa2m_afirmar(pila_vacia(pila), "La pila esta vacia cuando recien la creo");
	pa2m_afirmar(pila_tope(pila) == NULL, "Si intento ver el tope con la pila vacia el resultado es NULL");

	char string[] = {'i','s','s','e','m'};
	for (int i = 0; i < 5; i++) {
		pila_apilar(pila, &string[i]);
	}

	pa2m_afirmar(*(char *)pila_tope(pila) == 'm', "Apilo elementos y el tope es el correcto");
	pa2m_afirmar(pila_tamanio(pila) == 5, "El tamaño de la pila es la cantidad de elementos que agregue");

	char c = *(char*)pila_desapilar(pila);
	pa2m_afirmar(c == 'm', "desapilo y el elemento es el correcto");
	c = *(char*)pila_desapilar(pila);
	pa2m_afirmar(c == 'e', "desapilo y el elemento es el correcto");
	c = *(char*)pila_desapilar(pila);
	pa2m_afirmar(c == 's', "desapilo y el elemento es el correcto");
	c = *(char*)pila_desapilar(pila);
	pa2m_afirmar(c == 's', "desapilo y el elemento es el correcto");
	c = *(char*)pila_desapilar(pila);
	pa2m_afirmar(c == 'i', "desapilo y el elemento es el correcto");

	pa2m_afirmar(pila_vacia(pila), "La pila no tiene ningun elemento, por lo que esta vacia");
	pa2m_afirmar(pila_tamanio(pila) == 0, "El tamanio de la pila es 0 cuando esta vacia");

	void *elemento = pila_desapilar(pila);
	pa2m_afirmar(elemento == NULL, "Si desapilo con la pila vacia devuelve NULL");

	pila_destruir(pila);
}
void pruebas_colas()
{
	pa2m_nuevo_grupo("Pruebas con colas");

	cola_t *cola = cola_crear();
	
	pa2m_afirmar(!!cola, "la cola se crea sin ningun error");
	pa2m_afirmar(cola_vacia(cola), "La cola esta vacia cuando recien la creo");
	pa2m_afirmar(cola_frente(cola) == NULL, "Si intento ver el tope con la cola vacia el resultado es NULL");

	char string[] = {'i','s','s','e','m'};
	for (int i = 0; i < 5; i++) {
		cola_encolar(cola, &string[i]);
	}

	pa2m_afirmar(*(char *)cola_frente(cola) == 'i', "Encolo elementos y el frente es el correcto");
	pa2m_afirmar(cola_tamanio(cola) == 5, "El tamaño de la cola es la cantidad de elementos que agregue");

	char c = *(char*)cola_desencolar(cola);
	pa2m_afirmar(c == 'i', "desencolo y el elemento es el correcto");
	c = *(char*)cola_desencolar(cola);
	pa2m_afirmar(c == 's', "desencolo y el elemento es el correcto");
	c = *(char*)cola_desencolar(cola);
	pa2m_afirmar(c == 's', "desencolo y el elemento es el correcto");
	c = *(char*)cola_desencolar(cola);
	pa2m_afirmar(c == 'e', "desencolo y el elemento es el correcto");
	c = *(char*)cola_desencolar(cola);
	pa2m_afirmar(c == 'm', "desencolo y el elemento es el correcto");

	pa2m_afirmar(cola_vacia(cola), "La cola no tiene ningun elemento y esta vacia");
	pa2m_afirmar(cola_tamanio(cola) == 0, "El tamanio de la cola es 0 cuando esta vacia");

	void *elemento = cola_desencolar(cola);
	pa2m_afirmar(elemento == NULL, "Si desencolo con la cola vacia devuelve NULL");

	cola_destruir(cola);
}
int main()
{
	pruebas_creacion_insercion();
	pruebas_quitar();
	pruebas_iterador();
	pruebas_pilas();
	pruebas_colas();
	return pa2m_mostrar_reporte();
}
