#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <malloc.h>

int main()
{
	int 	i = 0;
	size_t	j = 1024;
	char	*s;
	while (i < (int)j)
	{
		s = ft_malloc(j);
		s[0] = 42;
		i++;
	}
	return 0;
}
