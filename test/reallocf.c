#include <malloc.h>

int main()
{
	char	*str1;
	char	*str2;

	str1 = malloc(27000);
	ft_putstr("\n--Memory after oversized realloc--\n");
	str2 = realloc(str1, -1);
	show_mem(ALL);
	if (str2 == NULL)
	{
		ft_putstr("realloc has returned null\n");
		ft_putstr("\n--Memory after oversized reallocf--\n");
		str2 = reallocf(str1, -1);
		show_mem(ALL);
		if (str2 == NULL)
			ft_putstr("reallocf has returned null\n");
	}
	return (0);
}
