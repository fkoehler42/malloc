#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <malloc.h>

int main()
{
	char	*str1;
	char	*str2;

	str1 = ft_malloc(MAX_ALLOC_SIZE - 1);
	str2 = ft_malloc(-1);
	printf("str1 : %s, str2 : %s\n", str1, str2);
	show_mem(ALL);
	return 0;
}
