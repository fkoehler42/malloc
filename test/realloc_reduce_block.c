/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_reduce_block.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 15:49:49 by fkoehler          #+#    #+#             */
/*   Updated: 2017/10/09 18:00:43 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int	main(void)
{
	char	*str1;
	char	*str2;

	str1 = (char*)malloc(54);
	ft_putstr("--Memory after malloc of 54--\n");
	show_mem(ALL);
	str2 = (char*)realloc(str1, 6);
	ft_putstr("\n--Memory after realloc of 6--\n");
	show_mem(ALL);
	if (str1 == str2)
		ft_putstr("str1 == str2, realloc has kept the same address\n");
	else
		ft_putstr("str1 != str2, realloc has changed the allocation address\n");
	return (0);
}
