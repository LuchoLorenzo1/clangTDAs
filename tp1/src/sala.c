#include "estructuras.h"
#include "sala.h"
#include "objeto.h"
#include "interaccion.h"
#include "variables.h"

void agregar_vector_objetos(struct objeto ***vector, struct objeto *elemento, int *cantidad_actual)
{
        if (cantidad_actual == NULL || elemento == NULL)
                return;

        struct objeto **nuevo_bloque = realloc(*vector, (unsigned int)(*cantidad_actual + 1) * sizeof(struct objeto*));

        if(nuevo_bloque == NULL)
                return;

        nuevo_bloque[*cantidad_actual] = elemento;

        *vector = nuevo_bloque;
         (*cantidad_actual)++;
}

void agregar_vector_interacciones(struct interaccion ***vector, struct interaccion *elemento, int *cantidad_actual)
{
        if (cantidad_actual == NULL || elemento == NULL)
                return;

        struct interaccion **nuevo_bloque = realloc(*vector, (unsigned int)(*cantidad_actual + 1) * sizeof(struct interaccion*));

        if (nuevo_bloque == NULL)
                return;

        nuevo_bloque[*cantidad_actual] = elemento;

        *vector = nuevo_bloque;
         (*cantidad_actual)++;
}


sala_t *sala_crear_desde_archivos(const char *objetos, const char *interacciones)
{
        FILE *archivo_objetos = fopen(objetos, "r");
        FILE *archivo_interacciones = fopen(interacciones, "r");

        if (archivo_objetos == NULL || archivo_interacciones == NULL)
                return NULL;

        sala_t *sala = malloc(sizeof(struct sala));

        if (sala == NULL) {
                fclose(archivo_objetos);
                fclose(archivo_interacciones);
                return NULL;
        }

        sala->cantidad_objetos = 0;
        sala->cantidad_interacciones = 0;
        sala->objetos = NULL;
        sala->interacciones = NULL;

        char linea[MAX_LINEA];

        while(fgets(linea, MAX_LINEA, archivo_objetos) != NULL){
                 struct objeto *puntero_objeto = objeto_crear_desde_string(linea);

                 if (puntero_objeto == NULL)
                         continue;

                 agregar_vector_objetos(&sala->objetos, puntero_objeto, &(sala->cantidad_objetos));
        }

        while(fgets(linea, MAX_LINEA, archivo_interacciones) != NULL){
                 struct interaccion *puntero_interaccion = interaccion_crear_desde_string(linea);

                 if (puntero_interaccion == NULL)
                         continue;

                 agregar_vector_interacciones(&sala->interacciones, puntero_interaccion, &(sala->cantidad_interacciones));
        }

        fclose(archivo_objetos);
        fclose(archivo_interacciones);

        if (sala->cantidad_interacciones == 0 || sala->cantidad_objetos == 0) {
                sala_destruir(sala);
                return NULL;
        }

        return sala;
}

char **sala_obtener_nombre_objetos(sala_t *sala, int *cantidad)
{

        if (sala == NULL) {
                if (cantidad != NULL)
                        *cantidad = -1;
                return NULL;
        }

        if (cantidad != NULL)
                *cantidad = sala->cantidad_objetos;

        char **nombres = malloc((unsigned int)sala->cantidad_objetos * sizeof(char*));

        if (nombres == NULL) {
                if (cantidad != NULL)
                        *cantidad = -1;
                return NULL;
        }

        for(int i = 0; i < sala->cantidad_objetos; i++) {
                nombres[i] = sala->objetos[i]->nombre;
        }

	return nombres;
}

bool sala_es_interaccion_valida(sala_t *sala, const char *verbo, const char *objeto1, const char *objeto2)
{
        if (sala == NULL || verbo == NULL || objeto2 == NULL)
                return false;

        for (int i = 0; i < sala->cantidad_interacciones; i++) {
                if (strcmp(sala->interacciones[i]->verbo, verbo) == 0 && strcmp(sala->interacciones[i]->objeto, objeto1) == 0) {
                        if (strcmp(sala->interacciones[i]->objeto_parametro, objeto2) == 0 || strcmp(objeto2, VACIO) == 0)
                                return true;
                }
        }

	return false;
}

void sala_destruir(sala_t *sala)
{
        for(int i = 0; i < sala->cantidad_objetos ; i++) {
                free(sala->objetos[i]);
        }
        free(sala->objetos);
        for(int i = 0; i < sala->cantidad_interacciones ; i++) {
                free(sala->interacciones[i]);
        }
        free(sala->interacciones);
        free(sala);
}
