#include <malloc.h>

int main()
{
	char *str;

	str = malloc(42);
	str[0] = 42;
	show_mem(ALL);
	return (0);
}
