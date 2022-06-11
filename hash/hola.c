#include <stdio.h>
int main(int argc, char *argv[])
{
	size_t n = 10;
	size_t p = 4;
	int r = 4;

	size_t total = r + p;

	printf("%zu\n", n % p);
	printf("%zu\n", n + p + r);
	return 0;
}
