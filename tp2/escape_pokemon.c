#include "src/sala.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if(argc != 3){
		printf("Los parametros nos son correctos.\n");
                return -1;
        }

	sala_t *sala = sala_crear_desde_archivos(argv[1], argv[2]);

	if (sala == NULL) {
		printf("Error al crear la sala de escape\n");
		return -1;
	}

	printf("Objetos...\n");

        int cantidad_nombres = 0;

        char **nombres = sala_obtener_nombre_objetos(sala, &cantidad_nombres);

        if(nombres == NULL) {
                sala_destruir(sala);
                return -1;
        }

        for (int i = 0; i < cantidad_nombres; i++) {
                printf("%d. %s\n", i, nombres[i]);
        }

        free(nombres);

        printf("\nInteracciones...\n");

        bool interaccion1 = sala_es_interaccion_valida(sala, "examinar", "habitacion", "");
        bool interaccion2 = sala_es_interaccion_valida(sala, "abrir", "pokebola", "");
        bool interaccion3 = sala_es_interaccion_valida(sala, "usar", "llave", "cajon");
        bool interaccion4 = sala_es_interaccion_valida(sala, "qumar", "mesa", "");

        printf("Examinar la habitación: %s\n", interaccion1 ? "Válido" : "Inválido");
        printf("Abrir pokebola: %s\n", interaccion2 ? "Valido" : "Inválido");
        printf("Usar llave en el cajón: %s\n", interaccion3 ? "Válido" : "Inválido");
        printf("Quemar la mesa: %s\n", interaccion4 ? "Válido" : "Inválido");

	sala_destruir(sala);

	return 0;
}
