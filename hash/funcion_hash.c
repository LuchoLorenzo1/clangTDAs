#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tamanio 30
#define constante 0.618033988

size_t funcion_hash1(const char *cadena)
{
	double n = constante * (double)strlen(cadena) *
		   ((double)cadena[0] + (double)cadena[strlen(cadena) - 1]);
	return (size_t)((double)tamanio * (n - (size_t)n));
}

size_t funcion_hash2(const char *cadena)
{
	int clave = 0;
	for (size_t i = 0; i < strlen(cadena); i = (i + 1) * 2) {
		clave += cadena[i];
	}

	return (strlen(cadena) * clave) % tamanio;
}

int main(int argc, char *argv[])
{
	char *lista[20] = { "di maria",	       "messi",
			    "de paul",	       "paredes",
			    "papu gomez",      "otamendi",
			    "cuti romero",     "kun aguero",
			    "dybala",	       "julian alvarez",
			    "guido rodriguez", "molina",
			    "scaloni",	       "lautaro martinez",
			    "dibu martinez",   "huevo acuna",
			    "mac allister",    "nico gonzalez",
			    "angel correa",    "menem" };

	int *array1 = calloc(tamanio, sizeof(int));
	if (!array1)
		return -1;
	int *array2 = calloc(tamanio, sizeof(int));
	if (!array2) {
		free(array1);
		return -1;
	}

	for (size_t i = 0; i < 20; i++) {
		array1[funcion_hash1(lista[i])]++;
	};
	for (size_t i = 0; i < tamanio; i++) {
		printf("%d, ", array1[i]);
	}
	printf("\n");

	for (size_t i = 0; i < 20; i++) {
		array2[funcion_hash2(lista[i])]++;
	};
	for (size_t i = 0; i < tamanio; i++) {
		printf("%d, ", array2[i]);
	}
	printf("\n");

	free(array1);
	free(array2);
}
