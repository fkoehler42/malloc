#include <malloc.h>

int main()
{
	char	*str1;
	char	*str2;
	int		i = 0;

	str2 = NULL;
	str1 = ft_malloc(0);
	while (i < 23)
	{
		str1[i] = i + 'a';
		i++;
	}
	str1[i] = 0;
	str2 = ft_malloc(42);
	i = 0;
	while (i < 41)
	{
		str2[i] = (i % 26) + 'A';
		i++;
	}
	str2[i] = 0;
	show_mem(ALL);
	printf("str1 : %s\nstr2 : %s\n", str1, str2);
	return 0;
}
