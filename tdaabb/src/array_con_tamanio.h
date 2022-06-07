#include "abb.h"

typedef struct array_con_tamanio {
	void ***puntero_array_de_punteros;
	size_t max;
	size_t *act;
} arr_t;

/*
 * Se encarga de insertar un elemento en el struct array_con_tamanio,
 * el cual es pasado como void pointer. Devuelve false si no debe seguir
 * agregando elementos al array o true en caso contrario.
*/
bool insertar_array(void *elemento, void *array_con_tamanio);
