#include <malloc.h>

int main()
{
	void	*ptr;

	ptr = malloc(42);
	ptr = malloc(420);
	ptr = malloc(1024);
	ptr = malloc(24903);
	ptr = malloc(9924900);

	ft_printf("\n---show_alloc_mem---\n");
	show_alloc_mem();
	ft_printf("\n---show_free_mem---\n");
	show_mem(FREE);
	ft_printf("\n---show_all_mem---\n");
	show_mem(ALL);
	return 0;
}
