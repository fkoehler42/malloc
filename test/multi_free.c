/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 15:43:04 by fkoehler          #+#    #+#             */
/*   Updated: 2017/10/09 17:56:30 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int	main(void)
{
	int		i;
	size_t	j;
	char	*s;

	i = 0;
	j = 1024;
	while (i < (int)j)
	{
		s = (char*)malloc(j);
		s[0] = 42;
		free(s);
		i++;
	}
	show_mem(ALL);
	return (0);
}
