#include <malloc.h>

int main()
{
	char	*str1;
	char	*str2;

	str1 = malloc(MAX_ALLOC_SIZE - 1);
	str2 = malloc(-1);
	ft_printf("str1 : %s, str2 : %s\n", str1, str2);
	show_mem(ALL);
	return 0;
}
