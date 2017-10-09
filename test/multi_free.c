#include "../includes/malloc.h"

int main()
{
	int 	i = 0;
	size_t	j = 1024;
	char	*s;
	while (i < (int)j)
	{
		s = malloc(j);
		s[0] = 42;
		free(s);
		i++;
	}
	show_mem(ALL);
	return 0;
}
