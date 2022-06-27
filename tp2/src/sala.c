#include "estructuras.h"
#include "utils/hash.h"
#include "utils/lista.h"
#include "objeto.h"
#include "interaccion.h"
#include "sala.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NOMBRE 20
#define MAX_LINEA 200
#define MAX_VERBO 20
#define MAX_TEXTO 200

typedef struct nodo_objeto {
	struct objeto *objeto;
	lista_t *interacciones;
	bool en_posesion;
	bool conocido;
} nodo_objeto_t;

typedef struct sala {
	hash_t *objetos;
} sala_t;

sala_t *sala_crear_desde_archivos(const char *objetos,
				  const char *interacciones)
{
	FILE *archivo_objetos = fopen(objetos, "r");
	FILE *archivo_interacciones = fopen(interacciones, "r");

	if (!archivo_objetos || !archivo_interacciones) {
		fclose(archivo_objetos);
		fclose(archivo_interacciones);
		return NULL;
	}

	sala_t *sala = malloc(sizeof(sala_t));
	if (!sala) {
		fclose(archivo_objetos);
		fclose(archivo_interacciones);
		return NULL;
	}

	hash_t *diccionario_objetos = hash_crear(10);

	if (!diccionario_objetos) {
		fclose(archivo_objetos);
		fclose(archivo_interacciones);
		free(sala);
		return NULL;
	}

	sala->objetos = diccionario_objetos;

	char linea[MAX_LINEA];
	while (fgets(linea, MAX_LINEA, archivo_objetos) != NULL) {
		struct objeto *objeto = objeto_crear_desde_string(linea);
		nodo_objeto_t *nodo_objeto = malloc(sizeof(nodo_objeto_t));
		if (!objetos || !nodo_objeto) {
			free(objeto);
			free(nodo_objeto);
			continue;
		}

		lista_t *lista_interacciones = lista_crear();
		if (!lista_interacciones) {
			free(objeto);
			free(nodo_objeto);
			continue;
		}

		nodo_objeto->en_posesion = false;
		nodo_objeto->objeto = objeto;
		nodo_objeto->interacciones = lista_interacciones;
		nodo_objeto->conocido = hash_cantidad(sala->objetos) == 0;

		hash_insertar(sala->objetos, objeto->nombre, nodo_objeto, NULL);
	}

	while (fgets(linea, MAX_LINEA, archivo_interacciones) != NULL) {
		struct interaccion *interaccion =
			interaccion_crear_desde_string(linea);

		if (interaccion == NULL)
			continue;

		hash_obtener(sala->objetos, interaccion->objeto);
	}

	fclose(archivo_objetos);
	fclose(archivo_interacciones);

	// if (sala->cantidad_interacciones == 0 || sala->cantidad_objetos == 0) {
	//         sala_destruir(sala);
	//         return NULL;
	// }

	return sala;
}

char **sala_obtener_nombre_objetos(sala_t *sala, int *cantidad)
{
	return NULL;
}

bool sala_es_interaccion_valida(sala_t *sala, const char *verbo,
				const char *objeto1, const char *objeto2)
{
	return false;
}

void sala_destruir(sala_t *sala)
{
}
