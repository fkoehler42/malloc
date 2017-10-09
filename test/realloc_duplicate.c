#include "../includes/malloc.h"

int main()
{
	int		i;
	char	*str1;
	char	*str2;

	i = 0;
	str1 = malloc(27);
	str2 = malloc(12);
	ft_putstr("--Memory after malloc of 27 and 12--\n");
	show_mem(ALL);
	while (i < 26)
	{
		str1[i] = i + 'a';
		i++;
	}
	str1[i] = 0;
	str2 = realloc(str1, 42);
	ft_putstr("\n--Memory after realloc of 42--\n");
	show_mem(ALL);
	ft_putstr("str2 = ");
	ft_putendl(str2);
	if (str1 == str2)
		ft_putstr("str1 == str2, realloc has kept the same address\n");
	else
		ft_putstr("str1 != str2, realloc has changed the allocation address\n");
	return (0);
}
