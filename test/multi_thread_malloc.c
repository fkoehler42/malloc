#include "../includes/malloc.h"

void	*allocate()
{
	int		i;
	char 	*str;

	i = 0;
	while (i < 21)
	{
		str = malloc(12200);
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
		if (pthread_create(&thread_id, NULL, allocate, NULL) != 0)
		{
			ft_putstr("Error on thread creation\n");
			exit(1);
		}
		i++;
	}
	sleep(1);
	show_mem(ALL);
	return (0);
}
