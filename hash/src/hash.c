#include <math.h>
#include "hash.h"
#include <string.h>

#define constante 0.618033988

typedef struct nodo nodo_t;

struct nodo {
	char *clave;
	int valor;
	nodo_t *siguiente;
};

struct hash {
	nodo_t *claves;
	size_t cantidad_maxima;
	size_t cantidad_actual;
};

int funcion_hash(hash_t hash, char *cadena)
{
	if (!cadena)
		return 0;
	int clave = strlen(cadena) * (cadena[0] * cadena[strlen(cadena) - 1]);
	double n = clave * constante;
	int parte_entera_n = (int)n;
	return (int)(hash.cantidad_maxima * (n - parte_entera_n));
}

hash_t *hash_crear(size_t capacidad)
{
	return NULL;
}

hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento,
		      void **anterior)
{
	return hash;
}

void *hash_quitar(hash_t *hash, const char *clave)
{
	return NULL;
}

void *hash_obtener(hash_t *hash, const char *clave)
{
	return NULL;
}

bool hash_contiene(hash_t *hash, const char *clave)
{
	return false;
}

size_t hash_cantidad(hash_t *hash)
{
	return 0;
}

void hash_destruir(hash_t *hash)
{
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
}

size_t hash_con_cada_clave(hash_t *hash,
			   bool (*f)(const char *clave, void *valor, void *aux),
			   void *aux)
{
	return 0;
}
