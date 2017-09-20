#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <malloc.h>

int main()
{
	int		i;
	char 	*str;
	char 	*str2;

	i = 0;
	str = ft_malloc(42);
	show_alloc_mem();
	while (i < 41)
	{
		str[i] = (i % 26) + 'a';
		i++;
	}
	str[i] = '\0';

	str2 = ft_malloc(60);
	show_alloc_mem();
	i = 0;
	while (i < 100)
	{
		str2[i] = (i % 26) + 'A';
		i++;
	}
	ft_free(str2);
	/* str2[i] = '\0'; */
	show_alloc_mem();
	/* printf("\n%s\n%s\n", str, str2); */
	return 0;
}
