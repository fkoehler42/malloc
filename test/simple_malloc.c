#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <malloc.h>

int main()
{
	char *str;

	str = ft_malloc(42);
	str[0] = 42;
	return 0;
}
