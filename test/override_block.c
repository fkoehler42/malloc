#include <malloc.h>

int main()
{
	int		i;
	char 	*str;
	char 	*str2;

	i = 0;
	str = malloc(42);
	str2 = malloc(60);
	show_alloc_mem();
	while (i < 49)
	{
		str[i] = (i % 26) + 'a';
		i++;
	}
	free(str2);
	return 0;
}
