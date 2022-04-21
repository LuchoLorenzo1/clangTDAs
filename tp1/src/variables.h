#ifndef VARIABLES_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "estructuras.h"

#define MAX_LINEA 1024
#define ERROR -1
#define VACIO ""

/*
 *
 * Recibe un vector de punteros struct objeto dinamico, un puntero a elemento y la cantidad actual de elementos y agrega el elemento al vector.
 *
 * Esta función reserva memoria con realloc para un objeto mas y lo agrega.
 * El vector tendra que ser destruido con free
 *
 */
void agregar_vector_objetos(struct objeto ***vector, struct objeto *elemento, int *cantidad_actual);

/*
 *
 * Recibe un vector de punteros struct interacciones dinamico, un  y elementola cantidad actual de elementos y agrega el elemento al vector.
 *
 * Esta función reserva memoria con realloc para un objeto mas y lo agrega.
 * El vector tendra que ser destruido con free
 *
 */
void agregar_vector_interacciones(struct interaccion ***vector, struct interaccion *elemento, int *cantidad_actual);

#endif
