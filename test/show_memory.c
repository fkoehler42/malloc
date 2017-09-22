#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <malloc.h>

int main()
{
	ft_malloc(42);
	ft_malloc(420);
	ft_malloc(1024);
	ft_malloc(24903);
	ft_malloc(9924900);

	ft_printf("\n---show_alloc_mem---\n");
	show_alloc_mem();
	ft_printf("\n---show_free_mem---\n");
	show_mem(FREE);
	ft_printf("\n---show_all_mem---\n");
	show_mem(ALL);
	return 0;
}
