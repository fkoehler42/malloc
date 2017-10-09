#include "../includes/malloc.h"

int main()
{
	int		i;
	char	*str;
	char	*str2;

	i = 0;
	str = malloc(100);
	while (i < 100)
	{
		str[i] = i;
		i++;
	}
	free(str);
	str2 = calloc(5, 20);
	show_mem(DUMP);
	if (str == str2)
		ft_putstr("calloc has taken the address space of the previous malloc\n");
	else
		ft_putstr("calloc has taken a different address from the previous malloc\n");
	return (0);
}
