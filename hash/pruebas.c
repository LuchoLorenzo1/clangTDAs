#include "src/hash.h"
#include "src/hash.c"
#include "pa2m.h"

void pruebas_insercion()
{
	pa2m_nuevo_grupo("Pruebas de creacion e insercion");
	hash_t *dict = hash_crear(8);

	pa2m_afirmar(dict != NULL, "El hash se crea correctamente");
	pa2m_afirmar(hash_cantidad(dict) == 0,
		     "La cantidad de elementos de un hash vacio es 0");
	pa2m_afirmar(dict != NULL, "El hash se crea correctamente");
	pa2m_afirmar(
		hash_obtener(dict, "messi") == NULL,
		"Obtener una clave en un hash recien creado (vacio) es NULL");

	int a = 1, b = 2, c = 3, d = 4;
	pa2m_afirmar(hash_insertar(dict, "Messi", &a, NULL) != NULL,
		     "Se pudo insertar un elemento correctamente");

	hash_insertar(dict, "Fideo Di maria", &b, NULL);
	hash_insertar(dict, "De paul", &c, NULL);
	hash_insertar(dict, "Paredes", &d, NULL);

	pa2m_afirmar(hash_cantidad(dict) == 4,
		     "Cuando inserto se actualiza el tamanio correctamente");
	pa2m_afirmar(*(int *)hash_obtener(dict, "messi") == a,
		     "El valor de una clave insertada es correcta");
	pa2m_afirmar(*(int *)hash_obtener(dict, "Fideo Di maria") == b,
		     "El valor de una clave insertada es correcta");

	int **anterior;
	pa2m_afirmar(hash_insertar(dict, "Messi", &c, (void **)anterior) !=
			     NULL,
		     "Se pudo actualizar un elemento correctamente");
	pa2m_afirmar(
		*anterior == &c,
		"El elemento actualizado se devuelve asigna correctamente");
	pa2m_afirmar(*(int *)hash_obtener(dict, "messi") == c,
		     "El valor de la clave actualizada es la correcta");
	pa2m_afirmar(
		hash_cantidad(dict) == 4,
		"Despues de la actualizacion de la clave no cambia la cantidad de elementos");

	hash_t *comprobar = hash_insertar(dict, "Dibu martinez", &b, NULL);
	comprobar = hash_insertar(dict, "Cuti romero", &c, NULL);
	comprobar = hash_insertar(dict, "Otamendi", &d, NULL);
	comprobar = hash_insertar(dict, "El papu gomez", &a, NULL);
	comprobar = hash_insertar(dict, "Julian alvarez", &d, NULL);
	pa2m_afirmar(
		comprobar != NULL,
		"Se pudo agregar mas elementos de los indicados en un principio y no hay errores");
	pa2m_afirmar(
		hash_cantidad(dict) == 9,
		"La cantidad se actualizo correctamente luego de haber insertado mas elementos que los indicados en un principio");
	pa2m_afirmar(
		*(int *)hash_obtener(dict, "Fideo Di maria") == b,
		"El valor de una clave insertada antes de superar la cantidad indicada en un principio es correcta");
	pa2m_afirmar(
		*(int *)hash_obtener(dict, "Julian alvarez") == d,
		"El valor de una clave insertada despues de superar la cantidad indicada en un principio es correcta");
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de algo");

	return pa2m_mostrar_reporte();
}
