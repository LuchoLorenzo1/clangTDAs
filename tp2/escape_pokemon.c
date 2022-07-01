#include "src/sala.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_OPCION 20
#define MAX_LINEA 200
#define MAX_COMANDO 20
#define BLANCO "\x1b[37;1m"
#define VERDE "\x1b[32;1m"
#define ERROR "\x1b[31;1m"
#define AMARILLO "\x1b[33;1m"
#define AZUL "\x1b[34;1m"
#define NORMAL "\x1b[0m"
#define FIN "\033[0m\n"
#define ITEM "*"

void mostrar_mensaje(const char *mensaje, enum tipo_accion accion, void *aux)
{
	if(!mensaje)
		return;
	printf("%s\n", mensaje);
}

int main(int argc, char *argv[])
{
	if (argc != 3) {
		printf(ERROR "Los parametros nos son correctos.\n");
		return -1;
	}

	sala_t *sala = sala_crear_desde_archivos(argv[1], argv[2]);
	if (sala == NULL) {
		printf("Error al crear la sala de escape\n");
		return -1;
	}

	printf("Bienvenido a la sala de escape! \n");

	char comandos[][MAX_LINEA] = {"ayuda","agarrar","describir","listar (objetos|inventario)","[verbo] [objeto1] [objeto2]","salir"};
	size_t cantidad_comandos = sizeof(comandos) / sizeof(comandos[0]);
	char comando[MAX_COMANDO] = "";
	char objeto1[MAX_OPCION] = "";
	char objeto2[MAX_OPCION] = "";
	char linea[MAX_LINEA];


	// game loop
	while (!sala_escape_exitoso(sala)) {
		printf("> ");
		fgets(linea, MAX_LINEA, stdin);
		sscanf(linea, "%s %s %s", comando, objeto1, objeto2);

		if (strcmp(comando, "ayuda") == 0) {
			for (size_t i = 0; i < cantidad_comandos; i++) {
				printf(AZUL ITEM AMARILLO " %s" FIN, comandos[i]);
			}

		} else if (strcmp(comando, "describir") == 0) {

			char *descripcion = sala_describir_objeto(sala, objeto1);
			if (!descripcion) {
				printf(ERROR "No conozco ese objeto" FIN);
				continue;
			}
			printf(AZUL "%s" FIN, descripcion);

		} else if (strcmp(comando, "agarrar") == 0) {

			bool agarrado = sala_agarrar_objeto(sala, objeto1);
			if (!agarrado) {
				printf(ERROR "No podes agarrar eso" FIN);
				continue;
			}

			printf(VERDE "Nuevo item adquirido: %s" FIN, objeto1);

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
				printf(ERROR "No puedo listar eso" FIN);
				continue;
			}

			for (int i = 0; i < cantidad; i++) {
				printf("%d. %s\n", i, vector_nombres[i]);
			}
		} else if (strcmp(comando, "salir") == 0 && strcmp(objeto1, "") == 0) {
			printf(ERROR "TE QUEDASTE ATRAPADO PARA SIEMPRE" FIN);
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
