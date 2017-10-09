/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_enlarge_block.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 15:49:21 by fkoehler          #+#    #+#             */
/*   Updated: 2017/10/09 18:00:36 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int	main(void)
{
	char	*str1;
	char	*str2;

	str2 = NULL;
	str1 = (char*)malloc(2700);
	ft_putstr("--Memory after malloc(2700)--\n");
	show_mem(ALL);
	str2 = (char*)realloc(str1, 3200);
	ft_putstr("\n--Memory after realloc(3200)--\n");
	show_mem(ALL);
	if (str1 == str2)
		ft_putstr("str1 == str2, realloc has kept the same address\n");
	else
		ft_putstr("str1 != str2, realloc has changed the allocation address\n");
	return (0);
}
