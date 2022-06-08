#include "src/hash.h"
#include "src/hash.c"
#include "pa2m.h"

void pruebas_insercion()
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
	pa2m_afirmar(*(int *)hash_obtener(diccionario_scaloneta, "messi") == a,
		     "El valor de una clave insertada es correcta");
	pa2m_afirmar(*(int *)hash_obtener(diccionario_scaloneta,
					  "Fideo Di maria") == b,
		     "El valor de una clave insertada es correcta");

	int **anterior;
	pa2m_afirmar(hash_insertar(diccionario_scaloneta, "Messi", &c,
				   (void **)anterior) != NULL,
		     "Se pudo actualizar un elemento correctamente");
	pa2m_afirmar(
		*anterior == &c,
		"El elemento actualizado se devuelve asigna correctamente");
	pa2m_afirmar(*(int *)hash_obtener(diccionario_scaloneta, "messi") == c,
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
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de algo");

	return pa2m_mostrar_reporte();
}
