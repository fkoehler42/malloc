#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <malloc.h>

int main()
{
	int 	i = 0;
	size_t	j = 1;
	char	*s = malloc(j);
	char	*t = malloc(j);
	while (i < 16)
		t[i++] = 'A';
	t[i] = '\0';
	i = 0;
	while (i < 100)
		s[i++] = 'B';
	s[i] = '\0';
	printf("\n%s\n", t);
	return 0;
}
