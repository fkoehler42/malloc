#include <malloc.h>

int main()
{
	char *s = malloc(42);
	s[0] = 42;
	free(s);
	return 0;
}
