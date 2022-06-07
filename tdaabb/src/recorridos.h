#ifndef __RECORRIDOS__H__
#define __RECORRIDOS__H__

#include "abb.h"

/**
 * Se encarga recorrer recursivamente el ABB con recorrido inorden
 * y ejecutar la funcion pasada por parametro con cada elemento del arbol hasta que el bool continuar deje de ser true.
 */
size_t recorrer_inorden(nodo_abb_t *nodo, bool (*funcion)(void *, void *),
			void *aux, bool *continuar);
/**
 * Se encarga recorrer recursivamente el ABB con recorrido preorden
 * y ejecutar la funcion pasada por parametro con cada elemento del arbol hasta que el bool continuar deje de ser true.
 */
size_t recorrer_preorden(nodo_abb_t *nodo, bool (*funcion)(void *, void *),
			 void *aux, bool *continuar);
/**
 * Se encarga recorrer recursivamente el ABB con recorrido postorden
 * y ejecutar la funcion pasada por parametro con cada elemento del arbol hasta que el bool continuar deje de ser true.
 */
size_t recorrer_postorden(nodo_abb_t *nodo, bool (*funcion)(void *, void *),
			  void *aux, bool *continuar);
#endif /* __RECORRIDOS__H__ */
