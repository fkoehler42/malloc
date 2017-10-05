#include <malloc.h>

int main()
{
	void	*str1;
	void	*str2;
	void	*str3;

	str1 = malloc(MAX_ALLOC_SIZE);
	str2 = malloc(MAX_ALLOC_SIZE + 1);
	str3 = malloc(-1);
	ft_putstr("str1 malloc return : 0x");
	ft_put_uintmax((size_t)str1, 16);
	ft_putstr("\nstr2 malloc return : 0x");
	ft_put_uintmax((size_t)str2, 16);
	ft_putstr("\nstr3 malloc return : 0x");
	ft_put_uintmax((size_t)str3, 16);
	return 0;
}
