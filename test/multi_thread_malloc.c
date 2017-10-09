/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_thread_malloc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 15:44:04 by fkoehler          #+#    #+#             */
/*   Updated: 2017/10/09 17:59:56 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	*allocate(void)
{
	int		i;
	char	*str;

	i = 0;
	while (i < 21)
	{
		str = (char*)malloc(12200);
		str[0] = 42;
		i++;
	}
	return (NULL);
}

int		main(void)
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
