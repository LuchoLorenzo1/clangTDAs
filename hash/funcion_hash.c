#include <stdio.h>
#include <string.h>

#define tamanio 40
#define constante 0.618033988

size_t funcion_hash(const char *cadena)
{
	double n = constante * (double)strlen(cadena) *
		   ((double)cadena[0] + (double)cadena[strlen(cadena) - 1]);
	return (size_t)((double)tamanio * (n - (size_t)n));
}

size_t funcion_hash2(const char *cadena)
{
	return (strlen(cadena) + cadena[0] + cadena[strlen(cadena) - 1]) %
	       tamanio;
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

	int array[40] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	for (size_t i = 0; i < 20; i++) {
		array[funcion_hash2(lista[i])]++;
	};
	for (size_t i = 0; i < tamanio; i++) {
		printf("%zu: %d\n", i, array[i]);
	}
}
