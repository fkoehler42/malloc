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
	str1 = ft_malloc(2700);
	while (i < 41)
	{
		str1[i] = (i % 26) + 'a';
		i++;
	}
	str1[i] = 0;
	printf("--Memory after malloc(2700)--\n");
	show_mem(ALL);
	str2 = ft_realloc(str1, 3200);
	printf("\n--Memory after realloc(3200)--\n");
	show_mem(ALL);
	return 0;
}
