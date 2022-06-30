#include "src/sala.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NOMBRE 20
#define MAX_LINEA 200
#define MAX_VERBO 20
#define MAX_TEXTO 200


void mostrar_mensaje(const char *mensaje, enum tipo_accion accion, void *aux)
{
	if(!mensaje)
		return;
	printf("%s\n", mensaje);
}

int main(int argc, char *argv[])
{
	if (argc != 3) {
		printf("Los parametros nos son correctos.\n");
		return -1;
	}

	sala_t *sala = sala_crear_desde_archivos(argv[1], argv[2]);
	if (sala == NULL) {
		printf("Error al crear la sala de escape\n");
		return -1;
	}

	printf("Bienvenido a la sala de escape! \n");

	char comando[MAX_VERBO];
	char objeto1[MAX_NOMBRE];
	char objeto2[MAX_NOMBRE];
	char linea[MAX_LINEA];

	// game loop
	while (!sala_escape_exitoso(sala)) {
		printf("> ");
		fgets(linea, MAX_LINEA, stdin);
		sscanf(linea, "%s %s %s", comando, objeto1, objeto2);

		if (strcmp(comando, "ayuda") == 0) {

			printf("comandos: \n * ayuda \n * agarrar \n * describir \n * listar (objetos|inventario) \n * [verbo] [objeto1] [objeto2] \n salir \n");

		} else if (strcmp(comando, "describir") == 0) {

			char *descripcion = sala_describir_objeto(sala, objeto1);
			if (!descripcion) {
				printf("No conozco ese objeto \n");
				continue;
			}
			printf("%s\n", descripcion);

		} else if (strcmp(comando, "agarrar") == 0) {

			bool agarrado = sala_agarrar_objeto(sala, objeto1);
			if (!agarrado) {
				printf("No podes agarrar eso\n");
				continue;
			}

			printf("Nuevo item adquirido: %s\n", objeto1);

		} else if (strcmp(comando, "listar") == 0){

			int cantidad = 0;
			char **vector_nombres;

			if(strcmp(objeto1, "objetos") == 0){
				vector_nombres = sala_obtener_nombre_objetos_conocidos(sala, &cantidad);
				if(!vector_nombres || cantidad == 0){
					printf("No hay objetos conocidos\n");
					continue;
				}
			}
			else if(strcmp(objeto1, "inventario") == 0){
				vector_nombres = sala_obtener_nombre_objetos_poseidos(sala, &cantidad);
				if(!vector_nombres || cantidad == 0){
					printf("No hay nada en el inventario\n");
					continue;
				}
			}
			else {
				printf("No puedo listar eso\n");
				continue;
			}

			for (int i = 0; i < cantidad; i++) {
				printf("%d. %s\n", i, vector_nombres[i]);
			}
		} else if (strcmp(comando, "salir") == 0 && strcmp(objeto1, "") == 0 && strcmp(objeto2, "") == 0) {
			sala_destruir(sala);
			return 0;
		}
		else {
			sala_ejecutar_interaccion(sala, comando, objeto1, objeto2, mostrar_mensaje, NULL);
		}
		strcpy(comando, "");
		strcpy(objeto1, "");
		strcpy(objeto2, "");
	}
	sala_destruir(sala);
	return 0;
}
