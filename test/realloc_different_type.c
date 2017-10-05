#include <malloc.h>

int main()
{
	char	*str1;
	char	*str2;

	str2 = NULL;
	str1 = malloc(42);
	ft_putstr("--Memory after malloc of 42 bytes (TINY)--\n");
	show_mem(ALL);
	str2 = realloc(str1, 4200);
	ft_putstr("\n--Memory after realloc of 4200 (SMALL)--\n");
	show_mem(ALL);
	if (str1 == str2)
		ft_putstr("str1 == str2, realloc has kept the same address\n");
	else
		ft_putstr("str1 != str2, realloc has changed the allocation address\n");
	return 0;
}
