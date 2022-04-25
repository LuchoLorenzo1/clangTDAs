#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa2m.h"

void pruebas_de_creacion()
{
        pa2m_nuevo_grupo("Pruebas de creacion");

	lista_t *lista = lista_crear();

	int primero = 2;
	int segundo = 3;

	lista_insertar(lista,&primero);
	lista_insertar(lista,&segundo);

	pa2m_afirmar(!!lista, "Lista creada con exito");
	pa2m_afirmar((int*)lista_elemento_en_posicion(lista, 0) == &primero, "El primer elemento que inserte, es el primero en la lista");
	pa2m_afirmar((int*)lista_elemento_en_posicion(lista, 1) == &segundo, "El segundo elemento que inserte, es el segundo en la lista");

	int tercero = 4;
	lista_insertar_en_posicion(lista,&tercero,0);
	pa2m_afirmar((int*)lista_elemento_en_posicion(lista, 0) == &tercero, "Inserto un elemento en el inicio de la lista y es el primero");

	lista_destruir(lista);
}


int main() {
        pruebas_de_creacion();
        return pa2m_mostrar_reporte();
}
