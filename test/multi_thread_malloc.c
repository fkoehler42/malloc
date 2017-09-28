#include <malloc.h>

void	*allocate()
{
	int		i;
	char 	*str;

	i = 0;
	while (i < 100)
	{
		str = malloc(420);
		str[0] = 42;
		i++;
	}
	return (NULL);
}

int 	main()
{
	int			i;
	pthread_t	thread_id;

	i = 0;
	while (i < 10)
	{
		if (pthread_create(&thread_id, NULL, allocate, NULL) == 0)
			ft_putstr("thread created\n");
		i++;
	}
	show_mem(ALL);
	return (0);
}
