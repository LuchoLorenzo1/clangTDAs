#include "estructuras.h"
#include "interaccion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct interaccion *interaccion_crear_desde_string(const char *string)
{

	if (string == NULL || strcmp(string, "") == 0)
		return NULL;

	char objeto[MAX_NOMBRE];
	char verbo[MAX_VERBO];
	char objeto_parametro[MAX_NOMBRE];
	struct accion nueva_accion;

	char tipo_accion[2];
	enum tipo_accion tipo;
	char nombre_objeto_accion[MAX_NOMBRE];
	char mensaje[MAX_TEXTO];

	int strings_obtenidas =
		sscanf(string, "%[^;];%[^;];%[^;];%[^:]:%[^:]:%[^\n]\n", objeto,
		       verbo, objeto_parametro, tipo_accion,
		       nombre_objeto_accion, mensaje);

	if (strings_obtenidas != 6 || strlen(tipo_accion) != 1)
		return NULL;

	if (strcmp(objeto_parametro, "_") == 0)
		strcpy(objeto_parametro, "");

	if (strcmp(nombre_objeto_accion, "_") == 0)
		strcpy(nombre_objeto_accion, "");

	switch (tipo_accion[0]) {
	case 'r':
		tipo = REEMPLAZAR_OBJETO;
		break;
	case 'd':
		tipo = DESCUBRIR_OBJETO;
		break;
	case 'e':
		tipo = ELIMINAR_OBJETO;
		break;
	case 'm':
		tipo = MOSTRAR_MENSAJE;
		break;
	default:
		tipo = ACCION_INVALIDA;
		break;
	}

	struct interaccion *nueva_interaccion =
		malloc(sizeof(struct interaccion));

	if (nueva_interaccion == NULL)
		return NULL;

	strcpy(nueva_accion.objeto, nombre_objeto_accion);
	strcpy(nueva_accion.mensaje, mensaje);
	nueva_accion.tipo = tipo;

	strcpy(nueva_interaccion->objeto, objeto);
	strcpy(nueva_interaccion->objeto_parametro, objeto_parametro);
	strcpy(nueva_interaccion->verbo, verbo);
	nueva_interaccion->accion = nueva_accion;

	return nueva_interaccion;
}
