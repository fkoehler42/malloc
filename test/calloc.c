/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 15:40:44 by fkoehler          #+#    #+#             */
/*   Updated: 2017/10/09 17:55:31 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int	main(void)
{
	int		i;
	char	*str;
	char	*str2;

	i = 0;
	str = (char*)malloc(100);
	while (i < 100)
	{
		str[i] = i;
		i++;
	}
	free(str);
	str2 = calloc(5, 20);
	show_mem(DUMP);
	if (str == str2)
		ft_putstr("calloc has used the address of the previous malloc\n");
	else
		ft_putstr("calloc has used a new address\n");
	return (0);
}
