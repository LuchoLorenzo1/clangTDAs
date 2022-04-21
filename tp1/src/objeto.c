#include "estructuras.h"
#include "variables.h"

struct objeto *objeto_crear_desde_string(const char *string)
{
        if (string == NULL || strcmp(string, "") == 0)
                return NULL;

        char nombre[MAX_NOMBRE];
	char descripcion[MAX_TEXTO];
        bool es_asible;
        char cadena_bool[6];

        int strings_obtenidas = sscanf(string,"%[^;];%[^;];%[^\n]\n", nombre, descripcion, cadena_bool);

        if (strings_obtenidas != 3)
                return NULL;

        if (strcmp(cadena_bool, "true") == 0)
                es_asible=true;
        else if (strcmp(cadena_bool, "false") == 0)
                es_asible=false;
        else
                return NULL;

        struct objeto *nuevo_objeto = malloc(sizeof(struct objeto));

        if(nuevo_objeto == NULL)
                return NULL;

        strcpy(nuevo_objeto->nombre, nombre);
        strcpy(nuevo_objeto->descripcion, descripcion);
        nuevo_objeto->es_asible = es_asible;

        return nuevo_objeto;
}
