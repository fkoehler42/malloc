/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   override_block.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 15:44:58 by fkoehler          #+#    #+#             */
/*   Updated: 2017/10/09 17:58:28 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int	main(void)
{
	int		i;
	char	*str;
	char	*str2;

	i = 0;
	str = (char*)malloc(42);
	str2 = (char*)malloc(60);
	show_alloc_mem();
	while (i < 49)
	{
		str[i] = (i % 26) + 'a';
		i++;
	}
	free(str2);
	return (0);
}
