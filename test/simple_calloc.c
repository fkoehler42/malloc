#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <malloc.h>

int main()
{
	int		i = 0;
/**
** first malloc to keep the same block address after freeing str later
**/
	 char	*str = ft_malloc(100);

	str = ft_malloc(27);
	while (i < 26)
	{
		str[i] = i + 'a';
		i++;
	}
	str[i] = '\0';

	i = 0;
	ft_free(str);
	str = ft_malloc(27);
	printf("Content of block %p using malloc : %s\n", str, str);


	i = 0;
	ft_free(str);
	str = ft_calloc(1, 27);
	printf("Content of block %p using calloc : %s\n", str, str);

	return 0;
}
