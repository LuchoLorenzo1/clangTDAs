#include "sala.h"

#include "utils/hash.h"
#include "utils/lista.h"

#include "estructuras.h"
#include "objeto.h"
#include "interaccion.h"

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
	size_t cantidad_objetos;
	size_t cantidad_interacciones;
	bool escape_exitoso;
};

sala_t *sala_crear_desde_archivos(const char *objetos,
		const char *interacciones)
{
	if (!objetos || !interacciones)
		return NULL;

	FILE *archivo_objetos = fopen(objetos, "r");
	if (!archivo_objetos) {
		return NULL;
	}
	FILE *archivo_interacciones = fopen(interacciones, "r");
	if (!archivo_interacciones) {
		fclose(archivo_objetos);
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
	sala->cantidad_objetos = 0;
	sala->cantidad_interacciones = 0;
	sala->escape_exitoso = false;

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
	sala->cantidad_objetos = hash_cantidad(sala->objetos);

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
		sala->cantidad_interacciones++;
	}

	fclose(archivo_objetos);
	fclose(archivo_interacciones);

	if (sala->cantidad_interacciones == 0 || sala->cantidad_objetos == 0) {
		sala_destruir(sala);
		return NULL;
	}

	return sala;
}

typedef struct vector_char_con_condicion {
	char **nombres;
	int tope;
	bool en_posesion;
	bool conocido;
} vector_char_t;

bool agrega_nombres(const char *nombre, void *nodo_objeto_void,
		void *vector_char_void)
{
	vector_char_t *vector_char = (vector_char_t *)vector_char_void;
	nodo_objeto_t *nodo_objeto = (nodo_objeto_t *)nodo_objeto_void;

	if (vector_char->en_posesion && !nodo_objeto->en_posesion)
		/*  Si necesita estar en posesion, pero no lo esta, sigo con el siguiente  */
		return true;
	if (vector_char->conocido && !nodo_objeto->conocido)
		return true;

	vector_char->nombres[vector_char->tope] = nodo_objeto->objeto->nombre;
	vector_char->tope++;
	return true;
}

char **sala_obtener_nombre_objetos_condicional(sala_t *sala, int *cantidad,
		bool conocido, bool en_posesion)
{
	if (!sala) {
		if (cantidad)
			*cantidad = -1;
		return NULL;
	}

	char **nombres = calloc(hash_cantidad(sala->objetos), sizeof(char *));
	if (!nombres) {
		if (cantidad)
			*cantidad = -1;
		return NULL;
	}

	vector_char_t *vector_char = malloc(sizeof(vector_char_t));
	if (!vector_char) {
		if (cantidad)
			*cantidad = -1;
		free(nombres);
		return NULL;
	}

	vector_char->tope = 0;
	vector_char->nombres = nombres;
	vector_char->en_posesion = en_posesion;
	vector_char->conocido = conocido;

	hash_con_cada_clave(sala->objetos, agrega_nombres, vector_char);

	if (cantidad)
		*cantidad = vector_char->tope;

	free(vector_char);

	return nombres;
}

char **sala_obtener_nombre_objetos(sala_t *sala, int *cantidad)
{
	return sala_obtener_nombre_objetos_condicional(sala, cantidad, false,
			false);
}

char **sala_obtener_nombre_objetos_conocidos(sala_t *sala, int *cantidad)
{
	return sala_obtener_nombre_objetos_condicional(sala, cantidad, true, false);
}

char **sala_obtener_nombre_objetos_poseidos(sala_t *sala, int *cantidad)
{
	return sala_obtener_nombre_objetos_condicional(sala, cantidad, false, true);
}

bool sala_es_interaccion_valida(sala_t *sala, const char *verbo,
		const char *objeto1, const char *objeto2)
{
	if (sala == NULL || verbo == NULL || objeto1 == NULL || objeto2 == NULL)
		return false;

	nodo_objeto_t *nodo_objeto1 =
		(nodo_objeto_t *)hash_obtener(sala->objetos, objeto1);

	if (!nodo_objeto1)
		return false;

	lista_iterador_t *it = lista_iterador_crear(nodo_objeto1->interacciones);
	struct interaccion *interaccion_actual = NULL;

	for (; lista_iterador_tiene_siguiente(it); lista_iterador_avanzar(it)) {
		interaccion_actual = (struct interaccion *)lista_iterador_elemento_actual(it);
		if (strcmp(verbo, interaccion_actual->verbo) == 0) {
			if (strcmp(objeto2,
						interaccion_actual->objeto_parametro) == 0 ||
					strcmp(objeto2, "") == 0) {
				lista_iterador_destruir(it);
				return true;
			}
		}
	}

	lista_iterador_destruir(it);
	return false;
}

bool sala_escape_exitoso(sala_t *sala)
{
	return sala->escape_exitoso;
}

int sala_ejecutar_interaccion_valida(
	sala_t *sala, struct interaccion *interaccion,  nodo_objeto_t *objeto1, nodo_objeto_t *objeto2,
	void (*mostrar_mensaje)(const char *mensaje, enum tipo_accion accion,
				void *aux),
	void *aux)
{
	if(!objeto1->en_posesion && objeto1->objeto->es_asible){
		mostrar_mensaje("Necesitas agarrarlo para poder usarlo", interaccion->accion.tipo, aux);
		return 0;
	}

	nodo_objeto_t *nodo_aux = hash_obtener(sala->objetos, interaccion->accion.objeto);

	switch (interaccion->accion.tipo) {

	case DESCUBRIR_OBJETO:
		if(!nodo_aux || !(objeto1->conocido || objeto1->en_posesion) || objeto2 != NULL){
			mostrar_mensaje("No se como hacer eso", interaccion->accion.tipo, aux);
			return 0;
		}

		if(nodo_aux->conocido || nodo_aux->en_posesion){
			mostrar_mensaje("Nada interesante", interaccion->accion.tipo, aux);
			return 0;
		}

		nodo_aux->conocido = true;
		break;

	case REEMPLAZAR_OBJETO:
		if(!objeto2 || !nodo_aux)
			return 0;
		if((objeto1->conocido || objeto1->en_posesion) && (objeto2->conocido || objeto2->en_posesion)){
			nodo_aux->conocido = objeto2->conocido;
			nodo_aux->en_posesion = objeto2->en_posesion;
			hash_quitar(sala->objetos, objeto2->objeto->nombre);
		}
		break;

	case ELIMINAR_OBJETO:
		if(objeto1->conocido || objeto1->en_posesion){
			if(nodo_aux)
				hash_quitar(sala->objetos, interaccion->accion.objeto);
			else
				return 0;
		}
		break;

	case MOSTRAR_MENSAJE:
		break;

	case ESCAPAR:
		sala->escape_exitoso = true;
		break;

	// case ACCION_INVALIDA:
	default:
		return 0;
		break;
	}
	mostrar_mensaje(interaccion->accion.mensaje, interaccion->accion.tipo, aux);
	return 1;
}

int sala_ejecutar_interaccion(sala_t *sala, const char *verbo,
			      const char *objeto1, const char *objeto2,
			      void (*mostrar_mensaje)(const char *mensaje,
						      enum tipo_accion accion,
						      void *aux),
			      void *aux)
{
	if (!sala || !verbo || !objeto1){
		mostrar_mensaje("Los parametros no son correctos", ACCION_INVALIDA, aux);
		return 0;
	}

	nodo_objeto_t *nodo_objeto1 = (nodo_objeto_t *)hash_obtener(sala->objetos, objeto1);
	if (!nodo_objeto1){
		mostrar_mensaje("No se a que te referis", ACCION_INVALIDA, aux);
		return 0;
	}

	nodo_objeto_t *nodo_objeto2 = (nodo_objeto_t *)hash_obtener(sala->objetos, objeto2);

	struct interaccion *interaccion_actual = NULL;
	lista_iterador_t *it = lista_iterador_crear(nodo_objeto1->interacciones);

	int interacciones_ejecutadas = 0;

	for (; lista_iterador_tiene_siguiente(it); lista_iterador_avanzar(it)) {
		interaccion_actual = (struct interaccion *)lista_iterador_elemento_actual(it);

		if (strcmp(verbo, interaccion_actual->verbo) == 0) {
			if (strcmp(objeto2, "") == 0 || strcmp(objeto2, interaccion_actual->objeto_parametro) == 0) {
				int n = sala_ejecutar_interaccion_valida(sala, interaccion_actual, nodo_objeto1, nodo_objeto2, mostrar_mensaje, aux);
				if(n == 0)
					return 0;
				interacciones_ejecutadas += n;
			}
		}
	}
	if (interacciones_ejecutadas == 0) {
		mostrar_mensaje("No puedo hacer eso", ACCION_INVALIDA, aux);
	}
	return interacciones_ejecutadas;
}

char *sala_describir_objeto(sala_t *sala, const char *nombre_objeto)
{
	if (!sala || !nombre_objeto)
		return NULL;
	nodo_objeto_t *nodo_objeto =
		(nodo_objeto_t *)hash_obtener(sala->objetos, nombre_objeto);

	if (!nodo_objeto)
		return NULL;

	if (nodo_objeto->conocido || nodo_objeto->en_posesion)
		return nodo_objeto->objeto->descripcion;
	return NULL;
}

bool sala_agarrar_objeto(sala_t *sala, const char *nombre_objeto)
{
	if (!sala || !nombre_objeto)
		return false;
	nodo_objeto_t *nodo_objeto = (nodo_objeto_t *)hash_obtener(sala->objetos, nombre_objeto);
	if (!nodo_objeto)
		return false;

	if (nodo_objeto->conocido && nodo_objeto->objeto->es_asible) {
		nodo_objeto->en_posesion = true;
		nodo_objeto->conocido = false;
		return true;
	}

	return false;
}

void destruir_interacciones(void *interaccion)
{
	free(interaccion);
}

void destruir_nodo_objeto(void *nodo_objeto_void)
{
	nodo_objeto_t *nodo_objeto = (nodo_objeto_t *)nodo_objeto_void;
	// lista_destruir_todo(nodo_objeto->interacciones, destruir_interacciones);
	lista_destruir_todo(nodo_objeto->interacciones, free);
	free(nodo_objeto->objeto);
	free(nodo_objeto);
}

void sala_destruir(sala_t *sala)
{
	hash_destruir_todo(sala->objetos, destruir_nodo_objeto);
	free(sala);
}
