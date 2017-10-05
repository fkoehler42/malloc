#include <malloc.h>

int main()
{
	char	*str1;
	char	*str2;
	int		i = 0;

	str2 = NULL;
	str1 = malloc(0);
	while (i < 7)
	{
		str1[i] = i + 'a';
		i++;
	}
	str1[i] = 0;
	str2 = malloc(42);
	i = 0;
	while (i < 41)
	{
		str2[i] = (i % 26) + 'A';
		i++;
	}
	str2[i] = 0;
	show_mem(ALLOC);
	ft_putstr("str1 : ");
	ft_putendl(str1);
	return 0;
}
