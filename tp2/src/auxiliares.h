#ifndef __AUXILIARES_H_
#define __AUXILIARES_H_

#include "hash.h"
#include "lista.h"
#include "estructuras.h"


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
	bool escape_exitoso;
};

/*
 * Recibe un nombre y un struct en void pointer de vector_char_t,
 * que contiene el vector de nombres a donde debe ser agregado el nombre si es que cupmle con las condiciones dadas.
 */
bool agrega_nombres(const char *nombre, void *nodo_objeto_void, void *vector_char_void);

/*
 * generaliza la funcion de sala_obtener_nombre_objetos, recibiendo dos booleanos (conocido y en_posesion),
 * para que los objetos que agreguen su nombre al vector sean los que cumplan las condiciones
 */

char **sala_obtener_nombre_objetos_condicional(sala_t *sala, int *cantidad, bool conocido, bool en_posesion);

/*
 * Recibe un nodo_objeto_t y libera su memoria.
 */
void destruir_nodo_objeto(void *nodo_objeto_void);

#endif /* __INTERNAS_H___ */
