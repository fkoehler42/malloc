#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <malloc.h>

int main()
{
	char	*str1;
	char	*str2;
	int		i = 0;

	str2 = NULL;
	str1 = ft_malloc(42);
	while (i < 41)
	{
		str1[i] = (i % 26) + 'a';
		i++;
	}
	str1[i] = 0;
	printf("--Memory after malloc(42)--\n");
	show_mem(ALL);
	str2 = ft_realloc(str1, 6);
	str2[5] = 0;
	printf("\n--Memory after realloc(6)--\n");
	show_mem(ALL);
	return 0;
}
