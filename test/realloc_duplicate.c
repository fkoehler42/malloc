/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_duplicate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 15:47:18 by fkoehler          #+#    #+#             */
/*   Updated: 2017/10/09 18:00:30 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int	main(void)
{
	int		i;
	char	*str1;
	char	*str2;

	i = 0;
	str1 = (char*)malloc(27);
	str2 = (char*)malloc(12);
	ft_putstr("--Memory after malloc of 27 and 12--\n");
	show_mem(ALL);
	while (i < 26)
	{
		str1[i] = i + 'a';
		i++;
	}
	str1[i] = 0;
	str2 = (char*)realloc(str1, 42);
	ft_putstr("\n--Memory after realloc of 42--\n");
	show_mem(ALL);
	ft_putstr("str2 = ");
	ft_putendl(str2);
	if (str1 == str2)
		ft_putstr("str1 == str2, realloc has kept the same address\n");
	else
		ft_putstr("str1 != str2, realloc has changed the allocation address\n");
	return (0);
}
