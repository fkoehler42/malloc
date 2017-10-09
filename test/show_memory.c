#include "../includes/malloc.h"

int main()
{
	int 	i;
	char	*ptr;

	i = -1;
	ptr = malloc(24);
	ptr = malloc(42);
	while (++i < 42)
		ptr[i] = i;
	ptr = malloc(1024);
	ft_putstr("\n---show_alloc_mem---\n");
	show_alloc_mem();
	ft_putstr("\n---show_free_mem---\n");
	show_mem(FREE);
	ft_putstr("\n---show_all_mem---\n");
	show_mem(ALL);
	ft_putstr("\n---show_mem_dump---\n");
	show_mem(DUMP);
	return 0;
}
