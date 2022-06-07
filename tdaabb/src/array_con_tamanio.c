#include "abb.h"
#include "array_con_tamanio.h"

bool insertar_array(void *elemento, void *array_con_tamanio)
{
	arr_t aux = *(arr_t *)array_con_tamanio;

	void **array_de_punteros = *aux.puntero_array_de_punteros;

	array_de_punteros[*aux.act] = elemento;
	(*aux.act)++;

	if (*aux.act == aux.max)
		return false;
	return true;
}
