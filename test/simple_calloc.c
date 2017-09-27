#include <malloc.h>

int main()
{
	int		i = 0;
/**
** first malloc to keep the same block address after freeing str later
**/
	char	*str = malloc(100);

	str = malloc(27);
	while (i < 26)
	{
		str[i] = i + 'a';
		i++;
	}
	str[i] = '\0';

	i = 0;
	free(str);
	str = malloc(27);
	ft_printf("Content of block %p using malloc : %s\n", str, str);


	i = 0;
	free(str);
	str = calloc(1, 27);
	ft_printf("Content of block %p using calloc : %s\n", str, str);
	return 0;
}
