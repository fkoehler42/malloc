#include <malloc.h>

int main()
{
	char *str;

	str = malloc(42);
	str[0] = 42;
	return 0;
}
