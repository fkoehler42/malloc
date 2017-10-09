/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_zero.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 15:41:55 by fkoehler          #+#    #+#             */
/*   Updated: 2017/10/09 17:57:29 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int	main(void)
{
	char	*str1;
	char	*str2;
	int		i;

	i = 0;
	str2 = NULL;
	str1 = (char*)malloc(0);
	while (i < 7)
	{
		str1[i] = i + 'a';
		i++;
	}
	str1[i] = 0;
	str2 = (char*)malloc(42);
	i = 0;
	while (i < 41)
	{
		str2[i] = (i % 26) + 'A';
		i++;
	}
	str2[i] = 0;
	show_mem(ALLOC);
	ft_putstr("str1 : ");
	ft_putendl(str1);
	return (0);
}
