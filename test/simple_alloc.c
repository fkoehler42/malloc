#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <malloc.h>

int main()
{
	char	*s = ft_malloc(42);
	s[0] = 42;
	return 0;
}