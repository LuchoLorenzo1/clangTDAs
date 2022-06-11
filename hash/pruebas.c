#include "src/hash.h"
#include "pa2m.h"
#include <stdlib.h>
#include <string.h>

void pruebas_creacion_insercion()
{
	pa2m_nuevo_grupo("Pruebas de creacion e insercion");
	hash_t *diccionario_scaloneta = hash_crear(8);

	pa2m_afirmar(diccionario_scaloneta != NULL,
		     "El hash se crea correctamente");
	pa2m_afirmar(hash_cantidad(diccionario_scaloneta) == 0,
		     "La cantidad de elementos de un hash vacio es 0");
	pa2m_afirmar(diccionario_scaloneta != NULL,
		     "El hash se crea correctamente");
	pa2m_afirmar(
		hash_obtener(diccionario_scaloneta, "messi") == NULL,
		"Obtener una clave en un hash recien creado (vacio) es NULL");

	int a = 1, b = 2, c = 3, d = 4;
	pa2m_afirmar(hash_insertar(diccionario_scaloneta, "Messi", &a, NULL) !=
			     NULL,
		     "Se pudo insertar un elemento correctamente");

	hash_insertar(diccionario_scaloneta, "Fideo Di maria", &b, NULL);
	hash_insertar(diccionario_scaloneta, "De paul", &c, NULL);
	hash_insertar(diccionario_scaloneta, "Paredes", &d, NULL);

	pa2m_afirmar(hash_cantidad(diccionario_scaloneta) == 4,
		     "Cuando inserto se actualiza el tamanio correctamente");
	pa2m_afirmar(*(int *)hash_obtener(diccionario_scaloneta, "Messi") == a,
		     "El valor de una clave insertada es correcta");
	pa2m_afirmar(*(int *)hash_obtener(diccionario_scaloneta,
					  "Fideo Di maria") == b,
		     "El valor de una clave insertada es correcta");

	int **anterior = calloc(1, sizeof(int **));
	if (!anterior)
		return;
	pa2m_afirmar(hash_insertar(diccionario_scaloneta, "Messi", &c,
				   (void **)anterior) != NULL,
		     "Se pudo actualizar un elemento correctamente");
	pa2m_afirmar(
		**anterior == a,
		"El elemento anterior al nuevo actualizado se asigna correctamente al puntero pasado por parametro");
	pa2m_afirmar(*(int *)hash_obtener(diccionario_scaloneta, "Messi") == c,
		     "El valor de la clave actualizada es la correcta");
	pa2m_afirmar(
		hash_cantidad(diccionario_scaloneta) == 4,
		"Despues de la actualizacion de la clave no cambia la cantidad de elementos");

	hash_t *comprobar =
		hash_insertar(diccionario_scaloneta, "Dibu martinez", &b, NULL);
	comprobar =
		hash_insertar(diccionario_scaloneta, "Cuti romero", &c, NULL);
	comprobar = hash_insertar(diccionario_scaloneta, "Otamendi", &d, NULL);
	comprobar =
		hash_insertar(diccionario_scaloneta, "El papu gomez", &a, NULL);
	comprobar = hash_insertar(diccionario_scaloneta, "Julian alvarez", &d,
				  NULL);

	pa2m_afirmar(
		comprobar != NULL,
		"Se pudo agregar mas elementos de los indicados en un principio y no hay errores");
	pa2m_afirmar(
		hash_cantidad(diccionario_scaloneta) == 9,
		"La cantidad se actualizo correctamente luego de haber insertado mas elementos que los indicados en un principio");
	pa2m_afirmar(
		*(int *)hash_obtener(diccionario_scaloneta, "Fideo Di maria") ==
			b,
		"El valor de una clave insertada antes de superar la cantidad indicada en un principio es correcta");
	pa2m_afirmar(
		*(int *)hash_obtener(diccionario_scaloneta, "Julian alvarez") ==
			d,
		"El valor de una clave insertada despues de superar la cantidad indicada en un principio es correcta");
	hash_destruir(diccionario_scaloneta);
	free(anterior);
}

void pruebas_quitar()
{
	pa2m_nuevo_grupo("Pruebas quitar");

	hash_t *dic_scaloneta = hash_crear(5);
	if (!dic_scaloneta)
		return;

	int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7;
	hash_insertar(dic_scaloneta, "Messi", &a, NULL);
	hash_insertar(dic_scaloneta, "Fideo Di maria", &b, NULL);
	hash_insertar(dic_scaloneta, "De paul", &c, NULL);
	hash_insertar(dic_scaloneta, "Paredes", &d, NULL);

	int *quitado = hash_quitar(dic_scaloneta, "Fideo Di maria");
	pa2m_afirmar(*quitado == b,
		     "Quitar un elemento devuelve el elemento quitado");
	pa2m_afirmar(
		hash_contiene(dic_scaloneta, "Fideo Di maria") == false,
		"Quitar un elemento y despues ver si el hash lo contiene devuelve false");
	pa2m_afirmar(hash_obtener(dic_scaloneta, "Fideo Di maria") == NULL,
		     "Quitar un elemento y despues buscarlo devuelve NULL");
	pa2m_afirmar(
		hash_cantidad(dic_scaloneta) == 3,
		"Quitar un elemento reduce la cantidad del hash correctamente");

	quitado = hash_quitar(dic_scaloneta, "Messi");
	pa2m_afirmar(*quitado == a,
		     "Quitar un elemento devuelve el elemento quitado");
	quitado = hash_quitar(dic_scaloneta, "De paul");
	pa2m_afirmar(*quitado == c,
		     "Quitar un elemento devuelve el elemento quitado");
	quitado = hash_quitar(dic_scaloneta, "Paredes");
	pa2m_afirmar(*quitado == d,
		     "Quitar un elemento devuelve el elemento quitado");

	pa2m_afirmar(hash_cantidad(dic_scaloneta) == 0,
		     "Vaciar el hash hace que la cantidad del hash sea 0");
	pa2m_afirmar(
		hash_contiene(dic_scaloneta, "Messi") == false,
		"Ver si contiene un elemento en un hash vacio devuelve false");

	hash_insertar(dic_scaloneta, "Messi", &a, NULL);
	hash_insertar(dic_scaloneta, "Fideo Di maria", &b, NULL);
	hash_insertar(dic_scaloneta, "De paul", &c, NULL);
	hash_insertar(dic_scaloneta, "Paredes", &d, NULL);
	hash_insertar(dic_scaloneta, "Guido rodriguez", &e, NULL);
	hash_insertar(dic_scaloneta, "lautaro martinez", &f, NULL);
	hash_insertar(dic_scaloneta, "otamendi", &g, NULL);

	quitado = hash_quitar(dic_scaloneta, "Messi");
	pa2m_afirmar(
		*quitado == a,
		"Sobrepasar la cantidad inicial y quitar un elemento lo devuelve correctamente");
	pa2m_afirmar(
		hash_contiene(dic_scaloneta, "Messi") == false,
		"Sobrepasar la cantidad inicial, quitar un elemento, y fijarse si lo contiene devuelve false");
	pa2m_afirmar(
		hash_obtener(dic_scaloneta, "Messi") == NULL,
		"Sobrepasar la cantidad inicial, quitar un elemento, y obtenerlo devuelve NULL");
	pa2m_afirmar(
		hash_cantidad(dic_scaloneta) == 6,
		"Sobrepasar la cantidad inicial, quitar un elemento, y la cantidad se actualiza correctamente");

	quitado = hash_quitar(dic_scaloneta, "De paul");
	pa2m_afirmar(*quitado == c,
		     "Quitar un elemento devuelve el elemento quitado");
	quitado = hash_quitar(dic_scaloneta, "Paredes");
	pa2m_afirmar(*quitado == d,
		     "Quitar un elemento devuelve el elemento quitado");

	hash_quitar(dic_scaloneta, "Fideo Di maria");
	hash_quitar(dic_scaloneta, "Guido rodriguez");
	hash_quitar(dic_scaloneta, "lautaro martinez");
	hash_quitar(dic_scaloneta, "otamendi");

	pa2m_afirmar(
		hash_cantidad(dic_scaloneta) == 0,
		"Vaciar el hash despues de haber sobrepasado la capacidad inicial, hace que la cantidad del hash sea 0");
	pa2m_afirmar(
		hash_contiene(dic_scaloneta, "otamendi") == false,
		"Ver si el hash contiene un elemento en un hash vacio devuelve false");
	pa2m_afirmar(hash_obtener(dic_scaloneta, "otamendi") == NULL,
		     "Obtener un elemento en un un hash vacio devuelve NULL");

	hash_destruir(dic_scaloneta);
}

bool duplica_elementos(const char *clave, void *elemento, void *aux)
{
	int *n = (int *)elemento;
	if (!n)
		return false;
	*n *= 2;
	return true;
}

void pruebas_iterador()
{
	pa2m_nuevo_grupo("Pruebas iterador");
	hash_t *dic_scaloneta = hash_crear(5);
	if (!dic_scaloneta)
		return;

	int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7;
	hash_insertar(dic_scaloneta, "Messi", &a, NULL);
	hash_insertar(dic_scaloneta, "Fideo Di maria", &b, NULL);
	hash_insertar(dic_scaloneta, "De paul", &c, NULL);

	size_t iterados =
		hash_con_cada_clave(dic_scaloneta, duplica_elementos, NULL);
	pa2m_afirmar(
		iterados == 3,
		"Iterar los elementos y la cantidad de elementos iterados devuelta es la correcta");
	pa2m_afirmar(a == 2,
		     "La funcion fue aplicada correctamente en un elemento");
	pa2m_afirmar(b == 4,
		     "La funcion fue aplicada correctamente en un elemento");
	pa2m_afirmar(c == 6,
		     "La funcion fue aplicada correctamente en un elemento");

	hash_insertar(dic_scaloneta, "Paredes", &d, NULL);
	hash_insertar(dic_scaloneta, "Guido rodriguez", &e, NULL);
	hash_insertar(dic_scaloneta, "lautaro martinez", &f, NULL);
	hash_insertar(dic_scaloneta, "otamendi", &g, NULL);

	iterados = hash_con_cada_clave(dic_scaloneta, duplica_elementos, NULL);
	pa2m_afirmar(
		iterados == 7,
		"Insertar mas elementos de los indicados incialmente, e iterar todos los elementos, devuelve la cantidad correcta");
	pa2m_afirmar(
		*(int *)hash_obtener(dic_scaloneta, "Paredes") == 8,
		"Obtengo un elemento del hash despue de haber sido modificado con el iterador y es el corecto");
	pa2m_afirmar(
		*(int *)hash_obtener(dic_scaloneta, "otamendi") == 14,
		"Obtengo un elemento del hash despue de haber sido modificado con el iterador y es el corecto");
	pa2m_afirmar(
		hash_cantidad(dic_scaloneta) == 7,
		"La cantidad del hash sigue siendo correcta luego de iterarlo.");

	hash_destruir(dic_scaloneta);
}

int main()
{
	pruebas_creacion_insercion();
	pruebas_quitar();
	pruebas_iterador();

	return pa2m_mostrar_reporte();
}
