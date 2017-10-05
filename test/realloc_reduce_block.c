#include <malloc.h>

int main()
{
	char	*str1;
	char	*str2;

	str1 = malloc(54);
	ft_putstr("--Memory after malloc of 54--\n");
	show_mem(ALL);
	str2 = realloc(str1, 6);
	ft_putstr("\n--Memory after realloc of 6--\n");
	show_mem(ALL);
	if (str1 == str2)
		ft_putstr("str1 == str2, realloc has kept the same address\n");
	else
		ft_putstr("str1 != str2, realloc has changed the allocation address\n");
	return (0);
}
