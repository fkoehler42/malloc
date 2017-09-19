#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <malloc.h>

int main()
{
	char	*s;

	s = ft_malloc(42);
	s = ft_malloc(420);
	s = ft_malloc(1024);
	s = ft_malloc(24903);
	s = ft_malloc(9924900);

	show_alloc_mem();
	return 0;
}
