#include "src/sala.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

	printf("Bienvenido a la sala de escape! \n");
	// game loop
	char *comando;
	char *objeto1;
	char *objeto2;
	while(sala_escape_exitoso(sala)){
		scanf("%s %s %s", comando, objeto1, objeto2);

		if(strcmp(comando, "ayuda") == 0){
			printf("comandos: \n * ayuda \n * agarrar \n * describir \n * [verbo] [objeto1] [objeto2]");
		} else if(strcmp(comando, "describir") == 0){
			char *descripcion = sala_describir_objeto(sala, objeto1);
			if (!descripcion){
				printf("No conozco ese objeto \n");
				continue;
			}
			printf("%s\n", descripcion);
		} else if(strcmp(comando, "agarrar") == 0){
			bool agarrado = sala_agarrar_objeto(sala, objeto1);
			if(!agarrado){
				printf("No podes agarrar eso\n");
				continue;
			}
			printf("Nuevo item adquirido: %s\n", objeto1);
		} else {
			if(!objeto2)
				objeto2 = "";
			bool valida = sala_es_interaccion_valida(sala, comando, objeto1, objeto2);
			if(!valida)
				printf("No podes hacer eso\n");
			printf("es muy buena interaccion, cuando lo implemente la ejecuto\n");
		}

	}
	printf("FELICIDADES! ESCAPASTE DE LA SALA! LIBERTAD!!! \n");
	sala_destruir(sala);
	return 0;
}
