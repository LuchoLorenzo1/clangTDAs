#include "estructuras.h"
#include "utils/hash.h"
#include "utils/lista.h"
#include "objeto.h"
#include "interaccion.h"
#include "sala.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

struct sala {
	hash_t *objetos;
};

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

		nodo_objeto_t *nodo_objeto = (nodo_objeto_t *)hash_obtener(
			sala->objetos, interaccion->objeto);

		if (!nodo_objeto) {
			free(interaccion);
			continue;
		}
		lista_insertar(nodo_objeto->interacciones, interaccion);
	}

	fclose(archivo_objetos);
	fclose(archivo_interacciones);
	return sala;
}

typedef struct vector_char {
	char **nombres;
	size_t tope;
} vector_char_t;

bool agrega_nombres(const char *nombre, void *nodo_objeto_void,
		    void *vector_char_void)
{
	vector_char_t *vector_char = (vector_char_t *)vector_char_void;
	nodo_objeto_t *nodo_objeto = (nodo_objeto_t *)nodo_objeto_void;

	vector_char->nombres[vector_char->tope] = nodo_objeto->objeto->nombre;
	vector_char->tope++;
	return true;
}

char **sala_obtener_nombre_objetos(sala_t *sala, int *cantidad)
{
	if (!cantidad)
		return NULL;
	if (!sala) {
		*cantidad = -1;
		return NULL;
	}

	// char **nombres = malloc((unsigned int)sala->cantidad_objetos * sizeof(char*));
	char **nombres = calloc(hash_cantidad(sala->objetos), sizeof(char *));
	if (!nombres) {
		*cantidad = -1;
		return NULL;
	}
	vector_char_t *vector_char = malloc(sizeof(vector_char_t));
	if (!vector_char) {
		*cantidad = -1;
		free(nombres);
		return NULL;
	}

	vector_char->tope = 0;
	vector_char->nombres = nombres;

	size_t recorridos =
		hash_con_cada_clave(sala->objetos, agrega_nombres, vector_char);
	free(vector_char);

	if (cantidad)
		*cantidad = (int)recorridos;

	return nombres;
}

bool sala_es_interaccion_valida(sala_t *sala, const char *verbo,
				const char *objeto1, const char *objeto2)
{
	if (sala == NULL || verbo == NULL || objeto2 == NULL)
		return false;

	nodo_objeto_t *nodo_objeto1 =
		(nodo_objeto_t *)hash_obtener(sala->objetos, objeto1);
	// nodo_objeto_t *nodo_objeto2 =
		// (nodo_objeto_t *)hash_obtener(sala->objetos, objeto2);

	return true;
}

void destruir_interacciones(void *interaccion)
{
	free(interaccion);
}

void destruir_nodo_objeto(void *nodo_objeto_void)
{
	nodo_objeto_t *nodo_objeto = (nodo_objeto_t *)nodo_objeto_void;
	lista_destruir_todo(nodo_objeto->interacciones, destruir_interacciones);
	free(nodo_objeto->objeto);
	free(nodo_objeto);
}
void sala_destruir(sala_t *sala)
{
	hash_destruir_todo(sala->objetos, destruir_nodo_objeto);
	free(sala);
}
