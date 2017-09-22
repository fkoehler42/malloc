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

	show_alloc_mem();
	return 0;
}
