#include <malloc.h>

int main()
{
	char *s;

	s = malloc(42);
	s[0] = 42;

/*
 ** Comment the lines to check the different error cases :
 ** double free, bad address into/out of mapping range
 */
	free(s);
	free(s);
	free(s + 10);
	free(s - 1000000);
	return (0);
}
